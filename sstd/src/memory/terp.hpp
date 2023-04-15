#pragma once
#include <string>
#include <vector>
#include "../definitions/typeDef.h"
#include "void_ptr_obj.hpp"


namespace sstd::terp{
    class var{
    private:
        sstd::void_ptr_obj  _vp;
        sstd::void_ptr_obj* _p;
        
    public:
        var(){}
        ~var(){}

        var operator=(const char* rhs){
            _vp = sstd::void_ptr_obj(new std::string(rhs));
            return var();
        }

        var operator[](uint idx){ return var(); }
        var operator[](char* pKey){ return var(); }

        void _to(std::string& dst, const sstd::void_ptr_obj& src) const { dst = (*(std::string*)_vp.ptr()); }

        template <typename T>
        const T to() const {
            T ret = T();
            _to(ret, _vp);
            return ret;
        }
    };
}

