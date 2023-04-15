#pragma once
#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>
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
        
        template <typename T>
        void _void_ptr_obj(T* ptr);
        
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

        void_ptr_obj(std::unordered_map<std::string, std::string>* ptr);
        
        ~void_ptr_obj();

        template <typename T>
        void _overwrite(T* ptr);
        
        void overwrite(       bool* ptr);
        void overwrite(       char* ptr);
        void overwrite(      int8 * ptr);
        void overwrite(      int16* ptr);
        void overwrite(      int32* ptr);
        void overwrite(      int64* ptr);
        void overwrite(     uint8 * ptr);
        void overwrite(     uint16* ptr);
        void overwrite(     uint32* ptr);
        void overwrite(     uint64* ptr);
        void overwrite(      float* ptr);
        void overwrite(     double* ptr);
        void overwrite(std::string* ptr);
        
        void overwrite(std::vector<       bool>* ptr);
        void overwrite(std::vector<       char>* ptr);
        void overwrite(std::vector<      int8 >* ptr);
        void overwrite(std::vector<      int16>* ptr);
        void overwrite(std::vector<      int32>* ptr);
        void overwrite(std::vector<      int64>* ptr);
        void overwrite(std::vector<     uint8 >* ptr);
        void overwrite(std::vector<     uint16>* ptr);
        void overwrite(std::vector<     uint32>* ptr);
        void overwrite(std::vector<     uint64>* ptr);
        void overwrite(std::vector<      float>* ptr);
        void overwrite(std::vector<     double>* ptr);
        void overwrite(std::vector<std::string>* ptr);

        void overwrite(std::unordered_map<std::string, std::string>* ptr);
        
        void copy(class void_ptr_obj& rhs, const class void_ptr_obj& lhs);
        void free(class void_ptr_obj& rhs);
        void move(class void_ptr_obj& rhs, class void_ptr_obj&& lhs);
        void* ptr() const;
        uint typeNum() const;
        
        class void_ptr_obj& operator=(const class void_ptr_obj& rhs);
    };
}
