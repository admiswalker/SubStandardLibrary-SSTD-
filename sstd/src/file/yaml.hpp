#pragma once

#include "file.hpp"

#include "../definitions/typeDef.h"
#include "../memory/terp/terp.hpp"
#include "../memory/terp/print.hpp" // for debug

//-----------------------------------------------------------------------------------------------------------------------------------------------
// internal functions for unit test

namespace sstd_yaml{

    //---
    // operation definition
    
    const static uchar ope_null   = 255;
    const static uchar ope_alloc  = 0; // allocate
    const static uchar ope_assign = 0; // assignemnt

    //---
    // type definition

    // TODO: num_ -> type_ に名前を置換する
    
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

    //---
    // token for proceed YAML parsing
    
    struct token {
        // Data for Debug YAML parsing
        uint line_num_begin = 1;                       // beginning line number
        uint line_num_end   = 1;                       // endding line number (for multipleline)
        std::string rawStr;                            // A raw string splitted by line concering the YAML processing units.
        
        // Data structure to load YAML
        //uint type = sstd_yaml::num_null; // sstd_yaml::num_str;                // A destination type number of this line
        uint type = sstd_yaml::num_str;                // A destination type number of this line
        uint format = sstd_yaml::num_block_style_base; // If containing flow style notation
        uint list_type_cnt = 0;                        // Number of list type. (`- - - v`)
        uint hsc_lx = 0;                               // head space counts for list type
        uint hsc_hx = 0;                               // head space counts for hash type
        
        bool val1_use_quotes;
        bool val2_use_quotes;
        std::string val1;
        std::string val2;
    };
    struct command{
        uint hsc_lx; // hsc: head space count, _lx: list-index.
        uint hsc_hx; // hsc: head space count, _hx: hash-index.
        uint8 type;
        uint8 format;
        bool val1_use_quotes;
        bool val2_use_quotes;
        std::string val1; // "list value" or "hash key"
        std::string val2; // "hash value" if Not required "sstd::terp::var"

        // debug info
        uint lineNum;
        std::string rawStr;
    };
    struct command_v2{
        // Data for Debug YAML parsing
        uint line_num_begin = 1;                       // beginning line number
        uint line_num_end   = 1;                       // endding line number (for multipleline)
        std::string rawStr;                            // A raw string splitted by line concering the YAML processing units.

        // Data structure to construct YAML
        uint ope; // operation
        uint hsc; // hsc: head space count
        uint8 type; // data type
        uint8 format; // data format
        std::string val; // value
    };

    //---

    bool _splitByLine_quotes_brackets(std::vector<std::string>& ret, const        char* str);
    bool _splitByLine_quotes_brackets(std::vector<std::string>& ret, const std::string& str);
    
    bool _split_quotes_by_control_chars(std::vector<std::string>& ret, const char* str, const uint str_len);
    bool _data_type_and_format(uint& type, uint& format, uint& list_type_cnt, std::string s);
    
    //---
    
    bool _str2token(std::vector<sstd_yaml::token>& ret, const char* str);
    bool _str2token(std::vector<sstd_yaml::token>& ret, const std::string& str);
    bool _token2cmd(std::vector<struct sstd_yaml::command_v2>& ret_vCmd, const std::vector<sstd_yaml::token>& v_token);
    bool _token2json(std::string& s_json, const std::vector<sstd_yaml::token>& v_token);
    
    //---
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
    void print(const sstd_yaml::token& rhs);
    void for_printn(const sstd_yaml::token& rhs);
    void print_for_vT(const sstd_yaml::token& rhs);
    
    void print(const sstd_yaml::command_v2& rhs);
    void for_printn(const sstd_yaml::command_v2& rhs);
    void print_for_vT(const sstd_yaml::command_v2& rhs);
    
    bool yaml_load     (           sstd::terp::var & ret_yml,  const        char* s);
    bool yaml_load     (           sstd::terp::var & ret_yml,  const std::string& s);
    bool yaml_load_all(std::vector<sstd::terp::var>& ret_vYml, const        char* s);
    bool yaml_load_all(std::vector<sstd::terp::var>& ret_vYml, const std::string& s);
    
    bool yaml_load    (            sstd::terp::var & ret_yml,  sstd::file& fp);
    bool yaml_load_all(std::vector<sstd::terp::var>& ret_vYml, sstd::file& fp);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
