#include <vector>
#include <string>

#include "yaml.hpp"

#include "../definitions/typeDef.h"
#include "../string/strEdit.hpp"
#include "../string/strmatch.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define NUM_NULL 255
#define NUM_VEC 1
#define NUM_HASH 2

//-----------------------------------------------------------------------------------------------------------------------------------------------

uint _count_head_space(std::string& s){
    uint c=0;
    for(uint i=0; i<s.size(); ++i){
        if(s[i]!=' '){ break; }
        ++c;
    }
    return c;
}
uint _data_type(uint hsc, std::string& s){
    if(s.size() <= hsc+2){ return NUM_NULL; }
    if(s[hsc]=='-' && s[hsc+1]==' '){ return NUM_VEC; }

    if(sstd::charIn(':', s)){ return NUM_HASH; }

    return NUM_NULL;
}
std::string _get_str_from_vec(const std::string& s){
    return &s[2];
}
void _get_str_from_hash(std::string& key, std::string& val, const std::string& s){
}

void _set_val(sstd::terp::var& ret, const std::vector<std::string>& ls, uint hsc, uint ls_begin){
    for(uint i=ls_begin; i<ls.size(); ++i){
        std::string s = _get_str_from_vec(ls[i]);
        sstd::printn(s);
        ret.push_back(s.c_str());
    }
}

sstd::terp::var sstd::yaml_from_str(const        char* s){
    sstd::terp::var ret;
    //std::vector<std::string> ls = sstd::splitByLine(s);                 // ls: line string
    //std::vector<uint> ln(ls.size()); std::iota(ln.begin(),ln.end(), 1); // ln: line number
    //sstd::remove(ls, ln);
    //sstd::printn(ls);
    //sstd::printn(ln);

    std::vector<std::string> ls = sstd::splitByLine(s); // line string
    //std::vector<uint> hsc(ls.size()); // head space count
    // ls = _rm_comment(ls);

    if(ls.size()==0){ return ret; }
    uint typeNum = _data_type(0, ls[0]);
    
    switch(typeNum){
    case NUM_VEC: { ret=sstd::terp::list(); } break;
    default: { sstd::pdbg("ERROR"); } break;
    }

    _set_val(ret, ls, 0, (uint)0);
    /*
    for(uint i=0; i<ls.size(); ++i){
        //sstd::printn(ls[i]);
        
        uint hsc = _count_head_space(ls[i]);
        //sstd::printn(hsc);
        //if(hsc!=0){ continue; }

        uint tn = _data_type(hsc, ls[i]);
        //sstd::printn(tn);
    }
    */
    return ret;
}
sstd::terp::var sstd::yaml_from_str(const std::string& s){ return sstd::yaml_from_str(s.c_str()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
