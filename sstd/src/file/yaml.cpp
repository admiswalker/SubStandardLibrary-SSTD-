#include <cassert>
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

bool sstd_yaml::_splitByLine_quotes_brackets(std::vector<std::string>& ret, const char* str){
    
    bool is_escaped=false;
    bool in_d_quate=false; // double quate
    bool in_s_quate=false; // single quate
    std::string buf;
    
    int num_of_square_brackets=0; // []
    int num_of_curly_brackets=0;  // {}
    for(uint r=0; str[r]!=0;){ // r: read place
        buf.clear();
        for(; str[r]!='\0'; ++r){
            if(str[r]=='\\'){ is_escaped=true; buf+=str[r]; ++r; if(str[r]=='\0'){break;} }
            
            if(!is_escaped && !in_s_quate && str[r]=='"' ){ in_d_quate = !in_d_quate; }
            if(!is_escaped && !in_d_quate && str[r]=='\''){ in_s_quate = !in_s_quate; }
            
            if(!in_d_quate && !in_s_quate && str[r]=='['){ ++num_of_square_brackets; }
            if(!in_d_quate && !in_s_quate && str[r]==']'){ --num_of_square_brackets; }
            
            if(!in_d_quate && !in_s_quate && str[r]=='{'){ ++num_of_curly_brackets; }
            if(!in_d_quate && !in_s_quate && str[r]=='}'){ --num_of_curly_brackets; }
            
            if(!in_d_quate && !in_s_quate && num_of_square_brackets==0 && num_of_curly_brackets==0 && str[r]==0x0A                  ){ r+=1; break; } // Uinx ("\n")
            if(!in_d_quate && !in_s_quate && num_of_square_brackets==0 && num_of_curly_brackets==0 && str[r]==0x0D && str[r+1]==0x0A){ r+=2; break; } // Windows ("\r\n")
            buf += str[r];
            
            is_escaped=false;
        }
        ret.push_back(std::move(buf));
    }
    if(in_d_quate){ ret.clear(); return false; }
    if(in_s_quate){ ret.clear(); return false; }
    if(num_of_square_brackets){ ret.clear(); return false; }
    if(num_of_curly_brackets ){ ret.clear(); return false; }
    
    return true;
}
bool sstd_yaml::_splitByLine_quotes_brackets(std::vector<std::string>& ret, const std::string& str){
    return sstd_yaml::_splitByLine_quotes_brackets(ret, str.c_str());
}

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
//            for(uint i_t=0; i_t<new_line_cnt-1; ++i_t){ ret += "\\n"; } // when using a escaped notation rule
            for(uint i_t=0; i_t<new_line_cnt-1; ++i_t){ ret += '\n'; }
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

void _rm_colon(std::string& s){
    if(s.size()>=1){
        s.pop_back();
    }
    return;
}
std::string _rm_hyphen(std::string s){
    uint i=0;
    for(; i<s.size(); ++i){
        if(s[i]==' '||s[i]=='-'){ continue; }
        break;
    }
    return &s[i];
}

//---

bool _is_hash(bool& ret, const std::string& s){
    ret = false;
    std::string ret_s;
    if(!sstd::extract_unquoted(ret_s, s)){ sstd::pdbg_err("quate is not closed\n"); return false; }
    ret = sstd::strIn(": ", ret_s) || (s.size()>=1 && s[s.size()-1]==':');
    return true;
}
std::string _extract_hash_value(const std::string& s){
    for(uint i=0; i<s.size()-1; ++i){
        if(s[i]==':' && s[i+1]==' ' && i+2<s.size()){ return std::string(&s[i+2]); }
    }
    
    return "";
}

//---

uint _head_space_or_hyphen_count(const std::string& s){
    uint c=0;
    for(uint i=0; i<s.size(); ++i){
        if(s[i]==' ' || s[i]=='-'){ ++c; continue; }
        break;
    }
    return c;
}
uint _head_space_count(const std::string& s){
    uint c=0;
    for(uint i=0; i<s.size(); ++i){
        if(s[i]==' '){ ++c; continue; }
        break;
    }
    return c;
}
bool _hsc_hx(uint& ret, const std::string& s){
    bool is_h;
    if(!_is_hash(is_h, s)){ sstd::pdbg_err("quate is not closed\n"); return false; }
    
    if(is_h){ ret = _head_space_or_hyphen_count(s); return true;
    }  else { ret = _head_space_count(s);           return true;
    }
}
void _hsc_lx(uint& ret, const std::string& s){
    ret = _head_space_count(s);
    return;
}

//---

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
void _print(const struct command& cmd){ // for debug
    printf("hsc_lx: %d\n",           cmd.hsc_lx                            );
    printf("hsc_hx: %d\n",           cmd.hsc_hx                            );
    printf("type: %d\n",             cmd.type                              );
    printf("format: %d\n",           cmd.format                            );
    printf("val1_use_quotes: %s\n", (cmd.val1_use_quotes ? "true":"false") );
    printf("val2_use_quotes: %s\n", (cmd.val2_use_quotes ? "true":"false") );
    printf("val1: %s\n",             cmd.val1.c_str()                      );
    printf("val2: %s\n",             cmd.val2.c_str()                      );
    printf("lineNum: %d\n",          cmd.lineNum                           );
    printf("rawStr: %s\n",           cmd.rawStr.c_str()                    );
    printf("\n");
}
void _print(const std::vector<struct command>& v_cmd){ // for debug
    for(uint i=0; i<v_cmd.size(); ++i){
        _print(v_cmd[i]);
    }
}

//---

bool sstd_yaml::_data_type_and_format(uint& type, uint& format, uint& list_type_cnt, std::string s){
    type   = sstd_yaml::num_str;
    format = sstd_yaml::num_block_style_base;
    list_type_cnt = 0;

    std::vector<std::string> v;
    if(!sstd::split_quotes(v, s)){ sstd::pdbg_err("quate is not closed\n"); return false; }
//    sstd::printn(v);
    
    bool is_list = false;
    bool is_hash = false;

    for(uint i=0; i<v.size(); ++i){
        uint size = v[i].size();
        
        if(size>=1 && v[i][   0  ]=='['){ format=sstd_yaml::num_flow_style_base; }
        if(size>=1 && v[i][   0  ]=='{'){ format=sstd_yaml::num_flow_style_base; }
        if(size==1 && v[i][   0  ]=='-'){ is_list=true; ++list_type_cnt; }
        if(size>=1 && v[i][size-1]==':'){ if(format!=sstd_yaml::num_flow_style_base){ is_hash=true; } }
    }
    if(is_list){ type += sstd_yaml::num_list; }
    if(is_hash){ type += sstd_yaml::num_hash; }
    
    return true;
}
bool _split_hash(std::vector<std::string>& ret_v, std::string s){
    if(s.size()>=1 && s[s.size()-1]==':'){ s.pop_back(); ret_v.push_back(s); return true; }
    return sstd::split_quotes(ret_v, s, ": ");
}
bool _get_value(bool& ret_val1_use_quotes, bool& ret_val2_use_quotes, std::string& ret_val1, std::string& ret_val2, std::string s, uint typeNum, uint format){
    ret_val1_use_quotes=false;
    ret_val2_use_quotes=false;
    ret_val1.clear();
    ret_val2.clear();
    bool dq, sq;

    // switch(v_cmd[i].format + v_cmd[i].type){ // 730 行目的なかんじ (<-) に修正したい
    if(format==sstd_yaml::num_block_style_base){
        switch(typeNum){
        case sstd_yaml::num_str:  {
            ret_val1 = _extract_quotes_value(sstd::strip_quotes(sq, dq, s));
            ret_val1_use_quotes = ( dq || sq );
        } break;
        case sstd_yaml::num_list: {
            ret_val1 = _extract_quotes_value(sstd::strip_quotes(sq, dq, _rm_hyphen(s)));
            ret_val1_use_quotes = ( dq || sq );
        } break;
        case sstd_yaml::num_hash:
        case sstd_yaml::num_list_and_hash: {
            std::vector<std::string> v;
            if(!_split_hash(v, s)){ sstd::pdbg_err("single quatation or double quatation is not closed\n"); return false; }
            //if(v.size()==0){ sstd::pdbg_err("Unexpected data size.\n"); return false; }
            if(v.size()>=1){ ret_val1 = _extract_quotes_value(sstd::strip_quotes(sq, dq, _rm_hyphen(v[0]))); ret_val1_use_quotes = ( sq || dq ); }
            if(v.size()>=2){ ret_val2 = _extract_quotes_value(sstd::strip_quotes(sq, dq,            v[1] )); ret_val2_use_quotes = ( sq || dq ); }
            if(v.size()>=3){ sstd::pdbg("Unexptected split by ':'."); return false; }
        } break;
        default: { sstd::pdbg_err("Unexpected typeNum\n"); return false; } break;
        }
        
    }else if(format==sstd_yaml::num_flow_style_base){
        switch(typeNum){
        case sstd_yaml::num_str:  {
            ret_val1 = _extract_quotes_value(sstd::strip_quotes(sq, dq, s));
            ret_val1_use_quotes = ( dq || sq );
        } break;
        case sstd_yaml::num_list:
        case sstd_yaml::num_hash:
        case sstd_yaml::num_list_and_hash: {
            ret_val1 = _extract_quotes_value(sstd::strip_quotes(sq, dq, _rm_hyphen(s)));
            ret_val1_use_quotes = ( dq || sq );
        } break;
        default: { sstd::pdbg_err("Unexpected typeNum\n"); return false; } break;
        }
        
    }else{
        sstd::pdbg_err("Unexpected data type\n"); return false;
    }
    
    return true;
}

bool _get_multi_line_str(std::string& ret, const uint hsc_prev, const std::string& opt, int indent_width, const std::vector<std::string>& ls, uint& i){
    std::vector<std::string> v_tmp;

    char separator='\n';
    //if(sstd::charIn('|', opt)){ separator = '\n'; }
    if(sstd::charIn('>', opt)){ separator =  ' '; }
//    if(indent_width == hsc_prev){ separator = '\n'; }

    for(; i<ls.size(); ++i){
        std::string s;
        s = ls[i];
        s = _rm_comment(s); // s = _rm_comment_quotes(s); に置き換える
        if(s=="..."){ --i; return true; } // detect end marker
        
        uint type=sstd_yaml::num_null, format=sstd_yaml::num_block_style_base, type_cnt=0; if(!sstd_yaml::_data_type_and_format(type, format, type_cnt, s)){ return false; }
        if(type==sstd_yaml::num_str){
            if(indent_width>=0 && s.size()>0){
                uint hsc = _head_space_count(s);
                
                if(hsc+1 <= (hsc_prev + indent_width)){ sstd::pdbg_err("indent indecation is too large.\n"); return false; }

                if(hsc_prev + indent_width == hsc){ // for "- >[Num]", "- >[Num]"
                    s = sstd::strip(s);
                }else{
                    s = sstd::rstrip(s);
                    if(indent_width < (int)s.size()){
                        separator = '\n';
                        s = &s[hsc_prev+indent_width];
                    }
                }
            }else{
                s = sstd::strip(s);
            }
            v_tmp.push_back(s);
        }else{
            --i;
            break;
        }
    }

    if      (opt=="|"  || opt==">" ){
        sstd::rmEmpty_r_ow(v_tmp);
        ret = sstd::join(v_tmp, separator);
        ret += "\n";
    }else if(opt=="|-" || opt==">-"){
        sstd::rmEmpty_r_ow(v_tmp);
        ret = sstd::join(v_tmp, separator);
    }else if(opt=="|+" || opt==">+"){
        uint cnt = sstd::cntEmpty_r(v_tmp) + 1;
        sstd::rmEmpty_r_ow(v_tmp);
        ret = sstd::join(v_tmp, separator) + std::string(cnt, '\n');
    }else{
        sstd::pdbg_err("Unexpected case\n"); return false;
    }

    return true;
}
bool _check_val_and_overwrite_multi_line_str(std::string& val_rw, const uint hsc_prev, const std::vector<std::string>& ls, uint& i){
    int indent_width = -1;

    if      (val_rw.starts_with("|-") || val_rw.starts_with(">-") ||    // case: "- |-123", "- >-123", "hash-key: |-123" or "hash-key: >-123"
             val_rw.starts_with("|+") || val_rw.starts_with(">+")    ){ // case: "- |+123", "- >+123", "hash-key: |+123" or "hash-key: >+123"
        ++i;
        std::string opt; opt += val_rw[0]; opt += val_rw[1];
        if(val_rw.size()>=3){
            indent_width = std::stoi(&val_rw[2]);
        }else{
            indent_width = _head_space_count(ls[i]);
        }
        
        if(!_get_multi_line_str(val_rw, hsc_prev, opt, indent_width, ls, i)){ return false; }
        
    }else if(val_rw.starts_with("|" ) || val_rw.starts_with(">" )){ // case: "- |123",  "- >123",  "hash-key: |123"  or "hash-key: >123"
        ++i;
        std::string opt; opt += val_rw[0];
        if(val_rw.size()>=2){
            indent_width = std::stoi(&val_rw[1]);
        }else{
            indent_width = _head_space_count(ls[i]);
        }
        
        if(!_get_multi_line_str(val_rw, hsc_prev, opt, indent_width, ls, i)){ return false; }
        
    }

    return true;
}

bool _parse_yaml(std::vector<struct command>& ret_vCmd, const std::vector<std::string>& ls, const uint base_idx){
    
    for(uint i=0; i<ls.size(); ++i){
        std::string raw, s;
        raw = ls[i];
        s = _rm_comment(raw); // s = _rm_comment_quotes(s); に置き換える
        if(s.size()==0){ continue; }
        if(s=="..."){ return true; } // detect end marker
        uint type=sstd_yaml::num_null, format=sstd_yaml::num_block_style_base, type_cnt=0; if(!sstd_yaml::_data_type_and_format(type, format, type_cnt, s)){ return false; }
        uint hsc_lx=0;     _hsc_lx(hsc_lx, s);
        uint hsc_hx=0; if(!_hsc_hx(hsc_hx, s)){ sstd::pdbg_err("quate is not closed\n"); return false; }
        
        bool val1_use_quotes, val2_use_quotes;
        std::string val1, val2;
        if(!_get_value(val1_use_quotes, val2_use_quotes, val1, val2, s, type, format)){ return false; }
        //if      (format==sstd_yaml::num_block_style_base){ if(!_get_value(val1_use_quotes, val2_use_quotes, val1, val2, s, type)){ return false; }
        //}else if(format==sstd_yaml::num_flow_style_base ){ val1 = s;
        //}else                            { sstd::pdbg_err("Unexpected data type\n"); return false; }
        
        // for multiple line string
        if(!_check_val_and_overwrite_multi_line_str(val1, hsc_lx, ls, i)){ sstd::pdbg_err("reading multiline is failed.\n"); return false; } // for list (val1=="|0123" or val1=="|-0123" val1=="|+0123")
        if(!_check_val_and_overwrite_multi_line_str(val2, hsc_hx, ls, i)){ sstd::pdbg_err("reading multiline is failed.\n"); return false; } // for hash (val2=="|0123" or val2=="|-0123" val2=="|+0123")

        struct command c;
        switch(type){
        case sstd_yaml::num_str: {
            c.hsc_lx          = hsc_lx;
            c.hsc_hx          = hsc_hx;
            c.type            = sstd_yaml::num_str;
            c.format          = format;
            c.val1_use_quotes = val1_use_quotes;
            c.val2_use_quotes = val2_use_quotes;
            c.val1            = val1;
            //c.val2           = val2;
            c.lineNum         = base_idx + i; // debug info
            c.rawStr          = raw;          // debug info
            
            ret_vCmd.push_back(c);
        } break;
        case sstd_yaml::num_list: {
            for(uint ti=0; ti<type_cnt-1; ++ti){ // for multiple list. ex: "- - a".
                c.hsc_lx          = hsc_lx + 2*ti;
                c.hsc_hx          = hsc_hx + 2*ti;
                c.type            = sstd_yaml::num_list;
                c.format          = format;
                c.val1_use_quotes = false;
                c.val2_use_quotes = false;
                //c.val1           = val1;
                //c.val2           = val2;
                c.lineNum         = base_idx + i; // debug info
                c.rawStr          = raw;          // debug info
            
                ret_vCmd.push_back(c);
            }
            
            c.hsc_lx          = hsc_lx + 2*(type_cnt-1);
            c.hsc_hx          = hsc_hx + 2*(type_cnt-1);
            c.type            = sstd_yaml::num_list;
            c.format          = format;
            c.val1_use_quotes = val1_use_quotes;
            c.val2_use_quotes = val2_use_quotes;
            c.val1            = val1;
            //c.val2           = val2;
            c.lineNum         = base_idx + i; // debug info
            c.rawStr          = raw;          // debug info
            
            ret_vCmd.push_back(c);
        } break;
        case sstd_yaml::num_hash: {
            c.hsc_lx          = hsc_lx;
            c.hsc_hx          = hsc_hx;
            c.type            = sstd_yaml::num_hash;
            c.format          = format;
            c.val1_use_quotes = val1_use_quotes;
            c.val2_use_quotes = val2_use_quotes;
            c.val1            = val1; // key
            c.val2            = val2; // value
            c.lineNum         = base_idx + i; // debug info
            c.rawStr          = raw;          // debug info
            
            ret_vCmd.push_back(c);
        } break;
        case sstd_yaml::num_list_and_hash:{
            for(uint ti=0; ti<type_cnt-1; ++ti){ // for multiple list-hash. ex: "- - k1: v1".
                c.hsc_lx          = hsc_lx + 2*ti;
                c.hsc_hx          = hsc_hx + 2*ti;
                c.type            = sstd_yaml::num_list;
                c.format          = format;
                c.val1_use_quotes = false;
                c.val2_use_quotes = false;
                //c.val1           = "";
                //c.val2           = "";
                c.lineNum         = base_idx + i; // debug info
                c.rawStr          = raw;          // debug info
                
                ret_vCmd.push_back(c);
            }
            
            c.hsc_lx          = hsc_lx + 2*(type_cnt-1);
            c.hsc_hx          = hsc_hx + 2*(type_cnt-1);
            c.type            = sstd_yaml::num_list_and_hash;
            c.format          = format;
            c.val1_use_quotes = false;
            c.val2_use_quotes = false;
            //c.val1           = "";
            //c.val2           = "";
            c.lineNum         = base_idx + i; // debug info
            c.rawStr          = raw;          // debug info
            
            ret_vCmd.push_back(c);
            
            c.hsc_lx          = hsc_lx + 2*(type_cnt-1);
            c.hsc_hx          = hsc_hx + 2*(type_cnt-1);
            c.type            = sstd_yaml::num_hash;
            c.format          = format;
            c.val1_use_quotes = val1_use_quotes;
            c.val2_use_quotes = val2_use_quotes;
            c.val1            = val1; // key
            c.val2            = val2; // value
            c.lineNum         = base_idx + i; // debug info
            c.rawStr          = raw;          // debug info
            
            ret_vCmd.push_back(c);
        } break;
        default: { sstd::pdbg_err("Unexpected data type\n"); return false; } break;
        };
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
    if(i+3<v_cs.size() && v_cs[i+1][0]==':' && (v_cs[i+3][0]==',' || v_cs[i+3][0]=='}' || v_cs[i+3][0]==']')){
        // { "k1": "v1" } or { "k1": "v1", "k2": "v2" }
        // [ "k1": "v1" ] <- Abbreviated of "[{ "k1": "v1" }]"
        ret_value = v_cs[i+2];
        is_null = false;
        i += 2;
        return true; // get value
    }else if(i+2<v_cs.size() && v_cs[i+1][0]==':' && (v_cs[i+2][0]=='}' || v_cs[i+2][0]==']' || v_cs[i+2][0]==',')){
        // { "k1": } or { "k1":, "k2" }
        // [ "k1": "v1" ] <- Abbreviated of "[{ "k1": "v1" }]"
        is_null = true;
        i += 2;
        return true; // get null value
    }else if(i+1<v_cs.size() && (v_cs[i+1][0]=='}' || v_cs[i+1][0]==']' || v_cs[i+1][0]==',')){
        // { "k1" }, { "k1", "k2" }
        // [ "k1": "v1" ] <- Abbreviated of "[{ "k1": "v1" }]"
        is_null = true;
        i += 1;
        return true; // get null value
    }

    // not get a string value (have a value of object)
    // { "k1" { "k2": }}
    return false;
}
bool _flow_style_str_to_obj(sstd::terp::var& var_out, const std::string& s_in){
    sstd::printn(var_out.typeStr());
    sstd::printn(s_in);
    std::vector<std::string> v_cs; // vector of commands and string
    if(!sstd_yaml::_split_quotes_by_control_chars(v_cs, s_in.c_str(), s_in.size())){ sstd::pdbg_err("_split_quotes_by_control_chars() is failed. Un-cloused quate.\n"); return false; }
    sstd::printn(v_cs);
    
    std::vector<sstd::terp::var*> v_dst;
    v_dst.push_back( &var_out );
    
    for(uint i=0; i<v_cs.size(); ++i){
        //sstd::printn(var_out);
        //printf("\n\n");
        //sstd::printn(v_cs[i]);
        //sstd::printn(v_dst.size());
        if(v_dst.size()==0){ sstd::pdbg_err("broken pointer\n"); return false; }
        sstd::terp::var* pVar = v_dst[v_dst.size()-1];
        sstd::terp::var& var = *pVar;
        //if(v_hsc_lx.size()==0){ sstd::pdbg_err("v_hsc_lx is out of range\n"); return false; }
        //if(v_hsc_hx.size()==0){ sstd::pdbg_err("v_hsc_hx is out of range\n"); return false; }
        
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
            //sstd::printn(v_cs[i]);
            //sstd::printn(var.typeNum());
            switch(var.typeNum()){
//            case sstd::num_str: {
//                sstd::printn(v_cs[i+1]);
//                if(i+1<v_cs.size() && v_cs[i+1].size()==1 && v_cs[i+1][0]==':'){ // for [k: v] which is an abbreviated notation of [{k: v}]
//                  printf("in 640 ----------------\n");
//                    var.push_back( sstd::terp::hash() );
//                    v_dst.push_back( &(var[var.size()-1]) );
//                    continue;
//                }
//                sstd::printn(var.typeStr());
//                var.push_back(v_cs[i]);
//            } break;
            case sstd::num_vec_terp_var: {
                // list
                if(i+1<v_cs.size() && v_cs[i+1].size()==1 && v_cs[i+1][0]==':'){ // for [k: v] which is an abbreviated notation of [{k: v}]
                    printf("in 640 ----------------\n");
                    var.push_back( sstd::terp::hash() );
                    v_dst.push_back( &(var[var.size()-1]) );
                    --i; continue;
                }
                var.push_back(v_cs[i]);
            } break;
            case sstd::num_hash_terp_var: {
                printf("in 660 ----------------\n");
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
            default: { sstd::pdbg_err("Unexpected data type. Type: %s\n", sstd::typeNum2str(var.typeNum()).c_str()); sstd::printn(var); } break;
            }
        }
    }
    
    return true;
}/*
bool _assignment_value(sstd::terp::var& ret_yml, const std::stirng& s_in, const uint format){
    if(v_cmd[i].format==sstd_yaml::num_block_style_base){
    }else if(v_cmd[i].format==sstd_yaml::num_flow_style_base){
        printf("in 720\n");
        if(!_flow_style_str_to_obj(var, v_cmd[i].val1.c_str())){ sstd::pdbg_err("Converting flow style string to object is failed."); return false; }
    }else{
        sstd::pdbg_err("Unexpected data fromat.");
    }
    return;
}*/
bool _construct_var(sstd::terp::var& ret_yml, const std::vector<struct command>& v_cmd){
    std::vector<sstd::terp::var*> v_dst;
    std::vector<uint> v_hsc_lx; // v: vector, hsc: head space count, _lx: list-index.
    std::vector<uint> v_hsc_hx; // v: vector, hsc: head space count. _hx: hash-index.
    v_dst.push_back(&ret_yml);
    v_hsc_lx.push_back(0);
    v_hsc_hx.push_back(0);
    
    for(uint i=0; i<v_cmd.size(); ++i){
        printf("\n\n--- begin cmd ---\n"); // for debug
        _print(v_cmd[i]);                  // for debug
        if(v_dst.size()==0){ sstd::pdbg_err("broken pointer\n"); return false; }
        sstd::terp::var* pVar = v_dst[v_dst.size()-1];
        sstd::terp::var& var = *pVar;
        if(v_hsc_lx.size()==0){ sstd::pdbg_err("v_hsc_lx is out of range\n"); return false; }
        if(v_hsc_hx.size()==0){ sstd::pdbg_err("v_hsc_hx is out of range\n"); return false; }
        uint hsc_base_lx = v_hsc_lx[v_hsc_lx.size()-1];
        uint hsc_base_hx = v_hsc_hx[v_hsc_hx.size()-1];
        
        // check indent
        switch(var.typeNum()){
        case sstd::num_vec_terp_var: {
            // list
            if(v_cmd[i].hsc_lx > hsc_base_lx){
                v_hsc_lx.push_back(v_cmd[i].hsc_lx);
                --i;
                continue;
            }else if(v_cmd[i].hsc_lx < hsc_base_lx){
                v_dst.pop_back();
                v_hsc_lx.pop_back();
                --i;
                continue;
            }
        } break;
        case sstd::num_hash_terp_var: {
            // hash
            if(v_cmd[i].hsc_hx > hsc_base_hx){
                v_hsc_hx.push_back(v_cmd[i].hsc_hx);
                --i;
                continue;
            }else if(v_cmd[i].hsc_hx < hsc_base_hx){
                v_dst.pop_back();
                v_hsc_hx.pop_back();
                --i;
                continue;
            }else if(v_cmd[i].type==sstd_yaml::num_list_and_hash){
                v_dst.pop_back();
                v_hsc_hx.pop_back();
                --i;
                continue;
            }
        } break;
        case sstd::num_null: {} break;
        default: { sstd::pdbg_err("Unexpected data type\n"); } break;
        }

        // set dst type (if dst is sstd::num_null)
        if(var.typeNum()==sstd::num_null){
            switch(v_cmd[i].type){
            case sstd_yaml::num_str:           {                           } break;
            case sstd_yaml::num_list:          { var = sstd::terp::list(); } break;
            case sstd_yaml::num_list_and_hash: { var = sstd::terp::list(); } break;
            case sstd_yaml::num_hash:          { var = sstd::terp::hash(); } break;
//            case NUM_FORMAT:        { sstd::pdbg_err("in NUM_FORMAT\n");                          } break;
            default: { sstd::pdbg_err("Unexpected data type\n"); return false; } break;
            }
        }

        // set dst
        bool needs_to_set_dst_list = !(v_cmd[i].val1.size()>=1 || v_cmd[i].val1_use_quotes);
        if(v_cmd[i].type==sstd_yaml::num_list && needs_to_set_dst_list){
            var.push_back( sstd::terp::list() );
            v_dst.push_back( &(var[var.size()-1]) );
            if(v_cmd[i].format==sstd_yaml::num_block_style_base){ continue; }
        }
        bool needs_to_set_dst_hash = !(v_cmd[i].val2.size()>=1 || v_cmd[i].val2_use_quotes);
        if((v_cmd[i].format + v_cmd[i].type)==sstd_yaml::num_block_style_base + sstd_yaml::num_hash && needs_to_set_dst_hash){
            v_dst.push_back( &(var[v_cmd[i].val1.c_str()]) );
            if(v_cmd[i].format==sstd_yaml::num_block_style_base){ continue; }
        }

        // set value
        sstd::printn(var);
        sstd::printn(v_cmd[i].format);
        sstd::printn(v_cmd[i].type);
        switch(v_cmd[i].format + v_cmd[i].type){
        case sstd_yaml::num_block_style_base + sstd_yaml::num_str: {
            if(var.typeNum()!=sstd::num_null){ sstd::pdbg_err("OverWritting the existing data. (String data type can only take one data.)\n"); break; }
            var = v_cmd[i].val1.c_str();
        } break;
        case sstd_yaml::num_block_style_base + sstd_yaml::num_list: {
            var.push_back( v_cmd[i].val1.c_str() );
        } break;
        case sstd_yaml::num_block_style_base + sstd_yaml::num_list_and_hash: {
            var.push_back( sstd::terp::hash() );
            v_dst.push_back( &(var[var.size()-1]) );
        } break;
        case sstd_yaml::num_block_style_base + sstd_yaml::num_hash: {
            printf("in 737\n");
            var[ v_cmd[i].val1.c_str() ] = v_cmd[i].val2.c_str();
            //std::string tmp = v_cmd[i].val2.c_str();
            //if(!_flow_style_str_to_obj(var[ v_cmd[i].val1.c_str() ], tmp)){ sstd::pdbg_err("Converting flow style string to object is failed."); return false; }
        } break;
        case sstd_yaml::num_flow_style_base + sstd_yaml::num_str: {
            if(!_flow_style_str_to_obj(var, v_cmd[i].val1.c_str())){ sstd::pdbg_err("Converting flow style string to object is failed."); return false; }
        } break;
        case sstd_yaml::num_flow_style_base + sstd_yaml::num_list: {
            printf("in 744\n");
            sstd::terp::var var_tmp;
            if(!_flow_style_str_to_obj(var_tmp, v_cmd[i].val1.c_str())){ sstd::pdbg_err("Converting flow style string to object is failed."); return false; }
            var.push_back(std::move( var_tmp ));
        } break;
        case sstd_yaml::num_flow_style_base + sstd_yaml::num_list_and_hash: {
            printf("in 750\n");
            //              sstd::terp::var var_tmp;
            //              if(!_flow_style_str_to_obj(var, v_cmd[i].val1.c_str())){ sstd::pdbg_err("Converting flow style string to object is failed."); return false; }
            //              var[var.size()-1]
            std::string tmp = v_cmd[i].val2.c_str();
            if(!_flow_style_str_to_obj(var[ v_cmd[i].val1.c_str() ], tmp)){ sstd::pdbg_err("Converting flow style string to object is failed."); return false; }
        } break;
        case sstd_yaml::num_flow_style_base + sstd_yaml::num_hash: {
            printf("in 756\n");
            if(!_flow_style_str_to_obj(var, v_cmd[i].val1.c_str())){ sstd::pdbg_err("Converting flow style string to object is failed."); return false; }
        } break;
        default: { sstd::pdbg_err("ERROR\n"); } break;
        }
        
        //sstd::printn(var); // for debug
        //sstd::printn(ret_yml); // for debug
    }

    return true;
}

//---

bool sstd::yaml_load(sstd::terp::var& ret_yml, const char* s){
    bool tf = true;
    
    std::vector<std::string> ls; if(!sstd_yaml::_splitByLine_quotes_brackets(ls, s)){ sstd::pdbg_err("single or double quatation is not closed\n"); return false; } // v: vector, ls: line string
    //sstd::printn(ls);
    std::vector<struct command> v_cmd; if(!_parse_yaml(v_cmd, ls, 0)){ return false; }
    //_print(v_cmd);
    if(!_construct_var(ret_yml, v_cmd)){ return false; }
    
    return tf;
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
bool sstd::yaml_load_all(std::vector<sstd::terp::var>& ret_vYml, const        char* s){
    std::vector<std::string> ls; if(!sstd_yaml::_splitByLine_quotes_brackets(ls, s)){ sstd::pdbg_err("double quatation is not closed\n"); return false; } // v: vector, ls: line string
    std::vector<std::vector<std::string>> v_ls = _split_by_separator(ls);

    uint base_idx=0;
    for(uint i=0; i<v_ls.size(); ++i){
        sstd::terp::var ret_yml;
        std::vector<struct command> v_cmd; if(!_parse_yaml(v_cmd, v_ls[i], base_idx)){ return false; }
        if(!_construct_var(ret_yml, v_cmd)){ return false; }
        
        ret_vYml.push_back(std::move(ret_yml));
        base_idx += v_ls[i].size() + 1;
    }
    
    return true;
}
bool sstd::yaml_load_all(std::vector<sstd::terp::var>& ret_vYml, const std::string& s){ return sstd::yaml_load_all(ret_vYml, s.c_str()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool sstd::yaml_load(sstd::terp::var& ret_yml, sstd::file& fp){
    size_t size = fp.fsize();
    std::vector<char> raw(size+1, 0);
    if(fp.fread((uchar*)&raw[0], sizeof(char), size)!=size){
        sstd::pdbg_err("fread was failed.\n");
        return false;
    }
    //printf("&raw[0] = %s\n", &raw[0]);
    
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
    //printf("&raw[0] = %s\n", &raw[0]);
    
    if(!sstd::yaml_load_all(ret_vYml, (const char*)&raw[0])){ return false; }
    
    return true;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

