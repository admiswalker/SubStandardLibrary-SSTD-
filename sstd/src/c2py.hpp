﻿#pragma once
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <vector>
#include <time.h>
#include <string.h>
#include <random>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
    #define omp_get_max_threads() 1
#endif

#include "typeDef.h"
#include "file/file.hpp"
#include "file/read_write.hpp"
#include "string/ssprintf.hpp"
#include "file/mkdir.hpp"
#include "file/rm.hpp"
#include "time/time.hpp"
#include "string/strEdit.hpp"
#include "string/strmatch.hpp"
#include "file/path.hpp"
#include "pid.hpp"
#include "matrixContainer_colMajor/mat_c.hpp"
#include "matrixContainer_rowMajor/mat_r.hpp"

//#include "print/print.hpp" // for debug (リリース時に削除するように)

//--------------------------------------------------------------------------------------------------------

// 名前空間を汚染しないように，namespace へ入れておく

namespace sstd_c2py{
    struct typeSet{
    private:
    public:
        typeSet(){ constTF=false; case_num=0; N_num=0; T_num=0; pointer=false; pointer_sidePy=false; cnv2builtIn_sidePy=false; }
        ~typeSet(){}
         bool retTF;                   // true: 戻り値として扱う．(true の場合は，値を書き戻すために，必ず，pointer も true でなければならない．) false: 引数として扱う．
         bool constTF;                 // true: ポインタの先の書き戻しを行う．false: ポインタの先の書き戻しを行わない．
                                       // const-> true, not const -> false.
        uchar case_num;                // case number is an id number identified by N_num and T_num.
        std::string name; uchar N_num; // void, int, vec<T>... and so on. // number of value
        std::string    T; uchar T_num; // template<typename "T"> or "" // number of value
        bool pointer;                  // *: pointer type sybol on cpp side                         // on left than vertical line '|' as a symbol of split
        bool pointer_sidePy;           // *: pointer type sybol on python side                      // on right than vertical line '|' as a symbol of split
        bool cnv2builtIn_sidePy;       // ~: conversion command to built in function on python side // on right than vertical line '|' as a symbol of split
        std::vector<uint32> arrLen;    // Array length of T*, str, vec<T>, mat<T> and mat_r<T>.
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
//  bool c2py_ret(                  uchar & inOut, sstd::file& fp, std::string& line); // same as uint8
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
//  bool c2py_ret(std::vector<      uchar>& inOut, sstd::file& fp, std::string& line); // same as uint8
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
    
//    bool c2py_ret(std::vector<std::vector<       bool>>& inOut, sstd::file& fp, std::string& line);
//    bool c2py_ret(std::vector<std::vector<       char>>& inOut, sstd::file& fp, std::string& line);
////    bool c2py_ret(std::vector<std::vector<      uchar>>& inOut, sstd::file& fp, std::string& line); // same as uint8
//    bool c2py_ret(std::vector<std::vector<       int8>>& inOut, sstd::file& fp, std::string& line);
//    bool c2py_ret(std::vector<std::vector<      int16>>& inOut, sstd::file& fp, std::string& line);
//    bool c2py_ret(std::vector<std::vector<      int32>>& inOut, sstd::file& fp, std::string& line);
//    bool c2py_ret(std::vector<std::vector<      int64>>& inOut, sstd::file& fp, std::string& line);
//    bool c2py_ret(std::vector<std::vector<      uint8>>& inOut, sstd::file& fp, std::string& line); // same as uchar
//    bool c2py_ret(std::vector<std::vector<     uint16>>& inOut, sstd::file& fp, std::string& line);
//    bool c2py_ret(std::vector<std::vector<     uint32>>& inOut, sstd::file& fp, std::string& line);
//    bool c2py_ret(std::vector<std::vector<     uint64>>& inOut, sstd::file& fp, std::string& line);
//    bool c2py_ret(std::vector<std::vector<      float>>& inOut, sstd::file& fp, std::string& line);
    bool c2py_ret(std::vector<std::vector<     double>>& inOut, sstd::file& fp, std::string& line);
//  bool c2py_ret(std::vector<std::vector<std::string>>& inOut, sstd::file& fp, std::string& line);
    
    bool c2py_ret(sstd::mat_c<       bool>& inOut, sstd::file& fp, std::string& line);
    bool c2py_ret(sstd::mat_c<       char>& inOut, sstd::file& fp, std::string& line);
//  bool c2py_ret(sstd::mat_c<      uchar>& inOut, sstd::file& fp, std::string& line); // same as uint8
    bool c2py_ret(sstd::mat_c<       int8>& inOut, sstd::file& fp, std::string& line);
    bool c2py_ret(sstd::mat_c<      int16>& inOut, sstd::file& fp, std::string& line);
    bool c2py_ret(sstd::mat_c<      int32>& inOut, sstd::file& fp, std::string& line);
    bool c2py_ret(sstd::mat_c<      int64>& inOut, sstd::file& fp, std::string& line);
    bool c2py_ret(sstd::mat_c<      uint8>& inOut, sstd::file& fp, std::string& line); // same as uchar
    bool c2py_ret(sstd::mat_c<     uint16>& inOut, sstd::file& fp, std::string& line);
    bool c2py_ret(sstd::mat_c<     uint32>& inOut, sstd::file& fp, std::string& line);
    bool c2py_ret(sstd::mat_c<     uint64>& inOut, sstd::file& fp, std::string& line);
    bool c2py_ret(sstd::mat_c<      float>& inOut, sstd::file& fp, std::string& line);
    bool c2py_ret(sstd::mat_c<     double>& inOut, sstd::file& fp, std::string& line);
    bool c2py_ret(sstd::mat_c<std::string>& inOut, sstd::file& fp, std::string& line);
    
    bool c2py_ret(sstd::mat_r<       bool>& inOut, sstd::file& fp, std::string& line);
    bool c2py_ret(sstd::mat_r<       char>& inOut, sstd::file& fp, std::string& line);
//  bool c2py_ret(sstd::mat_r<      uchar>& inOut, sstd::file& fp, std::string& line); // same as uint8
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
#define sstd_c2py_private                                               \
    std::string tmpDir;                          /* temporarilyDir   */ \
    std::string iFile;                           /* importFile       */ \
    std::string fName;                           /* functionName     */ \
    std::vector<std::string> fSList;             /* formatStringList */ \
    std::vector<struct sstd_c2py::typeSet> fList /* format list      */
#define sstd_c2py_constructor()                                         \
    tmpDir=temporarilyDir;                                              \
    iFile=importFile;                                                   \
    fName=functionName;                                                 \
                                                                        \
    sstd::mkdir(tmpDir.c_str());                                        \
    fSList = sstd::strip(sstd::split(format, ','));                     \
    fList  = sstd_c2py::format_str2typeSet(fSList)
#define sstd_c2py_destructor()                                          \
    //sstd::printn(sstd::rm(tmpDir.c_str())); // Don't enable this line, because if some one share "tmpDir", some times you may delete files that running on the other "sstd::c2py" function.
//----------------------------------------------------
namespace sstd{ template<typename T> class c2py; }

template<typename T> class sstd::c2py{
private: sstd_c2py_private;
public: c2py(const char* temporarilyDir, const char* importFile, const char* functionName, const char* format){ sstd_c2py_constructor(); } ~c2py(){ sstd_c2py_destructor(); };

    template<typename... ARGS>
    T operator()(ARGS... args){
        // make temporary directory
        struct timeval time_v=sstd::getTimeval();
        std::random_device rng; uint rand=rng();
        uint32 pid = (uint32)sstd::getpid(); // To avoid conflicts with multiprocessing
        uint32 otn = (uint32)omp_get_thread_num();
        std::string writeDir_base=sstd::ssprintf("%s/%lu_%06lu_%lu_%lu_%lu", tmpDir.c_str(), time_v.tv_sec, time_v.tv_usec, rand, pid, otn);
        sstd::mkdir(writeDir_base);
        
        int argc = fList.size()-1;
        T ret; sstd_c2py::operator_brackets(ret, writeDir_base.c_str(), iFile.c_str(), fName.c_str(), fSList, fList, argc, args...);
        
        // erase temp
        sstd::rm(writeDir_base); // when you debug c2py, commentting out this line will remain data files in the tmp directory.
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
        struct timeval time_v=sstd::getTimeval();
        std::random_device rng; uint rand=rng();
        uint32 pid = (uint32)sstd::getpid(); // To avoid conflicts with multiprocessing
        uint32 otn = (uint32)omp_get_thread_num();
        std::string writeDir_base=sstd::ssprintf("%s/%lu_%06lu_%lu_%lu_%lu", tmpDir.c_str(), time_v.tv_sec, time_v.tv_usec, rand, pid, otn);
        sstd::mkdir(writeDir_base);
        
        int argc = fList.size()-1;
        int ret; sstd_c2py::operator_brackets<int>(ret, writeDir_base.c_str(), iFile.c_str(), fName.c_str(), fSList, fList, argc, args...);

        // erase tmp
        sstd::rm(writeDir_base); // when you debug c2py, commentting out this line will remain data files in the tmp directory.
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
    if      (sstd::fileExist("./sstd/src/c2py.py"             )){ path_to_c2py_py = "./sstd/src/c2py.py";
    }else if(sstd::fileExist("./sstd/include/sstd/src/c2py.py")){ path_to_c2py_py = "./sstd/include/sstd/src/c2py.py";
    }else if(sstd::fileExist("/usr/include/sstd/src/c2py.py"  )){ path_to_c2py_py = "/usr/include/sstd/src/c2py.py";
    }else if(sstd::fileExist("./c2py.py"                      )){ path_to_c2py_py = "./c2py.py";
    }                        else                               { sstd::pdbg_err("\"c2py.py\" is not found."); return; }
    if(system(sstd::ssprintf("python -u %s %s %s %s", path_to_c2py_py.c_str(), writeDir_base, iFile, fName).c_str())!=0){ sstd::pdbg_err("system() was failed.\n"); return; }
    
    // write back non const pointer args.
        // read "argList.bin"
    std::vector<std::string> lines = sstd::splitByLine(sstd::read_withoutBOM(sstd::ssprintf("%s/argList.bin", writeDir_base).c_str()));
    if(!sstd_c2py::writeBack(lines, pArgList, writeDir_base, fSList, fList)){ return; } // ERROR
    
    // read return value
    {
        if(sstd_c2py::isRetVoid(fList)){ return; }
        
        sstd::file fp; std::string readDir=sstd::ssprintf("%s/arg0000.bin", writeDir_base);
        if(!fp.fopen(readDir.c_str(), "rb")){ sstd::pdbg_err("fopen was failed. (%s can't open.)\n", readDir.c_str()); return; }
        if(!sstd_c2py::c2py_ret(ret, fp, lines[0])){ return; }
    }
    return;
}

//--------------------------------------------------------------------------------------------------------

