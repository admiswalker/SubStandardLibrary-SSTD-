#pragma once
#include <string>
#include <vector>
#include "void_ptr.hpp"
#include "../definitions/typeDef.h"
#include "../definitions/typeNum.hpp"
#include "../print/pdbg.hpp"

#include "../print/print.hpp" // for debug

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define _P (*_p) // pointer object

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd::terp{
    class list; // allocate type
    class hash; // allocate type
    
    class var; // base type
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

class sstd::terp::list{
private:
    uint _allocate_size;
public:
    list(): _allocate_size(0) {}
    list(uint allocate_size){ _allocate_size=allocate_size; }
    ~list(){}

    uint allocate_size() const { return _allocate_size; }
};

//-----------------------------------------------------------------------------------------------------------------------------------------------

class sstd::terp::hash{
private:
    uint _allocate_size;
public:
    hash(): _allocate_size(0) {}
    hash(uint allocate_size){ _allocate_size=allocate_size; }
    ~hash(){}

    uint allocate_size() const { return _allocate_size; }
};

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd::terp{
    std::vector<sstd::void_ptr>* cast_vec_void_ptr(void* rhs){ return (std::vector<sstd::void_ptr>*)rhs; }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

class sstd::terp::var{
private:
    sstd::void_ptr  _vp;
    sstd::void_ptr* _p;
    
public:
    var(){ _p = &_vp; }
    var(sstd::void_ptr* p_in){ _p = p_in; }
//    var(const char* rhs){
//        _p = &_vp;
//        _vp.overwrite(new std::string(rhs));
//    }
//    var(const sstd::terp::list& rhs){
//        _p = &_vp;
//        _vp.overwrite(new std::vector<sstd::void_ptr>());
//    }
    ~var(){}
    
    //---
    
    var operator=(const char* rhs){
//        printf("in ope=char*\n");
        (*_p).overwrite(new std::string(rhs));
        return *this;
    }
    var operator=(const sstd::terp::list& rhs){
//        printf("in ope=list\n");
        (*_p).overwrite(new std::vector<sstd::void_ptr>(rhs.allocate_size()));
        return *this;
    }
    var operator=(const sstd::terp::hash& rhs){
//        printf("in ope=list\n");
//        (*_p).overwrite(new std::unordered_map<std::string, sstd::void_ptr>(rhs.allocate_size()));
        return *this;
    }
    
    var operator[](int idx){
//        printf("in ope[], int\n");
        switch(_P.typeNum()){
        case sstd::num_vec_void_ptr: { sstd::void_ptr* p=(sstd::void_ptr*)&(*cast_vec_void_ptr(_P.ptr()))[idx]; return var( p ); } break;
        default: { sstd::pdbg("ERROR"); } break;
        }
        return var();
    }
    var operator[](char* pKey){ return var(); }
    
    //---
    
    sstd::void_ptr* ptr(){ return _p; }

    //---

    void push_back(const char* pRhs){
        switch(_P.typeNum()){
        case sstd::num_vec_void_ptr: { (*cast_vec_void_ptr(_P.ptr())).push_back(new std::string(pRhs)); } break;
        default: { sstd::pdbg("ERROR"); } break;
        }
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
        case sstd::num_vec_void_ptr: {
            return (*cast_vec_void_ptr(_P.ptr())).size();
        } break;
        default: { sstd::pdbg("ERROR"); } break;
        }
        return 0;
    }

    //---
    
    void _to(std::string& dst, const sstd::void_ptr& src) const { dst = (*(std::string*)_p->ptr()); }

    template <typename T>
    const T to() const {
        T ret = T();
        _to(ret, *_p);
        return ret;
    }

    //---
};

//-----------------------------------------------------------------------------------------------------------------------------------------------
