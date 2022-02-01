#pragma once
#include <string>


namespace sstd{
    bool copy(const char*        pPath_src, const char*        pPath_dst, const char* opt);
    bool copy(const char*        pPath_src, const char*        pPath_dst);
    bool copy(const std::string&  path_src, const char*        pPath_dst);
    bool copy(const char*        pPath_src, const std::string&  path_dst);
    bool copy(const std::string&  path_src, const std::string&  path_dst);
    
    bool cp  (const char*        pPath_src, const char*        pPath_dst, const char* opt);
    bool cp  (const char*        pPath_src, const char*        pPath_dst);
    bool cp  (const std::string&  path_src, const char*        pPath_dst);
    bool cp  (const char*        pPath_src, const std::string&  path_dst);
    bool cp  (const std::string&  path_src, const std::string&  path_dst);
}
