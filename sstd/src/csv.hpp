#pragma once
#include <vector>
#include <string>

namespace sstd{
//	std::vector<std::vector<std::string>> csvPath2vvec_c(const char* pReadFile); // _c: col-major
	std::vector<std::vector<std::string>> csvPath2vvec_r(const char* pReadFile); // _r: row-major
}

