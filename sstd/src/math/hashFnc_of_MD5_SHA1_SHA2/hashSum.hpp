#pragma once

#include "../../definitions/typeDef.h"
#include <string>
#include <vector>


namespace sstd{
    std::string vecUint8_to_hexString(const std::vector<uint8>& hash);
    
    std::string md5sum   (const char*        pPath);
    std::string sha1sum  (const char*        pPath);
    std::string sha224sum(const char*        pPath);
    std::string sha256sum(const char*        pPath);
    std::string sha384sum(const char*        pPath);
    std::string sha512sum(const char*        pPath);
    
    std::string md5sum   (const std::string&  path);
    std::string sha1sum  (const std::string&  path);
    std::string sha224sum(const std::string&  path);
    std::string sha256sum(const std::string&  path);
    std::string sha384sum(const std::string&  path);
    std::string sha512sum(const std::string&  path);
}
