#pragma once
#include <string>
#include <vector>
#include "../definitions/typeDef.h"
#include "void_ptr.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd::terp{
    class list;
    
    class var;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

class sstd::terp::list{
private:
public:
    list(){}
    ~list(){}
};

//-----------------------------------------------------------------------------------------------------------------------------------------------

class sstd::terp::var{
private:
    sstd::void_ptr  _vp;
    sstd::void_ptr* _p;
    
public:
    var(){ _p = &_vp; }
    var(const sstd::terp::list& rhs){
        _p = &_vp;
        //_vp.overwrite(std::vector<>);
    }
    ~var(){}
    
    //---
    
//    var operator=(const sstd::terp::list& rhs){
//        _vp;
//        return var();
//    }
    
    //---
    
    var operator=(const char* rhs){
        *_p = sstd::void_ptr(new std::string(rhs));
        return var();
    }

    var operator[](uint idx){ return var(); }
    var operator[](char* pKey){ return var(); }

    void _to(std::string& dst, const sstd::void_ptr& src) const { dst = (*(std::string*)_p->ptr()); }

    template <typename T>
    const T to() const {
        T ret = T();
        _to(ret, _vp);
        return ret;
    }
};

//-----------------------------------------------------------------------------------------------------------------------------------------------
