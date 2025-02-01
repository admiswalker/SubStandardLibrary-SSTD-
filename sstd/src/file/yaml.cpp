#include <string.h>

#include <cassert>
#include <regex>
#include <string>
#include <vector>

#include "yaml.hpp"

#include "../container/vector/vec_manipulation.hpp"
#include "../definitions/typeDef.h"
#include "../string/strEdit.hpp"
#include "../string/strmatch.hpp"
#include "../print/print.hpp" // for debug


//-----------------------------------------------------------------------------------------------------------------------------------------------
// Abbreviations
//
// - dq: double quotation
// - sq: single quatation

//-----------------------------------------------------------------------------------------------------------------------------------------------
// print

#define sstd_print_token_base(rhs)                                      \
    printf("\n");                                                       \
    printf("debug info:\n");                                            \
    printf("    line_num_begin: %d\n", rhs.line_num_begin);             \
    printf("    line_num_end: %d\n", rhs.line_num_end);                 \
    printf("    rawStr: `%s`\n", rhs.rawStr.c_str());                   \
    printf("command:\n");                                               \
    printf("    type: %d\n", rhs.type);                                 \
    printf("    format: %d\n", rhs.format);                             \
    printf("    ref_type: %d\n", rhs.ref_type);                         \
    printf("    list_type_cnt: %d\n", rhs.list_type_cnt);               \
    printf("    hsc_lx: %d\n", rhs.hsc_lx);                             \
    printf("    hsc_hx: %d\n", rhs.hsc_hx);                             \
    printf("    hasValue: %s\n", (rhs.hasValue?"ture":"false"));        \
    printf("    key_is_dqed: %s\n", (rhs.key_is_dqed?"ture":"false"));  \
    printf("    key_is_sqed: %s\n", (rhs.key_is_sqed?"ture":"false"));  \
    printf("    val_is_dqed: %s\n", (rhs.val_is_dqed?"ture":"false"));  \
    printf("    val_is_sqed: %s\n", (rhs.val_is_sqed?"ture":"false"));  \
    printf("    mult_line_val: %s\n", (rhs.mult_line_val?"ture":"false")); \
    printf("    key: `%s`\n", rhs.key.c_str());                         \
    printf("    val: `%s`\n", rhs.val.c_str());                         \
    printf("anchor and alias:\n");                              \
    printf("    ref_type: %d\n", rhs.ref_type);                 \
    printf("    aa_val: `%s`\n", rhs.aa_val.c_str());           \
    printf(",\n");

void sstd::print_base(const sstd_yaml::token& rhs){
    sstd_print_token_base(rhs);
}

#undef sstd_print_token_base

//---

#define sstd_print_command_v2_base(rhs)                         \
    printf("\n");                                               \
    printf("debug info:\n");                                    \
    printf("    line_num_begin: %d\n", rhs.line_num_begin);     \
    printf("    line_num_end: %d\n", rhs.line_num_end);         \
    printf("    rawStr: `%s`\n", rhs.rawStr.c_str());           \
    printf("command:\n");                                       \
    printf("    ope: %d\n", rhs.ope);                           \
    printf("    hsc: %d\n", rhs.hsc);                           \
    printf("    type: %d\n", rhs.type);                         \
    printf("    format: %d\n", rhs.format);                     \
    printf("    val: `%s`\n", rhs.val.c_str());                 \
    printf("anchor and alias:\n");                              \
    printf("    ref_type: %d\n", rhs.ref_type);                 \
    printf("    aa_val: `%s`\n", rhs.aa_val.c_str());           \
    printf(",\n");

void sstd::print_base(const sstd_yaml::command& rhs){
    sstd_print_command_v2_base(rhs);
    printf("\n");
}

#undef sstd_print_command_v2_base

//-----------------------------------------------------------------------------------------------------------------------------------------------

std::string _extract_quotes_value(const std::string& str){
    std::string tmp;
    std::string ret;

    // Space conversion
    //   - example 1: "a b c " -> "a b c "
    //   - example 2: "a  \n  b  \n  c  " -> "a\nb\nc  "
    for(uint i=0; i<str.size(); ++i){
        if(str[i]=='\n'){
            sstd::rstrip_ow(tmp);
            tmp += str[i];
            ++i; while(i<str.size() && str[i]==' '){ ++i; } --i;
        }else{
            tmp += str[i];
        }
    }
    
    // conversion
    //   - example 1: "a\nb\nc  " -> "a b c  "
    bool escape = false;
    uint new_line_cnt=0;
    for(uint i=0; i<tmp.size(); ++i){
        if(tmp[i]=='\\'){
            escape=true;
            continue;
        }
//        if(escape){ // when using a escaped notation rule
//            switch(tmp[i]){
//            case '"': { ret += '\\'; } break;
//            default: break;
//            }
//        }
        
        if(tmp[i]=='\n'){ ++new_line_cnt; continue; }
        
        if(new_line_cnt==1){
            if(!escape){
                ret += " ";
            }
        }else if(new_line_cnt>=2){
//            for(uint i_t=0; i_t<new_line_cnt; ++i_t){ ret += "\\n"; } // when using a escaped notation rule
            for(uint i_t=0; i_t<new_line_cnt; ++i_t){ ret += '\n'; }
        }
        
        ret += tmp[i];
        
        new_line_cnt=0;
        escape = false;
    }
    
    return ret;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

std::string _rm_comment(const std::string& s){
    std::vector<std::string> v = sstd::split(s, '#');
    if(v.size()==0){ return std::string(); }
    return sstd::rstrip(v[0]);
}

//---

std::string _join_mult_line(const std::vector<std::string>& v, const bool ret_pipeSymbol, const bool ret_greaterThanSymbol){
    std::string ret;
    if(v.size()==0){ return ret; }
    
    std::vector<std::string> v_delimiter;
    if(ret_pipeSymbol){
        // '|'
        v_delimiter = std::vector<std::string>(v.size()-1, std::string("\n"));
        
    }else if(ret_greaterThanSymbol){
        // '>'
        v_delimiter = std::vector<std::string>(v.size()-1, std::string(" "));
        
        uint i = 0;
        uint hsc = sstd::lcount(v[i], ' '); // hsc: head space count
        if(hsc!=0){ v_delimiter[i] = "\n"; }
        ++i;
        for(; i<v.size()-1; ++i){
            hsc = sstd::lcount(v[i], ' '); // hsc: head space count
            if(hsc!=0){
                v_delimiter[i-1] = "\n";
                v_delimiter[i  ] = "\n";
            }
        }
    }else{
        sstd::pdbg_err("The multiple line needs to denoted by '|' or '>'.\n");
    }
    
    // join
    ret += v[0];
    for(uint i=1; i<v.size(); ++i){
        ret += v_delimiter[i-1] + v[i];
    }

    return ret;
}

//---

bool _parse_mult_line_opt(bool& ret_noSymbol, bool& ret_pipeSymbol, bool& ret_greaterThanSymbol, bool& ret_plusSymbol, bool& ret_minusSymbol, bool& ret_hasHsc, uint& ret_hsc, const std::string& opt_in){
    // input examples:
    //     "|+123", "|-123", "|123+", "|123-",
    //     ">+123", ">-123", ">123+", ">123-".

    std::string opt = sstd::lstrip(opt_in);

    ret_noSymbol=false;
    ret_pipeSymbol=false;
    ret_greaterThanSymbol=false;
    ret_plusSymbol=false;
    ret_minusSymbol=false;
    ret_hasHsc=false;
    ret_hsc=0;

    if(opt.size()==0 || (opt.size()>=1 && (opt[0]!='|' && opt[0]!='>'))){
        ret_noSymbol=true;
    }else{
        for(uint i=0; i<opt.size(); ++i){
            if(opt[i]=='|'){ if(ret_pipeSymbol       ){sstd::pdbg_err("Duplicated '|'.\n");return false;} ret_pipeSymbol       =true; continue; }
            if(opt[i]=='>'){ if(ret_greaterThanSymbol){sstd::pdbg_err("Duplicated '>'.\n");return false;} ret_greaterThanSymbol=true; continue; }
            if(opt[i]=='+'){ if(ret_plusSymbol       ){sstd::pdbg_err("Duplicated '+'.\n");return false;} ret_plusSymbol       =true; continue; }
            if(opt[i]=='-'){ if(ret_minusSymbol      ){sstd::pdbg_err("Duplicated '-'.\n");return false;} ret_minusSymbol      =true; continue; }
        }
        std::string sNum = sstd::stripAll(opt, "|>+-");
        if(sNum.size()==0){ return true; }
        if(!sstd::isNum(sNum)){ sstd::pdbg_err("Not numer.\n"); return false; }
        ret_hasHsc=true;
        ret_hsc = std::stoul(sNum);
    }
    
    return true;
}

//---

bool sstd_yaml::_format_mult_line_str(std::string& ret_str, const std::string& str, const uint hsc_base_yaml, const bool has_next_token){
    std::string ret;
    
    std::vector<std::string> v_str = sstd::splitByLine(str+"\n"); // "\n" modify the num of split sections
    std::vector<std::string> v_tmp;
    if(v_str.size()<2){ return true; }
    
    bool ret_noSymbol=false, ret_pipeSymbol=false, ret_greaterThanSymbol=false;
    bool ret_plusSymbol=false, ret_minusSymbol=false;
    bool ret_hasHsc=false; uint ret_user_requested_hsc=0;
    std::string opt=v_str[0];
    if(!_parse_mult_line_opt(ret_noSymbol, ret_pipeSymbol, ret_greaterThanSymbol, ret_plusSymbol, ret_minusSymbol, ret_hasHsc, ret_user_requested_hsc, opt)){ sstd::pdbg_err("_parse_mult_line_opt() is failed.\n"); return false; }

    if(ret_noSymbol){
        // noSymbol

        // parse multi-line string to YAML style string
        std::string tmp;
        bool prev_is_line_break=true;
        for(uint i=0; i<v_str.size(); ++i){
            tmp = sstd::strip(v_str[i]);
            if(tmp.starts_with("#")){ continue; }
            if(ret.size()==0 && tmp.size()==0){ continue; }
            
            if(tmp.size()==0){
                ret += '\n';
                prev_is_line_break=true;
            }else if(prev_is_line_break){
                ret += tmp;
                prev_is_line_break=false;
            }else{
                if(ret.ends_with('\\')){ // For the line break with escape. Example: `- "a\\n   b"` -> `["ab"]`.
                    ret.pop_back();
                    ret += tmp;
                    prev_is_line_break=false;
                }else{
                    ret += ' ' + tmp;
                    prev_is_line_break=false;
                }
            }
        }
        sstd::rstripAll_ow(ret, " \n");
        
    }else{
        // "|+N", "|-N", ">+N" or ">-N"
        
        const uint hsc_base_1st_line=sstd::lcount(v_str[1], ' '); // hsc: head space count
        if(hsc_base_1st_line<=hsc_base_yaml){
            // Error case.
            // - |
            // a  <- error (Required more than 1 hsc)
            sstd::pdbg_err("The space count of multiple line indent is invalid.\n");
            return false;
        }

        uint hsc_base=hsc_base_1st_line;
        if(ret_hasHsc){
            if(ret_user_requested_hsc==0){ sstd::pdbg_err("The user requested indent can not be 0.\n"); return false; }
            if(ret_user_requested_hsc>hsc_base_1st_line){
                // Error case.
                // - |9
                //   a  <- error (Required more than 10 hsc)
                sstd::pdbg_err("The user requested indent size is too large.\n");
                return false;
            }
            hsc_base=hsc_base_yaml+ret_user_requested_hsc;
        }
        
        for(uint i=1; i<v_str.size(); ++i){
            std::string s=v_str[i];
            std::string tmp;
            uint hsc = sstd::lcount(s, ' '); // hsc: head space count
            bool have_str_except_space = (hsc!=s.size());

            if(have_str_except_space && hsc<hsc_base){
                // Error case.
                // - |
                //   a
                // b    <- error (Required more than 2 hsc)
                //   c
                sstd::pdbg_err("The space count of multiple line indent is invalid.\n");
                return false;
            }
        
            if(s.size()>=hsc_base){
                tmp += (char*)&v_str[i][hsc_base];
            }

            v_tmp.push_back(tmp);
        }
        
        if((!ret_plusSymbol) && (!ret_minusSymbol)){
            // "|N" or ">N"
        
            int cnt = (int)sstd::cntEmpty_r(v_tmp);
            sstd::rmEmpty_r_ow(v_tmp);
            ret = _join_mult_line(v_tmp, ret_pipeSymbol, ret_greaterThanSymbol) + std::string(std::min(1,cnt), '\n');
            
        }else if(ret_minusSymbol){
            // "|-N" or ">-N"
        
            sstd::rmEmpty_r_ow(v_tmp);
            ret = _join_mult_line(v_tmp, ret_pipeSymbol, ret_greaterThanSymbol);
        
        }else if(ret_plusSymbol){
            // "|+N" or ">+N"
        
            int cnt = (int)sstd::cntEmpty_r(v_tmp) + (int)(has_next_token?1:0);
            sstd::rmEmpty_r_ow(v_tmp);
            ret = _join_mult_line(v_tmp, ret_pipeSymbol, ret_greaterThanSymbol) + std::string(cnt, '\n');
        
        }else{
            sstd::pdbg_err("Unexpected case\n"); return false;
        }
    }

    std::swap(ret_str, ret);
    return true;
}

bool sstd_yaml::_token2cmd(std::vector<struct sstd_yaml::command>& ret_vCmd, const std::vector<sstd_yaml::token>& v_token){
    
    for(uint i=0; i<v_token.size(); ++i){
        const sstd_yaml::token& t = v_token[i];
        
        // Construct alloc() or assign() command
        struct sstd_yaml::command c;
        switch(t.type){
        case sstd_yaml::type_str: {
            // --- debug info ---
            c.line_num_begin  = t.line_num_begin;
            c.line_num_end    = t.line_num_end;
            c.rawStr          = t.rawStr;
            // --- construct info ---
            c.ope             = sstd_yaml::ope_assign;
            c.hsc             = t.hsc_hx; // t.hsc_lx
            c.type            = sstd_yaml::type_str;
            c.format          = t.format;
            c.val             = t.val; // t.key;
            ret_vCmd.push_back(c);
        } break;
        case sstd_yaml::type_list: {
            {
                // --- debug info ---
                c.line_num_begin  = t.line_num_begin;
                c.line_num_end    = t.line_num_end;
                c.rawStr          = t.rawStr;
                // --- construct info ---
                c.ope             = sstd_yaml::ope_alloc;
                c.hsc             = t.hsc_lx; // t.hsc_hx
                c.type            = sstd_yaml::type_list;
                //c.format          = t.format;
                //c.val             = t.val; // t.key;
                // --- anchor and alias ---
                if(t.ref_type==sstd_yaml::ref_type_anchor){
                    c.ref_type    = t.ref_type;
                    c.aa_val      = t.aa_val;
                }else if(t.ref_type==sstd_yaml::ref_type_alias){
                    c.ref_type    = t.ref_type;
                    c.aa_val      = t.aa_val;
                }
                ret_vCmd.push_back(c);
            }

            if(t.hasValue){ // check the value is NOT NULL
                // --- debug info ---
                c.line_num_begin  = t.line_num_begin;
                c.line_num_end    = t.line_num_end;
                c.rawStr          = t.rawStr;
                // --- construct info ---
                c.ope             = sstd_yaml::ope_assign;
                c.hsc             = t.hsc_hx; // t.hsc_lx;
                c.type            = sstd_yaml::type_str;
                c.format          = t.format;
                c.val             = t.val; // t.key;
                ret_vCmd.push_back(c);
            }
        } break;
        case sstd_yaml::type_hash: {
            // --- debug info ---
            c.line_num_begin  = t.line_num_begin;
            c.line_num_end    = t.line_num_end;
            c.rawStr          = t.rawStr;
            // --- construct info ---
            c.ope             = sstd_yaml::ope_alloc;
            c.hsc             = t.hsc_hx; // t.hsc_lx
            c.type            = sstd_yaml::type_hash;
            //c.format          = t.format;
            c.val             = t.key; // t.val; // key
            ret_vCmd.push_back(c);
            
            if(t.hasValue){ // check the value is NOT NULL
                // --- debug info ---
                c.line_num_begin  = t.line_num_begin;
                c.line_num_end    = t.line_num_end;
                c.rawStr          = t.rawStr;
                // --- construct info ---
                c.ope             = sstd_yaml::ope_assign;
                c.hsc             = t.hsc_hx + 2; // t.hsc_lx;
                c.type            = sstd_yaml::type_str;
                c.format          = t.format;
                c.val             = t.val; // t.key; // value
                ret_vCmd.push_back(c);
            }
        } break;
        case sstd_yaml::type_list_and_hash:{
            {
                // --- debug info ---
                c.line_num_begin  = t.line_num_begin;
                c.line_num_end    = t.line_num_end;
                c.rawStr          = t.rawStr;
                // --- construct info ---
                c.ope             = sstd_yaml::ope_alloc;
                c.hsc             = t.hsc_lx; // t.hsc_hx + 2*ti
                c.type            = sstd_yaml::type_list;
                //c.format          = t.format;
                //c.val             = t.val; // t.key;
                ret_vCmd.push_back(c);
            }

            {
                // construction of stack() command
                
                // --- debug info ---
                c.line_num_begin  = t.line_num_begin;
                c.line_num_end    = t.line_num_end;
                c.rawStr          = t.rawStr;
                // --- construct info ---
                c.ope             = sstd_yaml::ope_stack;
                c.hsc             = t.hsc_hx; // hsc_lx
                
                ret_vCmd.push_back(c);
            }
            
            // --- debug info ---
            c.line_num_begin  = t.line_num_begin;
            c.line_num_end    = t.line_num_end;
            c.rawStr          = t.rawStr;
            // --- construct info ---
            c.ope             = sstd_yaml::ope_alloc;
            c.hsc             = t.hsc_hx; // hsc_lx
            c.type            = sstd_yaml::type_hash;
            //c.format          = t.format;
            c.val             = t.key; // t.val; // key
            ret_vCmd.push_back(c);
            
            if(t.hasValue){ // check the value is NOT NULL
                // --- debug info ---
                c.line_num_begin  = t.line_num_begin;
                c.line_num_end    = t.line_num_end;
                c.rawStr          = t.rawStr;
                // --- construct info ---
                c.ope             = sstd_yaml::ope_assign;
                c.hsc             = t.hsc_hx + 2; // t.hsc_lx;
                c.type            = sstd_yaml::type_str;
                c.format          = t.format;
                c.val             = t.val; // t.key; // value
                ret_vCmd.push_back(c);
            }
        } break;
        default: { sstd::pdbg_err("Unexpected data type\n"); return false; } break;
        };

        
        // construction of stack() command
        if( !t.hasValue && (t.type==sstd_yaml::type_list || t.type==sstd_yaml::type_hash || t.type==sstd_yaml::type_list_and_hash )){
            uint hsc_curr = c.hsc;
            uint hsc_next = 0;

            // Checking the Next if is Not end of the v_token. (Checking the v_token[i+1] is NOT Null).
            if( !(i+1<v_token.size()) ){
                // Case of "i" is the last token
                
                // If sstd_yaml::_token2cmd() did NOT append the pop() command,
                // anaway all the cmd2yaml() process is already finished.
                continue;
            }
            const sstd_yaml::token& t_nx = v_token[i+1]; // _nx: next
            
            switch(t_nx.type){
          //case sstd_yaml::type_str:           { hsc_next = t_nx.hsc_hx;                            } break;
            case sstd_yaml::type_str:           { continue; } break;
            case sstd_yaml::type_list:          { hsc_next = t_nx.hsc_lx + 2*(t_nx.list_type_cnt-1); } break;
            case sstd_yaml::type_hash:          { hsc_next = t_nx.hsc_hx;                            } break;
            case sstd_yaml::type_list_and_hash: { hsc_next = t_nx.hsc_lx + 2*(t_nx.list_type_cnt-1); } break; // works as a list
            default: { sstd::pdbg_err("Unexpected data type\n"); return false; } break;
            };

            // Table. stack() conditions
            //
            // ┌───┬───────────────────┬───────────────────────────────────────────────────────────┐
            // │   │                   │ hsc_current                                               │
            // ├───┼───────────────────┼───────────────────┬───────────────────┬───────────────────┤
            // │   │                   │                   │                   │ list_and_hash     │
            // │   │                   │ list              │ hash              │ (works as a hash) │
            // ├───┼───────────────────┼───────────────────┼───────────────────┼───────────────────┤
            // │ h │ list              │ >                 │ >=                │ >=                │
            // │ s │                   │                   │                   │                   │
            // │ c ├───────────────────┼───────────────────┼───────────────────┼───────────────────┤
            // │ _ │ list_and_hash     │ >                 │ >=                │ >=                │
            // │ n │ (works as a list) │                   │                   │                   │
            // │ e ├───────────────────┼───────────────────┼───────────────────┼───────────────────┤
            // │ x │ hash              │ >                 │ >                 │ >                 │
            // │ t │                   │                   │                   │                   │
            // └───┴───────────────────┴───────────────────┴───────────────────┴───────────────────┘
            //
            bool isGr     = t.type==sstd_yaml::type_list || t_nx.type==sstd_yaml::type_hash; // check '>'  case
            bool isGrOrEq = !isGr;                                                           // check '>=' case
            if((isGr     && hsc_next> hsc_curr) ||
               (isGrOrEq && hsc_next>=hsc_curr)    )
            {
                // --- debug info ---
                c.line_num_begin  = t.line_num_begin;
                c.line_num_end    = t.line_num_end;
                c.rawStr          = t.rawStr;
                // --- construct info ---
                c.ope             = sstd_yaml::ope_stack;
                c.hsc             = hsc_next;
                
                ret_vCmd.push_back(c);
            }
        }
    }
    
    return true;
}

bool _is_control_chars(const char c){
    return (c=='[' || c==']' || c=='{' || c=='}' || c==':' || c==',');
}
bool sstd_yaml::_split_quotes_by_control_chars(std::vector<std::string>& ret, const char* str, const uint str_len){
    bool is_escaped=false;
    bool in_d_quate=false; // double quate
    bool in_s_quate=false; // single quate
    std::string buf;
    uint i=0;
    while(i<str_len){ // r: read place
        if(str[i]=='\\'){ is_escaped=true; buf+=str[i]; ++i; if(i>=str_len){break;} }
        
        if(!is_escaped && !in_s_quate && str[i]=='"' ){ in_d_quate = !in_d_quate; }
        if(!is_escaped && !in_d_quate && str[i]=='\''){ in_s_quate = !in_s_quate; }
        
        if(!in_d_quate && !in_s_quate && (_is_control_chars(str[i]))){
            buf = sstd::strip(buf);
            if(buf.size()!=0){
                ret.push_back(buf);
                buf.clear();
            }
            ret.push_back(std::string(1, str[i])); // append a control char
            ++i;
        }else{
            buf += str[i];
            ++i;
        }
        
        is_escaped=false;
    }
    if(in_d_quate){ ret.clear(); return false; }
    if(in_s_quate){ ret.clear(); return false; }
    buf = sstd::strip(buf);
    if(buf.size()!=0){ ret.push_back(buf); }
    
    return true;
}
bool _get_hash_value(bool& is_null, std::string& ret_value, const std::vector<std::string>& v_cs, uint& i){
    
    if(i+3<v_cs.size() && v_cs[i+1][0]==':' && (v_cs[i+2][0]!=',' && v_cs[i+2][0]!='}' && v_cs[i+2][0]!=']') && (v_cs[i+3][0]==',' || v_cs[i+3][0]=='}' || v_cs[i+3][0]==']')){
        // { "k1": "v1" }, { "k1": "v1", "k2": "v2" } or [ "k1": "v1" ] (<- Abbreviated of "[{ "k1": "v1" }]")
        ret_value = v_cs[i+2];
        is_null = false;
        i+=2;
        return true; // get value
    }else if(i+2<v_cs.size() && v_cs[i+1][0]==':' && (v_cs[i+2][0]=='}' || v_cs[i+2][0]==']' || v_cs[i+2][0]==',')){
        // { "k1": }, { "k1":, "k2" } or [ "k1": "v1" ] (<- Abbreviated of "[{ "k1": "v1" }]")
        is_null = true;
        ++i;
        return true; // get null value
    }else if(i+1<v_cs.size() && (v_cs[i+1][0]=='}' || v_cs[i+1][0]==']' || v_cs[i+1][0]==',')){
        // { "k1" }, { "k1", "k2" } or [ "k1": "v1" ] (<- Abbreviated of "[{ "k1": "v1" }]")
        is_null = true;
        return true; // get null value
    }

    // not get a string value (have a value of object)
    // { "k1" { "k2": }}
    return false;
}
bool _flow_style_str_to_obj(sstd::terp::var& var_out, const std::unordered_map<std::string, sstd::terp::var*>& tbl_anchor_to_address, const std::string& s_in){
    
    std::vector<std::string> v_cs; // vector of commands and string
    if(!sstd_yaml::_split_quotes_by_control_chars(v_cs, s_in.c_str(), s_in.size())){ sstd::pdbg_err("_split_quotes_by_control_chars() is failed. Un-cloused quate.\n"); return false; }
    
    std::vector<sstd::terp::var*> v_dst;
    v_dst.push_back( &var_out );
    
    for(uint i=0; i<v_cs.size(); ++i){
        if(v_dst.size()==0){ sstd::pdbg_err("broken pointer\n"); return false; }
        sstd::terp::var* pVar = v_dst[v_dst.size()-1];
        sstd::terp::var& var = *pVar;
        
        if(v_cs[i].size()==1 && _is_control_chars(v_cs[i][0])){
            switch(v_cs[i][0]){
            case '[': {
                if(var.typeNum()==sstd::num_null){
                    var = sstd::terp::list();
                }else if(var.typeNum()==sstd::num_vec_terp_var){
                    var.push_back( sstd::terp::list() );
                    v_dst.push_back( &(var[var.size()-1]) );
                }
            } break;
            case ']': {
                if(var.typeNum()==sstd::num_hash_terp_var){ v_dst.pop_back(); } // for [k: v] which is an abbreviated notation of [{k: v}]
                v_dst.pop_back();
            } break;
            case '{': {
                if(var.typeNum()==sstd::num_null){
                    var = sstd::terp::hash();
                }else if(var.typeNum()==sstd::num_vec_terp_var){
                    var.push_back( sstd::terp::hash() );
                    v_dst.push_back( &(var[var.size()-1]) );
                }
            } break;
            case '}': { v_dst.pop_back(); } break;
            case ':': {} break;
            case ',': {} break;
            default: { sstd::pdbg_err("Unexpected char\n"); return false; } break;
            }
        }else{
            switch(var.typeNum()){
            case sstd::num_vec_terp_var: {
                // list
                if(i+1<v_cs.size() && v_cs[i+1].size()==1 && v_cs[i+1][0]==':'){ // for [k: v] which is an abbreviated notation of [{k: v}]
                    var.push_back( sstd::terp::hash() );
                    v_dst.push_back( &(var[var.size()-1]) );
                    --i; continue;
                }
                
//                bool is_alias = _is_alias(v_cs[i]); // for the '*' (alias)
//                if(is_alias){
//                    var.push_back( (sstd::terp::var*)tbl_anchor_to_address[ v_cs[i] ] );
//                }else{
                    var.push_back( v_cs[i] );
//                }
            } break;
            case sstd::num_hash_terp_var: {
                // hash
                bool is_null;
                std::string key = v_cs[i];
                std::string val;
                if(_get_hash_value(is_null, val, v_cs, i)){
                    if(!is_null){ var[ key.c_str() ] = _extract_quotes_value(sstd::strip_quotes(val.c_str()));
                    }   else    { var[ key.c_str() ]; }
                }else{
                    v_dst.push_back( &(var[key.c_str()]) );
                }
            } break;
            case sstd::num_null: {} break;
            default: { sstd::pdbg_err("Unexpected data type. Type: %s\n", sstd::typeNum2str(var.typeNum()).c_str()); sstd::printn_all(var); } break;
            }
        }
    }
    if(v_dst.size()!=0){ sstd::pdbg_err("'[' or '{' is not closed.\n"); return false; }
    
    return true;
}
bool _construct_var(sstd::terp::var& ret_yml, const std::vector<struct sstd_yaml::command>& v_cmd){
    std::vector<sstd::terp::var*> v_dst;    // v: vector, _dst: destination address. An address stack for sstd_yaml::ope_alloc (follows the YAML indent)
    std::vector<sstd::terp::var*> v_dst_cr; // v: vector, _dst: destination address, _cr: current. An address stack for sstd_yaml::ope_stack or sstd_yaml::ope_assign.
    std::vector<uint> v_hsc; // v: vector, hsc: head space count
    v_dst.push_back(&ret_yml);
    v_dst_cr.push_back(&ret_yml);
    v_hsc.push_back(0);

    std::unordered_map<std::string, sstd::terp::var*> tbl_anchor_to_address;
    
    for(uint i=0; i<v_cmd.size(); ++i){
        if(v_dst.size()==0){ sstd::pdbg_err("broken pointer\n"); return false; }
        const struct sstd_yaml::command& cmd = v_cmd[i];

        if(cmd.ope==sstd_yaml::ope_alloc){
            // Inits v_dst_cr if the v_cmd is the beginning of the `sstd_yaml::ope_alloc` operation.
            v_dst_cr.clear();
            if(v_dst.size()==0){ sstd::pdbg_err("broken pointer\n"); return false; }
            v_dst_cr.push_back(v_dst[v_dst.size()-1]);
        }
        sstd::terp::var* pVar = v_dst_cr[v_dst_cr.size()-1];
        sstd::terp::var& var = *pVar;
        if(v_hsc.size()==0){ sstd::pdbg_err("v_hsc is out of range\n"); return false; }
        uint hsc_base = v_hsc[v_hsc.size()-1];
        
        // checking the stack command
        if(cmd.ope==sstd_yaml::ope_stack){
            if(v_dst_cr.size()==0){ sstd::pdbg_err("broken pointer\n"); return false; }
            v_dst.push_back(v_dst_cr[v_dst_cr.size()-1]);
            v_hsc.push_back(cmd.hsc);
            continue;
        }
        
        // checking the YAML indent
        if(cmd.hsc < hsc_base){
            v_dst.pop_back();
            v_hsc.pop_back();
            --i;
            continue; // continue for multiple escape
        }
        
        // setting the value or allocate dst address
        if(cmd.ope==sstd_yaml::ope_assign){
            if(var.typeNum()!=sstd::num_null){ sstd::pdbg_err("OverWritting the existing data.\n"); return false; }
            if(cmd.format==sstd_yaml::format_flow_style){
                if(!_flow_style_str_to_obj(var, tbl_anchor_to_address, cmd.val)){ sstd::pdbg_err("_flow_style_str_to_obj() is failed.\n"); return false; }
            }else{
                var = cmd.val;
            }
        }else if(cmd.ope==sstd_yaml::ope_alloc){
            if(var.typeNum()==sstd::num_null){
                switch(cmd.type){
                case sstd_yaml::type_list: { var = sstd::terp::list(); } break;
                case sstd_yaml::type_hash: { var = sstd::terp::hash(); } break;
                default: { sstd::pdbg_err("Unexpected data type\n"); return false; } break;
                }
            }
            
            switch(cmd.type){
            case sstd_yaml::type_list: {
                var.push_back();
                v_dst_cr.push_back(&var[var.size()-1]);
                if(cmd.ref_type==sstd_yaml::ref_type_anchor){
                    tbl_anchor_to_address[ cmd.aa_val ] = &var[ var.size()-1 ];
                }else if(cmd.ref_type==sstd_yaml::ref_type_alias){
                    var[ var.size()-1 ] = (sstd::terp::var*)tbl_anchor_to_address[ cmd.aa_val ];
                }
            } break;
            case sstd_yaml::type_hash: {
                auto itr = var.find(cmd.val);
                if(itr!=var.end()){ sstd::pdbg_err("Detecting the duplicated hash key.\n"); return false; }
                v_dst_cr.push_back(&var[cmd.val]);
            } break;
            default: { sstd::pdbg_err("Unexpected data type\n"); return false; } break;
            }
        }else{
            sstd::pdbg_err("Unexpected data type\n"); return false;
        }
    }
    
    return true;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// str2token section

bool _is_flow(const std::string& s){
    return (s.starts_with('[') || s.starts_with('{'));
}
bool _is_end_marker(const std::string& s){
    return s.starts_with("...");
}
bool _is_separator(const std::string& s){
    return s.starts_with("---");
}
bool _is_anchor(const std::string& s){
    return s.starts_with("&");
}
bool _is_alias(const std::string& s){
    return s.starts_with("*");
}
void _split_aa_val_and_val(std::string& out_aa_val, std::string& out_val, const std::string& in){
    std::vector<std::string> v_tmp = sstd::split(in, 1);
    if(v_tmp.size()==1){
        std::string tmp;
        std::swap(out_aa_val, v_tmp[0]);
        std::swap(out_val,    tmp     );
    }else if(v_tmp.size()==2){
        std::swap(out_aa_val, v_tmp[0]);
        std::swap(out_val,    v_tmp[1]);
    }else{
        sstd::pdbg_err("Unexpected data size\n"); 
    }
    return;
}
bool sstd_yaml::_str2token_except_multilines(std::vector<sstd_yaml::token>& ret, const std::string& str){
    // Parse rule of YAML string
    // 
    // Rule1. For default, Block-Style-String ("- ", ": ") and Line-Break-Codes ('\n') are
    //        treated as controle-charactors ("- ", ": ", '\n').
    //        String are splitted by the controle-characotrs
    //        if the target string is out of quates ("", '') and brackets ([], {}) ranges.
    //        / デフォルトでは，Block-Style の文字列 ("- ", ": ") と改行コード ('\n') を制御文字列として扱います．
    //          引用符 ("", '') と括弧 ([], {}) の範囲外では，文字列は制御文字列で分割されます．
    //
    // Rule2. Skipping the splitting process using controle-charactors ("- ", ": ", '\n')
    //        if the string in quates range.
    //        / 文字列がクォーテーションで括られている場合は，
    //          制御文字 ("- ", ": ", '\n') での文字列の分割を停止します．
    // 
    // Rule3. Skipping the splitting process using controle-charactors ("- ", ": ", '\n')
    //        after detecting the subtoken is beginning from the beginning of brackets ([, {) for flow-style-notation.
    //        / Subtoken が Flow-Style 表記の開始を示す括弧 ([, {) で開始される場合は，
    //          制御文字 ("- ", ": ", '\n') での文字列の分割を停止します．
    // 
    // Rule4. Detecting comments by "#" (in head of the line) or " #" notation
    //        / コメントは "#" (行の先頭) または " #" 表記で判定します
    // 
    // Rule5. Using line break code ('\n') as a control charactor
    //        excepting the case of subtoken begin from multi-line notation charactor ('|').
    //        / 改行コード ('\n') は，制御文字として扱います．
    //          ただし，subtoken がマルチライン表記を示す文字 ('|') から始まる場合を除きます．
    
    uint line_num = 1; // line number is 1 indexed

    // for quotes ("", '')
    bool is_escaped=false; // \", \'
    bool in_d_quate=false; // double quate ("")
    bool in_s_quate=false; // single quate ('')

    for(uint r=0; str[r]!='\0';){ // r: read place
        sstd_yaml::token tmp;
        tmp.line_num_begin = line_num;
        
        std::string subt; // subtoken
        
        // for hsc
        bool is_hs=true; // To identify the spacs ' ' is hsc or charactor between the token.

        // for type
        bool is_list=false; // is list type "- "
        bool is_hash=false; // is hash type "k: v"
        bool is_flow=false; // is flow style "[{k: v}]"
        bool is_end_marker=false; // is "..."
        bool subt_has_a_val=false; // for "- a - b - c -"
        
        int num_of_square_brackets=0; // []
        int num_of_curly_brackets=0;  // {}

        // for quates ("", '')
        bool dqed=false; // double quated
        bool sqed=false; // single quated
        
        for(;;++r){
            if(str[r]=='\\'){ is_escaped=true; tmp.rawStr+=str[r]; subt+=str[r]; ++r; } // Escape for inside quates will be processed at xxx() functiuon.
            if(str[r]=='\0'){ ++line_num; break; }
            if(str[r]!=' '){ is_hs=false; }
            if(str[r]==' ' && is_hs){ ++tmp.hsc_lx; ++tmp.hsc_hx; }
            
            if(!is_escaped && !in_s_quate && str[r]=='"' ){ in_d_quate = !in_d_quate; dqed=true; }
            if(!is_escaped && !in_d_quate && str[r]=='\''){ in_s_quate = !in_s_quate; sqed=true; }
            
            if(!in_d_quate && !in_s_quate){
                if((subt.size()==0 && str[r]=='#') || (str[r]==' ' && str[r+1]=='#')){
                    tmp.rawStr+=str[r]; ++r;
                    while(str[r]!='\0' && str[r]!='\n'){ tmp.rawStr+=str[r]; ++r; } // skip comments
                    if(str[r]=='\0'){ ++line_num; break; }
                }
                
                is_end_marker = _is_end_marker(subt);
                if(is_end_marker){ break; }
                
                is_flow = _is_flow(subt+str[r]);
                if(!is_flow){
                    // Block Style
                    
                    // for Unix
                    if(str[r]=='-' && str[r+1]=='\n' && !subt_has_a_val){                                       subt.clear(); is_list=true; ++tmp.list_type_cnt; tmp.rawStr+=str[r]; continue; }
                    if(str[r]==':' && str[r+1]=='\n'                   ){ tmp.key=std::move(sstd::strip(subt)); subt.clear(); is_hash=true;                      tmp.rawStr+=str[r]; tmp.key_is_dqed=dqed; tmp.key_is_sqed=sqed; continue; }
                    
                    // the other case
                    if(str[r]=='-' && str[r+1]==' ' && !subt_has_a_val){                                       subt.clear(); is_list=true; ++tmp.list_type_cnt; tmp.rawStr+=str[r];                                             ++r; tmp.rawStr+=str[r]; continue; }
                    if(str[r]==':' && str[r+1]==' '                   ){ tmp.key=std::move(sstd::strip(subt)); subt.clear(); is_hash=true;                      tmp.rawStr+=str[r]; tmp.key_is_dqed=dqed; tmp.key_is_sqed=sqed; ++r; tmp.rawStr+=str[r]; continue; }
                }else{
                    // Flow Style
                    if(str[r]=='['){ ++num_of_square_brackets; }
                    if(str[r]==']'){ --num_of_square_brackets; }
                    if(str[r]=='{'){ ++num_of_curly_brackets; }
                    if(str[r]=='}'){ --num_of_curly_brackets; }
                }
            }

            // Checking the line break
            if(str[r]=='\n'){ // Uinx ("\n")
                ++line_num;
                is_hs=true;
                if(!is_flow && !is_escaped && !in_d_quate){ ++r; break; } 
                if( is_flow && num_of_square_brackets==0 && num_of_curly_brackets==0){ ++r; break; }
            }

            // save the input string to the buffers
            tmp.rawStr += str[r];
            subt       += str[r];
            if(str[r]!='-' && str[r]!=' '){ subt_has_a_val=true; }

            // init
            is_escaped = false;
        }
        if(is_end_marker){ break; }
        tmp.line_num_end = std::max((int)tmp.line_num_begin, ((int)line_num)-1);
        
        tmp.val=std::move(sstd::strip(subt));
        tmp.val_is_dqed=dqed;
        tmp.val_is_sqed=sqed;
        bool is_anchor = _is_anchor(tmp.val); // for the '&' (anchor)
        bool is_alias  = _is_alias (tmp.val); // for the '*' (alias)
        
        if(is_list){ tmp.type += sstd_yaml::type_list; tmp.hsc_hx+=2; }
        if(is_hash){ tmp.type += sstd_yaml::type_hash; }
        
        if(is_flow  ){ tmp.format   = sstd_yaml::format_flow_style;                                                     }
        if(is_anchor){ tmp.ref_type = sstd_yaml::ref_type_anchor; tmp.val.erase(0,1); _split_aa_val_and_val(tmp.aa_val, tmp.val, tmp.val); } // 1) set format type, 2) remove '&' in the head of the string
        if(is_alias ){ tmp.ref_type = sstd_yaml::ref_type_alias;  tmp.val.erase(0,1); _split_aa_val_and_val(tmp.aa_val, tmp.val, tmp.val); } // 1) set format type, 2) remove '*' in the head of the string
        
        // Skip empty tokens until the first non-empty token occurs. (Empty token is treated as a line-break related with to other token in a context of multi-line YAML)
        if(ret.size()==0 &&
           tmp.key.size()==0 &&
           tmp.val.size()==0 &&
           tmp.type==sstd_yaml::type_str){ continue; }
        
        // set hasValue
        tmp.hasValue=false;
        switch(tmp.type){
        case sstd_yaml::type_str:
        case sstd_yaml::type_list:
        case sstd_yaml::type_list_and_hash:
        case sstd_yaml::type_hash:          { if(tmp.val_is_dqed||tmp.val_is_sqed||tmp.val.size()>=1){tmp.hasValue=true;} } break; // check the value is NOT NULL
        default: { sstd::pdbg_err("Unexpected data type\n"); return false; } break;
        }

        ret.push_back(std::move(tmp));
    }
    if(in_d_quate){ ret.clear(); sstd::pdbg_err("The variable check of `in_d_quate` failed.\n"); return false; }
    if(in_s_quate){ ret.clear(); sstd::pdbg_err("The variable check of `in_s_quate` failed.\n"); return false; }
    
    if(str.size()>=1 && str[str.size()-1]=='\n'){
        ret.push_back(sstd_yaml::token());
    }
    
    return true;
}
bool _is_all_the_data_str_type(const std::vector<sstd_yaml::token>& v){
    for(uint i=0; i<v.size(); ++i){
        if(v[i].type!=sstd_yaml::type_str){ return false; }
    }
    return true;
}
bool _is_all_the_data_flowStyle(const std::vector<sstd_yaml::token>& v){
    for(uint i=0; i<v.size(); ++i){
        if(v[i].format!=sstd_yaml::format_flow_style){ return false; }
    }
    return true;
}
bool _merge_all_str(std::vector<sstd_yaml::token>& ret, const std::vector<sstd_yaml::token>& v){
    if(v.size()==0){ return true; }
    
    sstd_yaml::token t = v[0];
    //t.line_num_begin = v[     0    ].line_num_begin;
    t.line_num_end   = v[v.size()-1].line_num_end;
    
    for(uint i=1; i<v.size(); ++i){
        t.rawStr += "\n" + v[i].rawStr;
        t.val    += "\n" + v[i].val;
    }

    t.mult_line_val = true;
    
    ret.push_back(t);
    
    return true;
}
bool _is_control_types(uint type){
    return (type==sstd_yaml::type_list || type==sstd_yaml::type_hash || type==sstd_yaml::type_list_and_hash);
}
uint _get_criteria_hsc(const sstd_yaml::token& t){
    if(t.type==sstd_yaml::type_hash || t.type==sstd_yaml::type_list_and_hash){
        return t.hsc_hx;
    }else{
        if(t.list_type_cnt!=1){ return t.hsc_lx + t.list_type_cnt * 2; }
        return t.hsc_lx;
    }
}
uint _get_current_hsc(const sstd_yaml::token& t){
    if(t.type==sstd_yaml::type_hash){
        return t.hsc_hx;
    }else{
        return t.hsc_lx; // for sstd_yaml::type_str or sstd_yaml::type_list
    }
}
bool sstd_yaml::_token2token_split_bv_list_type_cnt(std::vector<sstd_yaml::token>& io){
    // Example:
    //
    // in:
    // > - - - a
    //
    // out:
    // > -
    // >   -
    // >     - a
    
    std::vector<sstd_yaml::token> ret;
    
    for(uint i=0; i<io.size(); ++i){
        sstd_yaml::token& t = io[i];
        
        if(t.list_type_cnt==0){
            ret.push_back(t);
        }else{
            // For `0 <= ti < t.list_type_cnt`
            uint ti=0;
            for(; ti+1<t.list_type_cnt; ++ti){
                sstd_yaml::token tmp = t;
                
                tmp.type = sstd_yaml::type_list;
                tmp.format = sstd_yaml::format_block_style;
                tmp.list_type_cnt = 1;
                tmp.hsc_lx = tmp.hsc_lx + 2 * ti;
                tmp.hsc_hx = tmp.hsc_lx + 2;
                
                tmp.hasValue = false;
                tmp.key_is_dqed = false;
                tmp.key_is_sqed = false;
                tmp.val_is_dqed = false;
                tmp.val_is_sqed = false;
                tmp.mult_line_val = false;

                tmp.key.clear();
                tmp.val.clear();
                
                ret.push_back(std::move(tmp));
            }
            
            // For `ti == t.list_type_cnt`.
            {
                sstd_yaml::token tmp = t;
                
                tmp.list_type_cnt = 1;
                tmp.hsc_lx = tmp.hsc_lx + 2 * ti;
                tmp.hsc_hx = tmp.hsc_lx + 2;
                
                ret.push_back(std::move(tmp));
            }
        }
    }
    
    std::swap(ret, io);
    return true;
}
bool sstd_yaml::_token2token_merge_multilines(std::vector<sstd_yaml::token>& io){
    std::vector<sstd_yaml::token> ret;

    bool is_all_the_data_flowStyle = _is_all_the_data_flowStyle(io);
    if(is_all_the_data_flowStyle){
        
        // Do notheing for the flowStyle
        
        return true;
    }
    bool is_all_the_data_str_type  = _is_all_the_data_str_type(io);
    if(is_all_the_data_str_type){
        
        if(!_merge_all_str(ret, io)){ sstd::pdbg_err("_merge_all_str() was failed.\n"); return false; }

        std::swap(ret, io);
        return true;
    }
    
    // mearge all the separated multi-line tokens
    uint i=0;
    do{
        sstd_yaml::token* pT = &io[i];
        sstd_yaml::token tmp = (*pT);

        // Check criteria values (Defining criteria value as a base token like list, hash or list_and_hash type to merge)
        bool start_with_string = (*pT).val.size()>=1 && (*pT).ref_type==sstd_yaml::ref_type_null;
        uint criteria_hsc = _get_criteria_hsc((*pT)); // criteria_hsc: criteria head space count
        
        for(uint merge_cnt=1;; ++merge_cnt){
            // Update
            ++i;
            if( i>=io.size() ){ break; }
            pT = &io[i];

            bool is_control_types = _is_control_types((*pT).type);
            
            // Check break
            uint curr_hsc = _get_current_hsc((*pT)); // curr_hsc: current head space count
            if( merge_cnt==1 && is_control_types && (!start_with_string||(curr_hsc<=criteria_hsc)) ){ break; }
            // - `!start_with_string` is for:
            //   │ k0:
            //   │   k1: v
            // - `curr_hsc<=criteria_hsc` is for:
            //   │ - k1: v1
            //   │ - k2: v2

            // Update `start_with_string` to the current token
            start_with_string |= (*pT).type==sstd_yaml::type_str; // for "k:\n  l1\n  l2"
            // Check the needs of breaking the merge process
            // Under the following situation, the parser needs to break the process of multi-line merging.
            //   - `start_with_string`: The string start with non-control charactor
            //   - `(*pT).key.size()!=0||(*pT).val.size()!=0`: The line is NOT Empty. (If the line is empty, the parser needs to treat as a line break of multi-line string).
            //   - `curr_hsc<=criteria_hsc`: The line is out of scope.
            if( start_with_string && (((*pT).key.size()!=0||(*pT).val.size()!=0||(*pT).key_is_dqed||(*pT).key_is_sqed||(*pT).val_is_dqed||(*pT).val_is_sqed) && curr_hsc<=criteria_hsc) ){ break; }

            if( _is_separator((*pT).rawStr) ){ break; }
            
            // Copy values
            tmp.rawStr += '\n' + (*pT).rawStr;
            tmp.val    += '\n' + (*pT).rawStr; // Needs to copy as row string in order to treat multi-line string as a raw data. Ex1: "k:\n x\n - a" is interpreted as `{k: "x - a"}`. Ex2: "k: |\n x # comment" is interpreted as `{k: "x # comment"}`.
            tmp.line_num_end = (*pT).line_num_end;
            tmp.mult_line_val = true;
        }
        
        ret.push_back(std::move(tmp));
    }while( i<io.size() );
    
    std::swap(ret, io);
    return true;
}
bool _escape_to_unicode_character(std::string& io){
    std::string tmp;
    
    for(uint i=0; i<io.size(); ++i){
        if(io[i]=='\\'){
            switch(io[i+1]){
            case '\0': { tmp += '\\'; break; }
            case '\'':  { tmp += '\''; break; }
            case '\n':  { tmp += "\\\n"; break; } // Do Nothing in order NOT to avoid `_format_mult_line_str()` function's process.
                
            case '\\': { tmp += '\\'; break; }
                
            case '"':  { tmp += '\"'; break; }
            case 'a':  { tmp += (uchar)0x07; break; }
            case 'b':  { tmp += '\b'; break; }
//            case 'e':  { tmp += '\u001b'; break; } // Needs to check "How UTF-8 encode" if we treats as UTF-8.
            case 'f':  { tmp += '\f'; break; }
                
            case 'n':  { tmp += '\n'; break; }
            case 'r':  { tmp += '\r'; break; }
            case 't':  { tmp += '\t'; break; }
            case 'v':  { tmp += '\u000b'; break; }
            case '0':  { tmp += (uchar)0x00; break; }
                
            //case ' ': { tmp += '\\'; break; }
//            case '_':  { tmp += '\u00a0'; break; } // Needs to check "How UTF-8 encode" if we treats as UTF-8. (Byte order is the concern point)
//            case 'N':  { tmp += '\u0085'; break; } // Needs to check "How UTF-8 encode" if we treats as UTF-8. (Byte order is the concern point)
//            case 'L':  { tmp += '\u2028'; break; } // Needs to check "How UTF-8 encode" if we treats as UTF-8. (Byte order is the concern point)
//            case 'P':  { tmp += '\u2029'; break; } // Needs to check "How UTF-8 encode" if we treats as UTF-8. (Byte order is the concern point)
            default: {
//                if      (sstd::startswith(&io[i+1], "x41"      )){ tmp += "A"; i+=strlen("x41"      ); break; // Needs to check "How UTF-8 encode" if we treats as UTF-8.
//                }else if(sstd::startswith(&io[i+1], "u0041"    )){ tmp += "A"; i+=strlen("u0041"    ); break; // Needs to check "How UTF-8 encode" if we treats as UTF-8.
//                }else if(sstd::startswith(&io[i+1], "U00000041")){ tmp += "A"; i+=strlen("U00000041"); break; } // Needs to check "How UTF-8 encode" if we treats as UTF-8.
                
                sstd::pdbg_err("%c%c is not escapeable.\n", io[i], io[i+1]); return false; }
            }
            ++i;
        }else{
            tmp += io[i];
        }
    }
    
    std::swap(tmp, io);
    return true;
}
bool sstd_yaml::_token2token_postprocess(std::vector<sstd_yaml::token>& io){
    
    for(uint i=0; i<io.size(); ++i){
        sstd_yaml::token& t = io[i];
        
        bool is_key_quated = t.key_is_dqed || t.key_is_sqed;
        bool is_val_quated = t.val_is_dqed || t.val_is_sqed;
        
        if(is_key_quated){
            if(!_escape_to_unicode_character(t.key)){ sstd::pdbg_err("_escape_to_unicode_character() is failed.\n"); return false; }
        }
        if(is_val_quated){
            if(!_escape_to_unicode_character(t.val)){ sstd::pdbg_err("_escape_to_unicode_character() is failed.\n"); return false; }
        }
        
        if(t.mult_line_val){
            // Needs to format with quates ("", '') for the YAML string of `- " a "`.
            uint hsc_base_yaml = _get_criteria_hsc(t);
            bool has_next_token = (io.size()>(i+1));
            if(!sstd_yaml::_format_mult_line_str(t.val, t.val, hsc_base_yaml, has_next_token)){ sstd::pdbg_err("sstd_yaml::_format_mult_line_str() is failed.\n"); return false; }
            if(!has_next_token){ sstd::rstripAll_ow(t.rawStr, " \n"); }
        }

        if(is_key_quated){
            bool key_sq, key_dq;
            t.key = sstd::strip_quotes(key_sq, key_dq, t.key);
        }
        if(is_val_quated){
            bool val_sq, val_dq;
            t.val = sstd::strip_quotes(val_sq, val_dq, t.val);
        }
    }
    
    return true;
}
bool sstd_yaml::_str2token(std::vector<sstd_yaml::token>& ret, const char* str_in){
    std::string str = std::regex_replace(str_in, std::regex("\r"), ""); // "\r\n" -> "\n"
    
    if(!sstd_yaml::_str2token_except_multilines(ret, str.c_str())){ sstd::pdbg_err("sstd_yaml::_str2token_except_multilines() was failed.\n"); return false; }
    if(!sstd_yaml::_token2token_merge_multilines(ret)){ sstd::pdbg_err("sstd_yaml::_token2token_merge_multilines() was failed.\n"); return false; }
    if(!sstd_yaml::_token2token_split_bv_list_type_cnt(ret)){ sstd::pdbg_err("sstd_yaml::_token2token_split_bv_list_type_cnt() was failed.\n"); return false; }
    if(!sstd_yaml::_token2token_postprocess(ret)){ sstd::pdbg_err("sstd_yaml::_token2token_postprocess() was failed.\n"); return false; }
    return true;
}
bool sstd_yaml::_str2token(std::vector<sstd_yaml::token>& ret, const std::string& str){ return sstd_yaml::_str2token(ret, str.c_str()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// YAML load section

bool _yaml_load_base(sstd::terp::var& ret_yml, const std::vector<sstd_yaml::token>& v_token){
    
    std::vector<struct sstd_yaml::command> v_cmd;
    if(!sstd_yaml::_token2cmd(v_cmd, v_token)){ return false; }
    sstd::printn_all(v_cmd);
    
    if(!_construct_var(ret_yml, v_cmd)){ return false; }
    
    return true;
}
bool sstd::yaml_load(sstd::terp::var& ret_yml, const char* s){
    
    std::vector<sstd_yaml::token> v_token;
    if(!sstd_yaml::_str2token(v_token, s)){ sstd::pdbg_err("single or double quatation is not closed\n"); return false; } // v: vector, ls: line string
    sstd::printn_all(v_token);
    
    if(!_yaml_load_base(ret_yml, v_token)){ sstd::pdbg_err("_yaml_load_base() is failed.\n"); return false; }
    sstd::printn_all(ret_yml);
    
    return true;
}
bool sstd::yaml_load(sstd::terp::var& ret_yml, const std::string& s){ return sstd::yaml_load(ret_yml, s.c_str()); }

//---

std::vector<std::vector<std::string>> _split_by_separator(const std::vector<std::string>& ls){
    std::vector<std::vector<std::string>> v_ls;

    std::vector<std::string> ls_tmp;
    for(uint i=0; i<ls.size(); ++i){
        std::string s = ls[i];
        s = _rm_comment(s); // s = _rm_comment_quotes(s); に置き換える
        if(s=="---"){ // detect the separator
            v_ls.push_back(std::move(ls_tmp));
            ls_tmp.clear();
            continue;
        }
        
        ls_tmp.push_back(std::move(ls[i]));
    }
    v_ls.push_back(std::move(ls_tmp));
    
    return v_ls;
}
std::vector<std::vector<sstd_yaml::token>> _split_by_separator(std::vector<sstd_yaml::token>& vT){
    std::vector<std::vector<sstd_yaml::token>> ret_vvT;
    
    std::vector<sstd_yaml::token> tmp_vT;
    for(uint i=0; i<vT.size(); ++i){
        if(vT[i].rawStr.starts_with("---")){ // detect the separator
            ret_vvT.push_back(std::move(tmp_vT));
            tmp_vT.clear();
            continue;
        }
        
        tmp_vT.push_back(std::move(vT[i]));
    }
    ret_vvT.push_back(std::move(tmp_vT));
    
    return ret_vvT;
}
bool sstd::yaml_load_all(std::vector<sstd::terp::var>& ret_vYml, const        char* s){
    std::vector<sstd_yaml::token> v_token;
    if(!sstd_yaml::_str2token(v_token, s)){ sstd::pdbg_err("single or double quatation is not closed\n"); return false; } // v: vector, ls: line string
    
    std::vector<std::vector<sstd_yaml::token>> vvT = _split_by_separator(v_token);
    
    uint base_idx=0;
    for(uint i=0; i<vvT.size(); ++i){
        sstd::terp::var ret_yml;
        if(!_yaml_load_base(ret_yml, vvT[i])){ sstd::pdbg_err("_yaml_load_base() is failed.\n"); return false; }
        ret_vYml.push_back(std::move(ret_yml));
        
        base_idx += 1 + vvT[i].size();
    }
    
    return true;
}
bool sstd::yaml_load_all(std::vector<sstd::terp::var>& ret_vYml, const std::string& s){ return sstd::yaml_load_all(ret_vYml, s.c_str()); }

//---

bool sstd::yaml_load(sstd::terp::var& ret_yml, sstd::file& fp){
    size_t size = fp.fsize();
    std::vector<char> raw(size+1, 0);
    if(fp.fread((uchar*)&raw[0], sizeof(char), size)!=size){
        sstd::pdbg_err("fread was failed.\n");
        return false;
    }
    
    if(!sstd::yaml_load(ret_yml, (const char*)&raw[0])){ return false; }
    
    return true;
}
bool sstd::yaml_load_all(std::vector<sstd::terp::var>& ret_vYml, sstd::file& fp){
    size_t size = fp.fsize();
    std::vector<char> raw(size+1, 0);
    if(fp.fread((uchar*)&raw[0], sizeof(char), size)!=size){
        sstd::pdbg_err("fread was failed.\n");
        return false;
    }
    
    if(!sstd::yaml_load_all(ret_vYml, (const char*)&raw[0])){ return false; }
    
    return true;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

