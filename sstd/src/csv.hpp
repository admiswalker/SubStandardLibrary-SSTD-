#pragma once
#include <vector>
#include <string>

namespace sstd{
    std::vector<std::vector<std::string>> csv2vvec(const        char* pReadFile); // vvec is always row-major.
    std::vector<std::vector<std::string>> csv2vvec(const std::string&  readFile);
    
    bool vvec2csv(const       char* pSavePath, const std::vector<std::vector<std::string>>& vecCSV);
    bool vvec2csv(const std::string& savePath, const std::vector<std::vector<std::string>>& vecCSV);
}

