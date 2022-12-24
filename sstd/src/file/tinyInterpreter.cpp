#include "tinyInterpreter.hpp"

#include "read_write.hpp"
#include "path.hpp"
#include "../print/pdbg.hpp"
#include "../string/strEdit.hpp"

/*
 * bug
 * 
 * cmd01, "cmd0 2" a,      , cmd04;
 * ->
 *   □ getCommandList & splitByComma
 * [cmd01] [" cmd0 2"a] [     ] [cmd04]
 */

void go2nextLine(const uchar*& str, uint& r){
    //・改行コード (CR: 0x0D, LF: 0x0A)
    //  - LF: Unix
    //  - CR+LF: Windows
    for(; str[r]!=0; ++r){
        if(str[r]=='\n'                  ){      break; } // Uinx
        if(str[r]=='\r' && str[r+1]=='\n'){ ++r; break; } // Windows
    }
}
bool go2asteriskSlash(struct debugInformation& dbgInf, const uchar*& str, uint& r){
    uint preLineNum = dbgInf.LineNum;
    for(; str[r]!=0; ){
        if(str[r]=='*' && str[r+1]=='/'){ ++r; break; }
        if(str[r]=='\n'                  ){      ++dbgInf.LineNum; }    // Line feed code (Linux)
        if(str[r]=='\r' && str[r+1]=='\n'){ ++r; ++dbgInf.LineNum; }    // erase Line feed code (Windows)
        ++r;
    }
    if(str[r]==0){ printf("ERROR: %s: Line(%u): Comment command of \"/**/\" is not closed. (\"*/\" is required).\n", dbgInf.FileName.c_str(), preLineNum); return false; }
    return true;
}
bool go2doubleQuotation(struct debugInformation& dbgInf, std::string& token, const uchar*& str, uint& r){
    token += str[r];
    ++r;
    for(; str[r]!=0; ++r){
        token += str[r];
        if(str[r]=='"'){ break; }

        if(str[r]=='\r' && str[r+1]=='\n'){ ++r; } // Line feed code (Windows): ignore '0x0D'
        if(str[r]=='\n'){                          // Line feed code (Unix)
            if(token.size()!=0){ printf("ERROR: %s: Line(%u): Indentation is invalid during '\"\"' command.\n", dbgInf.FileName.c_str(), dbgInf.LineNum); return false; }
            ++dbgInf.LineNum;
            continue;
        }
    }
    if(str[r]==0){ printf("ERROR: %s: Line(%u): Command of '\"\"' is not closed. ('\"' is required).\n", dbgInf.FileName.c_str(), dbgInf.LineNum); return false; }
    return true;
}
bool _txt2vLine(std::vector<uint>& ret_vLineNum, std::vector<std::string>& ret_vLine, const char* fileName, const uchar* str){
    
    struct debugInformation dbgInf;
    dbgInf.FileName = fileName;
    dbgInf.LineNum  = 1;
    
    // r: read place
    uint r=0;
    
    std::string token;
    bool ret=true;
    for(; str[r]!=0; ++r){
        if(!ret){ return false; }
        if(str[r]=='/'){
            // r に文字が挿入されている場合，r+1 には最悪でも終端コードが確保されているはずなので，一々確認する必要はない．
            if      (str[r+1]=='/'){ r+=2; go2nextLine(str, r); ++dbgInf.LineNum; continue;   // Comment command of "//".
            }else if(str[r+1]=='*'){ r+=2; ret=go2asteriskSlash(dbgInf, str, r);  continue; } // Comment command of "/**/".
        }
        if(str[r]=='"'){ ret=go2doubleQuotation(dbgInf, token, str, r); continue; }           // Command of '""'.
        if(str[r]==' '){ continue; }                                                          // erase Space
        
        if(str[r]==';'){   // ";" により分割されている命令をおのおの格納する．
            token += str[r];
            ret_vLine.push_back(std::move(token));
            ret_vLineNum.push_back(dbgInf.LineNum);
            token.clear(); // サイズを 0 にする．(メモリは解放されない．)
            continue;
        }
        if(str[r]=='\r' && str[r+1]=='\n'){ ++r; }                                            // Line feed code (Windows): ignore '0x0D'
        if(str[r]=='\n'){                                                                     // Line feed code (Unix)
            if(token.size()!=0){ printf("ERROR: %s: Line(%u): Invalid token '%s'. (Perhaps, you need to add ';' at the end of the command.)\n", dbgInf.FileName.c_str(), dbgInf.LineNum, token.c_str()); ret=false; continue; }
            ++dbgInf.LineNum;
            continue;
        }
        token += str[r];
    }
    return true;
}
bool sstd::_txt2vCmdList(std::vector<uint>& ret_vLineNum, std::vector<std::vector<std::string>>& ret_vCmdList, const char* fileName, const uchar* str){
    ret_vCmdList.clear();
    
    std::vector<std::string> v;
    bool ret = _txt2vLine(ret_vLineNum, v, fileName, str);
    
    for(uint i=0; i<v.size(); ++i){
        sstd::rstrip_ow(v[i], ';');
        ret_vCmdList.push_back( std::move(sstd::split(v[i], ',')) );
    }
    return ret;
}
bool _txt2vCmdList_base(std::vector<uint>& ret_vLineNum, std::vector<std::vector<std::string>>& ret_vCmdList, const char* pReadFile){
    std::string std_str; bool ret = sstd::read_woBOM(std_str, pReadFile); if(!ret){ return false; }
    const uchar* str = (const uchar*)std_str.c_str(); // uchar にキャストしないと，負の値が入力された場合に，比較演算が正常に機能しない．(例えば，0xFF は，0xFFFFFFFF のように，4 Byte 値として扱われるため，if(str[0]==0xFF)... としても必ず false となる．)
    return sstd::_txt2vCmdList(ret_vLineNum, ret_vCmdList, sstd::path2fileName(pReadFile), str);
}
bool sstd::txt2vCmdList(std::vector<std::vector<std::string>>& ret_vCmdList, const        char* pReadFile){ std::vector<uint> ret_vLineNum;  return _txt2vCmdList_base(ret_vLineNum, ret_vCmdList, pReadFile        ); }
bool sstd::txt2vCmdList(std::vector<std::vector<std::string>>& ret_vCmdList, const std::string&  readFile){ std::vector<uint> ret_vLineNum;  return _txt2vCmdList_base(ret_vLineNum, ret_vCmdList,  readFile.c_str()); }
bool sstd::txt2vCmdList(std::vector<uint>& ret_vLineNum, std::vector<std::vector<std::string>>& ret_vCmdList, const        char* pReadFile){ return _txt2vCmdList_base(ret_vLineNum, ret_vCmdList, pReadFile        ); }
bool sstd::txt2vCmdList(std::vector<uint>& ret_vLineNum, std::vector<std::vector<std::string>>& ret_vCmdList, const std::string&  readFile){ return _txt2vCmdList_base(ret_vLineNum, ret_vCmdList,  readFile.c_str()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Below functions are the not recommended to use. (Below functions will be delete on sstd ver 3.x.x).

std::vector<std::string> removeComment(struct debugInformation& dbgInf, const uchar* str){

    // r: read place
    uint r=0;

    std::vector<std::string> cmdList;
    std::string token;
    for(; str[r]!=0; ++r){
        if(str[r]=='/'){
            // r に文字が挿入されている場合，r+1 には最悪でも終端コードが確保されているはずなので，一々確認する必要はない．
            if      (str[r+1]=='/'){ r+=2; go2nextLine(str, r); ++dbgInf.LineNum; continue; // Comment command of "//".
            }else if(str[r+1]=='*'){ r+=2; go2asteriskSlash(dbgInf, str, r); continue; }    // Comment command of "/**/".
        }
        if(str[r]=='"'){ go2doubleQuotation(dbgInf, token, str, r); continue; }             // Command of '""'.
        if(str[r]==' '){ continue; }                                                        // erase Space

        if(str[r]==';'){    // ";" により分割されている命令をおのおの格納する．
            token += str[r];
            cmdList.push_back(std::move(token));
            token.clear();    // サイズを 0 にする．(メモリは解放されない．)
            continue;
        }
        if(str[r]==0x0D && str[r+1]==0x0A){ ++r; }                                           // Line feed code (Windows): ignore '0x0D'
        if(str[r]==0x0A){                                                                    // Line feed code (Unix)
            if(token.size()!=0){ printf("ERROR: %s: Line(%u): Invalid token '%s'. (Perhaps, you need to add ';' at the end of the command.)\n", dbgInf.FileName.c_str(), dbgInf.LineNum, token.c_str()); exit(0); }
            ++dbgInf.LineNum;
            continue;
        }
        token += str[r];
    }
    return cmdList;
}


std::vector<std::string> sstd::getCommandList(const char* pReadFile){
    std::string str = sstd::read_withoutBOM(pReadFile);

    struct debugInformation dbgInf;
    dbgInf.FileName = sstd::path2fileName(pReadFile);
    dbgInf.LineNum  = 1;

    return removeComment(dbgInf, (uchar*)str.c_str()); // uchar にキャストしないと，負の値が入力された場合に，比較演算が正常に機能しない．(例えば，0xFF は，0xFFFFFFFF のように，4 Byte 値として扱われるため，if(str[0]==0xFF)... としても必ず false となる．)
}
std::vector<std::string> sstd::getCommandList(const std::string& readFile){ return sstd::getCommandList(readFile.c_str()); }


std::vector<std::string> sstd::splitByComma(const std::string& str){
    std::vector<std::string> result;
    std::string token;
    for(uint i=0; str[i]!=0; ++i){
        if(str[i]==',' || str[i]==';'){
            result.push_back(std::move(token));
            token.clear();
            continue;
        }
//      if(str[i]=='"'){ continue; }
        token += str[i];
    }
    return result;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
