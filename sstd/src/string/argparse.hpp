#pragma once
//#include <stdio.h>
#include "../definitions/typeDef.h"

namespace sstd{ class argparse; }

class sstd::argparse{
private:
    std::vector<std::string> v_sw_cmd;
    std::vector<std::string> ;
    
public:
    argparse();
    ~argparse();

    template<typename T>
    int add_switch_rule(const char* cmd, int cmd_num, T res_parsed_cmd, T default_val){
        ;
        return 0;
    }
};

