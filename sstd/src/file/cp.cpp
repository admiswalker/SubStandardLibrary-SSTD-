#include "cp.hpp"

#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h> // read(), write()
#include <utime.h>
#include <unordered_map>
#include <algorithm> // sort()

#include "glob.hpp"
#include "mkdir.hpp"
#include "path.hpp"
#include "../string/strmatch.hpp"
#include "../print/pdbg.hpp"
//#include "../print.hpp" // for dbg


bool cmp_stat_equalToOrGreater(struct timespec& lhs, struct timespec& rhs){ // lhs >= rhs: true
    if(lhs.tv_sec>=rhs.tv_sec){ return true; }
    if(lhs.tv_sec==rhs.tv_sec && lhs.tv_nsec>=rhs.tv_nsec){ return true; }
    return false;
}
bool _copy_base(const char* pPath_src, const char* pPath_dst, const bool opt_n, const bool opt_p, const bool opt_u){
    bool fExist = false; // init to suppress a gcc warning (no need to initialize this option).
    int fd_src, fd_dst;
    struct stat st_src, st_dst;
    
    bool ret = true;
    char pBuf[4096]; // buf[1024];
    ssize_t size;
    struct timespec ts_buf[2];
    
    if(opt_n || opt_u){
        fExist = sstd::fileExist(pPath_dst);
        if(opt_n && fExist){ return true; }
    }
    if(::strcmp(pPath_src, pPath_dst)==0){ return false; }
    
    fd_src = open(pPath_src, O_RDONLY); if(fd_src<0){ return false; }
    if(fstat(fd_src, &st_src)!=0){ close(fd_src); return false; }
    fd_dst = open(pPath_dst, O_CREAT|O_WRONLY, st_src.st_mode); if(fd_dst<0){ close(fd_src); return false; }

    if(opt_u && fExist){
        if(fstat(fd_dst, &st_dst)!=0){ ret=false; goto exit; }
        if(cmp_stat_equalToOrGreater(st_dst.st_atim, st_src.st_atim)){ ret=true; goto exit; } // time stamp of dst file is equal to or greater than src file.
    }
    
    while((size=read(fd_src, pBuf, sizeof(pBuf))) > 0){
        if( write(fd_dst, pBuf, size) != size){ ret=false; goto exit; }
    }
    if(ftruncate(fd_dst, st_src.st_size)!=0){ ret=false; goto exit; } // Align the output file size with the input file when overwriting the existing file larger than input file.

    if(opt_p){
        ts_buf[0]=st_src.st_atim;
        ts_buf[1]=st_src.st_mtim;
        if(futimens(fd_dst, ts_buf)!=0){ ret=false; goto exit; }
    }
    
 exit:
    close(fd_dst);
    close(fd_src);
    return ret;
}
#define get_options()                                                         \
    bool opt_n=false;                                                          \
    bool opt_p=false;                                                          \
    bool opt_u=false;                                                          \
    for(uint i=0; opt[i]!='\0'; ++i){                                          \
        switch(opt[i]){                                                        \
        case 'n': { opt_n=true; break; }                                       \
        case 'p': { opt_p=true; break; }                                       \
        case 'u': { opt_u=true; break; }                                       \
        default: { sstd::pdbg_err("sstd::copy(): Unexpected option.\n"); break; } \
        }                                                                      \
    }
bool sstd::copy(const char*        pPath_src, const char*        pPath_dst, const char* opt){ get_options(); return _copy_base(pPath_src        , pPath_dst        , opt_n, opt_p, opt_u); }
bool sstd::copy(const std::string&  path_src, const char*        pPath_dst, const char* opt){ get_options(); return _copy_base( path_src.c_str(), pPath_dst        , opt_n, opt_p, opt_u); }
bool sstd::copy(const char*        pPath_src, const std::string&  path_dst, const char* opt){ get_options(); return _copy_base(pPath_src        ,  path_dst.c_str(), opt_n, opt_p, opt_u); }
bool sstd::copy(const std::string&  path_src, const std::string&  path_dst, const char* opt){ get_options(); return _copy_base( path_src.c_str(),  path_dst.c_str(), opt_n, opt_p, opt_u); }

bool sstd::copy(const char*        pPath_src, const char*        pPath_dst){ return _copy_base( pPath_src       , pPath_dst        , false, false, false); }
bool sstd::copy(const std::string&  path_src, const char*        pPath_dst){ return _copy_base( path_src.c_str(), pPath_dst        , false, false, false); }
bool sstd::copy(const char*        pPath_src, const std::string&  path_dst){ return _copy_base(pPath_src        ,  path_dst.c_str(), false, false, false); }
bool sstd::copy(const std::string&  path_src, const std::string&  path_dst){ return _copy_base( path_src.c_str(),  path_dst.c_str(), false, false, false); }


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
bool setTimestamp2file(const std::string& dirPath, const struct stat& st){
    bool ret=true;
    int fd = open(dirPath.c_str(), O_WRONLY); if(fd<0){ return false; }
    
    struct timespec ts_buf[2];
    ts_buf[0]=st.st_atim;
    ts_buf[1]=st.st_mtim;
    if(futimens(fd, ts_buf)!=0){ ret=false; goto exit; }

 exit:
    close(fd);
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
bool _cp_base(const char* pPath_src, const char* pPath_dst, const bool opt_n, const bool opt_p, const bool opt_u){
    bool TF_file = sstd::isFile(pPath_src);
    bool TF_dir  = sstd::isDir (pPath_src);
//  bool TF_wc   = !(TF_file||TF_dir); // when path include wild card
    
    if(TF_file){
        // test case01: when pPath_src is a file

        if(sstd::isDir(pPath_dst)){
            std::string path_dst = std::string(pPath_dst)+'/'+sstd::path2fileName(pPath_src);
            return _copy_base(pPath_src, path_dst.c_str(), opt_n, opt_p, opt_u);
        }else{
            return _copy_base(pPath_src, pPath_dst,        opt_n, opt_p, opt_u);
        }
    }else if(TF_dir){
        // test case02: when pPath_src is a directory

        std::string dstPath_baseDir = std::string(pPath_dst)+'/'+sstd::path2dirName(pPath_src);
        struct stat st; if(stat(pPath_src, &st)!=0){ return false; }
        ::mkdir(dstPath_baseDir.c_str(), st.st_mode);
        
        std::vector<sstd::pathAndType> vPath = sstd::glob_pt(std::string(pPath_src)+"/*", "dfr");
        uint begin_idx = sstd::path2dirName_begin_idx(pPath_src);
        for(uint i=0; i!=vPath.size(); ++i){
            if(vPath[i].type=='f'){
                // when vPath[i].path is a file path
                std::string file_dst = std::string(pPath_dst)+'/'+&(vPath[i].path[begin_idx]);
                _copy_base(vPath[i].path.c_str(), file_dst.c_str(), opt_n, opt_p, opt_u);
            }else{
                // when vPath[i].path is a directory path
                std::string dir_dst = std::string(pPath_dst)+'/'+&(vPath[i].path[begin_idx]);
                ::mkdir(dir_dst.c_str(), vPath[i].st.st_mode);
            }
        }
        
        if(opt_p){
            for(uint i=0; i!=vPath.size(); ++i){
                if(vPath[i].type=='f'){ continue; }
                
                std::string dir_dst = std::string(pPath_dst)+'/'+&(vPath[i].path[begin_idx]);
                if(!setTimestamp2dir(dir_dst, vPath[i].st)){ return false; }
            }
            if(!setTimestamp2dir(dstPath_baseDir, st)){ return false; }
        }
        
        return true;
        
    }else{
        // test case03: when pPath_src is a path with wild card
        
        // Implementation policy
        //
        // 1. extract required directories including files in order not to copy empty directories, when copying like "*.txt".
        //    example:
        //      excute function:
        //                            sstd::cp("./tmp1/*.txt", "./tmp2");
        //
        //      Directory structure:
        //                            ./tmp1/a/01.txt
        //                                   b/
        //                                   c/02.txt
        //                            ./tmp2/
        //
        //      description:
        //        The directories a/, b/ and c/ are contained in `vDirToMake` before the `vDir_matchWC` was inserted.
        //
        // 2. considering about copying empty directories, when copying like "exampleDir/*".
        //    example:
        //      excute function:
        //                            sstd::cp("./tmp1/*", "./tmp2");
        //
        //      Directory structure:
        //                            ./tmp1/a/
        //                                   b/
        //                                   c/
        //                            ./tmp2/
        //
        //      description:
        //        The directories a/, b/ and c/ are contained in `vDir_matchWC`.

        // Data flow
        //
        //   vPath
        //     |---dirs   ->  strmatch()  ->  `vDir_matchWC`  ->  generate_directories()
        //     |
        //     |---files  ->  strmatch(): get all path that match wildcard
        //                ->  getPath(): get all directory paths
        //                ->  rm_duplicate(): remove duplicated path
        //                ->  parsePath_withBase(): generate all possible direcotry paths to make directory recursively.
        //                                         (generating all possible and impossible candidates).
        //                ->  rm_duplicate(): remove duplicated path
        //                ->  sort(): sort path to make direcories in order from the bottom layer.
        //                ->  getAND(): 1. get AND with `vDir` to remove impossible candidates,
        //                                 because `vDir` has only possible candidates.
        //                              2. get AND with `vDir` to convert data type
        //                ->  generate_directories()
        
        sstd::mkdir(pPath_dst);
        std::vector<sstd::pathAndType> vPath = sstd::glob_pt(sstd::path2basePath_woWC(pPath_src)+"/*", "dfr");

        std::vector<sstd::pathAndType> vFile, vFile_matchWC;
        std::vector<sstd::pathAndType> vDir, vDir_matchWC;
        for(uint i=0; i<vPath.size(); ++i){
            if(vPath[i].type=='f'){ vFile.push_back( std::move(vPath[i]) );
            }        else         { vDir.push_back( std::move(vPath[i]) ); }
        }
        
        for(uint i=0; i<vFile.size(); ++i){
            if(!sstd::strmatch(vFile[i].path, pPath_src)){ continue; }
            vFile_matchWC.push_back( std::move(vFile[i]) );
        }
        for(uint i=0; i<vDir.size(); ++i){
            if(!sstd::strmatch(vDir[i].path, pPath_src)){ continue; }
            vDir_matchWC.push_back( vDir[i] );
        }
        
        std::vector<std::string> vDirOfFile;
        for(uint i=0; i<vFile_matchWC.size(); ++i){
            vDirOfFile.push_back( sstd::path2basePath(vFile_matchWC[i].path.c_str()) );
        }
        vDirOfFile = rmDuplicate<std::string>(vDirOfFile);
        
        std::vector<std::string> vDirOfFile_splitted;
        for(uint i=0; i<vDirOfFile.size(); ++i){
            std::vector<std::string> vP = sstd::parsePath_wBasePath(vDirOfFile[i].c_str());
            vDirOfFile_splitted.insert(vDirOfFile_splitted.end(), vP.begin(), vP.end());
        }
        vDirOfFile_splitted = rmDuplicate<std::string>(vDirOfFile_splitted);
        
        std::sort(vDirOfFile_splitted.begin(), vDirOfFile_splitted.end());
        std::vector<sstd::pathAndType> vDirToMake = getAND_ltype(vDir, vDirOfFile_splitted); // get AND, because vDir has all possible directories candidate.
        
        vDirToMake.insert(vDirToMake.end(), vDir_matchWC.begin(), vDir_matchWC.end());
        
        //---
        
        uint end_idx = sstd::path2dirName_end_idx_woWC(pPath_src);
        for(uint i=0; i<vDirToMake.size(); ++i){
            std::string dir_dst = std::string(pPath_dst)+'/'+&(vDirToMake[i].path[end_idx]);
            ::mkdir(dir_dst.c_str(), vDirToMake[i].st.st_mode);
        }
        for(uint i=0; i<vFile_matchWC.size(); ++i){
            std::string path_dst = std::string(pPath_dst)+'/'+&(vFile_matchWC[i].path[end_idx]);
            _copy_base(vFile_matchWC[i].path.c_str(), path_dst.c_str(), opt_n, opt_p, opt_u);
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
bool sstd::cp  (const char*        pPath_src, const char*        pPath_dst, const char* opt){ get_options(); return _cp_base(pPath_src        , pPath_dst        , opt_n, opt_p, opt_u); }
bool sstd::cp  (const std::string&  path_src, const char*        pPath_dst, const char* opt){ get_options(); return _cp_base( path_src.c_str(), pPath_dst        , opt_n, opt_p, opt_u); }
bool sstd::cp  (const char*        pPath_src, const std::string&  path_dst, const char* opt){ get_options(); return _cp_base(pPath_src        ,  path_dst.c_str(), opt_n, opt_p, opt_u); }
bool sstd::cp  (const std::string&  path_src, const std::string&  path_dst, const char* opt){ get_options(); return _cp_base( path_src.c_str(),  path_dst.c_str(), opt_n, opt_p, opt_u); }

bool sstd::cp  (const char*        pPath_src, const char*        pPath_dst){ return _cp_base(pPath_src        , pPath_dst        , false, false, false); }
bool sstd::cp  (const std::string&  path_src, const char*        pPath_dst){ return _cp_base( path_src.c_str(), pPath_dst        , false, false, false); }
bool sstd::cp  (const char*        pPath_src, const std::string&  path_dst){ return _cp_base(pPath_src        ,  path_dst.c_str(), false, false, false); }
bool sstd::cp  (const std::string&  path_src, const std::string&  path_dst){ return _cp_base( path_src.c_str(),  path_dst.c_str(), false, false, false); }

#undef get_options

