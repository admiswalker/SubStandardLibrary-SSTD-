#pragma once
#include <cstddef>
#include "definitions/typeDef.h"


namespace sstd{
    
    class unique_void_ptr{
    private:
        uint typeNum;
        void* pData;
    public:
        unique_void_ptr();
        unique_void_ptr(bool* ptr);
        unique_void_ptr(int* ptr);
        ~unique_void_ptr();
    };
    
    //void_obj void(){ return void_obj(); };

}
