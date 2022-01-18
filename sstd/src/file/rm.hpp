﻿#pragma once
#include <string>
#include <vector>

namespace sstd{
    struct pathAndType_tmp{
        std::string path;
        char type;        // 'f': file, 'd': directory
    };
    
    bool unlink(const char*        pPath); // delete file
    bool unlink(const std::string&  path); // delete file

    bool rmdir (const char*        pPath); // delete empty directory
    bool rmdir (const std::string&  path); // delete empty directory

    bool rm    (const char*        pPath); // delete all under the pPath
    bool rm    (const std::string&  path); // delete all under the path
}
