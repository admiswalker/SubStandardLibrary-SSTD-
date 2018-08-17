#include "c2py.hpp"
#include "str2num.hpp"

/*
 * NumPy の内部型を定義できれば事足りる．
 * 
 *  bool:  b
 *   int:  i,   char:  c,  int8: i8,  int16: i16,  int32: i32,  int64: i64
 *  uint: ui,  uchar: uc, uint8: u8, uint16: u16, uint32: u32, uint64: u64
 * float:  f, double:  d
 * 
 * bool*, len:  b*, len
 *  int*, len:  i*, len,     char*, len:  c*, len,    int8*, len:  i8, len,    int16*, len: i16*, len,    int32*, len: i32*, len,    int64*, len: i64*, len
 * uint*, len: ui*, len,    uchar*, len: uc*, len,   uint8*, len: u8*, len,   uint16*, len: u16*, len,   uint32*, len: u32*, len,   uint64*, len: u64*, len
 * float*, size, len: f*,   double*, size, len: d*
 * 
 * * * * * * * *
 * 
 *       std::vector<T>
 *       std::vector<T>*
 * const std::vector<T>*
 * 
 *       std::vector<std::vector<T>>
 *       std::vector<std::vector<T>>*
 * const std::vector<std::vector<T>>*
 * 
 * * * * * * * *
 * 
 *                         std::string  : str
 *             std::vector<std::string> : vecs
 * std::vector<std::vector<std::string>>: vvecs
 * 
 */

  /*
	Table 1. How to parse format. ([T]: ture, [F]: false, [x]: no type, vec<T>: std::vector<T>)
    ---------------------------------------------------------------------------------------------------
                                                                                       | python side |
     input string         -> parse to                    -> struct typeSet                    conve-
                               std::vector<std::string>   constTF   type          poi-   poi- rt2bu-
                                                                    name      T   nter* nter* iltIn~
    ---------------------------------------------------------------------------------------------------
	 int                  -> "int"                       -> [F], ["int32"], ["x"], [F],  [F],  [F]
	 int*                 -> "int", "*"                  -> [F], ["int32"], ["x"], [T],  [F],  [F]
	 int|~                -> "int", "~"                  -> [F], ["int32"], ["x"], [F],  [F],  [T]
	 int*|~               -> "int", "*", "~"             -> [F], ["int32"], ["x"], [T],  [T],  [T]
	 int|~*               -> "int", "~", "*"             -> [F], ["int32"], ["x"], [F],  [T],  [T]
    ---------------------------------------------------------------------------------------------------
	       vec<T>         ->          "vec", "T"         -> [F], [ "vec" ], ["T"], [F],  [F],  [F]
	       vec<T>*        ->          "vec", "T", "*"    -> [F], [ "vec" ], ["T"], [T],  [F],  [F]
	 const vec<T>*        -> "const", "vec", "T", "*"    -> [T], [ "vec" ], ["T"], [T],  [F],  [F]
    ---------------------------------------------------------------------------------------------------

	・unsigned long int, unsigned long long int 等々，割と命名規則が微妙なものも多いので，
      独自フォーマットとする．結局何 bits なのかよくわからないことも理由．

	・リファレンス参照は，項目を用意したが，可変長引数である va_list の実装上不可能であると分かった．(他に使用する予定もないので削除してもよい．)

    +------------------------------------------------------------------------------------------------------------------+
	| struct typeSet{                                                                                                  |
 	|    bool constTF;                 // true: ポインタの先の書き戻しを行う．false: ポインタの先の書き戻しを行わない．     |
 	|                                  // const-> true, not const -> false.                                            |
 	|    std::string name; char N_num; // void, int, vec<T>... and so on. // number of value                           |
 	|    std::string    T; char T_num; // template<typename "T"> or ""    // number of value                           |
 	|    bool pointer;                 // *                                                                            |
 	|    bool convert2builtIn;         // ~                                                                            |
 	| };                                                                                                               |
 	+------------------------------------------------------------------------------------------------------------------+
	Fig 1. "struct sstd_c2py::typeSet" from "c2py.hpp"
 */

//------------------------------------------------------------------------------------------------------------------------------------

// const と ret が同時に true となることはないが，処理の都合で，別に TF を設ける．
//                           ret const   vec     <type>    * |  *    ~
// "const vec<type>*|*~" ->  [F], [T], ["vec"], ["type"], [T], [T], [T] 0
//   "ret vec<type>*|*~" ->  [T], [F], ["vec"], ["type"], [T], [T], [T] 0
//                            0    1      2         3      4    5    6  7

#define elOffSet 7 // off set number for elements

//------------------------------------------------------------------------------------------------------------------------------------

// enum XXX{}; を使うと良い感じに数値を与えられるが，undef できないので，グローバル空間の汚染は回避できない．
// -> ヘッダから切り離したので，そのうち enum に変更する．??? -> enum だと，あくまで変数扱いなのでは??? (遅い)

#define   void_num  0

#define   bool_num  1
#define   char_num  2
#define  uchar_num  3

#define   int8_num  4
#define  int16_num  5
#define  int32_num  6
#define  int64_num  7

#define  uint8_num  8
#define uint16_num  9
#define uint32_num 10
#define uint64_num 11

#define  float_num 12
#define double_num 13

#define    len_num 14

#define    str_num 15
#define    vec_num 16 // std::vector<T>
#define   vvec_num 17 // std::vector<std::vector<T>>
#define    mat_num 18 // sstd::mat<T>
#define  mat_r_num 19 // sstd::mat_r<T>

//------------------------------------------------------------------------------------------------------------------------------------

// Does a "str" take shape of XXX<T>? (something like, vec<double>, sstd::mat<double>, sstd::mat_r<double>, ...)
//  - When "str"=="vec<double>" -> retType=="vec" and retTempT=="double" will be returnd.
bool Is_type_tempT(const std::string& str, std::string& retType, std::string& retTempT){
	retType.clear(); retTempT.clear();

	bool flagL=false, flagR=false;
	uint i=0;
	for(; str[i]!=0; i++){
		if(str[i]=='<'){ flagL=true; i++; break;
		}      else    { retType+=str[i]; }
	}
	for(; str[i]!=0; i++){
		if(str[i]=='>'){ flagR=true; break;
		}      else    { retTempT+=str[i]; }
	}
	if(i!=str.size()-1 && flagL==true && flagR==true){ sstd::pdbg("ERROR: Invalid token. There is something after '>'.\n"); return false; }
	if(flagL==true  && flagR==false){ sstd::pdbg("ERROR: Invalid token. '>' is not found while there is '<'.\n"); return false; }
	if(flagL==false && flagR==true ){ sstd::pdbg("ERROR: Invalid token. '<' is not found while there is '>', or order of '<' and '>' is incorrect.\n"); return false; }
	
	return (retTempT.size()!=0);
}

//------------------------------------------------------------------------------------------------------------------------------------

bool split_leftStr(const char* pStr, struct sstd_c2py::typeSet& f, std::string& fS){
	uint len=strlen(pStr);
	
	if(fS.size()<len){ return false; }

	uint i=0;
	for(; i<len; i++){
		if(pStr[i]!=fS[i]){ return false; }
	}

	// remove "const " and additional space.
	fS = sstd::removeHeadSpace((const uchar*)&fS[i]);
	return true;
}
void split_ret  (struct sstd_c2py::typeSet& f, std::string& fS){ f.retTF   = split_leftStr(R"(ret )", f, fS);   }
void split_const(struct sstd_c2py::typeSet& f, std::string& fS){ f.constTF = split_leftStr(R"(const )", f, fS); }
void split_pointer(struct sstd_c2py::typeSet& f, std::string& fS){
	for(int i=fS.size()-1; i>=0; i--){
		if      (fS[i]=='*'){ fS.erase(--fS.end()); f.pointer=true;
		}else if(fS[i]==' '){ fS.erase(--fS.end()); // 末尾を 1 文字削除
		}        else       { break; }
	}
}
void split_verticalLine(struct sstd_c2py::typeSet& f, std::string& fS){
	std::vector<std::string> verLineLR = sstd::split(fS, '|'); // split by vertical line
	fS=std::move(verLineLR[0]); // copy L (Left value)
	if(verLineLR.size()==2){ // evaluation of R (Right value)
		for(uint i=0; i<verLineLR[1].size(); i++){
			if      (verLineLR[1][i]=='*'){ f.pointer_sidePy    =true; // *: pointer type sybol on python side                      // on right than vertical line '|' as a symbol of split
			}else if(verLineLR[1][i]=='~'){ f.cnv2builtIn_sidePy=true; // ~: conversion command to built in function on python side // on right than vertical line '|' as a symbol of split
			}else if(verLineLR[1][i]==' '){ // pass
			}             else            { sstd::pdbg("ERROR: \"%s\" has invalid token.\n", verLineLR[1].c_str()); }
		}
	}else if(verLineLR.size()>=3){ sstd::pdbg("ERROR: \"%s\" has too many vartical line '|'.\n", fS.c_str());
	}else{}
}
bool setTandT_num(struct sstd_c2py::typeSet& out, std::string& in){
	if      (sstd::strcmp(in,  "bool")){ out.T=  "bool"; out.T_num=  bool_num;
	}else if(sstd::strcmp(in,  "char")){ out.T=  "char"; out.T_num=  char_num;
	}else if(sstd::strcmp(in, "uchar")){ out.T= "uchar"; out.T_num= uchar_num;
	}else if(sstd::strcmp(in,   "int")){ out.T= "int32"; out.T_num= int32_num;
	}else if(sstd::strcmp(in,  "int8")){ out.T=  "int8"; out.T_num=  int8_num;
	}else if(sstd::strcmp(in, "int16")){ out.T= "int16"; out.T_num= int16_num;
	}else if(sstd::strcmp(in, "int32")){ out.T= "int32"; out.T_num= int32_num;
	}else if(sstd::strcmp(in, "int64")){ out.T= "int64"; out.T_num= int64_num;
	}else if(sstd::strcmp(in, "uint8")){ out.T= "uint8"; out.T_num= uint8_num;
	}else if(sstd::strcmp(in,"uint16")){ out.T="uint16"; out.T_num=uint16_num;
	}else if(sstd::strcmp(in,"uint32")){ out.T="uint32"; out.T_num=uint32_num;
	}else if(sstd::strcmp(in,"uint64")){ out.T="uint64"; out.T_num=uint64_num;
	}else if(sstd::strcmp(in, "float")){ out.T= "float"; out.T_num= float_num;
	}else if(sstd::strcmp(in,"double")){ out.T="double"; out.T_num=double_num;
	}else if(sstd::strcmp(in,"string")){ out.T=   "str"; out.T_num=   str_num;
	}else if(sstd::strcmp(in,   "str")){ out.T=   "str"; out.T_num=   str_num;
	}else{ return false; }
	return true;
}
bool IsNext_Len(const std::vector<std::string>& fSList, const std::vector<struct sstd_c2py::typeSet>& fList, uint& i){
	if(i<(fList.size()-1)){
		if(sstd::strcmp(fSList[i+1],"len")){ return true; }
	}
	if(!(fList[i].N_num== char_num&&fList[i].pointer)&&
	   !(fList[i].N_num==  vec_num&&fList[i].pointer)&&
	   !(fList[i].N_num==  mat_num&&fList[i].pointer)&&
	   !(fList[i].N_num==mat_r_num&&fList[i].pointer)){
		sstd::pdbg("ERROR: \"%s\": Next of a pointer type (T*) must be len (len is a length of pointer and treated as a uint32), without \"char*\", \"str* (std::string*)\", \"vec<T>* (std::vector<T>*)\", \"mat<T>* (sstd::mat<T>*)\" and \"mat_r<T>* (sstd::mat_r<T>*)\".\n", fSList[i].c_str());
	}
	// uint32 as a len type is better than uint64.
	// Because in the case of "uint64 x; x = 123", "123" is a uint32 type while the user dosen't type "123ull" and 
	// x will sometimes be substituted illigal value (as a broken uint64 value force to read 64 bits from 32 bits data size).
	// Same problem will be happen to call poerator().
	return false;
}
bool IsPrevious_pointer(const std::vector<std::string>& fSList, const std::vector<struct sstd_c2py::typeSet>& fList, uint i){
	if(i>0 && fList[i-1].pointer){ return true; }
	sstd::pdbg("ERROR: \"%s\": Previous of a len type must be a type of pointer.\n", fSList[i].c_str());
	return false;
}
bool IsPrevious_pChar(const std::vector<std::string>& fSList, const std::vector<struct sstd_c2py::typeSet>& fList, uint i){
	if(i>0 && fList[i-1].N_num==char_num && fList[i-1].pointer==true){
		sstd::pdbg("ERROR: \"%s\": Previous of a len type can't have \"char*\". Because \"char*\" check its length by \"strlen()\" and doesn't need to be send its length.\n", fSList[i].c_str());
	}
	return false;
}
std::vector<struct sstd_c2py::typeSet> sstd_c2py::format_str2typeSet(const std::vector<std::string>& fSList){
	std::vector<struct sstd_c2py::typeSet> fList(fSList.size());
	std::string type, tempT;
	for(uint i=0; i<fList.size(); i++){
		std::string fS = fSList[i];
		split_const       (fList[i], fS); // "const type*|*~" -> "const", "type*|*~"
		split_ret         (fList[i], fS); //   "ret type*|*~" ->   "ret", "type*|*~"
		split_verticalLine(fList[i], fS); //                              "type*|*~" -> "type*", "*~"           // vartical line is just a splitting symbol
		split_pointer     (fList[i], fS); //                                            "type*" -> "type",  "*" // setting "true" or "false" of pointer
		if      (sstd::strcmp(fS,  "void")){ fList[i].name=  "void"; fList[i].N_num=  void_num; if(fList[i].pointer){ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
		}else if(sstd::strcmp(fS,  "bool")){ fList[i].name=  "bool"; fList[i].N_num=  bool_num;
		}else if(sstd::strcmp(fS,  "char")){ fList[i].name=  "char"; fList[i].N_num=  char_num; if(fList[i].pointer&& IsNext_Len(fSList, fList, i)){ sstd::pdbg("ERROR: \"%s\": Previous of a len type can't have \"char*\". Because \"char*\" check its length by \"strlen()\" and doesn't need to be send its length.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
		}else if(sstd::strcmp(fS, "uchar")){ fList[i].name= "uchar"; fList[i].N_num= uchar_num;
		}else if(sstd::strcmp(fS,   "int")){ fList[i].name= "int32"; fList[i].N_num= int32_num;
		}else if(sstd::strcmp(fS,  "int8")){ fList[i].name=  "int8"; fList[i].N_num=  int8_num;
		}else if(sstd::strcmp(fS, "int16")){ fList[i].name= "int16"; fList[i].N_num= int16_num;
		}else if(sstd::strcmp(fS, "int32")){ fList[i].name= "int32"; fList[i].N_num= int32_num;
		}else if(sstd::strcmp(fS, "int64")){ fList[i].name= "int64"; fList[i].N_num= int64_num;
		}else if(sstd::strcmp(fS, "uint8")){ fList[i].name= "uint8"; fList[i].N_num= uint8_num;
		}else if(sstd::strcmp(fS,"uint16")){ fList[i].name="uint16"; fList[i].N_num=uint16_num;
		}else if(sstd::strcmp(fS,"uint32")){ fList[i].name="uint32"; fList[i].N_num=uint32_num;
		}else if(sstd::strcmp(fS,"uint64")){ fList[i].name="uint64"; fList[i].N_num=uint64_num;
		}else if(sstd::strcmp(fS, "float")){ fList[i].name= "float"; fList[i].N_num= float_num;
		}else if(sstd::strcmp(fS,"double")){ fList[i].name="double"; fList[i].N_num=double_num;
		}else if(sstd::strcmp(fS,   "len")){ fList[i].name=   "len"; fList[i].N_num=   len_num; if(!IsPrevious_pointer(fSList, fList, i)){ sstd::pdbg("ERROR: \"%s\": Previous of a len type must be a pointer type without \"char*\". Because \"char*\" check its length by \"strlen()\" and doesn't need to be send its length.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
		}else if(sstd::strcmp(fS,"string")){ fList[i].name=   "str"; fList[i].N_num=   str_num;
		}else if(sstd::strcmp(fS,   "str")){ fList[i].name=   "str"; fList[i].N_num=   str_num;
		}else if(Is_type_tempT(fS, type, tempT)){
			// Example: fS=="vec<double>"
			//  - type =="vec"
			//  - tempT=="double"
			if      (sstd::strcmp(type,  "vec")){ fList[i].name="vec";   fList[i].N_num=vec_num;   if(!setTandT_num(fList[i], tempT)){ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
			}else if(sstd::strcmp(type,  "mat")){ fList[i].name="mat";   fList[i].N_num=mat_num;   if(!setTandT_num(fList[i], tempT)){ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
			}else if(sstd::strcmp(type,"mat_r")){ fList[i].name="mat_r"; fList[i].N_num=mat_r_num; if(!setTandT_num(fList[i], tempT)){ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
			}else{ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
		}else{
			if(fSList[i].size()==0){ sstd::pdbg("ERROR: There is a empty token. (There might be invalid \",\".)\n");
			}else{ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); }
			return std::vector<struct sstd_c2py::typeSet>(0);
		}
	}
	return fList;
}
std::string sstd_c2py::format_typeSet2str(const std::vector<struct sstd_c2py::typeSet>& fList){
	// make "./tempDir/[unixtime]_[microsec]/argList.bin"
	//-----------------------------------------------------------------------
	// Example of "int32" format:          _____F F int32 x F F F 0
	//                                    /      /    |   |  ＼＼＼＼___.
	//                             constTF, retTF, type, <T>, *, *, ~, NumOfArrElements
	//-----------------------------------------------------------------------
	// Example of "int32*" format:         _____F F int32 x T F F 1 L___________________
	//                                    /      /    |   |  ＼＼＼＼___.               ＼
	//                             constTF, retTF, type, <T>, *, *, ~, NumOfArrElements, ArrSize
	//-----------------------------------------------------------------------
	//                                                   row length    col length
	//                                                            ＼   /
	// Example of "const mat<T>*~" format: _____F T mat <T> T F T 2 R C 0_______________
	//                                    /      /   |   |   ＼＼＼＼___.               ＼
	//                             constTF, retTF, type, <T>, *, *, ~, NumOfArrElements, If "T" is a std::string, num of string length will be continue.
	//-----------------------------------------------------------------------
	
	std::string typeStr;
	if(fList.size()!=0){
		typeStr += "T "; // fList[0].retTF              ? "T ":"F "; // Whether explicit or not, fList[0] is a return value.
		typeStr += fList[0].constTF            ? "T ":"F ";
		typeStr += fList[0].name;
		typeStr += fList[0].T.size()!=0        ? ' '+fList[0].T:" x";
		typeStr += fList[0].pointer            ? " T":" F";
		typeStr += fList[0].pointer_sidePy     ? " T":" F";
		typeStr += fList[0].cnv2builtIn_sidePy ? " T":" F";
		
		// 型例外 (配列サイズを渡す)
		// 戻り値のサイズは確定していなので，渡すことはできない．このため，0 埋めする．
		typeStr += sstd::ssprintf(" %lu", fList[0].arrLen.size());
	}
	for(uint i=1; i<fList.size(); i++){
		typeStr += "\n";
		
		typeStr += fList[i].retTF              ? "T ":"F ";
		typeStr += fList[i].constTF            ? "T ":"F ";
		typeStr += fList[i].name;
		typeStr += fList[i].T.size()!=0        ? ' '+fList[i].T:" x";
		typeStr += fList[i].pointer            ? " T":" F";
		typeStr += fList[i].pointer_sidePy     ? " T":" F";
		typeStr += fList[i].cnv2builtIn_sidePy ? " T":" F";
		
		// 型例外 (配列サイズを渡す) (sstd::ssprintf() は比較的重いので，呼び出し回数を抑える．)
		if      (fList[i].N_num==str_num                             ){ typeStr += sstd::ssprintf(" %u %u",    fList[i].arrLen.size(), fList[i].arrLen[0]);
		}else if(fList[i].N_num==vec_num && fList[i].T_num==str_num  ){ typeStr += sstd::ssprintf(" %u",       fList[i].arrLen.size()); for(uint v=0; v<fList[i].arrLen.size(); v++){ typeStr += sstd::ssprintf(" %lu", fList[i].arrLen[v]); }
		}else if(fList[i].N_num==vec_num                             ){ typeStr += sstd::ssprintf(" %u %u",    fList[i].arrLen.size(), fList[i].arrLen[0]);
		}else if(fList[i].N_num==vvec_num                            ){ typeStr += sstd::ssprintf(" %u %u %u", fList[i].arrLen.size(), fList[i].arrLen[0], fList[i].arrLen[1]);
		}else if(fList[i].N_num==mat_num && fList[i].T_num==str_num  ){ typeStr += sstd::ssprintf(" %u",       fList[i].arrLen.size()); for(uint v=0; v<fList[i].arrLen.size(); v++){ typeStr += sstd::ssprintf(" %lu", fList[i].arrLen[v]); }
		}else if(fList[i].N_num==mat_num                             ){ typeStr += sstd::ssprintf(" %u %u %u", fList[i].arrLen.size(), fList[i].arrLen[0], fList[i].arrLen[1]);
		}else if(fList[i].N_num==mat_r_num && fList[i].T_num==str_num){ typeStr += sstd::ssprintf(" %u",       fList[i].arrLen.size()); for(uint v=0; v<fList[i].arrLen.size(); v++){ typeStr += sstd::ssprintf(" %lu", fList[i].arrLen[v]); }
		}else if(fList[i].N_num==mat_r_num                           ){ typeStr += sstd::ssprintf(" %u %u %u", fList[i].arrLen.size(), fList[i].arrLen[0], fList[i].arrLen[1]);
		}else if(fList[i].pointer                                    ){ typeStr += sstd::ssprintf(" %u %u",    fList[i].arrLen.size(), fList[i].arrLen[0]);
		}                           else                              { typeStr += sstd::ssprintf(" %u",       fList[i].arrLen.size()); }
	}
	return typeStr;
}
bool sstd_c2py::make_argList(const std::string& writeDir_base, std::string typeStr){
	sstd::file fp;
	std::string writeDir = sstd::ssprintf("%s/argList.bin", writeDir_base.c_str());
	if(!fp.fopen(writeDir.c_str(), "wb")){ sstd::pdbg("ERROR: fopen was failed. (%s can't open.)\n", writeDir.c_str()); return false; }
	fp.fwrite(&typeStr[0], sizeof(char), typeStr.size());
	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------

bool sstd_c2py::isRetVoid(std::vector<struct sstd_c2py::typeSet>& fList){ return void_num==fList[0].N_num; }

//------------------------------------------------------------------

bool sstd_c2py::c2py_ret(  bool& inOut, sstd::file& fp, std::string& line){ return (0!=fp.fread(&inOut,sizeof(  bool),1)); }
bool sstd_c2py::c2py_ret(  char& inOut, sstd::file& fp, std::string& line){ return (0!=fp.fread(&inOut,sizeof(  char),1)); }
//bool sstd_c2py::c2py_ret( uchar& inOut, sstd::file& fp, std::string& line){ return (0!=fp.fread(&inOut,sizeof( ucahr),1)); } // same as uint8
bool sstd_c2py::c2py_ret(  int8& inOut, sstd::file& fp, std::string& line){ return (0!=fp.fread(&inOut,sizeof(  int8),1)); }
bool sstd_c2py::c2py_ret( int16& inOut, sstd::file& fp, std::string& line){ return (0!=fp.fread(&inOut,sizeof( int16),1)); }
bool sstd_c2py::c2py_ret( int32& inOut, sstd::file& fp, std::string& line){ return (0!=fp.fread(&inOut,sizeof( int32),1)); }
bool sstd_c2py::c2py_ret( int64& inOut, sstd::file& fp, std::string& line){ return (0!=fp.fread(&inOut,sizeof( int64),1)); }
bool sstd_c2py::c2py_ret( uint8& inOut, sstd::file& fp, std::string& line){ return (0!=fp.fread(&inOut,sizeof( uint8),1)); } // same as uchar
bool sstd_c2py::c2py_ret(uint16& inOut, sstd::file& fp, std::string& line){ return (0!=fp.fread(&inOut,sizeof(uint16),1)); }
bool sstd_c2py::c2py_ret(uint32& inOut, sstd::file& fp, std::string& line){ return (0!=fp.fread(&inOut,sizeof(uint32),1)); }
bool sstd_c2py::c2py_ret(uint64& inOut, sstd::file& fp, std::string& line){ return (0!=fp.fread(&inOut,sizeof(uint64),1)); }
bool sstd_c2py::c2py_ret( float& inOut, sstd::file& fp, std::string& line){ return (0!=fp.fread(&inOut,sizeof( float),1)); }
bool sstd_c2py::c2py_ret(double& inOut, sstd::file& fp, std::string& line){ return (0!=fp.fread(&inOut,sizeof(double),1)); }
bool sstd_c2py::c2py_ret(std::string& inOut, sstd::file& fp, std::string& line){
	uint len = fp.fsize();
	inOut.resize(len);
	fp.fread(&inOut[0], sizeof(char), len); return true;
}

#define c2py_ret_vec(type)											\
	uint len = fp.fsize()/sizeof(type);								\
	inOut.resize(len);												\
	if(0!=fp.fread(&inOut[0],sizeof(type),len)){ return true;		\
	}                  else                    { return false; }
// std:vector<bool> は，8 bits に 1 要素ではなく，1 bits に 1 要素格納する仕様になっている．// メモ: 類似した型に std::bitset, std::deque がある．
// 処理上扱いにくいので，sstd::vec<T> の実装も考慮すべき．
bool sstd_c2py::c2py_ret(std::vector<  bool>& inOut, sstd::file& fp, std::string& line){
	uint len = fp.fsize()/sizeof(bool);
	std::vector<uchar> vecBuf(len);
	inOut.resize(len);
	if(0!=fp.fread(&vecBuf[0],sizeof(bool),len)){
		for(uint i=0; i<vecBuf.size(); i++){ inOut[i]=(bool)vecBuf[i]; }
		return true;
	}else{ return false; }
}
bool sstd_c2py::c2py_ret(std::vector<  char>& inOut, sstd::file& fp, std::string& line){ c2py_ret_vec(  int8); }
bool sstd_c2py::c2py_ret(std::vector<  int8>& inOut, sstd::file& fp, std::string& line){ c2py_ret_vec(  int8); }
bool sstd_c2py::c2py_ret(std::vector< int16>& inOut, sstd::file& fp, std::string& line){ c2py_ret_vec( int16); }
bool sstd_c2py::c2py_ret(std::vector< int32>& inOut, sstd::file& fp, std::string& line){ c2py_ret_vec( int32); }
bool sstd_c2py::c2py_ret(std::vector< int64>& inOut, sstd::file& fp, std::string& line){ c2py_ret_vec( int64); }
bool sstd_c2py::c2py_ret(std::vector< uint8>& inOut, sstd::file& fp, std::string& line){ c2py_ret_vec( uint8); }
bool sstd_c2py::c2py_ret(std::vector<uint16>& inOut, sstd::file& fp, std::string& line){ c2py_ret_vec(uint16); }
bool sstd_c2py::c2py_ret(std::vector<uint32>& inOut, sstd::file& fp, std::string& line){ c2py_ret_vec(uint32); }
bool sstd_c2py::c2py_ret(std::vector<uint64>& inOut, sstd::file& fp, std::string& line){ c2py_ret_vec(uint64); }
bool sstd_c2py::c2py_ret(std::vector< float>& inOut, sstd::file& fp, std::string& line){ c2py_ret_vec( float); }
bool sstd_c2py::c2py_ret(std::vector<double>& inOut, sstd::file& fp, std::string& line){ c2py_ret_vec(double); }
bool sstd_c2py::c2py_ret(std::vector<std::string>& inOut, sstd::file& fp, std::string& line){
	// getting size of return value
	std::vector<std::string> elements = sstd::split(line.c_str(), ' ');

	uint vecLen=sstd::str2int(elements[elOffSet]);
	inOut.resize(vecLen);
	for(uint i=0; i<vecLen; i++){
		inOut[i].resize(sstd::str2int(elements[elOffSet+1+i]));
	}
	
	// write back
	for(uint i=0; i<inOut.size(); i++){
		fp.fread(&inOut[i][0], sizeof(char), inOut[i].size());
	}
	return true;
}

// definition for column-major and row-major type of matrix.
#define c2py_ret_matCR(matType, type)									\
	/* getting size of return value */									\
	std::vector<std::string> elements = sstd::split(line.c_str(), ' ');	\
	uint rows=sstd::str2int(elements[elOffSet+1]);						\
	uint cols=sstd::str2int(elements[elOffSet+2]);						\
																		\
	/* write back */													\
	matType<type> buf(rows, cols);										\
	fp.fread(&buf[0], sizeof(type), rows*cols);							\
	inOut = buf;														\
	return true;
#define c2py_ret_matCR_str(matType, type)								\
	/* getting size of return value */									\
	std::vector<std::string> elements = sstd::split(line.c_str(), ' ');	\
																		\
	uint rows   = sstd::str2int(elements[elOffSet+1]);					\
	uint cols   = sstd::str2int(elements[elOffSet+2]);					\
	uint matLen = rows*cols;											\
	matType<type> buf(rows, cols);										\
	for(uint i=0; i<matLen; i++){										\
		buf[i].resize(sstd::str2int(elements[elOffSet+3+i]));			\
	}																	\
																		\
	/* write back */													\
	for(uint i=0; i<buf.len(); i++){									\
		fp.fread(&buf[i][0], sizeof(char), buf[i].size());				\
	}																	\
	sstd::move(inOut, buf);												\
	return true;
bool sstd_c2py::c2py_ret(sstd::mat<       bool>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat,        bool); }
bool sstd_c2py::c2py_ret(sstd::mat<       char>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat,        char); }
bool sstd_c2py::c2py_ret(sstd::mat<       int8>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat,        int8); }
bool sstd_c2py::c2py_ret(sstd::mat<      int16>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat,       int16); }
bool sstd_c2py::c2py_ret(sstd::mat<      int32>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat,       int32); }
bool sstd_c2py::c2py_ret(sstd::mat<      int64>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat,       int64); }
bool sstd_c2py::c2py_ret(sstd::mat<      uint8>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat,       uint8); }
bool sstd_c2py::c2py_ret(sstd::mat<     uint16>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat,      uint16); }
bool sstd_c2py::c2py_ret(sstd::mat<     uint32>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat,      uint32); }
bool sstd_c2py::c2py_ret(sstd::mat<     uint64>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat,      uint64); }
bool sstd_c2py::c2py_ret(sstd::mat<      float>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat,       float); }
bool sstd_c2py::c2py_ret(sstd::mat<     double>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat,      double); }
bool sstd_c2py::c2py_ret(sstd::mat<std::string>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR_str(sstd::mat, std::string); }
bool sstd_c2py::c2py_ret(sstd::mat_r<       bool>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_r,        bool); }
bool sstd_c2py::c2py_ret(sstd::mat_r<       char>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_r,        char); }
bool sstd_c2py::c2py_ret(sstd::mat_r<       int8>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_r,        int8); }
bool sstd_c2py::c2py_ret(sstd::mat_r<      int16>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_r,       int16); }
bool sstd_c2py::c2py_ret(sstd::mat_r<      int32>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_r,       int32); }
bool sstd_c2py::c2py_ret(sstd::mat_r<      int64>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_r,       int64); }
bool sstd_c2py::c2py_ret(sstd::mat_r<      uint8>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_r,       uint8); }
bool sstd_c2py::c2py_ret(sstd::mat_r<     uint16>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_r,      uint16); }
bool sstd_c2py::c2py_ret(sstd::mat_r<     uint32>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_r,      uint32); }
bool sstd_c2py::c2py_ret(sstd::mat_r<     uint64>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_r,      uint64); }
bool sstd_c2py::c2py_ret(sstd::mat_r<      float>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_r,       float); }
bool sstd_c2py::c2py_ret(sstd::mat_r<     double>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_r,      double); }
bool sstd_c2py::c2py_ret(sstd::mat_r<std::string>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR_str(sstd::mat_r, std::string); }

//------------------------------------------------------------------------------------------------------------------------------------

// 下記の実装はいずれも同様に動作する．このヘッダでは，グローバル空間の名前汚染を防ぐため，
// #define による実装を利用し，ヘッダ末尾で #undef することで，グローバル空間への名前汚染を防ぐ．
// 稀に inline にしても遅くなることがあるので，結局関数呼び出しになっている??

/*
// Example of template type implementation
//   pArgList[i] = vec_write2file<std::vector<double>,double>(fList[i].pointer, fp, ap);

template<typename T, typename sizeT>
inline void* vec_write2file(bool IsPointer, sstd::file& fp, va_list& ap){
	if(IsPointer){ T* pArgBuf=va_arg(ap, T*); fp.fwrite(&(*pArgBuf)[0], sizeof(sizeT), (*pArgBuf).size()); return pArgBuf;
	}     else   { T   argBuf=va_arg(ap, T ); fp.fwrite(    &argBuf[0], sizeof(sizeT),     argBuf.size()); return 0;       }
}
//*/

#define builtIn_write2file(pType, Type)									\
	if(fList[i].pointer){												\
		pType* pArgBuf=va_arg(ap,pType*);								\
		pArgList[i]=pArgBuf;											\
																		\
		uint32 len=1;													\
		if(i<fList.size()-1 && len_num==fList[i+1].N_num){				\
			len=va_arg(ap,uint32);										\
			fList[i].arrLen.clear();									\
			fList[i].arrLen.push_back(len);								\
			i++; /* adding i in order to pass the sequency of len_num */ \
		}else{															\
			fList[i].arrLen.clear();									\
			fList[i].arrLen.push_back(len);								\
		}																\
																		\
		fp.fwrite(pArgBuf,sizeof(pType),len);							\
	}else{																\
		Type argBuf=va_arg(ap,Type);									\
		fp.fwrite(&argBuf,sizeof(Type),1);								\
	}
#define vec_write2file(type)											\
	if(fList[i].pointer){ std::vector<type>* pArgBuf=va_arg(ap, std::vector<type>*); fp.fwrite(&(*pArgBuf)[0], sizeof(type), (*pArgBuf).size()); fList[i].arrLen.clear(); fList[i].arrLen.push_back((*pArgBuf).size()); pArgList[i]=pArgBuf; \
	}        else       { std::vector<type>   argBuf=va_arg(ap, std::vector<type> ); fp.fwrite(    &argBuf[0], sizeof(type),     argBuf.size()); fList[i].arrLen.clear(); fList[i].arrLen.push_back(    argBuf.size()); }
#define vec_write2file_bool()											\
	/* syntax error: vec_write2file(std::vector<  bool>,   bool, pArgList[i], fList[i].pointer, fp, ap, fList[i]); */ \
	/* std::vector<bool> の実装は特殊化されており，1 Byte に 1 つではなく，1 Bits に 1 つの bool 値を格納している．*/ \
	/* このため，std::vector<bool> buf(10); の &buf[0] は，一時オブジェクトを参照している．*/ \
	if(fList[i].pointer){												\
		std::vector<bool>* pArgBuf=va_arg(ap, std::vector<bool>*);		\
		std::vector<uchar> vecBuf((*pArgBuf).size());					\
		for(uint v=0; v<vecBuf.size(); v++){ vecBuf[v]=(uchar)(*pArgBuf)[v]; } /* copy */ \
		fp.fwrite(&vecBuf[0], sizeof(uchar), vecBuf.size());			\
		fList[i].arrLen.clear();										\
		fList[i].arrLen.push_back(vecBuf.size());						\
		pArgList[i]=pArgBuf;											\
	}else{																\
		std::vector<bool> argBuf=va_arg(ap, std::vector<bool>);			\
		std::vector<uchar> vecBuf(argBuf.size());						\
		for(uint v=0; v<vecBuf.size(); v++){ vecBuf[v]=(uchar)argBuf[v]; } /* copy */ \
		fp.fwrite(&vecBuf[0], sizeof(uchar), vecBuf.size());			\
		fList[i].arrLen.clear();										\
		fList[i].arrLen.push_back(argBuf.size());						\
	}
#define vec_write2file_str()											\
	/* argList.bin */													\
	/* F vec double F F 1 3 */											\
	/* F vec str F F lenOfVec StrLen1 StrLen2 StrLen3 ... */			\
	if(fList[i].pointer){												\
		std::vector<std::string>* pArgBuf=va_arg(ap,std::vector<std::string>*);	\
		pArgList[i]=pArgBuf;											\
																		\
		uint64 len=(uint64)pArgBuf->size();								\
		fList[i].arrLen.clear();										\
		uint64 len_sum=0;												\
		for(uint v=0; v<len; v++){										\
			fList[i].arrLen.push_back((*pArgBuf)[v].size());			\
			len_sum += (*pArgBuf)[v].size();							\
		}																\
		std::string writeBuf(len_sum, '\0'); writeBuf.clear();			\
		for(uint v=0; v<len; v++){ writeBuf+=(*pArgBuf)[v]; }			\
																		\
		fp.fwrite(&writeBuf[0],sizeof(char),writeBuf.size());			\
	}else{																\
		std::vector<std::string> argBuf=va_arg(ap,std::vector<std::string>); \
																		\
		uint64 len=(uint64)argBuf.size();								\
		fList[i].arrLen.clear();										\
		uint64 len_sum=0;												\
		for(uint v=0; v<len; v++){										\
			fList[i].arrLen.push_back(argBuf[v].size());				\
			len_sum += argBuf[v].size();								\
		}																\
		std::string writeBuf(len_sum, '\0'); writeBuf.clear();			\
		for(uint v=0; v<len; v++){ writeBuf+=argBuf[v]; }				\
																		\
		fp.fwrite(&writeBuf[0],sizeof(char),writeBuf.size());			\
	}

#define mat_write2file(matType, type)									\
	if(fList[i].pointer){ matType<type>* pArgBuf=va_arg(ap, matType<type>*); fp.fwrite(&(*pArgBuf)[0], sizeof(type), (*pArgBuf).len()); fList[i].arrLen.clear(); fList[i].arrLen.push_back((*pArgBuf).rows()); fList[i].arrLen.push_back((*pArgBuf).cols()); pArgList[i]=pArgBuf; \
	}        else       { matType<type>   argBuf=va_arg(ap, matType<type> ); fp.fwrite(    &argBuf[0], sizeof(type),     argBuf.len()); fList[i].arrLen.clear(); fList[i].arrLen.push_back(    argBuf.rows()); fList[i].arrLen.push_back(    argBuf.cols()); }

#define mat_write2file_str(matType)										\
	/* argList.bin */													\
	/* F mat str F F lenOfInfo rows cols strLen1 strLen2 strLen3 ... */	\
	if(fList[i].pointer){												\
		matType<std::string>* pArgBuf=va_arg(ap,matType<std::string>*);	\
		pArgList[i]=pArgBuf;											\
																		\
		uint64 len=(uint64)pArgBuf->len();								\
		fList[i].arrLen.clear();										\
		fList[i].arrLen.push_back((*pArgBuf).rows());					\
		fList[i].arrLen.push_back((*pArgBuf).cols());					\
		uint64 len_sum=0;												\
		for(uint v=0; v<len; v++){										\
			fList[i].arrLen.push_back((*pArgBuf)[v].size());			\
			len_sum += (*pArgBuf)[v].size();							\
		}																\
		std::string writeBuf(len_sum, '\0'); writeBuf.clear();			\
		for(uint v=0; v<len; v++){ writeBuf+=(*pArgBuf)[v]; }			\
																		\
		fp.fwrite(&writeBuf[0],sizeof(char),writeBuf.size());			\
	}else{																\
		matType<std::string> argBuf=va_arg(ap,matType<std::string>);	\
																		\
		uint64 len=(uint64)argBuf.len();								\
		fList[i].arrLen.clear();										\
		fList[i].arrLen.push_back(argBuf.rows());						\
		fList[i].arrLen.push_back(argBuf.cols());						\
		uint64 len_sum=0;												\
		for(uint v=0; v<len; v++){										\
			fList[i].arrLen.push_back(argBuf[v].size());				\
			len_sum += argBuf[v].size();								\
		}																\
		std::string writeBuf(len_sum, '\0'); writeBuf.clear();			\
		for(uint v=0; v<len; v++){ writeBuf+=argBuf[v]; }				\
																		\
		fp.fwrite(&writeBuf[0],sizeof(char),writeBuf.size());			\
	}
				
//------------------------------------------------------------------

// *** Exceptional processing of getting arg pointer and writting data to a file ***

// Exception of char*
#define builtIn_write2file_pChar()\
	if(fList[i].pointer){ char* pArgBuf=va_arg(ap, char*); pArgList[i]=pArgBuf; uint32 len=strlen(pArgBuf); fList[i].arrLen.clear(); fList[i].arrLen.push_back(len); fp.fwrite(pArgBuf,sizeof(  char),len);\
	}       else        { uint32 argBuf=va_arg(ap,uint32);                                                                                                           fp.fwrite(&argBuf,sizeof(uint32),1  ); } // char is treated as a 4 bytes type by va_arg();

// Exception of std::string*
#define builtIn_write2file_pStr()\
	if(fList[i].pointer){ std::string* pArgBuf=va_arg(ap,std::string*); pArgList[i]=pArgBuf; uint64 len=(uint64)pArgBuf->size(); fList[i].arrLen.clear(); fList[i].arrLen.push_back(len); fp.fwrite(&(*pArgBuf)[0],sizeof(char),len          );\
	}       else        { std::string   argBuf=va_arg(ap,std::string );                      uint64 len=(uint64)  argBuf.size(); fList[i].arrLen.clear(); fList[i].arrLen.push_back(len); fp.fwrite(&   argBuf [0],sizeof(char),argBuf.size()); }

//------------------------------------------------------------------

bool isBuiltin(char N_num){ if(bool_num==N_num || char_num==N_num || uchar_num==N_num || int8_num==N_num || uint8_num==N_num || int16_num==N_num || uint16_num==N_num || int32_num==N_num || uint32_num==N_num || int64_num==N_num || uint64_num==N_num || float_num==N_num || double_num==N_num){ return true; }else{ return false; } }

//------------------------------------------------------------------

std::vector<void*> sstd_c2py::getArg_and_write2file(va_list& ap, const char* writeDir_base, std::vector<std::string> fSList, std::vector<struct sstd_c2py::typeSet>& fList){
	
	std::vector<void*> pArgList(fList.size(), 0); // note noly pointer type
	for(uint i=1; i<fList.size(); i++){ // begin 1 to avoid return value
		if(fList[i].retTF){
			if(!fList[i].pointer){ sstd::pdbg("ERROR: ret type must be a pointer type."); return std::vector<void*>(); }

			pArgList[i]=va_arg(ap, void*);
			fList[i].arrLen.clear();

			uint32 len=1;
			fList[i].arrLen.clear();
			if(i<fList.size()-1 && len_num==fList[i+1].N_num){ len=va_arg(ap,uint32); fList[i].arrLen.push_back(len); i++; // adding i in order to pass the sequency of len_num
			}else if(              isBuiltin(fList[i].N_num)){                        fList[i].arrLen.push_back(len);
			}               else                             {                        fList[i].arrLen.push_back( 0 ); } // ret の場合，builtin 型以外は，サイズ 0 としておく．
			continue; // pass "ret" type
		}
		
		sstd::file fp; std::string writeDir = sstd::ssprintf("%s/arg%04d.bin", writeDir_base, i);
		if(!fp.fopen(writeDir.c_str(), "wb")){ sstd::pdbg("ERROR: fopen was failed. (%s can't open.)\n", writeDir.c_str()); return std::vector<void*>(); }

		// 条件分岐は少なくとも選択肢が連続した整数の場合は switch case を利用することにより，選択肢 5 つ以上でテーブルジャンプで最適化が行われ，定数時間で終了するはず．vec_num 内も <T> ごとに個別の番号を振る方がよい．
		// 加えて，ポインタかどうかの判定も，全て #define で番号を振っておけば，より高速に処理できるはず．ただし，データファイルを 1 つにまとめて読み込みを高速化したり，パイプ等でプロセス間通信をした方が，オーバーヘッドは減る気がするので，後回し．
		// あと，ポインタ分行数が増えると，可読性がさらに落ちる．
		if      (  bool_num==fList[i].N_num){ builtIn_write2file(  bool, uint32); // bool is treated as a 4 bytes type by va_arg();
		}else if(  char_num==fList[i].N_num){ builtIn_write2file_pChar();         // "char*" is treated exceptionaly because of the utilization of strlen() in order to count its length.
		}else if( uchar_num==fList[i].N_num){ builtIn_write2file( uchar, uint32); // ‘uchar {aka unsigned char}’ is promoted to ‘int’ when passed through ‘...’
		}else if(  int8_num==fList[i].N_num){ builtIn_write2file(  int8, uint32); // ‘int8 {aka signed char}’ is promoted to ‘int’ when passed through ‘...’
		}else if( uint8_num==fList[i].N_num){ builtIn_write2file( uint8, uint32); // ‘uint8 {aka unsigned char}’ is promoted to ‘int’ when passed through ‘...’
		}else if( int16_num==fList[i].N_num){ builtIn_write2file( int16, uint32); // ‘int16 {aka short int}’ is promoted to ‘int’ when passed through ‘...’
		}else if(uint16_num==fList[i].N_num){ builtIn_write2file(uint16, uint32); // ‘uint16 {aka short unsigned int}’ is promoted to ‘int’ when passed through ‘...’
		}else if( int32_num==fList[i].N_num){ builtIn_write2file( int32,  int32);
		}else if(uint32_num==fList[i].N_num){ builtIn_write2file(uint32, uint32);
		}else if( int64_num==fList[i].N_num){ builtIn_write2file( int64,  int64);
		}else if(uint64_num==fList[i].N_num){ builtIn_write2file(uint64, uint64);
		}else if( float_num==fList[i].N_num){ builtIn_write2file(uint64, uint64); // ‘float’ is promoted to ‘double’ when passed through ‘...’// va_arg() ではなく，opertor() で読み込まれる時点で，既に double 型として扱われているので，uint32 で読み込んでも，壊れたデータしか読み込めない．
		}else if(double_num==fList[i].N_num){ builtIn_write2file(double, double);
		}else if(   len_num==fList[i].N_num){ if((int)i-1<0 || !fList[i-1].pointer){ sstd::pdbg("ERROR: \"%s\": Previous of len (len is a length of pointer and treated as a uint32) must be pointer type (T*), without \"char*\", \"str* (std::string*)\", \"vec<T>* (std::vector<T>*)\", \"mat<T>* (sstd::mat<T>*)\" and \"mat_r<T>* (sstd::mat_r<T>*)\".\n", fSList[i].c_str()); }
		}else if(   str_num==fList[i].N_num){ builtIn_write2file_pStr();
		}else if(   vec_num==fList[i].N_num){ 
			if      (  bool_num==fList[i].T_num){ vec_write2file_bool();
			}else if(  char_num==fList[i].T_num){ vec_write2file(  char);
			}else if( uchar_num==fList[i].T_num){ vec_write2file( uchar);
			}else if(  int8_num==fList[i].T_num){ vec_write2file(  int8);
			}else if( uint8_num==fList[i].T_num){ vec_write2file( uint8);
			}else if( int16_num==fList[i].T_num){ vec_write2file( int16);
			}else if(uint16_num==fList[i].T_num){ vec_write2file(uint16);
			}else if( int32_num==fList[i].T_num){ vec_write2file( int32);
			}else if(uint32_num==fList[i].T_num){ vec_write2file(uint32);
			}else if( int64_num==fList[i].T_num){ vec_write2file( int64);
			}else if(uint64_num==fList[i].T_num){ vec_write2file(uint64);
			}else if( float_num==fList[i].T_num){ vec_write2file( float);
			}else if(double_num==fList[i].T_num){ vec_write2file(double);
			}else if(   str_num==fList[i].T_num){ vec_write2file_str();
			}else{ sstd::pdbg("ERROR: \"%s\" is an unsupported type of vec<T>.\n", fSList[i].c_str()); return std::vector<void*>(); }
		}else if(   mat_num==fList[i].N_num){
			if      (  bool_num==fList[i].T_num){ mat_write2file    (sstd::mat,   bool);
			}else if(  char_num==fList[i].T_num){ mat_write2file    (sstd::mat,   char);
			}else if( uchar_num==fList[i].T_num){ mat_write2file    (sstd::mat,  uchar);
			}else if(  int8_num==fList[i].T_num){ mat_write2file    (sstd::mat,   int8);
			}else if( uint8_num==fList[i].T_num){ mat_write2file    (sstd::mat,   int8);
			}else if( int16_num==fList[i].T_num){ mat_write2file    (sstd::mat,  int16);
			}else if(uint16_num==fList[i].T_num){ mat_write2file    (sstd::mat, uint16);
			}else if( int32_num==fList[i].T_num){ mat_write2file    (sstd::mat,  int32);
			}else if(uint32_num==fList[i].T_num){ mat_write2file    (sstd::mat, uint32);
			}else if( int64_num==fList[i].T_num){ mat_write2file    (sstd::mat,  int64);
			}else if(uint64_num==fList[i].T_num){ mat_write2file    (sstd::mat, uint64);
			}else if( float_num==fList[i].T_num){ mat_write2file    (sstd::mat,  float);
			}else if(double_num==fList[i].T_num){ mat_write2file    (sstd::mat, double);
			}else if(   str_num==fList[i].T_num){ mat_write2file_str(sstd::mat);
			}else{ sstd::pdbg("ERROR: \"%s\" is an unsupported type of mat<T>.\n", fSList[i].c_str()); return std::vector<void*>(); }
		}else if( mat_r_num==fList[i].N_num){
			if      (  bool_num==fList[i].T_num){ mat_write2file    (sstd::mat_r,   bool);
			}else if(  char_num==fList[i].T_num){ mat_write2file    (sstd::mat_r,   char);
			}else if( uchar_num==fList[i].T_num){ mat_write2file    (sstd::mat_r,  uchar);
			}else if(  int8_num==fList[i].T_num){ mat_write2file    (sstd::mat_r,   int8);
			}else if( uint8_num==fList[i].T_num){ mat_write2file    (sstd::mat_r,  uint8);
			}else if( int16_num==fList[i].T_num){ mat_write2file    (sstd::mat_r,  int16);
			}else if(uint16_num==fList[i].T_num){ mat_write2file    (sstd::mat_r, uint16);
			}else if( int32_num==fList[i].T_num){ mat_write2file    (sstd::mat_r,  int32);
			}else if(uint32_num==fList[i].T_num){ mat_write2file    (sstd::mat_r, uint32);
			}else if( int64_num==fList[i].T_num){ mat_write2file    (sstd::mat_r,  int64);
			}else if(uint64_num==fList[i].T_num){ mat_write2file    (sstd::mat_r, uint64);
			}else if( float_num==fList[i].T_num){ mat_write2file    (sstd::mat_r,  float);
			}else if(double_num==fList[i].T_num){ mat_write2file    (sstd::mat_r, double);
			}else if(   str_num==fList[i].T_num){ mat_write2file_str(sstd::mat_r);
			}else{ sstd::pdbg("ERROR: \"%s\" is an unsupported type of mat_r<T>.\n", fSList[i].c_str()); return std::vector<void*>(); }
		}else{ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<void*>(); }
	}
	return pArgList;
}

//------------------------------------------------------------------------------------------------------------------------------------

//   writeBack: WB
bool checkError_WB(uint fSize, uint arrSize){
	if(fSize>arrSize){ sstd::pdbg("ERROR: Write back size is larger than giving size. Only the length of pointer will be written back.\n"); return false;
	}      else      { return true; }
}

#define readLenOfPointer(Type)											\
	fp.fread(pArgList[i],sizeof(Type),fList[i].arrLen[0]);				\
	if(!checkError_WB(fp.fsize(),fList[i].arrLen[0]*sizeof(Type))){ return false; }

#define readLenOfPointer_str()						\
	std::string* pStr=(std::string*)pArgList[i];	\
	uint len=fp.fsize();							\
	(*pStr).resize(len);							\
	fp.fread(&(*pStr)[0], sizeof(char), len); 

//------------------------------------------------------------------

bool sstd_c2py::writeBack(std::vector<std::string>& lines, std::vector<void*>& pArgList, const char* writeDir_base, std::vector<std::string>& fSList, std::vector<struct sstd_c2py::typeSet>& fList){
	for(uint i=1; i<pArgList.size(); i++){ // begin 1 to avoid return value
		if(pArgList[i]==0 || fList[i].constTF==true || fList[i].N_num==len_num){ continue; }
		
		sstd::file fp; std::string readDir=sstd::ssprintf("%s/arg%04d.bin", writeDir_base, i);
		if(!fp.fopen(readDir.c_str(), "rb")){ sstd::pdbg("ERROR: fopen was failed. (%s can't open.)\n", readDir.c_str()); return false; }

		// For built in types: If the length of pointer is smaller than return value, below lines will write back only pointer length.
		if      (  bool_num==fList[i].N_num){ readLenOfPointer(  bool);
		}else if(  char_num==fList[i].N_num){ readLenOfPointer(  char); // Python says [TypeError: 'str' object does not support item assignment] so, this might be impossible.
		}else if( uchar_num==fList[i].N_num){ readLenOfPointer( uchar);
		}else if(  int8_num==fList[i].N_num){ readLenOfPointer(  int8);
		}else if( uint8_num==fList[i].N_num){ readLenOfPointer( uint8);
		}else if( int16_num==fList[i].N_num){ readLenOfPointer( int16);
		}else if(uint16_num==fList[i].N_num){ readLenOfPointer(uint16);
		}else if( int32_num==fList[i].N_num){ readLenOfPointer( int32);
		}else if(uint32_num==fList[i].N_num){ readLenOfPointer(uint32);
		}else if( int64_num==fList[i].N_num){ readLenOfPointer( int64);
		}else if(uint64_num==fList[i].N_num){ readLenOfPointer(uint64);
		}else if( float_num==fList[i].N_num){ readLenOfPointer( float);
		}else if(double_num==fList[i].N_num){ readLenOfPointer(double);
		}else if(   str_num==fList[i].N_num){ readLenOfPointer_str();           // Python says [TypeError: 'str' object does not support item assignment] so, this might be impossible.
		}else if(   vec_num==fList[i].N_num){
			if      (  bool_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((std::vector<       bool>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(  char_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((std::vector<       char>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( uchar_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((std::vector<      uchar>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(  int8_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((std::vector<       int8>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( uint8_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((std::vector<      uint8>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( int16_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((std::vector<      int16>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(uint16_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((std::vector<     uint16>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( int32_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((std::vector<      int32>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(uint32_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((std::vector<     uint32>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( int64_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((std::vector<      int64>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(uint64_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((std::vector<     uint64>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( float_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((std::vector<      float>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(double_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((std::vector<     double>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(   str_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((std::vector<std::string>*)pArgList[i]), fp, lines[i])){ return false; }
			}else{ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return false; }
		}else if(   mat_num==fList[i].N_num){
			if      (  bool_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat<       bool>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(  char_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat<       char>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( uchar_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat<      uchar>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(  int8_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat<       int8>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( uint8_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat<      uint8>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( int16_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat<      int16>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(uint16_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat<     uint16>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( int32_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat<      int32>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(uint32_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat<     uint32>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( int64_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat<      int64>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(uint64_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat<     uint64>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( float_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat<      float>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(double_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat<     double>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(   str_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat<std::string>*)pArgList[i]), fp, lines[i])){ return false; }
			}else{ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return false; }
		}else if( mat_r_num==fList[i].N_num){
			if      (  bool_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat_r<       bool>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(  char_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat_r<       char>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( uchar_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat_r<      uchar>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(  int8_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat_r<       int8>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( uint8_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat_r<      uint8>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( int16_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat_r<      int16>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(uint16_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat_r<     uint16>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( int32_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat_r<      int32>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(uint32_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat_r<     uint32>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( int64_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat_r<      int64>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(uint64_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat_r<     uint64>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if( float_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat_r<      float>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(double_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat_r<     double>*)pArgList[i]), fp, lines[i])){ return false; }
			}else if(   str_num==fList[i].T_num){ if(!sstd_c2py::c2py_ret(*((sstd::mat_r<std::string>*)pArgList[i]), fp, lines[i])){ return false; }
			}else{ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return false; }
		}else{ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return false; }
	}
	return true;
}

//--------------------------------------------------------------------------------------------------------
