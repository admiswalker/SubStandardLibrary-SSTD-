#pragma once
#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>
#include "../definitions/typeDef.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
    class void_ptr;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

class sstd::void_ptr{
private:
    uint typeNumber;
    void* pData;
public:
    void_ptr(); // default constructor
    void_ptr(const class void_ptr&  rhs); // copy constructor
    void_ptr(      class void_ptr&& rhs); // move constructor
        
    template <typename T>
    void _void_ptr(T* ptr);
        
    void_ptr(          bool* ptr);
    void_ptr(          char* ptr);
    void_ptr(         int8 * ptr);
    void_ptr(         int16* ptr);
    void_ptr(         int32* ptr);
    void_ptr(         int64* ptr);
    void_ptr(        uint8 * ptr);
    void_ptr(        uint16* ptr);
    void_ptr(        uint32* ptr);
    void_ptr(        uint64* ptr);
    void_ptr(         float* ptr);
    void_ptr(        double* ptr);
    void_ptr(   std::string* ptr);
    void_ptr(sstd::void_ptr* ptr);
        
    void_ptr(std::vector<          bool>* ptr);
    void_ptr(std::vector<          char>* ptr);
    void_ptr(std::vector<         int8 >* ptr);
    void_ptr(std::vector<         int16>* ptr);
    void_ptr(std::vector<         int32>* ptr);
    void_ptr(std::vector<         int64>* ptr);
    void_ptr(std::vector<        uint8 >* ptr);
    void_ptr(std::vector<        uint16>* ptr);
    void_ptr(std::vector<        uint32>* ptr);
    void_ptr(std::vector<        uint64>* ptr);
    void_ptr(std::vector<         float>* ptr);
    void_ptr(std::vector<        double>* ptr);
    void_ptr(std::vector<   std::string>* ptr);
    void_ptr(std::vector<sstd::void_ptr>* ptr);

    void_ptr(std::unordered_map<std::string,       std::string>* ptr);
    void_ptr(std::unordered_map<std::string,    sstd::void_ptr>* ptr);
//    void_ptr(std::unordered_map<sstd::void_ptr, sstd::void_ptr>* ptr);
    
    ~void_ptr();

    template <typename T>
    void _overwrite(T* ptr);
        
    void overwrite(          bool* ptr);
    void overwrite(          char* ptr);
    void overwrite(         int8 * ptr);
    void overwrite(         int16* ptr);
    void overwrite(         int32* ptr);
    void overwrite(         int64* ptr);
    void overwrite(        uint8 * ptr);
    void overwrite(        uint16* ptr);
    void overwrite(        uint32* ptr);
    void overwrite(        uint64* ptr);
    void overwrite(         float* ptr);
    void overwrite(        double* ptr);
    void overwrite(   std::string* ptr);
    void overwrite(sstd::void_ptr* ptr);
        
    void overwrite(std::vector<          bool>* ptr);
    void overwrite(std::vector<          char>* ptr);
    void overwrite(std::vector<         int8 >* ptr);
    void overwrite(std::vector<         int16>* ptr);
    void overwrite(std::vector<         int32>* ptr);
    void overwrite(std::vector<         int64>* ptr);
    void overwrite(std::vector<        uint8 >* ptr);
    void overwrite(std::vector<        uint16>* ptr);
    void overwrite(std::vector<        uint32>* ptr);
    void overwrite(std::vector<        uint64>* ptr);
    void overwrite(std::vector<         float>* ptr);
    void overwrite(std::vector<        double>* ptr);
    void overwrite(std::vector<   std::string>* ptr);
    void overwrite(std::vector<sstd::void_ptr>* ptr);

    void overwrite(std::unordered_map<std::string,       std::string>* ptr);
    void overwrite(std::unordered_map<std::string,    sstd::void_ptr>* ptr);
//    void overwrite(std::unordered_map<sstd::void_ptr, sstd::void_ptr>* ptr);
    
    void copy(class void_ptr& lhs, const class void_ptr& rhs);
    void free(class void_ptr& rhs);
    void move(class void_ptr& lhs, class void_ptr&& rhs);
    void* ptr() const;
    uint typeNum() const;
        
    class void_ptr& operator=(const class void_ptr& rhs);
};

//-----------------------------------------------------------------------------------------------------------------------------------------------
