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
// dq and sq functions

// - dq: double quotation
// - sq: single quatation

// ここの関数は，あとで各々の sstd namespace のファイルに移す

//---

std::string sstd::_join(const std::vector<std::string>& v, const std::string& delimiter){
    std::string ret;

    if(v.size()>=1){
        ret += v[0];
    }
    for(uint i=1; i<v.size(); ++i){
        ret += delimiter + v[i];
    }
    return ret;
}

//---

void sstd::_strip_ow(std::vector<std::string>& v){
    for(uint i=0; i<v.size(); ++i){
        sstd::strip_ow(v[i]);
    }
}

//---

std::string _mearge_vec_by_space_or_newLines(const std::vector<std::string>& v){
    sstd::printn(v);
    std::string ret;

    std::vector<std::string> v_delmiter;

    uint cnt=0;
    for(uint i=0; i<v.size(); ++i){
        if(v[i].size()==(uint)0){
            ++cnt;
            continue;
        }
        sstd::printn(cnt);
        
        if(cnt!=0){
            std::string tmp;
            for(uint i_t=0; i_t<cnt; ++i_t){ tmp += "\\n"; }
            v_delmiter.push_back(tmp);
        }
        cnt=0;
    }
    sstd::printn(v_delmiter);
    
    bool is_prev_empty=false;
    uint i_vd=0;
    uint i=0;
    for(; i<v.size(); ++i){
        if(v[i].size()==(uint)0){ is_prev_empty=true; continue; }
        
        if(is_prev_empty){
            if(i_vd>=v_delmiter.size()){ sstd::pdbg_err("i_vd out the range of v_delmiter size.\n"); return ret; }
            ret += v_delmiter[i_vd]; ++i_vd;
        }else if(i!=0){
            ret += " ";
        }
        
        ret += v[i];
        is_prev_empty=false;
    }
//    if(v[v.size()-1].size()!=0){
//        ret += " " + v[ v.size()-1 ];
//    }
    
    //v_tmp.clean();
    
    /*
    std::string delimiter;
    for(int i=0; i<(int)v.size()-1; ++i){
        bool is_delimiter_inserted=false;
        
        if(v[i].size()==0 || v[i]=="\\"){
            delimiter += "\\n";
            continue;
        }else{
            delimiter += " ";
        }
        
        ret += delimiter;
        ret += v[i];
        
        delimiter.clear();
    }
    ret += v[v.size()-1];
    */
    return ret;
}

//---

std::string sstd::_strip_dq_sq(const        char* str){
    return std::move(sstd::_strip_dq_sq(std::string(str)));
}
std::string sstd::_strip_dq_sq(const std::string& str){
//    bool dq_sq_is_used = false;
    
    // remove head and tail ' ' and '\t'
    int li=0, ri=((int)str.size())-1;
    while(li<(int)str.size()){
        if(str[li]!=' ' && str[li]!='\t'){ break; } // remove head ' ' and '\t'
        ++li;
    }
    while(ri>=li){
        sstd::printn(ri);
        sstd::printn(str[ri]);
        if(str[ri]!=' ' && str[ri]!='\t'){ break; } // remove tail ' ' and '\t'
        --ri;
    }
        sstd::printn(li);
        sstd::printn(ri);
    sstd::printn(str.substr(li, ri-li+1));
    
    // remove head and tail '"' or '\''
    std::string tmp;
    {
        if((ri+1 - li)<= 0){ return std::string(); }
        
        char c_head = str[li];
        char c_tail = str[ri];
        
        // rm '"'
        if(c_head=='"' && c_tail=='"'){
//            dq_sq_is_used = true;
            printf("in dq \n");
            ++li;
            --ri;
        }
        
        // rm '\''
        if(c_head=='\'' && c_tail=='\''){
//            dq_sq_is_used = true;
            printf("in sq \n");
            ++li;
            --ri;
        }
        
        tmp = str.substr(li, ri-li+1);
    }
    sstd::printn(tmp);
    
    std::string ret;
    
    bool escape = false;
    uint new_line_cnt=0;
    for(uint i=0; i<tmp.size(); ++i){
        if(tmp[i]=='\\'){
            escape=true;
            continue;
        }
        if(escape){
            switch(tmp[i]){
            case '"': { ret += '\\'; } break;
            default: break;
            }
        }
        
        if(tmp[i]=='\n'){ ++new_line_cnt; continue; }
        
        if(new_line_cnt==1){
            if(!escape){
                ret += " ";
            }
        }else if(new_line_cnt>=2){
            for(uint i_t=0; i_t<new_line_cnt-1; ++i_t){ ret += "\\n"; }
        }
        
        while(new_line_cnt!=0 && tmp[i]==' ' && i<tmp.size()){ ++i; } // remove head ' '
        if(i>=tmp.size()){ break; }
        
        ret += tmp[i];
        
        new_line_cnt=0;
        escape = false;
    }
    
//    std::vector<std::string> vTmp = sstd::splitByLine(tmp);
//    for(uint i=0; i<vTmp.size(); ++i){
//        vTmp[i];
//    }
    
//    if(dq_sq_is_used){
//        std::vector<std::string> vTmp = sstd::splitByLine(tmp);
//        sstd::_strip_ow(vTmp);
//        tmp = sstd::_join(vTmp, "\n");
//        sstd::printn(tmp);
//    }

    
//    std::string ret = _mearge_vec_by_space_or_newLines(vTmp);
    
    /*
    std::string ret;

    // decode escape sequence
//    for(int i=li; i<=ri; ++i){
    for(uint i=0; i<tmp.size(); ++i){
        if(tmp[i]=='\\'){
            //++i; if(i>ri){ sstd::pdbg_err("decode escape sequence is failed.\n"); break; }
            ++i; if(i>=tmp.size()){ sstd::pdbg_err("decode escape sequence is failed.\n"); break; }
            
            switch(tmp[i]){
            case 'n' : { ret += '\n'; } break; // new line
            case 't' : { ret += '\t'; } break; // tab
            case 'b' : { ret += '\b'; } break; // back space
            case '"' : { ret += '\"'; } break; // double quate
            case '?' : { ret += '\?'; } break; // question mark
            case 'r' : { ret += '\r'; } break; // return
            case 'a' : { ret += '\a'; } break; // bell (alert)
            case '\\': { ret += '\\'; } break; // back slash
            case '\'': { ret += '\''; } break; // single quate
//            case ' ': {} break;
            default: break;
            }
        }else if(tmp[i]=='\n'){
            ret += ' ';
        }else{
            ret += tmp[i];
        }
    }
    */
    return ret;
}

//-----------------------------

std::vector<std::string> sstd::_splitByLine_dq_sq(const char* str){
    
    std::vector<std::string> ret;
    
    bool is_escaped=false;
    bool in_d_quate=false; // double quate
    bool in_s_quate=false; // single quate
    std::string buf;
    for(uint r=0; str[r]!=0;){ // r: read place
        buf.clear();
        for(; str[r]!='\0'; ++r){
            if(str[r]=='\\'){ is_escaped=true; buf+=str[r]; ++r; if(str[r]=='\0'){break;} }
            
            if(!is_escaped && !in_s_quate && str[r]=='"' ){ in_d_quate = !in_d_quate; }
            if(!is_escaped && !in_d_quate && str[r]=='\''){ in_s_quate = !in_s_quate; }
            
            if(!in_d_quate && !in_s_quate && str[r]==0x0A                  ){ r+=1; break; } // Uinx
            if(!in_d_quate && !in_s_quate && str[r]==0x0D && str[r+1]==0x0A){ r+=2; break; } // Windows
            buf += str[r];
            
            is_escaped=false;
        }
        ret.push_back(std::move(buf));
    }
    if(in_d_quate){ sstd::pdbg_err("double quatation is not closed\n"); return std::vector<std::string>(); }
    if(in_s_quate){ sstd::pdbg_err("single quatation is not closed\n"); return std::vector<std::string>(); }
    
    return ret;
}
std::vector<std::string> sstd::_splitByLine_dq_sq(const std::string& str){
    return sstd::_splitByLine_dq_sq(str.c_str());
}

//-------------------------------

std::vector<std::string> sstd::_split_dq_sq(const char* str, const char X){
    
    std::vector<std::string> ret;
    
    bool is_escaped=false;
    bool in_d_quate=false; // double quate
    bool in_s_quate=false; // single quate
    std::string buf;
    for(uint r=0; str[r]!='\0';){ // r: read place
        buf.clear();
        for(; str[r]!='\0'; ++r){
            if(str[r]=='\\'){ is_escaped=true; buf+=str[r]; ++r; if(str[r]=='\0'){break;} }
            
            if(!is_escaped && !in_s_quate && str[r]=='"' ){ in_d_quate = !in_d_quate; }
            if(!is_escaped && !in_d_quate && str[r]=='\''){ in_s_quate = !in_s_quate; }
            
            if(!in_d_quate && !in_s_quate && str[r]==X){ ++r; break; }
            buf += str[r];
            
            is_escaped=false;
        }
        ret.push_back(std::move(buf));
    }
    if(in_d_quate){ sstd::pdbg_err("double quatation is not closed\n"); return std::vector<std::string>(); }
    if(in_s_quate){ sstd::pdbg_err("single quatation is not closed\n"); return std::vector<std::string>(); }
    
    return ret;
}
std::vector<std::string> sstd::_split_dq_sq(const std::string& str, const char X){
    return std::move(sstd::_split_dq_sq(str.c_str(), X));
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

std::string _rm_bw_dq_sq(const std::string& str){ // _bw: between, _dq: double quotation, _sq: single quatation
    std::string ret;
    
    bool is_escaped=false;
    bool in_d_quate=false; // double quate
    bool in_s_quate=false; // single quate
    for(uint r=0; str[r]!='\0'; ++r){ // r: read place
        if(str[r]=='\\'){ is_escaped=true; ++r; if(str[r]=='\0'){break;} continue; }
        
        if(!is_escaped && !in_s_quate && str[r]=='"' ){ in_d_quate = !in_d_quate; }
        if(!is_escaped && !in_d_quate && str[r]=='\''){ in_s_quate = !in_s_quate; }
        is_escaped=false;

        if(in_s_quate || in_d_quate){ continue; }
        ret += str[r];
    }
    if(in_d_quate){ sstd::pdbg_err("double quatation is not closed\n"); return std::string(); }
    if(in_s_quate){ sstd::pdbg_err("single quatation is not closed\n"); return std::string(); }

    return ret;
}

bool _is_hash(const std::string& s){
    return sstd::charIn(':', _rm_bw_dq_sq(s));
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
bool _get_value(std::string& ret_val1, std::string& ret_val2, std::string s, uint typeNum){
    ret_val1.clear();
    ret_val2.clear();

    switch(typeNum){
    case NUM_STR:  {
        ret_val1 = sstd::_strip_dq_sq(s);
    } break;
    case NUM_LIST: {
        ret_val1 = sstd::_strip_dq_sq(_rm_hyphen(s));
    } break;
    case NUM_HASH:
    case NUM_LIST_AND_HASH: {
        std::vector<std::string> v = sstd::_split_dq_sq(s, ':');
        if(v.size()>=1){ ret_val1 = sstd::_strip_dq_sq(_rm_hyphen(v[0])); }
        if(v.size()>=2){ ret_val2 = sstd::_strip_dq_sq(           v[1] ); }
        if(v.size()>=3){ sstd::printn(v); sstd::pdbg("Unexptected split by ':'."); return false; }
    } break;
    default: { sstd::pdbg_err("Unexpected typeNum\n"); return false; } break;
    }

    return true;
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
bool _get_multi_line_str(std::string& ret, const uint hsc_prev, const std::string& opt, int indent_width, const std::vector<std::string>& ls, uint& i){
    std::vector<std::string> v_tmp;

    char separator='\n';
    //if(sstd::charIn('|', opt)){ separator = '\n'; }
    if(sstd::charIn('>', opt)){ separator =  ' '; }
//    if(indent_width == hsc_prev){ separator = '\n'; }
 
    for(; i<ls.size(); ++i){
        std::string s;
        s = ls[i];
        s = _rm_comment(s); // s = _rm_comment_dq_sq(s); に置き換える
        if(s=="..."){ --i; return true; } // detect end marker
        
        uint type = _data_type(s);
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
        sstd::pdbg_err("Unexpected case\n"); return false;
    }

    return true;
}
bool _check_val_and_overwrite_multi_line_str(const uint hsc_prev, std::string& val_rw, const std::vector<std::string>& ls, uint& i){
    int indent_width = -1;

    if      (val_rw.starts_with("|-") || val_rw.starts_with(">-") ||    // case: "- |-123", "- >-123", "hash-key: |-123" or "hash-key: >-123"
             val_rw.starts_with("|+") || val_rw.starts_with(">+")    ){ // case: "- |+123", "- >+123", "hash-key: |+123" or "hash-key: >+123"
        ++i;
        std::string opt; opt += val_rw[0]; opt += val_rw[1];
        if(val_rw.size()>=3){
            indent_width = std::stoi(&val_rw[2]);
        }
        
        if(!_get_multi_line_str(val_rw, hsc_prev, opt, indent_width, ls, i)){ return false; }
        
    }else if(val_rw.starts_with("|" ) || val_rw.starts_with(">" )){ // case: "- |123",  "- >123",  "hash-key: |123"  or "hash-key: >123"
        ++i;
        std::string opt; opt += val_rw[0];
        if(val_rw.size()>=2){
            indent_width = std::stoi(&val_rw[1]);
        }
        
        if(!_get_multi_line_str(val_rw, hsc_prev, opt, indent_width, ls, i)){ return false; }
    }

    return true;
}

bool _parse_yaml(std::vector<struct command>& ret_vCmd, const std::vector<std::string>& ls, const uint base_idx){
    
    for(uint i=0; i<ls.size(); ++i){
        std::string s;
        s = ls[i];
        s = _rm_comment(s); // s = _rm_comment_dq_sq(s); に置き換える
        if(s.size()==0){ continue; }
        if(s=="..."){ return true; } // detect end marker
        uint type = _data_type(s);
        uint hsc_lx = _hsc_lx(s);
        uint hsc_hx = _hsc_hx(s);
        sstd::printn(s);
        std::string val1, val2; if(!_get_value(val1, val2, s, type)){ return false; }

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
            c.lineNum = base_idx + i; // debug info
            c.rawStr  = ls[i];        // debug info
            
            ret_vCmd.push_back(c);
        } break;
        case NUM_LIST: {
            c.hsc_lx  = hsc_lx;
            c.hsc_hx  = hsc_hx;
            c.verb    = '-';
            c.val1    = val1;
            //c.val2    = val2;
            c.lineNum = base_idx + i; // debug info
            c.rawStr  = ls[i];        // debug info
            
            ret_vCmd.push_back(c);
        } break;
        case NUM_HASH: {
            c.hsc_lx  = hsc_lx;
            c.hsc_hx  = hsc_hx;
            c.verb    = ':';
            c.val1    = val1; // key
            c.val2    = val2; // value
            c.lineNum = base_idx + i; // debug info
            c.rawStr  = ls[i];        // debug info
            
            ret_vCmd.push_back(c);
        } break;
        case NUM_LIST_AND_HASH:{
            c.hsc_lx  = hsc_lx;
            c.hsc_hx  = hsc_hx;
            c.verb    = 'x'; // x: list x(and) hash: 
            c.val1    = "";
            c.val2    = "";
            c.lineNum = base_idx + i; // debug info
            c.rawStr  = ls[i];        // debug info
            
            ret_vCmd.push_back(c);
            
            c.hsc_lx  = hsc_lx;
            c.hsc_hx  = hsc_hx;
            c.verb    = ':';
            c.val1    = val1; // key
            c.val2    = val2; // value
            c.lineNum = base_idx + i; // debug info
            c.rawStr  = ls[i];        // debug info
            
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
        //_print(v_cmd[i]);
        sstd::terp::var var = sstd::terp::var( v_dst[v_dst.size()-1] );
        uint hsc_base_lx = v_hsc_lx[v_hsc_lx.size()-1];
        uint hsc_base_hx = v_hsc_hx[v_hsc_hx.size()-1];
        //sstd::printn(v_dst);
        //sstd::printn(v_hsc_lx);
        //sstd::printn(v_hsc_hx);
        //sstd::printn(ret_var);
        //printf("\n");
        
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

    return true;
}

//---

bool sstd::yaml_load(sstd::terp::var& ret_yml, const char* s){
    bool tf = true;
    
    std::vector<std::string> ls = sstd::_splitByLine_dq_sq(s); // v: vector, ls: line string
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
        s = _rm_comment(s); // s = _rm_comment_dq_sq(s); に置き換える
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
    std::vector<std::string> ls = sstd::_splitByLine_dq_sq(s); // v: vector, ls: line string
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

