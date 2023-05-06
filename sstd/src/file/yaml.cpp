#include <vector>
#include <string>

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
bool _is_empty(const std::string& s){
    for(uint i=0; i<s.size(); ++i){
        if(s[i]!=' '){ return false; }
    }
    return true;
}
void _skip_empty_line(uint& idx, const std::vector<std::string>& ls){
    for(; idx<ls.size(); ++idx){
        if(!_is_empty(ls[idx])){break;} // skip empty lines
    }
}

//---

uint _data_type(std::string s){
    if(sstd::charIn(':', s)){ return NUM_HASH; }
    s = sstd::lstrip(s);
    if(s.size()>=2 && s[0]=='-' && s[1]==' '){ return NUM_LIST; }
    return NUM_NULL;
}
bool _is_list(const std::string& s){
    for(uint i=0; i<s.size(); ++i){
        if(s[i]==' '){ continue; }
        if(s[i]=='-'){ return true; }
    }
    return false;
}
bool _is_list_value(const std::string& s){
    for(uint i=0; i+1<s.size(); ++i){
        if(s[i]==' '){ continue; }
        if(s[i]=='-' && s[i+1]==' '){ return true; }
    }
    return false;
}
bool _is_hash(const std::string& s){
    if(sstd::charIn(':', s)){ return true; }
    
    return false;
}
uint _head_space_count_for_hash(const std::string& s){
    uint c=0;
    for(uint i=0; i<s.size(); ++i){
        if(s[i]==' ' || s[i]=='-'){ ++c; continue; }
        break;
    }
    return c;
}
uint _head_space_count_for_list(const std::string& s){
    if(_is_hash(s)){ return _head_space_count_for_hash(s); }
    uint c=0;
    for(uint i=0; i<s.size(); ++i){
        if(s[i]==' '){ ++c; continue; }
        break;
    }
    return c;
}
uint _head_space_count(const std::string& s){
    if(_is_hash(s)){ return _head_space_count_for_hash(s); }
    return _head_space_count_for_list(s);
}
uint _head_space_count(const std::string& s, uint typeNum){
    if(typeNum==NUM_HASH || typeNum==NUM_LIST_AND_HASH){ return _head_space_count_for_hash(s); }
    return _head_space_count_for_list(s);
}

//---

std::string _rm_hyphen(std::string s){
    uint i=0;
    for(; i<s.size(); ++i){
        if(s[i]==' '||s[i]=='-'){ continue; }
        break;
    }
    return &s[i];
}

//---

std::string _get_list_str(const std::string& s, uint hsc){
    if(s.size()<=hsc){ return std::string(); }
    return &s[hsc];
}

//---

void _set_val(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc, uint& idx); // forward declaration

void _push_back_for_list(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc, uint& idx){
    std::string s;
    s = _get_list_str(ls[idx], hsc);
    s = _rm_comment(s);
    if(_is_empty(s)){ return; }

    ret.push_back(s.c_str());
}
void _set_val_str(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc, uint& idx){
    for(uint i=idx; i<ls.size(); ++i){
        std::string s;
        s = _get_list_str(ls[i], hsc);
        s = _rm_comment(s);
        if(_is_empty(s)){ continue; }

        if(ret.typeNum()!=sstd::num_null){ sstd::pdbg_err("ERROR\n"); break; }
        ret = s.c_str();
    }
}
void _set_val(sstd::terp::var& ret, const std::string& key_prev, std::string s, uint typeNum){
    if(typeNum==NUM_HASH){
        std::vector<std::string> v = sstd::split(s, ':');
        for(uint i=0; i<v.size(); ++i){ v[i]=sstd::strip(v[i]); } // remove spaces
        if(v.size()!=2){ sstd::pdbg_err("ERROR\n"); return; }

        ret[sstd::rstrip(_rm_hyphen(v[0])).c_str()] = sstd::strip(v[1]).c_str();
    }else if(typeNum==NUM_LIST){
        s = _rm_hyphen(s);
        ret.push_back(s.c_str());
    }else{
        sstd::printn("ERROR\n");
    }
}
void _set_val_list(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc_base, uint& idx){
    std::string key_prev;
    for(; idx<ls.size(); ++idx){
        std::string s;
        s = _rm_comment(ls[idx]);
        if(_is_empty(s)){ continue; }
        uint typeNum = _data_type(s);
        
        uint hsc = _head_space_count(s);
        if(hsc>hsc_base){
            if(typeNum==NUM_HASH){ ret.push_back(sstd::terp::hash()); }
            
            const sstd::terp::var& ret_tmp=ret[ret.size()-1];
            _set_val((sstd::terp::var&)ret_tmp, ls, hsc, idx);
            continue;
        }else if(hsc<hsc_base){
            --idx;
            break;
        }
        
        if(s=="-"){
            ret.push_back(sstd::terp::list());
            continue;
        }
        _set_val(ret, key_prev, s, typeNum);
    }
}
void _set_val_hash(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc_base, uint& idx){
    std::string key_prev;
    for(; idx<ls.size(); ++idx){
        std::string s;
        s = _rm_comment(ls[idx]);
        if(_is_empty(s)){ continue; }
        uint typeNum = _data_type(s);
        
        uint hsc = _head_space_count(s);
        if(hsc>hsc_base){
            if      (typeNum==NUM_HASH){ ret[key_prev.c_str()] = sstd::terp::hash();
            }else if(typeNum==NUM_LIST){ ret[key_prev.c_str()] = sstd::terp::list(); }
            
            const sstd::terp::var& ret_tmp=ret[key_prev.c_str()];
            _set_val((sstd::terp::var&)ret_tmp, ls, hsc, idx);
            continue;
        }else if(hsc<hsc_base){
            --idx;
            break;
        }
        
        if(typeNum==NUM_HASH && sstd::rstrip(s)[s.size()-1]==':'){
            std::vector<std::string> v = sstd::split(s, ':');
            for(uint i=0; i<v.size(); ++i){ v[i]=sstd::strip(v[i]); }
            key_prev = v[0];
            continue;
        }
        _set_val(ret, key_prev, s, typeNum);
    }
}

//---

void _set_val(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc, uint& idx){
    if(idx>=ls.size()){ return; }
    uint typeNum = _data_type(ls[idx]);
    //sstd::printn(typeNum);
    
    switch(typeNum){
    case NUM_NULL: { _set_val_str (ret, ls, hsc, idx); } break;
    case NUM_LIST: { _set_val_list(ret, ls, hsc, idx); } break;
    case NUM_HASH: { _set_val_hash(ret, ls, hsc, idx); } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }
}

//---

void _set_list_hash(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc, uint& idx){
    if(idx>=ls.size()){ return; }
    uint typeNum = _data_type(ls[idx]);
    
    switch(typeNum){
    case NUM_NULL: {                         } break;
    case NUM_LIST: { ret=sstd::terp::list(); } break;
    case NUM_HASH: { ret=sstd::terp::hash(); } break;
    default: { sstd::pdbg_err("ERROR\n"); } break;
    }
}

//---

struct command{
    uint hsc; // head space count
    char verb;
    std::string val1; // "list value" or "hash key"
    std::string val2; // "hash value" if Not required "sstd::terp::var"

    // debug info
    uint lineNum;
    std::string rawStr;
};
void _print(const struct command& cmd){
    printf("hsc: %d\n",  cmd.hsc         );
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
/*
void _set_val(sstd::terp::var& ret, const std::string& key_prev, std::string s, uint typeNum){
    if(typeNum==NUM_HASH){
        std::vector<std::string> v = sstd::split(s, ':');
        for(uint i=0; i<v.size(); ++i){ v[i]=sstd::strip(v[i]); } // remove spaces
        if(v.size()!=2){ sstd::pdbg_err("ERROR\n"); return; }

        ret[sstd::rstrip(_rm_hyphen(v[0])).c_str()] = sstd::strip(v[1]).c_str();
    }else if(typeNum==NUM_LIST){
        s = _rm_hyphen(s);
        ret.push_back(s.c_str());
    }else{
        sstd::printn("ERROR\n");
    }
}
*/
uint _data_type_ver2(std::string s){
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

std::vector<struct command> _parse_yaml(const std::vector<std::string>& ls){
    std::vector<struct command> v_cmd;
    sstd::printn(ls);
    
    for(uint i=0; i<ls.size(); ++i){
//        sstd::printn(ls[i]);

        std::string s;
        s = ls[i];
        s = _rm_comment(s);
        if(s.size()==0){ continue; }
//        sstd::printn(s);
        uint type = _data_type_ver2(s);
        uint hsc = _head_space_count(s, type);
        std::string val1, val2; _get_value(val1, val2, s, type);
        
        struct command c;
        switch(type){
        case NUM_STR: {
            c.hsc     = hsc;
            c.verb    = 's';
            c.val1    = val1;
            //c.val2    = val2;
            c.lineNum = i;     // debug info
            c.rawStr  = ls[i]; // debug info
            
            v_cmd.push_back(c);
        } break;
        case NUM_LIST: {
            c.hsc     = hsc;
            c.verb    = '-';
            c.val1    = val1;
            //c.val2    = val2;
            c.lineNum = i;     // debug info
            c.rawStr  = ls[i]; // debug info
            
            v_cmd.push_back(c);
        } break;
        case NUM_HASH: {
            c.hsc     = hsc;
            c.verb    = ':';
            c.val1    = val1;
            c.val2    = val2;
            c.lineNum = i;     // debug info
            c.rawStr  = ls[i]; // debug info
            
            v_cmd.push_back(c);
        } break;
        case NUM_LIST_AND_HASH:{
            c.hsc     = hsc;
            c.verb    = 'x'; // x: list x(and) hash: 
            c.val1    = "";
            c.val2    = "";
            c.lineNum = i;     // debug info
            c.rawStr  = ls[i]; // debug info
            
            v_cmd.push_back(c);
            
            c.hsc     = hsc;
            c.verb    = ':';
            c.val1    = val1;
            c.val2    = val2;
            c.lineNum = i;     // debug info
            c.rawStr  = ls[i]; // debug info
            
            v_cmd.push_back(c);
        } break;
        default: { sstd::pdbg_err("ERROR\n"); } break;
        };
    }
    
    return v_cmd;
}
void _set_val_ver2(sstd::terp::var& ret, const std::string& key_prev, std::string s, uint typeNum){
    if(typeNum==NUM_HASH){
        std::vector<std::string> v = sstd::split(s, ':');
        for(uint i=0; i<v.size(); ++i){ v[i]=sstd::strip(v[i]); } // remove spaces
        if(v.size()!=2){ sstd::pdbg_err("ERROR\n"); return; }

        ret[sstd::rstrip(_rm_hyphen(v[0])).c_str()] = sstd::strip(v[1]).c_str();
    }else if(typeNum==NUM_LIST){
        s = _rm_hyphen(s);
        ret.push_back(s.c_str());
    }else{
        sstd::printn("ERROR\n");
    }
}
void _construct_terpVar(sstd::terp::var& ret, const std::vector<struct command>& v_cmd){

    //std::vector<sstd::terp::var*> v_dst;
    std::vector<sstd::void_ptr*> v_dst;
    std::vector<uint> v_hsc;
    v_dst.push_back(ret.p());
    v_hsc.push_back(0);

    for(uint i=0; i<v_cmd.size(); ++i){
        sstd::printn(v_dst.size());
        sstd::printn(v_hsc.size());
        sstd::terp::var var = sstd::terp::var( v_dst[v_dst.size()-1] );
        uint hsc_base = v_hsc[v_hsc.size()-1];
        //uint typeNum = v_cmd[i].typeNum;
        sstd::printn(i);
        sstd::printn_all(var.typeNum());
        sstd::printn_all(var);
        _print(v_cmd[i]);
        
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
        sstd::printn_all(var.typeNum());
        
        if(v_cmd[i].hsc > hsc_base){
            printf("in sw push\n");
//            switch(v_cmd[i].verb){
//            case '-': { v_dst.push_back( var[var.size()-1].p() );          v_hsc.push_back(v_cmd[i].hsc); } break;
//            case ':': { v_dst.push_back( var[v_cmd[i].val1.c_str()].p() ); v_hsc.push_back(v_cmd[i].hsc); } break;
//            switch(var.typeNum()){
//            case sstd::num_vec_void_ptr:      { v_dst.push_back( var[var.size()-1].p() );          v_hsc.push_back(v_cmd[i].hsc); } break;
//            case sstd::num_hash_str_void_ptr: { v_dst.push_back( var[v_cmd[i].val1.c_str()].p() ); v_hsc.push_back(v_cmd[i].hsc); } break;
//            default: { sstd::pdbg_err("ERROR\n"); } break;
//            }
//            sstd::printn_all(var.typeNum());
            v_hsc.push_back(v_cmd[i].hsc);
            --i;
            continue;
        }else if(v_cmd[i].hsc < hsc_base){
            printf("in sw pop\n");
            v_dst.pop_back();
            v_hsc.pop_back();
            --i;
            continue;
        }
        
        // set dst value
        switch(v_cmd[i].verb){
        case 's': {
            if(var.typeNum()!=sstd::num_null){ sstd::pdbg_err("OverWritting the existing data. (String data type can only take one data.)\n"); break; }
            var = v_cmd[i].val1.c_str();
        } break;
        case '-': {
            if(v_cmd[i].val1.size()!=0){
                var.push_back( v_cmd[i].val1.c_str() );
            }else{
                var.push_back( sstd::terp::list() );
                v_dst.push_back( var[var.size()-1].p() );
                //v_hsc.push_back(v_cmd[i].hsc);
            }
        } break;
        case 'x': {
            var.push_back( sstd::terp::hash() );
            v_dst.push_back( var[var.size()-1].p() );
        } break;
        case ':': {
            if(v_cmd[i].val2.size()!=0){
                var[ v_cmd[i].val1.c_str() ] = v_cmd[i].val2.c_str();
            }else{
                v_dst.push_back( var[v_cmd[i].val1.c_str()].p() );
                //v_hsc.push_back(v_cmd[i].hsc);
            }
        } break;
        default: { sstd::pdbg_err("ERROR\n"); } break;
        }
    }
    
    return ;
}

sstd::terp::var sstd::yaml_from_str(const        char* s){
    sstd::terp::var ret;

    std::vector<std::string> ls = sstd::splitByLine(s); // ls: line string
    //sstd::printn(ls);
    std::vector<struct command> v_cmd = _parse_yaml(ls);
    printf("\n");
    //_print(v_cmd);
    sstd::terp::var ret2;
    _construct_terpVar(ret2, v_cmd);
    printf("\n");
    sstd::printn(ret2);
    printf("\n");
    
    /*
    uint idx=0;
    _skip_empty_line(idx, ls);
    _set_list_hash(ret, ls, 0, idx);
    _set_val(ret, ls, 0, idx);
    */
    
    return ret2;
}
sstd::terp::var sstd::yaml_from_str(const std::string& s){ return sstd::yaml_from_str(s.c_str()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
