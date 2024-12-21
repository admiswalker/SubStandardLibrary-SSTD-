//#include <stdio.h>
//#include <string.h>
#include "terp.hpp"

#include "../../definitions/typeNum.hpp"
#include "../../print/pdbg.hpp"
#include "../../string/ssprintf.hpp"
#include "../../string/strmatch.hpp"

#include "../../print/print.hpp" // sstd::printn() for debugging at development

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define _CAST2VEC(_P) (*(std::vector<sstd::terp::var*>*)_P)
#define _CAST2HASH(_P) (*(std::unordered_map<std::string,sstd::terp::var*>*)_P)

void _free_val(sstd::terp::var* _pVar, void*& _p, sstd::terp::srcr_tbl* _pSRCR_tbl, const uint type, const bool _is_reference);

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for internal use

// cast
std::string*                                    _cast2str (void* rhs){ return (                std::string*)rhs; }
std::vector<sstd::void_ptr>*                    _cast2vec (void* rhs){ return (std::vector<sstd::void_ptr>*)rhs; }
std::unordered_map<std::string,sstd::void_ptr>* _cast2hash(void* rhs){ return (std::unordered_map<std::string,sstd::void_ptr>*)rhs; }

#define STR (*(std::string*)src.p())

void sstd::terp::_to(     bool  & dst, const sstd::terp::var& src){
    if(STR=="true"||STR=="yes"||STR=="on"){
        dst = true;
    }else if(STR=="false"||STR=="no"||STR=="off"){
        dst = false;
    }else{
        sstd::pdbg_err("input string is not bool type.\n");
    }
}
void sstd::terp::_to(     char  & dst, const sstd::terp::var& src){ dst = STR.size()>=1 ? STR[0] : 0; }
void sstd::terp::_to(     int8  & dst, const sstd::terp::var& src){ dst = strtol(STR.c_str(), NULL, 10); }
void sstd::terp::_to(     int16 & dst, const sstd::terp::var& src){ dst = strtol(STR.c_str(), NULL, 10); }
void sstd::terp::_to(     int32 & dst, const sstd::terp::var& src){ dst = strtol(STR.c_str(), NULL, 10); }
void sstd::terp::_to(     int64 & dst, const sstd::terp::var& src){ dst = strtoll(STR.c_str(), NULL, 10); }
void sstd::terp::_to(    uint8  & dst, const sstd::terp::var& src){ dst = strtoul(STR.c_str(), NULL, 10); }
void sstd::terp::_to(    uint16 & dst, const sstd::terp::var& src){ dst = strtoul(STR.c_str(), NULL, 10); }
void sstd::terp::_to(    uint32 & dst, const sstd::terp::var& src){ dst = strtoul(STR.c_str(), NULL, 10); }
void sstd::terp::_to(    uint64 & dst, const sstd::terp::var& src){ dst = strtoull(STR.c_str(), NULL, 10); }
void sstd::terp::_to(     float & dst, const sstd::terp::var& src){ dst = strtof(STR.c_str(), NULL); }
void sstd::terp::_to(    double & dst, const sstd::terp::var& src){ dst = strtod(STR.c_str(), NULL); }
void sstd::terp::_to(const char*& dst, const sstd::terp::var& src){ dst = STR.c_str(); }
void sstd::terp::_to(std::string& dst, const sstd::terp::var& src){ dst = STR; }
void sstd::terp::_to(std::string& dst, const std::string    & src){ dst = src; }
#undef STR

#define NULL_CHECK(p) if(p==NULL){ sstd::pdbg_err("NULL pointer is detected\n"); return; }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp

bool sstd::terp::equal(const sstd::terp::var& lhs, const sstd::terp::var& rhs){ // TODO: write interface tests
    return lhs.equal(rhs);
}
bool sstd::terp::equal(const sstd::terp::var& lhs, const sstd::terp::var& rhs, const char* opt){ // TODO: write interface tests
    return lhs.equal(rhs, opt);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::iterator

// constructors
sstd::terp::iterator::iterator(): _type(sstd::num_null) {}
sstd::terp::iterator::iterator(const _v_iterator& rhs){ this->_type=sstd::num_vec_terp_var;  _v_itr=rhs; } 
sstd::terp::iterator::iterator(const _h_iterator& rhs){ this->_type=sstd::num_hash_terp_var; _h_itr=rhs; }
sstd::terp::iterator::~iterator(){}

//---

const sstd::terp::_v_iterator& sstd::terp::iterator::_v_itr_R() const { return _v_itr; }
const sstd::terp::_h_iterator& sstd::terp::iterator::_h_itr_R() const { return _h_itr; }

//---

sstd::terp::iterator sstd::terp::iterator::operator+(const int rhs){
    switch(this->_type){
    case sstd::num_vec_terp_var:      { return iterator( _v_itr + rhs ); } break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return iterator();
}

//---

sstd::terp::var sstd::terp::iterator::second(){
    switch(this->_type){
    case sstd::num_hash_terp_var: {
        return sstd::terp::var(*(*_h_itr).second);
    } break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return sstd::terp::var();
}

//---

const bool sstd::terp::iterator::operator!=(const iterator& rhs) const {
    switch(this->_type){
    case sstd::num_vec_terp_var:  { return _v_itr != rhs._v_itr_R(); } break;
    case sstd::num_hash_terp_var: { return _h_itr != rhs._h_itr_R(); } break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return false;
}

sstd::terp::iterator sstd::terp::iterator::operator++(){
    switch(this->_type){
    case sstd::num_vec_terp_var:  { ++_v_itr; } break;
    case sstd::num_hash_terp_var: { ++_h_itr; } break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::hash

sstd::terp::var sstd::terp::hash(uint allocate_size){
    sstd::terp::var r;
    r.type_RW() = sstd::num_hash_terp_var;
    r.p_RW()    = new std::unordered_map<std::string,sstd::terp::var*>(allocate_size);
    return r;
}
sstd::terp::var sstd::terp::hash(){ return sstd::terp::hash(0); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::list

sstd::terp::var sstd::terp::list(uint allocate_size){
    sstd::terp::var r;
    r.type_RW() = num_vec_terp_var;
    r.p_RW()    = new std::vector<sstd::terp::var*>(allocate_size);
    
    for(uint i=0; i<allocate_size; ++i){
        _CAST2VEC(r.p_RW())[i] = new sstd::terp::var(r.pSRCR_tbl());
    }
    
    return r;
}
sstd::terp::var sstd::terp::list(){
    sstd::terp::var r;
    r.type_RW() = num_vec_terp_var;
    r.p_RW()    = new std::vector<sstd::terp::var*>();
    return r;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// type check

bool sstd::terp::isHash (const sstd::terp::var& rhs){
    return ( rhs.typeNum()==sstd::num_hash_str_void_ptr || rhs.typeNum()==sstd::num_hash_terp_var );
}
bool sstd::terp::isList (const sstd::terp::var& rhs){
    return rhs.typeNum()==sstd::num_vec_terp_var;
}
bool sstd::terp::isNull (const sstd::terp::var& rhs){
    return rhs.typeNum()==sstd::num_null;
}
bool sstd::terp::isValue(const sstd::terp::var& rhs){
    return rhs.typeNum()==sstd::num_str;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::var

uint _digits(double rhs){
    uint num=0;
    while((int)rhs!=0){
        rhs *= 0.1;
        ++num;
    }
    return num;
}
std::string _format(float rhs){
    uint digits=_digits(rhs);
    if(digits<=6){ return sstd::ssprintf("%%%u.%uf", digits, 15-digits);
    }    else    { return sstd::ssprintf("%%f"); }
}
std::string _format(double rhs){
    uint digits=_digits(rhs);
    if(digits<=15){ return sstd::ssprintf("%%%u.%ulf", digits, 15-digits);
    }    else     { return sstd::ssprintf("%%lf"); }
}

// constructors
sstd::terp::var::var():                       _type(sstd::num_null), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(NULL) {}
sstd::terp::var::var(const class var&   rhs): _type(sstd::num_null), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(NULL) { copy(rhs); }
sstd::terp::var::var(      class var&&  rhs): _type(sstd::num_null), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(NULL) { free(); move(std::move(rhs)); }
sstd::terp::var::var(const class var*  pRhs): _type(sstd::num_null), _is_reference(true ), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(NULL) { _type=pRhs->type(); _p=(void*)pRhs; }
sstd::terp::var::var(        bool       rhs): _type(sstd::num_null), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(new std::string(rhs?"true":"false")) {}
sstd::terp::var::var(        char       rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(new std::string({rhs})) {}
sstd::terp::var::var(        int8       rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(new std::string(sstd::ssprintf("%d", rhs))) {}
sstd::terp::var::var(        int16      rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(new std::string(sstd::ssprintf("%d", rhs))) {}
sstd::terp::var::var(        int32      rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(new std::string(sstd::ssprintf("%d", rhs))) {}
sstd::terp::var::var(        int64      rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(new std::string(sstd::ssprintf("%ld", rhs))) {}
sstd::terp::var::var(       uint8       rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(new std::string(sstd::ssprintf("%u", rhs))) {}
sstd::terp::var::var(       uint16      rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(new std::string(sstd::ssprintf("%u", rhs))) {}
sstd::terp::var::var(       uint32      rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(new std::string(sstd::ssprintf("%u", rhs))) {}
sstd::terp::var::var(       uint64      rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(new std::string(sstd::ssprintf("%lu", rhs))) {}
sstd::terp::var::var(        float      rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(new std::string(sstd::ssprintf(_format(rhs).c_str(), rhs))) {}
sstd::terp::var::var(       double      rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(new std::string(sstd::ssprintf(_format(rhs).c_str(), rhs))) {}
sstd::terp::var::var(const char*        rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(new std::string(rhs)) {}
sstd::terp::var::var(const std::string& rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new sstd::terp::srcr_tbl()), _p(new std::string(rhs)) {}
sstd::terp::var::var(const sstd::terp::srcr_tbl* rhs): _type(sstd::num_null), _is_reference(false), _is_pSRCR_tbl_base(false), _pSRCR_tbl((sstd::terp::srcr_tbl*)rhs), _p(NULL) {}

sstd::terp::var::~var(){ sstd::terp::var::free(); }

//---
// internal

uint sstd::terp::var::type() const { return this->_type; }
bool sstd::terp::var::is_reference() const { return this->_is_reference; }
bool sstd::terp::var::is_pSRCR_tbl_base() const { return this->_is_pSRCR_tbl_base; }
sstd::terp::srcr_tbl* sstd::terp::var::pSRCR_tbl() const { return this->_pSRCR_tbl; }
void* sstd::terp::var::p() const { return this->_p; }

uint & sstd::terp::var::type_RW(){ return this->_type; }
bool & sstd::terp::var::is_reference_RW(){ return this->_is_reference; }
bool & sstd::terp::var::is_pSRCR_tbl_base_RW(){ return this->_is_pSRCR_tbl_base; }
sstd::terp::srcr_tbl*& sstd::terp::var::pSRCR_tbl_RW(){ return this->_pSRCR_tbl; }
void*& sstd::terp::var::p_RW(){ return this->_p; }

//---
// common

// copy(), allocate(), free()

bool _is_internal_ref(const class sstd::terp::var* pVar){
    return pVar->is_reference() && ( pVar->pSRCR_tbl() == ((sstd::terp::var*)pVar->p())->pSRCR_tbl() );
}
bool _is_external_ref(const class sstd::terp::var* pVar){
    return pVar->is_reference() && ( pVar->pSRCR_tbl() != ((sstd::terp::var*)pVar->p())->pSRCR_tbl() );
}
bool _copy_value(
                 class sstd::terp::var* pLhs, const class sstd::terp::var* pRhs_in,
                        
                 std::vector<std::tuple<sstd::terp::var*,sstd::terp::var*,uint>>& vStack_copyDstAds_asRef_and_origRefAds,
                 std::unordered_map<sstd::terp::var*,sstd::terp::var*>& tbl_copySrcAds_to_copyDstAds,
                 const char opt_a, const char opt_i, const char opt_e
                 )
{ // TODO: これ，reference あるとかなり実装が面倒になるはず
    bool res=true;
    class sstd::terp::var* pRhs = (sstd::terp::var*)pRhs_in;
    
    bool copy_internal_ref_as_obj = _is_internal_ref(pRhs) && opt_i=='o';
    bool copy_external_ref_as_obj = _is_external_ref(pRhs) && opt_e=='o';
    bool copy_ref_as_obj = copy_internal_ref_as_obj || copy_external_ref_as_obj;
    sstd::printn_all(copy_ref_as_obj);
    sstd::printn_all(pRhs->is_reference());
    sstd::printn_all(!copy_ref_as_obj && pRhs->is_reference());
    if(!copy_ref_as_obj && pRhs->is_reference()){
        vStack_copyDstAds_asRef_and_origRefAds.push_back( std::make_tuple((sstd::terp::var*)pLhs, (sstd::terp::var*)pRhs->p(), pRhs->type()) );
        return res;
    }else{
        pRhs = (!pRhs->is_reference()) ? pRhs : (sstd::terp::var*)pRhs->p();
    }
    
    //---
    
    pLhs->type_RW() = pRhs->type();
    if(pRhs->p()==NULL){ pLhs->p_RW()=NULL; }
    switch (pRhs->type()){
    case sstd::num_null    : {} break;
        
    case sstd::num_bool    : { pLhs->p_RW() = new           bool(*(         bool *)pRhs->p()); } break;
    case sstd::num_char    : { pLhs->p_RW() = new           char(*(         char *)pRhs->p()); } break;
    case sstd::num_int8    : { pLhs->p_RW() = new          int8 (*(         int8 *)pRhs->p()); } break;
    case sstd::num_int16   : { pLhs->p_RW() = new          int16(*(         int16*)pRhs->p()); } break;
    case sstd::num_int32   : { pLhs->p_RW() = new          int32(*(         int32*)pRhs->p()); } break;
    case sstd::num_int64   : { pLhs->p_RW() = new          int64(*(         int64*)pRhs->p()); } break;
    case sstd::num_uint8   : { pLhs->p_RW() = new         uint8 (*(        uint8 *)pRhs->p()); } break;
    case sstd::num_uint16  : { pLhs->p_RW() = new         uint16(*(        uint16*)pRhs->p()); } break;
    case sstd::num_uint32  : { pLhs->p_RW() = new         uint32(*(        uint32*)pRhs->p()); } break;
    case sstd::num_uint64  : { pLhs->p_RW() = new         uint64(*(        uint64*)pRhs->p()); } break;
    case sstd::num_float   : { pLhs->p_RW() = new          float(*(         float*)pRhs->p()); } break;
    case sstd::num_double  : { pLhs->p_RW() = new         double(*(        double*)pRhs->p()); } break;
    case sstd::num_str     : { pLhs->p_RW() = new    std::string(*(   std::string*)pRhs->p()); } break;
//    case sstd::num_void_ptr: { pLhs->_p = new sstd::void_ptr(*(sstd::void_ptr*)pRhs->p()); } break;
        
    case sstd::num_vec_bool    : { pLhs->p_RW() = new std::vector<          bool>(*(std::vector<          bool>*)pRhs->p()); } break;
    case sstd::num_vec_char    : { pLhs->p_RW() = new std::vector<          char>(*(std::vector<          char>*)pRhs->p()); } break;
    case sstd::num_vec_int8    : { pLhs->p_RW() = new std::vector<         int8 >(*(std::vector<         int8 >*)pRhs->p()); } break;
    case sstd::num_vec_int16   : { pLhs->p_RW() = new std::vector<         int16>(*(std::vector<         int16>*)pRhs->p()); } break;
    case sstd::num_vec_int32   : { pLhs->p_RW() = new std::vector<         int32>(*(std::vector<         int32>*)pRhs->p()); } break;
    case sstd::num_vec_int64   : { pLhs->p_RW() = new std::vector<         int64>(*(std::vector<         int64>*)pRhs->p()); } break;
    case sstd::num_vec_uint8   : { pLhs->p_RW() = new std::vector<        uint8 >(*(std::vector<        uint8 >*)pRhs->p()); } break;
    case sstd::num_vec_uint16  : { pLhs->p_RW() = new std::vector<        uint16>(*(std::vector<        uint16>*)pRhs->p()); } break;
    case sstd::num_vec_uint32  : { pLhs->p_RW() = new std::vector<        uint32>(*(std::vector<        uint32>*)pRhs->p()); } break;
    case sstd::num_vec_uint64  : { pLhs->p_RW() = new std::vector<        uint64>(*(std::vector<        uint64>*)pRhs->p()); } break;
    case sstd::num_vec_float   : { pLhs->p_RW() = new std::vector<         float>(*(std::vector<         float>*)pRhs->p()); } break;
    case sstd::num_vec_double  : { pLhs->p_RW() = new std::vector<        double>(*(std::vector<        double>*)pRhs->p()); } break;
    case sstd::num_vec_str     : { pLhs->p_RW() = new std::vector<   std::string>(*(std::vector<   std::string>*)pRhs->p()); } break;
//    case sstd::num_vec_void_ptr: { pLhs->p_RW() = new std::vector<sstd::void_ptr>(*(std::vector<sstd::void_ptr>*)pRhs->p()); } break;
        
    case sstd::num_hash_str_str          : { pLhs->p_RW() = new std::unordered_map<std::string,      std::string>(*(std::unordered_map<std::string,      std::string>*)pRhs->p()); } break;
//    case sstd::num_hash_str_void_ptr     : { pLhs->p_RW() = new std::unordered_map<std::string,   sstd::void_ptr>(*(std::unordered_map<std::string,   sstd::void_ptr>*)pRhs->p()); } break;
//    case sstd::num_hash_void_ptr_void_ptr: { pLhs->p_RW() = new std::unordered_map<sstd::void_ptr,sstd::void_ptr>(*(std::unordered_map<sstd::void_ptr,sstd::void_ptr>*)pRhs->p()); } break;
        
    case sstd::num_vec_terp_var: {
        pLhs->p_RW() = new std::vector<sstd::terp::var*>(pRhs->size(), NULL);
        for(uint i=0;i<pRhs->size();++i){
            _CAST2VEC(pLhs->p_RW())[i] = new sstd::terp::var(pLhs->pSRCR_tbl());
            res &= _copy_value(_CAST2VEC(pLhs->p_RW())[i], _CAST2VEC(pRhs->p())[i],
                               vStack_copyDstAds_asRef_and_origRefAds, tbl_copySrcAds_to_copyDstAds,
                               opt_a, opt_i, opt_e); // TODO: base の pLhs->pSRCR_tbl() がコピー先でも再帰的に適用されるように修正する
        }
    } break;
//    case sstd::num_hash_terp_var: { pLhs->p_RW() = new std::unordered_map<std::string,sstd::terp::var*>(*(std::unordered_map<std::string,sstd::terp::var*>*)pRhs->p()); } break;
    case sstd::num_hash_terp_var: {
        std::unordered_map<std::string,sstd::terp::var*>* pRHash = (std::unordered_map<std::string,sstd::terp::var*>*)pRhs->p();

        std::unordered_map<std::string,sstd::terp::var*>* pLHash = new std::unordered_map<std::string,sstd::terp::var*>( pRHash->bucket_count() );
        pLhs->p_RW() = pLHash;
        
        for(auto itr=pRHash->begin(); itr!=pRHash->end(); ++itr){
            sstd::terp::var* pVal = new sstd::terp::var();
            (*pLHash)[ itr->first ] = pVal;
            res &= _copy_value(pVal, itr->second,
                               vStack_copyDstAds_asRef_and_origRefAds, tbl_copySrcAds_to_copyDstAds,
                               opt_a, opt_i, opt_e);
        }
    } break;
        
    default: { sstd::pdbg("ERROR: memory allocation is failed. typeNum '%d' is not defined.", pLhs->type()); return false; } break;
        
    }

    if(copy_internal_ref_as_obj && copy_external_ref_as_obj){ return res; }
    tbl_copySrcAds_to_copyDstAds[ (sstd::terp::var*)pRhs ] = (sstd::terp::var*)pLhs;
    
    return res;
}
void _copy_reference(
                     std::vector<std::tuple<sstd::terp::var*,sstd::terp::var*,uint>>& vStack_copyDstAds_asRef_and_origRefAds,
                     std::unordered_map<sstd::terp::var*,sstd::terp::var*>& tbl_copySrcAds_to_copyDstAds,
                     const char opt_a, const char opt_i, const char opt_e
                     )
{
    for(uint i=0; i<vStack_copyDstAds_asRef_and_origRefAds.size(); ++i){
        
        // Update addresses
        sstd::terp::var* copyDstAds_asRef = std::get<0>( vStack_copyDstAds_asRef_and_origRefAds[i] );
        sstd::terp::var* origRefAds       = std::get<1>( vStack_copyDstAds_asRef_and_origRefAds[i] );
        uint type                         = std::get<2>( vStack_copyDstAds_asRef_and_origRefAds[i] );
        
        auto itr = tbl_copySrcAds_to_copyDstAds.find( origRefAds );
        if(itr != tbl_copySrcAds_to_copyDstAds.end() && opt_i!='e'){
            // Internal reference
            
            //   Copy address
            copyDstAds_asRef->is_reference_RW() = true;
            copyDstAds_asRef->p_RW()            = itr->second;
            copyDstAds_asRef->type_RW()         = type;
            
            //   Update _pSRCR_tbl
            (*copyDstAds_asRef->pSRCR_tbl_RW())[ (sstd::terp::var*)copyDstAds_asRef->p() ].insert( copyDstAds_asRef );
        }else{
            // External reference
            
            //   Copy address
            copyDstAds_asRef->is_reference_RW() = true;
            copyDstAds_asRef->p_RW()            = origRefAds;
            copyDstAds_asRef->type_RW()         = type;
            
            //   Update _pSRCR_tbl
            (*((sstd::terp::var*)copyDstAds_asRef->p())->pSRCR_tbl_RW())[ (sstd::terp::var*)copyDstAds_asRef->p() ].insert( copyDstAds_asRef );
        }
    }
    
    return;
}
bool _copy_base(class sstd::terp::var* pLhs, const class sstd::terp::var* pRhs, const char opt_a, const char opt_i, const char opt_e){
    //  Table. Parameter settings for opt variables (opt_a, opt_i, opt_e).
    // ┌─────────────────────────┬───────────────────────────────────┬──────────────────────────────────────────────────────────────────────────┐
    // │                         │ Setting of the options (*1)       │                                                                          │
    // │                         │                                   │                                                                          │
    // │                         │    Copying object type is (*2):   │                                                                          │
    // │                         │ Actual  │ Internal   │ External   │                                                                          │
    // │                         │ object: │ reference: │ reference: │                                                                          │
    // │ Copy function name      │  opt_a  │  opt_i     │  opt_e     │ Descriptions                                                             │
    // ├─────────────────────────┼───────────────────────────────────┼──────────────────────────────────────────────────────────────────────────┤
    // │ sstd::terp::copy()      │    o    │      i     │      e     │ Copies the object as it is.                                              │
    // ├─────────────────────────┼───────────────────────────────────┼──────────────────────────────────────────────────────────────────────────┤
    // │ sstd::terp::eRef_copy() │    o    │      e     │      e     │ Copies the reference as its original address. (eRef: external reference) │
    // ├─────────────────────────┼───────────────────────────────────┼──────────────────────────────────────────────────────────────────────────┤
    // │ sstd::terp::deep_copy() │    o    │      o     │      o     │ Copies the reference by object.                                          │
    // └─────────────────────────┴───────────────────────────────────┴──────────────────────────────────────────────────────────────────────────┘
    // *1. Options:
    //       o: copy as an object
    //       i: copy as an internal reference (Constructing an internal reference structure)
    //       e: copy as an external reference
    // *2. Possible options:
    //       opt_a: 'o'
    //       opt_i: 'o', 'i', 'e'
    //       opt_e: 'o',      'e'
    bool res=true;
    
    _free_val(pLhs, pLhs->p_RW(), pLhs->pSRCR_tbl_RW(), pLhs->type_RW(), pLhs->is_reference_RW());
    
    std::vector<std::tuple<sstd::terp::var*,sstd::terp::var*,uint>> vStack_copyDstAds_asRef_and_origRefAds;
    std::unordered_map<sstd::terp::var*,sstd::terp::var*> tbl_copySrcAds_to_copyDstAds;
    res &= _copy_value(pLhs, pRhs,
                       vStack_copyDstAds_asRef_and_origRefAds,
                       tbl_copySrcAds_to_copyDstAds,
                       opt_a, opt_i, opt_e
                       );
    sstd::printn_all( vStack_copyDstAds_asRef_and_origRefAds );
    sstd::printn_all( tbl_copySrcAds_to_copyDstAds );

    _copy_reference(vStack_copyDstAds_asRef_and_origRefAds,
                    tbl_copySrcAds_to_copyDstAds,
                    opt_a, opt_i, opt_e
                    );

    return res;
}
void sstd::terp::var::copy(const class sstd::terp::var& rhs){ _copy_base(this, &rhs, 'o', 'i', 'e'); }
//void sstd::terp::var::copy(const class sstd::terp::var& rhs, const char opt_a, const char opt_i, const char opt_e){ _copy_base(this, &rhs, opt_a, opt_i, opt_e); }

//---

bool sstd::terp::copy     (sstd::terp::var& lhs, const sstd::terp::var& rhs){ return _copy_base(&lhs, &rhs, 'o', 'i', 'e'); }
bool sstd::terp::eRef_copy(sstd::terp::var& lhs, const sstd::terp::var& rhs){ return _copy_base(&lhs, &rhs, 'o', 'e', 'e'); }
bool sstd::terp::deep_copy(sstd::terp::var& lhs, const sstd::terp::var& rhs){ return _copy_base(&lhs, &rhs, 'o', 'o', 'o'); }

//---

void sstd::terp::var::move(      class sstd::terp::var&& rhs){
    _free_val(this, _p, _pSRCR_tbl, _type, _is_reference);
    
    if(this->_is_pSRCR_tbl_base && rhs.is_pSRCR_tbl_base()){
        std::swap(this->_type,              rhs.type_RW()             );
        std::swap(this->_is_reference,      rhs.is_reference_RW()     );
        std::swap(this->_is_pSRCR_tbl_base, rhs.is_pSRCR_tbl_base_RW());
        std::swap(this->_pSRCR_tbl,         rhs.pSRCR_tbl_RW()        );
        std::swap(this->_p,                 rhs.p_RW()                );
        
    }else{
        // Because of pSRCR_tbl is shareed amaong all the elements, 
        // if rhs is NOT a root (=base) element, `sstd::terp::var` can NOT identify which pSRCR_tbl's values should be copied.
        sstd::terp::var::copy(rhs);
        
    }
}

void _fill_dependent_ref_null(sstd::terp::var* _pVar, void* _p, sstd::terp::srcr_tbl* _pSRCR_tbl, const uint _type, const bool _is_reference){
    if(_is_reference==true || _pSRCR_tbl==NULL){ return; }

    auto itr_ht = _pSRCR_tbl->find( (sstd::terp::var*)_pVar ); // _ht: hash table
    if(!(itr_ht!=_pSRCR_tbl->end())){ return; }
    
    std::unordered_set<sstd::terp::var*>& hash_set = itr_ht->second;
    for(auto itr_hs=hash_set.begin(); itr_hs!=hash_set.end(); ++itr_hs){ // _hs: hash set
        ((sstd::terp::var*)*itr_hs)->type_RW()         = sstd::num_null;
        ((sstd::terp::var*)*itr_hs)->is_reference_RW() = false;
        ((sstd::terp::var*)*itr_hs)->p_RW()            = NULL;
    }

    _pSRCR_tbl->erase( itr_ht );
}
void _rm_dependent_ret_from_precedent_pSRCR_tbl(sstd::terp::var* _pVar_in, void* _p, sstd::terp::srcr_tbl* _pSRCR_tbl_in, const uint _type, const bool _is_reference){
    if(_pSRCR_tbl_in==NULL){ return; }
    
    sstd::terp::var*      _pVar      = (!_is_reference) ? _pVar_in      : (sstd::terp::var*)_pVar_in->p();
    sstd::terp::srcr_tbl* _pSRCR_tbl = (!_is_reference) ? _pSRCR_tbl_in :((sstd::terp::var*)_pVar_in->p())->pSRCR_tbl();
    
    auto itr_ht = _pSRCR_tbl->find( _pVar ); // _ht: hash table
    if(!(itr_ht!=_pSRCR_tbl->end())){ return; }
    
    std::unordered_set<sstd::terp::var*>& hash_set = itr_ht->second;
    auto itr_hs = hash_set.find( _pVar_in );
    if(!(itr_hs!=hash_set.end())){ return; }
    
    if(hash_set.size()==1){
        _pSRCR_tbl->erase( itr_ht );
    }else{
        hash_set.erase( itr_hs );
    }
}
void _free_vec_terp_var(sstd::terp::var* _pVar, void* _p, const uint _type, const bool _is_reference){
    for(uint i=0;i<_CAST2VEC(_p).size();++i){
        sstd::terp::var* var_p = _CAST2VEC(_p)[i];
        if( var_p==NULL || var_p->is_reference() ){ continue; }
        _free_val( var_p, var_p->p_RW(), var_p->pSRCR_tbl_RW(), var_p->type(), var_p->is_reference() );
    }
    delete (std::vector<sstd::terp::var*>*)_p;
}
void _free_hash_terp_var(sstd::terp::var* _pVar, void* _p, const uint _type, const bool _is_reference){
    for(auto itr=_CAST2HASH(_p).begin(); itr!=_CAST2HASH(_p).end(); ++itr){
        sstd::terp::var* var_p = itr->second;
        if( var_p==NULL || var_p->is_reference() ){ continue; }
        _free_val( var_p, var_p->p_RW(), var_p->pSRCR_tbl_RW(), var_p->type(), var_p->is_reference() );
    }
    delete (std::unordered_map<std::string,sstd::terp::var*>*)_p;
}
void _free_val(sstd::terp::var* _pVar, void*& _p, sstd::terp::srcr_tbl* _pSRCR_tbl, const uint _type, const bool _is_reference){
    if(_p==NULL){ return; }
    _fill_dependent_ref_null                  (_pVar, _p, _pSRCR_tbl, _type, _is_reference); // A Process for the dependent object
    _rm_dependent_ret_from_precedent_pSRCR_tbl(_pVar, _p, _pSRCR_tbl, _type, _is_reference); // A Process for the precedent object
    if(_is_reference==true){ _pVar->type_RW()=sstd::num_null; _pVar->is_reference_RW()=false; _pVar->p_RW()=NULL; return; }

    switch (_type){
    case sstd::num_null    : {} break;
    case sstd::num_bool    : { delete (          bool*)_p; } break;
    case sstd::num_char    : { delete (          char*)_p; } break;
    case sstd::num_int8    : { delete (         int8 *)_p; } break;
    case sstd::num_int16   : { delete (         int16*)_p; } break;
    case sstd::num_int32   : { delete (         int32*)_p; } break;
    case sstd::num_int64   : { delete (         int64*)_p; } break;
    case sstd::num_uint8   : { delete (        uint8 *)_p; } break;
    case sstd::num_uint16  : { delete (        uint16*)_p; } break;
    case sstd::num_uint32  : { delete (        uint32*)_p; } break;
    case sstd::num_uint64  : { delete (        uint64*)_p; } break;
    case sstd::num_float   : { delete (         float*)_p; } break;
    case sstd::num_double  : { delete (        double*)_p; } break;
    case sstd::num_str     : { delete (   std::string*)_p; } break;
//    case sstd::num_void_ptr: { delete (sstd::void_ptr*)_p; } break; // DELETE LATER
        
    case sstd::num_vec_bool    : { delete (std::vector<          bool>*)_p; } break;
    case sstd::num_vec_char    : { delete (std::vector<          char>*)_p; } break;
    case sstd::num_vec_int8    : { delete (std::vector<         int8 >*)_p; } break;
    case sstd::num_vec_int16   : { delete (std::vector<         int16>*)_p; } break;
    case sstd::num_vec_int32   : { delete (std::vector<         int32>*)_p; } break;
    case sstd::num_vec_int64   : { delete (std::vector<         int64>*)_p; } break;
    case sstd::num_vec_uint8   : { delete (std::vector<        uint8 >*)_p; } break;
    case sstd::num_vec_uint16  : { delete (std::vector<        uint16>*)_p; } break;
    case sstd::num_vec_uint32  : { delete (std::vector<        uint32>*)_p; } break;
    case sstd::num_vec_uint64  : { delete (std::vector<        uint64>*)_p; } break;
    case sstd::num_vec_float   : { delete (std::vector<         float>*)_p; } break;
    case sstd::num_vec_double  : { delete (std::vector<        double>*)_p; } break;
    case sstd::num_vec_str     : { delete (std::vector<   std::string>*)_p; } break;
//    case sstd::num_vec_void_ptr: { delete (std::vector<sstd::void_ptr>*)_p; } break; // DELETE LATER
        
    case sstd::num_hash_str_str          : { delete (std::unordered_map<std::string,      std::string>*)_p; } break;
//    case sstd::num_hash_str_void_ptr     : { delete (std::unordered_map<std::string,   sstd::void_ptr>*)_p; } break;
//    case sstd::num_hash_void_ptr_void_ptr: { delete (std::unordered_map<sstd::void_ptr,sstd::void_ptr>*)_p; } break;
        
    case sstd::num_vec_terp_var:  { _free_vec_terp_var (_pVar, _p, _type, _is_reference); } break;
    case sstd::num_hash_terp_var: { _free_hash_terp_var(_pVar, _p, _type, _is_reference); } break;
        
    default: { sstd::pdbg("ERROR: free() memory is failed. typeNum '%d' is not defined.", _type); } break;
    }

    _p=NULL;
}
void sstd::terp::var::_free_SRCR_tbl(){
    if(this->_pSRCR_tbl==NULL){ return; }
    if(this->_is_pSRCR_tbl_base){
        delete this->_pSRCR_tbl;
        this->_pSRCR_tbl=NULL;
        this->_is_pSRCR_tbl_base=false;
    }
}
void sstd::terp::var::free(){
    _free_val(this, _p, _pSRCR_tbl, _type, _is_reference);
    sstd::terp::var::_free_SRCR_tbl();
}

sstd::terp::var& sstd::terp::var::operator=(const sstd::terp::var&  rhs){
    sstd::print_all("operator=(const sstd::terp::var&  rhs)");
    copy(rhs);
    return *this;
}
sstd::terp::var  sstd::terp::var::operator=(      sstd::terp::var&& rhs){
    sstd::print_all("operator=(      sstd::terp::var&& rhs)");
    move(std::move(rhs));
    return *this;
}
sstd::terp::var& sstd::terp::var::operator=(const sstd::terp::var* pRhs_in){
    sstd::print_all("operator=(const sstd::terp::var* pRhs)");

    sstd::terp::var* pRhs = (! pRhs_in->is_reference()) ? (sstd::terp::var*)pRhs_in : (sstd::terp::var*)pRhs_in->p(); // resolve double reference
    this->_is_reference = true;
    this->_type         =        pRhs->type();
    this->_p            = (void*)pRhs;
    (*pRhs->_pSRCR_tbl)[ (sstd::terp::var*)pRhs ].insert( (sstd::terp::var*)this );
    sstd::printn_all(*pRhs->_pSRCR_tbl);
    sstd::printn_all(pRhs->_pSRCR_tbl);
    return *this;
}

template <typename T>
void sstd::terp::var::_overwrite(T* ptr){
    _free_val(this, _p, _pSRCR_tbl, _type, _is_reference);
    this->_type = sstd::type2num(T());
    this->_p    = ptr;
}
sstd::terp::var& sstd::terp::var::operator=(const char* rhs){
    sstd::print_all("operator=(const char* rhs)");
    _overwrite(new std::string(rhs));
    return *this;
}

bool _is_equal(const sstd::terp::var& lhs, const sstd::terp::var& rhs, const bool check_ref_flag, const bool check_ref_addr); // forward declaration
bool _is_equal_list(const sstd::terp::var& lhs, const sstd::terp::var& rhs, const bool check_ref_flag, const bool check_ref_addr){
    if(lhs.size()!=rhs.size()){ return false; }
    
    for(uint i=0; i<lhs.size(); ++i){
        if(!_is_equal(lhs[i], rhs[i], check_ref_flag, check_ref_addr)){ return false; }
    }
    
    return true;
}
bool _is_equal_hash(const sstd::terp::var& lhs, const sstd::terp::var& rhs, const bool check_ref_flag, const bool check_ref_addr){ // TODO: これ，reference あるとかなり実装が面倒になるはず
    if(lhs.size()!=rhs.size()){ return false; }
    
    for(auto itr=lhs.begin(); itr!=lhs.end(); ++itr){
        std::string key = itr.first_to<std::string>();
        
        auto itr_rhs = rhs.find(key.c_str());
        if(!(itr_rhs!=rhs.end())){ return false; }

        if(!_is_equal(itr.second(), itr_rhs.second(), check_ref_flag, check_ref_addr)){ return false; }
    }
    
    return true;
}
bool _is_equal(const sstd::terp::var& lhs, const sstd::terp::var& rhs, const bool check_ref_flag, const bool check_ref_addr){
    if(check_ref_flag && lhs.is_reference()!=rhs.is_reference()){ return false; }
    if(lhs.type()!=rhs.type()){ return false; }
    
    switch(lhs.typeNum()){
    case sstd::num_str:           { return lhs.to<std::string>()==rhs.to<std::string>(); } break;
    case sstd::num_vec_terp_var:  { return _is_equal_list(lhs, rhs, check_ref_flag, check_ref_addr); } break;
    case sstd::num_hash_terp_var: { return _is_equal_hash(lhs, rhs, check_ref_flag, check_ref_addr); } break;
    case sstd::num_null:          { return true; } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }
    
    return false;
}
bool sstd::terp::var::equal(const sstd::terp::var& rhs, const char* opt) const { // TODO: write interface tests
    if(!sstd::charIn_all(std::string(opt)+" ", "ar ")){ sstd::pdbg_err("sstd::terp::var::equal() is falied. `%s` is unexpected option.", opt); return false; }
    // TOCO: sstd::charIn_all("", "abc") のように strlen(arg1)==0 の return 値は true にした方がよいのでは・・・？
    bool check_ref_flag = sstd::charIn('r', opt); // Opt "r" checks reference flag
    bool check_ref_addr = sstd::charIn('a', opt); // Opt "a" checks reference address
    
    return _is_equal(*this, rhs, check_ref_flag, check_ref_addr);
}
bool sstd::terp::var::equal(const sstd::terp::var& rhs) const { // TODO: write interface tests
    return sstd::terp::var::equal(rhs, "r");
}
bool sstd::terp::var::operator==(const sstd::terp::var& rhs){ return  sstd::terp::var::equal(rhs); }
bool sstd::terp::var::operator!=(const sstd::terp::var& rhs){ return !sstd::terp::var::equal(rhs); }

#define _OPE_SUBSCRIPT_IDX_BASE()                                       \
    void* local_p = (! this->_is_reference) ? _p : (void*)((sstd::terp::var*)_p)->_p; \
                                                                        \
    switch(_type){                                                      \
    case sstd::num_vec_terp_var: { return *_CAST2VEC(local_p)[idx]; } break; \
    default: { sstd::pdbg_err("Ope[](char*) is failed. Unexpedted data type. sstd::terp::var takes \"sstd::terp::hash()\" type, but treat as a \"sstd::terp::list()\".\n"); } break; \
    }                                                                   \
    return *this;
#define _OPE_SUBSCRIPT_KEY_BASE(pKey)                                   \
    switch(_type){                                                      \
    case sstd::num_hash_terp_var: {                                     \
        sstd::terp::var** ppVal = &(_CAST2HASH(_p)[pKey]);              \
        if(*ppVal==NULL){ (*ppVal)=new sstd::terp::var(_pSRCR_tbl); }   \
        return **ppVal;                                                 \
    } break;                                                            \
    case sstd::num_null: {                                              \
        _type = sstd::num_hash_terp_var;                                \
        _p    = new std::unordered_map<std::string, sstd::terp::var*>(); \
        sstd::terp::var** ppVal = &(_CAST2HASH(_p)[pKey]);              \
        (*ppVal)=new sstd::terp::var(_pSRCR_tbl);                       \
        return **ppVal;                                                 \
    } break;                                                            \
    default: { sstd::pdbg_err("Ope[](char*) is failed. Unexpedted data type. sstd::terp::var takes type number `%d`, but treat as a \"sstd::terp::hash()\".\n", _type); } break; \
    }                                                                   \
    return *this;
#define _OPE_SUBSCRIPT_KEY_BASE_CONST(pKey)                             \
    switch(_type){                                                      \
    case sstd::num_hash_terp_var: {                                     \
        sstd::terp::var* pVal = _CAST2HASH(_p)[pKey];                   \
        if(pVal==NULL){ sstd::pdbg_err("Ope[](char*) is failed. NULL pointer detection error. pKey: `%s` is NOT allocated.\n", pKey); return *this; } \
        return *pVal;                                                   \
    } break;                                                            \
    default: { sstd::pdbg_err("Ope[](char*) is failed. Unexpedted data type. sstd::terp::var takes type number `%d`, but treat as a \"sstd::terp::hash()\".\n", _type); } break; \
    }                                                                   \
    return *this;
      sstd::terp::var& sstd::terp::var::operator[](const   int  idx)       { _OPE_SUBSCRIPT_IDX_BASE(); }
const sstd::terp::var& sstd::terp::var::operator[](const   int  idx) const { _OPE_SUBSCRIPT_IDX_BASE(); }
      sstd::terp::var& sstd::terp::var::operator[](const       char* pKey)       { _OPE_SUBSCRIPT_KEY_BASE      (pKey); }
const sstd::terp::var& sstd::terp::var::operator[](const       char* pKey) const { _OPE_SUBSCRIPT_KEY_BASE_CONST(pKey); }
      sstd::terp::var& sstd::terp::var::operator[](const std::string  key)       { _OPE_SUBSCRIPT_KEY_BASE      (key.c_str()); }
const sstd::terp::var& sstd::terp::var::operator[](const std::string  key) const { _OPE_SUBSCRIPT_KEY_BASE_CONST(key.c_str()); }

      sstd::terp::var& sstd::terp::var::ope_sb  (const int idx)       { return (*this)[idx]; }
const sstd::terp::var& sstd::terp::var::ope_sb_c(const int idx) const { return (*this)[idx]; }
      sstd::terp::var& sstd::terp::var::ope_sb  (const       char* pKey)       { return (*this)[pKey]; }
const sstd::terp::var& sstd::terp::var::ope_sb_c(const       char* pKey) const { return (*this)[pKey]; }

//---

const sstd::terp::_v_iterator _v_begin(bool _is_reference, void* p_in){
    return (! _is_reference) ? _CAST2VEC(p_in).begin() : _CAST2VEC(((sstd::terp::var*)p_in)->p()).begin();
}
const sstd::terp::_v_iterator _v_end  (bool _is_reference, void* p_in){
    return (! _is_reference) ? _CAST2VEC(p_in).end()   : _CAST2VEC(((sstd::terp::var*)p_in)->p()).end();
}
const sstd::terp::_h_iterator _h_begin(bool _is_reference, void* p_in){
    return (! _is_reference) ? _CAST2HASH(p_in).begin() : _CAST2HASH(((sstd::terp::var*)p_in)->p()).begin();
}
const sstd::terp::_h_iterator _h_end  (bool _is_reference, void* p_in){
    return (! _is_reference) ? _CAST2HASH(p_in).end()   : _CAST2HASH(((sstd::terp::var*)p_in)->p()).end();
}
sstd::terp::iterator sstd::terp::var::begin() const {
    switch(_type){
    case sstd::num_vec_terp_var:  { return sstd::terp::iterator(_v_begin(_is_reference, _p)); } break;
    case sstd::num_hash_terp_var: { return sstd::terp::iterator(_h_begin(_is_reference, _p)); } break;
    case sstd::num_null:          {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return sstd::terp::iterator();
}
sstd::terp::iterator sstd::terp::var::end() const {
    switch(_type){
    case sstd::num_vec_terp_var:  { return sstd::terp::iterator(_v_end(_is_reference, _p)); } break;
    case sstd::num_hash_terp_var: { return sstd::terp::iterator(_h_end(_is_reference, _p)); } break;
    case sstd::num_null:          {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return sstd::terp::iterator();
}

//---

uint sstd::terp::var::typeNum() const { return this->_type; }
std::string sstd::terp::var::typeStr() const { return sstd::typeNum2str(_type); }

//---
// for hash type

uint sstd::terp::var::bucket_count(){
    switch(_type){
    case sstd::num_hash_terp_var: { return _CAST2HASH(_p).bucket_count(); } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }
    return 0;
}

//---

sstd::terp::iterator sstd::terp::var::erase(const sstd::terp::iterator& rhs){
    switch(_type){
    case sstd::num_vec_terp_var:  { delete (sstd::terp::var*)(*rhs._v_itr_R()); return sstd::terp::iterator( _CAST2VEC(_p).erase(rhs._v_itr_R()) ); } break;
    case sstd::num_null:          {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return sstd::terp::iterator();
}
uint sstd::terp::var::erase(const char* pKey){
    switch(_type){
    case sstd::num_hash_terp_var: {
        auto itr = _CAST2HASH(_p).find(pKey);
        if(itr!=_CAST2HASH(_p).end()){
            delete (sstd::terp::var*)itr->second;
            return (_CAST2HASH(_p).erase(itr)!=_CAST2HASH(_p).end() ? 1:0);
        }
        return 0;
    } break;
    case sstd::num_null:          {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return 0;
}

//---

sstd::terp::iterator sstd::terp::var::find(const char* pKey) const {
    switch(_type){
    case sstd::num_hash_terp_var: { return sstd::terp::iterator( _CAST2HASH(_p).find(pKey) ); } break;
    case sstd::num_null:          {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return sstd::terp::iterator();
}
sstd::terp::iterator sstd::terp::var::find(const std::string  key) const {
    return sstd::terp::var::find(key.c_str());
}

//---
// for list type

void sstd::terp::var::pop_back(){
    NULL_CHECK(_p);
    switch(_type){
    case sstd::num_vec_terp_var: { if(_CAST2VEC(this->_p).size()==0){return;} delete _CAST2VEC(this->_p).back(); _CAST2VEC(this->_p).pop_back(); return; } break;
    case sstd::num_null:         {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return;
}

void sstd::terp::var::push_back(){ // push_back null
    NULL_CHECK(_p);
    if(_type!=sstd::num_vec_terp_var){ sstd::pdbg_err("push_back(char*) is failed. Unexpedted data type. This function requires sstd::num_vec_terp_var type, but takes %s type.\n", sstd::typeNum2str(this->_type).c_str()); return; }
    _CAST2VEC(_p).push_back(new sstd::terp::var());
}
void sstd::terp::var::push_back(const char* pRhs){
    NULL_CHECK(_p);
    if(_type!=sstd::num_vec_terp_var){ sstd::pdbg_err("push_back(char*) is failed. Unexpedted data type. This function requires sstd::num_vec_terp_var type, but takes %s type.\n", sstd::typeNum2str(this->_type).c_str()); return; }
    _CAST2VEC(_p).push_back(new sstd::terp::var(pRhs));
}
void sstd::terp::var::push_back(const sstd::terp::var& rhs){
    NULL_CHECK(_p);
    if(_type!=sstd::num_vec_terp_var){ sstd::pdbg_err("push_back(var&) is failed. Unexpedted data type. This function requires sstd::num_vec_terp_var type, but takes %s type.\n", sstd::typeNum2str(this->_type).c_str()); return; }
    _CAST2VEC(_p).push_back(new sstd::terp::var(rhs));
}
void sstd::terp::var::push_back(      sstd::terp::var&& rhs){
    NULL_CHECK(_p);
    if(_type!=sstd::num_vec_terp_var){ sstd::pdbg_err("push_back(var&) is failed. Unexpedted data type. This function requires sstd::num_vec_terp_var type, but takes %s type.\n", sstd::typeNum2str(this->_type).c_str()); return; }
    _CAST2VEC(_p).push_back(new sstd::terp::var(std::move(rhs))); // call move constructor of "sstd::void_ptr::void_ptr()"
}

void sstd::terp::var::resize(uint len){
    uint current_size = this->size();
    
    if(len < current_size){
        // Release the outscope memory
        for(int i=current_size-1; i>=(int)len; --i){
            delete _CAST2VEC(_p)[i];
        }
    }
    
    switch(_type){
    case sstd::num_vec_terp_var: { _CAST2VEC(_p).resize( len ); } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }

    if(len > current_size){
        // Allocate the outscope memory
        for(uint i=current_size; i<len; ++i){
            _CAST2VEC(_p)[i] = new sstd::terp::var();
        }
    }
}

uint sstd::terp::var::size() const {
    void* local_p = (! this->_is_reference) ? _p : (void*)((sstd::terp::var*)_p)->_p;
    
    switch(_type){
    case sstd::num_vec_terp_var : { return _CAST2VEC (local_p).size(); } break;
    case sstd::num_hash_terp_var: { return _CAST2HASH(local_p).size(); } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
