#pragma once

#include "../definitions/typeDef.h"
#include "../memory/terp/terp.hpp"
#include "../memory/terp/print.hpp" // for debug

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
//    sstd::terp::var yaml(const        char* p_file_path);
//    sstd::terp::var yaml(const std::stirng&   file_path);
    
    sstd::terp::var yaml_from_str(const        char* s);
    sstd::terp::var yaml_from_str(const std::string& s);

    /*
                sstd::terp::var  yaml_load    (sstd::file& fp); // sstd::file fp; fp.open("xxx");
    std::vector<sstd::terp::var> yaml_load_all(sstd::file& fp); // sstd::file fp; fp.open("xxx");

                sstd::terp::var  yaml_load    (const        char* s);
                sstd::terp::var  yaml_load    (const std::string& s);
    std::vector<sstd::terp::var> yaml_load_all(const        char* s);
    std::vector<sstd::terp::var> yaml_load_all(const std::string& s);

     */
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
