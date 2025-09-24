#pragma once
//#include <stdio.h>
#include <string>
#include <vector>
#include "../definitions/typeDef.h"

namespace sstd{
    template<typename T>
    void _argstack(std::vector<T>& res_stack, T&& obj){
        res_stack.push_back(obj);
    }
    template<typename T, class Head, class... Tail>
    void _argstack(std::vector<T>& res_stack, Head&& head, Tail&&... tail){
        res_stack.push_back(head);
        _argstack(res_stack, std::forward<Tail>(tail)...);
    }
    
    template<typename T, class... Args>
    void argstack(std::vector<T>& res_stack, Args... args){
        sstd::_argstack(res_stack, std::forward<Args>(args)...);
    }
}

namespace sstd{ class argparse; }

class sstd::argparse{
private:
//    std::vector<std::string> v_sw_cmd;
//    std::vector<std::string> ;
    std::vector<std::string> arg_stack;
    
public:
    argparse();
    ~argparse();

    template<class... Args>
    int parse(int argc, char* argv[], Args... args){
        sstd::argstack(arg_stack, args...);
        return 0;
    }

    const std::vector<std::string> _get_arg_stack(){ return arg_stack; }

//    template<typename T>
//    int add_switch_rule(const char* cmd, int cmd_num, T res_parsed_cmd, T default_val){
//        ;
//        return 0;
//    }
};


