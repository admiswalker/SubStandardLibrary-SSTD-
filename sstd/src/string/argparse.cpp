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

bool _is_short_opt(const std::stirng s){
    return s.size()>=2 && sstd::isAlphabet(s[1]);
}
bool _is_full_opt(const std::stirng s){
    return s.starts_with("--");
}

bool _parse_argc_argv(
                      // return variables:
                      std::string& err,
                      uint& cmdIdx,
                      std::vector<std::string>& cmdArgs,
                      std::vector<uint>& v_optIdx,
                      std::vector<std::vector<std::string>>& v_optArgs,
                      
                      // input variables:
                      const std::unordered_map<std::string,uint>& ht_cmd2idx,
                      const std::unordered_map<std::string,uint>& ht_opt2idx_full,
                      const std::unordered_map<std::string,uint>& ht_opt2idx_short,
                      
                      const std::vector<struct sstd::arg_rule::cmd_rule>& arg_vCmd,
                      const std::vector<struct sstd::arg_rule::opt_rule>& arg_vOpt,
                      
                      const int argc, const char* argv[])
{
    std::vector<std::string> vArg;
    for(uint i=1; i<argc; ++i){ vArg.push_back(argv[i]); } // Skip exe file name by `i=1`.
    
//    for(uint i=1; i<argc; ++i){
    for(uint i=0; i<vArg.size(); ++i){
//    std::string arg = argv[i];
        
        if(_is_short_opt(vArg[i])){
//            vArg[i] = vArg[i] && sstd::slice(1, sstd::end()); // rm '-' // あとで追加実装する
            vArg[i] = (const char*)&vArg[i][1]; // rm '-'
            std::string opts;
            std::swap(opts, vArg[i]); // Fill `vArg[i]` empty.

            if(opts.size()==1){
                auto itr = ht_opt2idx_short.find( "-"+opts );
                if(itr==ht_opt2idx_short.end()){
                    err = "ERROR: _parse_argc_argv() failed. User input argument `"+arg[1]+"` does NOT defined by `sstd::arg_rule::opt()`.";
                    return false;
                }
                v_optIdx.push_back( itr->second );
                v_optArgs.push_back( std::vector<std::string>() );
            }
            for(uint is=1; is<opts.size(); ++is){
                auto itr = ht_opt2idx_short.find( "-"+opts[is] );
                if(itr==ht_opt2idx_short.end()){
                    err = "ERROR: _parse_argc_argv() failed. User input argument `-"+opts[is]+"` does NOT defined by `sstd::arg_rule::opt()`.";
                    return false;
                }

                uint optIdx = itr->second;
                v_optIdx.push_back( optIdx );
                
                int opt_len = arg_vOpt[ optIdx ].opt_len;
                if(opt_len==-1){ // means that the option has variable length argument
                    opt_len=0;
                    
                }
//                    vArg && sstd::slice_mv(); // move 後の値の保証がない？ -> sstd::slice_sw() が必要? -> 初期値と sw する
                if( vArg.size() >= (i+opt_len) ){
                    err = "ERROR: _parse_argc_argv() failed. User input option `-"+opts[is]+"`, defined by `sstd::arg_rule::opt()` requires "+std::itos(opt_len)+" arguments, but there is only "++" arguments.";
                    return false;
                }
                std::vector<std::string> optArgs = vArg && sstd::slice_sw(i, i+opt_len);
                v_optArgs.push_back( std::move(optArgs) );
            }
            
            
        }else if(_is_full_opt(arg)){
            ;
        }
    }

    sstd::rmEmpty_ow( vArg ); // This line extracts `cmdArgs` by removing empty items which are filled empty by option rule parsing process.
    std::swap( cmdArgs, vArg );
    return true;

    //---
    
    std::vector<std::string> res_v;
//    std::vector<std::string> vOpt_short;

    for(uint i=0; i<vArg.size(); ++i){
        std::string& arg = vArg[i];
        if      (arg.starts_with("--")){
            auto itr = arg_vOpt.find( arg );
            if(itr==arg_vOpt.end()){ err="ERROR: The `"+arg+"` option is not defined."; return false; }
            
            ;
            
//        }else if(vArg[i].starts_with("-" )){
//            ;
        }else{
            ;
        }
    }
    
    return true;
}

sstd::argparse::argparse(){}
sstd::argparse::~argparse(){}

int sstd::argparse::_parse(const int argc, const char* argv[]
                           , const std::vector<struct sstd::arg_rule::cmd_rule>& arg_vCmd
                           , const std::vector<struct sstd::arg_rule::opt_rule>& arg_vOpt)
{
//    std::vector<std::string> vArg;
//    for(uint i=0; i<argc; ++i){ vArg.push_back(argv[i]); }

    // Process arg_vCmd
    std::unordered_map<std::string,uint> ht_cmd2idx;
    for(uint i=0; i<arg_vCmd.size(); ++i){
        auto [itr, inserted] = ht_cmd2idx.insert({arg_vCmd[i].cmd, i});
        if(!inserted){ this->err="sstd::argparse::_parse() failed. The duplicated command definition by `sstd::arg_rule::cmd()`. The `"+arg_vCmd[i].cmd+"` already exists.";  return -1; }
    }

    // Process arg_vOpt
    std::unordered_map<std::string,int> ht_opt2idx_full;
    std::unordered_map<std::string,int> ht_opt2idx_short;
    for(uint i=0; i<arg_vOpt.size(); ++i){
        auto [f_itr, f_inserted] = ht_opt2idx_full.insert({arg_vOpt[i].opt_full, i});
        if(!f_inserted){ this->err="sstd::argparse::_parse() failed. The duplicated option definition by `sstd::arg_rule::opt()`. The `"+arg_vOpt[i].opt_full+"` already exists.";  return -1; }
        
        auto [s_itr, s_inserted] = ht_opt2idx_short.insert({arg_vOpt[i].opt_short, i});
        if(!s_inserted){ this->err="sstd::argparse::_parse() failed. The duplicated option definition by `sstd::arg_rule::opt()`. The `"+arg_vOpt[i].opt_short+"` already exists.";  return -1; }
    }
    sstd::printn(ht_opt2idx_full);
    sstd::printn(ht_opt2idx_short);

    sstd::printn(vArg);
    vArg = 
    sstd::printn(vArg);
    
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

