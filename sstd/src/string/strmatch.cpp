#include <algorithm> // for std::reverse
#include <string.h>
#include <vector>

#include "./strmatch.hpp"
#include "../definitions/typeDef.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// startswith()

bool _startswith_base(const        char* str, const        char* searchString, const uint len){
    return ::strncmp(str, searchString, len)==0; // strncmp() is a standard function of the C Langage.
}
bool sstd::startswith(const        char* str, const        char* searchString){ return _startswith_base(str        , searchString        , ::strlen(searchString)); }
bool sstd::startswith(const        char* str, const std::string& searchString){ return _startswith_base(str        , searchString.c_str(), searchString.size()   ); }
bool sstd::startswith(const std::string& str, const        char* searchString){ return _startswith_base(str.c_str(), searchString        , ::strlen(searchString)); }
bool sstd::startswith(const std::string& str, const std::string& searchString){ return _startswith_base(str.c_str(), searchString.c_str(), searchString.size()   ); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// strcmp()

bool sstd::strcmp(const char*        str1, const char*        str2){ return (::strcmp(str1,         str2        )==0); }
bool sstd::strcmp(const char*        str1, const std::string& str2){ return (::strcmp(str1,         str2.c_str())==0); }
bool sstd::strcmp(const std::string& str1, const char*        str2){ return (::strcmp(str1.c_str(), str2        )==0); }
bool sstd::strcmp(const std::string& str1, const std::string& str2){ return (::strcmp(str1.c_str(), str2.c_str())==0); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// strmatch()

bool sstd::strmatch(
        const char* str,     // target string to search
        const char* wildcard // wild card ('*' and '?' are available.)
){
    if      (*wildcard=='\0'){ return '\0' == *str;
    }else if(*wildcard=='*' ){ return strmatch(str, wildcard+1) || (('\0' != *str) && strmatch(str+1, wildcard));
    }else if(*wildcard=='?' ){ return ('\0' != *str) && strmatch(str+1, wildcard+1);
    }          else          { return ((uchar)*wildcard == (uchar)*str) && strmatch(str+1, wildcard+1);
    }
}
bool sstd::strmatch(const        char* str, const std::string& wildcard){ return sstd::strmatch(str        , wildcard.c_str()); }
bool sstd::strmatch(const std::string& str, const        char* wildcard){ return sstd::strmatch(str.c_str(), wildcard        ); }
bool sstd::strmatch(const std::string& str, const std::string& wildcard){ return sstd::strmatch(str.c_str(), wildcard.c_str()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool sstd::pathmatch(
               const char* str,     // target string to search
               const char* wildcard // wild card ('*' and '?' are available.)
){
    if      (*wildcard=='\0'){ return '\0' == *str;
    }else if(*wildcard=='*' ){ return pathmatch(str, wildcard+1) || (('\0' != *str) && ('/' != *str) && ('\\' != *str) && pathmatch(str+1, wildcard));
    }else if(*wildcard=='?' ){ return ('\0' != *str) && ('/' != *str) && ('\\' != *str) && pathmatch(str+1, wildcard+1);
    }          else          { return ((uchar)*wildcard == (uchar)*str) && pathmatch(str+1, wildcard+1);
    }
}
bool sstd::pathmatch(const        char* str, const std::string& wildcard){ return sstd::pathmatch(str        , wildcard.c_str()); }
bool sstd::pathmatch(const std::string& str, const        char* wildcard){ return sstd::pathmatch(str.c_str(), wildcard        ); }
bool sstd::pathmatch(const std::string& str, const std::string& wildcard){ return sstd::pathmatch(str.c_str(), wildcard.c_str()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// strmatch_getWC()

/*
bool getWC_entity(
        const char* str,      // target string to search
        const char* wildcard, // wild card ('*' and '?' are available.)
        std::string& retWC    // returning a string that matches the wild card
){
    if(*wildcard=='\0'){
        return '\0' == *str;
        
    }else if(*wildcard=='*'){
        bool retL = getWC_entity(str, wildcard+1, retWC);
        bool retR = (('\0' != *str) && getWC_entity(str+1, wildcard, retWC));
        if(retR && '\0'!=*str){ retWC += *str; }
        return retL || retR;
        
    }else if(*wildcard=='?'){
        bool ret = ('\0' != *str) && getWC_entity(str+1, wildcard+1, retWC);
        if(ret && '\0'!=*str){ retWC += *str; }
        return ret;
        
    }else{
        return ((uchar)*wildcard == (uchar)*str) && getWC_entity(str+1, wildcard+1, retWC);
    }
}
bool sstd::strmatch_getWC(
        const char* str,      // target string to search
        const char* wildcard, // wild card ('*' and '?' are available.)
        std::string& retWC    // returning a string that matches the wild card
){
    retWC.clear();
    bool ret = getWC_entity(str, wildcard, retWC);
    if(!ret){ retWC.clear(); }
    
    std::reverse(retWC.begin(), retWC.end());
    return ret;
}
// This code is optimized like below code. (removing std::reverse()).

//*/

bool getWC_entity(
        const char* str,      // target string to search
        const char* wildcard, // wild card ('*' and '?' are available.)
        std::string& retWC    // returning a string that matches the wild card
){
    if(*wildcard=='\0'){
        return '\0' == *str;
        
    }else if(*wildcard=='*'){
        bool retL = getWC_entity(str, wildcard+1, retWC);
        
        if('\0'!=*str){ retWC += *str; }
        bool retR = (('\0' != *str) && getWC_entity(str+1, wildcard, retWC));
        if(!retR && '\0'!=*str){ retWC.erase(--retWC.end()); }
        
        return retL || retR;
        
    }else if(*wildcard=='?'){
        if('\0'!=*str){ retWC += *str; }
        bool ret = ('\0' != *str) && getWC_entity(str+1, wildcard+1, retWC);
        if(!ret && '\0'!=*str){ retWC.erase(--retWC.end()); }
        return ret;
        
    }else{
        return ((uchar)*wildcard == (uchar)*str) && getWC_entity(str+1, wildcard+1, retWC);
    }
}
bool sstd::strmatch_getWC(
        const char* str,      // target string to search
        const char* wildcard, // wild card ('*' and '?' are available.)
        std::string& retWC    // returning a string that matches the wild card
){
    retWC.clear();
    bool ret = getWC_entity(str, wildcard, retWC);
    if(!ret){ retWC.clear(); }
    return ret;
}

bool sstd::strmatch_getWC(const        char* str, const std::string& wildcard, std::string& retWC){ return sstd::strmatch_getWC(str        , wildcard.c_str(), retWC); }
bool sstd::strmatch_getWC(const std::string& str, const        char* wildcard, std::string& retWC){ return sstd::strmatch_getWC(str.c_str(), wildcard        , retWC); }
bool sstd::strmatch_getWC(const std::string& str, const std::string& wildcard, std::string& retWC){ return sstd::strmatch_getWC(str.c_str(), wildcard.c_str(), retWC); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// rcount(), lcount(), count()

uint _rcount_base(const        char* str, uint len, char X){
    uint ret_cnt=0;
    for(int i=len-1; i>=0; --i){
        if(str[i]!=X){ break; }
        ++ret_cnt;
    }
    return ret_cnt;
}
uint sstd::rcount(const        char* str, char X){ return _rcount_base(str        , ::strlen(str), X); }
uint sstd::rcount(const std::string& str, char X){ return _rcount_base(str.c_str(), str.size()   , X); }

//---

uint sstd::lcount(const char* str, char X){
    uint ret_cnt=0;
    for(uint i=0; str[i]!='\0'; ++i){
        if(str[i]!=X){ break; }
        ++ret_cnt;
    }
    return ret_cnt;
}
uint sstd::lcount(const std::string& str, char X){ return sstd::lcount(str.c_str(), X); }

//---

uint  sstd::count(const        char* str, char X){
    uint ret_cnt=0;
    for(uint i=0; str[i]!='\0'; ++i){
        if(str[i]==X){ ++ret_cnt; }
    }
    return ret_cnt;
}
uint  sstd::count(const std::string& str, char X){ return sstd::count(str.c_str(), X); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define return_isX(X)                                   \
    for(uint i=0; rhs[i]!='\0'; ++i){                   \
        if(! X ){ return false; }                       \
    }                                                   \
    return true;

bool sstd::isNum            (const        char  rhs){ return      ('0'<=rhs   &&rhs   <='9');   }
bool sstd::isNum            (const        char* rhs){ return_isX( ('0'<=rhs[i]&&rhs[i]<='9') ); }
bool sstd::isNum            (const std::string& rhs){ return_isX( ('0'<=rhs[i]&&rhs[i]<='9') ); }
bool sstd::isAlphabet       (const        char  rhs){ return       ('a'<=rhs   &&rhs   <='z') || ('A'<=rhs   &&rhs   <='Z');    }
bool sstd::isAlphabet       (const        char* rhs){ return_isX( (('a'<=rhs[i]&&rhs[i]<='z') || ('A'<=rhs[i]&&rhs[i]<='Z')) ); }
bool sstd::isAlphabet       (const std::string& rhs){ return_isX( (('a'<=rhs[i]&&rhs[i]<='z') || ('A'<=rhs[i]&&rhs[i]<='Z')) ); }
bool sstd::isAlphabet_upper(const        char  rhs){ return      ('A'<=rhs    && rhs   <='Z');   }
bool sstd::isAlphabet_upper(const        char* rhs){ return_isX( ('A'<=rhs[i] && rhs[i]<='Z') ); }
bool sstd::isAlphabet_upper(const std::string& rhs){ return_isX( ('A'<=rhs[i] && rhs[i]<='Z') ); }
bool sstd::isAlphabet_lower(const        char  rhs){ return      ('a'<=rhs    && rhs   <='z');   }
bool sstd::isAlphabet_lower(const        char* rhs){ return_isX( ('a'<=rhs[i] && rhs[i]<='z') ); }
bool sstd::isAlphabet_lower(const std::string& rhs){ return_isX( ('a'<=rhs[i] && rhs[i]<='z') ); }

#undef return_isX

//-----------------------------------------------------------------------------------------------------------------------------------------------
// charIn()

bool sstd::charIn(const char lhs, const char* rhs){ // Is lhs in rhs ?
    for(uint i=0; rhs[i]!='\0'; ++i){
        if(rhs[i]==lhs){ return true; }
    }
    return false;
}
bool sstd::charIn(const char lhs, const std::string& rhs){ return sstd::charIn(lhs, rhs.c_str()); }

bool sstd::charIn(const char* lhs, const char* rhs){ // Is lhs in rhs ?
    for(uint ri=0; rhs[ri]!='\0'; ++ri){
        for(uint li=0; lhs[li]!='\0'; ++li){
            if(rhs[ri]==lhs[li]){ return true; }
        }
    }
    return false;
}
bool sstd::charIn(const        char* lhs, const std::string& rhs){ return sstd::charIn(lhs,         rhs.c_str()); }
bool sstd::charIn(const std::string& lhs, const        char* rhs){ return sstd::charIn(lhs.c_str(), rhs        ); }
bool sstd::charIn(const std::string& lhs, const std::string& rhs){ return sstd::charIn(lhs.c_str(), rhs.c_str()); }

bool sstd::charIn_all(const        char* lhs, const        char* rhs){
    int l_len=strlen(lhs);
    std::vector<bool> vUsed(l_len, false);
    
    for(uint ri=0; rhs[ri]!='\0'; ++ri){
        for(uint li=0; lhs[li]!='\0'; ++li){
            if(rhs[ri]==lhs[li]){
                if(!vUsed[li]){ --l_len; }
                vUsed[li] = true;
                if(l_len==0){ return true; }
            }
        }
    }
    return false;
}
bool sstd::charIn_all(const        char* lhs, const std::string& rhs){ return sstd::charIn_all(lhs,         rhs.c_str()); }
bool sstd::charIn_all(const std::string& lhs, const        char* rhs){ return sstd::charIn_all(lhs.c_str(), rhs        ); }
bool sstd::charIn_all(const std::string& lhs, const std::string& rhs){ return sstd::charIn_all(lhs.c_str(), rhs.c_str()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// strIn()

bool sstd::strIn(const char* lhs, const char* rhs){ // Is lhs in rhs ?
    if(lhs[0]=='\0'){ return true; }
    
    bool ret=true;
    uint l=0, r=0;
    for(; rhs[r]!='\0'; ++r){
        if(sstd::startswith(&rhs[r], lhs)){ return true; }
    }
    return false;
}
bool sstd::strIn(const char*        lhs, const std::string& rhs){ return sstd::strIn(lhs        , rhs.c_str()); }
bool sstd::strIn(const std::string& lhs, const char*        rhs){ return sstd::strIn(lhs.c_str(), rhs        ); }
bool sstd::strIn(const std::string& lhs, const std::string& rhs){ return sstd::strIn(lhs.c_str(), rhs.c_str()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
