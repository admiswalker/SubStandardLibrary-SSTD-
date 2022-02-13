#pragma once
#include <string>


namespace sstd{
    /*
    bool mv  (const char*        pPath_src, const char*        pPath_dst, const char* opt);
    bool mv  (const std::string&  path_src, const char*        pPath_dst, const char* opt);
    bool mv  (const char*        pPath_src, const std::string&  path_dst, const char* opt);
    bool mv  (const std::string&  path_src, const std::string&  path_dst, const char* opt);
    */
    bool mv  (const char*        pPath_src, const char*        pPath_dst);
    bool mv  (const std::string&  path_src, const char*        pPath_dst);
    bool mv  (const char*        pPath_src, const std::string&  path_dst);
    bool mv  (const std::string&  path_src, const std::string&  path_dst);
}
