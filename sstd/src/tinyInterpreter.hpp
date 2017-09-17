#pragma once

#include <vector>
#include <string>
#include "./typeDef.h"


struct debugInformation{
	std::string FileName;
	uint LineNum;
};


namespace sstd{

	// How to use GetCommandList(); function.
	//
	// TinyInterpreter define middle of "/*~*/" and before "//" as a commnet.
	// And a ";" mean the end of command. Return value is the list of command.
	
	std::string readAll(const char* pReadFile);
	std::string readAll_withoutBOM(const char* pReadFile);
	std::vector<std::string> getCommandList(const char* pReadFile);
	std::vector<std::string> splitByComma(const std::string& str);	// str をカンマで分割する
	std::vector<std::string> splitByLine(const std::string& str);
}
