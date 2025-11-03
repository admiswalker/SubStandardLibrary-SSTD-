#include "argparse.hpp"
#include "../container/vector/slice.hpp"
#include "../container/vector/stdVector_expansion.hpp"
#include "../print/pdbg.hpp"
#include "../print/print.hpp" // for debug
#include "../string/ssprintf.hpp"
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
    
    return 0;
}

int _get_cmd_id(const struct sstd::arg_rule::cmd_rule& cmdRule){ return cmdRule.cmd_id; }
int _get_cmd_id(const struct sstd::arg_rule::opt_rule& optRule){ return 0; }
template<typename T>
int _fill_result_arg_by_val(std::string& errMsg, const T& rule, const std::vector<std::string>& input_args){

    std::vector<std::string> args = input_args&&sstd::slice(1,sstd::end());
    uint arg_len = rule.expected_num_of_args;
    
    int res=0;
    if(arg_len!=-1 && args.size()!=arg_len){
        errMsg+=sstd::pdbg_err_str(("The number of input argument(s) is `"+std::to_string(args.size())+"` ("+sstd::to_string(input_args)+"). But `"+std::to_string(arg_len)+"` argument(s) are expected by the definition of sstd::arg_rule::opt().\n").c_str());
        res = -1;
    }

    int   type = rule.return_val_type;
    void* ptr  = rule.return_val_ptr;
    
    if(res==0 && args.size()!=0){
        res = sstd__str2voidp(ptr, type, args);
        if(res==-1){
            errMsg+=sstd::pdbg_err_str(("The input arguments of `"+sstd::to_string(input_args)+"` is failed to convert to `"+sstd::typeNum2str(type)+"` type.\n").c_str());
        }else if(res==-2){
            errMsg+=sstd::pdbg_err_str(("The input data type of `"+sstd::typeNum2str(type)+"` is our of support.\n").c_str());
        }
    }
    if(res!=0 || args.size()==0){
        bool tf = _fill_by_initial_val(ptr, type, rule.initial_val_ptr);
        if(!tf){
            errMsg+=sstd::pdbg_err_str(("Failed to init default value. Data type is `"+sstd::typeNum2str(type)+"`.\n").c_str());
            return -1;
        }
    }
    if(res!=0){
        return -1;
    }
    
    return _get_cmd_id(rule);
}

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

#define DEFAULT 0
#define CMD 1
#define OPT 2
#define OPT_M 3
#define NOT_A_SEPARATOR -1
int _is_separator(const std::string& s, const std::unordered_map<std::string,uint>& ht_cmd2idx){
    if      ( _is_opt_fs         (s)             ){ return OPT;
    }else if( _is_opt_multi_short(s)             ){ return OPT_M;
    }else if( _is_cmd            (s, ht_cmd2idx) ){ return CMD;
    }
    return NOT_A_SEPARATOR;
}

bool _parse_argc_argv(
                      std::string& errMsg,
                      
                      // return variables:
                      std::vector<std::string>& res_cmd_args,
                      std::vector<std::vector<std::string>>& res_opt_vArgs,
                      
                      // input variables:
                      const int argc, const char* argv[],
                      const std::unordered_map<std::string,uint>& ht_cmd2idx)
{
    int prev_type=DEFAULT;
    std::vector<std::string> tmp_args;
    for(uint i=1; i<(uint)argc; ++i){
        std::string s = argv[i];

        int type = _is_separator(s, ht_cmd2idx);
        if(type!=-1){
            if      (prev_type==CMD  ){ std::vector<std::string> v; std::swap(v, tmp_args); res_cmd_args  <<= std::move(v);
            }else if(prev_type==OPT  ){ std::vector<std::string> v; std::swap(v, tmp_args); res_opt_vArgs <<= std::move(v);
            }else if(prev_type==OPT_M){
                // parse "-abc" -> "-a", "-b" and "-c"
                
                if(tmp_args.size()!=1){ errMsg+=sstd::pdbg_err_str(("The input option defined by sstd::arg_rule::opt() can NOT take arguments inputted as `"+sstd::to_string(tmp_args)+"`.\n").c_str()); return -1; }
                
                for(uint i=1; i<tmp_args[0].size(); ++i){ // `i=1` means to skipp '-'.
                    res_opt_vArgs <<= std::vector<std::string>({ std::string("-")+tmp_args[0][i] });
                }
            }
            prev_type = type;
        }
        
        tmp_args.push_back(std::move(s));
    }
    if      (prev_type==CMD  ){ res_cmd_args  <<= std::move(tmp_args); // TODO: operator の先でmove が機能するようにする
    }else if(prev_type==OPT  ){ res_opt_vArgs <<= std::move(tmp_args);
    }else if(prev_type==OPT_M){
        // parse "-abc" -> "-a", "-b" and "-c"
        
        if(tmp_args.size()!=1){ errMsg+=sstd::pdbg_err_str(("The input option defined by sstd::arg_rule::opt() can NOT take arguments inputted as `"+sstd::to_string(tmp_args)+"`.\n").c_str()); return -1; }
        
        std::vector<std::string> v;
        for(uint i=1; i<tmp_args[0].size(); ++i){ // `i=1` means to skipp '-'.
            res_opt_vArgs <<= std::vector<std::string>({ std::string("-")+tmp_args[0][i] });
        }
    }
    
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
                 const std::vector<std::string>& cmd_args,
                 const std::vector<struct sstd::arg_rule::cmd_rule>& cmd_vRule,
                 const std::unordered_map<std::string,uint>& ht_cmd2idx)
{
    int cmd_id = sstd::arg_rule::num_command_does_not_exist;
    
    if(cmd_args.size()!=0){
        int cmd_idx = _parse_cmd(cmd_args[0], ht_cmd2idx); if(cmd_idx==-1){ return -1; }
        cmd_id = _fill_result_arg_by_val(errMsg, cmd_vRule[cmd_idx], cmd_args); if(cmd_id==-1){ return -1; }
    }
    
    return cmd_id;
}

//---

int _get_opt(const std::string& opt, const std::unordered_map<std::string,uint>& ht_opt2idx){
    auto itr = ht_opt2idx.find( opt );
    if(itr==ht_opt2idx.end()){ return -1; }
    return itr->second;
}
std::vector<int> _parse_opt(const std::vector<std::vector<std::string>>& opt_vArgs,
                             const std::vector<struct sstd::arg_rule::opt_rule>& opt_vRule,
                             const std::unordered_map<std::string,uint>& ht_opt2idx_short,
                             const std::unordered_map<std::string,uint>& ht_opt2idx_full)
{
    std::vector<int> res_opt_vIdx;
    
    for(uint i=0; i<opt_vArgs.size(); ++i){
        const std::vector<std::string>& optArgs = opt_vArgs[i];
        
        if(optArgs.size()==0){
            res_opt_vIdx.push_back(-1);
        }else if(_is_opt_short(optArgs[0])){
            // Opt is short.
            const std::string& opts = optArgs[0];
            for(uint is=1; is<opts.size(); ++is){ // skip '-'
                int opt_idx = _get_opt(std::string("-")+opts[is], ht_opt2idx_short);
                res_opt_vIdx.push_back(opt_idx);
            }
        }else{
            // Opt is full.
            const std::string& opt = optArgs[0];
            int opt_idx = _get_opt(opt, ht_opt2idx_full);
            res_opt_vIdx.push_back(opt_idx);
        }
    }
    
    return res_opt_vIdx;
}

int _process_opt(std::string& errMsg,
                 std::vector<bool>& opt_vRule_inited,
                 const std::vector<std::vector<std::string>>& opt_vArgs,
                 const std::vector<struct sstd::arg_rule::opt_rule>& opt_vRule,
                 const std::unordered_map<std::string,uint>& ht_opt2idx_short,
                 const std::unordered_map<std::string,uint>& ht_opt2idx_full)
{
    std::vector<int> opt_vIdx = _parse_opt(opt_vArgs, opt_vRule, ht_opt2idx_short, ht_opt2idx_full);
    
    std::vector<std::tuple<uint,uint>> vDuplicated = sstd__duplicated(opt_vIdx);
    if(vDuplicated.size()!=0){
        errMsg = "ERROR: There are duplicated definition in the arg input.";
        return -1;
    }
    for(uint i=0; i<opt_vIdx.size(); ++i){
        int opt_idx = opt_vIdx[i];
        if(opt_idx==-1){
            errMsg+=sstd::pdbg_err_str(("The input argument(s) of `"+sstd::to_string(opt_vArgs[i])+"` is NOT defnied by sstd::arg_rule::opt() as an input option.\n").c_str());
            return -1;
        }
        int res = _fill_result_arg_by_val(errMsg, opt_vRule[opt_idx], opt_vArgs[opt_idx]);
        opt_vRule_inited[opt_idx] = true; // Even if the `_fill_result_arg_by_val` failed, this function tried to update the option by default value.
        if(res!=0){ return -1; }
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
    std::vector<std::string> cmd_args;
    std::vector<std::vector<std::string>> opt_vArgs;
    int res = _parse_argc_argv(this->errMsg, cmd_args, opt_vArgs, argc, argv, ht_cmd2idx);
    if(res!=0){ return -1; }
    
    // parse command
    int cmd_id = _process_cmd(this->errMsg, cmd_args, cmd_vRule, ht_cmd2idx);
    
    // parse option
    std::vector<bool> opt_vRule_inited(opt_vRule.size(), false);
    int res1 = _process_opt     (this->errMsg, opt_vRule_inited, opt_vArgs, opt_vRule, ht_opt2idx_short, ht_opt2idx_full);
    sstd::printn_all(res1);
    int res2 = _process_opt_init(this->errMsg, opt_vRule, opt_vRule_inited);
    sstd::printn_all(res2);
    if(res1==-1 || res2==-1){ return -1; }
    
    return cmd_id;
}
