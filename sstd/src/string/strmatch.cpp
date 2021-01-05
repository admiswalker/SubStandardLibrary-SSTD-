#include <algorithm> // for std::reverse
#include <string.h> // for ::strcmp()

#include "./strmatch.hpp"
#include "../typeDef.h"


//--------------------------------------------------------------------------------------------------------
// strmatch()

bool sstd::strmatch(
        const char* str,     // target string to search
        const char* wildCard // wild card ('*' and '?' are available.)
){
    if      (*wildCard=='\0'){ return '\0' == *str;
    }else if(*wildCard=='*' ){ return strmatch(str, wildCard+1) || (('\0' != *str) && strmatch(str+1, wildCard));
    }else if(*wildCard=='?' ){ return ('\0' != *str) && strmatch(str+1, wildCard+1);
    }          else          { return ((uchar)*wildCard == (uchar)*str) && strmatch(str+1, wildCard+1);
    }
}
bool sstd::strmatch(const        char* str, const std::string& wildCard){ return sstd::strmatch(str        , wildCard.c_str()); }
bool sstd::strmatch(const std::string& str, const        char* wildCard){ return sstd::strmatch(str.c_str(), wildCard        ); }
bool sstd::strmatch(const std::string& str, const std::string& wildCard){ return sstd::strmatch(str.c_str(), wildCard.c_str()); }

//--------------------------------------------------------------------------------------------------------
// strmatch_getWC()

/*
bool getWC_entity(
        const char* str,      // target string to search
        const char* wildCard, // wild card ('*' and '?' are available.)
        std::string& retWC    // returning a string that matches the wild card
){
    if(*wildCard=='\0'){
        return '\0' == *str;
        
    }else if(*wildCard=='*'){
        bool retL = getWC_entity(str, wildCard+1, retWC);
        bool retR = (('\0' != *str) && getWC_entity(str+1, wildCard, retWC));
        if(retR && '\0'!=*str){ retWC += *str; }
        return retL || retR;
        
    }else if(*wildCard=='?'){
        bool ret = ('\0' != *str) && getWC_entity(str+1, wildCard+1, retWC);
        if(ret && '\0'!=*str){ retWC += *str; }
        return ret;
        
    }else{
        return ((uchar)*wildCard == (uchar)*str) && getWC_entity(str+1, wildCard+1, retWC);
    }
}
bool sstd::strmatch_getWC(
        const char* str,      // target string to search
        const char* wildCard, // wild card ('*' and '?' are available.)
        std::string& retWC    // returning a string that matches the wild card
){
    retWC.clear();
    bool ret = getWC_entity(str, wildCard, retWC);
    if(!ret){ retWC.clear(); }
    
    std::reverse(retWC.begin(), retWC.end());
    return ret;
}
// This code is optimized like below code. (removing std::reverse()).

//*/

bool getWC_entity(
        const char* str,      // target string to search
        const char* wildCard, // wild card ('*' and '?' are available.)
        std::string& retWC    // returning a string that matches the wild card
){
    if(*wildCard=='\0'){
        return '\0' == *str;
        
    }else if(*wildCard=='*'){
        bool retL = getWC_entity(str, wildCard+1, retWC);
        
        if('\0'!=*str){ retWC += *str; }
        bool retR = (('\0' != *str) && getWC_entity(str+1, wildCard, retWC));
        if(!retR && '\0'!=*str){ retWC.erase(--retWC.end()); }
        
        return retL || retR;
        
    }else if(*wildCard=='?'){
        if('\0'!=*str){ retWC += *str; }
        bool ret = ('\0' != *str) && getWC_entity(str+1, wildCard+1, retWC);
        if(!ret && '\0'!=*str){ retWC.erase(--retWC.end()); }
        return ret;
        
    }else{
        return ((uchar)*wildCard == (uchar)*str) && getWC_entity(str+1, wildCard+1, retWC);
    }
}
bool sstd::strmatch_getWC(
        const char* str,      // target string to search
        const char* wildCard, // wild card ('*' and '?' are available.)
        std::string& retWC    // returning a string that matches the wild card
){
    retWC.clear();
    bool ret = getWC_entity(str, wildCard, retWC);
    if(!ret){ retWC.clear(); }
    return ret;
}

bool sstd::strmatch_getWC(const        char* str, const std::string& wildCard, std::string& retWC){ return sstd::strmatch_getWC(str        , wildCard.c_str(), retWC); }
bool sstd::strmatch_getWC(const std::string& str, const        char* wildCard, std::string& retWC){ return sstd::strmatch_getWC(str.c_str(), wildCard        , retWC); }
bool sstd::strmatch_getWC(const std::string& str, const std::string& wildCard, std::string& retWC){ return sstd::strmatch_getWC(str.c_str(), wildCard.c_str(), retWC); }

//--------------------------------------------------------------------------------------------------------

bool sstd::isNum               (char rhs){ return ('0'<=rhs && rhs<='9'); }
bool sstd::isAlphabet          (char rhs){ return ('a'<=rhs && rhs<='z') || ('A'<=rhs && rhs<='Z'); }
bool sstd::isAlphabet_onlyUpper(char rhs){ return ('A'<=rhs && rhs<='Z'); }
bool sstd::isAlphabet_onlyLower(char rhs){ return ('a'<=rhs && rhs<='z'); }

//--------------------------------------------------------------------------------------------------------
// strcmp()

bool sstd::strcmp(const char*        str1, const char*        str2){ return (::strcmp(str1,         str2        )==0); }
bool sstd::strcmp(const char*        str1, const std::string& str2){ return (::strcmp(str1,         str2.c_str())==0); }
bool sstd::strcmp(const std::string& str1, const char*        str2){ return (::strcmp(str1.c_str(), str2        )==0); }
bool sstd::strcmp(const std::string& str1, const std::string& str2){ return (::strcmp(str1.c_str(), str2.c_str())==0); }

//--------------------------------------------------------------------------------------------------------
// charIn()

bool sstd::charIn(const char lhs, const char* rhs){ // Is lhs in rhs ?
    for(uint i=0; rhs[i]!='\0'; ++i){
        if(rhs[i]==lhs){ return true; }
    }
    return false;
}
bool sstd::charIn(const char lhs, const std::string& rhs){ return sstd::charIn(lhs, rhs.c_str()); }

//--------------------------------------------------------------------------------------------------------
// strIn()

bool sstd::strIn(const char* lhs, const char* rhs){ // Is lhs in rhs ?
    bool ret=true;
    uint l=0, r=0;
    for(;;){
        if(lhs[l]=='\0'){ return ret;   }
        if(rhs[r]=='\0'){ return false; }
        
        if(lhs[l]==rhs[r]){ ++l; ret=true;
        }       else      { l=0; ret=false; }
        
        ++r;
    }
}
bool sstd::strIn(const char*        lhs, const std::string& rhs){ return sstd::strIn(lhs        , rhs.c_str()); }
bool sstd::strIn(const std::string& lhs, const char*        rhs){ return sstd::strIn(lhs.c_str(), rhs        ); }
bool sstd::strIn(const std::string& lhs, const std::string& rhs){ return sstd::strIn(lhs.c_str(), rhs.c_str()); }

//--------------------------------------------------------------------------------------------------------
