#include "file.hpp"
#include <stdarg.h>

//--------------------------------------------------------------------------------------------------------

sstd::file::file(){
    fp=NULL;
    type=0; // 0: fopen(), 1: popen().
}
sstd::file::~file(){
    close();
}

//---

#ifdef _WIN32
    inline bool sstd_file_fopen_win32(FILE** fp, const char*& fileName, const char*& mode){
        return (fopen_s(fp, fileName, mode)==NULL);
    }
#else
    inline bool sstd_file_fopen_linux(FILE** fp, const char*& fileName, const char*& mode){
        *fp = fopen(fileName, mode);
        return (*fp!=NULL);
    }
#endif
bool sstd::file::fopen(const char* fileName, const char* mode){
    #ifdef _WIN32
        return sstd_file_fopen_win32(&this->fp, fileName, mode);
    #else
        return sstd_file_fopen_linux(&this->fp, fileName, mode);
    #endif
}
bool sstd::file::fopen(const std::string& fileName, const char* mode){
    type = 0;
    return sstd::file::fopen(fileName.c_str(), mode);
}

//---

bool sstd::file::popen(const char* fileName, const char* mode){
    type = 1;
    this->fp = ::popen(fileName, mode);
    return this->fp!=NULL;
}
bool sstd::file::popen(const std::string& fileName, const char* mode){ return sstd::file::popen(fileName.c_str(), mode); }

//---

bool sstd::file::close(){
    if(fp==NULL){ return false; }
    
    switch(type){
    case 0: ::fclose(fp); return fp!=NULL;
    case 1: ::pclose(fp); return fp!=NULL;
    default: return false;
    }
}

//---

char* sstd::file::fgets(char* s, int size){ return ::fgets(s, size, this->fp); }
size_t sstd::file::fread(void* ptr, const size_t& size, const size_t& nmemb){ return ::fread(ptr, size, nmemb, this->fp); }
int sstd::file::fseek(const long& offset, const int& whence){ return ::fseek(this->fp, offset, whence); }
size_t sstd::file::fsize(){
    size_t size_buf = ::ftell(fp);   // ファイルポインタの位置を記録しておく
    ::fseek(fp, 0, SEEK_END);        // ファイルポインタをファイルの最後に移動させる
    size_t size = ::ftell(fp);       // ファイルサイズを取得する        // fgetpos(fp, &size);
    ::fseek(fp, size_buf, SEEK_SET); // ファイルポインタを元の位置に戻す
    return size;
}
long sstd::file::ftell(){ return ::ftell(this->fp); }
size_t sstd::file::fwrite(const void* ptr, const size_t& size, const size_t& nmemb){ return ::fwrite(ptr, size, nmemb, this->fp); }

//--------------------------------------------------------------------------------------------------------
