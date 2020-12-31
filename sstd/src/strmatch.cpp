#include <algorithm> // for std::reverse
#include "strmatch.hpp"
#include "./typeDef.h"

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
//*
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
//*/

bool sstd::isNum               (char rhs){ return ('0'<=rhs && rhs<='9'); }
bool sstd::isAlphabet          (char rhs){ return ('a'<=rhs && rhs<='z') || ('A'<=rhs && rhs<='Z'); }
bool sstd::isAlphabet_onlyUpper(char rhs){ return ('A'<=rhs && rhs<='Z'); }
bool sstd::isAlphabet_onlyLower(char rhs){ return ('a'<=rhs && rhs<='z'); }

