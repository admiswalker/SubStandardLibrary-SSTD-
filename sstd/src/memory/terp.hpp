#pragma once
#include <string>
#include <vector>
#include "void_ptr.hpp"
#include "../definitions/typeDef.h"
#include "../definitions/typeNum.hpp"
#include "../print/pdbg.hpp"

#include "../print/print.hpp" // for debug

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for user

namespace sstd::terp{
    // var
    class var;

    // iterator
    class iterator;
    using _v_iterator = typename std::vector<sstd::void_ptr>::const_iterator;
    using _h_iterator = typename std::unordered_map<std::string,sstd::void_ptr>::const_iterator;

    // list
    var list(uint allocate_size);
    var list();

    // hash
    var hash(uint allocate_size);
    var hash();
    
    // cast
//    std::vector<sstd::void_ptr>*                    cast_vec_void_ptr     (void* rhs);
//    std::unordered_map<std::string,sstd::void_ptr>* cast_hash_str_void_ptr(void* rhs);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for internal use

#define _P (*_p) // pointer object

namespace sstd::terp{
    // cast
    std::vector<sstd::void_ptr>*                    cast_vec_void_ptr     (void* rhs);
    std::unordered_map<std::string,sstd::void_ptr>* cast_hash_str_void_ptr(void* rhs);

    // to (data type conversion)
    void _to(std::string& dst, const sstd::void_ptr& src);
    void _to(std::string& dst, const std::string   & src);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// iterator

class sstd::terp::iterator{
private:
    uint _typeNum;
    _v_iterator _v_itr;
    _h_iterator _h_itr;
public:
    iterator(): _typeNum(sstd::num_null) {}
    iterator(const _v_iterator& rhs){ _typeNum=sstd::num_vec_void_ptr;      _v_itr=rhs; }
    iterator(const _h_iterator& rhs){ _typeNum=sstd::num_hash_str_void_ptr; _h_itr=rhs; }
    ~iterator(){}

    //---
    
    const _v_iterator& _v_itr_R() const { return _v_itr; }
    const _h_iterator& _h_itr_R() const { return _h_itr; }

    //---

    template <typename T>
    T first_to() const {
        T ret = T();
        switch(_typeNum){
        case sstd::num_vec_void_ptr:      { sstd::terp::_to(ret, (sstd::void_ptr)(*_v_itr)      ); return ret; } break;
        case sstd::num_hash_str_void_ptr: { sstd::terp::_to(ret, (std::string   )(*_h_itr).first); return ret; } break;
        default: { sstd::pdbg("ERROR"); }
        }
        return ret;
    }
    template <typename T>
    T second_to() const {
        T ret = T();
        switch(_typeNum){
        case sstd::num_hash_str_void_ptr: { sstd::terp::_to(ret, (sstd::void_ptr)(*_h_itr).second); return ret; } break;
        default: { sstd::pdbg("ERROR"); }
        }
        return ret;
    }

    //---
    
    const bool operator!=(const iterator& rhs) const {
        switch(_typeNum){
        case sstd::num_vec_void_ptr:      { return _v_itr != rhs._v_itr_R(); } break;
        case sstd::num_hash_str_void_ptr: { return _h_itr != rhs._h_itr_R(); } break;
        default: { sstd::pdbg("ERROR"); }
        }
        return false;
    }
    
    class iterator operator++(){
        switch(_typeNum){
        case sstd::num_vec_void_ptr:      { ++_v_itr; } break;
        case sstd::num_hash_str_void_ptr: { ++_h_itr; } break;
        default: { sstd::pdbg("ERROR"); }
        }
        return *this;
    }
};

//-----------------------------------------------------------------------------------------------------------------------------------------------

class sstd::terp::var{
private:
    sstd::void_ptr  _vp;
    sstd::void_ptr* _p;
    
public:
    var(){ _p = &_vp; }
    var(const var&  rhs){ _vp=*rhs.p(); _p=&_vp; }
//    var(const var&& rhs){ _vp=*rhs.p(); _p=&_vp; }
    var(sstd::void_ptr* p_in){ _p = p_in; }
    ~var(){}
    
    //---
    
    var operator=(const char* rhs){
        (*_p).overwrite(new std::string(rhs));
        return *this;
    }
    var operator=(const sstd::terp::var& rhs){
        *_p = *rhs.p();
        return *this;
    }

    //---
    
    var operator[](int idx){
        switch(_P.typeNum()){
        case sstd::num_vec_void_ptr: { sstd::void_ptr* p=(sstd::void_ptr*)&(*cast_vec_void_ptr(_P.ptr()))[idx]; return var( p ); } break;
        default: { sstd::pdbg("ERROR"); } break;
        }
        return var();
    }
    var operator[](const char* pKey){
        switch(_P.typeNum()){
        case sstd::num_hash_str_void_ptr: { sstd::void_ptr* p=(sstd::void_ptr*)&(*cast_hash_str_void_ptr(_P.ptr()))[pKey]; return var( p ); } break;
        default: { sstd::pdbg("ERROR"); } break;
        }
        return var();
    }
    
    //---
    
    const _v_iterator _v_begin(void* p_in) const {
        if(_p==NULL){ return _v_iterator(); }
        std::vector<sstd::void_ptr>* p = cast_vec_void_ptr(p_in);
        return (*p).begin();
    }
    const _v_iterator _v_end(void* p_in) const {
        if(_p==NULL){ return _v_iterator(); }
        std::vector<sstd::void_ptr>* p = cast_vec_void_ptr(p_in);
        return (*p).end();
    }
    const _h_iterator _h_begin(void* p_in) const {
        if(_p==NULL){ return _h_iterator(); }
        std::unordered_map<std::string,sstd::void_ptr>* p = cast_hash_str_void_ptr(p_in);
        return (*p).begin();
    }
    const _h_iterator _h_end(void* p_in) const {
        if(_p==NULL){ return _h_iterator(); }
        std::unordered_map<std::string,sstd::void_ptr>* p = cast_hash_str_void_ptr(p_in);
        return (*p).end();
    }
    sstd::terp::iterator begin(){
        switch((*_p).typeNum()){
        case sstd::num_vec_void_ptr:      { return sstd::terp::iterator(_v_begin((*_p).ptr())); } break;
        case sstd::num_hash_str_void_ptr: { return sstd::terp::iterator(_h_begin((*_p).ptr())); } break;
        case sstd::num_null:              {} break;
        default: { sstd::pdbg("ERROR"); }
        }
        return sstd::terp::iterator();
    }
    sstd::terp::iterator end(){
        switch((*_p).typeNum()){
        case sstd::num_vec_void_ptr:      { return sstd::terp::iterator(_v_end((*_p).ptr())); } break;
        case sstd::num_hash_str_void_ptr: { return sstd::terp::iterator(_h_end((*_p).ptr())); } break;
        case sstd::num_null:              {} break;
        default: { sstd::pdbg("ERROR"); }
        }
        return sstd::terp::iterator();
    }
    
    //---
    
    uint bucket_count(){
        switch(_P.typeNum()){
        case sstd::num_hash_str_void_ptr: { return (*cast_hash_str_void_ptr(_P.ptr())).bucket_count(); } break;
        default: { sstd::pdbg("ERROR"); } break;
        }
        return 0;
    }

    //---
    
    //sstd::void_ptr  vp() const { return *_p; }
    sstd::void_ptr* p () const { return _p;  }
    
    //---

    void push_back(const char* pRhs){
        if(_P.typeNum()!=sstd::num_vec_void_ptr){ sstd::pdbg("ERROR"); return; }
        (*cast_vec_void_ptr(_P.ptr())).push_back(new std::string(pRhs));
    }
    void push_back(const sstd::terp::var& rhs){
        if(_P.typeNum()!=sstd::num_vec_void_ptr){ sstd::pdbg("ERROR"); return; }
        (*cast_vec_void_ptr(_P.ptr())).push_back(*rhs.p());
    }
    
    //---
    
    void resize(uint len){
        switch(_P.typeNum()){
        case sstd::num_vec_void_ptr: { return (*cast_vec_void_ptr(_P.ptr())).resize( len ); } break;
        default: { sstd::pdbg("ERROR"); } break;
        }
    }
    
    //---

    uint size() const {
        switch(_P.typeNum()){
        case sstd::num_vec_void_ptr     : { return (*cast_vec_void_ptr(_P.ptr())).size();      } break;
        case sstd::num_hash_str_void_ptr: { return (*cast_hash_str_void_ptr(_P.ptr())).size(); } break;
        default: { sstd::pdbg("ERROR"); } break;
        }
        return 0;
    }

    //---
    
//    void _to(std::string& dst, const sstd::void_ptr& src) const { dst = (*(std::string*)_p->ptr()); }

    template <typename T>
    const T to() const {
        T ret = T();
        sstd::terp::_to(ret, *_p);
        return ret;
    }
    
    //---

    uint typeNum(){
        return _P.typeNum();
    }
    std::string typeStr(){
        return std::string();//sstd::type(_P.typeNum());
    }

    //---
};

//-----------------------------------------------------------------------------------------------------------------------------------------------

#undef _P

//-----------------------------------------------------------------------------------------------------------------------------------------------