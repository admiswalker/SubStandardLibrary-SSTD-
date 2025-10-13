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

std::string sstd::_argparse::fn_T2K(const struct sstd::arg_rule::cmd_rule& rhs){
    return rhs.cmd;
}
struct sstd::arg_rule::cmd_rule sstd::_argparse::fn_T2V(struct sstd::arg_rule::cmd_rule&& rhs){
    return std::move(rhs);
}

//---

sstd::argparse::argparse(){}
sstd::argparse::~argparse(){}

int sstd::argparse::_parse(const int argc, const char* argv[], const std::vector<struct sstd::arg_rule::cmd_rule>& arg_stack){
    std::vector<std::string> vArg;
    for(uint i=0; i<argc; ++i){ vArg.push_back(argv[i]); }
    
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
    
    return cmd_id;
}

