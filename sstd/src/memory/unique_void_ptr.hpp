#pragma once
#include <string>
#include <vector>
#include <cstddef>
#include "../definitions/typeDef.h"


namespace sstd{
    
    class unique_void_ptr{
    private:
        uint typeNumber;
        void* pData;
    public:
        unique_void_ptr();
        
        unique_void_ptr(       bool* ptr);
        unique_void_ptr(       char* ptr);
        unique_void_ptr(      int8 * ptr);
        unique_void_ptr(      int16* ptr);
        unique_void_ptr(      int32* ptr);
        unique_void_ptr(      int64* ptr);
        unique_void_ptr(     uint8 * ptr);
        unique_void_ptr(     uint16* ptr);
        unique_void_ptr(     uint32* ptr);
        unique_void_ptr(     uint64* ptr);
        unique_void_ptr(      float* ptr);
        unique_void_ptr(     double* ptr);
        unique_void_ptr(std::string* ptr);
        
        unique_void_ptr(std::vector<       bool>* ptr);
        unique_void_ptr(std::vector<       char>* ptr);
        unique_void_ptr(std::vector<      int8 >* ptr);
        unique_void_ptr(std::vector<      int16>* ptr);
        unique_void_ptr(std::vector<      int32>* ptr);
        unique_void_ptr(std::vector<      int64>* ptr);
        unique_void_ptr(std::vector<     uint8 >* ptr);
        unique_void_ptr(std::vector<     uint16>* ptr);
        unique_void_ptr(std::vector<     uint32>* ptr);
        unique_void_ptr(std::vector<     uint64>* ptr);
        unique_void_ptr(std::vector<      float>* ptr);
        unique_void_ptr(std::vector<     double>* ptr);
        unique_void_ptr(std::vector<std::string>* ptr);
        
        ~unique_void_ptr();

        uint typeNum();
        void* ptr();
    };
}
