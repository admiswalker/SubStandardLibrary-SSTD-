#include "strEdit.hpp"
#include "file/file.hpp"
#include "pdbg.hpp"
#include <string.h> // for ::strcmp()


//--------------------------------------------------------------------------------------------------------

std::vector<std::string> sstd::splitByLine(const std::string& str){

    std::vector<std::string> ret;
    
    std::string buf;
    for(uint r=0; str[r]!=0; ++r){ // r: read place
        buf.clear();
        for(; str[r]!=0; ++r){
            if(str[r]==0x0A){ break; }                            // Uinx
            if(str[r]==0x0D && str[r+1]==0x0A){ ++r; break; }    // Windows
            buf += str[r];
        }
        ret.push_back(std::move(buf));
    }
    
    return ret;
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

bool sstd::strcmp(const char*        str1, const char*        str2){ return (::strcmp(str1,         str2        )==0); }
bool sstd::strcmp(const char*        str1, const std::string& str2){ return (::strcmp(str1,         str2.c_str())==0); }
bool sstd::strcmp(const std::string& str1, const char*        str2){ return (::strcmp(str1.c_str(), str2        )==0); }
bool sstd::strcmp(const std::string& str1, const std::string& str2){ return (::strcmp(str1.c_str(), str2.c_str())==0); }

//--------------------------------------------------------------------------------------------------------

bool sstd::strIn(const char*        lhs, const char*        rhs){
    bool ret=true;
    uint l=0, r=0;
    for(;;){
        if(lhs[l]=='\0'){ return ret;   }
        if(rhs[r]=='\0'){ return false; }
        
        if(lhs[l]==rhs[r]){ ret=true;
        }       else      { ret=false; l=0; }
        
        ++l; ++r;
    }
}
bool sstd::strIn(const char*        lhs, const std::string& rhs){ return sstd::strIn(lhs        , rhs.c_str()); }
bool sstd::strIn(const std::string& lhs, const char*        rhs){ return sstd::strIn(lhs.c_str(), rhs        ); }
bool sstd::strIn(const std::string& lhs, const std::string& rhs){ return sstd::strIn(lhs.c_str(), rhs.c_str()); }

//--------------------------------------------------------------------------------------------------------

