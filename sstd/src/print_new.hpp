#pragma once
#include <string>
#include <vector>
#include "./typeDef.h"
#include "./ssprintf.hpp" // for dev
#include "./strmatch.hpp" // for dev


namespace sstd{
    // woLF: without line feed code ('\n')
    void print_woLF_new(const  bool  rhs){ printf("%c", (rhs ? 'T' : 'F')); }
    void print_woLF_new(const  char  rhs){ printf("'%c'", rhs); }
    void print_woLF_new(const  int8  rhs){ printf("%d", rhs); }
    void print_woLF_new(const  int16 rhs){ printf("%d", rhs); }
    void print_woLF_new(const  int32 rhs){ printf("%d", rhs); }
    void print_woLF_new(const  int64 rhs){ printf("%ld", rhs); }
    void print_woLF_new(const uint8  rhs){ printf("%u", rhs); }
    void print_woLF_new(const uint16 rhs){ printf("%u", rhs); }
    void print_woLF_new(const uint32 rhs){ printf("%u", rhs); }
    void print_woLF_new(const uint64 rhs){ printf("%lu", rhs); }
    void print_woLF_new(const float  rhs){
        std::string s = sstd::ssprintf("%g", rhs);
        if(! sstd::charIn('.', s) ){ s += '.'; }
        printf("%s", s.c_str());
    }
    void print_woLF_new(const double  rhs){
        std::string s = sstd::ssprintf("%g", rhs); // Note: Prioritize readability and do not display all effective digits of double-precision type.
        if(! sstd::charIn('.', s) ){ s += '.'; }
        printf("%s", s.c_str());
    }
    void print_woLF_new(const        char* rhs){ printf("%s", rhs); }
    void print_woLF_new(const std::string& rhs){ printf("%s", rhs.c_str()); }
    template <typename T> void print_woLF_new(const std::vector<T>& rhs);
    
    // with line feed code ('\n')
    void print_new(const  bool  rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
    void print_new(const  char  rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
    void print_new(const  int8  rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
    void print_new(const  int16 rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
    void print_new(const  int32 rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
    void print_new(const  int64 rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
    void print_new(const uint8  rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
    void print_new(const uint16 rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
    void print_new(const uint32 rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
    void print_new(const uint64 rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
    void print_new(const float  rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
    void print_new(const double rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
    void print_new(const        char* rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
    void print_new(const std::string& rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
    
    void for_printn_new( bool  rhs){ printf(" = "); sstd::print_new(rhs); }
    void for_printn_new( char  rhs){ printf(" = "); sstd::print_new(rhs); }
    void for_printn_new( int8  rhs){ printf(" = "); sstd::print_new(rhs); }
    void for_printn_new( int16 rhs){ printf(" = "); sstd::print_new(rhs); }
    void for_printn_new( int32 rhs){ printf(" = "); sstd::print_new(rhs); }
    void for_printn_new( int64 rhs){ printf(" = "); sstd::print_new(rhs); }
    void for_printn_new(uint8  rhs){ printf(" = "); sstd::print_new(rhs); }
    void for_printn_new(uint16 rhs){ printf(" = "); sstd::print_new(rhs); }
    void for_printn_new(uint32 rhs){ printf(" = "); sstd::print_new(rhs); }
    void for_printn_new(uint64 rhs){ printf(" = "); sstd::print_new(rhs); }
    void for_printn_new( float rhs){ printf(" = "); sstd::print_new(rhs); }
    void for_printn_new(double rhs){ printf(" = "); sstd::print_new(rhs); }
    void for_printn_new(const        char* rhs){ printf(" = "); sstd::print_new(rhs); }
    void for_printn_new(const std::string& rhs){ printf(" = "); sstd::print_new(rhs); }
    
    template <typename T> void for_printn_new(const std::vector<T>& rhs);
    
    /*
    void for_printn_new(const std::vector<bool>& rhs);
    void for_printn_new(const std::vector<char>& rhs);  // 文字として表示 for_printnf("%c", rhs[i]);
    void for_printn_new(const std::vector<int8>& rhs);
    void for_printn_new(const std::vector<int16>& rhs);
    void for_printn_new(const std::vector<int32>& rhs);
    void for_printn_new(const std::vector<int64>& rhs);
    void for_printn_new(const std::vector<uint8>& rhs);
    void for_printn_new(const std::vector<uint16>& rhs);
    void for_printn_new(const std::vector<uint32>& rhs);
    void for_printn_new(const std::vector<uint64>& rhs);
    void for_printn_new(const std::vector<float>& rhs);
    void for_printn_new(const std::vector<double>& rhs);
    void for_printn_new(const std::vector<std::string>& rhs);
    
    void for_printn_new(const std::vector<std::vector<bool>>& rhs);
    void for_printn_new(const std::vector<std::vector<char>>& rhs);  // 文字として表示 for_printnf("%c", rhs[i]);
    void for_printn_new(const std::vector<std::vector<int8>>& rhs);
    void for_printn_new(const std::vector<std::vector<int16>>& rhs);
    void for_printn_new(const std::vector<std::vector<int32>>& rhs);
    void for_printn_new(const std::vector<std::vector<int64>>& rhs);
    void for_printn_new(const std::vector<std::vector<uint8>>& rhs);
    void for_printn_new(const std::vector<std::vector<uint16>>& rhs);
    void for_printn_new(const std::vector<std::vector<uint32>>& rhs);
    void for_printn_new(const std::vector<std::vector<uint64>>& rhs);
    void for_printn_new(const std::vector<std::vector<float>>& rhs);
    void for_printn_new(const std::vector<std::vector<double>>& rhs);
    void for_printn_new(const std::vector<std::vector<std::string>>& rhs);
    */
}

//====================================================================================================
//====================================================================================================

template <typename T> void sstd::print_woLF_new(const std::vector<T>& rhs){
    printf("[");
    if(rhs.size()>=1){
        for(uint i=0; i<rhs.size()-1; ++i){ sstd::print_woLF_new(rhs[i]); printf(" "); }
        sstd::print_woLF_new( rhs[rhs.size()-1] );
    }
    printf("]");
}
template <typename T> void sstd::for_printn_new(const std::vector<T>& rhs){
    printf(" = ");
    sstd::print_woLF_new(rhs);
    printf("\n");
}

namespace sstd{
    inline void printn_dummy_new(){}
    
    inline void printn_new(...){}
//    inline void printn_all(...){}
}

#define printn_new(var) printn_dummy_new();{printf("%s", #var);sstd::for_printn_new(var);}
//#define printn_all(var) printn_dummy();{printf("%s(%d): %s", __func__, __LINE__, #var);sstd::for_printn_new(var);}
//#define printn_fflv(var) printn_dummy();{printf("%s: %s(%d): %s", __FILE__, __func__, __LINE__, #var);sstd::for_printn_new(var);}

