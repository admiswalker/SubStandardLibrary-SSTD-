#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "typeDef.h"
#include "file/glob.hpp"


namespace sstd{
    void print_for_vT(const  bool  rhs);
    void print_for_vT(const  char  rhs);
    void print_for_vT(const  int8  rhs);
    void print_for_vT(const  int16 rhs);
    void print_for_vT(const  int32 rhs);
    void print_for_vT(const  int64 rhs);
    void print_for_vT(const uint8  rhs);
    void print_for_vT(const uint16 rhs);
    void print_for_vT(const uint32 rhs);
    void print_for_vT(const uint64 rhs);
    void print_for_vT(const float  rhs);
    void print_for_vT(const double rhs);
    void print_for_vT(const        char* rhs);
    void print_for_vT(const std::string& rhs);
    void print_for_vT(const struct pathAndType& rhs);
    template <typename T>
    void print_for_vT(const std::vector<T>& rhs){
        printf("[");
        if(rhs.size()>=1){
            for(uint i=0; i<rhs.size()-1; ++i){ sstd::print_for_vT(rhs[i]); printf(" "); }
            sstd::print_for_vT( rhs[rhs.size()-1] );
        }
        printf("]");
    }
    
    void print(const  bool  rhs);
    void print(const  char  rhs);
    void print(const  int8  rhs);
    void print(const  int16 rhs);
    void print(const  int32 rhs);
    void print(const  int64 rhs);
    void print(const uint8  rhs);
    void print(const uint16 rhs);
    void print(const uint32 rhs);
    void print(const uint64 rhs);
    void print(const float  rhs);
    void print(const double rhs);
    void print(const        char* rhs);
    void print(const std::string& rhs);
    void print(const struct pathAndType& rhs);
    template <typename T>
    void print(const std::vector<T>& rhs){ sstd::print_for_vT(rhs); printf("\n"); }
    template <typename T_lhs, typename T_rhs>
    void print_table_base(const std::unordered_map<T_lhs, T_rhs>& rhs){
        printf("[");
        for(auto itr=rhs.begin(); itr!=rhs.end(); ++itr){
            if(itr!=rhs.begin()){ printf(","); }
            printf(" [key: "); sstd::print_for_vT(itr->first);
            printf(", value: "); sstd::print_for_vT(itr->second);
            printf("]");
        }
        printf(" ]");
    }
    template <typename T_lhs, typename T_rhs>
    void print(const std::unordered_map<T_lhs, T_rhs>& rhs){ sstd::print_table_base<T_lhs, T_rhs>(rhs); printf("\n"); }
    
    void for_printn( bool  rhs);
    void for_printn( char  rhs);
    void for_printn( int8  rhs);
    void for_printn( int16 rhs);
    void for_printn( int32 rhs);
    void for_printn( int64 rhs);
    void for_printn(uint8  rhs);
    void for_printn(uint16 rhs);
    void for_printn(uint32 rhs);
    void for_printn(uint64 rhs);
    void for_printn( float rhs);
    void for_printn(double rhs);
    void for_printn(const        char* rhs);
    void for_printn(const std::string& rhs);
    void for_printn(const struct pathAndType& rhs);
    template <typename T>
    void for_printn(const std::vector<T>& rhs){
        printf(" = ");
        sstd::print_for_vT(rhs); // using "without line feed" version for recursive call for deep std::vector<std::vector<... std::vector<T>... >>.
        printf("\n");
    }
    template <typename T_lhs, typename T_rhs>
    void for_printn(const std::unordered_map<T_lhs, T_rhs>& rhs){
        printf(" = ");
        sstd::print_table_base<T_lhs, T_rhs>(rhs); // using "without line feed" version for recursive call for deep std::vector<std::vector<... std::vector<T>... >>.
        printf("\n");
    }

    //---
    
    // for #define
    inline void printn_dummy(){}
    inline void printn(...){}
    inline void printn_all(...){}
}

#define printn(var) printn_dummy();{printf("%s", #var);sstd::for_printn(var);}
#define printn_all(var) printn_dummy();{printf("%s(%d): %s", __func__, __LINE__, #var);sstd::for_printn(var);}
#define printn_fflv(var) printn_dummy();{printf("%s: %s(%d): %s", __FILE__, __func__, __LINE__, #var);sstd::for_printn(var);}

