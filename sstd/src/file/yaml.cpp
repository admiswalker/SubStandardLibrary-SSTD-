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

#define NUM_NULL 255
#define NUM_STR  1
#define NUM_LIST 2
#define NUM_HASH 3
#define NUM_LIST_AND_HASH 4

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
    
    std::vector<std::string> v;// = sstd::split(s);
    if(!sstd::split_quotes(v, s)){ sstd::pdbg_err("quate is not closed\n"); return false; }
    //sstd::strip(v);
    sstd::printn(v);
    
    ret = v.size()>=1 && v[0].size()>=1 && v[0][v[0].size()-1]==':';
    
    return true;
}
bool _is_list(bool& ret, uint& cnt, const std::string& s){
    std::vector<std::string> v;
    if(!sstd::split_quotes(v, s, ' ')){ sstd::pdbg_err("quate is not closed\n"); return false; }
    
    for(uint i=0; i<v.size(); ++i){
        if(v[i].size()==1 && v[i]=="-"){ ++cnt; }
    }
    ret = ( cnt >= 1 );
    
    return true;
}
bool _is_flow(bool& ret, const std::string& s){ // for flow style notation
    ret = false;
    std::string ret_s;
    if(!sstd::extract_unquoted(ret_s, s)){ sstd::pdbg_err("quate is not closed\n"); return false; }
    for(uint i=0; i<ret_s.size(); ++i){
        if(ret_s[i]==' ' || ret_s[i]=='-' || ret_s[i]==' '){ continue; }
        
        if(ret_s[i]=='{' || ret_s[i]=='['){
            ret=true; return true;
        }else{
            return true;
        }
    }
    return true;
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
    char verb;
    bool val1_use_quotes;
    bool val2_use_quotes;
    std::string val1; // "list value" or "hash key"
    std::string val2; // "hash value" if Not required "sstd::terp::var"

    // debug info
    uint lineNum;
    std::string rawStr;
};
void _print(const struct command& cmd){ // for debug
    printf("hsc_lx: %d\n",  cmd.hsc_lx        );
    printf("hsc_hx: %d\n",  cmd.hsc_hx        );
    printf("verb: %c\n",    cmd.verb          );
    printf("val1_use_quotes: %s\n", (cmd.val1_use_quotes ? "true":"false") );
    printf("val2_use_quotes: %s\n", (cmd.val2_use_quotes ? "true":"false") );
    printf("val1: %s\n",    cmd.val1.c_str()  );
    printf("val2: %s\n",    cmd.val2.c_str()  );
    printf("lineNum: %d\n", cmd.lineNum       );
    printf("rawStr: %s\n",  cmd.rawStr.c_str());
    printf("\n");
}
void _print(const std::vector<struct command>& v_cmd){ // for debug
    for(uint i=0; i<v_cmd.size(); ++i){
        _print(v_cmd[i]);
    }
}

//---

bool _data_type(uint& type, uint& num, std::string s){
    bool is_h; if(!_is_hash(is_h,      s      )){ return false; }
    bool is_l; if(!_is_list(is_l, num, s      )){ return false; }
//    bool is_f; if(!_is_flow(is_f,      s, is_h)){ return false; }
    
    if(is_h && is_l){ type = NUM_LIST_AND_HASH; return true; }
    if(is_h){ type = NUM_HASH; return true; }
    if(is_l){ type = NUM_LIST; return true; }
    
    type = NUM_STR;
    return true;
}
std::vector<std::string> _get_verb(std::string s){
    std::vector<std::string> v;
    if(sstd::charIn('-', s)){ v.push_back("-"); }
    if(sstd::charIn(':', s)){ v.push_back(":"); }
    return v;
}
bool _get_value(bool& ret_val1_use_quotes, bool& ret_val2_use_quotes, std::string& ret_val1, std::string& ret_val2, std::string s, uint typeNum){
    ret_val1_use_quotes=false;
    ret_val2_use_quotes=false;
    ret_val1.clear();
    ret_val2.clear();
    bool dq, sq;
    
    switch(typeNum){
    case NUM_STR:  {
        ret_val1 = _extract_quotes_value(sstd::strip_quotes(sq, dq, s));
        ret_val1_use_quotes = ( dq || sq );
    } break;
    case NUM_LIST: {
        ret_val1 = _extract_quotes_value(sstd::strip_quotes(sq, dq, _rm_hyphen(s)));
        ret_val1_use_quotes = ( dq || sq );
    } break;
    case NUM_HASH:
    case NUM_LIST_AND_HASH: {
        std::vector<std::string> v; if(!sstd::split_quotes(v, s, ':')){ sstd::pdbg_err("single quatation or double quatation is not closed\n"); return false; }
        if(v.size()>=1){ ret_val1 = _extract_quotes_value(sstd::strip_quotes(sq, dq, _rm_hyphen(v[0]))); ret_val1_use_quotes = ( sq || dq ); }
        if(v.size()>=2){ ret_val2 = _extract_quotes_value(sstd::strip_quotes(sq, dq,            v[1] )); ret_val2_use_quotes = ( sq || dq ); }
        if(v.size()>=3){ sstd::pdbg("Unexptected split by ':'."); return false; }
    } break;
    default: { sstd::pdbg_err("Unexpected typeNum\n"); return false; } break;
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
        
        uint type=NUM_NULL, type_cnt=0; if(!_data_type(type, type_cnt, s)){ return false; }
        if(type==NUM_STR){
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
        uint type=NUM_NULL, type_cnt=0; if(!_data_type(type, type_cnt, s)){ return false; }
        uint hsc_lx=0;     _hsc_lx(hsc_lx, s);
        uint hsc_hx=0; if(!_hsc_hx(hsc_hx, s)){ sstd::pdbg_err("quate is not closed\n"); return false; }
        
        bool val1_use_quotes, val2_use_quotes;
        std::string val1, val2;
        if(!_get_value(val1_use_quotes, val2_use_quotes, val1, val2, s, type)){ return false; }

        // for multiple line string
        _check_val_and_overwrite_multi_line_str(val1, hsc_lx, ls, i); // for list (val1=="|0123" or val1=="|-0123" val1=="|+0123")
        _check_val_and_overwrite_multi_line_str(val2, hsc_hx, ls, i); // for hash (val2=="|0123" or val2=="|-0123" val2=="|+0123")

        struct command c;
        switch(type){
        case NUM_STR: {
            c.hsc_lx         = hsc_lx;
            c.hsc_hx         = hsc_hx;
            c.verb           = 's';
            c.val1_use_quotes = val1_use_quotes;
            c.val2_use_quotes = val2_use_quotes;
            c.val1           = val1;
            //c.val2           = val2;
            c.lineNum        = base_idx + i; // debug info
            c.rawStr         = raw;          // debug info
            
            ret_vCmd.push_back(c);
        } break;
        case NUM_LIST: {
            for(uint ti=0; ti<type_cnt-1; ++ti){ // for multiple list. ex: "- - a".
                c.hsc_lx         = hsc_lx + 2*ti;
                c.hsc_hx         = hsc_hx + 2*ti;
                c.verb           = '-';
                c.val1_use_quotes = false;
                c.val2_use_quotes = false;
                //c.val1           = val1;
                //c.val2           = val2;
                c.lineNum        = base_idx + i; // debug info
                c.rawStr         = raw;          // debug info
            
                ret_vCmd.push_back(c);
            }
            
            c.hsc_lx         = hsc_lx + 2*(type_cnt-1);
            c.hsc_hx         = hsc_hx + 2*(type_cnt-1);
            c.verb           = '-';
            c.val1_use_quotes = val1_use_quotes;
            c.val2_use_quotes = val2_use_quotes;
            c.val1           = val1;
            //c.val2           = val2;
            c.lineNum        = base_idx + i; // debug info
            c.rawStr         = raw;          // debug info
            
            ret_vCmd.push_back(c);
        } break;
        case NUM_HASH: {
            c.hsc_lx         = hsc_lx;
            c.hsc_hx         = hsc_hx;
            c.verb           = ':';
            c.val1_use_quotes = val1_use_quotes;
            c.val2_use_quotes = val2_use_quotes;
            c.val1           = val1; // key
            c.val2           = val2; // value
            c.lineNum        = base_idx + i; // debug info
            c.rawStr         = raw;          // debug info
            
            ret_vCmd.push_back(c);
        } break;
        case NUM_LIST_AND_HASH:{
            for(uint ti=0; ti<type_cnt-1; ++ti){ // for multiple list-hash. ex: "- - k1: v1".
                c.hsc_lx         = hsc_lx + 2*ti;
                c.hsc_hx         = hsc_hx + 2*ti;
                c.verb           = '-'; // x: list x(and) hash: 
                c.val1_use_quotes = false;
                c.val2_use_quotes = false;
                //c.val1           = "";
                //c.val2           = "";
                c.lineNum        = base_idx + i; // debug info
                c.rawStr         = raw;          // debug info
                
                ret_vCmd.push_back(c);
            }
            
            c.hsc_lx         = hsc_lx + 2*(type_cnt-1);
            c.hsc_hx         = hsc_hx + 2*(type_cnt-1);
            c.verb           = 'x'; // x: list x(and) hash: 
            c.val1_use_quotes = false;
            c.val2_use_quotes = false;
            //c.val1           = "";
            //c.val2           = "";
            c.lineNum        = base_idx + i; // debug info
            c.rawStr         = raw;          // debug info
            
            ret_vCmd.push_back(c);
            
            c.hsc_lx         = hsc_lx + 2*(type_cnt-1);
            c.hsc_hx         = hsc_hx + 2*(type_cnt-1);
            c.verb           = ':';
            c.val1_use_quotes = val1_use_quotes;
            c.val2_use_quotes = val2_use_quotes;
            c.val1           = val1; // key
            c.val2           = val2; // value
            c.lineNum        = base_idx + i; // debug info
            c.rawStr         = raw;          // debug info
            
            ret_vCmd.push_back(c);
        } break;
        default: { sstd::pdbg_err("Unexpected data type\n"); return false; } break;
        };
    }
    
    return true;
}
bool _construct_var(sstd::terp::var& ret_yml, const std::vector<struct command>& v_cmd){
    std::vector<sstd::void_ptr*> v_dst;
    std::vector<uint> v_hsc_lx; // v: vector, hsc: head space count, _lx: list-index.
    std::vector<uint> v_hsc_hx; // v: vector, hsc: head space count. _hx: hash-index.
    v_dst.push_back(ret_yml.p());
    v_hsc_lx.push_back(0);
    v_hsc_hx.push_back(0);
    
    for(uint i=0; i<v_cmd.size(); ++i){
        //printf("\n\n--- begin cmd ---\n"); // for debug
        //_print(v_cmd[i]);                  // for debug
        if(v_dst.size()==0){ sstd::pdbg_err("broken pointer\n"); return false; }
        sstd::terp::var var = sstd::terp::var( v_dst[v_dst.size()-1] );
        if(v_hsc_lx.size()==0){ sstd::pdbg_err("v_hsc_lx is out of range\n"); return false; }
        if(v_hsc_hx.size()==0){ sstd::pdbg_err("v_hsc_hx is out of range\n"); return false; }
        uint hsc_base_lx = v_hsc_lx[v_hsc_lx.size()-1];
        uint hsc_base_hx = v_hsc_hx[v_hsc_hx.size()-1];
        
        // set dst type (if dst is sstd::num_null)
        if(var.typeNum()==sstd::num_null){
            switch(v_cmd[i].verb){
            case 's': {                           } break;
            case '-': { var = sstd::terp::list(); } break;
            case 'x': { var = sstd::terp::list(); } break;
            case ':': { var = sstd::terp::hash(); } break;
            default: { sstd::pdbg_err("Unexpected data type\n"); return false; } break;
            }
        }

        // check indent
        switch(var.typeNum()){
        case sstd::num_vec_void_ptr: {
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
        case sstd::num_hash_str_void_ptr: {
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
            }else if(v_cmd[i].verb=='x'){
                v_dst.pop_back();
                v_hsc_hx.pop_back();
                --i;
                continue;
            }
        } break;
        case sstd::num_null: {} break;
        default: { sstd::pdbg_err("Unexpected data type\n"); } break;
        }

        // set dst and value
        switch(v_cmd[i].verb){
        case 's': { // 's': string
            if(var.typeNum()!=sstd::num_null){ sstd::pdbg_err("OverWritting the existing data. (String data type can only take one data.)\n"); break; }
            var = v_cmd[i].val1.c_str();
        } break;
        case '-': { // '-': list
            if(v_cmd[i].val1.size()>=1 || v_cmd[i].val1_use_quotes){ // 'val1_use_quotes' is required to detect 0 length string
                var.push_back( v_cmd[i].val1.c_str() );
            }else{
                var.push_back( sstd::terp::list() );
                v_dst.push_back( var[var.size()-1].p() );
            }
        } break;
        case 'x': { // 'x': list-and-hash
            var.push_back( sstd::terp::hash() );
            v_dst.push_back( var[var.size()-1].p() );
        } break;
        case ':': { // ':': hash
            if(v_cmd[i].val2.size()>=1 || v_cmd[i].val2_use_quotes){ // 'val2_use_quotes' is required to detect 0 length string
                var[ v_cmd[i].val1.c_str() ] = v_cmd[i].val2.c_str();
            }else{
                v_dst.push_back( var[v_cmd[i].val1.c_str()].p() );
            }
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
    
    std::vector<std::string> ls; if(! sstd::splitByLine_quotes(ls, s)){ sstd::pdbg_err("single or double quatation is not closed\n"); return false; } // v: vector, ls: line string
    sstd::printn(ls);
    std::vector<struct command> v_cmd; if(!_parse_yaml(v_cmd, ls, 0)){ return false; }
    _print(v_cmd);
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
    std::vector<std::string> ls; if(!sstd::splitByLine_quotes(ls, s)){ sstd::pdbg_err("double quatation is not closed\n"); return false; } // v: vector, ls: line string
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

