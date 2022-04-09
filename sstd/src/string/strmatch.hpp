#pragma once
#include <string>

namespace sstd{
    bool strcmp(const        char* str1, const        char* str2);
    bool strcmp(const        char* str1, const std::string& str2);
    bool strcmp(const std::string& str1, const        char* str2);
    bool strcmp(const std::string& str1, const std::string& str2);
    
    bool strmatch(const        char* str, const        char* wildcard);
    bool strmatch(const        char* str, const std::string& wildcard);
    bool strmatch(const std::string& str, const        char* wildcard);
    bool strmatch(const std::string& str, const std::string& wildcard);
    
    bool pathmatch(const        char* str, const        char* wildcard);
    bool pathmatch(const        char* str, const std::string& wildcard);
    bool pathmatch(const std::string& str, const        char* wildcard);
    bool pathmatch(const std::string& str, const std::string& wildcard);
    
    bool strmatch_getWC(
        const char* str,      // target string to search
        const char* wildcard, // wild card ('*' and '?' are available.)
        std::string& retWC    // returning a string that matches the wild card
    );
    bool strmatch_getWC(const        char* str, const std::string& wildcard, std::string& retWC);
    bool strmatch_getWC(const std::string& str, const        char* wildcard, std::string& retWC);
    bool strmatch_getWC(const std::string& str, const std::string& wildcard, std::string& retWC);

    bool isNum             (const        char  rhs);
    bool isNum             (const        char* rhs);
    bool isNum             (const std::string& rhs);
    bool isAlphabet       (const        char  rhs);
    bool isAlphabet       (const        char* rhs);
    bool isAlphabet       (const std::string& rhs);
    bool isAlphabet_upper(const        char  rhs);
    bool isAlphabet_upper(const        char* rhs);
    bool isAlphabet_upper(const std::string& rhs);
    bool isAlphabet_lower(const        char  rhs);
    bool isAlphabet_lower(const        char* rhs);
    bool isAlphabet_lower(const std::string& rhs);

    bool charIn(const        char  lhs, const        char* rhs); // Is lhs in rhs ?
    bool charIn(const        char  lhs, const std::string& rhs); // Is lhs in rhs ?
    
    bool charIn(const        char* lhs, const        char* rhs); // Is lhs in rhs ?
    bool charIn(const        char* lhs, const std::string& rhs); // Is lhs in rhs ?
    bool charIn(const std::string& lhs, const        char* rhs); // Is lhs in rhs ?
    bool charIn(const std::string& lhs, const std::string& rhs); // Is lhs in rhs ?
    
    bool charIn_all(const        char* lhs, const        char* rhs); // Is all lhs char(s) in rhs ?
    bool charIn_all(const        char* lhs, const std::string& rhs); // Is all lhs char(s) in rhs ?
    bool charIn_all(const std::string& lhs, const        char* rhs); // Is all lhs char(s) in rhs ?
    bool charIn_all(const std::string& lhs, const std::string& rhs); // Is all lhs char(s) in rhs ?
    
    bool strIn(const char*        lhs, const char*        rhs); // is lhs in rhs ? (is rhs include lhs ?)
    bool strIn(const char*        lhs, const std::string& rhs);
    bool strIn(const std::string& lhs, const char*        rhs);
    bool strIn(const std::string& lhs, const std::string& rhs);
}
