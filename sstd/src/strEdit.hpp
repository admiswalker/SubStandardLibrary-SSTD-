#include "typeDef.h"
#include <string>
#include <vector>

namespace sstd{
	// file exist
	bool fexist(const char*        pCheckFile);
	bool fexist(const std::string&  checkFile);
	
	std::string              readAll(const char* pReadFile);
	std::string              readAll_withoutBOM(const char* pReadFile);
	std::vector<std::string> splitByLine(const std::string& str);
	
	std::vector<std::string> split(const char*        str, const char X);
	std::vector<std::string> split(const std::string& str, const char X);
	
	std::string              removeHeadSpace(const uchar* str);
	void                     removeTailSpace(std::string& str);
	std::string              removeSpace_of_HeadAndTail(const uchar* str);
	std::vector<std::string> removeSpace_of_HeadAndTail(const std::vector<std::string>& vec);
}

