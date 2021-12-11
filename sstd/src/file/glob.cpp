#include "glob.hpp"

#ifdef _WIN32   //windows環境の場合は「_WIN32」が定義されているので、こちら。

    #include <winsock2.h> // for "struct timeval" // マクロが再定義されました。主な原因は、<WinSock2.h>より先に<windows.h>がインクルードされたことです。Windowsの制約として、windows.hよりも先にwinsock2.hをインクルードすることが必要です。http://www.02.246.ne.jp/~torutk/cxx/socket/win32_socket.html
    #include <windows.h>
    #undef min
    #undef max
#else

    #include <dirent.h>
    #include <sys/stat.h>    //stat(), S_ISDIR
    #include <string.h>        //strcmp()

    #include <stdio.h>        //std::sort
    #include <vector>        //std::sort
    #include <algorithm>    //std::sort
    #include <functional>    //std::sort
#endif

#include <stdexcept>
#include <stdio.h>

#include "path.hpp"
#include "../pdbg.hpp"
#include "../string/strmatch.hpp"
#include "../typeDef.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------

std::vector<std::string> _glob_worker(const std::string& search_path, const char* wild_card, const bool opt_d, const bool opt_f, const bool opt_r){
    DIR *pDir;
    struct dirent *pEnt;
    struct stat Stat;
    std::vector<std::string> v_path;
    std::vector<std::string> v_path_stack; // Useing STACK in order NOT to exceed the limit of opendir() number.
    
    pDir = opendir(search_path.c_str());
    if(pDir==NULL){ return v_path; } // No files or directories.
    
    for(pEnt=readdir(pDir); pEnt!=0; pEnt=readdir(pDir)){
        // get file status
        std::string path = search_path + pEnt->d_name;
        if( stat( path.c_str(), &Stat ) ){
            sstd::pdbg("ERROR: glob_worker(): Failed to get stat %s\n", path.c_str());
            break;
        }
        if(!sstd::strmatch(path, wild_card)){ continue; }
        
        if (S_ISDIR(Stat.st_mode)){
            // when a directory
            if((strcmp( pEnt->d_name, "." )!=0) && (strcmp( pEnt->d_name, ".." )!=0)){
                // subdirectory
                // printf( "subdirectory: %s\n", pEnt->d_name );
                if(opt_d){
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
            if(opt_f){
                v_path.push_back( path );
            }
        }
    }
    closedir(pDir);

    if(opt_r){
        for(uint i=0; i<v_path_stack.size(); ++i){
            std::vector<std::string> v = _glob_worker(v_path_stack[i], wild_card, opt_d, opt_f, opt_r);
            v_path.insert(v_path.end(), v.begin(), v.end());
        }
    }

    return v_path;
}
std::vector<std::string> _glob_base(const char* path, const bool opt_d, const bool opt_f, const bool opt_r){
    std::string search_path = sstd::getPath(path);
    std::vector<std::string> v_path = _glob_worker(search_path.c_str(), path, opt_d, opt_f, opt_r);
    std::sort(v_path.begin(), v_path.end());
    return v_path;
}
std::vector<std::string> sstd::glob(const char* path, const char* opt){
    bool opt_d=false;
    bool opt_f=false;
    bool opt_r=false;
    for(uint i=0; opt[i]!='\0'; ++i){
        switch(opt[i]){
        case 'd': { opt_d=true; break; }
        case 'f': { opt_f=true; break; }
        case 'r': { opt_r=true; break; }
        default: { sstd::pdbg("ERROR: glob(): Unexpected option.\n"); break; }
        }
    }
    return _glob_base(path, opt_d, opt_f, opt_r);
}
std::vector<std::string> sstd::glob(const std::string& path, const char* opt){ return sstd::glob(path.c_str(), opt); }
std::vector<std::string> sstd::glob(const        char* path){ return sstd::glob(path, "f"); }
std::vector<std::string> sstd::glob(const std::string& path){ return sstd::glob(path.c_str(), "f"); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
/*

// old implimentation

std::vector<std::string> sstd::glob_f(const char* path){
#ifdef _WIN32    //windows環境の場合は「_WIN32」が定義されているので、こちら。

    HANDLE hFind;
    WIN32_FIND_DATA fd;
    std::vector<std::string> FileList;
    
    hFind = FindFirstFileEx(path, FindExInfoStandard, &fd, FindExSearchNameMatch, NULL, 0);
    if(hFind==INVALID_HANDLE_VALUE){ return FileList; } // No files or directories.
    
    do{
        if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){ // WIN32_FIND_DATA構造体のdwFileAttributesとFILE_ATTRIBUTE_DIRECTORYのビットの論理積を取り、ファイルかディレクトリかを判断している

            // directory found
            if((strcmp( fd.cFileName, "." )!=0) && (strcmp( fd.cFileName, ".." )!=0)){
                // subdirectory (サブディレクトリ)
//                printf( "subdirectory: %s\n", fd.cFileName );
            }else{
                //  . current directory (カレントディレクトリ)
                // .. parent directory (親ディレクトリ)
//                printf( "current or parent directory: %s\n", fd.cFileName );
            }
        }else{

            // file found
            std::string buf = sstd::getPath(path) + std::string( fd.cFileName );
            FileList.push_back(buf.c_str());
//            FileList.push_back(fd.cFileName);
//            printf("file: %s\n", FileList.back().c_str());
        }
    }while(FindNextFile(hFind, &fd));

    FindClose(hFind);

    return FileList;

#else            //Linux環境の場合は、「_WIN32」が定義されていないので、こちら。

    DIR *pDir;
    struct dirent *pEnt;
    struct stat Stat;
    std::string PathName;
    std::vector<std::string> FileList;

    std::string DirPath = sstd::getPath(path);

    // ディレクトリを開く
    pDir = opendir(DirPath.c_str());
    if(pDir==NULL){ return FileList; } // No files or directories.

    for(pEnt=readdir(pDir); pEnt!=0; pEnt=readdir(pDir)){

        // ファイルの情報を取得
        PathName = DirPath + pEnt->d_name;
        if( stat( PathName.c_str(), &Stat ) ){
            printf( "ERROR: Failed to get stat %s\n", PathName.c_str() );
            break;
        }

        if (S_ISDIR(Stat.st_mode)){

            // directory found
            if((strcmp( pEnt->d_name, "." )!=0) && (strcmp( pEnt->d_name, ".." )!=0)){
                // subdirectory (サブディレクトリ)
//                   printf( "subdirectory: %s\n", pEnt->d_name );
            }else{
                //  . current directory (カレントディレクトリ)
                // .. parent directory (親ディレクトリ)
//                   printf( "current or parent directory: %s\n", pEnt->d_name );
            }
        }else{
            if(sstd::strmatch( pEnt->d_name, sstd::getFileName(path))){
                // マッチした場合に true を返します。
                FileList.push_back( PathName );
            }
        }
    }

    // ハンドルを閉じる
    closedir(pDir);

    std::sort(FileList.begin(), FileList.end());//昇順ソート
    return FileList;
#endif
}
std::vector<std::string> sstd::glob_f(const std::string& path){
    return sstd::glob_f(path.c_str());
}

*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
