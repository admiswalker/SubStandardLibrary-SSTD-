#include "cp.hpp"
#include <string.h>

#include "mkdir.hpp"
#include "path.hpp"
#include "../print.hpp" // for dbg


bool sstd::copy(const char*        pPath_src, const char*        pPath_dst){
    if(strcmp(pPath_src, pPath_dst)==0){ return false; }
    FILE* fp_src = fopen(pPath_src, "rb"); if(!fp_src){                 return false; }
    FILE* fp_dst = fopen(pPath_dst, "wb"); if(!fp_dst){ fclose(fp_src); return false; }
    
    bool ret = true;
    char buf[4096]; // buf[1024];
    size_t size;
    while((size=fread(buf, sizeof(char), sizeof(buf), fp_src)) > 0){
        if( fwrite(buf, sizeof(char), size, fp_dst) != size){ ret=false; break; }
    }

    fclose(fp_dst);
    fclose(fp_src);
    return ret;
}
bool sstd::copy(const std::string&  path_src, const char*        pPath_dst){ return sstd::copy( path_src.c_str(), pPath_dst        ); }
bool sstd::copy(const char*        pPath_src, const std::string&  path_dst){ return sstd::copy(pPath_src        ,  path_dst.c_str()); }
bool sstd::copy(const std::string&  path_src, const std::string&  path_dst){ return sstd::copy( path_src.c_str(),  path_dst.c_str()); }


bool sstd::cp  (const char*        pPath_src, const char*        pPath_dst){
    bool TF_file = sstd::isFile(pPath_src);
    bool TF_dir  = sstd::isDir (pPath_src);
//  bool TF_wc   = !(TF_file||TF_dir); // when path include wild card
    
    if(TF_file){
        // when pPath_src is a file
        
        sstd::mkdir(sstd::getPath(pPath_dst));
        return sstd::copy(pPath_src, pPath_dst);
        
    }else if(TF_dir){
        // when pPath_src is a directory
        
        std::string dstPath_baseDir = std::string(pPath_dst)+'/'+sstd::getDirName(pPath_src);
        sstd::mkdir(dstPath_baseDir);
        
        std::vector<sstd::pathAndType> vPath = sstd::glob_pt(std::string(pPath_src)+"/*", "dfr");
        uint begin_idx = sstd::getDirName_begin_idx(pPath_src);
        for(uint i=0; i!=vPath.size(); ++i){
            if(vPath[i].type=='f'){
                // when vPath[i].path is a file path
                std::string path_dst = std::string(pPath_dst)+'/'+&(vPath[i].path[begin_idx]);
                sstd::copy(vPath[i].path.c_str(), path_dst.c_str());
            }else{
                // when vPath[i].path is a directory path
                std::string dir_dst = std::string(pPath_dst)+'/'+&(vPath[i].path[begin_idx]);
                sstd::mkdir(dir_dst.c_str());
            }
        }
        
        return true;
        
    }else{
        // when pPath_src is a path with wild card
        
        sstd::mkdir(pPath_dst);
        
        std::vector<sstd::pathAndType> vPath = sstd::glob_pt(std::string(pPath_src), "dfr");
        uint end_idx = sstd::getDirName_end_idx_woWC(pPath_src);
        for(uint i=0; i!=vPath.size(); ++i){
            if(vPath[i].type=='f'){
                // when vPath[i].path is a file path
                std::string path_dst = std::string(pPath_dst)+'/'+&(vPath[i].path[end_idx]);
                sstd::mkdir(sstd::getPath_woWC(path_dst.c_str()).c_str());
                sstd::copy(vPath[i].path.c_str(), path_dst.c_str());
            }else{
                // when vPath[i].path is a directory path
                std::string dir_dst = std::string(pPath_dst)+'/'+&(vPath[i].path[end_idx]);
                sstd::mkdir(dir_dst.c_str());
            }
        }
        return true;
    }
    
    return true;
}
bool sstd::cp  (const std::string&  path_src, const char*        pPath_dst){ return sstd::cp  ( path_src.c_str(), pPath_dst        ); }
bool sstd::cp  (const char*        pPath_src, const std::string&  path_dst){ return sstd::cp  (pPath_src        ,  path_dst.c_str()); }
bool sstd::cp  (const std::string&  path_src, const std::string&  path_dst){ return sstd::cp  ( path_src.c_str(),  path_dst.c_str()); }
