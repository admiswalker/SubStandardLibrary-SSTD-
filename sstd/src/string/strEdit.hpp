﻿#pragma once

#include "../definitions/typeDef.h"
#include <string>
#include <vector>

namespace sstd{
    bool extract_quoted(std::vector<std::string>& ret, const        char* str);
    bool extract_quoted(std::vector<std::string>& ret, const std::string& str);
    bool extract_unquoted(std::string& ret, const        char* str);
    bool extract_unquoted(std::string& ret, const std::string& str);
    
    //---
    
    std::vector<std::string> splitByLine(const        char* str);
    std::vector<std::string> splitByLine(const std::string& str);
    bool splitByLine_quotes(std::vector<std::string>& ret, const        char* str);
    bool splitByLine_quotes(std::vector<std::string>& ret, const std::string& str);

    std::vector<std::string> split(const char*        str);
    std::vector<std::string> split(const std::string& str);
    std::vector<std::string> split(const char*        str, int maxsplit);
    std::vector<std::string> split(const std::string& str, int maxsplit);
    
    std::vector<std::string> split(const char*        str, const char X);
    std::vector<std::string> split(const std::string& str, const char X);
//    std::vector<std::string> split(const char*        str, const char X, int maxsplit); // TODO
//    std::vector<std::string> split(const std::string& str, const char X, int maxsplit); // TODO
    
    std::vector<std::string> split(const char*        str, const char*        X);
    std::vector<std::string> split(const std::string& str, const std::string& X);
//    std::vector<std::string> split(const char*        str, const char*        X, int maxsplit); // TODO
//    std::vector<std::string> split(const std::string& str, const std::string& X, int maxsplit); // TODO
    
    std::vector<std::string> splitAll       (const char*        str, const char*        X);
    std::vector<std::string> splitAll       (const std::string& str, const char*        X);
    std::vector<std::string> splitAll       (const char*        str, const std::string& X);
    std::vector<std::string> splitAll       (const std::string& str, const std::string& X);
    std::vector<std::string> splitAll_tight(const char*        str, const char*        X);
    std::vector<std::string> splitAll_tight(const std::string& str, const char*        X);
    std::vector<std::string> splitAll_tight(const char*        str, const std::string& X);
    std::vector<std::string> splitAll_tight(const std::string& str, const std::string& X);
    
    std::vector<std::string> split_rmSpace(const char*        str);               // rm: remove
    std::vector<std::string> split_rmSpace(const std::string& str);               // rm: remove
    std::vector<std::string> split_rmSpace(const char*        str, const char X); // rm: remove
    std::vector<std::string> split_rmSpace(const std::string& str, const char X); // rm: remove

    bool split_quotes(std::vector<std::string>& ret, const        char* str);
    bool split_quotes(std::vector<std::string>& ret, const std::string& str);
    bool split_quotes(std::vector<std::string>& ret, const        char* str, const char X);
    bool split_quotes(std::vector<std::string>& ret, const std::string& str, const char X);
    bool split_quotes(std::vector<std::string>& ret, const        char* str, const char*        X);
    bool split_quotes(std::vector<std::string>& ret, const std::string& str, const std::string& X);

    //---
    
    // remove space or tab.
    std::string              lstrip   (const                    char * str); // removing head tab and spaces
    std::string              lstrip   (const             std::string & str); // removing head tab and spaces
    std::vector<std::string> lstrip   (const std::vector<std::string>& vec); // removing tail tab and spaces
    void                     lstrip_ow(                  std::string & str); // removing head tab and spaces. ow: overwrite
    void                     lstrip_ow(      std::vector<std::string>& vec); // removing tail tab and spaces. ow: overwrite
    std::string              rstrip   (const                    char * str); // removing tail tab and spaces
    std::string              rstrip   (const             std::string & str); // removing tail tab and spaces
    std::vector<std::string> rstrip   (const std::vector<std::string>& vec); // removing tail tab and spaces
    void                     rstrip_ow(                  std::string & str); // removing tail tab and spaces. ow: overwrite
    void                     rstrip_ow(      std::vector<std::string>& vec); // removing tail tab and spaces. ow: overwrite
    std::string               strip   (const                    char * str); // removing head and tail tab and spaces
    std::string               strip   (const             std::string & str); // removing head and tail tab and spaces
    std::vector<std::string>  strip   (const std::vector<std::string>& vec); // -> strip(str) // removing head and tail spaces
    void                      strip_ow(                  std::string & str); // removing head and tail tab and spaces. ow: overwrite
    void                      strip_ow(      std::vector<std::string>& vec); // -> strip(str) // removing head and tail spaces
    
    std::string              lstrip   (const        char* str, const char c);
    std::string              lstrip   (const std::string& str, const char c);
    void                     lstrip_ow(      std::string& str, const char c);
    std::string              rstrip   (const        char* str, const char c);
    std::string              rstrip   (const std::string& str, const char c);
    void                     rstrip_ow(      std::string& str, const char c);
    std::string               strip   (const        char* str, const char c);
    std::string               strip   (const std::string& str, const char c);
    void                      strip_ow(      std::string& str, const char c);
    
    std::string               stripAll   (const        char* str, const        char  c        );
    std::string               stripAll   (const std::string& str, const        char  c        );
    void                      stripAll_ow(      std::string& str, const        char  c        );
    
    std::string               stripAll   (const        char* str, const        char* stripList);
    std::string               stripAll   (const std::string& str, const        char* stripList);
    std::string               stripAll   (const        char* str, const std::string& stripList);
    std::string               stripAll   (const std::string& str, const std::string& stripList);

    void                     lstripAll_ow(      std::string& str, const        char* stripList);
    void                     lstripAll_ow(      std::string& str, const std::string& stripList);
    void                     rstripAll_ow(      std::string& str, const        char* stripList);
    void                     rstripAll_ow(      std::string& str, const std::string& stripList);
    void                      stripAll_ow(      std::string& str, const        char* stripList);
    void                      stripAll_ow(      std::string& str, const std::string& stripList);
    // todo: rm '\t'
    // todo: implementing memcopy version. Ref: https://postd.cc/how-quickly-can-you-remove-spaces-from-a-string/
    
    std::string strip_quotes(                            const        char* str);
    std::string strip_quotes(                            const std::string& str);
    std::string strip_quotes(bool& ret_sq, bool& ret_dq, const        char* str); // _sq: single quatation, _dq: double quotation
    std::string strip_quotes(bool& ret_sq, bool& ret_dq, const std::string& str); // _sq: single quatation, _dq: double quotation
    
    //---
    
    std::string join(const std::vector<std::string>& v, const        char  delimiter);
    std::string join(const std::vector<std::string>& v, const        char* delimiter);
    std::string join(const std::vector<std::string>& v, const std::string& delimiter);
}
