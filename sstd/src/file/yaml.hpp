#pragma once

#include "../definitions/typeDef.h"
#include "../memory/terp/terp.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
//    sstd::terp::var yaml(const        char* p_file_path);
//    sstd::terp::var yaml(const std::stirng&   file_path);
    
    sstd::terp::var yaml_from_str(const        char* s);
    sstd::terp::var yaml_from_str(const std::string& s);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
