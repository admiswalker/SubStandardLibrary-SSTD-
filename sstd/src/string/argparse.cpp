#include "argparse.hpp"
#include "../container/vector/slice.hpp"
#include "../print/print.hpp" // for debug
#include "../string/strEdit.hpp"

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

std::string sstd::arg_rule::fn_T2K(const struct sstd::arg_rule::cmd_rule& rhs){
    return rhs.cmd;
}
struct sstd::arg_rule::cmd_rule&& fn_T2V(struct sstd::arg_rule::cmd_rule&& rhs){
    return std::move(rhs);
}

//---

sstd::argparse::argparse(){}
sstd::argparse::~argparse(){}

int sstd::argparse::_parse(const int argc, const char* argv[], const std::vector<struct sstd::arg_rule::cmd_rule>& arg_stack){
    std::vector<std::string> vArg;
    for(uint i=0; i<argc; ++i){ vArg.push_back(argv[i]); }
    
    int max_cmd_len=0;
    std::unordered_map<std::string,uint> ht_cmd_cnt; // hash table, command, count
    
    for(uint i=0; i<arg_stack.size(); ++i){
        const struct sstd::arg_rule::cmd_rule& arg = arg_stack[i];
        std::vector<std::string> vTmp;
        if(!sstd::split_quotes(vTmp, arg.cmd, ' ')){ this->err="sstd::argparse::_parse() failed."; return -1; }
        
        std::string key = sstd::join(vTmp, ' ');
        uint argstack_idx = i;
        auto [itr, inserted] = ht_cmd_cnt.insert({key, argstack_idx});
        if(!inserted){ this->err="sstd::argparse::_parse() failed. Duplicated command definition by sstd::arg_rule::cmd()."; return -1; }

        max_cmd_len = std::max(max_cmd_len, (int)vTmp.size());
    }
    
    bool key_found=false;
    uint argstack_idx=0;
    for(int len=max_cmd_len; len!=0; --len){
        std::string key = sstd::join(vArg && sstd::slice(1, len+1), ' ');
        
        auto itr = ht_cmd_cnt.find( key );
        if(itr!=ht_cmd_cnt.end()){
            key_found = true;
            argstack_idx = itr->second;
            break;
        }
    }
    if(!key_found){ this->err="sstd::argparse::_parse() failed. User input command defined by `sstd::arg_rule::cmd()` did NOT found."; return -1; }
    
    
    int cmd_id = arg_stack[ argstack_idx ].cmd_id;
    
    printf("\n");
    printf("\n");
    printf("-------------------------------\n");
    printf("\n");
    sstd::printn(argc);
    sstd::printn(argv);
    sstd::printn(ht_cmd_cnt);
//    sstd::printn(min_cmd_len);
    sstd::printn(max_cmd_len);
    
    return cmd_id;
}

