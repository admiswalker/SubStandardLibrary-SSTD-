#include "strEdit.hpp"
#include "../file/file.hpp"
#include "../print/pdbg.hpp"
#include <string.h>


//--------------------------------------------------------------------------------------------------------

std::vector<std::string> sstd::splitByLine(const char* str){

    std::vector<std::string> ret;
    
    std::string buf;
    for(uint r=0; str[r]!=0; ++r){ // r: read place
        buf.clear();
        for(; str[r]!=0; ++r){
            if(str[r]==0x0A){ break; }                        // Uinx
            if(str[r]==0x0D && str[r+1]==0x0A){ ++r; break; } // Windows
            buf += str[r];
        }
        ret.push_back(std::move(buf));
    }
    
    return ret;
}
std::vector<std::string> sstd::splitByLine(const std::string& str){
    return sstd::splitByLine(str.c_str());
}

//--------------------------------------------------------------------------------------------------------

std::vector<std::string> asASpcase(const char* str){
    std::vector<std::string> splitList;
    
    std::string buf;
    uint i=0;
    while(str[i]!=0){ if(' '==str[i]){++i;}else{break;} } // skip space
    while(str[i]!=0){
        if(' '==str[i]){
            splitList.push_back(buf); buf.clear();
            ++i;
            while(str[i]!=0){ if(' '==str[i]){++i;}else{break;} } // skip space
        }else{
            buf+=str[i];
            ++i;
        }
    }
    if(buf.size()!=0){ splitList.push_back(buf); }
    return splitList;
}
std::vector<std::string> asAX(const char* str, const char X){
    std::vector<std::string> splitList;
    
    std::string buf;
    uint i=0;
    while(str[i]!=0){ if(' '==str[i]){++i;}else{break;} } // skip space
    while(str[i]!=0){
        if(X==str[i]){
            sstd::rstrip_ow(buf); splitList.push_back(buf); buf.clear();
            ++i;
            while(str[i]!=0){ if(' '==str[i]){++i;}else{break;} } // skip space
        }else{
            buf+=str[i];
            ++i;
        }
    }
    if(buf.size()!=0){ sstd::rstrip_ow(buf); splitList.push_back(buf); }
    return splitList;
}
std::vector<std::string> sstd::split(const char* str, const char X){
    if(X==' '){ return asASpcase(str);
    }  else   { return asAX     (str, X); }
}
std::vector<std::string> sstd::split(const std::string& str, const char X){
    return std::move(sstd::split(str.c_str(), X));
}

//--------------------------------------------------------------------------------------------------------

std::string lstrip_base(const uchar* str){
    std::string ret;
    
    uint r=0;
    for(; str[r]!=0; ++r){
        if(str[r]==' ' || str[r]=='\t'){
        }             else             { break; }
    }
    for(; str[r]!=0; ++r){ ret+=str[r]; }
    
    return ret;
}
std::string sstd::lstrip(const        char* str){ return lstrip_base((const uchar*)str        ); }
std::string sstd::lstrip(const std::string& str){ return lstrip_base((const uchar*)str.c_str()); }

void sstd::lstrip_ow(std::string& str){
    std::string sre_ret = sstd::lstrip(str);
    str = std::move(sre_ret);
}

std::string rstrip_base(const uchar* str, int len){
    int r=len-1;
    for(; r>=0; --r){
        if(str[r]==' ' || str[r]=='\t'){
        }             else             { break; }
    }
    return std::string((const char*)str, r+1);
}
std::string sstd::rstrip(const        char* str){ return rstrip_base((const uchar*)str,         strlen(str)); }
std::string sstd::rstrip(const std::string& str){ return rstrip_base((const uchar*)str.c_str(), str.size() ); }

void sstd::rstrip_ow(std::string& str){
    for(int r=str.size()-1; r>=0; --r){
        if(str[r]==' ' || str[r]=='\t'){ str.erase(r);
        }             else             { break; }
    }
}

std::string strip_base(const uchar* str){
    std::string ret = lstrip_base(str);
    sstd::rstrip_ow(ret);
    return ret;
}
std::string sstd::strip(const        char* str){ return strip_base((const uchar*)str        ); }
std::string sstd::strip(const std::string& str){ return strip_base((const uchar*)str.c_str()); }

void sstd::strip_ow(std::string& str){
    str = lstrip_base((const uchar*)str.c_str());
    sstd::rstrip_ow(str);
}
std::vector<std::string> sstd::strip(const std::vector<std::string>& vec){
    std::vector<std::string> ret(vec.size()); ret.clear();
    
    for(uint i=0; i<vec.size(); ++i){
        ret.push_back(strip_base((const uchar*)vec[i].c_str()));
    }
    
    return ret;
}

//--------------------------------------------------------------------------------------------------------

std::string lstrip_base(const char* str, const uint len, const char c){
    uint i=0;
    while(i<len && str[i]==c){ ++i; }
    
    return std::string(&str[i], len-i);
}
std::string sstd::lstrip   (const        char* str, const char c){ return lstrip_base(str,         strlen(str), c); }
std::string sstd::lstrip   (const std::string& str, const char c){ return lstrip_base(str.c_str(),  str.size(), c); }
void        sstd::lstrip_ow(      std::string& str, const char c){
    uint i=0;
    while(i<str.size() && str[i]==c){ ++i; }

    uint r=0;
    for(; i<str.size(); ++r, ++i){
        str[r] = str[i];
    }
    str.resize(r);
}

//---

std::string rstrip_base(const char* str, const uint len, const char c){
    int i=len-1;
    while(i>=0 && str[i]==c){ --i; }
    
    return std::string(&str[0], i+1);
}
std::string sstd::rstrip   (const        char* str, const char c){ return rstrip_base(str,         strlen(str), c); }
std::string sstd::rstrip   (const std::string& str, const char c){ return rstrip_base(str.c_str(),  str.size(), c); }
void        sstd::rstrip_ow(      std::string& str, const char c){
    int i=str.size()-1;
    while(i>=0 && str[i]==c){ --i; }
    
    str.resize(i+1);
}

//---

std::string strip_base(const char* str, uint len, const char c){
    uint b=0; // begin
    while(b<len && str[b]==c){ ++b; }
    if(b==len){ return std::string(); }
    
    int e=len-1; // end
    while(e>=0 && str[e]==c){ --e; }
    
//    if(e<(int)b){ return std::string(); }
    return std::string(&str[b], e-b+1);
}
std::string sstd::strip   (const        char* str, const char c){ return strip_base(str,         strlen(str), c); }
std::string sstd::strip   (const std::string& str, const char c){ return strip_base(str.c_str(),  str.size(), c); }
void        sstd::strip_ow(      std::string& str, const char c){
    uint b=0; // begin
    while(b<str.size() && str[b]==c){ ++b; }
    if(b==str.size()){ str.resize(0); return; }
    
    int e=str.size()-1; // end
    while(e>=0 && str[e]==c){ --e; }

    uint r=0;
    for(uint i=b; i<(uint)e+1; ++r, ++i){
        str[r] = str[i];
    }
    str.resize(e-b+1);
}

//--------------------------------------------------------------------------------------------------------

std::string stripAll_base(const char* str, const uint len, const char c){
    std::string ret('0', len); ret.clear();
    
    for(uint i=0; i<len; ++i){
        if(str[i]==c){ continue; }
        ret += str[i];
    }
    return ret;
}
std::string sstd::stripAll(const        char* str, const char c){ return stripAll_base(str,         strlen(str), c); }
std::string sstd::stripAll(const std::string& str, const char c){ return stripAll_base(str.c_str(),  str.size(), c); }

//--------------------------------------------------------------------------------------------------------

void sstd::stripAll_ow(std::string& str, const char c){
    uint r=0;
    
    for(uint i=0; i<str.size(); ++i){
        if(str[i]==c){ continue; }
        str[r] = str[i]; ++r;
    }
    
    str.resize(r);
}

//--------------------------------------------------------------------------------------------------------

std::string stripAll_base(const char* str, const uint len, const char* stripList, const uint sLen){
    std::string ret('0', len); ret.clear();
    
    if(len * sLen <= 256){
        for(uint i=0; i<len; ++i){
            bool TF_continue=false;
            for(uint si=0; si<sLen; ++si){
                if(str[i]==stripList[si]){ TF_continue=true; break; }
            }
            if(TF_continue){ continue; }
            
            ret += str[i];
        }
    }else{
        bool sTbl[256]={false};
        for(uint si=0; si<sLen; ++si){ sTbl[ (uchar)stripList[si] ] = true; }
        
        for(uint i=0; i<len; ++i){
            if( sTbl[ (uchar)str[i] ] ){ continue; }
            ret += str[i];
        }
    }
    
    return ret;
}
std::string sstd::stripAll   (const        char* str, const        char* stripList){ return stripAll_base(str,         strlen(str), stripList,         strlen(stripList)); }
std::string sstd::stripAll   (const std::string& str, const        char* stripList){ return stripAll_base(str.c_str(),  str.size(), stripList,         strlen(stripList)); }
std::string sstd::stripAll   (const        char* str, const std::string& stripList){ return stripAll_base(str,         strlen(str), stripList.c_str(),  stripList.size()); }
std::string sstd::stripAll   (const std::string& str, const std::string& stripList){ return stripAll_base(str.c_str(),  str.size(), stripList.c_str(),  stripList.size()); }

void stripAll_ow_base(std::string& str, const char* stripList, const uint sLen){
    const uint len = str.size();
    uint r=0;
    
    if(len * sLen <= 256){
        for(uint i=0; i<len; ++i){
            bool TF_continue=false;
            for(uint si=0; si<sLen; ++si){
                if(str[i]==stripList[si]){ TF_continue=true; break; }
            }
            if(TF_continue){ continue; }
            
            str[r] = str[i]; ++r;
        }
    }else{
        bool sTbl[256]={false};
        for(uint si=0; si<sLen; ++si){ sTbl[ (uchar)stripList[si] ] = true; }
        
        for(uint i=0; i<len; ++i){
            if( sTbl[ (uchar)str[i] ] ){ continue; }
            str[r] = str[i]; ++r;
        }
    }
    
    str.resize(r);
    return;
}
void        sstd::stripAll_ow(      std::string& str, const        char* stripList){ stripAll_ow_base(str, stripList,         strlen(stripList)); return; }
void        sstd::stripAll_ow(      std::string& str, const std::string& stripList){ stripAll_ow_base(str, stripList.c_str(),  stripList.size()); return; }

//--------------------------------------------------------------------------------------------------------
