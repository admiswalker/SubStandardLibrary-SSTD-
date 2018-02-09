#include "./tinyInterpreter.hpp"
#include "./file.hpp"
#include "./pdbg.hpp"
#include "./path.hpp"
#include "./strEdit.hpp"

/*
 * bug
 * 
 * cmd01, "cmd0 2" a,      , cmd04;
 * ->
 *   □ getCommandList & splitByComma
 * [cmd01] [" cmd0 2"a] [     ] [cmd04]
 */

void go2nextLine(uchar*& str, uint& r){
	//・改行コード (CR: 0x0D, LF: 0x0A)
	//  - LF: Unix
	//  - CR+LF: Windows
	for(; str[r]!=0; r++){
		if(str[r]==0x0A){ break; }							// Uinx
		if(str[r]==0x0D && str[r+1]==0x0A){ r++; break; }	// Windows
	}
}
void go2asteriskSlash(struct debugInformation& dbgInf, uchar*& str, uint& r){
	uint preLineNum = dbgInf.LineNum;
	for(; str[r]!=0; ){
		if(str[r]=='*' && str[r+1]=='/'){ r++; break; }
		if(str[r]==0x0A                  ){      dbgInf.LineNum++; }	// Line feed code (Linux)
		if(str[r]==0x0D && str[r+1]==0x0A){ r++; dbgInf.LineNum++; }	// erase Line feed code (Windows)
		r++;
	}
	if(str[r]==0){ printf("ERROR: %s: Line(%u): Comment command of \"/**/\" is not closed. (\"*/\" is required).\n", dbgInf.FileName.c_str(), preLineNum); exit(0); }
}
void go2doubleQuotation(struct debugInformation& dbgInf, std::string& token, uchar*& str, uint& r){
	token += str[r];
	r++;
	for(; str[r]!=0; r++){
		token += str[r];
		if(str[r]=='"'){ break; }

		if(str[r]==0x0D && str[r+1]==0x0A){ r++; }	// Line feed code (Windows): ignore '0x0D'
		if(str[r]==0x0A){							// Line feed code (Unix)
			if(token.size()!=0){ printf("ERROR: %s: Line(%u): Indentation is invalid during '\"\"' command.\n", dbgInf.FileName.c_str(), dbgInf.LineNum); exit(0); }
			dbgInf.LineNum++;
			continue;
		}
	}
	if(str[r]==0){ printf("ERROR: %s: Line(%u): Command of '\"\"' is not closed. ('\"' is required).\n", dbgInf.FileName.c_str(), dbgInf.LineNum); exit(0); }
}
std::vector<std::string> removeComment(struct debugInformation& dbgInf, uchar* str){

	// r: read place
	uint r=0;

	std::vector<std::string> cmdList;
	std::string token;
	for(; str[r]!=0; r++){
		if(str[r]=='/'){
			// r に文字が挿入されている場合，r+1 には最悪でも終端コードが確保されているはずなので，一々確認する必要はない．
			      if(str[r+1]=='/'){ r+=2; go2nextLine(str, r); dbgInf.LineNum++; continue;	// Comment command of "//".
			}else if(str[r+1]=='*'){ r+=2; go2asteriskSlash(dbgInf, str, r); continue; }	// Comment command of "/**/".
		}
		if(str[r]=='"'){ go2doubleQuotation(dbgInf, token, str, r); continue; }				// Command of '""'.
		if(str[r]==' '){ continue; }														// erase Space

		if(str[r]==';'){	// ";" により分割されている命令をおのおの格納する．
			token += str[r];
			cmdList.push_back(std::move(token));
			token.clear();	// サイズを 0 にする．(メモリは解放されない．)
			continue;
		}
		if(str[r]==0x0D && str[r+1]==0x0A){ r++; }											// Line feed code (Windows): ignore '0x0D'
		if(str[r]==0x0A){																	// Line feed code (Unix)
			if(token.size()!=0){ printf("ERROR: %s: Line(%u): Invalid token '%s'. (Perhaps, you need to add ';' at the end of the command.)\n", dbgInf.FileName.c_str(), dbgInf.LineNum, token.c_str()); exit(0); }
			dbgInf.LineNum++;
			continue;
		}
		token += str[r];
	}
	return cmdList;
}


std::vector<std::string> sstd::getCommandList(const char* pReadFile){
	std::string str = sstd::readAll_withoutBOM(pReadFile);

	struct debugInformation dbgInf;
	dbgInf.FileName = sstd::getFileName(pReadFile);
	dbgInf.LineNum  = 1;

	return removeComment(dbgInf, (uchar*)str.c_str());	// uchar にキャストしないと，負の値が入力された場合に，比較演算が正常に機能しない．(例えば，0xFF は，0xFFFFFFFF のように，4 Byte 値として扱われるため，if(str[0]==0xFF)... としても必ず false となる．)
}


std::vector<std::string> sstd::splitByComma(const std::string& str){
	std::vector<std::string> result;
	std::string token;
	for(uint i=0; str[i]!=0; i++){
		if(str[i]==',' || str[i]==';'){
			result.push_back(std::move(token));
			token.clear();
			continue;
		}
//		if(str[i]=='"'){ continue; }
		token += str[i];
	}
	return result;
}
