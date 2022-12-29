#include "void_ptr_obj.hpp"

#include "../definitions/typeNum.hpp"
#include "../print/pdbg.hpp"


//-----------------------------------------------------------------------------------------------------------------------------------------------
// constructors

sstd::void_ptr_obj::void_ptr_obj(): typeNumber(sstd::num_null), pData(NULL) {}
sstd::void_ptr_obj::void_ptr_obj(const class void_ptr_obj& rhs){ // copy constructor
    this->typeNumber = rhs.typeNumber;
    if(rhs.pData==NULL){ this->pData=NULL; return; }
    
    switch (this->typeNumber){
        
    case sstd::num_bool  : { this->pData = new        bool(*(      bool *)rhs.pData); } break;
    case sstd::num_char  : { this->pData = new        char(*(      char *)rhs.pData); } break;
    case sstd::num_int8  : { this->pData = new       int8 (*(      int8 *)rhs.pData); } break;
    case sstd::num_int16 : { this->pData = new       int16(*(      int16*)rhs.pData); } break;
    case sstd::num_int32 : { this->pData = new       int32(*(      int32*)rhs.pData); } break;
    case sstd::num_int64 : { this->pData = new       int64(*(      int64*)rhs.pData); } break;
    case sstd::num_uint8 : { this->pData = new      uint8 (*(     uint8 *)rhs.pData); } break;
    case sstd::num_uint16: { this->pData = new      uint16(*(     uint16*)rhs.pData); } break;
    case sstd::num_uint32: { this->pData = new      uint32(*(     uint32*)rhs.pData); } break;
    case sstd::num_uint64: { this->pData = new      uint64(*(     uint64*)rhs.pData); } break;
    case sstd::num_float : { this->pData = new       float(*(      float*)rhs.pData); } break;
    case sstd::num_double: { this->pData = new      double(*(     double*)rhs.pData); } break;
    case sstd::num_str   : { this->pData = new std::string(*(std::string*)rhs.pData); } break;
        
    case sstd::num_vec_bool  : { this->pData = new std::vector<       bool>(*(std::vector<       bool>*)rhs.pData); } break;
    case sstd::num_vec_char  : { this->pData = new std::vector<       char>(*(std::vector<       char>*)rhs.pData); } break;
    case sstd::num_vec_int8  : { this->pData = new std::vector<      int8 >(*(std::vector<      int8 >*)rhs.pData); } break;
    case sstd::num_vec_int16 : { this->pData = new std::vector<      int16>(*(std::vector<      int16>*)rhs.pData); } break;
    case sstd::num_vec_int32 : { this->pData = new std::vector<      int32>(*(std::vector<      int32>*)rhs.pData); } break;
    case sstd::num_vec_int64 : { this->pData = new std::vector<      int64>(*(std::vector<      int64>*)rhs.pData); } break;
    case sstd::num_vec_uint8 : { this->pData = new std::vector<     uint8 >(*(std::vector<     uint8 >*)rhs.pData); } break;
    case sstd::num_vec_uint16: { this->pData = new std::vector<     uint16>(*(std::vector<     uint16>*)rhs.pData); } break;
    case sstd::num_vec_uint32: { this->pData = new std::vector<     uint32>(*(std::vector<     uint32>*)rhs.pData); } break;
    case sstd::num_vec_uint64: { this->pData = new std::vector<     uint64>(*(std::vector<     uint64>*)rhs.pData); } break;
    case sstd::num_vec_float : { this->pData = new std::vector<      float>(*(std::vector<      float>*)rhs.pData); } break;
    case sstd::num_vec_double: { this->pData = new std::vector<     double>(*(std::vector<     double>*)rhs.pData); } break;
    case sstd::num_vec_str   : { this->pData = new std::vector<std::string>(*(std::vector<std::string>*)rhs.pData); } break;
        
    default: { sstd::pdbg("ERROR: allocating memory is failed. typeNum '%d' is not defined.", this->typeNumber); } break;
        
    }
}
sstd::void_ptr_obj::void_ptr_obj(class void_ptr_obj&& rhs){ // move constructor
    this->typeNumber = rhs.typeNumber; rhs.typeNumber=sstd::num_null;
    this->pData      = rhs.pData;      rhs.pData=NULL;
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

uint sstd::void_ptr_obj::typeNum(){ return this->typeNumber; }
void* sstd::void_ptr_obj::ptr(){ return this->pData; }

//-----------------------------------------------------------------------------------------------------------------------------------------------

