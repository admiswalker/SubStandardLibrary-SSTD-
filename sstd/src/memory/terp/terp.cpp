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
#undef STR

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
    switch((*_p).typeNum()){
    case sstd::num_vec_void_ptr: { _cast2vec((*_p).ptr())->pop_back(); return; } break;
    case sstd::num_null:         {} break;
    default: { sstd::pdbg_err("ERROR\n"); }
    }
    return;
}

//---

void sstd::terp::var::push_back(const char* pRhs){
    if((*_p).typeNum()!=sstd::num_vec_void_ptr){ sstd::pdbg_err("push_back(char*) is failed. Unexpedted data type. This function requires sstd::num_vec_void_ptr type, but takes %s type.\n", sstd::typeNum2str((*_p).typeNum()).c_str()); return; }
    (*_cast2vec((*_p).ptr())).push_back(new std::string(pRhs));
}
void sstd::terp::var::push_back(const sstd::terp::var& rhs){
    if((*_p).typeNum()!=sstd::num_vec_void_ptr){ sstd::pdbg_err("push_back(var&) is failed. Unexpedted data type. This function requires sstd::num_vec_void_ptr type, but takes %s type.\n", sstd::typeNum2str((*_p).typeNum()).c_str()); return; }
    (*_cast2vec((*_p).ptr())).push_back(*rhs.p());
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
    return std::string();//sstd::type((*_p).typeNum());
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::list

sstd::terp::var sstd::terp::list(uint allocate_size){
    sstd::terp::var r;
    r.p()->overwrite(new std::vector<sstd::void_ptr>(allocate_size));
    return r;
}
sstd::terp::var sstd::terp::list(){ return sstd::terp::list(0); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::hash

sstd::terp::var sstd::terp::hash(uint allocate_size){
    sstd::terp::var r;
    r.p()->overwrite(new std::unordered_map<std::string, sstd::void_ptr>(allocate_size));
    return r;
}
sstd::terp::var sstd::terp::hash(){ return sstd::terp::hash(0); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
