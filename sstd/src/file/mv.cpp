#include "mv.hpp"

#include <stdio.h>

#include "path.hpp"
#include "../print.hpp" // for dbg


/*
bool sstd::mv  (const char*        pPath_src, const char*        pPath_dst, const char* opt){
    // memo: refer to a src/file/cp.cpp implementation
}
bool sstd::mv  (const std::string&  path_src, const char*        pPath_dst, const char* opt);
bool sstd::mv  (const char*        pPath_src, const std::string&  path_dst, const char* opt);
bool sstd::mv  (const std::string&  path_src, const std::string&  path_dst, const char* opt);
//*/

bool sstd::mv  (const char*        pPath_src, const char*        pPath_dst){
    bool TFs_file = sstd::isFile(pPath_src);
    bool TFs_dir  = sstd::isDir (pPath_src);
    bool TFs_WC   = (!TFs_file) && (!TFs_dir);
//  bool TFd_file = sstd::isFile(pPath_dst);
    bool TFd_dir  = sstd::isDir (pPath_dst);
    
    if(TFs_file && (!TFd_dir)){
        // file to file
        ::rename(pPath_src, pPath_dst);
        
    }else if(TFs_file && TFd_dir){
        // file to dir
        std::string path_dst = std::string(pPath_dst) + '/' + sstd::path2fileName(pPath_src);
        ::rename(pPath_src, path_dst.c_str());
        
    }else if(TFs_dir && TFd_dir){
        // dir to dir
        std::string path_dst = std::string(pPath_dst) + '/' + sstd::path2fileName(pPath_src);
        ::rename(pPath_src, path_dst.c_str());
        
    }else if(TFs_WC && TFd_dir){
        // wildcard to dir

        // Not Implimented
    }else{
        return false;
    }
    
    return true;
}
bool sstd::mv  (const std::string&  path_src, const char*        pPath_dst){ return sstd::mv( path_src.c_str(), pPath_dst        ); }
bool sstd::mv  (const char*        pPath_src, const std::string&  path_dst){ return sstd::mv(pPath_src        ,  path_dst.c_str()); }
bool sstd::mv  (const std::string&  path_src, const std::string&  path_dst){ return sstd::mv( path_src.c_str(),  path_dst.c_str()); }

