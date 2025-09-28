#include "argparse.hpp"

//---

void sstd::print_base(const sstd::arg_rule::cmd_rule& rhs){
    printf("cmd_id: %d\n", rhs.cmd_id);
    printf("return_val_ptr: <TBD>\n");
    printf("initial_val_ptr: <TBD>\n");
    printf("cmd: %s\n", rhs.cmd.c_str());
    printf("expected_num_of_args: %d\n", rhs.expected_num_of_args);
    printf(",\n");
}

//---

struct sstd::arg_rule::cmd_rule sstd::arg_rule::cmd(const char* ps){
    sstd::arg_rule::cmd_rule res;
    res.cmd = std::string(ps);
    return res;
}

struct sstd::arg_rule::cmd_rule sstd::arg_rule::cmd(const int cmd_id,                                      const char* cmd, const int expected_num_of_args){
    sstd::arg_rule::cmd_rule res;
    res.cmd_id = cmd_id;
    res.cmd = std::string(cmd);
    res.expected_num_of_args = expected_num_of_args;
    return res;
}

//---

sstd::argparse::argparse(){}
sstd::argparse::~argparse(){}

//int sstd::argparse::parse(const int argc, const char* argv[]){
//    return 0;
//}

