#pragma once
#include <string>
#include <vector>
#include "../definitions/typeDef.h"
#include "../definitions/typeNum.hpp"
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

namespace sstd{
//    template<typename K, typename V, typename T>
    template<typename K, typename T>
    bool _arghash(std::unordered_map<K,T>& res_hashT,
                  K (*pFn_T2K)(const T&),
//                  V&& (*pFn_T2V)(T&&),
                  T&& obj)
    {
//        auto [itr, inserted] = res_hashT.insert({pFn_T2K(obj), pFn_T2V(obj)});
        auto [itr, inserted] = res_hashT.insert({pFn_T2K(obj), obj});
        return inserted;
    }
//    template<typename K, typename V, typename T, class Head, class... Tail>
    template<typename K, typename T, class Head, class... Tail>
    bool _arghash(std::unordered_map<K,T>& res_hashT,
                  K (*pFn_T2K)(const T&),
//                  V&& (*pFn_T2V)(T&&),
                  Head&& head, Tail&&... tail)
    {
        auto [itr, inserted] = res_hashT.insert({pFn_T2K(head), head});
//        auto [itr, inserted] = res_hashT.insert({pFn_T2K(head), pFn_T2V(head)});
        if(!inserted){ return false; }
        return sstd::_arghash(res_hashT, pFn_T2K, std::forward<Tail>(tail)...);
    }
    
//    template<typename K, typename V, typename T, class... Args>
    template<typename K, typename T, class... Args>
    bool arghash(std::unordered_map<K,T>& res_hashT,
                 K (*pFn_T2K)(const T&),
//                 V&& (*pFn_T2V)(T&&),
                 Args... args)
    {
        return sstd::_arghash(res_hashT, pFn_T2K, std::forward<Args>(args)...);
    }
}

//---

namespace sstd::arg_rule{
    struct cmd_rule{
        int cmd_id                     = -1;
        int   return_val_type          = sstd::num_null;
        void* return_val_ptr           = NULL;
        sstd::void_ptr initial_val_ptr;
        std::string cmd;
        int expected_num_of_args       = 0;
    };
//    struct opt_rule{
//    }
    
    struct sstd::arg_rule::cmd_rule cmd(const char* ps); // temporal implementation (delete this line later)
    struct sstd::arg_rule::cmd_rule cmd(const int cmd_id,                                      const char* cmd, const int expected_num_of_args);
    
    template<typename T>
    struct sstd::arg_rule::cmd_rule cmd(const int cmd_id, T& return_val, const T& initial_val, const char* cmd, const int expected_num_of_args){
        
        struct cmd_rule res;
        res.cmd_id               = cmd_id;
        res.return_val_type      = sstd::type2num(return_val);
        res.return_val_ptr       =               &return_val ;
        res.initial_val_ptr      = sstd::void_ptr(new T(initial_val));
        res.cmd                  = std::string(cmd);
        res.expected_num_of_args = expected_num_of_args;
        
        return res;
    }
    
    //---
    
    std::string fn_T2K(const struct sstd::arg_rule::cmd_rule&);
    struct sstd::arg_rule::cmd_rule&& fn_T2V(struct sstd::arg_rule::cmd_rule&&);
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
    std::unordered_map<std::string,struct sstd::arg_rule::cmd_rule> arg_hash;
    std::string err;
    
public:
    argparse();
    ~argparse();

    int _parse(const int argc, const char* argv[], const std::vector<struct sstd::arg_rule::cmd_rule>& arg_stack);

    template<class... Args>
    int parse(const int argc, const char* argv[], Args... args){
        sstd::arghash(arg_hash, sstd::arg_rule::fn_T2K, args...);
        //sstd::arghash(arg_hashT, sstd::arg_rule::fn_T2K, sstd::arg_rule::fn_T2V, args...);
        //sstd::argstack(arg_stack, args...);
        return sstd::argparse::_parse(argc, argv, arg_stack);
    }

    const std::vector<struct sstd::arg_rule::cmd_rule>& _get_arg_stack(){ return arg_stack; }
    const std::unordered_map<std::string,struct sstd::arg_rule::cmd_rule>& _get_arg_hash(){ return arg_hash; }

//    template<typename T>
//    int add_switch_rule(const char* cmd, int cmd_num, T res_parsed_cmd, T default_val){
//        ;
//        return 0;
//    }
};


