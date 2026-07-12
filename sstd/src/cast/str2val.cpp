#include "str2val.hpp"
#include <string.h> // for ::strlen()
#include "../print/print.hpp" // for debug
#include "../string/strEdit.hpp"
#include "../string/strmatch.hpp"


bool sstd::str2val(     bool  & return_val, const char* s_in){
    std::string s = sstd::lowered(s_in);

    if      (s=="true"  || s=="t" || s=="yes" || s=="y" || s=="on"  || s=="1"){ return_val=true;  return true;
    }else if(s=="false" || s=="f" || s=="no"  || s=="n" || s=="off" || s=="0"){ return_val=false; return true;
    }else if(sstd::isNum(s)){ return_val=(std::stoi(s)!=0); return true;
    }
    
    return false;
}
bool sstd::str2val(     char  & return_val, const char* s){
    if(::strlen(s)!=1){ return false; }
    return_val=(char)s[0];
    return true;
}
#define SSTD_STR2VAL_INTEGER(T, FN_S2I)         \
    char *pEnd;                                 \
    return_val=(T)FN_S2I(s, &pEnd, 0);          \
    return *pEnd=='\0';
bool sstd::str2val(      int8 & return_val, const char* s){ SSTD_STR2VAL_INTEGER( int8,  std::strtol  ); }
bool sstd::str2val(      int16& return_val, const char* s){ SSTD_STR2VAL_INTEGER( int16, std::strtol  ); }
bool sstd::str2val(      int32& return_val, const char* s){ SSTD_STR2VAL_INTEGER( int32, std::strtol  ); }
bool sstd::str2val(      int64& return_val, const char* s){ SSTD_STR2VAL_INTEGER( int64, std::strtol  ); }
bool sstd::str2val(     uint8 & return_val, const char* s){ SSTD_STR2VAL_INTEGER(uint8 , std::strtoul ); }
bool sstd::str2val(     uint16& return_val, const char* s){ SSTD_STR2VAL_INTEGER(uint16, std::strtoul ); }
bool sstd::str2val(     uint32& return_val, const char* s){ SSTD_STR2VAL_INTEGER(uint32, std::strtoul ); }
bool sstd::str2val(     uint64& return_val, const char* s){ SSTD_STR2VAL_INTEGER(uint64, std::strtoull); }
#undef SSTD_STR2VAL_INTEGER
#define SSTD_STR2VAL_FLOAT(T, FN_S2I)           \
    char *pEnd;                                 \
    return_val=(T)FN_S2I(s, &pEnd);             \
    return *pEnd=='\0';
bool sstd::str2val(      float& return_val, const char* s){ SSTD_STR2VAL_FLOAT( float, std::strtof); }
bool sstd::str2val(     double& return_val, const char* s){ SSTD_STR2VAL_FLOAT(double, std::strtod); }
#undef SSTD_STR2VAL_FLOAT
bool sstd::str2val(std::string& return_val, const char* s){
    return_val=s;
    return true;
}

bool sstd::str2val(                 bool   & return_val, const             std::string & s){ return sstd::str2val(return_val, s.c_str()); }
bool sstd::str2val(                 char   & return_val, const             std::string & s){ if(s.size()!=1){return false;} return_val=(char)s[0]; return true; }
bool sstd::str2val(                  int8  & return_val, const             std::string & s){ return sstd::str2val(return_val, s.c_str()); }
bool sstd::str2val(                  int16 & return_val, const             std::string & s){ return sstd::str2val(return_val, s.c_str()); }
bool sstd::str2val(                  int32 & return_val, const             std::string & s){ return sstd::str2val(return_val, s.c_str()); }
bool sstd::str2val(                  int64 & return_val, const             std::string & s){ return sstd::str2val(return_val, s.c_str()); }
bool sstd::str2val(                 uint8  & return_val, const             std::string & s){ return sstd::str2val(return_val, s.c_str()); }
bool sstd::str2val(                 uint16 & return_val, const             std::string & s){ return sstd::str2val(return_val, s.c_str()); }
bool sstd::str2val(                 uint32 & return_val, const             std::string & s){ return sstd::str2val(return_val, s.c_str()); }
bool sstd::str2val(                 uint64 & return_val, const             std::string & s){ return sstd::str2val(return_val, s.c_str()); }
bool sstd::str2val(                  float & return_val, const             std::string & s){ return sstd::str2val(return_val, s.c_str()); }
bool sstd::str2val(                 double & return_val, const             std::string & s){ return sstd::str2val(return_val, s.c_str()); }
bool sstd::str2val(            std::string & return_val, const             std::string & s){ return_val=s; return true; }

#define SSTD_STR2VAL_INTEGER_VEC()                      \
    if(v.size()!=1){ return false; }                    \
    return sstd::str2val(return_val, v[0]);
bool sstd::str2val(     bool  & return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd::str2val(     char  & return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd::str2val(      int8 & return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd::str2val(      int16& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd::str2val(      int32& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd::str2val(      int64& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd::str2val(     uint8 & return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd::str2val(     uint16& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd::str2val(     uint32& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd::str2val(     uint64& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd::str2val(     float & return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd::str2val(     double& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd::str2val(std::string& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
#undef SSTD_STR2VAL_INTEGER_VEC

//---

#define SSTD_STR2VAL_VEC_VEC(TYPE)                      \
    for(uint i=0; i<v.size(); ++i){                     \
        TYPE tmp;                                       \
        if(!sstd::str2val(tmp, v[i])){ return false; }  \
        return_val.push_back( tmp );                    \
    }                                                   \
    return true;
bool sstd::str2val(std::vector<     bool  >& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(bool  ); }
bool sstd::str2val(std::vector<     char  >& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(char  ); }
bool sstd::str2val(std::vector<      int8 >& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC( int8 ); }
bool sstd::str2val(std::vector<      int16>& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC( int16); }
bool sstd::str2val(std::vector<      int32>& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC( int32); }
bool sstd::str2val(std::vector<      int64>& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC( int64); }
bool sstd::str2val(std::vector<     uint8 >& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(uint8 ); }
bool sstd::str2val(std::vector<     uint16>& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(uint16); }
bool sstd::str2val(std::vector<     uint32>& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(uint32); }
bool sstd::str2val(std::vector<     uint64>& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(uint64); }
bool sstd::str2val(std::vector<     float >& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(float ); }
bool sstd::str2val(std::vector<     double>& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(double); }
bool sstd::str2val(std::vector<std::string>& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(std::string); }
#undef SSTD_STR2VAL_VEC_VEC

