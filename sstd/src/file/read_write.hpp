#pragma once

#include "../typeDef.h"
#include <vector>
#include <string>


namespace sstd{
    std::vector<uint8> read_bin(const char*        path); // read all of the file as a binary
    std::vector<uint8> read_bin(const std::string& path); // read all of the file as a binary
    
    bool write_bin(const char*        path, std::vector<uint8>& rhs);
    bool write_bin(const std::string& path, std::vector<uint8>& rhs);
    
    std::string read(const char*        path);
    std::string read(const std::string& path);
    std::string read_withoutBOM(const char*        path);
    std::string read_withoutBOM(const std::string& path);
    
    size_t write(const        char* path, const void* ptr, const size_t type_size, const size_t num); // (1)
    size_t write(const std::string& path, const void* ptr, const size_t type_size, const size_t num); // (2)
    size_t write(const        char* path, const std::string& s);                                      // (3)
    size_t write(const std::string& path, const        char* s);                                      // (4)
    size_t write(const std::string& path, const std::string& s);                                      // (5)
}
