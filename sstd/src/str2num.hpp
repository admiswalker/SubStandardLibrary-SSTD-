#pragma once
#include <string>

namespace sstd{
	double str2double(const std::string& rhs);
	int str2int(const std::string& rhs); // 小数点以下，切り捨て
}
