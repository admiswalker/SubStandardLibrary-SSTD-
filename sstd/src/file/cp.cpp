#include "cp.hpp"
#include <string.h>

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


bool sstd::cp  (const char*        pPath){
//    std::vector<sstd::pathAndType> vPath = sstd::glob_pt(pPath_src+std::string("/*"), "dfr");
//    sstd::printn(vPath);
    return true;
}
bool sstd::cp  (const std::string&  path){ return sstd::cp(path.c_str()); }
