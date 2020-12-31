#pragma once
#include <string>

namespace sstd{
    bool strmatch(
        const char* str,     // target string to search
        const char* wildCard // wild card ('*' and '?' are available.)
    );
    bool strmatch_getWC(
        const char* str,      // target string to search
        const char* wildCard, // wild card ('*' and '?' are available.)
        std::string& retWC    // returning a string that matches the wild card
    );

    bool isNum               (char rhs);
    bool isAlphabet          (char rhs);
    bool isAlphabet_onlyUpper(char rhs);
    bool isAlphabet_onlyLower(char rhs);
}
