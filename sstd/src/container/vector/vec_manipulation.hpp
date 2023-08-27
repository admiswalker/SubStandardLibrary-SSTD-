#pragma once

#include "../../definitions/typeDef.h"
#include <vector>

namespace sstd{
    //-----------------------------------------------------------------------------------------------------------------------------------------------
    
    template<typename T> std::vector<T> rmEmpty   (const std::vector<T>& vec); // remove empty elements
    template<typename T> void           rmEmpty_ow(      std::vector<T>& vec); // remove empty elements overwrite
    
    //---

    template<typename T> std::vector<T> rmEmpty_l   (const std::vector<T>& vec); // remove empty elements from left side
    template<typename T> void           rmEmpty_l_ow(      std::vector<T>& vec); // remove empty elements from left side overwrite
    
    //---
    
    template<typename T> std::vector<T> rmEmpty_r   (const std::vector<T>& vec); // remove empty elements from right side
    template<typename T> void           rmEmpty_r_ow(      std::vector<T>& vec); // remove empty elements from right side overwrite
    
    //---
    // rmEmpty_ow(arg1, arg2, ...) of multiple vector arguments
    
    template<typename T>                      inline void _rmEmpty_ow(const std::vector<bool>& v, std::vector<T>& head);
    template<typename Head, typename... Tail> inline void _rmEmpty_ow(const std::vector<bool>& v, Head&& head, Tail&&... tail);
    template<typename Head, typename... Tail> inline void rmEmpty_ow(Head&& head, Tail&&... tail);
    
    //-----------------------------------------------------------------------------------------------------------------------------------------------

    template<typename T> uint cntEmpty  (const std::vector<T>& vec); // count empty elements
    template<typename T> uint cntEmpty_l(const std::vector<T>& vec); // count empty elements from left side
    template<typename T> uint cntEmpty_r(const std::vector<T>& vec); // count empty elements from right side
    
    //-----------------------------------------------------------------------------------------------------------------------------------------------
}

//-----------------------------------------------------------------------------------------------------------------------------------------------


template<typename T>
std::vector<T> sstd::rmEmpty(const std::vector<T>& vec){
    std::vector<T> ret_vec;
    for(uint i=0; i<vec.size(); ++i){
        if(vec[i].size()==0){ continue; }
        ret_vec.push_back(vec[i]);
    }
    return ret_vec;
}

template<typename T>
void sstd::rmEmpty_ow(std::vector<T>& vec){
    uint i_ret=0;
    for(uint i=0; i<vec.size(); ++i){
        if(vec[i].size()==0){ continue; }
        std::swap(vec[i_ret], vec[i]); ++i_ret;
    }
    vec.resize(i_ret);
}

//---

template<typename T>
std::vector<T> sstd::rmEmpty_l(const std::vector<T>& vec){
    uint i=0;
    for(; i<vec.size(); ++i){
        if(vec[i].size()!=0){ break; }
    }
    if(i>=vec.size()){ return std::vector<T>(); }
        
    return std::vector<T>(vec.begin()+i, vec.end());
}
template<typename T>
void sstd::rmEmpty_l_ow(std::vector<T>& vec){
    uint i=0;
    for(; i<vec.size(); ++i){
        if(vec[i].size()==0){ continue; }else{ break; }
    }
        
    uint i_ret=0;
    for(; i<vec.size(); ++i){
        std::swap(vec[i_ret], vec[i]); ++i_ret;
    }
    vec.resize(i_ret);
}

//---

template<typename T>
std::vector<T> sstd::rmEmpty_r(const std::vector<T>& vec){
    int i=vec.size()-1;
    for(; i>=0; --i){
        if(vec[i].size()!=0){ break; }
    }
    if(i<0){ return std::vector<T>(); }
        
    return std::vector<T>(vec.begin(), vec.begin()+i+1);
}
template<typename T>
void sstd::rmEmpty_r_ow(std::vector<T>& vec){
    int i=vec.size()-1;
    for(; i>=0; --i){
        if(vec[i].size()!=0){ break; }
        vec.pop_back();
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
inline void sstd::_rmEmpty_ow(const std::vector<bool>& v, std::vector<T>& head){
    uint i_ret=0;
    for(uint i=0; i<v.size() && i<head.size(); ++i){
        if(v[i]==false){ continue; }
        std::swap(head[i_ret], head[i]); ++i_ret;
    }
    head.resize(i_ret);
}
template<typename Head, typename... Tail>
inline void sstd::_rmEmpty_ow(const std::vector<bool>& v, Head&& head, Tail&&... tail){
    sstd::_rmEmpty_ow(v, std::forward<Head>(head));
    sstd::_rmEmpty_ow(v, std::forward<Tail>(tail)...);
}
template<typename Head, typename... Tail>
inline void sstd::rmEmpty_ow(Head&& head, Tail&&... tail){
    std::vector<bool> v(head.size(), true);
    for(uint i=0; i<head.size(); ++i){ if(head[i].size()==0){v[i]=false;} }
        
    sstd::_rmEmpty_ow(v, std::forward<Head>(head));
    sstd::_rmEmpty_ow(v, std::forward<Tail>(tail)...);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

template<typename T> uint sstd::cntEmpty  (const std::vector<T>& vec){
    uint cnt=0;
    for(uint i=0; i<vec.size(); ++i){
        if(vec[i].size()!=0){ continue; }
        ++cnt;
    }
    return cnt;
}
template<typename T> uint sstd::cntEmpty_l(const std::vector<T>& vec){
    uint cnt=0;
    for(uint i=0; i<vec.size(); ++i){
        if(vec[i].size()!=0){ break; }
        ++cnt;
    }
    return cnt;
}
template<typename T> uint sstd::cntEmpty_r(const std::vector<T>& vec){
    uint cnt=0;
    for(int i=vec.size()-1; i>=0; ++i){
        if(vec[i].size()!=0){ break; }
        ++cnt;
    }
    return cnt;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
