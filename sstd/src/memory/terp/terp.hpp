#pragma once
#include <string>
#include <vector>

#include "../void_ptr.hpp"
#include "../../definitions/typeDef.h"
#include "../../definitions/typeNum.hpp"
#include "../../print/pdbg.hpp"
#include "../../print/print.hpp" // for debug

//-----------------------------------------------------------------------------------------------------------------------------------------------
// forward declaration

namespace sstd::terp{
    // var
    class var;

    // iterator
    class iterator;

    // list
    var list(uint allocate_size);
    var list();

    // hash
    var hash(uint allocate_size);
    var hash();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for internal use

namespace sstd::terp{
    // iterator
    using _v_iterator = typename std::vector<sstd::void_ptr>::const_iterator;
    using _h_iterator = typename std::unordered_map<std::string,sstd::void_ptr>::const_iterator;

    // to (data type conversion)
//    void _to(      bool & dst, const sstd::void_ptr& src);
    
    void _to(      char & dst, const sstd::void_ptr& src);
    void _to(     int8  & dst, const sstd::void_ptr& src);
    void _to(     int16 & dst, const sstd::void_ptr& src);
    void _to(     int32 & dst, const sstd::void_ptr& src);
    void _to(     int64 & dst, const sstd::void_ptr& src);
    void _to(    uint8  & dst, const sstd::void_ptr& src);
    void _to(    uint16 & dst, const sstd::void_ptr& src);
    void _to(    uint32 & dst, const sstd::void_ptr& src);
    void _to(    uint64 & dst, const sstd::void_ptr& src);
    void _to(    float & dst, const sstd::void_ptr& src);
    void _to(    double & dst, const sstd::void_ptr& src);
    void _to(const char*& dst, const sstd::void_ptr& src);
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
    iterator();
    iterator(const _v_iterator& rhs);
    iterator(const _h_iterator& rhs);
    ~iterator();

    //---
    
    const _v_iterator& _v_itr_R() const;
    const _h_iterator& _h_itr_R() const;

    //---
    
    iterator operator+(const int rhs);
    
    //---

    template <typename T>
    T first_to() const {
        T ret = T();
        switch(_typeNum){
        case sstd::num_vec_void_ptr:      { sstd::terp::_to(ret, (sstd::void_ptr)(*_v_itr)      ); return ret; } break;
        case sstd::num_hash_str_void_ptr: { sstd::terp::_to(ret, (std::string   )(*_h_itr).first); return ret; } break;
        default: { sstd::pdbg_err("ERROR\n"); }
        }
        return ret;
    }
    
    template <typename T>
    T second_to() const {
        T ret = T();
        switch(_typeNum){
        case sstd::num_hash_str_void_ptr: { sstd::terp::_to(ret, (sstd::void_ptr)(*_h_itr).second); return ret; } break;
        default: { sstd::pdbg_err("ERROR\n"); }
        }
        return ret;
    }
    sstd::terp::var second();
    
    //---
    
    const bool operator!=(const iterator& rhs) const;
    class iterator operator++();

    //---
};

//-----------------------------------------------------------------------------------------------------------------------------------------------

class sstd::terp::var{
private:
    sstd::void_ptr  _vp;
    sstd::void_ptr* _p;
    
public:
    var();
    var(const var&  rhs);
    var(const sstd::void_ptr& vp_in);
    var(      sstd::void_ptr*  p_in);
    var(const char         rhs);
    var(const  int8        rhs);
    var(const  int16       rhs);
    var(const  int32       rhs);
    var(const  int64       rhs);
    var(const uint8        rhs);
    var(const uint16       rhs);
    var(const uint32       rhs);
    var(const uint64       rhs);
    var(const  float       rhs);
    var(const double       rhs);
    var(const char*        rhs);
    var(const std::string& rhs);
    ~var();
    
    //---
    
    var operator=(const char* rhs);
    var operator=(const sstd::terp::var& rhs);

    //---
    
    bool operator==(const sstd::terp::var& rhs);
    bool operator!=(const sstd::terp::var& rhs);

    //---

          var operator[](const int idx);
    const var operator[](const int idx) const;
          var operator[](const char* pKey);
    const var operator[](const char* pKey) const;
    
    //---
    
    sstd::terp::iterator begin() const;
    sstd::terp::iterator end  () const;
    
    //---
    
    uint bucket_count();

    //---
    
    sstd::terp::iterator erase(const sstd::terp::iterator& rhs);
    uint erase(const char* pKey);
    
    //---
    
    sstd::terp::iterator find(const char* pKey) const;
    
    //---
    
    sstd::void_ptr* p() const;
    
    //---

    void pop_back();

    //---

    void push_back(const char* pRhs);
    void push_back(const sstd::terp::var& rhs);
    
    //---
    
    void resize(uint len);
    
    //---

    uint size() const;

    //---
    
//    void _to(std::string& dst, const sstd::void_ptr& src) const { dst = (*(std::string*)_p->ptr()); }

    template <typename T>
    const T to() const {
        T ret = T();
        sstd::terp::_to(ret, *_p);
        return ret;
    }
    
    //---

    uint typeNum() const;
    std::string typeStr() const;

    //---
};

//-----------------------------------------------------------------------------------------------------------------------------------------------
