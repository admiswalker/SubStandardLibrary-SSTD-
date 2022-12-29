#pragma once
#include <string>
#include <vector>
#include <cstddef>
#include "../definitions/typeDef.h"


namespace sstd{
    
    class void_ptr_obj{
    private:
        uint typeNumber;
        void* pData;
    public:
        void_ptr_obj(); // default constructor
        void_ptr_obj(const class void_ptr_obj&  rhs); // copy constructor
        void_ptr_obj(      class void_ptr_obj&& rhs); // move constructor
        
        void_ptr_obj(       bool* ptr);
        void_ptr_obj(       char* ptr);
        void_ptr_obj(      int8 * ptr);
        void_ptr_obj(      int16* ptr);
        void_ptr_obj(      int32* ptr);
        void_ptr_obj(      int64* ptr);
        void_ptr_obj(     uint8 * ptr);
        void_ptr_obj(     uint16* ptr);
        void_ptr_obj(     uint32* ptr);
        void_ptr_obj(     uint64* ptr);
        void_ptr_obj(      float* ptr);
        void_ptr_obj(     double* ptr);
        void_ptr_obj(std::string* ptr);
        
        void_ptr_obj(std::vector<       bool>* ptr);
        void_ptr_obj(std::vector<       char>* ptr);
        void_ptr_obj(std::vector<      int8 >* ptr);
        void_ptr_obj(std::vector<      int16>* ptr);
        void_ptr_obj(std::vector<      int32>* ptr);
        void_ptr_obj(std::vector<      int64>* ptr);
        void_ptr_obj(std::vector<     uint8 >* ptr);
        void_ptr_obj(std::vector<     uint16>* ptr);
        void_ptr_obj(std::vector<     uint32>* ptr);
        void_ptr_obj(std::vector<     uint64>* ptr);
        void_ptr_obj(std::vector<      float>* ptr);
        void_ptr_obj(std::vector<     double>* ptr);
        void_ptr_obj(std::vector<std::string>* ptr);
        
        ~void_ptr_obj();

        uint typeNum();
        void* ptr();
    };
}
