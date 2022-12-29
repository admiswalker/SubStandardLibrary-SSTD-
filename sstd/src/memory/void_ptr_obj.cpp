#include "void_ptr_obj.hpp"

#include "../definitions/typeNum.hpp"
#include "../print/pdbg.hpp"


//-----------------------------------------------------------------------------------------------------------------------------------------------
// constructors

sstd::void_ptr_obj::void_ptr_obj(): typeNumber(sstd::num_null), pData(NULL) {}
sstd::void_ptr_obj::void_ptr_obj(const class void_ptr_obj& rhs){ // copy constructor
    sstd::void_ptr_obj::copy(*this, rhs);
}
sstd::void_ptr_obj::void_ptr_obj(class void_ptr_obj&& rhs){ // move constructor
    sstd::void_ptr_obj::move(*this, std::move(rhs));
}


#define SSTD_DEF_void_ptr_obj(Type)                           \
    sstd::void_ptr_obj::void_ptr_obj(Type* ptr){              \
        this->typeNumber = sstd::type2num(Type());            \
        this->pData      = ptr;                               \
    }

SSTD_DEF_void_ptr_obj(       bool);
SSTD_DEF_void_ptr_obj(       char);
//SSTD_DEF_void_ptr_obj(      uchar);
SSTD_DEF_void_ptr_obj(      int8 );
SSTD_DEF_void_ptr_obj(      int16);
SSTD_DEF_void_ptr_obj(      int32);
SSTD_DEF_void_ptr_obj(      int64);
SSTD_DEF_void_ptr_obj(     uint8 );
SSTD_DEF_void_ptr_obj(     uint16);
SSTD_DEF_void_ptr_obj(     uint32);
SSTD_DEF_void_ptr_obj(     uint64);
SSTD_DEF_void_ptr_obj(      float);
SSTD_DEF_void_ptr_obj(     double);
SSTD_DEF_void_ptr_obj(std::string);

SSTD_DEF_void_ptr_obj(std::vector<       bool>);
SSTD_DEF_void_ptr_obj(std::vector<       char>);
//SSTD_DEF_void_ptr_obj(std::vector<      uchar>);
SSTD_DEF_void_ptr_obj(std::vector<      int8 >);
SSTD_DEF_void_ptr_obj(std::vector<      int16>);
SSTD_DEF_void_ptr_obj(std::vector<      int32>);
SSTD_DEF_void_ptr_obj(std::vector<      int64>);
SSTD_DEF_void_ptr_obj(std::vector<     uint8 >);
SSTD_DEF_void_ptr_obj(std::vector<     uint16>);
SSTD_DEF_void_ptr_obj(std::vector<     uint32>);
SSTD_DEF_void_ptr_obj(std::vector<     uint64>);
SSTD_DEF_void_ptr_obj(std::vector<      float>);
SSTD_DEF_void_ptr_obj(std::vector<     double>);
SSTD_DEF_void_ptr_obj(std::vector<std::string>);

//-----------------------------------------------------------------------------------------------------------------------------------------------
// destructor

sstd::void_ptr_obj::~void_ptr_obj(){
    sstd::void_ptr_obj::free(*this);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// member functions

void sstd::void_ptr_obj::copy(class void_ptr_obj& rhs, const class void_ptr_obj& lhs){
    sstd::void_ptr_obj::free(rhs);
    
    rhs.typeNumber = lhs.typeNumber;
    if(lhs.pData==NULL){ rhs.pData=NULL; return; }
    
    switch (rhs.typeNumber){
        
    case sstd::num_bool  : { rhs.pData = new        bool(*(      bool *)lhs.pData); } break;
    case sstd::num_char  : { rhs.pData = new        char(*(      char *)lhs.pData); } break;
    case sstd::num_int8  : { rhs.pData = new       int8 (*(      int8 *)lhs.pData); } break;
    case sstd::num_int16 : { rhs.pData = new       int16(*(      int16*)lhs.pData); } break;
    case sstd::num_int32 : { rhs.pData = new       int32(*(      int32*)lhs.pData); } break;
    case sstd::num_int64 : { rhs.pData = new       int64(*(      int64*)lhs.pData); } break;
    case sstd::num_uint8 : { rhs.pData = new      uint8 (*(     uint8 *)lhs.pData); } break;
    case sstd::num_uint16: { rhs.pData = new      uint16(*(     uint16*)lhs.pData); } break;
    case sstd::num_uint32: { rhs.pData = new      uint32(*(     uint32*)lhs.pData); } break;
    case sstd::num_uint64: { rhs.pData = new      uint64(*(     uint64*)lhs.pData); } break;
    case sstd::num_float : { rhs.pData = new       float(*(      float*)lhs.pData); } break;
    case sstd::num_double: { rhs.pData = new      double(*(     double*)lhs.pData); } break;
    case sstd::num_str   : { rhs.pData = new std::string(*(std::string*)lhs.pData); } break;
        
    case sstd::num_vec_bool  : { rhs.pData = new std::vector<       bool>(*(std::vector<       bool>*)lhs.pData); } break;
    case sstd::num_vec_char  : { rhs.pData = new std::vector<       char>(*(std::vector<       char>*)lhs.pData); } break;
    case sstd::num_vec_int8  : { rhs.pData = new std::vector<      int8 >(*(std::vector<      int8 >*)lhs.pData); } break;
    case sstd::num_vec_int16 : { rhs.pData = new std::vector<      int16>(*(std::vector<      int16>*)lhs.pData); } break;
    case sstd::num_vec_int32 : { rhs.pData = new std::vector<      int32>(*(std::vector<      int32>*)lhs.pData); } break;
    case sstd::num_vec_int64 : { rhs.pData = new std::vector<      int64>(*(std::vector<      int64>*)lhs.pData); } break;
    case sstd::num_vec_uint8 : { rhs.pData = new std::vector<     uint8 >(*(std::vector<     uint8 >*)lhs.pData); } break;
    case sstd::num_vec_uint16: { rhs.pData = new std::vector<     uint16>(*(std::vector<     uint16>*)lhs.pData); } break;
    case sstd::num_vec_uint32: { rhs.pData = new std::vector<     uint32>(*(std::vector<     uint32>*)lhs.pData); } break;
    case sstd::num_vec_uint64: { rhs.pData = new std::vector<     uint64>(*(std::vector<     uint64>*)lhs.pData); } break;
    case sstd::num_vec_float : { rhs.pData = new std::vector<      float>(*(std::vector<      float>*)lhs.pData); } break;
    case sstd::num_vec_double: { rhs.pData = new std::vector<     double>(*(std::vector<     double>*)lhs.pData); } break;
    case sstd::num_vec_str   : { rhs.pData = new std::vector<std::string>(*(std::vector<std::string>*)lhs.pData); } break;
        
    default: { sstd::pdbg("ERROR: allocating memory is failed. typeNum '%d' is not defined.", rhs.typeNumber); } break;
        
    }
}
void sstd::void_ptr_obj::free(class void_ptr_obj& rhs){
    if(this->pData==NULL){ return; }
    
    switch (this->typeNumber){
    case sstd::num_bool  : { delete (       bool*)pData; } break;
    case sstd::num_char  : { delete (       char*)pData; } break;
    case sstd::num_int8  : { delete (      int8 *)pData; } break;
    case sstd::num_int16 : { delete (      int16*)pData; } break;
    case sstd::num_int32 : { delete (      int32*)pData; } break;
    case sstd::num_int64 : { delete (      int64*)pData; } break;
    case sstd::num_uint8 : { delete (     uint8 *)pData; } break;
    case sstd::num_uint16: { delete (     uint16*)pData; } break;
    case sstd::num_uint32: { delete (     uint32*)pData; } break;
    case sstd::num_uint64: { delete (     uint64*)pData; } break;
    case sstd::num_float : { delete (      float*)pData; } break;
    case sstd::num_double: { delete (     double*)pData; } break;
    case sstd::num_str   : { delete (std::string*)pData; } break;
    case sstd::num_vec_bool  : { delete (std::vector<       bool>*)pData; } break;
    case sstd::num_vec_char  : { delete (std::vector<       char>*)pData; } break;
    case sstd::num_vec_int8  : { delete (std::vector<      int8 >*)pData; } break;
    case sstd::num_vec_int16 : { delete (std::vector<      int16>*)pData; } break;
    case sstd::num_vec_int32 : { delete (std::vector<      int32>*)pData; } break;
    case sstd::num_vec_int64 : { delete (std::vector<      int64>*)pData; } break;
    case sstd::num_vec_uint8 : { delete (std::vector<     uint8 >*)pData; } break;
    case sstd::num_vec_uint16: { delete (std::vector<     uint16>*)pData; } break;
    case sstd::num_vec_uint32: { delete (std::vector<     uint32>*)pData; } break;
    case sstd::num_vec_uint64: { delete (std::vector<     uint64>*)pData; } break;
    case sstd::num_vec_float : { delete (std::vector<      float>*)pData; } break;
    case sstd::num_vec_double: { delete (std::vector<     double>*)pData; } break;
    case sstd::num_vec_str   : { delete (std::vector<std::string>*)pData; } break;
    default: { sstd::pdbg("ERROR: free() memory is failed. typeNum '%d' is not defined.", this->typeNumber); } break;
    }
}
void sstd::void_ptr_obj::move(class void_ptr_obj& rhs, class void_ptr_obj&& lhs){
    rhs.typeNumber = lhs.typeNumber; lhs.typeNumber=sstd::num_null;
    rhs.pData      = lhs.pData;      lhs.pData=NULL;
}
void* sstd::void_ptr_obj::ptr(){ return this->pData; }
uint sstd::void_ptr_obj::typeNum(){ return this->typeNumber; }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// operators

class sstd::void_ptr_obj& sstd::void_ptr_obj::operator=(const sstd::void_ptr_obj& rhs){
    sstd::void_ptr_obj::copy(*this, rhs);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

