#include "argparse.hpp"
#include "../container/vector/slice.hpp"
#include "../print/print.hpp" // for debug
#include "../string/strEdit.hpp"
#include "../string/strmatch.hpp"

//---

template<typename T>
std::vector<std::tuple<uint,uint>> sstd__duplicated(const std::vector<T>& v_in){
    std::vector<std::tuple<uint,uint>> out_vDuplicated; // index of `v_in`, count
    std::unordered_map<T,uint> tbl_iIdx_oIdx; // in index, out index

    uint outIdx=0;
    for(uint i=0; i<v_in.size(); ++i){
        auto [itr, inserted] = tbl_iIdx_oIdx.insert({v_in[i], outIdx});
        if(inserted){
            out_vDuplicated.push_back(std::make_tuple({i, 1}));
            ++outIdx;
        }else{
            ++std::get<1>( out_vDuplicated[ itr->second ] );
        }
    }
    
    return out_vDuplicated;
}

//---

bool sstd__str2val(std::vector<int>& return_val, const std::vector<std::string>& v){
    for(uint i=0; i<v.size(); ++i){
        if(!sstd::isNum(v[i])){ return false; }
        return_val.push_back( std::stoi(v[i]) );
    }
    return true;
}

bool sstd__str2voidp(const void* return_val_ptr, const int type, const std::vector<std::string>& v){
    
    switch(type){
    case num_vec_int32: { if(!sstd__str2val(return_val_ptr, v)){return false;} } break;
    default: { return false; }
    }
    
    return true;
}

template<typename T>
bool _fill_result_arg_by_val(int& res_cmd_id, const T& rule, const std::vector<std::string>& cmdArgs){
    
//    if(rule.expected_num_of_args==-1){
//        // Under construction
//    }
//    if(cmdArgs.size()!=1+rule.expected_num_of_args){ return false; }

    int   return_val_type = rule.return_val_type;
    void* return_val_ptr  = rule.return_val_ptr;
    bool tf = _str2voidp(return_val_type, return_val_ptr, cmdArgs&&sstd::slice(1,sstd::end()));
    if(!tf){
        this->err="Failed to convert string to value.";
    }

    //---
    
//    void* return_val_ptr = itr->second.return_val_ptr;
//    for(uint i=0; i<vCmdArg.size(); ++i){
//        if(!sstd::isNum(vCmdArg[i])){
//            this->err="sstd::argparse::_parse() failed. The `"+cr.cmd+"` command expects integer arguments, but `"+vCmdArg[i]+"` is NOT integer.";
//            return -1;
//        }
//        ((std::vector<int>*)return_val_ptr)->push_back( std::stoi(vCmdArg[i]) );
//    }

    return true;
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

bool _is_cmd(const std::stirng& s){
    auto itr = ht_cmd2idx.find( s );
    return itr!=ht_cmd2idx.end();
}
bool _is_opt_short(const std::stirng& s){
    return s.starts_with("-") && s.size()>=2 && sstd::isAlphabet(s[1]);
}
bool _is_opt_full(const std::stirng& s){
    return s.starts_with("--") && s.size()>=3 && sstd::isAlphabet(s[2]);
}
bool _is_opt(const std::stirng& s){
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
    for(uint i=1; i<argc; ++i){
        std::string s = argv[i];

        int type = _is_separator(s, ht_cmd2idx);
        if(type!=-1){
            if      (prev_type==OPT){ std::vector<std::string> v; std::swap(v, tmp_args); res_vOptArgs.push_back(std::move(v));
            }else if(prev_type==CMD){ std::vector<std::string> v; std::swap(v, tmp_args); res_cmdArgs. push_back(std::move(v));
            }
            prev_type = type;
        }
        
        tmp_args.push_back(std::move(s));
    }
    if      (prev_type==OPT){ res_vOptArgs.push_back(std::move(tmp_args));
    }else if(prev_type==CMD){ res_cmdArgs. push_back(std::move(tmp_args));
    }
    
    return true;
}
#undef NOT_A_SEPARATOR
#undef CMD
#undef OPT

//---

bool _parse_cmd(uint& res_cmd_idx,
                const std::string& cmd,
                const std::unordered_map<std::string,uint>& ht_cmd2idx)
{
    auto itr = ht_cmd2idx.find( cmd );
    if(itr!=ht_cmd2idx.end()){ return false; }
    res_cmd_idx = itr->second;
    return true;
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
        if(_is_opt_short(vOptArgs[i])){
            // Opt is short.
            std::string& opts = vOptArgs[i];
            for(uint is=1; is<opts.size(); ++is){ // skip '-'
                int opt_idx = _get_opt("-"+opts[is], ht_opt2idx_short);
                res_vOptIdx.push_back(opt_idx);
            }
        }else{
            // Opt is full.
            std::string& opt = vOptArgs[i];
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
    
    // Process vOptRule
    std::unordered_map<std::string,uint> ht_opt2idx_short;
    std::unordered_map<std::string,uint> ht_opt2idx_full;
    for(uint i=0; i<vOptRule.size(); ++i){
        auto [s_itr, s_inserted] = ht_opt2idx_short.insert({vOptRule[i].opt_short, i});
        if(!s_inserted){ this->err="sstd::argparse::_parse() failed. The duplicated option definition by `sstd::arg_rule::opt()`. The `"+vOptRule[i].opt_short+"` already exists.";  return -1; }
        
        auto [f_itr, f_inserted] = ht_opt2idx_full.insert({vOptRule[i].opt_full, i});
        if(!f_inserted){ this->err="sstd::argparse::_parse() failed. The duplicated option definition by `sstd::arg_rule::opt()`. The `"+vOptRule[i].opt_full+"` already exists.";  return -1; }
    }
    sstd::printn(ht_opt2idx_short);
    sstd::printn(ht_opt2idx_full);
    
    sstd::printn(vArg);

    // Parse input argc and argv
    std::vector<std::string> cmdArgs;
    std::vector<std::vector<std::string>> vOptArgs;
    _parse_argc_argv(cmdArgs, vOptArgs, argc, argv, ht_cmd2idx);
    if(cmdArgs.size()==0){ return -1; }
    
    // parse cmd
    uint cmd_idx;
    if(!_parse_cmd(cmd_id, cmd_idx, cmdArgs[0], vCmdRule, ht_cmd2idx)){ return -1; }
    
    int cmd_id;
    if(!_fill_result_arg_by_val(cmd_id, vCmdRule[cmd_idx], cmdArgs)){ return -1; }
    
    // parse opt
    std::vector<uint> vOptIdx;
    if(!_parse_opt(vOptIdx, vOptArgs, ht_opt2idx_full, ht_opt2idx_short, vOptRule)){ return -1; }
    std::vector<std::tuple<uint,uint>> vDuplicated = sstd__duplicated(vOptIdx);
    if(vDuplicated.size()!=0){
        this->err = "ERROR: There are duplicated definition in the arg input.";
        return false;
    }
    for(uint opt_idx=0; opt_idx<vOptIdx.size(); ++opt_idx){
        if(vOptRule[opt_idx]==-1){
            this->err = "ERROR:";
            return false;
        }
        if(!_fill_result_arg_by_val(vOptRule[opt_idx], vOptArgs[opt_idx])){ return -1; }
    }
    
    return cmd_id;
    
    /*
    int max_cmd_len=0;
    for(auto itr=arg_hash_cmd.begin(); itr!=arg_hash_cmd.end(); ++itr){
        const std::string& cmd_definition = itr->first;
        itr->second.cmd_len = (int)sstd::split(cmd_definition, ' ').size();
        max_cmd_len = std::max(max_cmd_len, itr->second.cmd_len);
    }
    
    bool key_found=false;
    auto itr = arg_hash_cmd.begin();
    for(uint len=max_cmd_len; len!=0; --len){
        std::string key = sstd::join(vArg && sstd::slice(1, len+1), ' ');
        
        itr = arg_hash_cmd.find( key );
        if(itr!=arg_hash_cmd.end()){
            key_found = true;
            break;
        }
    }
    if(!key_found){ this->err="sstd::argparse::_parse() failed. User input command defined by `sstd::arg_rule::cmd()` does NOT found."; return -1; }

    struct sstd::arg_rule::cmd_rule& cr = itr->second;
    int cmd_id = cr.cmd_id;
    int cmd_len = cr.cmd_len;
    sstd::printn(cr.cmd_id);
    sstd::printn(cr.cmd_len);
    
    std::vector<std::string> vCmdArg = vArg && sstd::slice(1+cmd_len, sstd::end());
    sstd::printn(vCmdArg);

    sstd::printn(itr->second.return_val_type);

    void* return_val_ptr = itr->second.return_val_ptr;

    for(uint i=0; i<vCmdArg.size(); ++i){
        if(!sstd::isNum(vCmdArg[i])){
            this->err="sstd::argparse::_parse() failed. The `"+cr.cmd+"` command expects integer arguments, but `"+vCmdArg[i]+"` is NOT integer.";
            return -1;
        }
        ((std::vector<int>*)return_val_ptr)->push_back( std::stoi(vCmdArg[i]) );
    }
    
    printf("\n");
    printf("\n");
    printf("-------------------------------\n");
    printf("\n");
    sstd::printn(argc);
    sstd::printn(argv);
//    sstd::printn(ht_cmd_cnt);
//    sstd::printn(min_cmd_len);
    sstd::printn(max_cmd_len);
    */
    
    printf("\n");
    printf("\n");
    printf("-------------------------------\n");
    printf("\n");
//    sstd::printn(vCmdRule);
//    sstd::printn(vOptRule);

    int cmd_id=-1;
    
    return cmd_id;
}

