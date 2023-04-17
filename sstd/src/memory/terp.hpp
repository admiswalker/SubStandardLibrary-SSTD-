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

    // list
    var list(uint allocate_size);
    var list();

    // hash
    var hash(uint allocate_size);
    var hash();
    
    // cast
    std::vector<sstd::void_ptr>*                    cast_vec_void_ptr     (void* rhs);
    std::unordered_map<std::string,sstd::void_ptr>* cast_hash_str_void_ptr(void* rhs);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for internal use

#define _P (*_p) // pointer object

namespace sstd::terp{
    // cast
    std::vector<sstd::void_ptr>*                    cast_vec_void_ptr     (void* rhs);
    std::unordered_map<std::string,sstd::void_ptr>* cast_hash_str_void_ptr(void* rhs);
}

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
    
    void _to(std::string& dst, const sstd::void_ptr& src) const { dst = (*(std::string*)_p->ptr()); }

    template <typename T>
    const T to() const {
        T ret = T();
        _to(ret, *_p);
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
