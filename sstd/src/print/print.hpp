#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "../definitions/typeDef.h"
#include "../file/glob.hpp"
#include "../memory/terp/print.hpp"


namespace sstd{
    // forward declaration
    template <typename T> void print_base(const std::vector<T>& rhs);
    template <typename T> void print_base(const std::unordered_set<T>& rhs);
    template <typename T_lhs, typename T_rhs> void print_base(const std::unordered_map<T_lhs, T_rhs>& rhs);
    template <typename... Types> void print_base(const std::tuple<Types...>& rhs);

    //---
    // print_base()
    
    void print_base(const  void* rhs);
    void print_base(const  bool  rhs);
    void print_base(const  char  rhs);
    void print_base(const  int8  rhs);
    void print_base(const  int16 rhs);
    void print_base(const  int32 rhs);
    void print_base(const  int64 rhs);
    void print_base(const uint8  rhs);
    void print_base(const uint16 rhs);
    void print_base(const uint32 rhs);
    void print_base(const uint64 rhs);
    void print_base(const float  rhs);
    void print_base(const double rhs);
    void print_base(const        char* rhs);
    void print_base(const std::string& rhs);
    void print_base(const struct pathAndType& rhs);
    template <typename T>
    void print_base(const std::vector<T>& rhs){
        printf("[");
        if(rhs.size()>=1){
            for(uint i=0; i<rhs.size()-1; ++i){ sstd::print_base(rhs[i]); printf(" "); }
            sstd::print_base( rhs[rhs.size()-1] );
        }
        printf("]");
    }
    template <typename T>
    void print_base(const std::unordered_set<T>& rhs){
        printf("{");
        for(auto itr=rhs.begin();;){
            sstd::print_base(*itr);
            ++itr;
            if(itr!=rhs.end()){ printf(", "); continue; }
            break;
        }
        printf("}");
    }
    template <typename T_lhs, typename T_rhs>
    void print_base(const std::unordered_map<T_lhs, T_rhs>& rhs){
        printf("{");
        for(auto itr=rhs.begin(); itr!=rhs.end(); ++itr){
            if(itr!=rhs.begin()){ printf(","); }
            printf(" (key: "); sstd::print_base(itr->first);
            printf(", value: "); sstd::print_base(itr->second);
            printf(")");
        }
        printf(" }");
    }
    template<typename TupleT, size_t ID>
    void _print_tuple_base(const TupleT& rhs, const size_t idx){
        if(idx!=0){ printf(", "); }
        print_base( std::get<ID>(rhs) );
    }
    template<typename TupleT, size_t... IDs>
    void _print_tuple(const TupleT& rhs, std::index_sequence<IDs...>){
        (..., ( _print_tuple_base<TupleT,IDs>(rhs, IDs) ));
    }
    template<typename... Types>
    void print_base(const std::tuple<Types...>& rhs){
        printf("(");
        sstd::_print_tuple(rhs, std::make_index_sequence<sizeof...(Types)>());
        printf(")");
    }

    //---
    // print()
    
    template <typename T>
    void print(const T& rhs){
        print_base(rhs);
        printf("\n");
    }
    
    //---
    // for #define
    inline void printn_dummy(){}
    inline void printn(...){}
    inline void printn_all(...){}
    inline void printn_fflv(...){}
}

#define printn(var) printn_dummy();{printf("%s = ", #var);sstd::print(var);}
#define printn_all(var) printn_dummy();{printf("%s(%d): %s = ", __func__, __LINE__, #var);sstd::print(var);}
#define printn_fflv(var) printn_dummy();{printf("%s: %s(%d): %s = ", __FILE__, __func__, __LINE__, #var);sstd::print(var);}
