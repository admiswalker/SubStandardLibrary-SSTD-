#pragma once
#include <vector>
#include <string>

namespace sstd{
	std::vector<std::vector<std::string>> csv2vvec(const char* pReadFile); // vvec is always row-major.
	bool vvec2csv(const char* pSavePath, const std::vector<std::vector<std::string>>& vecCSV);
}

