#include "argparse.hpp"
#include "../print/print.hpp" // for debug

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

sstd::argparse::argparse(){}
sstd::argparse::~argparse(){}

int sstd::argparse::_parse(int argc, char* argv[], const std::vector<struct sstd::arg_rule::cmd_rule>& arg_stack){
    std::vector<std::string> vCmd;

    for(uint i=0; i<arg_stack.size(); ++i){
        const struct sstd::arg_rule::cmd_rule& arg = arg_stack[i];
        vCmd.push_back( arg.cmd );
    }

    printf("\n");
    sstd::printn(argc);
    sstd::printn(argv);
    sstd::printn(vCmd);
    printf("\n");
    
    return -1;
}

