#pragma once

#include "../definitions/typeDef.h"
#include <string>
#include <vector>

namespace sstd{
    std::vector<std::string> splitByLine(const        char* str);
    std::vector<std::string> splitByLine(const std::string& str);

    std::vector<std::string> split(const char*        str, const char X);
    std::vector<std::string> split(const std::string& str, const char X);
    
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
    void                      strip_ow(                  std::string & str); // removing head and tail tab and spaces. ow: overwrite
    std::vector<std::string>  strip   (const std::vector<std::string>& vec); // -> strip(str) // removing head and tail spaces
    
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

    void                      stripAll_ow(      std::string& str, const        char* stripList);
    void                      stripAll_ow(      std::string& str, const std::string& stripList);
    // todo: rm '\t'
    // todo: implementing memcopy version. Ref: https://postd.cc/how-quickly-can-you-remove-spaces-from-a-string/
}

