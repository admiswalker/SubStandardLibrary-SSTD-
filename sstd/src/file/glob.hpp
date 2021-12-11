#pragma once

#include <vector>
#include <string>

namespace sstd{
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

    /*
    // Old implimentation

    // glob file
    std::vector<std::string> glob_f(const        char* path);
    std::vector<std::string> glob_f(const std::string& path);
    */
}


