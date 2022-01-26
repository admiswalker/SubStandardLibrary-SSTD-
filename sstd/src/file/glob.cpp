#include "glob.hpp"

#include <dirent.h>
#include <sys/stat.h> //stat(), S_ISDIR
#include <string.h>   //strcmp()

#include <stdio.h>    //std::sort
#include <vector>     //std::sort
#include <algorithm>  //std::sort
#include <functional> //std::sort

#include <stdexcept>
#include <stdio.h>

#include "path.hpp"
#include "../pdbg.hpp"
#include "../string/strmatch.hpp"
#include "../typeDef.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------

std::vector<std::string> _glob_worker(const std::string& search_path_in, const char* wild_card, const bool opt_d, const bool opt_f, const bool opt_p, const bool opt_r){
    DIR *pDir;
    struct dirent *pEnt;
    struct stat Stat;
    std::vector<std::string> v_path;
    std::vector<std::string> v_path_stack; // Useing STACK in order NOT to exceed the limit of opendir() number.

    v_path_stack.push_back(search_path_in+'/');
    
    for(;v_path_stack.size()!=0;){
        std::string search_path = v_path_stack.back(); v_path_stack.pop_back();
        
        pDir = opendir(search_path.c_str());
        if(pDir==NULL){ continue; } // No files or directories.
        
        for(pEnt=readdir(pDir); pEnt!=0; pEnt=readdir(pDir)){
            // get file status
            std::string path = search_path + pEnt->d_name;
            if( stat( path.c_str(), &Stat ) ){
                sstd::pdbg("ERROR: glob_worker(): Failed to get stat %s\n", path.c_str());
                break;
            }
            
            bool TF_match;
            if(opt_p){ TF_match = sstd::pathmatch(path, wild_card);
            }  else  { TF_match = sstd::strmatch (path, wild_card); }
            
            if (S_ISDIR(Stat.st_mode)){
                // when a directory
                if((strcmp( pEnt->d_name, "." )!=0) && (strcmp( pEnt->d_name, ".." )!=0)){
                    // subdirectory
                    // printf( "subdirectory: %s\n", pEnt->d_name );
                    if(opt_d && TF_match){
                        v_path.push_back( path );
                    }
                    if(opt_r){
                        v_path_stack.push_back( path + '/' );
                    }
                }else{
                    //  . current directory
                    // .. parent directory
                    // printf( "current or parent directory: %s\n", pEnt->d_name );
                
                    // --- nothing to do ---
                }
            }else{
                // when a file
                if(opt_f && TF_match){
                    v_path.push_back( path );
                }
            }
        }
        closedir(pDir);
        if(!opt_r){ break; }
    }
    
    return v_path;
}
std::vector<std::string> _glob_base(const char* path_wc, const bool opt_d, const bool opt_f, const bool opt_p, const bool opt_r){
    std::string search_path = sstd::getPath_woWC(path_wc);
    std::vector<std::string> v_path = _glob_worker(search_path.c_str(), path_wc, opt_d, opt_f, opt_p, opt_r);
    std::sort(v_path.begin(), v_path.end());
    return v_path;
}
std::vector<std::string> sstd::glob(const char* path, const char* opt){
    bool opt_d=false;
    bool opt_f=false;
    bool opt_p=false;
    bool opt_r=false;
    for(uint i=0; opt[i]!='\0'; ++i){
        switch(opt[i]){
        case 'd': { opt_d=true; break; }
        case 'f': { opt_f=true; break; }
        case 'p': { opt_p=true; break; }
        case 'r': { opt_r=true; break; }
        default: { sstd::pdbg("ERROR: glob(): Unexpected option.\n"); break; }
        }
    }
    return _glob_base(path, opt_d, opt_f, opt_p, opt_r);
}
std::vector<std::string> sstd::glob(const std::string& path, const char* opt){ return sstd::glob(path.c_str(), opt); }
std::vector<std::string> sstd::glob(const        char* path){ return sstd::glob(path, "f"); }
std::vector<std::string> sstd::glob(const std::string& path){ return sstd::glob(path.c_str(), "f"); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

std::vector<struct sstd::pathAndType> _glob_worker_pt(const std::string& search_path_in, const char* wild_card, const bool opt_d, const bool opt_f, const bool opt_p, const bool opt_r){
    DIR *pDir;
    struct dirent *pEnt;
    struct stat Stat;
    std::vector<struct sstd::pathAndType> v_path;
    std::vector<std::string> v_path_stack; // Useing STACK in order NOT to exceed the limit of opendir() number.

    v_path_stack.push_back(search_path_in+'/');
    
    for(;v_path_stack.size()!=0;){
        std::string search_path = v_path_stack.back(); v_path_stack.pop_back();
        
        pDir = opendir(search_path.c_str());
        if(pDir==NULL){ continue; } // No files or directories.
        
        for(pEnt=readdir(pDir); pEnt!=0; pEnt=readdir(pDir)){
            // get file status
            std::string path = search_path + pEnt->d_name;
            if( stat( path.c_str(), &Stat ) ){
                sstd::pdbg("ERROR: glob_worker(): Failed to get stat %s\n", path.c_str());
                break;
            }
            
            bool TF_match;
            if(opt_p){ TF_match = sstd::pathmatch(path, wild_card);
            }  else  { TF_match = sstd::strmatch (path, wild_card); }
            
            if (S_ISDIR(Stat.st_mode)){
                // when a directory
                if((strcmp( pEnt->d_name, "." )!=0) && (strcmp( pEnt->d_name, ".." )!=0)){
                    // subdirectory
                    // printf( "subdirectory: %s\n", pEnt->d_name );
                    if(opt_d && TF_match){
                        struct sstd::pathAndType pt;
                        pt.path = path;
                        pt.type = 'd';
                        v_path.push_back( pt );
                    }
                    if(opt_r){
                        v_path_stack.push_back( path + '/' );
                    }
                }else{
                    //  . current directory
                    // .. parent directory
                    // printf( "current or parent directory: %s\n", pEnt->d_name );
                
                    // --- nothing to do ---
                }
            }else{
                // when a file
                if(opt_f && TF_match){
                    struct sstd::pathAndType pt;
                    pt.path = path;
                    pt.type = 'f';
                    v_path.push_back( pt );
                }
            }
        }
        closedir(pDir);
        if(!opt_r){ break; }
    }
    
    return v_path;
}
std::vector<struct sstd::pathAndType> _glob_base_pt(const char* path_wc, const bool opt_d, const bool opt_f, const bool opt_p, const bool opt_r){
    std::string search_path = sstd::getPath_woWC(path_wc);
    std::vector<struct sstd::pathAndType> v_path = _glob_worker_pt(search_path.c_str(), path_wc, opt_d, opt_f, opt_p, opt_r);
    std::sort(v_path.begin(), v_path.end());
    return v_path;
}
std::vector<struct sstd::pathAndType> sstd::glob_pt(const char* path, const char* opt){
    bool opt_d=false;
    bool opt_f=false;
    bool opt_p=false;
    bool opt_r=false;
    for(uint i=0; opt[i]!='\0'; ++i){
        switch(opt[i]){
        case 'd': { opt_d=true; break; }
        case 'f': { opt_f=true; break; }
        case 'p': { opt_p=true; break; }
        case 'r': { opt_r=true; break; }
        default: { sstd::pdbg("ERROR: glob(): Unexpected option.\n"); break; }
        }
    }
    return _glob_base_pt(path, opt_d, opt_f, opt_p, opt_r);
}
std::vector<struct sstd::pathAndType> sstd::glob_pt(const std::string& path, const char* opt){ return sstd::glob_pt(path.c_str(), opt); }
std::vector<struct sstd::pathAndType> sstd::glob_pt(const        char* path){ return sstd::glob_pt(path, "f"); }
std::vector<struct sstd::pathAndType> sstd::glob_pt(const std::string& path){ return sstd::glob_pt(path.c_str(), "f"); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
