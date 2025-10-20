#include "argparse.hpp"
#include "../container/vector/slice.hpp"
#include "../print/print.hpp" // for debug
#include "../string/strEdit.hpp"
#include "../string/strmatch.hpp"

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

bool _is_short_opt(const std::stirng& s){
    return s.starts_with("-") && s.size()>=2 && sstd::isAlphabet(s[1]);
}
bool _is_full_opt(const std::stirng& s){
    return s.starts_with("--");
}
bool _is_cmd(const std::stirng& s, const std::unordered_map<std::string,uint>& ht_cmd2idx){
    auto itr = ht_cmd2idx.find( s );
    return itr!=ht_cmd2idx.end();
}

#define OPT_SHORT 1
#define OPT_FULL 2
#define CMD 3
#define NOT_A_SEPARATOR -1
int _is_separator(const std::string& s, const std::unordered_map<std::string,uint>& ht_cmd2idx){
    if      ( _is_short_opt(s)         ){ return OPT_SHORT;
    }else if( _is_full_opt (s)         ){ return OPT_FULL;
    }else if( _is_cmd( s, ht_cmd2idx ) ){ return CMD;
    }
    return NOT_A_SEPARATOR;
}

bool _parse_argc_argv(
                      // return variables:
                      std::vector<std::string>& res_cmdArgs,
                      std::vector<std::vector<std::string>>& res_vOptArgs_short,
                      std::vector<std::vector<std::string>>& res_vOptArgs_full,
                      
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
            if      (prev_type==OPT_SHORT){ std::vector<std::string> v; std::swap(v, tmp_args); res_vOptArgs_short.push_back(std::move(v));
            }else if(prev_type==OPT_FULL ){ std::vector<std::string> v; std::swap(v, tmp_args); res_vOptArgs_full. push_back(std::move(v));
            }else if(prev_type==CMD      ){ std::vector<std::string> v; std::swap(v, tmp_args); res_cmdArgs.       push_back(std::move(v));
            }
            prev_type = type;
        }
        
        tmp_args.push_back(std::move(s));
    }
    if      (prev_type==OPT_SHORT){ res_vOptArgs_short.push_back(std::move(tmp_args));
    }else if(prev_type==OPT_FULL ){ res_vOptArgs_full. push_back(std::move(tmp_args));
    }else if(prev_type==CMD      ){ res_cmdArgs.       push_back(std::move(tmp_args));
    }
    
    return true;
}
#undef NOT_A_SEPARATOR
#undef CMD
#undef OPT_FULL
#undef OPT_SHORT

//---

sstd::argparse::argparse(){}
sstd::argparse::~argparse(){}

int sstd::argparse::_parse(const int argc, const char* argv[]
                           , const std::vector<struct sstd::arg_rule::cmd_rule>& arg_vCmd
                           , const std::vector<struct sstd::arg_rule::opt_rule>& arg_vOpt)
{

    // Process arg_vCmd
    std::unordered_map<std::string,uint> ht_cmd2idx;
    for(uint i=0; i<arg_vCmd.size(); ++i){
        auto [itr, inserted] = ht_cmd2idx.insert({arg_vCmd[i].cmd, i});
        if(!inserted){ this->err="sstd::argparse::_parse() failed. The duplicated command definition by `sstd::arg_rule::cmd()`. The `"+arg_vCmd[i].cmd+"` already exists.";  return -1; }
    }

    // Process arg_vOpt
    std::unordered_map<std::string,uint> ht_opt2idx_short;
    std::unordered_map<std::string,uint> ht_opt2idx_full;
    for(uint i=0; i<arg_vOpt.size(); ++i){
        auto [s_itr, s_inserted] = ht_opt2idx_short.insert({arg_vOpt[i].opt_short, i});
        if(!s_inserted){ this->err="sstd::argparse::_parse() failed. The duplicated option definition by `sstd::arg_rule::opt()`. The `"+arg_vOpt[i].opt_short+"` already exists.";  return -1; }
        
        auto [f_itr, f_inserted] = ht_opt2idx_full.insert({arg_vOpt[i].opt_full, i});
        if(!f_inserted){ this->err="sstd::argparse::_parse() failed. The duplicated option definition by `sstd::arg_rule::opt()`. The `"+arg_vOpt[i].opt_full+"` already exists.";  return -1; }
    }
    sstd::printn(ht_opt2idx_short);
    sstd::printn(ht_opt2idx_full);

    sstd::printn(vArg);

    // Parse input argc and argv
    std::vector<std::string> cmdArgs;
    std::vector<std::vector<std::string>> vOptArgs_short;
    std::vector<std::vector<std::string>> vOptArgs_full;
    _parse_argc_argv(cmdArgs, vOptArgs_short, vOptArgs_full, argc, argv, ht_cmd2idx);
    
    // parse cmd
    uint cmd_id, cmd_idx;
    if(!_parse_cmd(cmd_id, cmdArgs, arg_vCmd, ht_cmd2idx)){ return -1; }
    if(!_fill_result_arg_by_val(arg_vCmd[cmd_idx], cmdArgs)){ return -1; }
    
    // parse opt
    std::vector<uint> vOptIdx;
    _parse_opt(vOptIdx, arg_vOpt, ht_opt2idx_full, ht_opt2idx_short, vOptArgs_short, vOptArgs_full);
    for(uint opt_idx=0; opt_idx<vOptIdx.size(); ++opt_idx){
        if(!_fill_result_arg_by_val(arg_vOpt[opt_idx], cmdArgs)){ return -1; }
    }
    
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
//    sstd::printn(arg_vCmd);
//    sstd::printn(arg_vOpt);

    int cmd_id=-1;
    
    return cmd_id;
}

