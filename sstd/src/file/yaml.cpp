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
    return v[0];
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

uint _get_head_space_count(const std::string& s){
    uint c=0;
    for(uint i=0; i<s.size(); ++i){
        if(s[i]!=' '){ break; }
        ++c;
    }
    return c;
}
uint _data_type(const std::string& s, uint hsc){
    if(s.size() <= hsc+2){ return NUM_NULL; }
    if(s[hsc]=='-' && s[hsc+1]==' '){ return NUM_LIST; }

    if(sstd::charIn(':', s)){ return NUM_HASH; }

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

//---

std::string _rm_hyphen(std::string s){
    if(s.size()<=2){ return std::string();}
    return &s[2];
}

//---

std::string _get_list_str(const std::string& s, uint hsc){
    if(s.size()<=hsc){ return std::string(); }
    return &s[hsc];
}
std::string _get_hash_str(const std::string& s){
    return s;
}

//---

void _set_val(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc, uint& idx); // forward declaration

void _push_back_for_list(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc, uint& idx){
    std::string s;
    s = _get_list_str(ls[idx], hsc);
    s = _rm_comment(s);
    if(_is_empty(s)){ return; }

    ret.push_back(s.c_str());
    //sstd::printn(hsc);
    //sstd::printn(s);
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
    
    for(uint i=idx; i<ls.size(); ++i){
        std::string s;
        //s = _get_list_str(ls[i], hsc_base);
        //s = _rm_comment(s);
        sstd::printn(ls[i]);
        s = _rm_comment(ls[i]);
        if(_is_empty(s)){ continue; }
        
        sstd::printn(i);
        sstd::printn(s);
        uint hsc_tmp = _get_head_space_count(s);
        sstd::printn(hsc_base);
        sstd::printn(hsc_tmp);
        
        //sstd::printn(hsc_tmp);
        if(hsc_tmp!=hsc_base){
            printf("imh\n");
            const sstd::terp::var& ret_tmp=ret[ret.size()-1];
            _set_val((sstd::terp::var&)ret_tmp, ls, hsc_tmp, idx);
            continue;
        }
        
        if(s=="-"){
            ret.push_back(sstd::terp::list());
            continue;
        }
        s = _rm_hyphen(s);
        ret.push_back(s.c_str());
    }
}
void _set_val_hash(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc, uint& idx){
    for(uint i=idx; i<ls.size(); ++i){
        std::string s;
        s = _get_hash_str(ls[i]);
        s = _rm_comment(s);
        if(_is_empty(s)){ continue; }

        std::vector<std::string> v = sstd::split(s, ':');
        if(v.size()!=2){ sstd::pdbg("ERROR\n"); }
        
//        sstd::printn(v);
        ret[v[0].c_str()] = v[1].c_str();
    }
}

//---

void _set_val(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc, uint& idx){
    if(idx>=ls.size()){ return; }
    uint typeNum = _data_type(ls[idx], hsc);
    //sstd::printn(idx);
    //sstd::printn(ls[idx]);
    //sstd::printn(typeNum);
    
    switch(typeNum){
    case NUM_NULL: {                         _set_val_str (ret, ls, hsc+0, idx); } break;
    case NUM_LIST: { ret=sstd::terp::list(); _set_val_list(ret, ls, hsc+0, idx); } break;
    case NUM_HASH: { ret=sstd::terp::hash(); _set_val_hash(ret, ls, hsc+0, idx); } break;
    default: { sstd::pdbg("ERROR\n"); } break;
    }
}

sstd::terp::var sstd::yaml_from_str(const        char* s){
    sstd::terp::var ret;

    std::vector<std::string> ls = sstd::splitByLine(s); // ls: line string
    //sstd::printn(ls);

    uint idx=0;
    _skip_empty_line(idx, ls);
    
    _set_val(ret, ls, 0, idx);
    
    return ret;
}
sstd::terp::var sstd::yaml_from_str(const std::string& s){ return sstd::yaml_from_str(s.c_str()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
