﻿#pragma once

#include <sys/stat.h>
#include <vector>
#include <string>

namespace sstd{
    struct pathAndType{
        char type; // 'f': file, 'd': directory
        struct stat st;
        std::string path;
        
        bool operator < (const struct pathAndType& rhs){
            return (*this).path < rhs.path;
        }
    };
    
    // Because of under construction, this function does not work exactly same as the usual glob function.
    
    // glob
    //   options:
    //     d: directory
    //     f: file
    //     r: recursive
    std::vector<std::string> glob(const        char* path, const char* opt);
    std::vector<std::string> glob(const std::string& path, const char* opt);
    std::vector<std::string> glob(const        char* path);
    std::vector<std::string> glob(const std::string& path);

    std::vector<struct pathAndType> glob_pt(const        char* path, const char* opt); // _pt: with path type
    std::vector<struct pathAndType> glob_pt(const std::string& path, const char* opt);
    std::vector<struct pathAndType> glob_pt(const        char* path);
    std::vector<struct pathAndType> glob_pt(const std::string& path);
}

