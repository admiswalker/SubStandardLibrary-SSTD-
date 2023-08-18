#pragma once

#include "file.hpp"

#include "../definitions/typeDef.h"
#include "../memory/terp/terp.hpp"
#include "../memory/terp/print.hpp" // for debug

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
    bool yaml_load     (           sstd::terp::var & ret_yml,  const        char* s);
    bool yaml_load     (           sstd::terp::var & ret_yml,  const std::string& s);
    bool yaml_load_all(std::vector<sstd::terp::var>& ret_vYml, const        char* s);
    bool yaml_load_all(std::vector<sstd::terp::var>& ret_vYml, const std::string& s);
    
    bool yaml_load    (            sstd::terp::var & ret_yml,  sstd::file& fp);
    bool yaml_load_all(std::vector<sstd::terp::var>& ret_vYml, sstd::file& fp);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// dependent fn

namespace sstd{

    //std::string _join(const std::vector<std::string>& v, const std::string& delimiter);

    //---
    
    void _strip_ow(std::vector<std::string>& v);

    //---

    std::string _strip_dq_sq(const        char* str);
    std::string _strip_dq_sq(const std::string& str);
    std::string _strip_dq_sq(bool& ret_dq, bool& ret_sq, const        char* str);
    std::string _strip_dq_sq(bool& ret_dq, bool& ret_sq, const std::string& str);

    std::string _extract_dq_sq_value(const std::string& str);
    std::string _extract_dq_sq_value(const std::string& str);

    //---
    
    std::vector<std::string> _splitByLine_dq_sq(const        char* str);
    std::vector<std::string> _splitByLine_dq_sq(const std::string& str);

    //---
    
    bool _split_dq_sq(std::vector<std::string>& ret, const        char* str, const char X);
    bool _split_dq_sq(std::vector<std::string>& ret, const std::string& str, const char X);
//    std::vector<std::string> _split_dq_sq(const        char* str, const char X);
//    std::vector<std::string> _split_dq_sq(const std::string& str, const char X);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
