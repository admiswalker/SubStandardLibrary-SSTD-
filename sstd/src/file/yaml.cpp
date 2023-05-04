#include <vector>
#include <string>

#include "yaml.hpp"

#include "../definitions/typeDef.h"
#include "../string/strEdit.hpp"
#include "../string/strmatch.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define NUM_NULL 255
#define NUM_LIST 1
#define NUM_HASH 2

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

uint _data_type(const std::string& s, uint hsc){
    if(s.size() <= hsc+2){ return NUM_NULL; }
    if(sstd::charIn(':', s)){ return NUM_HASH; }
    if(s[hsc]=='-' && s[hsc+1]==' '){ return NUM_LIST; }

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

        if(ret.typeNum()!=sstd::num_null){ sstd::pdbg("ERROR\n"); break; }
        ret = s.c_str();
    }
}
void _set_val_list(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc_base, uint& idx){
    for(; idx<ls.size(); ++idx){
        std::string s;
        s = _rm_comment(ls[idx]);
        if(_is_empty(s)){ continue; }
        
        uint hsc = _head_space_count(s);
        if(hsc>hsc_base){
            if(_is_hash(s)){
                ret.push_back(sstd::terp::hash());
            }
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
        s = _rm_hyphen(s);
        ret.push_back(s.c_str());
    }
}
void _set_val_hash(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc_base, uint& idx){
    std::string key_prev;
    for(; idx<ls.size(); ++idx){
        std::string s;
        s = _rm_comment(ls[idx]);
        if(_is_empty(s)){ continue; }
        
        uint hsc = _head_space_count(s);
        if(hsc>hsc_base){
            const sstd::terp::var& ret_tmp=ret[key_prev.c_str()];
            _set_val((sstd::terp::var&)ret_tmp, ls, hsc, idx);
            continue;
        }else if(hsc<hsc_base){
            --idx;
            break;
        }
        
        std::vector<std::string> v = sstd::split(s, ':');
        for(uint i=0; i<v.size(); ++i){ v[i]=sstd::strip(v[i]); }
        if(v.size()==1 && sstd::charIn(':', s)){
            key_prev = v[0];
            ret[key_prev.c_str()] = sstd::terp::hash();
            continue;
        }
        if(v.size()!=2){ sstd::pdbg("ERROR\n"); return; }

        ret[sstd::rstrip(_rm_hyphen(v[0])).c_str()] = sstd::strip(v[1]).c_str();
    }
}

//---

void _set_val(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc, uint& idx){
    if(idx>=ls.size()){ return; }
    uint typeNum = _data_type(ls[idx], hsc);
    //sstd::printn(typeNum);
    
    switch(typeNum){
    case NUM_NULL: { _set_val_str (ret, ls, hsc, idx); } break;
    case NUM_LIST: { _set_val_list(ret, ls, hsc, idx); } break;
    case NUM_HASH: { _set_val_hash(ret, ls, hsc, idx); } break;
    default: { sstd::pdbg("ERROR\n"); } break;
    }
}

//---

void _set_list_hash(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc, uint& idx){
    if(idx>=ls.size()){ return; }
    uint typeNum = _data_type(ls[idx], hsc);
    
    switch(typeNum){
    case NUM_NULL: {                         } break;
    case NUM_LIST: { ret=sstd::terp::list(); } break;
    case NUM_HASH: { ret=sstd::terp::hash(); } break;
    default: { sstd::pdbg("ERROR\n"); } break;
    }
}

//---

sstd::terp::var sstd::yaml_from_str(const        char* s){
    sstd::terp::var ret;

    std::vector<std::string> ls = sstd::splitByLine(s); // ls: line string
    //sstd::printn(ls);

    uint idx=0;
    _skip_empty_line(idx, ls);

    _set_list_hash(ret, ls, 0, idx);
    _set_val(ret, ls, 0, idx);
    
    return ret;
}
sstd::terp::var sstd::yaml_from_str(const std::string& s){ return sstd::yaml_from_str(s.c_str()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
