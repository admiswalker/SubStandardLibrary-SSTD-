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

std::string _rmComment(const std::string& s){
    std::vector<std::string> v = sstd::split(s, '#');
    sstd::printn(v);
    //return sstd::rstrip(v[0]);
    return "";
}
bool _isEmpty(const std::string& s){
    for(uint i=0; i<s.size(); ++i){
        if(s[i]!=' '){ return false; }
    }
    return true;
}
void _skip_empty_line(uint& idx, const std::vector<std::string>& ls){
    for(; idx<ls.size(); ++idx){
        if(!_isEmpty(ls[idx])){break;} // skip empty lines
    }
}

//---

uint _count_head_space(std::string& s){
    uint c=0;
    for(uint i=0; i<s.size(); ++i){
        if(s[i]!=' '){ break; }
        ++c;
    }
    return c;
}
uint _data_type(uint hsc, const std::string& s){
    if(s.size() <= hsc+2){ return NUM_NULL; }
    if(s[hsc]=='-' && s[hsc+1]==' '){ return NUM_LIST; }

    if(sstd::charIn(':', s)){ return NUM_HASH; }

    return NUM_NULL;
}
std::string _get_str_from_vec(const std::string& s){
    if(s.size()<=2){ return std::string(); }
    return &s[2];
}
void _get_str_from_hash(std::string& key, std::string& val, const std::string& s){
}

void _set_val_list(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc, uint idx){
    for(uint i=idx; i<ls.size(); ++i){
        std::string s;
        s = _get_str_from_vec(ls[i]);
        s = _rmComment(s);
//        if(_isEmpty(s)){ continue; }
        
        sstd::printn(s);
//        ret.push_back(s.c_str());
    }
}
void _set_val_hash(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc, uint idx){
    for(uint i=idx; i<ls.size(); ++i){
        std::string s = _get_str_from_vec(ls[i]);
        if(_isEmpty(ls[i])){ continue; }
        
//        sstd::printn(s);
        ret.push_back(s.c_str());
    }
}
void _set_val(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc, uint idx){
    if(idx>=ls.size()){ return; }
    uint typeNum = _data_type(hsc, ls[idx]);
    
    switch(typeNum){
    case NUM_LIST: { ret=sstd::terp::list(); _set_val_list(ret, ls, hsc, idx); } break;
    case NUM_HASH: { ret=sstd::terp::hash(); _set_val_hash(ret, ls, hsc, idx); } break;
    default: { sstd::pdbg("ERROR"); } break;
    }
}

sstd::terp::var sstd::yaml_from_str(const        char* s){
    sstd::terp::var ret;

    std::vector<std::string> ls = sstd::splitByLine(s); // line string
    //sstd::printn(ls);

    uint idx=0;
    _skip_empty_line(idx, ls);
    /*
    if(idx>=ls.size()){ return ret; }
    uint typeNum = _data_type(0, ls[idx]);
    
    switch(typeNum){
    case NUM_LIST: { ret=sstd::terp::list(); } break;
    case NUM_HASH: { ret=sstd::terp::hash(); } break;
    default: { sstd::pdbg("ERROR"); } break;
    }

    _set_val(ret, ls, 0, (uint)idx);
    */
    _set_val(ret, ls, 0, (uint)idx);
    
    return ret;
}
sstd::terp::var sstd::yaml_from_str(const std::string& s){ return sstd::yaml_from_str(s.c_str()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
