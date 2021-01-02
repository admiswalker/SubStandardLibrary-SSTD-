#pragma once

#include "../typeDef.h"
#include <vector>
#include <string>


namespace sstd{
    std::vector<uint8>       readAll_bin(const char*        pReadFile); // read all of the file as a binary
    std::vector<uint8>       readAll_bin(const std::string&  readFile); // read all of the file as a binary
    
    bool                     writeAll_bin(const char*        pWritePath, std::vector<uint8>& rhs);
    bool                     writeAll_bin(const std::string&  writePath, std::vector<uint8>& rhs);
    
    size_t                   write(const        char* path, const void* ptr, const size_t type_size, const size_t num); // (1)
    size_t                   write(const std::string& path, const void* ptr, const size_t type_size, const size_t num); // (2)
    size_t                   write(const        char* path, const std::string& s);                                      // (3)
    size_t                   write(const std::string& path, const        char* s);                                      // (4)
    size_t                   write(const std::string& path, const std::string& s);                                      // (5)
    
    std::string              readAll(const char*        pReadFile); // readAll_str()
    std::string              readAll(const std::string&  readFile); // readAll_str()
    std::string              readAll_withoutBOM(const char*        pReadFile);
    std::string              readAll_withoutBOM(const std::string&  readFile);
    std::vector<std::string> splitByLine(const std::string& str);
}
