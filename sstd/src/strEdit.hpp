#include "typeDef.h"
#include <string>
#include <vector>

namespace sstd{
	std::vector<uint8>       readAll_bin(const char*        pReadFile); // read all of the file as a binary
	std::vector<uint8>       readAll_bin(const std::string&  readFile); // read all of the file as a binary
	
	bool                     writeAll_bin(const char*        pWritePath, std::vector<uint8>& rhs);
	bool                     writeAll_bin(const std::string&  writePath, std::vector<uint8>& rhs);
	
	std::string              readAll(const char*        pReadFile); // readAll_str()
	std::string              readAll(const std::string&  readFile); // readAll_str()
	std::string              readAll_withoutBOM(const char*        pReadFile);
	std::string              readAll_withoutBOM(const std::string&  readFile);
	std::vector<std::string> splitByLine(const std::string& str);
	
	std::vector<std::string> split(const char*        str, const char X);
	std::vector<std::string> split(const std::string& str, const char X);
	
	std::string              removeHeadSpace(const uchar* str);
	void                     removeTailSpace(std::string& str);
	std::string              removeSpace_of_HeadAndTail(const uchar* str);
	std::vector<std::string> removeSpace_of_HeadAndTail(const std::vector<std::string>& vec);
	
	bool strcmp(const char*        str1, const char*        str2);
	bool strcmp(const char*        str1, const std::string& str2);
	bool strcmp(const std::string& str1, const char*        str2);
	bool strcmp(const std::string& str1, const std::string& str2);
}

