#include "cp.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h> // read(), write()
#include <unordered_map>
#include <algorithm> // sort()

#include "glob.hpp"
#include "mkdir.hpp"
#include "path.hpp"
#include "../string/strmatch.hpp"
#include "../pdbg.hpp"
#include "../print.hpp" // for dbg


bool _copy_base(const char* pPath_src, const char* pPath_dst, const bool opt_p){
    if(::strcmp(pPath_src, pPath_dst)==0){ return false; }
    
    int fd_src = open(pPath_src, O_RDONLY); if(fd_src<0){ return false; }
    struct stat st; if(fstat(fd_src, &st)!=0){ close(fd_src); return false; }
    int fd_dst = open(pPath_dst, O_CREAT|O_WRONLY, st.st_mode); if(fd_dst<0){ close(fd_src); return false; }
    
    bool ret = true;
    char pBuf[4096]; // buf[1024];
    ssize_t size;
    struct timespec ts_buf[2];
    while((size=read(fd_src, pBuf, sizeof(pBuf))) > 0){
        if( write(fd_dst, pBuf, size) != size){ ret=false; goto exit; }
    }
    if(ftruncate(fd_dst, st.st_size)!=0){ ret=false; goto exit; } // Align the output file size with the input file when overwriting the existing file larger than input file.

    if(opt_p){
        ts_buf[0]=st.st_atim;
        ts_buf[1]=st.st_mtim;
        if(futimens(fd_dst, ts_buf)!=0){ ret=false; goto exit; }
    }
    
 exit:
    close(fd_dst);
    close(fd_src);
    return ret;
}
bool sstd::copy(const char*        pPath_src, const char*        pPath_dst, const char* opt){
//  bool opt_n=false;
    bool opt_p=false;
//  bool opt_u=false;
    for(uint i=0; opt[i]!='\0'; ++i){
        switch(opt[i]){
//      case 'n': { opt_n=true; break; }
        case 'p': { opt_p=true; break; }
//      case 'u': { opt_u=true; break; }
        default: { sstd::pdbg("ERROR: glob(): Unexpected option.\n"); break; }
        }
    }
    return _copy_base(pPath_src, pPath_dst, opt_p);
}
bool sstd::copy(const char*        pPath_src, const char*        pPath_dst){ return _copy_base( pPath_src       , pPath_dst        , false); }
bool sstd::copy(const std::string&  path_src, const char*        pPath_dst){ return _copy_base( path_src.c_str(), pPath_dst        , false); }
bool sstd::copy(const char*        pPath_src, const std::string&  path_dst){ return _copy_base(pPath_src        ,  path_dst.c_str(), false); }
bool sstd::copy(const std::string&  path_src, const std::string&  path_dst){ return _copy_base( path_src.c_str(),  path_dst.c_str(), false); }


template <typename T>
std::vector<T> rmDuplicate(const std::vector<T>& v){
    using is = std::pair<T,char>;
    
    std::unordered_map<T,char> hashT;
    for(uint i=0; i<v.size(); ++i){
        hashT.insert( is{v[i], 0} );
    }
    
    std::vector<T> ret(hashT.size());
    uint i=0;
    for(auto itr=hashT.begin(); itr!=hashT.end(); ++itr){
        ret[i] = itr->first;
        ++i;
    }
    
    return ret;
}
/*
template <typename T>
std::vector<T> getAND(const std::vector<T>& lhs, const std::vector<T>& rhs){
    using is = std::pair<T,char>;
    
    std::unordered_map<T,uint64> hashT;
    for(uint i=0; i<lhs.size(); ++i){
        hashT.insert( is{lhs[i], 0} );
    }
    
    std::vector<T> ret;
    for(uint i=0; i<rhs.size(); ++i){
        if(hashT.find(rhs[i])!=hashT.end()){ continue; }
        ret.push_back( rhs[i] );
    }
    
    return ret;
}
*/
std::vector<sstd::pathAndType> getAND_ltype(const std::vector<sstd::pathAndType>& lhs, const std::vector<std::string>& rhs){
    using is = std::pair<std::string,uint>;
    
    std::unordered_map<std::string,uint> hashT;
    for(uint i=0; i<lhs.size(); ++i){
        hashT.insert( is{lhs[i].path, i} );
    }
    
    std::vector<sstd::pathAndType> ret;
    for(uint i=0; i<rhs.size(); ++i){
        auto itr = hashT.find(rhs[i]);
        if(itr!=hashT.end()){
            ret.push_back( lhs[ itr->second ] );
        }
    }
    
    return ret;
}
bool setTimestamp2dir(const std::string& dirPath, const struct stat& st){
    bool ret=true;
    int fd = open(dirPath.c_str(), O_DIRECTORY); if(fd<0){ return false; }
    
    struct timespec ts_buf[2];
    ts_buf[0]=st.st_atim;
    ts_buf[1]=st.st_mtim;
    if(futimens(fd, ts_buf)!=0){ ret=false; goto exit; }

 exit:
    close(fd);
    return ret;
}
bool _cp_base(const char* pPath_src, const char* pPath_dst, const bool opt_p){
    bool TF_file = sstd::isFile(pPath_src);
    bool TF_dir  = sstd::isDir (pPath_src);
//  bool TF_wc   = !(TF_file||TF_dir); // when path include wild card
    
    if(TF_file){
        // test case01: when pPath_src is a file
        
        sstd::mkdir(sstd::getPath(pPath_dst));
        return _copy_base(pPath_src, pPath_dst, opt_p);
        
    }else if(TF_dir){
        // test case02: when pPath_src is a directory

        sstd::mkdir(pPath_dst);
        std::string dstPath_baseDir = std::string(pPath_dst)+'/'+sstd::getDirName(pPath_src);
        struct stat st; if(stat(pPath_src, &st)!=0){ return false; }
        ::mkdir(dstPath_baseDir.c_str(), st.st_mode);
        
        std::vector<sstd::pathAndType> vPath = sstd::glob_pt(std::string(pPath_src)+"/*", "dfr");
        uint begin_idx = sstd::getDirName_begin_idx(pPath_src);
        for(uint i=0; i!=vPath.size(); ++i){
            if(vPath[i].type=='f'){
                // when vPath[i].path is a file path
                std::string path_dst = std::string(pPath_dst)+'/'+&(vPath[i].path[begin_idx]);
                _copy_base(vPath[i].path.c_str(), path_dst.c_str(), opt_p);
            }else{
                // when vPath[i].path is a directory path
                std::string dir_dst = std::string(pPath_dst)+'/'+&(vPath[i].path[begin_idx]);
                ::mkdir(dir_dst.c_str(), vPath[i].st.st_mode);
            }
        }
        
        if(opt_p){
            for(uint i=0; i!=vPath.size(); ++i){
                if(vPath[i].type=='f'){ continue; }
                // when vPath[i].path is a directory path
                std::string dir_dst = std::string(pPath_dst)+'/'+&(vPath[i].path[begin_idx]);
                if(!setTimestamp2dir(dir_dst, vPath[i].st)){ return false; }
            }
            if(!setTimestamp2dir(dstPath_baseDir, st)){ return false; }
        }
        
        return true;
        
    }else{
        // test case03: when pPath_src is a path with wild card
        
        sstd::mkdir(pPath_dst);
        std::vector<sstd::pathAndType> vPath = sstd::glob_pt(sstd::getPath_woWC(pPath_src)+"/*", "dfr");

        std::vector<sstd::pathAndType> vFile, vFile_matchWC;
        std::vector<sstd::pathAndType> vDir;
        for(uint i=0; i<vPath.size(); ++i){
            if(vPath[i].type=='f'){ vFile.push_back( std::move(vPath[i]) );
            }        else         { vDir.push_back( std::move(vPath[i]) ); }
        }
        
        for(uint i=0; i<vFile.size(); ++i){
            if(!sstd::strmatch(vFile[i].path, pPath_src)){ continue; }
            vFile_matchWC.push_back( std::move(vFile[i]) );
        }
        
        std::vector<std::string> vDirOfFile;
        for(uint i=0; i<vFile_matchWC.size(); ++i){
            vDirOfFile.push_back( sstd::getPath(vFile_matchWC[i].path.c_str()) );
        }
        vDirOfFile = rmDuplicate<std::string>(vDirOfFile);
        
        std::vector<std::string> vDirOfFile_splitted;
        for(uint i=0; i<vDirOfFile.size(); ++i){
            std::vector<std::string> vP = sstd::parsePath_withBase(vDirOfFile[i].c_str());
            vDirOfFile_splitted.insert(vDirOfFile_splitted.end(), vP.begin(), vP.end());
        }
        vDirOfFile_splitted = rmDuplicate<std::string>(vDirOfFile_splitted);
        
        std::sort(vDirOfFile_splitted.begin(), vDirOfFile_splitted.end());
        std::vector<sstd::pathAndType> vDirToMake = getAND_ltype(vDir, vDirOfFile_splitted);

        //---
        
        uint end_idx = sstd::getDirName_end_idx_woWC(pPath_src);
        for(uint i=0; i<vDirToMake.size(); ++i){
            std::string dir_dst = std::string(pPath_dst)+'/'+&(vDirToMake[i].path[end_idx]);
            ::mkdir(dir_dst.c_str(), vDirToMake[i].st.st_mode);
        }
        for(uint i=0; i<vFile_matchWC.size(); ++i){
            std::string path_dst = std::string(pPath_dst)+'/'+&(vFile_matchWC[i].path[end_idx]);
            _copy_base(vFile_matchWC[i].path.c_str(), path_dst.c_str(), opt_p);
        }

        if(opt_p){
            for(uint i=0; i<vDirToMake.size(); ++i){
                std::string dir_dst = std::string(pPath_dst)+'/'+&(vDirToMake[i].path[end_idx]);
                if(!setTimestamp2dir(dir_dst, vDirToMake[i].st)){ return false; }
            }
        }
        
        return true;
    }
    
    return true;
}
bool sstd::cp(const char* pPath_src, const char* pPath_dst, const char* opt){
//  bool opt_n=false;
    bool opt_p=false;
//  bool opt_u=false;
    for(uint i=0; opt[i]!='\0'; ++i){
        switch(opt[i]){
//      case 'n': { opt_n=true; break; }
        case 'p': { opt_p=true; break; }
//      case 'u': { opt_u=true; break; }
        default: { sstd::pdbg("ERROR: glob(): Unexpected option.\n"); break; }
        }
    }
    return _cp_base(pPath_src, pPath_dst, opt_p);
}
bool sstd::cp  (const char*        pPath_src, const char*        pPath_dst){ return _cp_base(pPath_src        , pPath_dst        , false); }
bool sstd::cp  (const std::string&  path_src, const char*        pPath_dst){ return _cp_base( path_src.c_str(), pPath_dst        , false); }
bool sstd::cp  (const char*        pPath_src, const std::string&  path_dst){ return _cp_base(pPath_src        ,  path_dst.c_str(), false); }
bool sstd::cp  (const std::string&  path_src, const std::string&  path_dst){ return _cp_base( path_src.c_str(),  path_dst.c_str(), false); }
