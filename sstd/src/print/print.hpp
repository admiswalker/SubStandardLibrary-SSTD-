#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "../definitions/typeDef.h"
#include "../file/glob.hpp"
#include "../memory/terp/print.hpp"


namespace sstd{
    // forward declaration
    template <typename T> std::string to_string(const std::vector<T>& rhs);
    template <typename T> std::string to_string(const std::unordered_set<T>& rhs);
    template <typename T_lhs, typename T_rhs> std::string to_string(const std::unordered_map<T_lhs, T_rhs>& rhs);
    template <typename... Types> std::string to_string(const std::tuple<Types...>& rhs);

    //---
    // to_string()
    
    std::string to_string(const  void* rhs);
    std::string to_string(const  bool  rhs);
    std::string to_string(const  char  rhs);
    std::string to_string(const  int8  rhs);
    std::string to_string(const  int16 rhs);
    std::string to_string(const  int32 rhs);
    std::string to_string(const  int64 rhs);
    std::string to_string(const uint8  rhs);
    std::string to_string(const uint16 rhs);
    std::string to_string(const uint32 rhs);
    std::string to_string(const uint64 rhs);
    std::string to_string(const float  rhs);
    std::string to_string(const double rhs);
    std::string to_string(const        char* rhs);
    std::string to_string(const std::string& rhs);
    std::string to_string(const struct pathAndType& rhs);
    template <typename T>
    std::string to_string(const std::vector<T>& rhs){
        std::string s;
        s+="[";
        if(rhs.size()>=1){
            for(uint i=0; i<rhs.size()-1; ++i){ s+=sstd::to_string(rhs[i])+" "; }
            s+=sstd::to_string( rhs[rhs.size()-1] );
        }
        s+="]";
        return s;
    }
    template <typename T>
    std::string to_string(const std::unordered_set<T>& rhs){
        std::string s;
        s+="{";
        for(auto itr=rhs.begin();;){
            s+=sstd::to_string(*itr);
            ++itr;
            if(itr!=rhs.end()){ s+=", "; continue; }
            break;
        }
        s+="}";
        return s;
    }
    template <typename T_lhs, typename T_rhs>
    std::string to_string(const std::unordered_map<T_lhs, T_rhs>& rhs){
        std::string s;
        s+="{";
        for(auto itr=rhs.begin(); itr!=rhs.end(); ++itr){
            if(itr!=rhs.begin()){ s+=","; }
            s+=" (key: "+sstd::to_string(itr->first)+", value: "+sstd::to_string(itr->second)+")";
        }
        s+=" }";
        return s;
    }
    template<typename TupleT, size_t ID>
    void _tuple_to_str_internal(std::string& res_s, const TupleT& rhs, const size_t idx){
        if(idx!=0){ res_s+=", "; }
        res_s+=sstd::to_string( std::get<ID>(rhs) );
    }
    template<typename TupleT, size_t... IDs>
    void _tuple_to_str_internal_base(std::string& res_s, const TupleT& rhs, std::index_sequence<IDs...>){
        (..., ( _tuple_to_str_internal<TupleT,IDs>(res_s, rhs, IDs) ));
    }
    template<typename... Types>
    std::string to_string(const std::tuple<Types...>& rhs){
        std::string s;
        s+="(";
        sstd::_tuple_to_str_internal_base(s, rhs, std::make_index_sequence<sizeof...(Types)>());
        s+=")";
        return s;
    }

    //---
    // print()
    
    template <typename T>
    void print(const T& rhs){
        std::cout << sstd::to_string(rhs) + "\n";
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

#define print_all(var) printn_dummy();{printf("%s(%d): ", __func__, __LINE__);sstd::print(var);}
