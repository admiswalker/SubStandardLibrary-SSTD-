#include "argparse.hpp"
#include "../container/vector/slice.hpp"
#include "../container/vector/stdVector_expansion.hpp"
#include "../print/pdbg.hpp"
#include "../print/print.hpp" // for debug
#include "../string/ssprintf.hpp"
#include "../string/strEdit.hpp"
#include "../string/strmatch.hpp"
#include "../utils/vector/duplicated.hpp"

//---

bool _fill_by_initial_val(void* ptr, const int type, const sstd::void_ptr& initial_val_ptr){
    switch(type){
    case sstd::num_bool      : { std::swap(*(                 bool   *)ptr, *(                 bool   *)initial_val_ptr.ptr()); } break;
//  case sstd::num_char      : { std::swap(*(                 char   *)ptr, *(                 char   *)initial_val_ptr.ptr()); } break;
    case sstd::num_int8      : { std::swap(*(                  int8  *)ptr, *(                  int8  *)initial_val_ptr.ptr()); } break;
    case sstd::num_int16     : { std::swap(*(                  int16 *)ptr, *(                  int16 *)initial_val_ptr.ptr()); } break;
    case sstd::num_int32     : { std::swap(*(                  int32 *)ptr, *(                  int32 *)initial_val_ptr.ptr()); } break;
    case sstd::num_int64     : { std::swap(*(                  int64 *)ptr, *(                  int64 *)initial_val_ptr.ptr()); } break;
    case sstd::num_uint8     : { std::swap(*(                 uint8  *)ptr, *(                 uint8  *)initial_val_ptr.ptr()); } break;
    case sstd::num_uint16    : { std::swap(*(                 uint16 *)ptr, *(                 uint16 *)initial_val_ptr.ptr()); } break;
    case sstd::num_uint32    : { std::swap(*(                 uint32 *)ptr, *(                 uint32 *)initial_val_ptr.ptr()); } break;
    case sstd::num_uint64    : { std::swap(*(                 uint64 *)ptr, *(                 uint64 *)initial_val_ptr.ptr()); } break;
    case sstd::num_float     : { std::swap(*(                 float  *)ptr, *(                 float  *)initial_val_ptr.ptr()); } break;
    case sstd::num_double    : { std::swap(*(                 double *)ptr, *(                 double *)initial_val_ptr.ptr()); } break;
    case sstd::num_str       : { std::swap(*(            std::string *)ptr, *(            std::string *)initial_val_ptr.ptr()); } break;
    case sstd::num_vec_bool  : { std::swap(*(std::vector<     bool  >*)ptr, *(std::vector<     bool  >*)initial_val_ptr.ptr()); } break;
    case sstd::num_vec_char  : { std::swap(*(std::vector<     char  >*)ptr, *(std::vector<     char  >*)initial_val_ptr.ptr()); } break;
    case sstd::num_vec_int8  : { std::swap(*(std::vector<      int8 >*)ptr, *(std::vector<      int8 >*)initial_val_ptr.ptr()); } break;
    case sstd::num_vec_int16 : { std::swap(*(std::vector<      int16>*)ptr, *(std::vector<      int16>*)initial_val_ptr.ptr()); } break;
    case sstd::num_vec_int32 : { std::swap(*(std::vector<      int32>*)ptr, *(std::vector<      int32>*)initial_val_ptr.ptr()); } break;
    case sstd::num_vec_int64 : { std::swap(*(std::vector<      int64>*)ptr, *(std::vector<      int64>*)initial_val_ptr.ptr()); } break;
    case sstd::num_vec_uint8 : { std::swap(*(std::vector<     uint8 >*)ptr, *(std::vector<     uint8 >*)initial_val_ptr.ptr()); } break;
    case sstd::num_vec_uint16: { std::swap(*(std::vector<     uint16>*)ptr, *(std::vector<     uint16>*)initial_val_ptr.ptr()); } break;
    case sstd::num_vec_uint32: { std::swap(*(std::vector<     uint32>*)ptr, *(std::vector<     uint32>*)initial_val_ptr.ptr()); } break;
    case sstd::num_vec_uint64: { std::swap(*(std::vector<     uint64>*)ptr, *(std::vector<     uint64>*)initial_val_ptr.ptr()); } break;
    case sstd::num_vec_float : { std::swap(*(std::vector<     float >*)ptr, *(std::vector<     float >*)initial_val_ptr.ptr()); } break;
    case sstd::num_vec_double: { std::swap(*(std::vector<     double>*)ptr, *(std::vector<     double>*)initial_val_ptr.ptr()); } break;
    case sstd::num_vec_str   : { std::swap(*(std::vector<std::string>*)ptr, *(std::vector<std::string>*)initial_val_ptr.ptr()); } break;
    default: { return false; }
    }
    return true;
}

//---

bool sstd__str2val(     bool& return_val, const std::string& s){
    if      (s=="T" || s=="true"  || s=="True" ){ return_val=true;  return true;
    }else if(s=="F" || s=="false" || s=="False"){ return_val=false; return true;
    }else if(sstd::isNum(s)){ return_val=(std::stoi(s)!=0); return true;
    }
    
    return false;
}
bool sstd__str2val(     char& return_val, const std::string& s){
    if(s.size()!=1){ return false; }
    return_val=(char)s[0];
    return true;
}
#define SSTD_STR2VAL_INTEGER(T, FN_S2I)         \
    char *pEnd;                                 \
    return_val=(T)FN_S2I(s.c_str(), &pEnd, 0);  \
    return *pEnd=='\0';
bool sstd__str2val(      int8 & return_val, const             std::string & s){ SSTD_STR2VAL_INTEGER( int8,  std::strtol  ); }
bool sstd__str2val(      int16& return_val, const             std::string & s){ SSTD_STR2VAL_INTEGER( int16, std::strtol  ); }
bool sstd__str2val(      int32& return_val, const             std::string & s){ SSTD_STR2VAL_INTEGER( int32, std::strtol  ); }
bool sstd__str2val(      int64& return_val, const             std::string & s){ SSTD_STR2VAL_INTEGER( int64, std::strtol  ); }
bool sstd__str2val(     uint8 & return_val, const             std::string & s){ SSTD_STR2VAL_INTEGER(uint8 , std::strtoul ); }
bool sstd__str2val(     uint16& return_val, const             std::string & s){ SSTD_STR2VAL_INTEGER(uint16, std::strtoul ); }
bool sstd__str2val(     uint32& return_val, const             std::string & s){ SSTD_STR2VAL_INTEGER(uint32, std::strtoul ); }
bool sstd__str2val(     uint64& return_val, const             std::string & s){ SSTD_STR2VAL_INTEGER(uint64, std::strtoull); }
#undef SSTD_STR2VAL_INTEGER
#define SSTD_STR2VAL_FLOAT(T, FN_S2I)           \
    char *pEnd;                                 \
    return_val=(T)FN_S2I(s.c_str(), &pEnd);     \
    return *pEnd=='\0';
bool sstd__str2val(      float& return_val, const             std::string & s){ SSTD_STR2VAL_FLOAT( float, std::strtof); }
bool sstd__str2val(     double& return_val, const             std::string & s){ SSTD_STR2VAL_FLOAT(double, std::strtod); }
#undef SSTD_STR2VAL_FLOAT
bool sstd__str2val(std::string& return_val, const std::string& s){
    return_val=s;
    return true;
}

#define SSTD_STR2VAL_INTEGER_VEC()                      \
    if(v.size()!=1){ return false; }                    \
    return sstd__str2val(return_val, v[0].c_str());
bool sstd__str2val(     bool  & return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd__str2val(     char  & return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd__str2val(      int8 & return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd__str2val(      int16& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd__str2val(      int32& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd__str2val(      int64& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd__str2val(     uint8 & return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd__str2val(     uint16& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd__str2val(     uint32& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd__str2val(     uint64& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd__str2val(     float & return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd__str2val(     double& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
bool sstd__str2val(std::string& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_INTEGER_VEC(); }
#undef SSTD_STR2VAL_INTEGER_VEC

//---

#define SSTD_STR2VAL_VEC_VEC(TYPE)                      \
    for(uint i=0; i<v.size(); ++i){                     \
        TYPE tmp;                                       \
        if(!sstd__str2val(tmp, v[i])){ return false; }  \
        return_val.push_back( tmp );                    \
    }                                                   \
    return true;
bool sstd__str2val(std::vector<     bool  >& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(bool  ); }
bool sstd__str2val(std::vector<     char  >& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(char  ); }
bool sstd__str2val(std::vector<      int8 >& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC( int8 ); }
bool sstd__str2val(std::vector<      int16>& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC( int16); }
bool sstd__str2val(std::vector<      int32>& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC( int32); }
bool sstd__str2val(std::vector<      int64>& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC( int64); }
bool sstd__str2val(std::vector<     uint8 >& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(uint8 ); }
bool sstd__str2val(std::vector<     uint16>& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(uint16); }
bool sstd__str2val(std::vector<     uint32>& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(uint32); }
bool sstd__str2val(std::vector<     uint64>& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(uint64); }
bool sstd__str2val(std::vector<     float >& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(float ); }
bool sstd__str2val(std::vector<     double>& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(double); }
bool sstd__str2val(std::vector<std::string>& return_val, const std::vector<std::string>& v){ SSTD_STR2VAL_VEC_VEC(std::string); }
#undef SSTD_STR2VAL_VEC_VEC

int sstd__str2voidp(void* return_val_ptr, const int type, const std::vector<std::string>& v){
    
    switch(type){
    case sstd::num_bool      : { if(!sstd__str2val(*(                 bool   *)return_val_ptr, v)){return -1;} } break;
    case sstd::num_char      : { if(!sstd__str2val(*(                 char   *)return_val_ptr, v)){return -1;} } break;
    case sstd::num_int8      : { if(!sstd__str2val(*(                  int8  *)return_val_ptr, v)){return -1;} } break;
    case sstd::num_int16     : { if(!sstd__str2val(*(                  int16 *)return_val_ptr, v)){return -1;} } break;
    case sstd::num_int32     : { if(!sstd__str2val(*(                  int32 *)return_val_ptr, v)){return -1;} } break;
    case sstd::num_int64     : { if(!sstd__str2val(*(                  int64 *)return_val_ptr, v)){return -1;} } break;
    case sstd::num_uint8     : { if(!sstd__str2val(*(                 uint8  *)return_val_ptr, v)){return -1;} } break;
    case sstd::num_uint16    : { if(!sstd__str2val(*(                 uint16 *)return_val_ptr, v)){return -1;} } break;
    case sstd::num_uint32    : { if(!sstd__str2val(*(                 uint32 *)return_val_ptr, v)){return -1;} } break;
    case sstd::num_uint64    : { if(!sstd__str2val(*(                 uint64 *)return_val_ptr, v)){return -1;} } break;
    case sstd::num_float     : { if(!sstd__str2val(*(                 float  *)return_val_ptr, v)){return -1;} } break;
    case sstd::num_double    : { if(!sstd__str2val(*(                 double *)return_val_ptr, v)){return -1;} } break;
    case sstd::num_str       : { if(!sstd__str2val(*(            std::string *)return_val_ptr, v)){return -1;} } break;
    case sstd::num_vec_bool  : { if(!sstd__str2val(*(std::vector<     bool  >*)return_val_ptr, v)){return -1;} } break;
    case sstd::num_vec_char  : { if(!sstd__str2val(*(std::vector<     char  >*)return_val_ptr, v)){return -1;} } break;
    case sstd::num_vec_int8  : { if(!sstd__str2val(*(std::vector<      int8 >*)return_val_ptr, v)){return -1;} } break;
    case sstd::num_vec_int16 : { if(!sstd__str2val(*(std::vector<      int16>*)return_val_ptr, v)){return -1;} } break;
    case sstd::num_vec_int32 : { if(!sstd__str2val(*(std::vector<      int32>*)return_val_ptr, v)){return -1;} } break;
    case sstd::num_vec_int64 : { if(!sstd__str2val(*(std::vector<      int64>*)return_val_ptr, v)){return -1;} } break;
    case sstd::num_vec_uint8 : { if(!sstd__str2val(*(std::vector<     uint8 >*)return_val_ptr, v)){return -1;} } break;
    case sstd::num_vec_uint16: { if(!sstd__str2val(*(std::vector<     uint16>*)return_val_ptr, v)){return -1;} } break;
    case sstd::num_vec_uint32: { if(!sstd__str2val(*(std::vector<     uint32>*)return_val_ptr, v)){return -1;} } break;
    case sstd::num_vec_uint64: { if(!sstd__str2val(*(std::vector<     uint64>*)return_val_ptr, v)){return -1;} } break;
    case sstd::num_vec_float : { if(!sstd__str2val(*(std::vector<     float >*)return_val_ptr, v)){return -1;} } break;
    case sstd::num_vec_double: { if(!sstd__str2val(*(std::vector<     double>*)return_val_ptr, v)){return -1;} } break;
    case sstd::num_vec_str   : { if(!sstd__str2val(*(std::vector<std::string>*)return_val_ptr, v)){return -1;} } break;
    default: { return -2; }
    }
    
    return 0;
}

//---
// TODO: sstd/src/string/strEdit.cpp に移動する。

std::vector<std::string> _asAX(const char* str, const char X, const int maxsplit){ // <- 既存の _asAX をこれの maxsplit=-1 で置換できるはず。
    if(maxsplit==0){ return std::vector<std::string>({str}); }
    std::vector<std::string> splitList;
    
    std::string buf;
    uint i=0;
//    while(str[i]!='\0'){ if(' '==str[i]){++i;}else{break;} } // skip space
    while(str[i]!='\0'){
        if(maxsplit>=0 && splitList.size()==(uint)maxsplit){
            buf += (const char*)&str[i];
            break;
        }

        if(str[i]==X){
//            sstd::rstrip_ow(buf); splitList.push_back(buf); buf.clear();
            splitList.push_back(buf); buf.clear();
            ++i;
//            while(str[i]!=0){ if(' '==str[i]){++i;}else{break;} } // skip space
        }else{
            buf+=str[i];
            ++i;
        }
    }
//    if(buf.size()!=0){ sstd::rstrip_ow(buf); splitList.push_back(buf); }
    if(buf.size()!=0){ splitList.push_back(buf); }
//    if(i>=1 && str[i-1]==X){ splitList.push_back(std::string()); }
    return splitList;
}
std::vector<std::string> sstd__split(const        char* str, const char X, int maxsplit){ return _asAX(str,          X, maxsplit); }
std::vector<std::string> sstd__split(const std::string& str, const char X, int maxsplit){ return _asAX(str.c_str(),  X, maxsplit); }

//---

int _get_cmd_id(const struct sstd::arg_rule::cmd_rule& cmdRule){ return cmdRule.cmd_id; }
int _get_cmd_id(const struct sstd::arg_rule::opt_rule& optRule){ return 0; }

#define COMMON_ERR_MSG sstd::pdbg_err_str(("Failed to init default value. Data type is `"+sstd::typeNum2str(type)+"`.\n").c_str());

template<typename T>
int _fill_result_arg_by_val(std::string& errMsg, const T& rule, const std::vector<std::string>& input_args){
    
    std::vector<std::string> args = input_args&&sstd::slice(1,sstd::end());
    int arg_len = rule.expected_num_of_args;
    
    int   type = rule.return_val_type;
    void* ptr  = rule.return_val_ptr;
    
    if(arg_len!=-1 && (int)args.size()!=arg_len){
        errMsg+=sstd::pdbg_err_str(("The number of input argument(s) is `"+std::to_string(args.size())+"` ("+sstd::to_string(input_args)+"). But `"+std::to_string(arg_len)+"` argument(s) are expected by the definition of sstd::arg_rule::opt().\n").c_str());
        errMsg+=COMMON_ERR_MSG;
        return -1;
    }
    
    if(args.size()!=0){
        // args.size()!=0
        
        int res = sstd__str2voidp(ptr, type, args);
        if(res==-1){
            errMsg+=sstd::pdbg_err_str(("The input arguments of `"+sstd::to_string(input_args)+"` is failed to convert to `"+sstd::typeNum2str(type)+"` type.\n").c_str());
            errMsg+=COMMON_ERR_MSG;
            return -1;
        }else if(res==-2){
            errMsg+=sstd::pdbg_err_str(("The input data type of `"+sstd::typeNum2str(type)+"` is our of support.\n").c_str());
            errMsg+=COMMON_ERR_MSG;
            return -1;
        }
        
    }else{
        // args.size()==0
        
        if(type==sstd::num_bool){
            
            *(bool*)ptr = true;
            
        }else{
            bool tf = _fill_by_initial_val(ptr, type, rule.initial_val_ptr);
            if(!tf){
                errMsg+=sstd::pdbg_err_str(("Failed to init default value. Data type is `"+sstd::typeNum2str(type)+"`.\n").c_str());
                return -1;
            }
        }
    }
    
    return _get_cmd_id(rule);
}

#undef COMMON_ERR_MSG

//---

std::string sstd::to_string(const sstd::arg_rule::cmd_rule& rhs){
    std::string s;
    s += sstd::ssprintf("cmd_id: %d\n", rhs.cmd_id);
    s += sstd::ssprintf("return_val_ptr: <Print function is NOT implemented>\n");
    s += sstd::ssprintf("initial_val_ptr: <Print function is NOT implemented>\n");
    s += sstd::ssprintf("cmd: `%s`\n", rhs.cmd.c_str());
    s += sstd::ssprintf("expected_num_of_args: %d\n", rhs.expected_num_of_args);
    s += ",\n";
    return s;
}

//---

std::string sstd::to_string(const sstd::arg_rule::opt_rule& rhs){
    std::string s;
    s += sstd::ssprintf("return_val_ptr: <Print function is NOT implemented>\n");
    s += sstd::ssprintf("initial_val_ptr: <Print function is NOT implemented>\n");
    s += sstd::ssprintf("opt_short: `%s`\n", rhs.opt_short.c_str());
    s += sstd::ssprintf("opt_full: `%s`\n", rhs.opt_full.c_str());
    s += sstd::ssprintf("expected_num_of_args: %d\n", rhs.expected_num_of_args);
    s += ",\n";
    return s;
}

//---

struct sstd::arg_rule::cmd_rule sstd::arg_rule::cmd(const char* cmd){
    sstd::arg_rule::cmd_rule res;
    res.cmd                  = std::string(cmd);
    return res;
}

struct sstd::arg_rule::cmd_rule sstd::arg_rule::cmd(const int cmd_id,                                      const char* cmd, const int expected_num_of_args){
    sstd::arg_rule::cmd_rule res;
    res.cmd_id               = cmd_id;
    res.cmd                  = std::string(cmd);
    res.expected_num_of_args = expected_num_of_args;
    return res;
}

//---

bool _is_cmd(const std::string& s, const std::unordered_map<std::string,uint>& ht_cmd2idx){
    auto itr = ht_cmd2idx.find( s );
    return itr!=ht_cmd2idx.end();
}
bool _is_opt_short(const std::string& s){
    return s.starts_with("-") && s.size()==2 && sstd::isAlphabet(s[1]);
}
bool _is_opt_multi_short(const std::string& s){
    return s.starts_with("-") && s.size()>=3 && sstd::isAlphabet(s[1]);
}
bool _is_opt_full(const std::string& s){
    return s.starts_with("--") && s.size()>=3 && sstd::isAlphabet(s[2]);
}
bool _is_opt_fs(const std::string& s){
    return ( _is_opt_short(s) || _is_opt_full(s) );
}

//---

bool _is_cmd(const std::string& s, int& rule_idx, int& arg_len, const std::vector<struct sstd::arg_rule::cmd_rule>& cmd_vRule, const std::unordered_map<std::string,uint>& ht_cmd2idx){
    auto itr = ht_cmd2idx.find( s );
    if(itr==ht_cmd2idx.end()){ return false; }
    rule_idx = itr->second;
    arg_len = cmd_vRule[itr->second].expected_num_of_args;
    return true;
}
bool _get_short_opt_ruleIdx_argLen(int& rule_idx, int& arg_len, const std::vector<struct sstd::arg_rule::opt_rule>& opt_vRule, const std::unordered_map<std::string,uint>& ht_opt2idx_short, const std::string& s){
    
    auto itr = ht_opt2idx_short.find( s );
    if(itr==ht_opt2idx_short.end()){ return false; }
    rule_idx = itr->second;
    arg_len = opt_vRule[itr->second].expected_num_of_args;
    
    return true;
}
bool _get_multi_short_opt_vRuleIdx(std::string& errMsg, std::vector<int>& v_rule_idx, const std::vector<struct sstd::arg_rule::opt_rule>& opt_vRule, const std::unordered_map<std::string,uint>& ht_opt2idx_short, const std::string& s){
    
    for(uint i=1; i<s.size(); ++i){
        auto itr = ht_opt2idx_short.find( std::string("-")+s[i] );
        if(itr==ht_opt2idx_short.end()){ return false; }
        v_rule_idx <<= itr->second;
        int type    = opt_vRule[itr->second].return_val_type;
        int arg_len = opt_vRule[itr->second].expected_num_of_args;
        if(arg_len!=0){
            errMsg+=sstd::pdbg_err_str(("multi_short option like `"+s+"` can not take arguments. But the short option of `"+std::string("-")+s[i]+"` with data type `"+sstd::typeNum2str(type)+"` expects "+std::to_string(arg_len)+" argument(s). As defined by sstd::arg_rule::opt().\n").c_str());
            return false;
        }
    }
    
    return true;
}
bool _get_full_opt_ruleIdx_argLen(int& rule_idx, int& arg_len, const std::vector<struct sstd::arg_rule::opt_rule>& opt_vRule, const std::unordered_map<std::string,uint>& ht_opt2idx_full, const std::string& s){
    
    auto itr = ht_opt2idx_full.find( s );
    if(itr==ht_opt2idx_full.end()){ return false; }
    rule_idx = itr->second;
    arg_len = opt_vRule[itr->second].expected_num_of_args;
    
    return true;
}

#define DEFAULT 0
#define CMD 1
#define OPT 2
#define OPT_M 3
#define NOT_A_SEPARATOR -1
bool _arg_type_and_len(
                      std::string& errMsg,
                      
                      // return variables:
                      int& res_type, std::vector<int>& v_rule_idx, int& arg_len,
                      
                      // input variables:
                      const std::string& s,
                      const std::vector<struct sstd::arg_rule::cmd_rule>& cmd_vRule,
                      const std::vector<struct sstd::arg_rule::opt_rule>& opt_vRule,
                      const std::unordered_map<std::string,uint>& ht_cmd2idx,
                      const std::unordered_map<std::string,uint>& ht_opt2idx_short,
                      const std::unordered_map<std::string,uint>& ht_opt2idx_full)
{
    int rule_idx=-1;
    
    if( _is_opt_short(s) && _get_short_opt_ruleIdx_argLen(rule_idx, arg_len, opt_vRule, ht_opt2idx_short, s) ){

        res_type = OPT;
        v_rule_idx <<= rule_idx;
        
        return true;
    }
    if( _is_opt_full(s) && _get_full_opt_ruleIdx_argLen(rule_idx, arg_len, opt_vRule, ht_opt2idx_full, s) ){
        
        res_type = OPT;
        v_rule_idx <<= rule_idx;
        
        return true;
    }
    if( _is_opt_multi_short(s) ){
        
        bool res = _get_multi_short_opt_vRuleIdx(errMsg, v_rule_idx, opt_vRule, ht_opt2idx_short, s);
        if(!res){ return false; }
        res_type = OPT_M;
        
        return true;
    }
    if( _is_cmd(s, rule_idx, arg_len, cmd_vRule, ht_cmd2idx) ){
        
        res_type=CMD;
        v_rule_idx<<=rule_idx;
        
        return true;
    }
    
    res_type=NOT_A_SEPARATOR;
    return true;
}
std::vector<std::string> _extract_opt_by_length(bool& res, std::string& errMsg, const int argc, const char* argv[], uint& i, const int arg_len){
    
    std::vector<std::string> res_v;
    res=true;
    
    if      (arg_len==-1){
        sstd::printn_all("ERROR: NOT implimented.");
    }else if(arg_len== 0){
            res_v <<= (std::string)argv[i]; // ex: '-a' -> 1 option + 0 args.
            
    }else if(arg_len>= 1){
        uint extract_cnt=0;
        for(; i<(uint)argc; ++i){
            res_v <<= (std::string)argv[i];
            ++extract_cnt;
            if(extract_cnt>(uint)arg_len){ break; } // ex: '-a 1 2 3' -> 1 option + 3 args.
        }
    }else{
        // ERROR
        sstd::printn_all("ERROR: NOT implimented.");
    }
    
    return res_v;
}

int _parse_argc_argv(
                      std::string& errMsg,
                      
                      // return variables:
                      int& ret_cmd_idx,
                      std::vector<std::string>& res_cmd_args,
                      std::vector<int>& ret_opt_vIdx,
                      std::vector<std::vector<std::string>>& res_opt_vArgs,
                      
                      // input variables:
                      const int argc, const char* argv[],
                      const std::vector<struct sstd::arg_rule::cmd_rule>& cmd_vRule,
                      const std::vector<struct sstd::arg_rule::opt_rule>& opt_vRule,
                      const std::unordered_map<std::string,uint>& ht_cmd2idx,
                      const std::unordered_map<std::string,uint>& ht_opt2idx_short,
                      const std::unordered_map<std::string,uint>& ht_opt2idx_full)
{
    // Ex.
    //    in:
    //        argv == [./a.out cmd -a 1 2 -b -cd -e true -f=true -g false -h=true --rectangle 5 5 5 5 src_path dst_path]
    //   out:
    //        res_cmd_args == [cmd src_path dst_path]
    //        res_opt_vArgs == [[-a 1 2],
    //                          [-b],
    //                          [-c],
    //                          [-d],
    //                          [-e true],
    //                          [-f true],  <- Note: `=` is removed
    //                          [-g true],
    //                          [-h false], <- Note: `=` is removed
    //                          [--rectangle 5 5 5 5]]

    ret_cmd_idx=-1;
    int cmd_arg_len=0;
    
    for(uint i=1; i<(uint)argc; ++i){
        std::vector<std::string> v = sstd__split(argv[i], '=', 1); // "-f=true" -> ["-f" "true"]
        std::string opt_candidate = std::move(v[0]);
        std::string val_candidate = v.size()==2 ? std::move(v[1]) : "";
        
        int type=0; std::vector<int> v_rule_idx; int arg_len=0;
        bool res = _arg_type_and_len(errMsg, type, v_rule_idx, arg_len, opt_candidate, cmd_vRule, opt_vRule, ht_cmd2idx, ht_opt2idx_short, ht_opt2idx_full);
        if(!res){ return -1; }
        if(val_candidate.size()!=0){
            if(type==CMD || type==OPT_M){
                errMsg+=sstd::pdbg_err_str(("The input argument of `"+sstd::to_string(argv[i])+"` is command or multiple short option. These types can NOT take the assignment operator of `=`.\n").c_str());
                return -1;
            }
            if(type==OPT && arg_len!=1){
                errMsg+=sstd::pdbg_err_str(("When the assignment operator of `=` is in use, only 1 argument expected. But the option of `"+opt_candidate+"` expects "+std::to_string(arg_len)+" arguments.\n").c_str());
                return -1;
            }
        }
        
        if      (type==CMD){
            // command
            ret_cmd_idx = (int)v_rule_idx[0];
            res_cmd_args <<= (std::string)argv[i];
            cmd_arg_len = arg_len;
            
        }else if(type==OPT){
            ret_opt_vIdx <<= (int)v_rule_idx[0];
            if(val_candidate.size()==0){
                bool res; res_opt_vArgs <<= _extract_opt_by_length(res, errMsg, argc, argv, i, arg_len); if(!res){ return -1; }
            }else{
                res_opt_vArgs <<= std::vector<std::string>({std::move(opt_candidate),std::move(val_candidate)});
            }
            
        }else if(type==OPT_M){
            ret_opt_vIdx <<= v_rule_idx;
            //res_opt_vArgs <<= std::vector<std::vector<std::string>>(v_rule_idx.size(), {""}); // make empty `std::vector<std::string>("")`, `v_rule_idx.size()` times.
            std::string tmp=argv[i];
            for(uint i2=1; i2<tmp.size(); ++i2){
                res_opt_vArgs <<= std::vector<std::string>({std::string("-")+tmp[i2]}); // Invedding [-a, -b, -c] is the wast of memory, but to keep for easy debugging and error message handling.
            }
            
        }else{
            res_cmd_args <<= (std::string)argv[i];
            
        }
    }

    if( ret_cmd_idx!=-1 && cmd_arg_len!=-1 && res_cmd_args.size()!=cmd_arg_len+1 ){ return -1; }

    return 0;
}
#undef NOT_A_SEPARATOR
#undef OPT_M
#undef OPT
#undef CMD
#undef DEFAULT

//---

int _parse_cmd(const std::string& cmd,
                const std::unordered_map<std::string,uint>& ht_cmd2idx)
{
    auto itr = ht_cmd2idx.find( cmd );
    if(itr==ht_cmd2idx.end()){ return -1; }
    int cmd_idx = (int)itr->second;
    return cmd_idx;
}

int _process_cmd(std::string& errMsg,
                 const int cmd_idx,
                 const std::vector<std::string>& cmd_args,
                 const std::vector<struct sstd::arg_rule::cmd_rule>& cmd_vRule,
                 const std::unordered_map<std::string,uint>& ht_cmd2idx)
{
    int cmd_id = sstd::arg_rule::num_command_does_not_exist;
    if(cmd_idx==-1){
        errMsg+=sstd::pdbg_err_str(("The input argument(s) of `"+sstd::to_string(cmd_args)+"` is NOT defnied by sstd::cmd_rule::opt() as an input option.\n").c_str());
        return cmd_id;
    }
    
    if(cmd_args.size()!=0){
        cmd_id = _fill_result_arg_by_val(errMsg, cmd_vRule[cmd_idx], cmd_args);
        
        if(cmd_id==-1){
            // If the `_fill_result_arg_by_val()` failed, `sstd::argparse()` tried to fill the value by default.
            
            int   type = cmd_vRule[cmd_idx].return_val_type;
            void* ptr  = cmd_vRule[cmd_idx].return_val_ptr;
            bool tf = _fill_by_initial_val(ptr, type, cmd_vRule[cmd_idx].initial_val_ptr);
            if(!tf){
                errMsg+=sstd::pdbg_err_str(("Failed to init default value. Data type is `"+sstd::typeNum2str(type)+"`.\n").c_str());
            }
            return -1;
        }
    }
    
    return cmd_id;
}

//---

int _process_opt(std::string& errMsg,
                 std::vector<bool>& opt_vRule_inited,
                 const std::vector<int>& opt_vIdx,
                 const std::vector<std::vector<std::string>>& opt_vArgs,
                 const std::vector<struct sstd::arg_rule::opt_rule>& opt_vRule,
                 const std::unordered_map<std::string,uint>& ht_opt2idx_short,
                 const std::unordered_map<std::string,uint>& ht_opt2idx_full)
{
    std::vector<std::tuple<int,uint>> vDuplicated = sstd::duplicated_key_cnt(opt_vIdx);
    if(vDuplicated.size()!=0){
        std::string err = "There are duplicated input in the arg. The duplicated options are follows:";
        for(uint i=0; i<vDuplicated.size(); ++i){
            err += " `"+opt_vRule[ std::get<0>(vDuplicated[i]) ].opt_full+" ("+opt_vRule[ std::get<0>(vDuplicated[i]) ].opt_short+")`";
        }
        err += ".\n";
        errMsg+=sstd::pdbg_err_str(err.c_str());
        return -1;
    }
    for(uint i=0; i<opt_vIdx.size(); ++i){
        int opt_idx = opt_vIdx[i];
        int res = _fill_result_arg_by_val(errMsg, opt_vRule[opt_idx], opt_vArgs[opt_idx]);
        if(res!=0){ return -1; }
        opt_vRule_inited[opt_idx] = true; // Even if the `_fill_result_arg_by_val` failed, this function tried to update the option by default value.
    }
    
    return 0;
}

int _process_opt_init(std::string& errMsg,
                      const std::vector<struct sstd::arg_rule::opt_rule>& opt_vRule,
                      const std::vector<bool>& opt_vRule_inited)
{
    int res=0;
    
    for(uint i=0; i<opt_vRule_inited.size(); ++i){
        if(opt_vRule_inited[i]){ continue; }

        int   type = opt_vRule[i].return_val_type;
        void* ptr  = opt_vRule[i].return_val_ptr;
        bool tf = _fill_by_initial_val(ptr, type, opt_vRule[i].initial_val_ptr);
        if(!tf){
            errMsg+=sstd::pdbg_err_str(("Failed to init default value. Data type is `"+sstd::typeNum2str(type)+"`.\n").c_str());
            res = -1;
        }
    }
    
    return res;
}

//---

sstd::argparse::argparse(){}
sstd::argparse::~argparse(){}

const std::string& sstd::argparse::err() const { return this->errMsg; }

int sstd::argparse::_parse(const int argc, const char* argv[]
                           , const std::vector<struct sstd::arg_rule::cmd_rule>& cmd_vRule
                           , const std::vector<struct sstd::arg_rule::opt_rule>& opt_vRule)
{
    // Process cmd_vRule
    std::unordered_map<std::string,uint> ht_cmd2idx;
    for(uint i=0; i<cmd_vRule.size(); ++i){
        auto [itr, inserted] = ht_cmd2idx.insert({cmd_vRule[i].cmd, i});
        if(!inserted){ this->errMsg="sstd::argparse::_parse() failed. The duplicated command definition by `sstd::arg_rule::cmd()`. The `"+cmd_vRule[i].cmd+"` already exists.";  return -1; }
    }
    
    // Process opt_vRule
    std::unordered_map<std::string,uint> ht_opt2idx_short;
    std::unordered_map<std::string,uint> ht_opt2idx_full;
    for(uint i=0; i<opt_vRule.size(); ++i){
        auto [s_itr, s_inserted] = ht_opt2idx_short.insert({opt_vRule[i].opt_short, i});
        if(!s_inserted){ this->errMsg="sstd::argparse::_parse() failed. The duplicated option definition by `sstd::arg_rule::opt()`. The `"+opt_vRule[i].opt_short+"` already exists.";  return -1; }
        
        auto [f_itr, f_inserted] = ht_opt2idx_full.insert({opt_vRule[i].opt_full, i});
        if(!f_inserted){ this->errMsg="sstd::argparse::_parse() failed. The duplicated option definition by `sstd::arg_rule::opt()`. The `"+opt_vRule[i].opt_full+"` already exists.";  return -1; }
    }
    
    // Parse input argc and argv
    int cmd_idx;
    std::vector<std::string> cmd_args;
    std::vector<int> opt_vIdx;
    std::vector<std::vector<std::string>> opt_vArgs;
    int res_p = _parse_argc_argv(this->errMsg, cmd_idx, cmd_args, opt_vIdx, opt_vArgs, argc, argv, cmd_vRule, opt_vRule, ht_cmd2idx, ht_opt2idx_short, ht_opt2idx_full);
    
    // parse command
    int cmd_id = _process_cmd(this->errMsg, cmd_idx, cmd_args, cmd_vRule, ht_cmd2idx);
    
    // parse option
    std::vector<bool> opt_vRule_inited(opt_vRule.size(), false);
    int res_o1 = _process_opt     (this->errMsg, opt_vRule_inited, opt_vIdx, opt_vArgs, opt_vRule, ht_opt2idx_short, ht_opt2idx_full);
    int res_o2 = _process_opt_init(this->errMsg, opt_vRule, opt_vRule_inited);
    
    if(res_p==-1 || res_o1==-1 || res_o2==-1){ return -1; }
    return cmd_id;
}
