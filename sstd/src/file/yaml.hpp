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
    
    const static uint8 ope_null   = 255;
    const static uint8 ope_alloc  = 0; // allocate
    const static uint8 ope_stack  = 1; // stacking a value to v_dst
    const static uint8 ope_assign = 2; // assignemnt

    //---
    // type definition

    // TODO: num_ -> type_ に名前を置換する
    
    const static uint8 num_null             = 255;
    const static uint8 num_block_style_base = 0;
    const static uint8 num_str              = 0; // for BLOCK_STYLE
    const static uint8 num_list             = 1; // for BLOCK_STYLE
    const static uint8 num_hash             = 2; // for BLOCK_STYLE
    const static uint8 num_list_and_hash    = 3; // for BLOCK_STYLE
    const static uint8 num_flow_style_base  = 4;
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
        
        bool hasValue = false; // If the value (val1 or val2) is vaild for each data type (list or hash).
        bool key_is_dqed = false;
        bool key_is_sqed = false;
        bool val_is_dqed = false;
        bool val_is_sqed = false;
        bool mult_line_val = false;
        std::string key; // key for "hash"
        std::string val; // value for "list" or "hash"
    };
    struct command{
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

    bool _split_quotes_by_control_chars(std::vector<std::string>& ret, const char* str, const uint str_len);
    
    //---
    
    bool _format_mult_line_str(std::string& ret, const std::string& str, const uint hsc_base_yaml, const bool has_next_token);
    
    //---

    bool _str2token_except_multilines(std::vector<sstd_yaml::token>& ret, const std::string& str);
    bool _token2token_split_bv_list_type_cnt(std::vector<sstd_yaml::token>& io);
    bool _token2token_merge_multilines(std::vector<sstd_yaml::token>& io);
    bool _token2token_postprocess(std::vector<sstd_yaml::token>& io);
    bool _str2token(std::vector<sstd_yaml::token>& ret, const char* str);
    bool _str2token(std::vector<sstd_yaml::token>& ret, const std::string& str);
    
    bool _token2cmd(std::vector<struct sstd_yaml::command>& ret_vCmd, const std::vector<sstd_yaml::token>& v_token);
    bool _token2json(std::string& s_json, const std::vector<sstd_yaml::token>& v_token);
    
    //---
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
    void print(const sstd_yaml::token& rhs);
    void for_printn(const sstd_yaml::token& rhs);
    void print_for_vT(const sstd_yaml::token& rhs);
    
    void print(const sstd_yaml::command& rhs);
    void for_printn(const sstd_yaml::command& rhs);
    void print_for_vT(const sstd_yaml::command& rhs);
    
    bool yaml_load     (           sstd::terp::var & ret_yml,  const        char* s);
    bool yaml_load     (           sstd::terp::var & ret_yml,  const std::string& s);
    bool yaml_load_all(std::vector<sstd::terp::var>& ret_vYml, const        char* s);
    bool yaml_load_all(std::vector<sstd::terp::var>& ret_vYml, const std::string& s);
    
    bool yaml_load    (            sstd::terp::var & ret_yml,  sstd::file& fp);
    bool yaml_load_all(std::vector<sstd::terp::var>& ret_vYml, sstd::file& fp);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
