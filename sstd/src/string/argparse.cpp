#include "argparse.hpp"
#include "../container/vector/slice.hpp"
#include "../container/vector/stdVector_expansion.hpp"
#include "../print/pdbg.hpp"
#include "../print/print.hpp" // for debug
#include "../string/strEdit.hpp"
#include "../string/strmatch.hpp"

//---

template<typename T>
std::vector<std::tuple<uint,uint>> sstd__duplicated(const std::vector<T>& v){
    std::unordered_map<T,uint> tbl_idx_cnt; // index, count

    for(uint i=0; i<v.size(); ++i){
        auto [itr, inserted] = tbl_idx_cnt.insert({v[i], 1});
        if(!inserted){ ++(itr->second); }
    }
    
    std::vector<std::tuple<uint,uint>> out_vDuplicated; // index of `v_in`, count
    for(auto itr=tbl_idx_cnt.begin(); itr!=tbl_idx_cnt.end(); ++itr){
        if(itr->second>=2){
            out_vDuplicated.push_back(std::make_tuple(itr->first, itr->second));
        }
    }
    
    return out_vDuplicated;
}

//---

bool _fill_by_initial_val(void* ptr, const int type, const sstd::void_ptr& initial_val_ptr){
    switch(type){
    case sstd::num_bool:      { std::swap(*(bool*)ptr,               *(bool*)initial_val_ptr.ptr()              ); } break;
    case sstd::num_vec_int32: { std::swap(*(std::vector<int32>*)ptr, *(std::vector<int32>*)initial_val_ptr.ptr()); } break;
    default: { return false; }
    }
    return true;
}

//---

bool sstd__str2val(std::vector<int>& return_val, const std::vector<std::string>& v){
    for(uint i=0; i<v.size(); ++i){
        if(!sstd::isNum(v[i])){ return false; }
        return_val.push_back( std::stoi(v[i]) );
    }
    return true;
}

bool sstd__str2val(bool& return_val, const std::vector<std::string>& v){
    if(v.size()!=1){ return false; }
    const std::string& rhs=v[0];
    
    if      (rhs=="T" || rhs=="true" || rhs=="True"){ return_val=true; return true;
    }else if(rhs=="F" || rhs=="false" || rhs=="False"){ return_val=false; return true;
    }else if(sstd::isNum(rhs)){ return_val=(std::stoi(rhs)!=0); return true;
    }
    
    return false;
}

int sstd__str2voidp(void* return_val_ptr, const int type, const std::vector<std::string>& v){
    
    switch(type){
    case sstd::num_bool:      { if(!sstd__str2val(*(bool              *)return_val_ptr, v)){return -1;} } break;
    case sstd::num_vec_int32: { if(!sstd__str2val(*(std::vector<int32>*)return_val_ptr, v)){return -1;} } break;
    default: { return -2; }
    }
    
    return true;
}

int _get_cmd_id(const struct sstd::arg_rule::cmd_rule& cmdRule){ return cmdRule.cmd_id; }
int _get_cmd_id(const struct sstd::arg_rule::opt_rule& optRule){ return 0; }
template<typename T>
int _fill_result_arg_by_val(const T& rule, const std::vector<std::string>& cmdArgs){
    
//    if(rule.expected_num_of_args==-1){
//        // Under construction
//    }
//    if(cmdArgs.size()!=1+rule.expected_num_of_args){ return false; }

    std::vector<std::string> args = cmdArgs&&sstd::slice(1,sstd::end());

    int   type = rule.return_val_type;
    void* ptr  = rule.return_val_ptr;
    
    if(args.size()==0){
        bool tf = _fill_by_initial_val(ptr, type, rule.initial_val_ptr);
        if(!tf){
            //        this->err="Failed to convert string to value.";
            return -1;
        }
        
    }else{
        bool tf = sstd__str2voidp(ptr, type, args);
        if(tf==-1){
            this->err=pdbg_err_str()+"ERROR: The input value `` ";
            // print_base() が，直接標準出力にデータを出力するので，文字列変換として使えない．．．
            // obj2str の定義が先に必要そう．．．
            return -1;
        }else if(tf==-2){
            return -1;
        }
    }

    return _get_cmd_id(rule);
}

//---

void sstd::print_base(const sstd::arg_rule::cmd_rule& rhs){
    printf("cmd_id: %d\n", rhs.cmd_id);
    printf("return_val_ptr: <Print function is NOT implemented>\n");
    printf("initial_val_ptr: <Print function is NOT implemented>\n");
    printf("cmd: `%s`\n", rhs.cmd.c_str());
    printf("expected_num_of_args: %d\n", rhs.expected_num_of_args);
    printf(",\n");
}

//---

void sstd::print_base(const sstd::arg_rule::opt_rule& rhs){
    printf("return_val_ptr: <Print function is NOT implemented>\n");
    printf("initial_val_ptr: <Print function is NOT implemented>\n");
    printf("opt_short: `%s`\n", rhs.opt_short.c_str());
    printf("opt_full: `%s`\n", rhs.opt_full.c_str());
    printf("expected_num_of_args: %d\n", rhs.expected_num_of_args);
    printf(",\n");
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
    return s.starts_with("-") && s.size()>=2 && sstd::isAlphabet(s[1]);
}
bool _is_opt_full(const std::string& s){
    return s.starts_with("--") && s.size()>=3 && sstd::isAlphabet(s[2]);
}
bool _is_opt(const std::string& s){
    return ( _is_opt_short(s) || _is_opt_full(s) );
}

#define OPT 1
#define CMD 2
#define NOT_A_SEPARATOR -1
int _is_separator(const std::string& s, const std::unordered_map<std::string,uint>& ht_cmd2idx){
    if      ( _is_opt(s)             ){ return OPT;
    }else if( _is_cmd(s, ht_cmd2idx) ){ return CMD;
    }
    return NOT_A_SEPARATOR;
}

bool _parse_argc_argv(
                      // return variables:
                      std::vector<std::string>& res_cmdArgs,
                      std::vector<std::vector<std::string>>& res_vOptArgs,
                      
                      // input variables:
                      const int argc, const char* argv[],
                      const std::unordered_map<std::string,uint>& ht_cmd2idx)
{
    int prev_type=0;
    std::vector<std::string> tmp_args;
    for(uint i=1; i<(uint)argc; ++i){
        std::string s = argv[i];

        int type = _is_separator(s, ht_cmd2idx);
        if(type!=-1){
            if      (prev_type==CMD){ std::vector<std::string> v; std::swap(v, tmp_args); res_cmdArgs  <<= std::move(v);
            }else if(prev_type==OPT){ std::vector<std::string> v; std::swap(v, tmp_args); res_vOptArgs <<= std::move(v);
            }
            prev_type = type;
        }
        
        tmp_args.push_back(std::move(s));
    }
    if      (prev_type==CMD){ res_cmdArgs  <<= std::move(tmp_args); // TODO: operator の先でmove が機能するようにする
    }else if(prev_type==OPT){ res_vOptArgs <<= std::move(tmp_args);
    }
    
    return true;
}
#undef NOT_A_SEPARATOR
#undef CMD
#undef OPT

//---

int _parse_cmd(const std::string& cmd,
                const std::unordered_map<std::string,uint>& ht_cmd2idx)
{
    auto itr = ht_cmd2idx.find( cmd );
    if(itr==ht_cmd2idx.end()){ return -1; }
    int cmd_idx = (int)itr->second;
    return cmd_idx;
}

int _get_opt(const std::string& opt, const std::unordered_map<std::string,uint>& ht_opt2idx){
    auto itr = ht_opt2idx.find( opt );
    if(itr==ht_opt2idx.end()){ return -1; }
    return itr->second;
}
std::vector<int> _parse_opt(const std::vector<std::vector<std::string>>& vOptArgs,
                             const std::unordered_map<std::string,uint>& ht_opt2idx_short,
                             const std::unordered_map<std::string,uint>& ht_opt2idx_full,
                             const std::vector<struct sstd::arg_rule::opt_rule>& vOptRule)
{
    std::vector<int> res_vOptIdx;
    
    for(uint i=0; i<vOptArgs.size(); ++i){
        const std::vector<std::string>& optArgs = vOptArgs[i];

        if(optArgs.size()==0){
            res_vOptIdx.push_back(-1);
        }else if(_is_opt_short(optArgs[0])){
            // Opt is short.
            const std::string& opts = optArgs[0];
            sstd::printn_all(opts);
            for(uint is=1; is<opts.size(); ++is){ // skip '-'
                int opt_idx = _get_opt(std::string("-")+opts[is], ht_opt2idx_short);
                res_vOptIdx.push_back(opt_idx);
            }
        }else{
            // Opt is full.
            const std::string& opt = optArgs[0];
            int opt_idx = _get_opt(opt, ht_opt2idx_full);
            res_vOptIdx.push_back(opt_idx);
        }
    }
    
    return res_vOptIdx;
}

//---

sstd::argparse::argparse(){}
sstd::argparse::~argparse(){}

int sstd::argparse::_parse(const int argc, const char* argv[]
                           , const std::vector<struct sstd::arg_rule::cmd_rule>& vCmdRule
                           , const std::vector<struct sstd::arg_rule::opt_rule>& vOptRule)
{
    // Process vCmdRule
    std::unordered_map<std::string,uint> ht_cmd2idx;
    for(uint i=0; i<vCmdRule.size(); ++i){
        auto [itr, inserted] = ht_cmd2idx.insert({vCmdRule[i].cmd, i});
        if(!inserted){ this->err="sstd::argparse::_parse() failed. The duplicated command definition by `sstd::arg_rule::cmd()`. The `"+vCmdRule[i].cmd+"` already exists.";  return -1; }
    }
    sstd::printn_all("");
    
    // Process vOptRule
    std::unordered_map<std::string,uint> ht_opt2idx_short;
    std::unordered_map<std::string,uint> ht_opt2idx_full;
    for(uint i=0; i<vOptRule.size(); ++i){
        auto [s_itr, s_inserted] = ht_opt2idx_short.insert({vOptRule[i].opt_short, i});
        if(!s_inserted){ this->err="sstd::argparse::_parse() failed. The duplicated option definition by `sstd::arg_rule::opt()`. The `"+vOptRule[i].opt_short+"` already exists.";  return -1; }
        
        auto [f_itr, f_inserted] = ht_opt2idx_full.insert({vOptRule[i].opt_full, i});
        if(!f_inserted){ this->err="sstd::argparse::_parse() failed. The duplicated option definition by `sstd::arg_rule::opt()`. The `"+vOptRule[i].opt_full+"` already exists.";  return -1; }
    }
    sstd::printn_all("");
    
    // Parse input argc and argv
    std::vector<std::string> cmdArgs;
    std::vector<std::vector<std::string>> vOptArgs;
    _parse_argc_argv(cmdArgs, vOptArgs, argc, argv, ht_cmd2idx);
    sstd::printn_all("");
    
    // parse cmd
    int cmd_id = -2;
    if(cmdArgs.size()!=0){
        int cmd_idx = _parse_cmd(cmdArgs[0], ht_cmd2idx); if(cmd_idx==-1){ return -1; }
        sstd::printn_all(cmd_idx);
        cmd_id = _fill_result_arg_by_val(vCmdRule[cmd_idx], cmdArgs); if(cmd_id==-1){ return -1; }
        sstd::printn_all(cmd_id);
    }
    
    // parse opt
    sstd::printn_all(vOptArgs);
    std::vector<int> vOptIdx = _parse_opt(vOptArgs, ht_opt2idx_short, ht_opt2idx_full, vOptRule);
    sstd::printn_all(vOptIdx);
    
    std::vector<std::tuple<uint,uint>> vDuplicated = sstd__duplicated(vOptIdx);
    sstd::printn_all(vDuplicated);
    if(vDuplicated.size()!=0){
        this->err = "ERROR: There are duplicated definition in the arg input.";
        return -1;
    }
    for(uint i=0; i<vOptIdx.size(); ++i){
        int opt_idx = vOptIdx[i];
        if(opt_idx==-1){
            this->err = "ERROR:";
            return -1;
        }
        sstd::printn_all(opt_idx);
        int res = _fill_result_arg_by_val(vOptRule[opt_idx], vOptArgs[opt_idx]);
        if(res!=0){ return -1; }
    }
    
    return cmd_id;
}

