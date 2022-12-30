#pragma once

#include "../../definitions/typeDef.h"
#include <vector>

namespace sstd{
    template<typename T>
    std::vector<T> rmEmpty(const std::vector<T>& vec){
        std::vector<T> ret_vec;
        for(uint i=0; i<vec.size(); ++i){
            if(vec[i].size()==0){ continue; }
            ret_vec.push_back(vec[i]);
        }
        return ret_vec;
    }
    template<typename T>
    void rmEmpty_ow(std::vector<T>& vec){
        uint i_ret=0;
        for(uint i=0; i<vec.size(); ++i){
            if(vec[i].size()==0){ continue; }
            std::swap(vec[i_ret], vec[i]); ++i_ret;
        }
        vec.resize(i_ret);
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------
    // rmEmpty_ow(arg1, arg2, ...) of multiple vector arguments
    
    template<typename T>
    inline void _rmEmpty_ow(const std::vector<bool>& v, std::vector<T>& head){
        uint i_ret=0;
        for(uint i=0; i<v.size() && i<head.size(); ++i){
            if(v[i]==false){ continue; }
            std::swap(head[i_ret], head[i]); ++i_ret;
        }
        head.resize(i_ret);
    }
    template<typename Head, typename... Tail>
    inline void _rmEmpty_ow(const std::vector<bool>& v, Head&& head, Tail&&... tail){
        sstd::_rmEmpty_ow(v, std::forward<Head>(head));
        sstd::_rmEmpty_ow(v, std::forward<Tail>(tail)...);
    }
    template<typename Head, typename... Tail>
    inline void rmEmpty_ow(Head&& head, Tail&&... tail){ // Ascending: 昇順: 0, 1, 2, ...
        std::vector<bool> v(head.size(), true);
        for(uint i=0; i<head.size(); ++i){ if(head[i].size()==0){v[i]=false;} }
        
        sstd::_rmEmpty_ow(v, std::forward<Head>(head));
        sstd::_rmEmpty_ow(v, std::forward<Tail>(tail)...);
    }
    
    //-----------------------------------------------------------------------------------------------------------------------------------------------
}
