#pragma once

#include <vector>
#include <string>

namespace sstd{
    std::vector<std::string> glob_f     (const        char* path); // Because of under construction, this function does not work exactly same as the normal glob function.
    std::vector<std::string> glob_f     (const std::string& path); // Because of under construction, this function does not work exactly same as the normal glob function.
//    std::vector<std::string> glob_escape(const        char* path);
//    std::vector<std::string> glob_escape(const std::string& path);
}

