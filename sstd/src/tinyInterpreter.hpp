#pragma once

#include <vector>
#include <string>
#include "./typeDef.h"


struct debugInformation{
	std::string FileName;
	uint LineNum;
};


namespace sstd{

	// How to use getCommandList(); function.
	//
	// TinyInterpreter define middle of "/*~*/" and before "//" as a commnet.
	// And a ";" mean the end of command. Return value is a list of command.
	
	std::vector<std::string> getCommandList(const char* pReadFile);
	std::vector<std::string> splitByComma(const std::string& str);	// str をカンマで分割する
}
