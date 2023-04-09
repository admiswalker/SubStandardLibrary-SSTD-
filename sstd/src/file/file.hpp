﻿#pragma once

#include <stdio.h>
#include <string>

//--------------------------------------------------------------------------------------------------------

namespace sstd{ class file; }
class sstd::file{
private:
    FILE* fp;
    int type; // 0: fopen(), 1: popen().
    
public:
    file();
    ~file();
    
    bool fopen(const        char* fileName, const char* mode);
    bool fopen(const std::string& fileName, const char* mode);
    bool popen(const        char* fileName, const char* mode);
    bool popen(const std::string& fileName, const char* mode);
    int close();
    
    char*  fgets (char* s, int size);
    size_t fread (void* ptr, const size_t& size, const size_t& nmemb);
    template <typename... Args>
    int    fscanf(const char* format, Args const&... args){ return ::fscanf(this->fp, format, args...); }
    int    fseek (const long& offset, const int& whence);
    size_t fsize();
    long   ftell();
    size_t fwrite(const void* ptr, const size_t& size, const size_t& nmemb);
};

//--------------------------------------------------------------------------------------------------------
