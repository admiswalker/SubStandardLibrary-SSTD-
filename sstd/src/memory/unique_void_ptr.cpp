#include "unique_void_ptr.hpp"

#include "../definitions/typeNum.hpp"
#include "../print/pdbg.hpp"


//-----------------------------------------------------------------------------------------------------------------------------------------------
// constructors

sstd::unique_void_ptr::unique_void_ptr(): typeNumber(sstd::num_null), pData(NULL) {}
sstd::unique_void_ptr::unique_void_ptr(class unique_void_ptr&& rhs){ // move constructor
    this->typeNumber = rhs.typeNumber; rhs.typeNumber=sstd::num_null;
    this->pData      = rhs.pData;      rhs.pData=NULL;
}


#define SSTD_DEF_unique_void_ptr(Type)                        \
    sstd::unique_void_ptr::unique_void_ptr(Type* ptr){        \
        this->typeNumber    = sstd::type2num(Type());         \
        this->pData = ptr;                                    \
    }

SSTD_DEF_unique_void_ptr(       bool);
SSTD_DEF_unique_void_ptr(       char);
//SSTD_DEF_unique_void_ptr(      uchar);
SSTD_DEF_unique_void_ptr(      int8 );
SSTD_DEF_unique_void_ptr(      int16);
SSTD_DEF_unique_void_ptr(      int32);
SSTD_DEF_unique_void_ptr(      int64);
SSTD_DEF_unique_void_ptr(     uint8 );
SSTD_DEF_unique_void_ptr(     uint16);
SSTD_DEF_unique_void_ptr(     uint32);
SSTD_DEF_unique_void_ptr(     uint64);
SSTD_DEF_unique_void_ptr(      float);
SSTD_DEF_unique_void_ptr(     double);
SSTD_DEF_unique_void_ptr(std::string);

SSTD_DEF_unique_void_ptr(std::vector<       bool>);
SSTD_DEF_unique_void_ptr(std::vector<       char>);
//SSTD_DEF_unique_void_ptr(std::vector<      uchar>);
SSTD_DEF_unique_void_ptr(std::vector<      int8 >);
SSTD_DEF_unique_void_ptr(std::vector<      int16>);
SSTD_DEF_unique_void_ptr(std::vector<      int32>);
SSTD_DEF_unique_void_ptr(std::vector<      int64>);
SSTD_DEF_unique_void_ptr(std::vector<     uint8 >);
SSTD_DEF_unique_void_ptr(std::vector<     uint16>);
SSTD_DEF_unique_void_ptr(std::vector<     uint32>);
SSTD_DEF_unique_void_ptr(std::vector<     uint64>);
SSTD_DEF_unique_void_ptr(std::vector<      float>);
SSTD_DEF_unique_void_ptr(std::vector<     double>);
SSTD_DEF_unique_void_ptr(std::vector<std::string>);

//-----------------------------------------------------------------------------------------------------------------------------------------------
// destructor

sstd::unique_void_ptr::~unique_void_ptr(){
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

//-----------------------------------------------------------------------------------------------------------------------------------------------
// member functions

uint sstd::unique_void_ptr::typeNum(){ return this->typeNumber; }
void* sstd::unique_void_ptr::ptr(){ return this->pData; }

//-----------------------------------------------------------------------------------------------------------------------------------------------

