#pragma once
//#include <stdio.h>
#include <string>
#include <vector>
#include "../definitions/typeDef.h"

namespace sstd{ class argparse; }

class sstd::argparse{
private:
//    std::vector<std::string> v_sw_cmd;
//    std::vector<std::string> ;
    std::vector<std::string> arg_stack;
    
public:
    argparse();
    ~argparse();

    void _stack(std::string&& s){
        arg_stack.push_back(s);
    }
    template <class Head, class... Tail>
    void _stack(Head&& head, Tail&&... tail){
        arg_stack.push_back(head);
        _stack(std::forward<Tail>(tail)...);
    }
    
    template<class... Args>
    int parse(int argc, char* argv[], Args... args
              ){
        _stack(std::forward<Args>(args)...);
        return 0;
    }

    const std::vector<std::string> _get_arg_stack(){ return arg_stack; }

//    template<typename T>
//    int add_switch_rule(const char* cmd, int cmd_num, T res_parsed_cmd, T default_val){
//        ;
//        return 0;
//    }
};

