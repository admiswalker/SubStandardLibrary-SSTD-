#pragma once
#include <string>
#include <vector>

#include "../void_ptr.hpp"
#include "../../definitions/typeDef.h"
#include "../../definitions/typeNum.hpp"
#include "../../print/pdbg.hpp"
//#include "../../print/print.hpp" // for debug

//-----------------------------------------------------------------------------------------------------------------------------------------------
// forward declaration

namespace sstd::terp{
    // var
    class var;
    class var_v2;

    // iterator
    class iterator;
    class iterator_v2;

    // hash
    var hash(uint allocate_size);
    var hash();
    var_v2 hash_v2(uint allocate_size);
    var_v2 hash_v2();

    // list
    var list(uint allocate_size);
    var list();
    var_v2 list_v2(uint allocate_size);
    var_v2 list_v2();
    
//    void free(class sstd::terp::var_v2& lhs);
//    void copy(class sstd::terp::var_v2& lhs, const class sstd::terp::var_v2& rhs);

    // type check
    bool isHash (const sstd::terp::var& rhs);
    bool isList (const sstd::terp::var& rhs);
    bool isNull (const sstd::terp::var& rhs);
    bool isValue(const sstd::terp::var& rhs);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for internal use

namespace sstd::terp{
    // iterator
    using _v_iterator = typename std::vector<sstd::void_ptr>::const_iterator;
    using _h_iterator = typename std::unordered_map<std::string,sstd::void_ptr>::const_iterator;

    // to (data type conversion)
    void _to(      bool & dst, const sstd::void_ptr& src);
    void _to(      char & dst, const sstd::void_ptr& src);
    void _to(     int8  & dst, const sstd::void_ptr& src);
    void _to(     int16 & dst, const sstd::void_ptr& src);
    void _to(     int32 & dst, const sstd::void_ptr& src);
    void _to(     int64 & dst, const sstd::void_ptr& src);
    void _to(    uint8  & dst, const sstd::void_ptr& src);
    void _to(    uint16 & dst, const sstd::void_ptr& src);
    void _to(    uint32 & dst, const sstd::void_ptr& src);
    void _to(    uint64 & dst, const sstd::void_ptr& src);
    void _to(     float & dst, const sstd::void_ptr& src);
    void _to(    double & dst, const sstd::void_ptr& src);
    void _to(const char*& dst, const sstd::void_ptr& src);
    void _to(std::string& dst, const sstd::void_ptr& src);
    void _to(std::string& dst, const std::string   & src);
    
    void _to_v2(      bool & dst, const sstd::terp::var_v2& src);
    void _to_v2(      char & dst, const sstd::terp::var_v2& src);
    void _to_v2(     int8  & dst, const sstd::terp::var_v2& src);
    void _to_v2(     int16 & dst, const sstd::terp::var_v2& src);
    void _to_v2(     int32 & dst, const sstd::terp::var_v2& src);
    void _to_v2(     int64 & dst, const sstd::terp::var_v2& src);
    void _to_v2(    uint8  & dst, const sstd::terp::var_v2& src);
    void _to_v2(    uint16 & dst, const sstd::terp::var_v2& src);
    void _to_v2(    uint32 & dst, const sstd::terp::var_v2& src);
    void _to_v2(    uint64 & dst, const sstd::terp::var_v2& src);
    void _to_v2(     float & dst, const sstd::terp::var_v2& src);
    void _to_v2(    double & dst, const sstd::terp::var_v2& src);
    void _to_v2(const char*& dst, const sstd::terp::var_v2& src);
    void _to_v2(std::string& dst, const sstd::terp::var_v2& src);
    void _to_v2(std::string& dst, const std::string       & src);
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
    var(const bool         rhs);
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
    // internal
    
    sstd::void_ptr* p() const;
    
    //---
    // common
    
    var operator=(const char* rhs);
    var operator=(const sstd::terp::var& rhs);

    bool operator==(const sstd::terp::var& rhs);
    bool operator!=(const sstd::terp::var& rhs);

          var operator[](const int idx);
    const var operator[](const int idx) const;
          var operator[](const char* pKey);
    const var operator[](const char* pKey) const;
    
    sstd::terp::iterator begin() const;
    sstd::terp::iterator end  () const;
    
    uint size() const;

//    void _to(std::string& dst, const sstd::void_ptr& src) const { dst = (*(std::string*)_p->ptr()); }
    template <typename T>
    const T to() const {
        T ret = T();
        if(_p==NULL){ sstd::pdbg_err("NULL pointer is detected\n"); return ret; }
        sstd::terp::_to(ret, *_p);
        return ret;
    }
    
    uint typeNum() const;
    std::string typeStr() const;
    
    //---
    // for hash type
    
    uint bucket_count();
    
    sstd::terp::iterator erase(const sstd::terp::iterator& rhs);
    uint erase(const char* pKey);
    
    sstd::terp::iterator find(const char* pKey) const;
    
    //---
    // for list type

    void pop_back();

    void push_back(const char* pRhs);
    void push_back(const sstd::terp::var&  rhs);
    void push_back(      sstd::terp::var&& rhs);
    
    void resize(uint len);
};

//-----------------------------------------------------------------------------------------------------------------------------------------------

class sstd::terp::var_v2{
private:
    uint _type;
    void* _p;
    
public:
    var_v2();
    var_v2(const class var_v2&  rhs);
    var_v2(      class var_v2&& rhs);
    var_v2(const bool         rhs);
    //var_v2(const char         rhs);
    //var_v2(const  int8        rhs);
    //var_v2(const  int16       rhs);
    //var_v2(const  int32       rhs);
    //var_v2(const  int64       rhs);
    //var_v2(const uint8        rhs);
    //var_v2(const uint16       rhs);
    //var_v2(const uint32       rhs);
    //var_v2(const uint64       rhs);
    //var_v2(const  float       rhs);
    //var_v2(const double       rhs);
    var_v2(const char*        rhs);
    //var_v2(const std::string& rhs);
    ~var_v2();
    
    //---
    // internal
    
    void* p() const;
    uint type() const;
    
    void*& p_RW();
    uint & type_RW();
    
    //---
    // common

    void copy(const class sstd::terp::var_v2&  rhs);
    void move(      class sstd::terp::var_v2&& rhs);
    void free();
    
    template <typename T>
    void _overwrite(T* ptr);
    
    var_v2& operator=(const sstd::terp::var_v2& rhs);
    //var_v2 operator=(      sstd::terp::var_v2&& rhs);
    
    var_v2& operator=(const char* rhs);

    bool operator==(const sstd::terp::var_v2& rhs);
    bool operator!=(const sstd::terp::var_v2& rhs);

          var_v2& operator[](const int idx);
    const var_v2& operator[](const int idx) const;
          var_v2& operator[](const char* pKey);
    const var_v2& operator[](const char* pKey) const;
    
    sstd::terp::iterator_v2 begin() const;
    sstd::terp::iterator_v2 end  () const;
    
    uint size() const;

//    void _to(std::string& dst, const sstd::void_ptr& src) const { dst = (*(std::string*)_p->ptr()); }
    template <typename T>
    const T to() const {
        T ret = T();
        if(this->_p==NULL){ sstd::pdbg_err("NULL pointer is detected\n"); return ret; }
        sstd::terp::_to_v2(ret, *this);
        return ret;
    }
    
    uint typeNum() const;
    std::string typeStr() const;
    
    //---
    // for hash type
    
    uint bucket_count();
    
    sstd::terp::iterator_v2 erase(const sstd::terp::iterator_v2& rhs);
    uint erase(const char* pKey);
    
    sstd::terp::iterator_v2 find(const char* pKey) const;
    
    //---
    // for list type

//    void list_v2(uint allocate_size);
//    void list_v2();

    void pop_back();

    void push_back(const char* pRhs);
    void push_back(const sstd::terp::var_v2&  rhs);
    void push_back(      sstd::terp::var_v2&& rhs);
    
    void resize(uint len);
};

//-----------------------------------------------------------------------------------------------------------------------------------------------
// iterator_v2

namespace sstd::terp{
    // iterator
    using _v_iterator_v2 = typename std::vector<sstd::terp::var_v2>::const_iterator;
    using _h_iterator_v2 = typename std::unordered_map<std::string,sstd::terp::var_v2>::const_iterator;
}

//---

class sstd::terp::iterator_v2{
private:
    uint _type;
    _v_iterator_v2 _v_itr;
    _h_iterator_v2 _h_itr;
public:
    iterator_v2();
    iterator_v2(const _v_iterator_v2& rhs);
    iterator_v2(const _h_iterator_v2& rhs);
    ~iterator_v2();

    //---
    
    const _v_iterator_v2& _v_itr_R() const;
    const _h_iterator_v2& _h_itr_R() const;

    //---
    
    iterator_v2 operator+(const int rhs);
    
    //---

    template <typename T>
    T first_to() const {
        T ret = T();
        switch(this->_type){
        case sstd::num_vec_terp_var_v2:  { sstd::terp::_to_v2(ret, (sstd::terp::var_v2)(*_v_itr)      ); return ret; } break;
        case sstd::num_hash_terp_var_v2: { sstd::terp::_to_v2(ret, (std::string       )(*_h_itr).first); return ret; } break;
        default: { sstd::pdbg_err("ERROR\n"); }
        }
        return ret;
    }
    
    template <typename T>
    T second_to() const {
        T ret = T();
        switch(this->_type){
        case sstd::num_hash_terp_var_v2: { sstd::terp::_to_v2(ret, (sstd::terp::var_v2)(*_h_itr).second); return ret; } break;
        default: { sstd::pdbg_err("ERROR\n"); }
        }
        return ret;
    }
    sstd::terp::var_v2 second();
    
    //---
    
    const bool operator!=(const iterator_v2& rhs) const;
    class iterator_v2 operator++();

    //---
};

//-----------------------------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------------------------------
