#include "void_ptr.hpp"

#include "../definitions/typeNum.hpp"
#include "../print/pdbg.hpp"


//-----------------------------------------------------------------------------------------------------------------------------------------------
// constructors

sstd::void_ptr::void_ptr(): typeNumber(sstd::num_null), pData(NULL) {}
sstd::void_ptr::void_ptr(const class void_ptr& rhs){ // copy constructor
    this->pData      = NULL;
    this->typeNumber = sstd::num_null;
    sstd::void_ptr::copy(*this, rhs);
}
sstd::void_ptr::void_ptr(class void_ptr&& rhs){ // move constructor
    sstd::void_ptr::move(*this, std::move(rhs));
}

template <typename T> void sstd::void_ptr::_void_ptr(T* ptr){
    this->typeNumber = sstd::type2num(T());
    this->pData      = ptr;
}

sstd::void_ptr::void_ptr(          bool* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(          char* ptr){ _void_ptr(ptr); }
//sstd::void_ptr::void_ptr(      uchar* ptr){ _void_ptr(ptr); } // same as uint8
sstd::void_ptr::void_ptr(         int8 * ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(         int16* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(         int32* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(         int64* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(        uint8 * ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(        uint16* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(        uint32* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(        uint64* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(         float* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(        double* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(   std::string* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(sstd::void_ptr* ptr){ _void_ptr(ptr); }

sstd::void_ptr::void_ptr(std::vector<          bool>* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(std::vector<          char>* ptr){ _void_ptr(ptr); }
//sstd::void_ptr::void_ptr(std::vector<         uchar>* ptr){ _void_ptr(ptr); } // same as uint8
sstd::void_ptr::void_ptr(std::vector<         int8 >* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(std::vector<         int16>* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(std::vector<         int32>* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(std::vector<         int64>* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(std::vector<        uint8 >* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(std::vector<        uint16>* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(std::vector<        uint32>* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(std::vector<        uint64>* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(std::vector<         float>* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(std::vector<        double>* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(std::vector<   std::string>* ptr){ _void_ptr(ptr); }
sstd::void_ptr::void_ptr(std::vector<sstd::void_ptr>* ptr){ _void_ptr(ptr); }

sstd::void_ptr::void_ptr(std::unordered_map<std::string, std::string>* ptr){ _void_ptr(ptr); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// destructor

sstd::void_ptr::~void_ptr(){
    sstd::void_ptr::free(*this);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// member functions

template <typename T>
void sstd::void_ptr::_overwrite(T* ptr){
    sstd::void_ptr::free(*this);
    this->typeNumber = sstd::type2num(T());
    this->pData      = ptr;
}

void sstd::void_ptr::overwrite(          bool* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(          char* ptr){ _overwrite(ptr); }
//void sstd::void_ptr::overwrite(         uchar* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(         int8 * ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(         int16* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(         int32* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(         int64* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(        uint8 * ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(        uint16* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(        uint32* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(        uint64* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(         float* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(        double* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(   std::string* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(sstd::void_ptr* ptr){ _overwrite(ptr); }

void sstd::void_ptr::overwrite(std::vector<          bool>* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(std::vector<          char>* ptr){ _overwrite(ptr); }
//void sstd::void_ptr::overwrite(std::vector<         uchar>* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(std::vector<         int8 >* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(std::vector<         int16>* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(std::vector<         int32>* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(std::vector<         int64>* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(std::vector<        uint8 >* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(std::vector<        uint16>* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(std::vector<        uint32>* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(std::vector<        uint64>* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(std::vector<         float>* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(std::vector<        double>* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(std::vector<   std::string>* ptr){ _overwrite(ptr); }
void sstd::void_ptr::overwrite(std::vector<sstd::void_ptr>* ptr){ _overwrite(ptr); }

void sstd::void_ptr::overwrite(std::unordered_map<std::string, std::string>* ptr){ _overwrite(ptr); }

void sstd::void_ptr::copy(class void_ptr& lhs, const class void_ptr& rhs){
    sstd::void_ptr::free(lhs);
    
    lhs.typeNumber = rhs.typeNumber;
    if(rhs.pData==NULL){ lhs.pData=NULL; return; }
    
    switch (lhs.typeNumber){
        
    case sstd::num_bool    : { lhs.pData = new           bool(*(         bool *)rhs.pData); } break;
    case sstd::num_char    : { lhs.pData = new           char(*(         char *)rhs.pData); } break;
    case sstd::num_int8    : { lhs.pData = new          int8 (*(         int8 *)rhs.pData); } break;
    case sstd::num_int16   : { lhs.pData = new          int16(*(         int16*)rhs.pData); } break;
    case sstd::num_int32   : { lhs.pData = new          int32(*(         int32*)rhs.pData); } break;
    case sstd::num_int64   : { lhs.pData = new          int64(*(         int64*)rhs.pData); } break;
    case sstd::num_uint8   : { lhs.pData = new         uint8 (*(        uint8 *)rhs.pData); } break;
    case sstd::num_uint16  : { lhs.pData = new         uint16(*(        uint16*)rhs.pData); } break;
    case sstd::num_uint32  : { lhs.pData = new         uint32(*(        uint32*)rhs.pData); } break;
    case sstd::num_uint64  : { lhs.pData = new         uint64(*(        uint64*)rhs.pData); } break;
    case sstd::num_float   : { lhs.pData = new          float(*(         float*)rhs.pData); } break;
    case sstd::num_double  : { lhs.pData = new         double(*(        double*)rhs.pData); } break;
    case sstd::num_str     : { lhs.pData = new    std::string(*(   std::string*)rhs.pData); } break;
    case sstd::num_void_ptr: { lhs.pData = new sstd::void_ptr(*(sstd::void_ptr*)rhs.pData); } break;
        
    case sstd::num_vec_bool    : { lhs.pData = new std::vector<          bool>(*(std::vector<          bool>*)rhs.pData); } break;
    case sstd::num_vec_char    : { lhs.pData = new std::vector<          char>(*(std::vector<          char>*)rhs.pData); } break;
    case sstd::num_vec_int8    : { lhs.pData = new std::vector<         int8 >(*(std::vector<         int8 >*)rhs.pData); } break;
    case sstd::num_vec_int16   : { lhs.pData = new std::vector<         int16>(*(std::vector<         int16>*)rhs.pData); } break;
    case sstd::num_vec_int32   : { lhs.pData = new std::vector<         int32>(*(std::vector<         int32>*)rhs.pData); } break;
    case sstd::num_vec_int64   : { lhs.pData = new std::vector<         int64>(*(std::vector<         int64>*)rhs.pData); } break;
    case sstd::num_vec_uint8   : { lhs.pData = new std::vector<        uint8 >(*(std::vector<        uint8 >*)rhs.pData); } break;
    case sstd::num_vec_uint16  : { lhs.pData = new std::vector<        uint16>(*(std::vector<        uint16>*)rhs.pData); } break;
    case sstd::num_vec_uint32  : { lhs.pData = new std::vector<        uint32>(*(std::vector<        uint32>*)rhs.pData); } break;
    case sstd::num_vec_uint64  : { lhs.pData = new std::vector<        uint64>(*(std::vector<        uint64>*)rhs.pData); } break;
    case sstd::num_vec_float   : { lhs.pData = new std::vector<         float>(*(std::vector<         float>*)rhs.pData); } break;
    case sstd::num_vec_double  : { lhs.pData = new std::vector<        double>(*(std::vector<        double>*)rhs.pData); } break;
    case sstd::num_vec_str     : { lhs.pData = new std::vector<   std::string>(*(std::vector<   std::string>*)rhs.pData); } break;
    case sstd::num_vec_void_ptr: { lhs.pData = new std::vector<sstd::void_ptr>(*(std::vector<sstd::void_ptr>*)rhs.pData); } break;
        
    case sstd::num_hash_str_str   : { lhs.pData = new std::unordered_map<std::string,std::string>(*(std::unordered_map<std::string,std::string>*)rhs.pData); } break;
        
    default: { sstd::pdbg("ERROR: allocating memory is failed. typeNum '%d' is not defined.", lhs.typeNumber); } break;
        
    }
}
void sstd::void_ptr::free(class void_ptr& rhs){
    if(this->pData==NULL){ return; }
    
    switch (this->typeNumber){
    case sstd::num_bool    : { delete (          bool*)pData; } break;
    case sstd::num_char    : { delete (          char*)pData; } break;
    case sstd::num_int8    : { delete (         int8 *)pData; } break;
    case sstd::num_int16   : { delete (         int16*)pData; } break;
    case sstd::num_int32   : { delete (         int32*)pData; } break;
    case sstd::num_int64   : { delete (         int64*)pData; } break;
    case sstd::num_uint8   : { delete (        uint8 *)pData; } break;
    case sstd::num_uint16  : { delete (        uint16*)pData; } break;
    case sstd::num_uint32  : { delete (        uint32*)pData; } break;
    case sstd::num_uint64  : { delete (        uint64*)pData; } break;
    case sstd::num_float   : { delete (         float*)pData; } break;
    case sstd::num_double  : { delete (        double*)pData; } break;
    case sstd::num_str     : { delete (   std::string*)pData; } break;
    case sstd::num_void_ptr: { delete (sstd::void_ptr*)pData; } break;
    case sstd::num_vec_bool    : { delete (std::vector<          bool>*)pData; } break;
    case sstd::num_vec_char    : { delete (std::vector<          char>*)pData; } break;
    case sstd::num_vec_int8    : { delete (std::vector<         int8 >*)pData; } break;
    case sstd::num_vec_int16   : { delete (std::vector<         int16>*)pData; } break;
    case sstd::num_vec_int32   : { delete (std::vector<         int32>*)pData; } break;
    case sstd::num_vec_int64   : { delete (std::vector<         int64>*)pData; } break;
    case sstd::num_vec_uint8   : { delete (std::vector<        uint8 >*)pData; } break;
    case sstd::num_vec_uint16  : { delete (std::vector<        uint16>*)pData; } break;
    case sstd::num_vec_uint32  : { delete (std::vector<        uint32>*)pData; } break;
    case sstd::num_vec_uint64  : { delete (std::vector<        uint64>*)pData; } break;
    case sstd::num_vec_float   : { delete (std::vector<         float>*)pData; } break;
    case sstd::num_vec_double  : { delete (std::vector<        double>*)pData; } break;
    case sstd::num_vec_str     : { delete (std::vector<   std::string>*)pData; } break;
    case sstd::num_vec_void_ptr: { delete (std::vector<sstd::void_ptr>*)pData; } break;
    case sstd::num_hash_str_str: { delete (std::unordered_map<std::string,std::string>*)pData; } break;
    default: { sstd::pdbg("ERROR: free() memory is failed. typeNum '%d' is not defined.", this->typeNumber); } break;
    }

    this->pData=NULL;
}
void sstd::void_ptr::move(class void_ptr& lhs, class void_ptr&& rhs){
    lhs.typeNumber = rhs.typeNumber; rhs.typeNumber=sstd::num_null;
    lhs.pData      = rhs.pData;      rhs.pData=NULL;
}
void* sstd::void_ptr::ptr() const { return this->pData; }
uint sstd::void_ptr::typeNum() const { return this->typeNumber; }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// operators

class sstd::void_ptr& sstd::void_ptr::operator=(const sstd::void_ptr& rhs){
    sstd::void_ptr::copy(*this, rhs);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

