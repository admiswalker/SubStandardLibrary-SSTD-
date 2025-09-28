#pragma once
//#include <stdio.h>
#include <string>
#include <vector>
#include "../definitions/typeDef.h"
#include "../memory/void_ptr.hpp"

namespace sstd{
    template<typename T>
    void _argstack(std::vector<T>& res_stack, T&& obj){
        res_stack.push_back(obj);
    }
    template<typename T, class Head, class... Tail>
    void _argstack(std::vector<T>& res_stack, Head&& head, Tail&&... tail){
        res_stack.push_back(head);
        sstd::_argstack(res_stack, std::forward<Tail>(tail)...);
    }
    
    template<typename T, class... Args>
    void argstack(std::vector<T>& res_stack, Args... args){
        sstd::_argstack(res_stack, std::forward<Args>(args)...);
    }
}

//---

namespace sstd::arg_rule{
    struct cmd_rule{
        int cmd_id;
        sstd::void_ptr return_val_ptr;
        sstd::void_ptr initial_val_ptr;
        std::string cmd;
        int expected_num_of_args;
    };
//    struct opt_rule{
//    }
    
    struct sstd::arg_rule::cmd_rule cmd(const char* ps); // temporal implementation (delete this line later)
    struct sstd::arg_rule::cmd_rule cmd(const int cmd_id,                                      const char* cmd, const int expected_num_of_args);
//    std::string cmd(const int cmd_id, T& return_val, const T& initial_val, const char* cmd, const int expected_num_of_args);
}

namespace sstd{
    void print_base(const sstd::arg_rule::cmd_rule& rhs);
}

//---

namespace sstd{ class argparse; }

class sstd::argparse{
private:
//    std::vector<std::string> v_sw_cmd;
//    std::vector<std::string> ;
    std::vector<struct sstd::arg_rule::cmd_rule> arg_stack;
    
public:
    argparse();
    ~argparse();

    template<class... Args>
    int parse(int argc, char* argv[], Args... args){
        sstd::argstack(arg_stack, args...);
        return 0;
    }

    const std::vector<struct sstd::arg_rule::cmd_rule> _get_arg_stack(){ return arg_stack; }

//    template<typename T>
//    int add_switch_rule(const char* cmd, int cmd_num, T res_parsed_cmd, T default_val){
//        ;
//        return 0;
//    }
};


