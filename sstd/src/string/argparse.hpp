#pragma once
#include <string>
#include <vector>
#include "../definitions/typeDef.h"
#include "../definitions/typeNum.hpp"
#include "../memory/void_ptr.hpp"
#include "../utils/argstack.hpp"

namespace sstd::arg_rule{
    const static int num_error                  = -1;
    const static int num_command_does_not_exist = -2;
    
    //---
    
    struct cmd_rule{
        int cmd_id                     = -1;
        int   return_val_type          = sstd::num_null;
        void* return_val_ptr           = NULL;
        sstd::void_ptr initial_val_ptr;
        std::string cmd;
//        int cmd_len                    = 0;
        int expected_num_of_args       = 0;
    };
    struct opt_rule{
        int   return_val_type          = sstd::num_null;
        void* return_val_ptr           = NULL;
        sstd::void_ptr initial_val_ptr;
        std::string opt_full;
        std::string opt_short;
//        int opt_len                    = 0;
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
}

namespace sstd{
    std::string to_string(const sstd::arg_rule::cmd_rule& rhs);
    std::string to_string(const sstd::arg_rule::opt_rule& rhs);
}

//---

namespace sstd{ class argparse; }

class sstd::argparse{
private:
    std::vector<struct sstd::arg_rule::cmd_rule> arg_vCmd;
    std::vector<struct sstd::arg_rule::opt_rule> arg_vOpt;
    std::string errMsg;
    
public:
    argparse();
    ~argparse();
    const std::string& err() const;
    

    int _parse(const int argc, const char* argv[]
               , const std::vector<struct sstd::arg_rule::cmd_rule>& arg_vCmd
               , const std::vector<struct sstd::arg_rule::opt_rule>& arg_vOpt);

    template<class... Args>
    int parse(const int argc, const char* argv[], Args... args){
        sstd::argstack(std::make_tuple(&arg_vCmd, &arg_vOpt), args...);
        return sstd::argparse::_parse(argc, argv, arg_vCmd, arg_vOpt);
    }

    const std::vector<struct sstd::arg_rule::cmd_rule>& _get_arg_vCmd(){ return arg_vCmd; }
    const std::vector<struct sstd::arg_rule::opt_rule>& _get_arg_vOpt(){ return arg_vOpt; }
};

