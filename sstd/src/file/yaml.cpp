#include <cassert>
#include <string>
#include <vector>

#include "yaml.hpp"

#include "../definitions/typeDef.h"
#include "../string/strEdit.hpp"
#include "../string/strmatch.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define NUM_NULL 255
#define NUM_STR  1
#define NUM_LIST 2
#define NUM_HASH 3
#define NUM_LIST_AND_HASH 4

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

bool _is_hash(const std::string& s){
    if(sstd::charIn(':', s)){ return true; }
    
    return false;
}
bool _is_list(const std::string& s){
    for(uint i=0; i<s.size(); ++i){
        if      (s[i]==' '){ continue;
        }else if(s[i]=='-'){ return true;
        }else              { return false; }
    }
    return false;
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
uint _hsc_hx(const std::string& s){
    if(_is_hash(s)){ return _head_space_or_hyphen_count(s);
    }     else     { return _head_space_count(s);
    }
}
uint _hsc_lx(const std::string& s){
    return _head_space_count(s);
}

//---

struct command{
    uint hsc_lx; // hsc: head space count, _lx: list-index.
    uint hsc_hx; // hsc: head space count, _hx: hash-index.
    char verb;
    std::string val1; // "list value" or "hash key"
    std::string val2; // "hash value" if Not required "sstd::terp::var"

    // debug info
    uint lineNum;
    std::string rawStr;
};
void _print(const struct command& cmd){
    printf("hsc_lx: %d\n",  cmd.hsc_lx   );
    printf("hsc_hx: %d\n",  cmd.hsc_hx   );
    printf("verb: %c\n", cmd.verb        );
    printf("val1: %s\n", cmd.val1.c_str());
    printf("val2: %s\n", cmd.val2.c_str());
    printf("lineNum: %d\n", cmd.lineNum);
    printf("rawStr: %s\n", cmd.rawStr.c_str());
    printf("\n");
}
void _print(const std::vector<struct command>& v_cmd){
    for(uint i=0; i<v_cmd.size(); ++i){
        _print(v_cmd[i]);
    }
}

//---

uint _data_type(std::string s){
    bool is_l = _is_list(s);
    bool is_h = _is_hash(s);

    if(is_l && is_h){ return NUM_LIST_AND_HASH; }
    if(is_l){ return NUM_LIST; }
    if(is_h){ return NUM_HASH; }
    
    return NUM_STR;
}
std::vector<std::string> _get_verb(std::string s){
    std::vector<std::string> v;
    if(sstd::charIn('-', s)){ v.push_back("-"); }
    if(sstd::charIn(':', s)){ v.push_back(":"); }
    return v;
}
void _get_value(std::string& ret_val1, std::string& ret_val2, std::string s, uint typeNum){
    ret_val1.clear();
    ret_val2.clear();
    
    switch(typeNum){
    case NUM_STR:  {
        ret_val1 = sstd::strip(s);
    } break;
    case NUM_LIST: {
        ret_val1 = sstd::strip(_rm_hyphen(s));
    } break;
    case NUM_HASH:
    case NUM_LIST_AND_HASH: {
        std::vector<std::string> v = sstd::split(s, ':');
        if(v.size()>=1){ ret_val1 = sstd::strip(_rm_hyphen(v[0])); }
        if(v.size()>=2){ ret_val2 = sstd::strip(           v[1] ); }
    } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }
}

void _rremove_empty_ow(std::vector<std::string>& v){ // remove tail empty elements
    for(int i=v.size()-1; i>=0; --i){
        if(v[i].size()!=0){ break; }
        v.pop_back();
    }
}
uint _rcount_empty(std::vector<std::string>& v){
    uint cnt=0;
    for(int i=v.size()-1; i>=0; --i){
        if(v[i].size()!=0){ break; }
        ++cnt;
    }
    return cnt;
}
std::string _join(const std::vector<std::string>& v, const char separator){
    std::string ret;
    for(uint i=0; i<v.size()-1; ++i){
        ret += v[i] + separator;
    }
    if(v.size()>=1){
        ret += v[v.size()-1];
    }
    return ret;
}
std::string _get_multi_line_str(const uint hsc_prev, const std::string& opt, int indent_width, const std::vector<std::string>& ls, uint& i){
    std::string ret;
    std::vector<std::string> v_tmp;

    char separator='\n';
    //if(sstd::charIn('|', opt)){ separator = '\n'; }
    if(sstd::charIn('>', opt)){ separator =  ' '; }
//    if(indent_width == hsc_prev){ separator = '\n'; }
 
    for(; i<ls.size(); ++i){
        std::string s;
        s = ls[i];
        s = _rm_comment(s);
        if(s=="..."){ --i; return ret; } // detect end marker
        
        uint type = _data_type(s);
        if(type==NUM_STR){
            if(indent_width>=0 && s.size()>0){
                uint hsc = _head_space_count(s);
                
                if(hsc+1 <= (hsc_prev + indent_width)){ sstd::pdbg_err("indent indecation is too large.\n"); }

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
        _rremove_empty_ow(v_tmp);
        ret = _join(v_tmp, separator);
        ret += "\n";
    }else if(opt=="|-" || opt==">-"){
        _rremove_empty_ow(v_tmp);
        ret = _join(v_tmp, separator);
    }else if(opt=="|+" || opt==">+"){
        uint cnt = _rcount_empty(v_tmp) + 1;
        _rremove_empty_ow(v_tmp);
        ret = _join(v_tmp, separator) + std::string(cnt, '\n');
    }else{
        sstd::pdbg_err("Unexpected case\n");
    }

    return ret;
}
void _check_val_and_overwrite_multi_line_str(const uint hsc_prev, std::string& val_rw, const std::vector<std::string>& ls, uint& i){
    int indent_width = -1;

    if      (val_rw.starts_with("|-") || val_rw.starts_with(">-") ||    // case: "- |-123", "- >-123", "hash-key: |-123" or "hash-key: >-123"
             val_rw.starts_with("|+") || val_rw.starts_with(">+")    ){ // case: "- |+123", "- >+123", "hash-key: |+123" or "hash-key: >+123"
        ++i;
        std::string opt; opt += val_rw[0]; opt += val_rw[1];
        if(val_rw.size()>=3){
            indent_width = std::stoi(&val_rw[2]);
        }
        val_rw = _get_multi_line_str(hsc_prev, opt, indent_width, ls, i);
    }else if(val_rw.starts_with("|" ) || val_rw.starts_with(">" )){ // case: "- |123",  "- >123",  "hash-key: |123"  or "hash-key: >123"
        ++i;
        std::string opt; opt += val_rw[0];
        if(val_rw.size()>=2){
            indent_width = std::stoi(&val_rw[1]);
        }
        val_rw = _get_multi_line_str(hsc_prev, opt, indent_width, ls, i);
    }
}

std::vector<struct command> _parse_yaml(const std::vector<std::string>& ls){
    std::vector<struct command> v_cmd;

    for(uint i=0; i<ls.size(); ++i){
        std::string s;
        s = ls[i];
        s = _rm_comment(s);
        if(s.size()==0){ continue; }
        if(s=="..."){ return v_cmd; } // detect end marker
        uint type = _data_type(s);
        uint hsc_lx = _hsc_lx(s);
        uint hsc_hx = _hsc_hx(s);
        std::string val1, val2; _get_value(val1, val2, s, type);

        // for multiple line string
        _check_val_and_overwrite_multi_line_str(hsc_lx, val1, ls, i); // for list (val1=="|0123" or val1=="|-0123" val1=="|+0123")
        _check_val_and_overwrite_multi_line_str(hsc_hx, val2, ls, i); // for hash (val2=="|0123" or val2=="|-0123" val2=="|+0123")

        struct command c;
        switch(type){
        case NUM_STR: {
            c.hsc_lx  = hsc_lx;
            c.hsc_hx  = hsc_hx;
            c.verb    = 's';
            c.val1    = val1;
            //c.val2    = val2;
            c.lineNum = i;     // debug info
            c.rawStr  = ls[i]; // debug info
            
            v_cmd.push_back(c);
        } break;
        case NUM_LIST: {
            c.hsc_lx  = hsc_lx;
            c.hsc_hx  = hsc_hx;
            c.verb    = '-';
            c.val1    = val1;
            //c.val2    = val2;
            c.lineNum = i;     // debug info
            c.rawStr  = ls[i]; // debug info
            
            v_cmd.push_back(c);
        } break;
        case NUM_HASH: {
            c.hsc_lx  = hsc_lx;
            c.hsc_hx  = hsc_hx;
            c.verb    = ':';
            c.val1    = val1; // key
            c.val2    = val2; // value
            c.lineNum = i;     // debug info
            c.rawStr  = ls[i]; // debug info
            
            v_cmd.push_back(c);
        } break;
        case NUM_LIST_AND_HASH:{
            c.hsc_lx  = hsc_lx;
            c.hsc_hx  = hsc_hx;
            c.verb    = 'x'; // x: list x(and) hash: 
            c.val1    = "";
            c.val2    = "";
            c.lineNum = i;     // debug info
            c.rawStr  = ls[i]; // debug info
            
            v_cmd.push_back(c);
            
            c.hsc_lx  = hsc_lx;
            c.hsc_hx  = hsc_hx;
            c.verb    = ':';
            c.val1    = val1; // key
            c.val2    = val2; // value
            c.lineNum = i;     // debug info
            c.rawStr  = ls[i]; // debug info
            
            v_cmd.push_back(c);
        } break;
        default: { sstd::pdbg_err("ERROR\n"); } break;
        };
    }
    
    return v_cmd;
}
sstd::terp::var _construct_var(const std::vector<struct command>& v_cmd){
    sstd::terp::var ret;
    std::vector<sstd::void_ptr*> v_dst;
    std::vector<uint> v_hsc_lx; // v: vector, hsc: head space count, _lx: list-index.
    std::vector<uint> v_hsc_hx; // v: vector, hsc: head space count. _hx: hash-index.
    v_dst.push_back(ret.p());
    v_hsc_lx.push_back(0);
    v_hsc_hx.push_back(0);
    
    for(uint i=0; i<v_cmd.size(); ++i){
        //_print(v_cmd[i]);
        sstd::terp::var var = sstd::terp::var( v_dst[v_dst.size()-1] );
        uint hsc_base_lx = v_hsc_lx[v_hsc_lx.size()-1];
        uint hsc_base_hx = v_hsc_hx[v_hsc_hx.size()-1];
        //sstd::printn(v_dst);
        //sstd::printn(v_hsc_lx);
        //sstd::printn(v_hsc_hx);
        //sstd::printn(ret);
        //printf("\n");
        
        // set dst type (if dst is sstd::num_null)
        if(var.typeNum()==sstd::num_null){
            switch(v_cmd[i].verb){
            case 's': {                           } break;
            case '-': { var = sstd::terp::list(); } break;
            case 'x': {                           } break;
            case ':': { var = sstd::terp::hash(); } break;
            default: { sstd::pdbg_err("Unexpected data type\n"); } break;
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
            if(v_cmd[i].val1.size()!=0){
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
            if(v_cmd[i].val2.size()!=0){
                var[ v_cmd[i].val1.c_str() ] = v_cmd[i].val2.c_str();
            }else{
                v_dst.push_back( var[v_cmd[i].val1.c_str()].p() );
            }
        } break;
        default: { sstd::pdbg_err("ERROR\n"); } break;
        }
    }

    return ret;
}

//---

sstd::terp::var sstd::yaml_from_str(const        char* s){
    std::vector<std::string> ls = sstd::splitByLine(s); // ls: line string
    std::vector<struct command> v_cmd = _parse_yaml(ls);
    //_print(v_cmd);
    //sstd::terp::var ret;
    sstd::terp::var ret = _construct_var(v_cmd);
    
    return ret;
}
sstd::terp::var sstd::yaml_from_str(const std::string& s){ return sstd::yaml_from_str(s.c_str()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
