#pragma once
#include <string>
#include <vector>
#include "../definitions/typeDef.h"
#include "../definitions/typeNum.hpp"
#include "../memory/void_ptr.hpp"

namespace sstd{
    template<typename T>
    void _args2stack(std::vector<T>& res_stack, T&& obj){
        res_stack.push_back(obj);
    }
    template<typename T, class Head, class... Tail>
    void _args2stack(std::vector<T>& res_stack, Head&& head, Tail&&... tail){
        sstd::_args2stack(res_stack, std::move(head));
        sstd::_args2stack(res_stack, std::forward<Tail>(tail)...);
    }
    
    template<typename T, class... Args>
    void args2stack(std::vector<T>& res_stack, Args... args){
        sstd::_args2stack(res_stack, std::forward<Args>(args)...);
    }

    //---

    template<class... ResArgs, class T>
    void _argstack(const std::tuple<ResArgs...>& res_tuple_pV, T&& obj){
        std::vector<T>* res_pTbl = std::get<std::vector<T>*>(res_tuple_pV);
        res_pTbl->push_back(obj);
    }
    template<class... ResArgs, class Head, class... Tail>
    void _argstack(const std::tuple<ResArgs...>& res_tuple_pV, Head&& head, Tail&&... tail){
        sstd::_argstack(res_tuple_pV, std::move(head));
        sstd::_argstack(res_tuple_pV, std::forward<Tail>(tail)...);
    }
    
    template<class... ResArgs, class... Args>
    void argstack(const std::tuple<ResArgs...>& res_tuple_pV, Args... args){
        sstd::_argstack(res_tuple_pV, std::forward<Args>(args)...);
    }
}

//---
/*
namespace sstd{
    template<typename K, typename V, typename T>
    bool _args2hash(std::unordered_map<K,V>& res_hashT,
                    K (*pFn_T2K)(const T& ),
                    V (*pFn_T2V)(      T&&),
                    T&& obj)
    {
        K key = pFn_T2K(obj);
        auto [itr, inserted] = res_hashT.insert({std::move(key), pFn_T2V(std::move(obj))});
        return inserted;
    }
    template<typename K, typename V, typename T, class Head, class... Tail>
    bool _args2hash(std::unordered_map<K,V>& res_hashT,
                    K (*pFn_T2K)(const T& ),
                    V (*pFn_T2V)(      T&&),
                    Head&& head, Tail&&... tail)
    {
        K key = pFn_T2K(head);
        bool inserted = sstd::_args2hash(res_hashT, pFn_T2K, pFn_T2V, std::move(head));
        if(!inserted){ return false; }
        return sstd::_args2hash(res_hashT, pFn_T2K, pFn_T2V, std::forward<Tail>(tail)...);
    }
    
    template<typename K, typename V, typename T, class... Args>
    bool args2hash(std::unordered_map<K,V>& res_hashT,
                   K (*pFn_T2K)(const T& ),
                   V (*pFn_T2V)(      T&&),
                   Args... args)
    {
        return sstd::_args2hash(res_hashT, pFn_T2K, pFn_T2V, std::forward<Args>(args)...);
    }
}
*/
//---
/*
namespace sstd{
    template<class... ResArgs, class... ArgsPFn, typename T>
    bool _args2hash(const std::tuple<ResArgs...>& res_tuple_pTbl,
                    const std::tuple<ArgsPFn...>& tuple_pFn,
                    T&& obj)
    {
        using DEF_pFn_insert = bool(*)(std::unordered_map<std::string,T>&,T&&); // 結局，テンプレートが関数引数の型で推論しているだけなので，ここの "std::string" を型推論できず，std::unordered_map<K,V> に対してこの汎用実装はできないことがわかった．(std::vector<T> 向けにはできるかも?)
        DEF_pFn_insert pFn_insert = std::get<DEF_pFn_insert>(tuple_pFn);
        
        std::unordered_map<std::string,T>* res_pTbl = std::get<std::unordered_map<std::string,T>*>(res_tuple_pTbl);
        return pFn_insert(*res_pTbl, std::move(obj));
    }
    template<class... ResArgs, class... ArgsPFn, class Head, class... Tail>
    bool _args2hash(const std::tuple<ResArgs...>& res_tuple_pTbl,
                    const std::tuple<ArgsPFn...>& tuple_pFn,
                    Head&& head, Tail&&... tail)
    {
        bool inserted = sstd::_args2hash(res_tuple_pTbl, tuple_pFn, std::move(head));
        if(!inserted){ return false; }
        return sstd::_args2hash(res_tuple_pTbl, tuple_pFn, std::forward<Tail>(tail)...);
    }
    
    template<class... ResArgs, class... ArgsPFn, class... Args>
    bool args2hash(const std::tuple<ResArgs...>& res_tuple_pTbl,
                   const std::tuple<ArgsPFn...>& tuple_pFn,
                   Args... args)
    {
        return sstd::_args2hash(res_tuple_pTbl, tuple_pFn, std::forward<Args>(args)...);
    }
}
*/
//---

namespace sstd::arg_rule{
    struct cmd_rule{
        int cmd_id                     = -1;
        int   return_val_type          = sstd::num_null;
        void* return_val_ptr           = NULL;
        sstd::void_ptr initial_val_ptr;
        std::string cmd;
        int cmd_len                    = 0;
        int expected_num_of_args       = 0;
    };
    struct opt_rule{
        int   return_val_type          = sstd::num_null;
        void* return_val_ptr           = NULL;
        sstd::void_ptr initial_val_ptr;
        std::string opt_short;
        std::string opt_full;
        int opt_len                    = 0;
        int expected_num_of_args       = 0;
    };
    
    //---
    
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
    
    template<typename T>
    struct sstd::arg_rule::opt_rule opt(T& return_val, const T& initial_val, const char* opt_short, const char* opt_full, const int expected_num_of_args){
        
        struct opt_rule res;
        res.return_val_type      = sstd::type2num(return_val);
        res.return_val_ptr       =               &return_val ;
        res.initial_val_ptr      = sstd::void_ptr(new T(initial_val));
        res.opt_short            = std::string(opt_short);
        res.opt_full             = std::string(opt_full );
        res.expected_num_of_args = expected_num_of_args;
        
        return res;
    }

    //---
}
namespace sstd::_argparse{
    bool fn_insert_cmd(std::unordered_map<std::string,struct sstd::arg_rule::cmd_rule>& res_hashT, struct sstd::arg_rule::cmd_rule&& cmd_rule);
    bool fn_insert_opt(std::unordered_map<std::string,struct sstd::arg_rule::opt_rule>& res_hashT, struct sstd::arg_rule::opt_rule&& opt_rule);
//    std::string fn_T2K(const struct sstd::arg_rule::cmd_rule&);
//    struct sstd::arg_rule::cmd_rule fn_T2V(struct sstd::arg_rule::cmd_rule&&);
}

namespace sstd{
    void print_base(const sstd::arg_rule::cmd_rule& rhs);
    void print_base(const sstd::arg_rule::opt_rule& rhs);
}

//---

namespace sstd{ class argparse; }

class sstd::argparse{
private:
//    std::vector<std::string> v_sw_cmd;
//    std::vector<std::string> ;
    std::vector<struct sstd::arg_rule::cmd_rule> arg_stack;
//    std::unordered_map<std::string,struct sstd::arg_rule::cmd_rule> arg_hash_cmd;
//    std::unordered_map<std::string,struct sstd::arg_rule::opt_rule> arg_hash_opt;
    std::vector<struct sstd::arg_rule::cmd_rule> arg_vCmd;
    std::vector<struct sstd::arg_rule::opt_rule> arg_vOpt;
    std::string err;
    
public:
    argparse();
    ~argparse();

    int _parse(const int argc, const char* argv[], const std::vector<struct sstd::arg_rule::cmd_rule>& arg_stack);

    template<class... Args>
    int parse(const int argc, const char* argv[], Args... args){
        sstd::argstack(std::make_tuple(&arg_vCmd, &arg_vOpt), args...);
//        bool res = sstd::args2hash(std::make_tuple(&arg_hash_cmd, &arg_hash_opt),
//                                   std::make_tuple(sstd::_argparse::fn_insert_cmd, sstd::_argparse::fn_insert_opt),
//                                   args...);
//        bool res = sstd::args2hash(arg_hash, sstd::_argparse::fn_T2K, sstd::_argparse::fn_T2V, args...);
//        if(!res){ this->err="sstd::argparse::_parse() failed. User input command defined by `sstd::arg_rule::cmd()` did NOT found."; return -1; }
        return sstd::argparse::_parse(argc, argv, arg_stack);
    }

    const std::vector<struct sstd::arg_rule::cmd_rule>& _get_arg_stack(){ return arg_stack; }
//    const std::unordered_map<std::string,struct sstd::arg_rule::cmd_rule>& _get_arg_hash_cmd(){ return arg_hash_cmd; }
//    const std::unordered_map<std::string,struct sstd::arg_rule::opt_rule>& _get_arg_hash_opt(){ return arg_hash_opt; }
    const std::vector<struct sstd::arg_rule::cmd_rule>& _get_arg_vCmd(){ return arg_vCmd; }
    const std::vector<struct sstd::arg_rule::opt_rule>& _get_arg_vOpt(){ return arg_vOpt; }

//    template<typename T>
//    int add_switch_rule(const char* cmd, int cmd_num, T res_parsed_cmd, T default_val){
//        ;
//        return 0;
//    }
};


