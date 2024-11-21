#pragma once
#include <string>
#include <vector>
#include <unordered_set>

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

    // iterator
    class iterator;

    // hash
    var hash(uint allocate_size);
    var hash();

    // list
    var list(uint allocate_size);
    var list();

    // type check
    bool isHash (const sstd::terp::var& rhs);
    bool isList (const sstd::terp::var& rhs);
    bool isNull (const sstd::terp::var& rhs);
    bool isValue(const sstd::terp::var& rhs);

    // type name
    using srcr_tbl = std::unordered_map<sstd::terp::var*,std::unordered_set<sstd::terp::var*>>;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for internal use

namespace sstd::terp{
    // to (data type conversion)
    void _to(      bool & dst, const sstd::terp::var& src);
    void _to(      char & dst, const sstd::terp::var& src);
    void _to(     int8  & dst, const sstd::terp::var& src);
    void _to(     int16 & dst, const sstd::terp::var& src);
    void _to(     int32 & dst, const sstd::terp::var& src);
    void _to(     int64 & dst, const sstd::terp::var& src);
    void _to(    uint8  & dst, const sstd::terp::var& src);
    void _to(    uint16 & dst, const sstd::terp::var& src);
    void _to(    uint32 & dst, const sstd::terp::var& src);
    void _to(    uint64 & dst, const sstd::terp::var& src);
    void _to(     float & dst, const sstd::terp::var& src);
    void _to(    double & dst, const sstd::terp::var& src);
    void _to(const char*& dst, const sstd::terp::var& src);
    void _to(std::string& dst, const sstd::terp::var& src);
    void _to(std::string& dst, const std::string   & src);

    bool equal(const sstd::terp::var& lhs, const sstd::terp::var& rhs);
    bool equal(const sstd::terp::var& lhs, const sstd::terp::var& rhs, const char* opt);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

class sstd::terp::var{
private:
    uint _type;
    bool _is_reference;
    bool _is_pSRCR_tbl_base;
    sstd::terp::srcr_tbl* _pSRCR_tbl; // Self-reference and Cross-reference Table
    void* _p;
    
public:
    var();
    var(const class var&  rhs);
    var(      class var&& rhs);
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
    var(const sstd::terp::srcr_tbl* rhs); // for internal use of sstd::terp::var
    ~var();
    
    //---
    // internal

    uint type() const;
    bool is_reference() const;
    bool is_pSRCR_tbl_base() const;
    sstd::terp::srcr_tbl* pSRCR_tbl() const;
    void* p() const;
    
    uint & type_RW();
    bool & is_reference_RW();
    bool & is_pSRCR_tbl_base_RW();
    sstd::terp::srcr_tbl*& pSRCR_tbl_RW();
    void*& p_RW();
    
    //---
    // common

    //void _fill_ref_src_null(sstd::terp::var* rhs);
    void _fill_ref_src_null(const std::unordered_set<sstd::terp::var*>& hash_set);
    void _fillout_ref_src_null();

    void copy(const class sstd::terp::var&  rhs);
    void move(      class sstd::terp::var&& rhs);
    void fill_dependent_ref_null();
    void free_SRCR_tbl();
    void free_val();
    void free();
    
    template <typename T>
    void _overwrite(T* ptr);
    
    var& operator=(const sstd::terp::var&  rhs);
    var  operator=(      sstd::terp::var&& rhs);
    
    var& operator=(const char* rhs);
    var& operator=(const  var* rhs); // for the reference of var address. // Note: sstd::terp did NOT mention the trouble with circular reference.

    bool equal(const sstd::terp::var& rhs) const;
    bool equal(const sstd::terp::var& rhs, const char* opt) const; // "r" (checks reference flag), "a" (checks reference address) for opt
    bool operator==(const sstd::terp::var& rhs);
    bool operator!=(const sstd::terp::var& rhs);

          var& operator[](const int idx);
    const var& operator[](const int idx) const;
          var& operator[](const       char* pKey);
    const var& operator[](const       char* pKey) const;
          var& operator[](const std::string  key);
    const var& operator[](const std::string  key) const;
    
    sstd::terp::iterator begin() const;
    sstd::terp::iterator end  () const;
    
    uint size() const;

//    void _to(std::string& dst, const sstd::void_ptr& src) const { dst = (*(std::string*)_p->ptr()); }
    template <typename T>
    const T to() const {
        T ret = T();
        if(this->_p==NULL){ sstd::pdbg_err("NULL pointer is detected\n"); return ret; }
        sstd::terp::_to(ret, *this);
        return ret;
    }
    
    uint typeNum() const;
    std::string typeStr() const;
    
    //---
    // for hash type
    
    uint bucket_count();
    
    sstd::terp::iterator erase(const sstd::terp::iterator& rhs);
    uint erase(const char* pKey);
    
    sstd::terp::iterator find(const       char* pKey) const;
    sstd::terp::iterator find(const std::string  key) const;
    
    //---
    // for list type

//    void list(uint allocate_size);
//    void list();

    void pop_back();

    void push_back(); // push_back null
    void push_back(const char* pRhs);
    void push_back(const sstd::terp::var&  rhs);
    void push_back(      sstd::terp::var&& rhs);
    
    void resize(uint len);
};

//-----------------------------------------------------------------------------------------------------------------------------------------------
// iterator

namespace sstd::terp{
    // iterator
    using _v_iterator = typename std::vector<sstd::terp::var*>::const_iterator;
    using _h_iterator = typename std::unordered_map<std::string,sstd::terp::var*>::const_iterator;
}

//---

class sstd::terp::iterator{
private:
    uint _type;
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
        switch(this->_type){
        case sstd::num_vec_terp_var:  { sstd::terp::_to(ret, *(sstd::terp::var*)(*_v_itr)      ); return ret; } break;
        case sstd::num_hash_terp_var: { sstd::terp::_to(ret,  (std::string     )(*_h_itr).first); return ret; } break;
        default: { sstd::pdbg_err("ERROR\n"); }
        }
        return ret;
    }
    
    template <typename T>
    T second_to() const {
        T ret = T();
        switch(this->_type){
        case sstd::num_hash_terp_var: { sstd::terp::_to(ret, *(sstd::terp::var*)(*_h_itr).second); return ret; } break;
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
