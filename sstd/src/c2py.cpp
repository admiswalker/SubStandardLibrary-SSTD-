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
// -> ヘッダから切り離したので，そのうち enum に変更する．

#define        num_void    200
#define        num_len     201

#define        num_bool    0
#define        num_char    1
#define        num_uchar   2
#define        num_int8    3
#define        num_int16   4
#define        num_int32   5
#define        num_int64   6
#define        num_uint8   7
#define        num_uint16  8
#define        num_uint32  9
#define        num_uint64 10
#define        num_float  11
#define        num_double 12
#define        num_str    13

#define    VEC_NUM_BASE   14 // std::vector<T> // vec_num_bool = num_bool + VEC_NUM_BASE
#define    vec_num_bool   14
#define    vec_num_char   15
#define    vec_num_uchar  16
#define    vec_num_int8   17
#define    vec_num_int16  18
#define    vec_num_int32  19
#define    vec_num_int64  20
#define    vec_num_uint8  21
#define    vec_num_uint16 22
#define    vec_num_uint32 23
#define    vec_num_uint64 24
#define    vec_num_float  25
#define    vec_num_double 26
#define    vec_num_str    27

#define   VVEC_NUM_BASE   28 // std::vector<std::vector<T>> // vvec_num_bool = num_bool + VVEC_NUM_BASE
#define   vvec_num_bool   28
#define   vvec_num_char   29
#define   vvec_num_uchar  30
#define   vvec_num_int8   31
#define   vvec_num_int16  32
#define   vvec_num_int32  33
#define   vvec_num_int64  34
#define   vvec_num_uint8  35
#define   vvec_num_uint16 36
#define   vvec_num_uint32 37
#define   vvec_num_uint64 38
#define   vvec_num_float  39
#define   vvec_num_double 40
#define   vvec_num_str    41

#define  MAT_C_NUM_BASE   42 // sstd::mat_c<T> // mat_c_num_bool = num_bool + MAT_C_NUM_BASE
#define  mat_c_num_bool   42
#define  mat_c_num_char   43
#define  mat_c_num_uchar  44
#define  mat_c_num_int8   45
#define  mat_c_num_int16  46
#define  mat_c_num_int32  47
#define  mat_c_num_int64  48
#define  mat_c_num_uint8  49
#define  mat_c_num_uint16 50
#define  mat_c_num_uint32 51
#define  mat_c_num_uint64 52
#define  mat_c_num_float  53
#define  mat_c_num_double 54
#define  mat_c_num_str    55

#define  MAT_R_NUM_BASE   56 // sstd::mat_r<T> // mat_r_num_bool = num_bool + MAT_R_NUM_BASE
#define  mat_r_num_bool   56
#define  mat_r_num_char   57
#define  mat_r_num_uchar  58
#define  mat_r_num_int8   59
#define  mat_r_num_int16  60
#define  mat_r_num_int32  61
#define  mat_r_num_int64  62
#define  mat_r_num_uint8  63
#define  mat_r_num_uint16 64
#define  mat_r_num_uint32 65
#define  mat_r_num_uint64 66
#define  mat_r_num_float  67
#define  mat_r_num_double 68
#define  mat_r_num_str    69

#define VMAT_C_NUM_BASE   70 // std::vector<sstd::mat_c<T>> // vmat_c_num_bool = num_bool + VMAT_C_NUM_BASE
#define vmat_c_num_bool   70
#define vmat_c_num_char   71
#define vmat_c_num_uchar  72
#define vmat_c_num_int8   73
#define vmat_c_num_int16  74
#define vmat_c_num_int32  75
#define vmat_c_num_int64  76
#define vmat_c_num_uint8  77
#define vmat_c_num_uint16 78
#define vmat_c_num_uint32 79
#define vmat_c_num_uint64 80
#define vmat_c_num_float  81
#define vmat_c_num_double 82
#define vmat_c_num_str    83

#define VMAT_R_NUM_BASE   84 // std::vector<sstd::mat_r<T>> // vmat_r_num_bool = num_bool + VMAT_R_NUM_BASE
#define vmat_r_num_bool   84
#define vmat_r_num_char   85
#define vmat_r_num_uchar  86
#define vmat_r_num_int8   87
#define vmat_r_num_int16  88
#define vmat_r_num_int32  89
#define vmat_r_num_int64  90
#define vmat_r_num_uint8  91
#define vmat_r_num_uint16 92
#define vmat_r_num_uint32 93
#define vmat_r_num_uint64 94
#define vmat_r_num_float  95
#define vmat_r_num_double 96
#define vmat_r_num_str    97

//------------------------------------------------------------------------------------------------------------------------------------

// Does a "str" take shape of XXX<T>? (something like, vec<double>, sstd::mat_c<double>, sstd::mat_r<double>, ...)
//  - When "str"=="vec<double>" -> retType=="vec" and retTempT=="double" will be returned.
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
	
	sstd::removeTailSpace(retType); // head space in "retType" is aleady removed when splitting by ','.
	sstd::removeSpace_of_HeadAndTail(retTempT);
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
void split_ret    (struct sstd_c2py::typeSet& f, std::string& fS){ f.retTF   = split_leftStr(R"(ret )", f, fS);   }
void split_const  (struct sstd_c2py::typeSet& f, std::string& fS){ f.constTF = split_leftStr(R"(const )", f, fS); }
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
	if      (sstd::strcmp(in,  "bool")){ out.T=  "bool"; out.T_num=num_bool  ;
	}else if(sstd::strcmp(in,  "char")){ out.T=  "char"; out.T_num=num_char  ;
	}else if(sstd::strcmp(in, "uchar")){ out.T= "uchar"; out.T_num=num_uchar ;
	}else if(sstd::strcmp(in,   "int")){ out.T= "int32"; out.T_num=num_int32 ;
	}else if(sstd::strcmp(in,  "int8")){ out.T=  "int8"; out.T_num=num_int8  ;
	}else if(sstd::strcmp(in, "int16")){ out.T= "int16"; out.T_num=num_int16 ;
	}else if(sstd::strcmp(in, "int32")){ out.T= "int32"; out.T_num=num_int32 ;
	}else if(sstd::strcmp(in, "int64")){ out.T= "int64"; out.T_num=num_int64 ;
	}else if(sstd::strcmp(in, "uint8")){ out.T= "uint8"; out.T_num=num_uint8 ;
	}else if(sstd::strcmp(in,"uint16")){ out.T="uint16"; out.T_num=num_uint16;
	}else if(sstd::strcmp(in,"uint32")){ out.T="uint32"; out.T_num=num_uint32;
	}else if(sstd::strcmp(in,"uint64")){ out.T="uint64"; out.T_num=num_uint64;
	}else if(sstd::strcmp(in, "float")){ out.T= "float"; out.T_num=num_float ;
	}else if(sstd::strcmp(in,"double")){ out.T="double"; out.T_num=num_double;
	}else if(sstd::strcmp(in,"string")){ out.T=   "str"; out.T_num=num_str   ;
	}else if(sstd::strcmp(in,   "str")){ out.T=   "str"; out.T_num=num_str   ;
	}else{ return false; }
	return true;
}
bool IsNext_Len(const std::vector<std::string>& fSList, const std::vector<struct sstd_c2py::typeSet>& fList, uint& i){
	if(i<(fList.size()-1)){
		if(sstd::strcmp(fSList[i+1],"len")){ return true; }
	}
	if(!(fList[i].N_num==      num_char&&fList[i].pointer)&&
	   !(fList[i].N_num==  VEC_NUM_BASE&&fList[i].pointer)&&
	   !(fList[i].N_num== VVEC_NUM_BASE&&fList[i].pointer)&&
	   !(fList[i].N_num==MAT_C_NUM_BASE&&fList[i].pointer)&&
	   !(fList[i].N_num==MAT_R_NUM_BASE&&fList[i].pointer)){
		sstd::pdbg("ERROR: \"%s\": Next of a pointer type (T*) must be len (len is a length of pointer and treated as a uint32), without \"char*\", \"str* (std::string*)\", \"vec<T>* (std::vector<T>*)\", \"mat_c<T>* (sstd::mat_c<T>*)\" and \"mat_r<T>* (sstd::mat_r<T>*)\".\n", fSList[i].c_str());
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
	if(i>0 && fList[i-1].N_num==num_char && fList[i-1].pointer==true){
		sstd::pdbg("ERROR: \"%s\": Previous of a len type can't have \"char*\". Because \"char*\" check its length by \"strlen()\" and doesn't need to be send its length.\n", fSList[i].c_str());
	}
	return false;
}
std::vector<struct sstd_c2py::typeSet> sstd_c2py::format_str2typeSet(const std::vector<std::string>& fSList){
	std::vector<struct sstd_c2py::typeSet> fList(fSList.size());
	std::string type, tempT;
	for(uint i=0; i<fList.size(); i++){
		std::string fS = fSList[i]; // format string list
		struct sstd_c2py::typeSet& f = fList[i]; // format list
		split_const       (f, fS); // "const type*|*~" -> "const", "type*|*~"
		split_ret         (f, fS); //   "ret type*|*~" ->   "ret", "type*|*~"
		split_verticalLine(f, fS); //                              "type*|*~" -> "type*", "*~"           // vartical line is just a splitting symbol
		split_pointer     (f, fS); //                                            "type*" -> "type",  "*" // setting "true" or "false" of pointer
		if      (sstd::strcmp(fS,  "void")){ f.name=  "void"; f.N_num=num_void  ; f.case_num=f.N_num; if(f.pointer){ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
		}else if(sstd::strcmp(fS,   "len")){ f.name=   "len"; f.N_num=num_len   ; f.case_num=f.N_num; if(!IsPrevious_pointer(fSList, fList, i)){ sstd::pdbg("ERROR: \"%s\": Previous of a len type must be a pointer type without \"char*\". Because \"char*\" check its length by \"strlen()\" and doesn't need to be send its length.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
		}else if(sstd::strcmp(fS,  "bool")){ f.name=  "bool"; f.N_num=num_bool  ; f.case_num=f.N_num;
		}else if(sstd::strcmp(fS,  "char")){ f.name=  "char"; f.N_num=num_char  ; f.case_num=f.N_num; if(f.pointer&& IsNext_Len(fSList, fList, i)){ sstd::pdbg("ERROR: \"%s\": Previous of a len type can't have \"char*\". Because \"char*\" check its length by \"strlen()\" and doesn't need to be send its length.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
		}else if(sstd::strcmp(fS, "uchar")){ f.name= "uchar"; f.N_num=num_uchar ; f.case_num=f.N_num;
		}else if(sstd::strcmp(fS,   "int")){ f.name= "int32"; f.N_num=num_int32 ; f.case_num=f.N_num;
		}else if(sstd::strcmp(fS,  "int8")){ f.name=  "int8"; f.N_num=num_int8  ; f.case_num=f.N_num;
		}else if(sstd::strcmp(fS, "int16")){ f.name= "int16"; f.N_num=num_int16 ; f.case_num=f.N_num;
		}else if(sstd::strcmp(fS, "int32")){ f.name= "int32"; f.N_num=num_int32 ; f.case_num=f.N_num;
		}else if(sstd::strcmp(fS, "int64")){ f.name= "int64"; f.N_num=num_int64 ; f.case_num=f.N_num;
		}else if(sstd::strcmp(fS, "uint8")){ f.name= "uint8"; f.N_num=num_uint8 ; f.case_num=f.N_num;
		}else if(sstd::strcmp(fS,"uint16")){ f.name="uint16"; f.N_num=num_uint16; f.case_num=f.N_num;
		}else if(sstd::strcmp(fS,"uint32")){ f.name="uint32"; f.N_num=num_uint32; f.case_num=f.N_num;
		}else if(sstd::strcmp(fS,"uint64")){ f.name="uint64"; f.N_num=num_uint64; f.case_num=f.N_num;
		}else if(sstd::strcmp(fS, "float")){ f.name= "float"; f.N_num=num_float ; f.case_num=f.N_num;
		}else if(sstd::strcmp(fS,"double")){ f.name="double"; f.N_num=num_double; f.case_num=f.N_num;
		}else if(sstd::strcmp(fS,"string")){ f.name=   "str"; f.N_num=num_str   ; f.case_num=f.N_num;
		}else if(sstd::strcmp(fS,   "str")){ f.name=   "str"; f.N_num=num_str   ; f.case_num=f.N_num;
		}else if(Is_type_tempT(fS, type, tempT)){
			// Example: fS=="vec<double>"
			//  - type =="vec"
			//  - tempT=="double"
			if      (sstd::strcmp(type,  "vec")){ f.name=  "vec"; f.N_num=  VEC_NUM_BASE; f.case_num=f.N_num; if(!setTandT_num(f, tempT)){ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
			}else if(sstd::strcmp(type, "vvec")){ f.name= "vvec"; f.N_num= VVEC_NUM_BASE; f.case_num=f.N_num; if(!setTandT_num(f, tempT)){ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
			}else if(sstd::strcmp(type,"mat_c")){ f.name="mat_c"; f.N_num=MAT_C_NUM_BASE; f.case_num=f.N_num; if(!setTandT_num(f, tempT)){ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
			}else if(sstd::strcmp(type,"mat_r")){ f.name="mat_r"; f.N_num=MAT_R_NUM_BASE; f.case_num=f.N_num; if(!setTandT_num(f, tempT)){ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
			}else{ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
			f.case_num += f.T_num;
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
		if      (fList[i].N_num==       num_str                           ){ typeStr += sstd::ssprintf(" %u %u",    fList[i].arrLen.size(), fList[i].arrLen[0]);
		}else if(fList[i].N_num==  VEC_NUM_BASE && fList[i].T_num==num_str){ typeStr += sstd::ssprintf(" %u",       fList[i].arrLen.size()); for(uint v=0; v<fList[i].arrLen.size(); v++){ typeStr += sstd::ssprintf(" %lu", fList[i].arrLen[v]); }
		}else if(fList[i].N_num==  VEC_NUM_BASE                           ){ typeStr += sstd::ssprintf(" %u %u",    fList[i].arrLen.size(), fList[i].arrLen[0]);
		}else if(fList[i].N_num== VVEC_NUM_BASE                           ){ typeStr += sstd::ssprintf(" %u",       fList[i].arrLen.size()); for(uint v=0; v<fList[i].arrLen.size(); v++){ typeStr += sstd::ssprintf(" %lu", fList[i].arrLen[v]); }
		}else if(fList[i].N_num==MAT_C_NUM_BASE && fList[i].T_num==num_str){ typeStr += sstd::ssprintf(" %u",       fList[i].arrLen.size()); for(uint v=0; v<fList[i].arrLen.size(); v++){ typeStr += sstd::ssprintf(" %lu", fList[i].arrLen[v]); }
		}else if(fList[i].N_num==MAT_C_NUM_BASE                           ){ typeStr += sstd::ssprintf(" %u %u %u", fList[i].arrLen.size(), fList[i].arrLen[0], fList[i].arrLen[1]);
		}else if(fList[i].N_num==MAT_R_NUM_BASE && fList[i].T_num==num_str){ typeStr += sstd::ssprintf(" %u",       fList[i].arrLen.size()); for(uint v=0; v<fList[i].arrLen.size(); v++){ typeStr += sstd::ssprintf(" %lu", fList[i].arrLen[v]); }
		}else if(fList[i].N_num==MAT_R_NUM_BASE                           ){ typeStr += sstd::ssprintf(" %u %u %u", fList[i].arrLen.size(), fList[i].arrLen[0], fList[i].arrLen[1]);
		}else if(fList[i].pointer                                         ){ typeStr += sstd::ssprintf(" %u %u",    fList[i].arrLen.size(), fList[i].arrLen[0]);
		}                              else                                { typeStr += sstd::ssprintf(" %u",       fList[i].arrLen.size()); }
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

bool sstd_c2py::isRetVoid(std::vector<struct sstd_c2py::typeSet>& fList){ return num_void==fList[0].N_num; }

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

//---

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

//---

// Below function is almost as same as "bool sstd_c2py::c2py_ret(std::vector<std::string>& inOut, sstd::file& fp, std::string& line);".
template<typename T>
inline bool c2py_ret_vvec(std::vector<std::vector<T>>& inOut, sstd::file& fp, std::string& line){
	// getting size of return value
	std::vector<std::string> elements = sstd::split(line.c_str(), ' ');
	
	uint vecLen=sstd::str2int(elements[elOffSet]);
	inOut.resize(vecLen);
	for(uint i=0; i<vecLen; i++){
		inOut[i].resize(sstd::str2int(elements[elOffSet+1+i]));
	}
	
	// write back
	for(uint i=0; i<inOut.size(); i++){
		fp.fread(&inOut[i][0], sizeof(T), inOut[i].size());
	}
	return true;
}
//bool sstd_c2py::c2py_ret(std::vector<std::vector<       bool>>& inOut, sstd::file& fp, std::string& line);
//bool sstd_c2py::c2py_ret(std::vector<std::vector<       char>>& inOut, sstd::file& fp, std::string& line);
//bool sstd_c2py::c2py_ret(std::vector<std::vector<       int8>>& inOut, sstd::file& fp, std::string& line);
//bool sstd_c2py::c2py_ret(std::vector<std::vector<      int16>>& inOut, sstd::file& fp, std::string& line);
//bool sstd_c2py::c2py_ret(std::vector<std::vector<      int32>>& inOut, sstd::file& fp, std::string& line);
//bool sstd_c2py::c2py_ret(std::vector<std::vector<      int64>>& inOut, sstd::file& fp, std::string& line);
//bool sstd_c2py::c2py_ret(std::vector<std::vector<      uint8>>& inOut, sstd::file& fp, std::string& line); // same as uchar
//bool sstd_c2py::c2py_ret(std::vector<std::vector<     uint16>>& inOut, sstd::file& fp, std::string& line);
//bool sstd_c2py::c2py_ret(std::vector<std::vector<     uint32>>& inOut, sstd::file& fp, std::string& line);
//bool sstd_c2py::c2py_ret(std::vector<std::vector<     uint64>>& inOut, sstd::file& fp, std::string& line);
//bool sstd_c2py::c2py_ret(std::vector<std::vector<      float>>& inOut, sstd::file& fp, std::string& line);
bool sstd_c2py::c2py_ret(std::vector<std::vector<     double>>& inOut, sstd::file& fp, std::string& line){ return c2py_ret_vvec(inOut, fp, line); }
//bool sstd_c2py::c2py_ret(std::vector<std::vector<std::string>>& inOut, sstd::file& fp, std::string& line);

//---

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
	for(uint i=0; i<buf.size(); i++){									\
		fp.fread(&buf[i][0], sizeof(char), buf[i].size());				\
	}																	\
	sstd::move(inOut, buf);												\
	return true;
bool sstd_c2py::c2py_ret(sstd::mat_c<       bool>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_c,        bool); }
bool sstd_c2py::c2py_ret(sstd::mat_c<       char>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_c,        char); }
bool sstd_c2py::c2py_ret(sstd::mat_c<       int8>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_c,        int8); }
bool sstd_c2py::c2py_ret(sstd::mat_c<      int16>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_c,       int16); }
bool sstd_c2py::c2py_ret(sstd::mat_c<      int32>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_c,       int32); }
bool sstd_c2py::c2py_ret(sstd::mat_c<      int64>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_c,       int64); }
bool sstd_c2py::c2py_ret(sstd::mat_c<      uint8>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_c,       uint8); }
bool sstd_c2py::c2py_ret(sstd::mat_c<     uint16>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_c,      uint16); }
bool sstd_c2py::c2py_ret(sstd::mat_c<     uint32>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_c,      uint32); }
bool sstd_c2py::c2py_ret(sstd::mat_c<     uint64>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_c,      uint64); }
bool sstd_c2py::c2py_ret(sstd::mat_c<      float>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_c,       float); }
bool sstd_c2py::c2py_ret(sstd::mat_c<     double>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR    (sstd::mat_c,      double); }
bool sstd_c2py::c2py_ret(sstd::mat_c<std::string>& inOut, sstd::file& fp, std::string& line){ c2py_ret_matCR_str(sstd::mat_c, std::string); }
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

#define builtIn_write2file(pType, Type)									\
	if(fList[i].pointer){												\
		pType* pArgBuf=va_arg(ap,pType*);								\
		pArgList[i]=pArgBuf;											\
																		\
		uint32 len=1;													\
		if(i<fList.size()-1 && num_len==fList[i+1].N_num){				\
			len=va_arg(ap,uint32);										\
			fList[i].arrLen.clear();									\
			fList[i].arrLen.push_back(len);								\
			i++; /* adding i in order to pass the sequency of num_len */ \
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
	std::vector<bool>   argBuf(0); /* This buffer will not be used, while the "fmt.pointer" is true. */ \
	std::vector<bool>* pArgBuf;											\
	if(fList[i].pointer){												\
		pArgBuf     = va_arg(ap, std::vector<bool>*);					\
		pArgList[i] = pArgBuf; /* adding a pointer to the "pArgList[i]". */	\
	}else{																\
		 argBuf = va_arg(ap, std::vector<bool>);						\
		pArgBuf = &argBuf;												\
	}																	\
	std::vector<uchar> vecBuf((*pArgBuf).size());						\
	for(uint v=0; v<vecBuf.size(); v++){ vecBuf[v]=(uchar)(*pArgBuf)[v]; } /* copy */ \
	fp.fwrite(&vecBuf[0], sizeof(uchar), vecBuf.size());				\
	fList[i].arrLen.clear();											\
	fList[i].arrLen.push_back(vecBuf.size());
#define vec_write2file_str()											\
	/* argList.bin */													\
	/* F vec double F F 1 3 */											\
	/* F vec str F F lenOfVec StrLen1 StrLen2 StrLen3 ... */			\
	std::vector<std::string>   argBuf(0); /* This buffer will not be used, while the "fmt.pointer" is true. */ \
	std::vector<std::string>* pArgBuf;									\
	if(fList[i].pointer){												\
		pArgBuf     = va_arg(ap, std::vector<std::string>*);			\
		pArgList[i] = pArgBuf; /* adding a pointer to the "pArgList[i]". */	\
	}else{																\
		 argBuf = va_arg(ap, std::vector<std::string>);					\
		pArgBuf = &argBuf;												\
	}																	\
																		\
	uint64 len=(uint64)pArgBuf->size();									\
	fList[i].arrLen.clear();											\
	uint64 len_sum=0;													\
	for(uint v=0; v<len; v++){											\
		fList[i].arrLen.push_back((*pArgBuf)[v].size());				\
		len_sum += (*pArgBuf)[v].size();								\
	}																	\
	std::string writeBuf(len_sum, '\0'); writeBuf.clear();				\
	for(uint v=0; v<len; v++){ writeBuf+=(*pArgBuf)[v]; }				\
																		\
	fp.fwrite(&writeBuf[0],sizeof(char),writeBuf.size());

template<typename T>
void vvec2file(sstd::file& fp, std::vector<std::vector<T>>& vvec){
	for(uint i=0; i<vvec.size(); i++){
		fp.fwrite(&(vvec[i])[0], sizeof(T), vvec[i].size());
	}
}
template<typename T>
void vvec_write2file(va_list& ap, sstd::file& fp, void*& pArgList_i, struct sstd_c2py::typeSet& fmt){
	// argList.bin
	// F vec double F F 1 3
	// F vvec F F lenOfVec lenOfVec[0] lenOfVec[1] lenOfVec[2] ...
	
	std::vector<std::vector<T>>   argBuf(0); // This buffer will not be used, while the "fmt.pointer" is true.
	std::vector<std::vector<T>>* pArgBuf;
	if(fmt.pointer){
		pArgBuf    = va_arg(ap, std::vector<std::vector<T>>*);
		pArgList_i = pArgBuf; // adding a pointer to the "pArgList[i]".
	}else{
		 argBuf = va_arg(ap, std::vector<std::vector<T>>);
		pArgBuf = &argBuf;
	}
	
	fmt.arrLen.clear();
	for(uint i=0; i<pArgBuf->size(); i++){ fmt.arrLen.push_back((*pArgBuf)[i].size()); }
	
	vvec2file(fp, (*pArgBuf));
}

#define mat_write2file(matType, type)									\
	if(fList[i].pointer){ matType<type>* pArgBuf=va_arg(ap, matType<type>*); fp.fwrite(&(*pArgBuf)[0], sizeof(type), (*pArgBuf).size()); fList[i].arrLen.clear(); fList[i].arrLen.push_back((*pArgBuf).rows()); fList[i].arrLen.push_back((*pArgBuf).cols()); pArgList[i]=pArgBuf; \
	}        else       { matType<type>   argBuf=va_arg(ap, matType<type> ); fp.fwrite(    &argBuf[0], sizeof(type),     argBuf.size()); fList[i].arrLen.clear(); fList[i].arrLen.push_back(    argBuf.rows()); fList[i].arrLen.push_back(    argBuf.cols()); }

#define mat_write2file_str(matType)										\
	/* argList.bin */													\
	/* F mat str F F lenOfInfo rows cols strLen1 strLen2 strLen3 ... */	\
																		\
	matType<std::string>   argBuf(0, 0); /* This buffer will not be used, while the "fmt.pointer" is true. */ \
	matType<std::string>* pArgBuf;										\
	if(fList[i].pointer){												\
		pArgBuf     = va_arg(ap, matType<std::string>*);				\
		pArgList[i] = pArgBuf; /* adding a pointer to the "pArgList[i]". */	\
	}else{																\
		 argBuf = va_arg(ap, matType<std::string>);						\
		pArgBuf = &argBuf;												\
	}																	\
																		\
	uint64 len=(uint64)pArgBuf->size();									\
	fList[i].arrLen.clear();											\
	fList[i].arrLen.push_back((*pArgBuf).rows());						\
	fList[i].arrLen.push_back((*pArgBuf).cols());						\
	uint64 len_sum=0;													\
	for(uint v=0; v<len; v++){											\
		fList[i].arrLen.push_back((*pArgBuf)[v].size());				\
		len_sum += (*pArgBuf)[v].size();								\
	}																	\
	std::string writeBuf(len_sum, '\0'); writeBuf.clear();				\
	for(uint v=0; v<len; v++){ writeBuf+=(*pArgBuf)[v]; }				\
																		\
	fp.fwrite(&writeBuf[0], sizeof(char), writeBuf.size());				\

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

bool isBuiltin(char N_num){ if(num_bool==N_num || num_char==N_num || num_uchar==N_num || num_int8==N_num || num_uint8==N_num || num_int16==N_num || num_uint16==N_num || num_int32==N_num || num_uint32==N_num || num_int64==N_num || num_uint64==N_num || num_float==N_num || num_double==N_num){ return true; }else{ return false; } }

//------------------------------------------------------------------

std::vector<void*> sstd_c2py::getArg_and_write2file(va_list& ap, const char* writeDir_base, std::vector<std::string> fSList, std::vector<struct sstd_c2py::typeSet>& fList){
	
	std::vector<void*> pArgList(fList.size(), 0); // note noly pointer type
	for(uint i=1; i<fList.size(); i++){ // begin 1 to avoid return value
		if(fList[i].retTF){
			if(!fList[i].pointer){ sstd::pdbg("ERROR: ret type must be a pointer type."); return std::vector<void*>(); }
			
			pArgList[i]=va_arg(ap, void*);
			
			uint32 len=1;
			fList[i].arrLen.clear();
			if(i<fList.size()-1 && num_len==fList[i+1].N_num){ len=va_arg(ap,uint32); fList[i].arrLen.push_back(len); i++; // adding i in order to pass the sequency of len_num
			}else if(              isBuiltin(fList[i].N_num)){                        fList[i].arrLen.push_back(len);
			}               else                             {                        fList[i].arrLen.push_back( 0 ); } // ret の場合，builtin 型以外は，サイズ 0 としておく．
			continue; // pass "ret" type
		}
		
		sstd::file fp; std::string writeDir = sstd::ssprintf("%s/arg%04d.bin", writeDir_base, i);
		if(!fp.fopen(writeDir.c_str(), "wb")){ sstd::pdbg("ERROR: fopen was failed. (%s can't open.)\n", writeDir.c_str()); return std::vector<void*>(); }
		
		switch(fList[i].case_num){
		case        num_len   :{ if((int)i-1<0 || !fList[i-1].pointer){ sstd::pdbg("ERROR: \"%s\": Previous of len (len is a length of pointer and treated as a uint32) must be pointer type (T*), without \"char*\", \"str* (std::string*)\", \"vec<T>* (std::vector<T>*)\", \"mat_c<T>* (sstd::mat_c<T>*)\" and \"mat_r<T>* (sstd::mat_r<T>*)\".\n", fSList[i].c_str()); } }break;
			
		case        num_bool  :{ builtIn_write2file(  bool, uint32); }break; // bool is treated as a 4 bytes type by va_arg();
		case        num_char  :{ builtIn_write2file_pChar();         }break; // "char*" is treated exceptionaly because of the utilization of strlen() in order to count its length.
		case        num_uchar :{ builtIn_write2file( uchar, uint32); }break; // ‘uchar {aka unsigned char}’ is promoted to ‘int’ when passed through ‘...’
		case        num_int8  :{ builtIn_write2file(  int8, uint32); }break; // ‘int8 {aka signed char}’ is promoted to ‘int’ when passed through ‘...’
		case        num_int16 :{ builtIn_write2file( int16, uint32); }break; // ‘int16 {aka short int}’ is promoted to ‘int’ when passed through ‘...’
		case        num_int32 :{ builtIn_write2file( int32,  int32); }break;
		case        num_int64 :{ builtIn_write2file( int64,  int64); }break;
		case        num_uint8 :{ builtIn_write2file( uint8, uint32); }break; // ‘uint8 {aka unsigned char}’ is promoted to ‘int’ when passed through ‘...’
		case        num_uint16:{ builtIn_write2file(uint16, uint32); }break; // ‘uint16 {aka short unsigned int}’ is promoted to ‘int’ when passed through ‘...’
		case        num_uint32:{ builtIn_write2file(uint32, uint32); }break;
		case        num_uint64:{ builtIn_write2file(uint64, uint64); }break;
		case        num_float :{ builtIn_write2file(double, double); }break; // ‘float’ is promoted to ‘double’ when passed through ‘...’// va_arg() ではなく，opertor() で読み込まれる時点で，既に double 型として扱われているので，uint32 で読み込んでも，壊れたデータしか読み込めない．
		case        num_double:{ builtIn_write2file(double, double); }break;
		case        num_str   :{ builtIn_write2file_pStr();          }break;
			
		case    vec_num_bool  :{ vec_write2file_bool();  }break;
		case    vec_num_char  :{ vec_write2file(  char); }break;
		case    vec_num_uchar :{ vec_write2file( uchar); }break;
		case    vec_num_int8  :{ vec_write2file(  int8); }break;
		case    vec_num_int16 :{ vec_write2file( int16); }break;
		case    vec_num_int32 :{ vec_write2file( int32); }break;
		case    vec_num_int64 :{ vec_write2file( int64); }break;
		case    vec_num_uint8 :{ vec_write2file( uint8); }break;
		case    vec_num_uint16:{ vec_write2file(uint16); }break;
		case    vec_num_uint32:{ vec_write2file(uint32); }break;
		case    vec_num_uint64:{ vec_write2file(uint64); }break;
		case    vec_num_float :{ vec_write2file( float); }break;
		case    vec_num_double:{ vec_write2file(double); }break;
		case    vec_num_str   :{ vec_write2file_str();   }break;
			
		case  vvec_num_bool   :{ /*vvec_write2file_bool(); */ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return std::vector<void*>(); }break;
		case  vvec_num_char   :{ /*vvec_write2file(  char);*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return std::vector<void*>(); }break;
		case  vvec_num_uchar  :{ /*vvec_write2file( uchar);*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return std::vector<void*>(); }break;
		case  vvec_num_int8   :{ /*vvec_write2file(  int8);*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return std::vector<void*>(); }break;
		case  vvec_num_int16  :{ /*vvec_write2file( int16);*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return std::vector<void*>(); }break;
		case  vvec_num_int32  :{ /*vvec_write2file( int32);*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return std::vector<void*>(); }break;
		case  vvec_num_int64  :{ /*vvec_write2file( int64);*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return std::vector<void*>(); }break;
		case  vvec_num_uint8  :{ /*vvec_write2file( uint8);*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return std::vector<void*>(); }break;
		case  vvec_num_uint16 :{ /*vvec_write2file(uint16);*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return std::vector<void*>(); }break;
		case  vvec_num_uint32 :{ /*vvec_write2file(uint32);*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return std::vector<void*>(); }break;
		case  vvec_num_uint64 :{ /*vvec_write2file(uint64);*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return std::vector<void*>(); }break;
		case  vvec_num_float  :{ /*vvec_write2file( float);*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return std::vector<void*>(); }break;
		case  vvec_num_double :{ vvec_write2file<double>(ap, fp, pArgList[i], fList[i]); }break;
		case  vvec_num_str    :{ /*vvec_write2file_str();  */ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return std::vector<void*>(); }break;
			
		case  mat_c_num_bool  :{ mat_write2file    (sstd::mat_c,   bool); }break;
		case  mat_c_num_char  :{ mat_write2file    (sstd::mat_c,   char); }break;
		case  mat_c_num_uchar :{ mat_write2file    (sstd::mat_c,  uchar); }break;
		case  mat_c_num_int8  :{ mat_write2file    (sstd::mat_c,   int8); }break;
		case  mat_c_num_int16 :{ mat_write2file    (sstd::mat_c,  int16); }break;
		case  mat_c_num_int32 :{ mat_write2file    (sstd::mat_c,  int32); }break;
		case  mat_c_num_int64 :{ mat_write2file    (sstd::mat_c,  int64); }break;
		case  mat_c_num_uint8 :{ mat_write2file    (sstd::mat_c,   int8); }break;
		case  mat_c_num_uint16:{ mat_write2file    (sstd::mat_c, uint16); }break;
		case  mat_c_num_uint32:{ mat_write2file    (sstd::mat_c, uint32); }break;
		case  mat_c_num_uint64:{ mat_write2file    (sstd::mat_c, uint64); }break;
		case  mat_c_num_float :{ mat_write2file    (sstd::mat_c,  float); }break;
		case  mat_c_num_double:{ mat_write2file    (sstd::mat_c, double); }break;
		case  mat_c_num_str   :{ mat_write2file_str(sstd::mat_c);         }break;
			
		case  mat_r_num_bool  :{ mat_write2file    (sstd::mat_r,   bool); }break;
		case  mat_r_num_char  :{ mat_write2file    (sstd::mat_r,   char); }break;
		case  mat_r_num_uchar :{ mat_write2file    (sstd::mat_r,  uchar); }break;
		case  mat_r_num_int8  :{ mat_write2file    (sstd::mat_r,   int8); }break;
		case  mat_r_num_int16 :{ mat_write2file    (sstd::mat_r,  int16); }break;
		case  mat_r_num_int32 :{ mat_write2file    (sstd::mat_r,  int32); }break;
		case  mat_r_num_int64 :{ mat_write2file    (sstd::mat_r,  int64); }break;
		case  mat_r_num_uint8 :{ mat_write2file    (sstd::mat_r,  uint8); }break;
		case  mat_r_num_uint16:{ mat_write2file    (sstd::mat_r, uint16); }break;
		case  mat_r_num_uint32:{ mat_write2file    (sstd::mat_r, uint32); }break;
		case  mat_r_num_uint64:{ mat_write2file    (sstd::mat_r, uint64); }break;
		case  mat_r_num_float :{ mat_write2file    (sstd::mat_r,  float); }break;
		case  mat_r_num_double:{ mat_write2file    (sstd::mat_r, double); }break;
		case  mat_r_num_str   :{ mat_write2file_str(sstd::mat_r);         }break;
			
		default:{ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<void*>(); }break;
		}
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
		if(pArgList[i]==0 || fList[i].constTF==true || fList[i].N_num==num_len){ continue; }
		
		sstd::file fp; std::string readDir=sstd::ssprintf("%s/arg%04d.bin", writeDir_base, i);
		if(!fp.fopen(readDir.c_str(), "rb")){ sstd::pdbg("ERROR: fopen was failed. (%s can't open.)\n", readDir.c_str()); return false; }
		
		// For built in types: If the length of pointer is smaller than return value, below lines will write back only pointer length.
		switch(fList[i].case_num){
		case        num_bool  :{ readLenOfPointer(  bool); }break;
		case        num_char  :{ readLenOfPointer(  char); }break; // Python says [TypeError: 'str' object does not support item assignment] so, this might be impossible.
		case        num_uchar :{ readLenOfPointer( uchar); }break;
		case        num_int8  :{ readLenOfPointer(  int8); }break;
		case        num_int16 :{ readLenOfPointer( int16); }break;
		case        num_int32 :{ readLenOfPointer( int32); }break;
		case        num_int64 :{ readLenOfPointer( int64); }break;
		case        num_uint8 :{ readLenOfPointer( uint8); }break;
		case        num_uint16:{ readLenOfPointer(uint16); }break;
		case        num_uint32:{ readLenOfPointer(uint32); }break;
		case        num_uint64:{ readLenOfPointer(uint64); }break;
		case        num_float :{ readLenOfPointer( float); }break;
		case        num_double:{ readLenOfPointer(double); }break;
		case        num_str   :{ readLenOfPointer_str();   }break; // Python says [TypeError: 'str' object does not support item assignment] so, this might be impossible.
			
		case    vec_num_bool  :{ if(!sstd_c2py::c2py_ret(*((std::vector<       bool>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case    vec_num_char  :{ if(!sstd_c2py::c2py_ret(*((std::vector<       char>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case    vec_num_uchar :{ if(!sstd_c2py::c2py_ret(*((std::vector<      uchar>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case    vec_num_int8  :{ if(!sstd_c2py::c2py_ret(*((std::vector<       int8>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case    vec_num_int16 :{ if(!sstd_c2py::c2py_ret(*((std::vector<      int16>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case    vec_num_int32 :{ if(!sstd_c2py::c2py_ret(*((std::vector<      int32>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case    vec_num_int64 :{ if(!sstd_c2py::c2py_ret(*((std::vector<      int64>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case    vec_num_uint8 :{ if(!sstd_c2py::c2py_ret(*((std::vector<      uint8>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case    vec_num_uint16:{ if(!sstd_c2py::c2py_ret(*((std::vector<     uint16>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case    vec_num_uint32:{ if(!sstd_c2py::c2py_ret(*((std::vector<     uint32>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case    vec_num_uint64:{ if(!sstd_c2py::c2py_ret(*((std::vector<     uint64>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case    vec_num_float :{ if(!sstd_c2py::c2py_ret(*((std::vector<      float>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case    vec_num_double:{ if(!sstd_c2py::c2py_ret(*((std::vector<     double>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case    vec_num_str   :{ if(!sstd_c2py::c2py_ret(*((std::vector<std::string>*)pArgList[i]), fp, lines[i])){ return false; } }break;
			
		case  vvec_num_bool   : { /*if(!sstd_c2py::c2py_ret(*((std::vector<std::vector<       bool>>*)pArgList[i]), fp, lines[i])){ return false; }*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return false; }break;
		case  vvec_num_char   : { /*if(!sstd_c2py::c2py_ret(*((std::vector<std::vector<       char>>*)pArgList[i]), fp, lines[i])){ return false; }*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return false; }break;
		case  vvec_num_uchar  : { /*if(!sstd_c2py::c2py_ret(*((std::vector<std::vector<      uchar>>*)pArgList[i]), fp, lines[i])){ return false; }*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return false; }break;
		case  vvec_num_int8   : { /*if(!sstd_c2py::c2py_ret(*((std::vector<std::vector<       int8>>*)pArgList[i]), fp, lines[i])){ return false; }*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return false; }break;
		case  vvec_num_int16  : { /*if(!sstd_c2py::c2py_ret(*((std::vector<std::vector<      int16>>*)pArgList[i]), fp, lines[i])){ return false; }*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return false; }break;
		case  vvec_num_int32  : { /*if(!sstd_c2py::c2py_ret(*((std::vector<std::vector<      int32>>*)pArgList[i]), fp, lines[i])){ return false; }*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return false; }break;
		case  vvec_num_int64  : { /*if(!sstd_c2py::c2py_ret(*((std::vector<std::vector<      int64>>*)pArgList[i]), fp, lines[i])){ return false; }*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return false; }break;
		case  vvec_num_uint8  : { /*if(!sstd_c2py::c2py_ret(*((std::vector<std::vector<      uint8>>*)pArgList[i]), fp, lines[i])){ return false; }*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return false; }break;
		case  vvec_num_uint16 : { /*if(!sstd_c2py::c2py_ret(*((std::vector<std::vector<     uint16>>*)pArgList[i]), fp, lines[i])){ return false; }*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return false; }break;
		case  vvec_num_uint32 : { /*if(!sstd_c2py::c2py_ret(*((std::vector<std::vector<     uint32>>*)pArgList[i]), fp, lines[i])){ return false; }*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return false; }break;
		case  vvec_num_uint64 : { /*if(!sstd_c2py::c2py_ret(*((std::vector<std::vector<     uint64>>*)pArgList[i]), fp, lines[i])){ return false; }*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return false; }break;
		case  vvec_num_float  : { /*if(!sstd_c2py::c2py_ret(*((std::vector<std::vector<      float>>*)pArgList[i]), fp, lines[i])){ return false; }*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return false; }break;
		case  vvec_num_double : { if(!sstd_c2py::c2py_ret(*((std::vector<std::vector<     double>>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  vvec_num_str    : { /*if(!sstd_c2py::c2py_ret(*((std::vector<std::vector<std::string>>*)pArgList[i]), fp, lines[i])){ return false; }*/ sstd::pdbg("ERROR: \"%s\" is not implimented yet for vvec<T>.\n", fSList[i].c_str()); return false; }break;
			
		case  mat_c_num_bool  : { if(!sstd_c2py::c2py_ret(*((sstd::mat_c<       bool>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_c_num_char  : { if(!sstd_c2py::c2py_ret(*((sstd::mat_c<       char>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_c_num_uchar : { if(!sstd_c2py::c2py_ret(*((sstd::mat_c<      uchar>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_c_num_int8  : { if(!sstd_c2py::c2py_ret(*((sstd::mat_c<       int8>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_c_num_int16 : { if(!sstd_c2py::c2py_ret(*((sstd::mat_c<      int16>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_c_num_int32 : { if(!sstd_c2py::c2py_ret(*((sstd::mat_c<      int32>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_c_num_int64 : { if(!sstd_c2py::c2py_ret(*((sstd::mat_c<      int64>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_c_num_uint8 : { if(!sstd_c2py::c2py_ret(*((sstd::mat_c<      uint8>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_c_num_uint16: { if(!sstd_c2py::c2py_ret(*((sstd::mat_c<     uint16>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_c_num_uint32: { if(!sstd_c2py::c2py_ret(*((sstd::mat_c<     uint32>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_c_num_uint64: { if(!sstd_c2py::c2py_ret(*((sstd::mat_c<     uint64>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_c_num_float : { if(!sstd_c2py::c2py_ret(*((sstd::mat_c<      float>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_c_num_double: { if(!sstd_c2py::c2py_ret(*((sstd::mat_c<     double>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_c_num_str   : { if(!sstd_c2py::c2py_ret(*((sstd::mat_c<std::string>*)pArgList[i]), fp, lines[i])){ return false; } }break;
			
		case  mat_r_num_bool  : { if(!sstd_c2py::c2py_ret(*((sstd::mat_r<       bool>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_r_num_char  : { if(!sstd_c2py::c2py_ret(*((sstd::mat_r<       char>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_r_num_uchar : { if(!sstd_c2py::c2py_ret(*((sstd::mat_r<      uchar>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_r_num_int8  : { if(!sstd_c2py::c2py_ret(*((sstd::mat_r<       int8>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_r_num_int16 : { if(!sstd_c2py::c2py_ret(*((sstd::mat_r<      int16>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_r_num_int32 : { if(!sstd_c2py::c2py_ret(*((sstd::mat_r<      int32>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_r_num_int64 : { if(!sstd_c2py::c2py_ret(*((sstd::mat_r<      int64>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_r_num_uint8 : { if(!sstd_c2py::c2py_ret(*((sstd::mat_r<      uint8>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_r_num_uint16: { if(!sstd_c2py::c2py_ret(*((sstd::mat_r<     uint16>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_r_num_uint32: { if(!sstd_c2py::c2py_ret(*((sstd::mat_r<     uint32>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_r_num_uint64: { if(!sstd_c2py::c2py_ret(*((sstd::mat_r<     uint64>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_r_num_float : { if(!sstd_c2py::c2py_ret(*((sstd::mat_r<      float>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_r_num_double: { if(!sstd_c2py::c2py_ret(*((sstd::mat_r<     double>*)pArgList[i]), fp, lines[i])){ return false; } }break;
		case  mat_r_num_str   : { if(!sstd_c2py::c2py_ret(*((sstd::mat_r<std::string>*)pArgList[i]), fp, lines[i])){ return false; } }break;
			
		default:{ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return false; }break;
		}
	}
	return true;
}

//--------------------------------------------------------------------------------------------------------

