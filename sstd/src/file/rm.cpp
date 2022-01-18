#include "rm.hpp"

#include "glob.hpp"
#include "path.hpp"
#include "../pdbg.hpp"
#include "../typeDef.h"

#include <vector>
#include <dirent.h>
#include <sys/stat.h> // stat(), S_ISDIR()
#include <string.h>   // strcmp()
#include <unistd.h>   // rmdir(), unlink()

//-------------------------------------------------------------------------------------------------------

bool sstd::unlink(const char* pPath){
    #ifdef _WIN32
        return DeleteFile(pPath);
    #else
        if(::unlink(pPath)==0){ return true; }else{ sstd::pdbg("ERROR: sstd::unlink(): %s.\n", strerror(errno)); return false; };
    #endif
}
bool sstd::unlink(const std::string& path){ return sstd::unlink(path.c_str()); }

//--------------------------------------------------------------------------------------------------------

bool sstd::rmdir(const char* pPath){
    #ifdef _WIN32
        return RemoveDirectory(pPath);
    #else
        return ::rmdir(pPath)==0;
    #endif
}
bool sstd::rmdir(const std::string& path){ return sstd::rmdir(path.c_str()); }

//--------------------------------------------------------------------------------------------------------

bool sstd::rm(const char* pPath){
    bool ret = true;
    
    std::vector<struct sstd::pathAndType> v_pt = sstd::glob_pt(pPath+std::string("/*"), "dfr");
    for(uint i=0; i<v_pt.size(); ++i){
        printf("path: %s\n", v_pt[i].path.c_str());
        printf("type: %c\n\n", v_pt[i].type);
    }
    
    // remove under pPath
    for(int i=v_pt.size()-1; i>=0; --i){
        switch(v_pt[i].type){
        case 'f': { if(!sstd::unlink(v_pt[i].path.c_str())){ret=false;} break; }
        case 'd': { if(!sstd::rmdir (v_pt[i].path.c_str())){ret=false;} break; }
        default: { sstd::pdbg("ERROR: sstd::rm(): sstd::glob_pt() returned unexpected file type.\n"); ret=false; break; }
        }
    }
    
    // remove myself (pPath)
    if(sstd::isFile(pPath)){
        if(!sstd::unlink(pPath)){ret=false;}
    }else{
        if(!sstd::rmdir(pPath)){ret=false;}
    }
    
    return ret;
}
bool sstd::rm(const std::string& path){ return sstd::rm(path.c_str()); }

//--------------------------------------------------------------------------------------------------------

