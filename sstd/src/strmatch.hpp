#pragma once
#include <string>

namespace sstd{
    bool strmatch(
        const char* str,     // target string to search
        const char* wildCard // wild card ('*' and '?' are available.)
    );
    bool strmatch(const        char* str, const std::string& wildCard);
    bool strmatch(const std::string& str, const        char* wildCard);
    bool strmatch(const std::string& str, const std::string& wildCard);
    
    bool strmatch_getWC(
        const char* str,      // target string to search
        const char* wildCard, // wild card ('*' and '?' are available.)
        std::string& retWC    // returning a string that matches the wild card
    );
    bool strmatch_getWC(const        char* str, const std::string& wildCard, std::string& retWC);
    bool strmatch_getWC(const std::string& str, const        char* wildCard, std::string& retWC);
    bool strmatch_getWC(const std::string& str, const std::string& wildCard, std::string& retWC);
    
    bool isNum               (char rhs);
    bool isAlphabet          (char rhs);
    bool isAlphabet_onlyUpper(char rhs);
    bool isAlphabet_onlyLower(char rhs);
}
