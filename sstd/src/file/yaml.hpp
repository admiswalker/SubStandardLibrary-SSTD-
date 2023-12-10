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
// internal functions for unit test

namespace sstd_yaml{
    const static uchar num_null = 255;
    const static uchar num_block_style_base = 0;
    const static uchar num_str           = 0; // for BLOCK_STYLE
    const static uchar num_list          = 1; // for BLOCK_STYLE
    const static uchar num_hash          = 2; // for BLOCK_STYLE
    const static uchar num_list_and_hash = 3; // for BLOCK_STYLE
    const static uchar num_flow_style_base = 4;
    // sstd_yaml::num_flow_style_base + sstd_yaml::num_str           4 // reserved number for FLOW_STYLE
    // sstd_yaml::num_flow_style_base + sstd_yaml::num_list          5 // reserved number for FLOW_STYLE
    // sstd_yaml::num_flow_style_base + sstd_yaml::num_hash          6 // reserved number for FLOW_STYLE
    // sstd_yaml::num_flow_style_base + sstd_yaml::num_list_and_hash 7 // reserved number for FLOW_STYLE

    bool _splitByLine_quotes_brackets(std::vector<std::string>& ret, const        char* str);
    bool _splitByLine_quotes_brackets(std::vector<std::string>& ret, const std::string& str);
    
    bool _split_quotes_by_control_chars(std::vector<std::string>& ret, const char* str, const uint str_len);
    bool _data_type_and_format(uint& type, uint& format, uint& list_type_cnt, std::string s);

    //---

    // token for proceed YAML parsing
    struct token {
        // Data for Debug YAML parsing
        uint line_num_being; // beginning line number
        uint line_num_end;   // endding line number (for multipleline)
        std::string rawStr;
        
        // Data for load YAML
        std::string s;               // A string removed comments
        std::vector<std::string> vs; // A string removed comments and split by ' ' (space)
        uint type;                   // A destination type number of this line
        uint format;                 // If containing flow style notation
        uint list_type_cnt;          // Number of list type. (`- - - v`)
        uint hsc_hx;                 // head space counts for hash type
        uint hsc_lx;                 // head space counts for list type
    };

    bool _str2token(std::vector<sstd_yaml::token>& ret, const std::string& str);
    
    //---
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
