#pragma once
#include <string>
#include <vector>
#include "string/ssprintf.hpp"

namespace sstd{
    int str2int(const        char* rhs); // 小数点以下，切り捨て
    int str2int(const std::string& rhs); // 小数点以下，切り捨て
    
                            double   str2double(const                         std::string  & rhs);
                std::vector<double>  str2double(const             std::vector<std::string> & rhs);
    std::vector<std::vector<double>> str2double(const std::vector<std::vector<std::string>>& rhs);
    
    //---
    
//    std::string int2str(const int& rhs);
    
                            std::string   double2str(const                         double  & rhs);
                std::vector<std::string>  double2str(const             std::vector<double> & rhs);
    std::vector<std::vector<std::string>> double2str(const std::vector<std::vector<double>>& rhs);
}
