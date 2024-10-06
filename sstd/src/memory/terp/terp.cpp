#include "terp.hpp"

#include "../../definitions/typeNum.hpp"
#include "../../print/pdbg.hpp"
#include "../../string/ssprintf.hpp"

#include "../../print/print.hpp" // sstd::printn() for debugging at development

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define _CAST2VEC(_P) (*(std::vector<sstd::terp::var*>*)_P)
#define _CAST2HASH(_P) (*(std::unordered_map<std::string,sstd::terp::var*>*)_P)

using srcr_tbl = std::unordered_map<sstd::terp::var*,std::unordered_set<sstd::terp::var*>>;

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
        // Allocate the outscope memory
        _CAST2VEC(r.p_RW())[i] = new sstd::terp::var(); // TODO: _pSRCR_tbl の再確保を余儀なくされているので，専用のコンストラクタを作る

        // Update _pSRCR_tbl base
        delete _CAST2VEC(r.p_RW())[i]->pSRCR_tbl_RW();
        _CAST2VEC(r.p_RW())[i]->is_pSRCR_tbl_base_RW() = false;
        _CAST2VEC(r.p_RW())[i]->pSRCR_tbl_RW()         = r.pSRCR_tbl();
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
sstd::terp::var::var():                       _type(sstd::num_null), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(NULL) {}
sstd::terp::var::var(const class var&   rhs): _type(sstd::num_null), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(NULL) { copy(rhs); }
sstd::terp::var::var(      class var&&  rhs): _type(sstd::num_null), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(NULL) { free(); move(std::move(rhs)); }
sstd::terp::var::var(        bool       rhs): _type(sstd::num_null), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(new std::string(rhs?"true":"false")) {}
sstd::terp::var::var(        char       rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(new std::string({rhs})) {}
sstd::terp::var::var(        int8       rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(new std::string(sstd::ssprintf("%d", rhs))) {}
sstd::terp::var::var(        int16      rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(new std::string(sstd::ssprintf("%d", rhs))) {}
sstd::terp::var::var(        int32      rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(new std::string(sstd::ssprintf("%d", rhs))) {}
sstd::terp::var::var(        int64      rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(new std::string(sstd::ssprintf("%ld", rhs))) {}
sstd::terp::var::var(       uint8       rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(new std::string(sstd::ssprintf("%u", rhs))) {}
sstd::terp::var::var(       uint16      rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(new std::string(sstd::ssprintf("%u", rhs))) {}
sstd::terp::var::var(       uint32      rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(new std::string(sstd::ssprintf("%u", rhs))) {}
sstd::terp::var::var(       uint64      rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(new std::string(sstd::ssprintf("%lu", rhs))) {}
sstd::terp::var::var(        float      rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(new std::string(sstd::ssprintf(_format(rhs).c_str(), rhs))) {}
sstd::terp::var::var(       double      rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(new std::string(sstd::ssprintf(_format(rhs).c_str(), rhs))) {}
sstd::terp::var::var(const char*        rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(new std::string(rhs)) {}
sstd::terp::var::var(const std::string& rhs): _type(sstd::num_str ), _is_reference(false), _is_pSRCR_tbl_base(true), _pSRCR_tbl(new srcr_tbl()), _p(new std::string(rhs)) {}

sstd::terp::var::~var(){ if(!_is_reference){sstd::terp::var::free();} }

//---
// internal

uint sstd::terp::var::type() const { return this->_type; }
bool sstd::terp::var::is_reference() const { return this->_is_reference; }
bool sstd::terp::var::is_pSRCR_tbl_base() const { return this->_is_pSRCR_tbl_base; }
srcr_tbl* sstd::terp::var::pSRCR_tbl() const { return this->_pSRCR_tbl; }
void* sstd::terp::var::p() const { return this->_p; }

uint & sstd::terp::var::type_RW(){ return this->_type; }
bool & sstd::terp::var::is_reference_RW(){ return this->_is_reference; }
bool & sstd::terp::var::is_pSRCR_tbl_base_RW(){ return this->_is_pSRCR_tbl_base; }
srcr_tbl*& sstd::terp::var::pSRCR_tbl_RW(){ return this->_pSRCR_tbl; }
void*& sstd::terp::var::p_RW(){ return this->_p; }

//---
// common

// copy(), allocate(), free()
void _copy_base(class sstd::terp::var* pLhs, const class sstd::terp::var* pRhs){ // TODO: これ，reference あるとかなり実装が面倒になるはず
    pLhs->type_RW() = pRhs->type();
    if(pRhs->p()==NULL){ pLhs->p_RW()=NULL; return; }
    switch (pLhs->type()){
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
        
    case sstd::num_vec_terp_var:  {
        pLhs->p_RW() = new std::vector<sstd::terp::var*>(pRhs->size(), NULL);
        for(uint i=0;i<pRhs->size();++i){
            _CAST2VEC(pLhs->p_RW())[i] = new sstd::terp::var();
            _copy_base(_CAST2VEC(pLhs->p_RW())[i], _CAST2VEC(pRhs->p())[i]);
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
            _copy_base(pVal, itr->second);
        }
    } break;
        
    default: { sstd::pdbg("ERROR: allocating memory is failed. typeNum '%d' is not defined.", pLhs->type()); } break;
        
    }
}
void sstd::terp::var::copy(const class sstd::terp::var& rhs){
    sstd::terp::var::free();
    _copy_base(this, &rhs);
}

void sstd::terp::var::move(      class sstd::terp::var&& rhs){
    this->_type = rhs.type(); rhs.type_RW() = sstd::num_null;
    this->_p    = rhs.p();    rhs.p_RW()    = NULL;
}
/*
void sstd::terp::var::_fill_ref_src_null(sstd::terp::var* ref_src_address){
    
    auto itr = _pSRCR_tbl->find(ref_src_address);
    
    if(itr!=_pSRCR_tbl->end()){
        std::unordered_set<sstd::terp::var*> hash_set = itr->second;
        
        for(auto itr=hash_set.begin(); itr!=hash_set.end(); ++itr){
            printf("301\n");
            sstd::terp::var* pRef = *itr;
            pRef->type_RW()         = sstd::num_null;
            pRef->is_reference_RW() = false;
            pRef->p_RW()            = NULL;
        }
    }
}*/
void sstd::terp::var::_fill_ref_src_null(const std::unordered_set<sstd::terp::var*>& hash_set){
    for(auto itr=hash_set.begin(); itr!=hash_set.end(); ++itr){
        sstd::terp::var* pRef = *itr;
        pRef->type_RW()         = sstd::num_null;
        pRef->is_reference_RW() = false;
        pRef->p_RW()            = NULL;
    }
}
void sstd::terp::var::_fillout_ref_src_null(){
    if(this->_is_pSRCR_tbl_base){
        for(auto itr=_pSRCR_tbl->begin(); itr!=_pSRCR_tbl->end(); ++itr){
            sstd::terp::var::_fill_ref_src_null(itr->second);
        }
        
        this->_is_pSRCR_tbl_base=false;
        delete this->_pSRCR_tbl;
        this->_pSRCR_tbl=NULL;
    }else{
        // TODO
    }
}
void sstd::terp::var::free(){
    sstd::terp::var::_fillout_ref_src_null();
    if(this->_p==NULL){ return; }

    switch (this->_type){
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
        
    case sstd::num_vec_terp_var: {
        for(uint i=0;i<_CAST2VEC(_p).size();++i){
            delete _CAST2VEC(_p)[i];
        }
        delete (std::vector<sstd::terp::var*>*)_p;
    } break;
    case sstd::num_hash_terp_var: {
        for(auto itr=_CAST2HASH(_p).begin(); itr!=_CAST2HASH(_p).end(); ++itr){
            delete itr->second;
        }
        delete (std::unordered_map<std::string,sstd::terp::var*>*)_p;
    } break;
        
    default: { sstd::pdbg("ERROR: free() memory is failed. typeNum '%d' is not defined.", this->_type); } break;
    }

    this->_p=NULL;
}

sstd::terp::var& sstd::terp::var::operator=(const sstd::terp::var& rhs){
    copy(rhs);
    return *this;
}
sstd::terp::var& sstd::terp::var::operator=(const sstd::terp::var* pRhs){
    this->_is_reference = true;
    this->_type         = pRhs->type();
    this->_p            = pRhs->p(); // TODO: ref アドレスが _is_reference==true の場合，free() が厄介になるので，解決してから代入するように修正すること
    printf("404\n");
    sstd::printn(pRhs->_pSRCR_tbl);
    (*pRhs->_pSRCR_tbl)[ (sstd::terp::var*)pRhs ].insert( (sstd::terp::var*)this );
    printf("406\n");
    return *this;
}

template <typename T>
void sstd::terp::var::_overwrite(T* ptr){
    sstd::terp::var::free();
    this->_type = sstd::type2num(T());
    this->_p    = ptr;
}
sstd::terp::var& sstd::terp::var::operator=(const char* rhs){
    _overwrite(new std::string(rhs));
    return *this;
}

bool _is_equal(const sstd::terp::var& lhs, const sstd::terp::var& rhs); // forward declaration
bool _is_equal_list(const sstd::terp::var& lhs, const sstd::terp::var& rhs){
    if(lhs.size()!=rhs.size()){ return false; }
    
    for(uint i=0; i<lhs.size(); ++i){
        if(!_is_equal(lhs[i], rhs[i])){ return false; }
    }
    
    return true;
}
bool _is_equal_hash(const sstd::terp::var& lhs, const sstd::terp::var& rhs){ // TODO: これ，reference あるとかなり実装が面倒になるはず
    if(lhs.size()!=rhs.size()){ return false; }

    for(auto itr=lhs.begin(); itr!=lhs.end(); ++itr){
        std::string key = itr.first_to<std::string>();
        
        auto itr_rhs = rhs.find(key.c_str());
        if(!(itr_rhs!=rhs.end())){ return false; }

        if(!_is_equal(itr.second(), itr_rhs.second())){ return false; }
    }
    
    return true;
}
bool _is_equal(const sstd::terp::var& lhs, const sstd::terp::var& rhs){
    if(lhs.type()!=rhs.type()){ return false; }
    
    switch(lhs.typeNum()){
    case sstd::num_str:           { return lhs.to<std::string>()==rhs.to<std::string>(); } break;
    case sstd::num_vec_terp_var:  { return _is_equal_list(lhs, rhs); } break;
    case sstd::num_hash_terp_var: { return _is_equal_hash(lhs, rhs); } break;
    case sstd::num_null:             { return true; } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }
    
    return false;
}
bool sstd::terp::var::operator==(const sstd::terp::var& rhs){ return  _is_equal(*this, rhs); }
bool sstd::terp::var::operator!=(const sstd::terp::var& rhs){ return !_is_equal(*this, rhs); }

#define _OPE_SUBSCRIPT_IDX_BASE()                                       \
    switch(_type){                                                      \
    case sstd::num_vec_terp_var: { return *_CAST2VEC(this->_p)[idx]; } break; \
    default: { sstd::pdbg_err("Ope[](char*) is failed. Unexpedted data type. sstd::terp::var takes \"sstd::terp::hash()\" type, but treat as a \"sstd::terp::list()\".\n"); } break; \
    }                                                                   \
    return *this;
#define _OPE_SUBSCRIPT_KEY_BASE(pKey)                                   \
    switch(_type){                                                      \
    case sstd::num_hash_terp_var: {                                     \
        sstd::terp::var** ppVal = &(_CAST2HASH(_p)[pKey]);              \
        if(*ppVal==NULL){ (*ppVal)=new sstd::terp::var(); }             \
        return **ppVal;                                                 \
    } break;                                                            \
    case sstd::num_null: {                                              \
        _type = sstd::num_hash_terp_var;                                \
        _p    = new std::unordered_map<std::string, sstd::terp::var*>(); \
        sstd::terp::var** ppVal = &(_CAST2HASH(_p)[pKey]);              \
        (*ppVal)=new sstd::terp::var();                                 \
        return **ppVal;                                                 \
    } break;                                                            \
    default: { sstd::pdbg_err("Ope[](char*) is failed. Unexpedted data type. sstd::terp::var takes type number `%d`, but treat as a \"sstd::terp::hash()\".\n", _type); } break; \
    }                                                                   \
    return *this;
#define _OPE_SUBSCRIPT_KEY_BASE_CONST(pKey)                             \
    switch(_type){                                                      \
    case sstd::num_hash_terp_var: {                                     \
        sstd::terp::var* pVal = _CAST2HASH(_p)[pKey];                   \
        if(pVal==NULL){ sstd::pdbg_err("Ope[](char*) is failed. NULL pointer detection error. pKey: `%s` is NOT allocated.\n", pKey); } \
        return *this;                                                   \
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

//---

const sstd::terp::_v_iterator _v_begin(void* p_in){
    return _CAST2VEC(p_in).begin();
}
const sstd::terp::_v_iterator _v_end(void* p_in){
    return _CAST2VEC(p_in).end();
}
const sstd::terp::_h_iterator _h_begin(void* p_in){
    return _CAST2HASH(p_in).begin();
}
const sstd::terp::_h_iterator _h_end(void* p_in){
    return _CAST2HASH(p_in).end();
}
sstd::terp::iterator sstd::terp::var::begin() const {
    switch(_type){
    case sstd::num_vec_terp_var:  { return sstd::terp::iterator(_v_begin(_p)); } break;
    case sstd::num_hash_terp_var: { return sstd::terp::iterator(_h_begin(_p)); } break;
    case sstd::num_null:             {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return sstd::terp::iterator();
}
sstd::terp::iterator sstd::terp::var::end() const {
    switch(_type){
    case sstd::num_vec_terp_var:  { return sstd::terp::iterator(_v_end(_p)); } break;
    case sstd::num_hash_terp_var: { return sstd::terp::iterator(_h_end(_p)); } break;
    case sstd::num_null:             {} break;
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
    switch(_type){
    case sstd::num_vec_terp_var : { return _CAST2VEC (_p).size(); } break;
    case sstd::num_hash_terp_var: { return _CAST2HASH(_p).size(); } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
