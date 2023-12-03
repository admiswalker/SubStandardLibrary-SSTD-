#include "terp.hpp"

#include "../../definitions/typeNum.hpp"
#include "../../print/pdbg.hpp"
#include "../../string/ssprintf.hpp"


//-----------------------------------------------------------------------------------------------------------------------------------------------
// for internal use

// cast
std::string*                                    _cast2str (void* rhs){ return (                std::string*)rhs; }
std::vector<sstd::void_ptr>*                    _cast2vec (void* rhs){ return (std::vector<sstd::void_ptr>*)rhs; }
std::unordered_map<std::string,sstd::void_ptr>* _cast2hash(void* rhs){ return (std::unordered_map<std::string,sstd::void_ptr>*)rhs; }

#define STR (*(std::string*)src.ptr())
#define STR_V2 (*(std::string*)src.p())
void sstd::terp::_to(     bool  & dst, const sstd::void_ptr& src){
    if(STR=="true"||STR=="yes"||STR=="on"){
        dst = true;
    }else if(STR=="false"||STR=="no"||STR=="off"){
        dst = false;
    }else{
        sstd::pdbg_err("input string is not bool type.\n");
    }
}
void sstd::terp::_to(     char  & dst, const sstd::void_ptr& src){ dst = STR.size()>=1 ? STR[0] : 0; }
void sstd::terp::_to(     int8  & dst, const sstd::void_ptr& src){ dst = strtol(STR.c_str(), NULL, 10); }
void sstd::terp::_to(     int16 & dst, const sstd::void_ptr& src){ dst = strtol(STR.c_str(), NULL, 10); }
void sstd::terp::_to(     int32 & dst, const sstd::void_ptr& src){ dst = strtol(STR.c_str(), NULL, 10); }
void sstd::terp::_to(     int64 & dst, const sstd::void_ptr& src){ dst = strtoll(STR.c_str(), NULL, 10); }
void sstd::terp::_to(    uint8  & dst, const sstd::void_ptr& src){ dst = strtoul(STR.c_str(), NULL, 10); }
void sstd::terp::_to(    uint16 & dst, const sstd::void_ptr& src){ dst = strtoul(STR.c_str(), NULL, 10); }
void sstd::terp::_to(    uint32 & dst, const sstd::void_ptr& src){ dst = strtoul(STR.c_str(), NULL, 10); }
void sstd::terp::_to(    uint64 & dst, const sstd::void_ptr& src){ dst = strtoull(STR.c_str(), NULL, 10); }
void sstd::terp::_to(     float & dst, const sstd::void_ptr& src){ dst = strtof(STR.c_str(), NULL); }
void sstd::terp::_to(    double & dst, const sstd::void_ptr& src){ dst = strtod(STR.c_str(), NULL); }
void sstd::terp::_to(const char*& dst, const sstd::void_ptr& src){ dst = STR.c_str(); }
void sstd::terp::_to(std::string& dst, const sstd::void_ptr& src){ dst = STR; }
void sstd::terp::_to(std::string& dst, const std::string   & src){ dst = src; }

//---

void sstd::terp::_to_v2(     bool  & dst, const sstd::terp::var_v2& src){
    if(STR_V2=="true"||STR_V2=="yes"||STR_V2=="on"){
        dst = true;
    }else if(STR_V2=="false"||STR_V2=="no"||STR_V2=="off"){
        dst = false;
    }else{
        sstd::pdbg_err("input string is not bool type.\n");
    }
}
void sstd::terp::_to_v2(     char  & dst, const sstd::terp::var_v2& src){ dst = STR_V2.size()>=1 ? STR_V2[0] : 0; }
void sstd::terp::_to_v2(     int8  & dst, const sstd::terp::var_v2& src){ dst = strtol(STR_V2.c_str(), NULL, 10); }
void sstd::terp::_to_v2(     int16 & dst, const sstd::terp::var_v2& src){ dst = strtol(STR_V2.c_str(), NULL, 10); }
void sstd::terp::_to_v2(     int32 & dst, const sstd::terp::var_v2& src){ dst = strtol(STR_V2.c_str(), NULL, 10); }
void sstd::terp::_to_v2(     int64 & dst, const sstd::terp::var_v2& src){ dst = strtoll(STR_V2.c_str(), NULL, 10); }
void sstd::terp::_to_v2(    uint8  & dst, const sstd::terp::var_v2& src){ dst = strtoul(STR_V2.c_str(), NULL, 10); }
void sstd::terp::_to_v2(    uint16 & dst, const sstd::terp::var_v2& src){ dst = strtoul(STR_V2.c_str(), NULL, 10); }
void sstd::terp::_to_v2(    uint32 & dst, const sstd::terp::var_v2& src){ dst = strtoul(STR_V2.c_str(), NULL, 10); }
void sstd::terp::_to_v2(    uint64 & dst, const sstd::terp::var_v2& src){ dst = strtoull(STR_V2.c_str(), NULL, 10); }
void sstd::terp::_to_v2(     float & dst, const sstd::terp::var_v2& src){ dst = strtof(STR_V2.c_str(), NULL); }
void sstd::terp::_to_v2(    double & dst, const sstd::terp::var_v2& src){ dst = strtod(STR_V2.c_str(), NULL); }
void sstd::terp::_to_v2(const char*& dst, const sstd::terp::var_v2& src){ dst = STR_V2.c_str(); }
void sstd::terp::_to_v2(std::string& dst, const sstd::terp::var_v2& src){ dst = STR_V2; }
void sstd::terp::_to_v2(std::string& dst, const std::string       & src){ dst = src; }
#undef STR
#undef STR_V2

#define NULL_CHECK(p) if(p==NULL){ sstd::pdbg_err("NULL pointer is detected\n"); return; }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::iterator

// constructors
sstd::terp::iterator::iterator(): _typeNum(sstd::num_null) {}
sstd::terp::iterator::iterator(const _v_iterator& rhs){ _typeNum=sstd::num_vec_void_ptr;      _v_itr=rhs; }
sstd::terp::iterator::iterator(const _h_iterator& rhs){ _typeNum=sstd::num_hash_str_void_ptr; _h_itr=rhs; }
sstd::terp::iterator::~iterator(){}

//---

const sstd::terp::_v_iterator& sstd::terp::iterator::_v_itr_R() const { return _v_itr; }
const sstd::terp::_h_iterator& sstd::terp::iterator::_h_itr_R() const { return _h_itr; }

//---

sstd::terp::iterator sstd::terp::iterator::operator+(const int rhs){
    switch(_typeNum){
    case sstd::num_vec_void_ptr:      { return iterator( _v_itr + rhs ); } break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return iterator();
}

//---

sstd::terp::var sstd::terp::iterator::second(){
    switch(_typeNum){
    case sstd::num_hash_str_void_ptr: {
        return sstd::terp::var((*_h_itr).second);
    } break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return sstd::terp::var();
}

//---

const bool sstd::terp::iterator::operator!=(const iterator& rhs) const {
    switch(_typeNum){
    case sstd::num_vec_void_ptr:      { return _v_itr != rhs._v_itr_R(); } break;
    case sstd::num_hash_str_void_ptr: { return _h_itr != rhs._h_itr_R(); } break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return false;
}

sstd::terp::iterator sstd::terp::iterator::operator++(){
    switch(_typeNum){
    case sstd::num_vec_void_ptr:      { ++_v_itr; } break;
    case sstd::num_hash_str_void_ptr: { ++_h_itr; } break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return *this;
}

//---
// sstd::terp::iterator_v2

// constructors
sstd::terp::iterator_v2::iterator_v2(): _type(sstd::num_null) {}
sstd::terp::iterator_v2::iterator_v2(const _v_iterator_v2& rhs){ this->_type=sstd::num_vec_terp_var_v2;  _v_itr=rhs; }
sstd::terp::iterator_v2::iterator_v2(const _h_iterator_v2& rhs){ this->_type=sstd::num_hash_terp_var_v2; _h_itr=rhs; }
sstd::terp::iterator_v2::~iterator_v2(){}

//---

//const sstd::terp::_v_iterator_v2& sstd::terp::iterator_v2::_v_itr_R() const { return _v_itr; }
//const sstd::terp::_h_iterator_v2& sstd::terp::iterator_v2::_h_itr_R() const { return _h_itr; }
const sstd::terp::_v_iterator_v2& sstd::terp::iterator_v2::_v_itr_R() const { return _v_itr; }
const sstd::terp::_h_iterator_v2& sstd::terp::iterator_v2::_h_itr_R() const { return _h_itr; }

//---

sstd::terp::iterator_v2 sstd::terp::iterator_v2::operator+(const int rhs){
    switch(this->_type){
    case sstd::num_vec_terp_var_v2:      { return iterator_v2( _v_itr + rhs ); } break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return iterator_v2();
}

//---

sstd::terp::var_v2 sstd::terp::iterator_v2::second(){
    switch(this->_type){
    case sstd::num_hash_terp_var_v2: {
        return sstd::terp::var_v2((*_h_itr).second);
    } break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return sstd::terp::var_v2();
}

//---

const bool sstd::terp::iterator_v2::operator!=(const iterator_v2& rhs) const {
    switch(this->_type){
    case sstd::num_vec_terp_var_v2:  { return _v_itr != rhs._v_itr_R(); } break;
    case sstd::num_hash_terp_var_v2: { return _h_itr != rhs._h_itr_R(); } break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return false;
}

sstd::terp::iterator_v2 sstd::terp::iterator_v2::operator++(){
    switch(this->_type){
    case sstd::num_vec_terp_var_v2:  { ++_v_itr; } break;
    case sstd::num_hash_terp_var_v2: { ++_h_itr; } break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return *this;
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
sstd::terp::var::var(){ _p = &_vp; }
sstd::terp::var::var(const var&  rhs){ _vp=*rhs.p(); _p=&_vp; }
sstd::terp::var::var(const sstd::void_ptr& vp_in){ _vp=vp_in; _p=&_vp; }
sstd::terp::var::var(      sstd::void_ptr*  p_in){ _p = p_in; }
sstd::terp::var::var(      bool         rhs){ _p=&_vp; (*_p).overwrite(new std::string(rhs?"true":"false")); }
sstd::terp::var::var(      char         rhs){ _p=&_vp; (*_p).overwrite(new std::string({rhs})); }
sstd::terp::var::var(      int8         rhs){ _p=&_vp; (*_p).overwrite(new std::string(sstd::ssprintf("%d", rhs))); }
sstd::terp::var::var(      int16        rhs){ _p=&_vp; (*_p).overwrite(new std::string(sstd::ssprintf("%d", rhs))); }
sstd::terp::var::var(      int32        rhs){ _p=&_vp; (*_p).overwrite(new std::string(sstd::ssprintf("%d", rhs))); }
sstd::terp::var::var(      int64        rhs){ _p=&_vp; (*_p).overwrite(new std::string(sstd::ssprintf("%ld", rhs))); }
sstd::terp::var::var(     uint8         rhs){ _p=&_vp; (*_p).overwrite(new std::string(sstd::ssprintf("%u", rhs))); }
sstd::terp::var::var(     uint16        rhs){ _p=&_vp; (*_p).overwrite(new std::string(sstd::ssprintf("%u", rhs))); }
sstd::terp::var::var(     uint32        rhs){ _p=&_vp; (*_p).overwrite(new std::string(sstd::ssprintf("%u", rhs))); }
sstd::terp::var::var(     uint64        rhs){ _p=&_vp; (*_p).overwrite(new std::string(sstd::ssprintf("%lu", rhs))); }
sstd::terp::var::var(      float        rhs){ _p=&_vp; (*_p).overwrite(new std::string(sstd::ssprintf(_format(rhs).c_str(), rhs))); }
sstd::terp::var::var(     double        rhs){ _p=&_vp; (*_p).overwrite(new std::string(sstd::ssprintf(_format(rhs).c_str(), rhs))); }
sstd::terp::var::var(const char*        rhs){ _p=&_vp; (*_p).overwrite(new std::string(rhs)); }
sstd::terp::var::var(const std::string& rhs){ _p=&_vp; (*_p).overwrite(new std::string(rhs)); }
sstd::terp::var::~var(){}

//---

sstd::terp::var sstd::terp::var::operator=(const char* rhs){
    (*_p).overwrite(new std::string(rhs));
    return *this;
}
sstd::terp::var sstd::terp::var::operator=(const sstd::terp::var& rhs){
    *_p = *rhs.p();
    return *this;
}

//---

bool _is_equal(const sstd::terp::var& lhs, const sstd::terp::var& rhs); // forward declaration

bool _is_equal_list(const sstd::terp::var& lhs, const sstd::terp::var& rhs){
    if(lhs.size()!=rhs.size()){ return false; }
    
    for(uint i=0; i<lhs.size(); ++i){
        if(!_is_equal(lhs[i], rhs[i])){ return false; }
    }
    
    return true;
}
bool _is_equal_hash(const sstd::terp::var& lhs, const sstd::terp::var& rhs){
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
    if(lhs.typeNum()!=rhs.typeNum()){ return false; }
    
    switch(lhs.typeNum()){
    case sstd::num_str:               { return lhs.to<std::string>()==rhs.to<std::string>(); } break;
    case sstd::num_vec_void_ptr:      { return _is_equal_list(lhs, rhs); } break;
    case sstd::num_hash_str_void_ptr: { return _is_equal_hash(lhs, rhs); } break;
    case sstd::num_null:              { return true; } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }
    
    return false;
}
bool sstd::terp::var::operator==(const sstd::terp::var& rhs){ return  _is_equal(*this, rhs); }
bool sstd::terp::var::operator!=(const sstd::terp::var& rhs){ return !_is_equal(*this, rhs); }

//---

sstd::terp::var _ope_subscript_idx_base(const sstd::void_ptr* _p, const int idx){
    switch((*_p).typeNum()){
    case sstd::num_vec_void_ptr: { sstd::void_ptr* p=(sstd::void_ptr*)&(*_cast2vec((*_p).ptr()))[idx]; return sstd::terp::var( p ); } break;
    default: { sstd::pdbg_err("Ope[](char*) is failed. Unexpedted data type. sstd::terp::var takes \"sstd::terp::hash()\" type, but treat as a \"sstd::terp::list()\".\n"); } break;
    }
    return sstd::terp::var();
}
sstd::terp::var _ope_subscript_pKey_base(const sstd::void_ptr* _p, const char* pKey){
    switch((*_p).typeNum()){
    case sstd::num_hash_str_void_ptr: { sstd::void_ptr* p=(sstd::void_ptr*)&(*_cast2hash((*_p).ptr()))[pKey]; return sstd::terp::var( p ); } break;
    default: { sstd::pdbg_err("Ope[](char*) is failed. Unexpedted data type. sstd::terp::var takes \"sstd::terp::list()\" type, but treat as a \"sstd::terp::hash()\".\n"); } break;
    }
    return sstd::terp::var();
}
      sstd::terp::var sstd::terp::var::operator[](const int idx)       { return _ope_subscript_idx_base(_p, idx); }
const sstd::terp::var sstd::terp::var::operator[](const int idx) const { return _ope_subscript_idx_base(_p, idx); }
      sstd::terp::var sstd::terp::var::operator[](const char* pKey)       { return _ope_subscript_pKey_base(_p, pKey); }
const sstd::terp::var sstd::terp::var::operator[](const char* pKey) const { return _ope_subscript_pKey_base(_p, pKey); }

//---

const sstd::terp::_v_iterator _v_begin(void* p_in){
    std::vector<sstd::void_ptr>* p = _cast2vec(p_in);
    return (*p).begin();
}
const sstd::terp::_v_iterator _v_end(void* p_in){
    std::vector<sstd::void_ptr>* p = _cast2vec(p_in);
    return (*p).end();
}
const sstd::terp::_h_iterator _h_begin(void* p_in){
    std::unordered_map<std::string,sstd::void_ptr>* p = _cast2hash(p_in);
    return (*p).begin();
}
const sstd::terp::_h_iterator _h_end(void* p_in){
    std::unordered_map<std::string,sstd::void_ptr>* p = _cast2hash(p_in);
    return (*p).end();
}
sstd::terp::iterator sstd::terp::var::begin() const {
    switch((*_p).typeNum()){
    case sstd::num_vec_void_ptr:      { return sstd::terp::iterator(_v_begin((*_p).ptr())); } break;
    case sstd::num_hash_str_void_ptr: { return sstd::terp::iterator(_h_begin((*_p).ptr())); } break;
    case sstd::num_null:              {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return sstd::terp::iterator();
}
sstd::terp::iterator sstd::terp::var::end() const {
    switch((*_p).typeNum()){
    case sstd::num_vec_void_ptr:      { return sstd::terp::iterator(_v_end((*_p).ptr())); } break;
    case sstd::num_hash_str_void_ptr: { return sstd::terp::iterator(_h_end((*_p).ptr())); } break;
    case sstd::num_null:              {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return sstd::terp::iterator();
}

//---

uint sstd::terp::var::bucket_count(){
    switch((*_p).typeNum()){
    case sstd::num_hash_str_void_ptr: { return (*_cast2hash((*_p).ptr())).bucket_count(); } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }
    return 0;
}

//---

sstd::terp::iterator sstd::terp::var::erase(const sstd::terp::iterator& rhs){
    switch((*_p).typeNum()){
    case sstd::num_vec_void_ptr:      { return sstd::terp::iterator( _cast2vec((*_p).ptr())->erase(rhs._v_itr_R()) ); } break;
        //case sstd::num_hash_str_void_ptr: { return _cast2hash((*_p).ptr())->erase(pKey); } break;
    case sstd::num_null:              {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return sstd::terp::iterator();
}
uint sstd::terp::var::erase(const char* pKey){
    switch((*_p).typeNum()){
    case sstd::num_hash_str_void_ptr: { return _cast2hash((*_p).ptr())->erase(pKey); } break;
    case sstd::num_null:              {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return 0;
}

//---

sstd::terp::iterator sstd::terp::var::find(const char* pKey) const {
    switch((*_p).typeNum()){
    case sstd::num_hash_str_void_ptr: { return sstd::terp::iterator( _cast2hash((*_p).ptr())->find(pKey) ); } break;
    case sstd::num_null:              {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return sstd::terp::iterator();
}

//---

sstd::void_ptr* sstd::terp::var::p() const { return _p; }

//---

void sstd::terp::var::pop_back(){
    NULL_CHECK(_p);
    switch((*_p).typeNum()){
    case sstd::num_vec_void_ptr: { if(_cast2vec((*_p).ptr())->size()==0){return;} _cast2vec((*_p).ptr())->pop_back(); return; } break;
    case sstd::num_null:         {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return;
}

//---

void sstd::terp::var::push_back(const char* pRhs){
    NULL_CHECK(_p);
    if((*_p).typeNum()!=sstd::num_vec_void_ptr){ sstd::pdbg_err("push_back(char*) is failed. Unexpedted data type. This function requires sstd::num_vec_void_ptr type, but takes %s type.\n", sstd::typeNum2str((*_p).typeNum()).c_str()); return; }
    (*_cast2vec((*_p).ptr())).push_back(new std::string(pRhs));
}
void sstd::terp::var::push_back(const sstd::terp::var& rhs){
    NULL_CHECK(_p);
    if((*_p).typeNum()!=sstd::num_vec_void_ptr){ sstd::pdbg_err("push_back(var&) is failed. Unexpedted data type. This function requires sstd::num_vec_void_ptr type, but takes %s type.\n", sstd::typeNum2str((*_p).typeNum()).c_str()); return; }
    (*_cast2vec((*_p).ptr())).push_back(*rhs.p());
}
void sstd::terp::var::push_back(      sstd::terp::var&& rhs){
    NULL_CHECK(_p);
    if((*_p).typeNum()!=sstd::num_vec_void_ptr){ sstd::pdbg_err("push_back(var&) is failed. Unexpedted data type. This function requires sstd::num_vec_void_ptr type, but takes %s type.\n", sstd::typeNum2str((*_p).typeNum()).c_str()); return; }
    (*_cast2vec((*_p).ptr())).push_back(std::move(*rhs.p())); // call move constructor of "sstd::void_ptr::void_ptr()"
}

//---

void sstd::terp::var::resize(uint len){
    switch((*_p).typeNum()){
    case sstd::num_vec_void_ptr: { return (*_cast2vec((*_p).ptr())).resize( len ); } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }
}
    
//---

uint sstd::terp::var::size() const {
    switch((*_p).typeNum()){
    case sstd::num_vec_void_ptr     : { return (*_cast2vec ((*_p).ptr())).size(); } break;
    case sstd::num_hash_str_void_ptr: { return (*_cast2hash((*_p).ptr())).size(); } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }
    return 0;
}

//---

uint sstd::terp::var::typeNum() const {
    return (*_p).typeNum();
}
std::string sstd::terp::var::typeStr() const {
    return sstd::typeNum2str((*_p).typeNum());
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::hash

sstd::terp::var sstd::terp::hash(uint allocate_size){
    sstd::terp::var r;
    r.p()->overwrite(new std::unordered_map<std::string, sstd::void_ptr>(allocate_size));
    return r;
}
sstd::terp::var sstd::terp::hash(){ return sstd::terp::hash(0); }

//---

sstd::terp::var_v2 sstd::terp::hash_v2(uint allocate_size){
    sstd::terp::var_v2 r;
    r.type_RW() = num_hash_terp_var_v2;
    r.p_RW()    = new std::unordered_map<std::string, sstd::void_ptr>(allocate_size);
    return r;
}
sstd::terp::var_v2 sstd::terp::hash_v2(){ return sstd::terp::hash_v2(0); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::list

sstd::terp::var sstd::terp::list(uint allocate_size){
    sstd::terp::var r;
    r.p()->overwrite(new std::vector<sstd::void_ptr>(allocate_size));
    return r;
}
sstd::terp::var sstd::terp::list(){ return sstd::terp::list(0); }

//---

sstd::terp::var_v2 sstd::terp::list_v2(uint allocate_size){
    sstd::terp::var_v2 r;
    r.type_RW() = num_vec_terp_var_v2;
    r.p_RW()    = new std::vector<sstd::terp::var_v2>(allocate_size);
    return r;
}
sstd::terp::var_v2 sstd::terp::list_v2(){
    sstd::terp::var_v2 r;
    r.type_RW() = num_vec_terp_var_v2;
    r.p_RW()    = new std::vector<sstd::terp::var_v2>();
    return r;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// type check

bool sstd::terp::isHash (const sstd::terp::var& rhs){
    return ( rhs.typeNum()==sstd::num_hash_str_void_ptr || rhs.typeNum()==sstd::num_hash_void_ptr_void_ptr );
}
bool sstd::terp::isList (const sstd::terp::var& rhs){
    return rhs.typeNum()==sstd::num_vec_void_ptr;
}
bool sstd::terp::isNull (const sstd::terp::var& rhs){
    return rhs.typeNum()==sstd::num_null;
}
bool sstd::terp::isValue(const sstd::terp::var& rhs){
    return rhs.typeNum()==sstd::num_str;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::var_v2

// constructors
sstd::terp::var_v2::var_v2():                         _type(sstd::num_null), _p(NULL) {}
sstd::terp::var_v2::var_v2(const class var_v2&  rhs): _type(sstd::num_null), _p(NULL) { copy(rhs); }
sstd::terp::var_v2::var_v2(      class var_v2&& rhs): _type(sstd::num_null), _p(NULL) { free(); move(std::move(rhs)); }
sstd::terp::var_v2::var_v2(        bool         rhs){ _type=sstd::num_str; _p=new std::string(rhs?"true":"false"); }
sstd::terp::var_v2::var_v2(        char         rhs){ _type=sstd::num_str; _p=new std::string({rhs}); }
sstd::terp::var_v2::var_v2(        int8         rhs){ _type=sstd::num_str; _p=new std::string(sstd::ssprintf("%d", rhs)); }
sstd::terp::var_v2::var_v2(        int16        rhs){ _type=sstd::num_str; _p=new std::string(sstd::ssprintf("%d", rhs)); }
sstd::terp::var_v2::var_v2(        int32        rhs){ _type=sstd::num_str; _p=new std::string(sstd::ssprintf("%d", rhs)); }
sstd::terp::var_v2::var_v2(        int64        rhs){ _type=sstd::num_str; _p=new std::string(sstd::ssprintf("%ld", rhs)); }
sstd::terp::var_v2::var_v2(       uint8         rhs){ _type=sstd::num_str; _p=new std::string(sstd::ssprintf("%u", rhs)); }
sstd::terp::var_v2::var_v2(       uint16        rhs){ _type=sstd::num_str; _p=new std::string(sstd::ssprintf("%u", rhs)); }
sstd::terp::var_v2::var_v2(       uint32        rhs){ _type=sstd::num_str; _p=new std::string(sstd::ssprintf("%u", rhs)); }
sstd::terp::var_v2::var_v2(       uint64        rhs){ _type=sstd::num_str; _p=new std::string(sstd::ssprintf("%lu", rhs)); }
sstd::terp::var_v2::var_v2(        float        rhs){ _type=sstd::num_str; _p=new std::string(sstd::ssprintf(_format(rhs).c_str(), rhs)); }
sstd::terp::var_v2::var_v2(       double        rhs){ _type=sstd::num_str; _p=new std::string(sstd::ssprintf(_format(rhs).c_str(), rhs)); }
sstd::terp::var_v2::var_v2(const char*        rhs): _type(sstd::num_str), _p(new std::string(rhs)) {}
//sstd::terp::var_v2::var_v2(const std::string& rhs){ _p=&_vp; (*_p).overwrite(new std::string(rhs)); }

sstd::terp::var_v2::~var_v2(){ sstd::terp::var_v2::free(); }

//---
/*
void sstd::terp::var_v2::list_v2(uint allocate_size){
    printf("in l\n");
    sstd::terp::var_v2::free();
        printf("in l2\n");
    this->_p    = new std::vector<sstd::terp::var_v2>(allocate_size);
    this->_type = num_vec_terp_var_v2;
}
void sstd::terp::var_v2::list_v2(){
    sstd::terp::var_v2::free();
    this->_p    = new std::vector<sstd::terp::var_v2>();
    this->_type = num_vec_terp_var_v2;
}
*/
//---
// internal

void* sstd::terp::var_v2::p() const { return this->_p; }
uint sstd::terp::var_v2::type() const { return this->_type; }
void*& sstd::terp::var_v2::p_RW(){ return this->_p; }
uint & sstd::terp::var_v2::type_RW(){ return this->_type; }

//---
// common

void sstd::terp::var_v2::copy(const class sstd::terp::var_v2& rhs){
    printf("in copy\n");
    sstd::terp::var_v2::free();
    
    this->_type = rhs.type();
    if(rhs.p()==NULL){ this->_p=NULL; return; }
    printf("in copy 479\n");
    switch (this->_type){
    case sstd::num_null    : {} break;
        
    case sstd::num_bool    : { this->_p = new           bool(*(         bool *)rhs.p()); } break;
    case sstd::num_char    : { this->_p = new           char(*(         char *)rhs.p()); } break;
    case sstd::num_int8    : { this->_p = new          int8 (*(         int8 *)rhs.p()); } break;
    case sstd::num_int16   : { this->_p = new          int16(*(         int16*)rhs.p()); } break;
    case sstd::num_int32   : { this->_p = new          int32(*(         int32*)rhs.p()); } break;
    case sstd::num_int64   : { this->_p = new          int64(*(         int64*)rhs.p()); } break;
    case sstd::num_uint8   : { this->_p = new         uint8 (*(        uint8 *)rhs.p()); } break;
    case sstd::num_uint16  : { this->_p = new         uint16(*(        uint16*)rhs.p()); } break;
    case sstd::num_uint32  : { this->_p = new         uint32(*(        uint32*)rhs.p()); } break;
    case sstd::num_uint64  : { this->_p = new         uint64(*(        uint64*)rhs.p()); } break;
    case sstd::num_float   : { this->_p = new          float(*(         float*)rhs.p()); } break;
    case sstd::num_double  : { this->_p = new         double(*(        double*)rhs.p()); } break;
    case sstd::num_str     : { this->_p = new    std::string(*(   std::string*)rhs.p()); } break;
    case sstd::num_void_ptr: { this->_p = new sstd::void_ptr(*(sstd::void_ptr*)rhs.p()); } break;
        
    case sstd::num_vec_bool    : { this->_p = new std::vector<          bool>(*(std::vector<          bool>*)rhs.p()); } break;
    case sstd::num_vec_char    : { this->_p = new std::vector<          char>(*(std::vector<          char>*)rhs.p()); } break;
    case sstd::num_vec_int8    : { this->_p = new std::vector<         int8 >(*(std::vector<         int8 >*)rhs.p()); } break;
    case sstd::num_vec_int16   : { this->_p = new std::vector<         int16>(*(std::vector<         int16>*)rhs.p()); } break;
    case sstd::num_vec_int32   : { this->_p = new std::vector<         int32>(*(std::vector<         int32>*)rhs.p()); } break;
    case sstd::num_vec_int64   : { this->_p = new std::vector<         int64>(*(std::vector<         int64>*)rhs.p()); } break;
    case sstd::num_vec_uint8   : { this->_p = new std::vector<        uint8 >(*(std::vector<        uint8 >*)rhs.p()); } break;
    case sstd::num_vec_uint16  : { this->_p = new std::vector<        uint16>(*(std::vector<        uint16>*)rhs.p()); } break;
    case sstd::num_vec_uint32  : { this->_p = new std::vector<        uint32>(*(std::vector<        uint32>*)rhs.p()); } break;
    case sstd::num_vec_uint64  : { this->_p = new std::vector<        uint64>(*(std::vector<        uint64>*)rhs.p()); } break;
    case sstd::num_vec_float   : { this->_p = new std::vector<         float>(*(std::vector<         float>*)rhs.p()); } break;
    case sstd::num_vec_double  : { this->_p = new std::vector<        double>(*(std::vector<        double>*)rhs.p()); } break;
    case sstd::num_vec_str     : { this->_p = new std::vector<   std::string>(*(std::vector<   std::string>*)rhs.p()); } break;
    case sstd::num_vec_void_ptr: { this->_p = new std::vector<sstd::void_ptr>(*(std::vector<sstd::void_ptr>*)rhs.p()); } break;
        
    case sstd::num_hash_str_str          : { this->_p = new std::unordered_map<std::string,      std::string>(*(std::unordered_map<std::string,      std::string>*)rhs.p()); } break;
    case sstd::num_hash_str_void_ptr     : { this->_p = new std::unordered_map<std::string,   sstd::void_ptr>(*(std::unordered_map<std::string,   sstd::void_ptr>*)rhs.p()); } break;
//    case sstd::num_hash_void_ptr_void_ptr: { this->_p = new std::unordered_map<sstd::void_ptr,sstd::void_ptr>(*(std::unordered_map<sstd::void_ptr,sstd::void_ptr>*)rhs.p()); } break;
        
    case sstd::num_vec_terp_var_v2:  { this->_p = new std::vector<sstd::terp::var_v2>(*(std::vector<sstd::terp::var_v2>*)rhs.p()); } break;
    case sstd::num_hash_terp_var_v2: { this->_p = new std::unordered_map<std::string,sstd::terp::var_v2>(*(std::unordered_map<std::string,sstd::terp::var_v2>*)rhs.p()); } break;
       
    default: { sstd::pdbg("ERROR: allocating memory is failed. typeNum '%d' is not defined.", this->_type); } break;
        
    }
    printf("out copy\n");
}

void sstd::terp::var_v2::move(      class sstd::terp::var_v2&& rhs){
    this->_type = rhs.type(); rhs.type_RW() = sstd::num_null;
    this->_p    = rhs.p();    rhs.p_RW()    = NULL;
}

void sstd::terp::var_v2::free(){
        printf("in free\n");
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
    case sstd::num_void_ptr: { delete (sstd::void_ptr*)_p; } break;
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
    case sstd::num_vec_void_ptr: { delete (std::vector<sstd::void_ptr>*)_p; } break;
    case sstd::num_hash_str_str          : { delete (std::unordered_map<std::string,      std::string>*)_p; } break;
    case sstd::num_hash_str_void_ptr     : { delete (std::unordered_map<std::string,   sstd::void_ptr>*)_p; } break;
//    case sstd::num_hash_void_ptr_void_ptr: { delete (std::unordered_map<sstd::void_ptr,sstd::void_ptr>*)_p; } break;
    case sstd::num_vec_terp_var_v2: { delete (std::vector<sstd::terp::var_v2>*)_p; } break;
    case sstd::num_hash_terp_var_v2: { delete (std::unordered_map<std::string,sstd::terp::var_v2>*)_p; } break;
    default: { sstd::pdbg("ERROR: free() memory is failed. typeNum '%d' is not defined.", this->_type); } break;
    }

    this->_p=NULL;
}

sstd::terp::var_v2& sstd::terp::var_v2::operator=(const sstd::terp::var_v2& rhs){
    printf("in ope=\n");
    copy(rhs);
    printf("out ope=\n");
    return *this;
}

template <typename T>
void sstd::terp::var_v2::_overwrite(T* ptr){
    sstd::terp::var_v2::free();
    this->_type = sstd::type2num(T());
    this->_p    = ptr;
}
sstd::terp::var_v2& sstd::terp::var_v2::operator=(const char* rhs){
    _overwrite(new std::string(rhs));
    return *this;
}

bool _is_equal_v2(const sstd::terp::var_v2& lhs, const sstd::terp::var_v2& rhs); // forward declaration
bool _is_equal_list_v2(const sstd::terp::var_v2& lhs, const sstd::terp::var_v2& rhs){
    if(lhs.size()!=rhs.size()){ return false; }
    
    for(uint i=0; i<lhs.size(); ++i){
        if(!_is_equal_v2(lhs[i], rhs[i])){ return false; }
    }
    
    return true;
}
bool _is_equal_hash_v2(const sstd::terp::var_v2& lhs, const sstd::terp::var_v2& rhs){
    if(lhs.size()!=rhs.size()){ return false; }

    for(auto itr=lhs.begin(); itr!=lhs.end(); ++itr){
        std::string key = itr.first_to<std::string>();
        
        auto itr_rhs = rhs.find(key.c_str());
        if(!(itr_rhs!=rhs.end())){ return false; }

        if(!_is_equal_v2(itr.second(), itr_rhs.second())){ return false; }
    }
    
    return true;
}
bool _is_equal_v2(const sstd::terp::var_v2& lhs, const sstd::terp::var_v2& rhs){
    if(lhs.type()!=rhs.type()){ return false; }
    
    switch(lhs.typeNum()){
    case sstd::num_str:              { return lhs.to<std::string>()==rhs.to<std::string>(); } break;
    case sstd::num_vec_terp_var_v2:  { return _is_equal_list_v2(lhs, rhs); } break;
    case sstd::num_hash_terp_var_v2: { return _is_equal_hash_v2(lhs, rhs); } break;
    case sstd::num_null:             { return true; } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }
    
    return false;
}
bool sstd::terp::var_v2::operator==(const sstd::terp::var_v2& rhs){ return  _is_equal_v2(*this, rhs); }
bool sstd::terp::var_v2::operator!=(const sstd::terp::var_v2& rhs){ return !_is_equal_v2(*this, rhs); }

#define _CAST2VEC(_P) (*(std::vector<sstd::terp::var_v2>*)_P)
#define _CAST2HASH(_P) (*(std::unordered_map<std::string,sstd::terp::var_v2>*)_P)

#define _OPE_SUBSCRIPT_IDX_BASE()                                       \
    switch(_type){                                                      \
    case sstd::num_vec_terp_var_v2: { return _CAST2VEC(this->_p)[idx]; } break; \
    default: { sstd::pdbg_err("Ope[](char*) is failed. Unexpedted data type. sstd::terp::var takes \"sstd::terp::hash()\" type, but treat as a \"sstd::terp::list()\".\n"); } break; \
    }                                                                   \
    return *this;
#define _OPE_SUBSCRIPT_KEY_BASE()                                       \
    switch(_type){                                                      \
    case sstd::num_hash_terp_var_v2: { return _CAST2HASH(_p)[pKey]; } break; \
    default: { sstd::pdbg_err("Ope[](char*) is failed. Unexpedted data type. sstd::terp::var takes \"sstd::terp::list()\" type, but treat as a \"sstd::terp::hash()\".\n"); } break; \
    }                                                                   \
    return *this;
      sstd::terp::var_v2& sstd::terp::var_v2::operator[](const   int  idx)       { _OPE_SUBSCRIPT_IDX_BASE(); }
const sstd::terp::var_v2& sstd::terp::var_v2::operator[](const   int  idx) const { _OPE_SUBSCRIPT_IDX_BASE(); }
      sstd::terp::var_v2& sstd::terp::var_v2::operator[](const char* pKey)       { _OPE_SUBSCRIPT_KEY_BASE(); }
const sstd::terp::var_v2& sstd::terp::var_v2::operator[](const char* pKey) const { _OPE_SUBSCRIPT_KEY_BASE(); }

//---

const sstd::terp::_v_iterator_v2 _v_begin_v2(void* p_in){
    return _CAST2VEC(p_in).begin();
}
const sstd::terp::_v_iterator_v2 _v_end_v2(void* p_in){
    return _CAST2VEC(p_in).end();
}
const sstd::terp::_h_iterator_v2 _h_begin_v2(void* p_in){
    return _CAST2HASH(p_in).begin();
}
const sstd::terp::_h_iterator_v2 _h_end_v2(void* p_in){
    return _CAST2HASH(p_in).end();
}
sstd::terp::iterator_v2 sstd::terp::var_v2::begin() const {
    switch(_type){
    case sstd::num_vec_terp_var_v2:  { return sstd::terp::iterator_v2(_v_begin_v2(_p)); } break;
    case sstd::num_hash_terp_var_v2: { return sstd::terp::iterator_v2(_h_begin_v2(_p)); } break;
    case sstd::num_null:             {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return sstd::terp::iterator_v2();
}
sstd::terp::iterator_v2 sstd::terp::var_v2::end() const {
    switch(_type){
    case sstd::num_vec_terp_var_v2:  { return sstd::terp::iterator_v2(_v_end_v2(_p)); } break;
    case sstd::num_hash_terp_var_v2: { return sstd::terp::iterator_v2(_h_end_v2(_p)); } break;
    case sstd::num_null:             {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return sstd::terp::iterator_v2();
}

//---

uint sstd::terp::var_v2::typeNum() const { return this->_type; }
std::string sstd::terp::var_v2::typeStr() const { return sstd::typeNum2str(_type); }

//---
// for hash type

uint sstd::terp::var_v2::bucket_count(){
    switch(_type){
    case sstd::num_hash_terp_var_v2: { return _CAST2HASH(_p).bucket_count(); } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }
    return 0;
}

//---

sstd::terp::iterator_v2 sstd::terp::var_v2::erase(const sstd::terp::iterator_v2& rhs){
    switch(_type){
    case sstd::num_vec_terp_var_v2:  { return sstd::terp::iterator_v2( _CAST2VEC(_p).erase(rhs._v_itr_R()) ); } break;
    case sstd::num_null:             {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return sstd::terp::iterator_v2();
}
uint sstd::terp::var_v2::erase(const char* pKey){
    switch(_type){
    case sstd::num_hash_terp_var_v2: { return _CAST2HASH(_p).erase(pKey); } break;
    case sstd::num_null:             {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return 0;
}

//---

sstd::terp::iterator_v2 sstd::terp::var_v2::find(const char* pKey) const {
    switch(_type){
    case sstd::num_hash_terp_var_v2: { return sstd::terp::iterator_v2( _CAST2HASH(_p).find(pKey) ); } break;
    case sstd::num_null:             {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return sstd::terp::iterator_v2();
}

//---
// for list type

void sstd::terp::var_v2::pop_back(){
    NULL_CHECK(_p);
    switch(_type){
    case sstd::num_vec_terp_var_v2: { if(_CAST2VEC(this->_p).size()==0){return;} _CAST2VEC(this->_p).pop_back(); return; } break;
    case sstd::num_null:            {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return;
}

void sstd::terp::var_v2::push_back(const char* pRhs){
    NULL_CHECK(_p);
    if(_type!=sstd::num_vec_terp_var_v2){ sstd::pdbg_err("push_back(char*) is failed. Unexpedted data type. This function requires sstd::num_vec_void_ptr type, but takes %s type.\n", sstd::typeNum2str(this->_type).c_str()); return; }
    _CAST2VEC(_p).push_back(sstd::terp::var_v2(pRhs));
}
void sstd::terp::var_v2::push_back(const sstd::terp::var_v2& rhs){
    NULL_CHECK(_p);
    if(_type!=sstd::num_vec_terp_var_v2){ sstd::pdbg_err("push_back(var&) is failed. Unexpedted data type. This function requires sstd::num_vec_void_ptr type, but takes %s type.\n", sstd::typeNum2str(this->_type).c_str()); return; }
    _CAST2VEC(_p).push_back(rhs);
}
void sstd::terp::var_v2::push_back(      sstd::terp::var_v2&& rhs){
    NULL_CHECK(_p);
    if(_type!=sstd::num_vec_terp_var_v2){ sstd::pdbg_err("push_back(var&) is failed. Unexpedted data type. This function requires sstd::num_vec_void_ptr type, but takes %s type.\n", sstd::typeNum2str(this->_type).c_str()); return; }
    _CAST2VEC(_p).push_back(std::move(rhs)); // call move constructor of "sstd::void_ptr::void_ptr()"
}

void sstd::terp::var_v2::resize(uint len){
    switch(_type){
    case sstd::num_vec_terp_var_v2: { _CAST2VEC(_p).resize( len ); } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }
}

uint sstd::terp::var_v2::size() const {
    switch(_type){
    case sstd::num_vec_terp_var_v2 : { return _CAST2VEC (_p).size(); } break;
    case sstd::num_hash_terp_var_v2: { return _CAST2HASH(_p).size(); } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
