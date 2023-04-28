#include "terp.hpp"

#include "../../definitions/typeNum.hpp"
#include "../../print/pdbg.hpp"


//-----------------------------------------------------------------------------------------------------------------------------------------------
// for user

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for internal use

// cast
std::vector<sstd::void_ptr>*                    _cast2vec (void* rhs){ return (std::vector<sstd::void_ptr>*)rhs; }
std::unordered_map<std::string,sstd::void_ptr>* _cast2hash(void* rhs){ return (std::unordered_map<std::string,sstd::void_ptr>*)rhs; }

void sstd::terp::_to(std::string& dst, const sstd::void_ptr& src){ dst = (*(std::string*)src.ptr()); }
void sstd::terp::_to(std::string& dst, const std::string   & src){ dst =                 src       ; }

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
    default: { sstd::pdbg("ERROR"); }
    }
    return iterator();
}

//---

sstd::terp::var sstd::terp::iterator::second(){
    switch(_typeNum){
    case sstd::num_hash_str_void_ptr: {
        return sstd::terp::var((*_h_itr).second);
    } break;
    default: { sstd::pdbg("ERROR"); }
    }
    return sstd::terp::var();
}

//---

const bool sstd::terp::iterator::operator!=(const iterator& rhs) const {
    switch(_typeNum){
    case sstd::num_vec_void_ptr:      { return _v_itr != rhs._v_itr_R(); } break;
    case sstd::num_hash_str_void_ptr: { return _h_itr != rhs._h_itr_R(); } break;
    default: { sstd::pdbg("ERROR"); }
    }
    return false;
}

sstd::terp::iterator sstd::terp::iterator::operator++(){
    switch(_typeNum){
    case sstd::num_vec_void_ptr:      { ++_v_itr; } break;
    case sstd::num_hash_str_void_ptr: { ++_h_itr; } break;
    default: { sstd::pdbg("ERROR"); }
    }
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::var

// constructors
sstd::terp::var::var(){ _p = &_vp; }
sstd::terp::var::var(const var&  rhs){ _vp=*rhs.p(); _p=&_vp; }
sstd::terp::var::var(const sstd::void_ptr& vp_in){ _vp=vp_in; _p=&_vp; }
sstd::terp::var::var(      sstd::void_ptr*  p_in){ _p = p_in; }
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

sstd::terp::var _ope_subscript_idx_base(const sstd::void_ptr* _p, const int idx){
    switch((*_p).typeNum()){
    case sstd::num_vec_void_ptr: { sstd::void_ptr* p=(sstd::void_ptr*)&(*_cast2vec((*_p).ptr()))[idx]; return sstd::terp::var( p ); } break;
    default: { sstd::pdbg("ERROR"); } break;
    }
    return sstd::terp::var();
}
sstd::terp::var _ope_subscript_pKey_base(const sstd::void_ptr* _p, const char* pKey){
    switch((*_p).typeNum()){
    case sstd::num_hash_str_void_ptr: { sstd::void_ptr* p=(sstd::void_ptr*)&(*_cast2hash((*_p).ptr()))[pKey]; return sstd::terp::var( p ); } break;
    default: { sstd::pdbg("ERROR"); } break;
    }
    return sstd::terp::var();
}
sstd::terp::var sstd::terp::var::operator[](      int idx)       { return _ope_subscript_idx_base(_p, idx); }
sstd::terp::var sstd::terp::var::operator[](const int idx) const { return _ope_subscript_idx_base(_p, idx); }
//sstd::terp::var sstd::terp::var::operator[](const char* pKey)       { return _ope_subscript_pKey_base(_p, pKey); }
sstd::terp::var sstd::terp::var::operator[](const char* pKey) const { return _ope_subscript_pKey_base(_p, pKey); }

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
    default: { sstd::pdbg("ERROR"); }
    }
    return sstd::terp::iterator();
}
sstd::terp::iterator sstd::terp::var::end() const {
    switch((*_p).typeNum()){
    case sstd::num_vec_void_ptr:      { return sstd::terp::iterator(_v_end((*_p).ptr())); } break;
    case sstd::num_hash_str_void_ptr: { return sstd::terp::iterator(_h_end((*_p).ptr())); } break;
    case sstd::num_null:              {} break;
    default: { sstd::pdbg("ERROR"); }
    }
    return sstd::terp::iterator();
}

//---

uint sstd::terp::var::bucket_count(){
    switch((*_p).typeNum()){
    case sstd::num_hash_str_void_ptr: { return (*_cast2hash((*_p).ptr())).bucket_count(); } break;
    default: { sstd::pdbg("ERROR"); } break;
    }
    return 0;
}

//---

sstd::terp::iterator sstd::terp::var::erase(const sstd::terp::iterator& rhs){
    switch((*_p).typeNum()){
    case sstd::num_vec_void_ptr:      { return sstd::terp::iterator( _cast2vec((*_p).ptr())->erase(rhs._v_itr_R()) ); } break;
        //case sstd::num_hash_str_void_ptr: { return _cast2hash((*_p).ptr())->erase(pKey); } break;
    case sstd::num_null:              {} break;
    default: { sstd::pdbg("ERROR"); }
    }
    return sstd::terp::iterator();
}
uint sstd::terp::var::erase(const char* pKey){
    switch((*_p).typeNum()){
    case sstd::num_hash_str_void_ptr: { return _cast2hash((*_p).ptr())->erase(pKey); } break;
    case sstd::num_null:              {} break;
    default: { sstd::pdbg("ERROR"); }
    }
    return 0;
}

//---

sstd::terp::iterator sstd::terp::var::find(const char* pKey){
    switch((*_p).typeNum()){
    case sstd::num_hash_str_void_ptr: { return sstd::terp::iterator( _cast2hash((*_p).ptr())->find(pKey) ); } break;
    case sstd::num_null:              {} break;
    default: { sstd::pdbg("ERROR"); }
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
    default: { sstd::pdbg("ERROR"); }
    }
    return;
}

//---

void sstd::terp::var::push_back(const char* pRhs){
    if((*_p).typeNum()!=sstd::num_vec_void_ptr){ sstd::pdbg("ERROR"); return; }
    (*_cast2vec((*_p).ptr())).push_back(new std::string(pRhs));
}
void sstd::terp::var::push_back(const sstd::terp::var& rhs){
    if((*_p).typeNum()!=sstd::num_vec_void_ptr){ sstd::pdbg("ERROR"); return; }
    (*_cast2vec((*_p).ptr())).push_back(*rhs.p());
}

//---

void sstd::terp::var::resize(uint len){
    switch((*_p).typeNum()){
    case sstd::num_vec_void_ptr: { return (*_cast2vec((*_p).ptr())).resize( len ); } break;
    default: { sstd::pdbg("ERROR"); } break;
    }
}
    
//---

uint sstd::terp::var::size() const {
    switch((*_p).typeNum()){
    case sstd::num_vec_void_ptr     : { return (*_cast2vec ((*_p).ptr())).size(); } break;
    case sstd::num_hash_str_void_ptr: { return (*_cast2hash((*_p).ptr())).size(); } break;
    default: { sstd::pdbg("ERROR"); } break;
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

