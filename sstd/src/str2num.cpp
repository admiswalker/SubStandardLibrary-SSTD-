#include "str2num.hpp"

double sstd::str2double(const std::string& rhs){ return std::stod(rhs); }
int sstd::str2int(const std::string& rhs){ return std::stoi(rhs); } // 小数点以下，切り捨て

