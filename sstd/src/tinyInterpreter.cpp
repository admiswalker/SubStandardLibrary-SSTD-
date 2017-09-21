#include "./tinyInterpreter.hpp"
#include "./file.hpp"
#include "./pdbg.hpp"
#include "./pathNameExtractor.hpp"


std::string sstd::readAll(const char* pReadFile){

	FILE* fp;
	if(!sstd::fopen(&fp, pReadFile, "rb")){ sstd::pdbg_always_stop_exit("fopen was failed.\n"); }

	size_t size;
	fseek(fp, 0, SEEK_END);		//ファイルポインタをファイルの最後に移動させる。
	size = ftell(fp); 			//ファイルサイズを取得する。// fgetpos(fp,&size);
	fseek(fp, 0L, SEEK_SET);	//ファイルポインタを先頭に戻す。

	std::string str(size+1, 0);	//0で初期化	//終端コード分を余分に確保

	if(fread(&str[0], sizeof(char), (size_t)size, fp)!=size){ sstd::pdbg_always_stop_exit("fread was failed.\n"); }
	fclose(fp);

	return str;
}
void ignoreBOM(uchar* str, uint& r){
	if      (str[0]==0xEF && str[1]==0xBB && str[2]==0xBF){ r+=3;                 // UTF-8
	}else if(str[0]==0xFE && str[1]==0xFF){ r+=2;                                 // UTF-16 BE (Big endian): Not compatible with ASCII code
	}else if(str[0]==0xFF && str[1]==0xFE){ r+=2;                                 // UTF-16 LE (Little endian): Not compatible with ASCII code
	}else if(str[0]==0x00 && str[1]==0x00 && str[2]==0xFE && str[3]==0xFF){ r+=4; // UTF-32 BE (Big endian): Not compatible with ASCII code
	}else if(str[0]==0xFF && str[1]==0xFE && str[2]==0x00 && str[3]==0x00){ r+=4; // UTF-32 LE (Little endian): Not compatible with ASCII code
	}else if(str[0]==0x2B && str[1]==0x2F && str[2]==0x76){ r+=3;                 // UTF-7: Not compatible with ASCII code
	}else if(str[0]==0x2B && str[1]==0x2F && str[2]==0x38){ r+=3;                 // UTF-7: Not compatible with ASCII code
	}else if(str[0]==0x2B && str[1]==0x2F && str[2]==0x39){ r+=3;                 // UTF-7: Not compatible with ASCII code
	}else if(str[0]==0x2B && str[1]==0x2F && str[2]==0x2B){ r+=3;                 // UTF-7: Not compatible with ASCII code
	}else if(str[0]==0x2B && str[1]==0x2F && str[2]==0x2F){ r+=3;                 // UTF-7: Not compatible with ASCII code
	}else{
		// UTF-8N (UTF-8 without BOM), 
		// UTF-16BE (UTF-16 without BOM), 
		// UTF-16LE (UTF-32 without BOM), 
		// UTF-32BE (UTF-32 without BOM), 
		// UTF-32LE (UTF-32 without BOM), 
		// or the other encoding.
	}
}
std::string sstd::readAll_withoutBOM(const char* pReadFile){

	FILE* fp;
	if(!sstd::fopen(&fp, pReadFile, "rb")){ sstd::pdbg_always_stop_exit("fopen was failed.\n"); }

	// check BOM (Byte Order Mark)
	uint BOM_len=0;
	uchar check_BOM[4];
	fread(&check_BOM[0], sizeof(uchar), 4, fp);
	ignoreBOM(check_BOM, BOM_len);

	size_t size;
	fseek(fp, 0, SEEK_END);			//ファイルポインタをファイルの最後に移動させる。
	size = ftell(fp) - BOM_len; 	//ファイルサイズを取得する。// fgetpos(fp,&size);
	fseek(fp, BOM_len, SEEK_SET);	//ファイルポインタを先頭 + BOM_len に戻す。

	std::string str(size+1, 0);		//0で初期化	//終端コード分を余分に確保

	if(fread(&str[0], sizeof(char), (size_t)size, fp)!=size){ sstd::pdbg_always_stop_exit("fread was failed.\n"); }
	fclose(fp);

	return str;
}


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
		if(str[r]==0x0A                  ){      dbgInf.LineNum++; }	// erase Line feed code (Windows)
		if(str[r]==0x0D && str[r+1]==0x0A){ r++; dbgInf.LineNum++; }	// erase Line feed code (Linux)
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

		if(str[r]==0x0D && str[r+1]==0x0A){ r++; }	// Line feed code (Unix)
		if(str[r]==0x0A){							// erase Line feed code (Windows)
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

	// Ignore BOM (BOM: byte order mark)
	ignoreBOM(str, r);

	std::vector<std::string> cmdList;
	std::string token;
	for(; str[r]!=0; r++){
		if(str[r]=='/'){
			// r に文字が挿入されている場合，r+1 には最悪でも終端コードが確保されているはずなので，一々確認する必要はない．
			      if(str[r+1]=='/'){ r+=2; go2nextLine(str, r); dbgInf.LineNum++; continue;	// Comment command of "//".
			}else if(str[r+1]=='*'){ r+=2; go2asteriskSlash(dbgInf, str, r); continue; }		// Comment command of "/**/".
		}
		if(str[r]=='"'){ go2doubleQuotation(dbgInf, token, str, r); continue; }				// Command of '""'.
		if(str[r]==' '){ continue; }															// erase Space

		if(str[r]==';'){	// ";" により分割されている命令をおのおの格納する．
			token += str[r];
			cmdList.push_back(token);
			token.clear();	// サイズを 0 にする．(メモリは解放されない．)
			continue;
		}
		if(str[r]==0x0D && str[r+1]==0x0A){ r++; }												// Line feed code (Unix)
		if(str[r]==0x0A){																		// erase Line feed code (Windows)
			if(token.size()!=0){ printf("ERROR: %s: Line(%u): Invalid token '%s'. (Perhaps, you need to add ';' at the end of the command.)\n", dbgInf.FileName.c_str(), dbgInf.LineNum, token.c_str()); exit(0); }
			dbgInf.LineNum++;
			continue;
		}
		token += str[r];
	}
	return cmdList;
}


std::vector<std::string> sstd::getCommandList(const char* pReadFile){
	std::string str = sstd::readAll(pReadFile);

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
			result.push_back(token);
			token.clear();
			continue;
		}
//		if(str[i]=='"'){ continue; }
		token += str[i];
	}
	return result;
}
//===

std::vector<std::string> sstd::splitByLine(const std::string& str){

	std::vector<std::string> ret;
	
	std::string buf;
	for(uint r=0; str[r]!=0; r++){ // r: read place
		buf.clear();
		for(; str[r]!=0; r++){
			if(str[r]==0x0A){ break; }							// Uinx
			if(str[r]==0x0D && str[r+1]==0x0A){ r++; break; }	// Windows
			buf += str[r];
		}
		ret.push_back(buf);
	}
	
	return ret;
}
