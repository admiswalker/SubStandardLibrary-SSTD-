#pragma once
#include <string>
#include <vector>
#include "./typeDef.h"


namespace sstd{
    // woLF: without line feed code ('\n')
    void print_woLF_new(const  bool  rhs);
    void print_woLF_new(const  char  rhs);
    void print_woLF_new(const  int8  rhs);
    void print_woLF_new(const  int16 rhs);
    void print_woLF_new(const  int32 rhs);
    void print_woLF_new(const  int64 rhs);
    void print_woLF_new(const uint8  rhs);
    void print_woLF_new(const uint16 rhs);
    void print_woLF_new(const uint32 rhs);
    void print_woLF_new(const uint64 rhs);
    void print_woLF_new(const float  rhs);
    void print_woLF_new(const double  rhs); // Note: Prioritize readability and do not display all effective digits of double-precision type.
    void print_woLF_new(const        char* rhs);
    void print_woLF_new(const std::string& rhs);
    template <typename T>
    void print_woLF_new(const std::vector<T>& rhs){
        printf("[");
        if(rhs.size()>=1){
            for(uint i=0; i<rhs.size()-1; ++i){ sstd::print_woLF_new(rhs[i]); printf(" "); }
            sstd::print_woLF_new( rhs[rhs.size()-1] );
        }
        printf("]");
    }
    
    // with line feed code ('\n')
    void print_new(const  bool  rhs);
    void print_new(const  char  rhs);
    void print_new(const  int8  rhs);
    void print_new(const  int16 rhs);
    void print_new(const  int32 rhs);
    void print_new(const  int64 rhs);
    void print_new(const uint8  rhs);
    void print_new(const uint16 rhs);
    void print_new(const uint32 rhs);
    void print_new(const uint64 rhs);
    void print_new(const float  rhs);
    void print_new(const double rhs);
    void print_new(const        char* rhs);
    void print_new(const std::string& rhs);
    template <typename T>
    void print_new(const std::vector<T>& rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
    
    void for_printn_new( bool  rhs);
    void for_printn_new( char  rhs);
    void for_printn_new( int8  rhs);
    void for_printn_new( int16 rhs);
    void for_printn_new( int32 rhs);
    void for_printn_new( int64 rhs);
    void for_printn_new(uint8  rhs);
    void for_printn_new(uint16 rhs);
    void for_printn_new(uint32 rhs);
    void for_printn_new(uint64 rhs);
    void for_printn_new( float rhs);
    void for_printn_new(double rhs);
    void for_printn_new(const        char* rhs);
    void for_printn_new(const std::string& rhs);
    template <typename T>
    void for_printn_new(const std::vector<T>& rhs){
        printf(" = ");
        sstd::print_woLF_new(rhs); // using "without line feed" version for recursive call for deep std::vector<std::vector<... std::vector<T>... >>.
        printf("\n");
    }

    //---
    
    // for #define
    inline void printn_dummy_new(){}
    inline void printn_new(...){}
//    inline void printn_all(...){}
}

#define printn_new(var) printn_dummy_new();{printf("%s", #var);sstd::for_printn_new(var);}
//#define printn_all(var) printn_dummy();{printf("%s(%d): %s", __func__, __LINE__, #var);sstd::for_printn_new(var);}
//#define printn_fflv(var) printn_dummy();{printf("%s: %s(%d): %s", __FILE__, __func__, __LINE__, #var);sstd::for_printn_new(var);}

