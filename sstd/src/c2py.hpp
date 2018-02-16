#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include <time.h>
#include <string.h>

#include "./typeDef.h"
#include "./file.hpp"
#include "./ssprintf.hpp"
#include "./mkdir.hpp"
#include "./rm.hpp"
#include "./time.hpp"
#include "./strEdit.hpp"
#include "./str2num.hpp"
#include "./MatrixStore_mat/mat.hpp"
#include "./MatrixStore_mat_rowMajor/mat_r.hpp"

#include "./print.hpp" // for debug (リリース時に削除するように)

//--------------------------------------------------------------------------------------------------------

// 名前空間を汚染しないように，namespace へ入れておく

namespace sstd_c2py{
	struct typeSet{
	private:
	public:
		typeSet(){ constTF=false; N_num=0; T_num=0; pointer=false; pointer_sidePy=false; cnv2builtIn_sidePy=false; }
		~typeSet(){}
 		bool retTF;                   // true: 戻り値として扱う．(true の場合は，値を書き戻すために，必ず，pointer も true でなければならない．) false: 引数として扱う．
 		bool constTF;                 // true: ポインタの先の書き戻しを行う．false: ポインタの先の書き戻しを行わない．
		                              // const-> true, not const -> false.
		std::string name; char N_num; // void, int, vec<T>... and so on. // number of value
		std::string    T; char T_num; // template<typename "T"> or "" // number of value
		bool pointer;                 // *: pointer type sybol on cpp side                         // on left than vertical line '|' as a symbol of split
		bool pointer_sidePy;          // *: pointer type sybol on python side                      // on right than vertical line '|' as a symbol of split
		bool cnv2builtIn_sidePy;      // ~: conversion command to built in function on python side // on right than vertical line '|' as a symbol of split
		std::vector<uint32> arrLen;   // Array length of T*, str, vec<T>, mat<T> and mat_r<T>.
	};
	
	template<typename T> void operator_brackets(T& ret, const char* writeDir_base, const char* iFile, const char* fName, std::vector<std::string>& fSList, std::vector<struct sstd_c2py::typeSet>& fList, int argc, ...);
	
	std::vector<struct typeSet> format_str2typeSet(const std::vector<std::string>& fSList);
	std::string format_typeSet2str(const std::vector<struct typeSet>& fList);
	bool make_argList(const std::string& writeDir_base, std::string typeStr);

	std::vector<void*> getArg_and_write2file(va_list& ap, const char* writeDir_base, std::vector<std::string> fSList, std::vector<struct sstd_c2py::typeSet>& fList);
	bool writeBack(std::vector<std::string>& lines, std::vector<void*>& pArgList, const char* writeDir_base, std::vector<std::string>& fSList, std::vector<struct sstd_c2py::typeSet>& fList);

	bool isRetVoid(std::vector<struct sstd_c2py::typeSet>& fList);
	
	bool c2py_ret(                   bool & inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(                   char & inOut, sstd::file& fp, std::string& line);
//	bool c2py_ret(                  uchar & inOut, sstd::file& fp, std::string& line); // same as uint8
	bool c2py_ret(                   int8 & inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(                  int16 & inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(                  int32 & inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(                  int64 & inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(                  uint8 & inOut, sstd::file& fp, std::string& line); // same as uchar
	bool c2py_ret(                 uint16 & inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(                 uint32 & inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(                 uint64 & inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(                  float & inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(                 double & inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(            std::string & inOut, sstd::file& fp, std::string& line);
	
	bool c2py_ret(std::vector<       bool>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(std::vector<       char>& inOut, sstd::file& fp, std::string& line);
//	bool c2py_ret(std::vector<      uchar>& inOut, sstd::file& fp, std::string& line); // same as uint8
	bool c2py_ret(std::vector<       int8>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(std::vector<      int16>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(std::vector<      int32>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(std::vector<      int64>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(std::vector<      uint8>& inOut, sstd::file& fp, std::string& line); // same as uchar
	bool c2py_ret(std::vector<     uint16>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(std::vector<     uint32>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(std::vector<     uint64>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(std::vector<      float>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(std::vector<     double>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(std::vector<std::string>& inOut, sstd::file& fp, std::string& line);
	
	bool c2py_ret(sstd::mat  <       bool>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat  <       char>& inOut, sstd::file& fp, std::string& line);
//	bool c2py_ret(sstd::mat  <      uchar>& inOut, sstd::file& fp, std::string& line); // same as uint8
	bool c2py_ret(sstd::mat  <       int8>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat  <      int16>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat  <      int32>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat  <      int64>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat  <      uint8>& inOut, sstd::file& fp, std::string& line); // same as uchar
	bool c2py_ret(sstd::mat  <     uint16>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat  <     uint32>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat  <     uint64>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat  <      float>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat  <     double>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat  <std::string>& inOut, sstd::file& fp, std::string& line);
	
	bool c2py_ret(sstd::mat_r<       bool>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat_r<       char>& inOut, sstd::file& fp, std::string& line);
//	bool c2py_ret(sstd::mat_r<      uchar>& inOut, sstd::file& fp, std::string& line); // same as uint8
	bool c2py_ret(sstd::mat_r<       int8>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat_r<      int16>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat_r<      int32>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat_r<      int64>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat_r<      uint8>& inOut, sstd::file& fp, std::string& line); // same as uchar
	bool c2py_ret(sstd::mat_r<     uint16>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat_r<     uint32>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat_r<     uint64>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat_r<      float>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat_r<     double>& inOut, sstd::file& fp, std::string& line);
	bool c2py_ret(sstd::mat_r<std::string>& inOut, sstd::file& fp, std::string& line);
}

//--------------------------------------------------------------------------------------------------------
#define sstd_c2py_private												\
	std::string tmpDir;                          /* temporarilyDir   */ \
	std::string iFile;                           /* importFile       */ \
	std::string fName;                           /* functionName     */ \
	std::vector<std::string> fSList;             /* formatStringList */ \
	std::vector<struct sstd_c2py::typeSet> fList /* format list      */
#define sstd_c2py_constructor()											\
	tmpDir=temporarilyDir;												\
	iFile=importFile;													\
	fName=functionName;													\
																		\
	sstd::mkdir(tmpDir.c_str());										\
	fSList = sstd::removeSpace_of_HeadAndTail(sstd::split(format, ','));\
	fList  = sstd_c2py::format_str2typeSet(fSList)
#define sstd_c2py_destructor()											\
	//sstd::printn(sstd::rm(tmpDir.c_str())); // Don't enable this line, because if some one share "tmpDir", some times you may delete files that running other "sstd::c2py" function.
//----------------------------------------------------
namespace sstd{ template<typename T> class c2py; }

template<typename T> class sstd::c2py{
private: sstd_c2py_private;
public: c2py(const char* temporarilyDir, const char* importFile, const char* functionName, const char* format){ sstd_c2py_constructor(); } ~c2py(){ sstd_c2py_destructor(); };

	template<typename... ARGS>
	T operator()(ARGS... args){
		// make temporary directory
		struct timeval time_v=sstd::getTimeval(); std::string writeDir_base=sstd::ssprintf("%s/%lu_%06lu", tmpDir.c_str(), time_v.tv_sec, time_v.tv_usec);
		sstd::mkdir(writeDir_base);
		
		int argc = fList.size()-1;
		T ret; sstd_c2py::operator_brackets(ret, writeDir_base.c_str(), iFile.c_str(), fName.c_str(), fSList, fList, argc, args...);

		// erase temp
		sstd::rm(writeDir_base); // when you debug c2py, commenting this line will remain data files in the tmp directory.
		return ret;
	}
};
//----------------------------------------------------
// Template specialization for "void".
namespace sstd{ template<> class c2py<void>; }

template<> class sstd::c2py<void>{
private: sstd_c2py_private;
public: c2py(const char* temporarilyDir, const char* importFile, const char* functionName, const char* format){ sstd_c2py_constructor(); } ~c2py(){ sstd_c2py_destructor(); };

	template<typename... ARGS>
	void operator()(ARGS... args){
		// make temporary directory
		struct timeval time_v=sstd::getTimeval(); std::string writeDir_base=sstd::ssprintf("%s/%lu_%06lu", tmpDir.c_str(), time_v.tv_sec, time_v.tv_usec);
		sstd::mkdir(writeDir_base);
		
		int argc = fList.size()-1;
		int ret; sstd_c2py::operator_brackets<int>(ret, writeDir_base.c_str(), iFile.c_str(), fName.c_str(), fSList, fList, argc, args...);

		// erase tmp
		sstd::rm(writeDir_base); // when you debug c2py, commenting this line will remain data files in the tmp directory.
	}
};
//----------------------------------------------------
#undef sstd_c2py_private
#undef sstd_c2py_constructor
#undef sstd_c2py_destructor
//--------------------------------------------------------------------------------------------------------

template<typename T>
inline void sstd_c2py::operator_brackets(T& ret, const char* writeDir_base, const char* iFile, const char* fName, std::vector<std::string>& fSList, std::vector<struct sstd_c2py::typeSet>& fList, int argc, ...){

	// write args values to the files
	va_list ap; va_start(ap, argc); // #define っぽいので，va_start を別関数にするとバグる．va_arg は関数やテンプレート関数でも問題なかった．
	std::vector<void*> pArgList = sstd_c2py::getArg_and_write2file(ap, writeDir_base, fSList, fList);
	va_end(ap);
	if(pArgList.size()==0){ return; } // ERROR
	
	// make argList.bin
	std::string typeStr = sstd_c2py::format_typeSet2str(fList);
	if(!sstd_c2py::make_argList(writeDir_base, typeStr)){ return; }
	
	// run python as a system command
		// "./sstd/src/" に "c2py.py" があるのは，ディレクトリにそのまま保存している場合だけなので，
		// システムにインストールされている場合は，ヘッダと一緒にコピーされているはずなので，そこへ path を通す．
		// 幾つか可能性のある path を file exist して確認する．
	std::string path_to_c2py_py;
	if      (sstd::fexist("./sstd/src/c2py.py"             )){ path_to_c2py_py = "./sstd/src/c2py.py";
	}else if(sstd::fexist("./sstd/include/sstd/src/c2py.py")){ path_to_c2py_py = "./sstd/include/sstd/src/c2py.py";
	}else if(sstd::fexist("/usr/include/sstd/src/c2py.py"  )){ path_to_c2py_py = "/usr/include/sstd/src/c2py.py";
	}else if(sstd::fexist("./c2py.py"                      )){ path_to_c2py_py = "./c2py.py";
	}                       else                             { sstd::pdbg_always("ERROR: \"c2py.py\" is not found."); return; }
	system(sstd::ssprintf("python -u %s %s %s %s", path_to_c2py_py.c_str(), writeDir_base, iFile, fName).c_str());
	
	// write back non const pointer args.
		// read "argList.bin"
	std::vector<std::string> lines = sstd::splitByLine(sstd::readAll_withoutBOM(sstd::ssprintf("%s/argList.bin", writeDir_base).c_str()));
	if(!sstd_c2py::writeBack(lines, pArgList, writeDir_base, fSList, fList)){ return; } // ERROR
	
	// read return value
	{
		if(sstd_c2py::isRetVoid(fList)){ return; }
		
		sstd::file fp; std::string readDir=sstd::ssprintf("%s/arg0000.bin", writeDir_base);
		if(!fp.fopen(readDir.c_str(), "rb")){ sstd::pdbg_always("ERROR: fopen was failed. (%s can't open.)\n", readDir.c_str()); return; }
		if(!sstd_c2py::c2py_ret(ret, fp, lines[0])){ return; }
	}
	return;
}

//--------------------------------------------------------------------------------------------------------

