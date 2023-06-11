#pragma once

#include "file.hpp"

#include "../definitions/typeDef.h"
#include "../memory/terp/terp.hpp"
#include "../memory/terp/print.hpp" // for debug

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
    bool yaml_load    (            sstd::terp::var & ret_var, sstd::file& fp);
//    bool yaml_load_all(std::vector<sstd::terp::var>& ret_var, sstd::file& fp);

//                sstd::terp::var  yaml_load    (const        char* s);
//                sstd::terp::var  yaml_load    (const std::string& s);
    bool yaml_load     (           sstd::terp::var & ret_var,  const        char* s);
    bool yaml_load     (           sstd::terp::var & ret_var,  const std::string& s);
//    bool yaml_load_all(std::vector<sstd::terp::var>& ret_vVar, const        char* s);
//    bool yaml_load_all(std::vector<sstd::terp::var>& ret_vVar, const std::string& s);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// below fns will be delete

//    sstd::terp::var yaml(const        char* p_file_path);
//    sstd::terp::var yaml(const std::stirng&   file_path);
    
//    sstd::terp::var yaml_from_str(const        char* s);
//    sstd::terp::var yaml_from_str(const std::string& s);

//-----------------------------------------------------------------------------------------------------------------------------------------------
