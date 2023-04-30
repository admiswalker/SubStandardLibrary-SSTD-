#pragma once

#include "../definitions/typeDef.h"
#include "../memory/terp/terp.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
//    class yaml;
    sstd::terp::var yaml_from_str(const        char* s);
    sstd::terp::var yaml_from_str(const std::string& s);

//    yaml str2yaml(std::string& s);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
/*
class sstd::yaml{
private:
    sstd::terp::var obj;
public:
    yaml();
//    yaml(const        char* p_file_path);
//    yaml(const std::stirng&   file_path);
    ~yaml();
    
    void init_from_str(const        char* s);
    void init_from_str(const std::string& s);
//    void str2yaml();
};
*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
