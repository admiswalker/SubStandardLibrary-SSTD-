#pragma once

#include "../typeDef.h"
#include <string>
#include <vector>


namespace sstd{
    std::string vecUint8_to_hexString(const std::vector<uint8>& hash);
    
    bool md5sum   (std::string& ret, const char*        pPath);
    bool sha1sum  (std::string& ret, const char*        pPath);
    bool sha224sum(std::string& ret, const char*        pPath);
    bool sha256sum(std::string& ret, const char*        pPath);
    bool sha384sum(std::string& ret, const char*        pPath);
    bool sha512sum(std::string& ret, const char*        pPath);
    
    bool md5sum   (std::string& ret, const std::string&  path);
    bool sha1sum  (std::string& ret, const std::string&  path);
    bool sha224sum(std::string& ret, const std::string&  path);
    bool sha256sum(std::string& ret, const std::string&  path);
    bool sha384sum(std::string& ret, const std::string&  path);
    bool sha512sum(std::string& ret, const std::string&  path);
}
