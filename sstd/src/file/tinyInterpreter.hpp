#pragma once

#include <vector>
#include <string>
#include "../definitions/typeDef.h"


struct debugInformation{
    std::string FileName;
    uint LineNum;
};


namespace sstd{

    // How to use txt2vCmdList(); function.
    //
    // TinyInterpreter define middle of "/*~*/" and before "//" as a commnet.
    // And a ";" mean the end of command. Return value is a list of command.
    
    bool _txt2vCmdList(std::vector<uint>& ret_vLineNum, std::vector<std::vector<std::string>>& ret_vCmdList, const char* fileName, const uchar* str); // for test
    
    bool txt2vCmdList(                                 std::vector<std::vector<std::string>>& ret_vCmdList, const        char* pReadFile);
    bool txt2vCmdList(                                 std::vector<std::vector<std::string>>& ret_vCmdList, const std::string&  readFile);
    bool txt2vCmdList(std::vector<uint>& ret_vLineNum, std::vector<std::vector<std::string>>& ret_vCmdList, const        char* pReadFile);
    bool txt2vCmdList(std::vector<uint>& ret_vLineNum, std::vector<std::vector<std::string>>& ret_vCmdList, const std::string&  readFile);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Below functions are the not recommended to use. (Below functions will be delete on sstd ver 3.x.x).

namespace sstd{
    
    // How to use getCommandList(); function.
    //
    // TinyInterpreter define middle of "/*~*/" and before "//" as a commnet.
    // And a ";" mean the end of command. Return value is a list of command.
    
    std::vector<std::string> getCommandList(const        char* pReadFile);
    std::vector<std::string> getCommandList(const std::string&  readFile);
    std::vector<std::string> splitByComma(const std::string& str);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
