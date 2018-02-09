#include "./csv.hpp"
#include "./tinyInterpreter.hpp"
#include "./strEdit.hpp"
#include "./path.hpp"


// erasing empty element(s) in the tail of vector
void eraseEmptyTail(std::vector<std::string>& inOut){
	uint cols = inOut.size();
	for(uint p=cols-1; p!=0; p--){
		if(inOut[p].size()==0){ inOut.erase(inOut.begin()+p);
		}         else        { break; }
	}
}
// erasing empty element(s) in the tail of vector
void eraseEmptyTail(std::vector<std::vector<std::string>>& inOut){
	uint rows = inOut.size();
	for(uint p=rows-1; p!=0; p--){
		if(inOut[p].size()==1 && inOut[p][0].size()==0){ inOut.erase(inOut.begin()+p);
		}                    else                      { break; }
	}
}

bool isEmpty(std::string& token, struct debugInformation& dbgInf){
	if(token.size()!=0){
		for(uint i=0; i<token.size(); i++){
			if(token[i]!=' '){ printf("ERROR: %s: Line(%u): There is a invalid value (%c) between ',' and '\"'.\n", dbgInf.FileName.c_str(), dbgInf.LineNum, token[i]); return false; }
		}
	}
	return true;
}
bool go2comma(const uchar*& str, uint& r, struct debugInformation& dbgInf){
	for(; str[r]!=0; r++){
		if(str[r]==','){ break; }
		if(str[r]==0x0D && str[r+1]==0x0A){ r++; break; }	// Line feed code (Windows)
		if(str[r]==0x0A){ break; }							// Line feed code (Unix)
		if(str[r]!=' '){ printf("ERROR: %s: Line(%u): There is a invalid value (%c) between '\"' and ','.\n", dbgInf.FileName.c_str(), dbgInf.LineNum, str[r]); return false; }
	}
	return true;
}
bool go2doubleQuotation(std::string& token, const uchar*& str, uint& r, struct debugInformation& dbgInf){

	if(isEmpty(token, dbgInf)==false){ return false; }
	r++;
	for(; str[r]!=0; r++){
		if(str[r]=='"' && str[r+1]=='"'){ r++; token += str[r]; continue; }	// "" is treated as a escape of ".
		if(str[r]=='"'){ r++; if(go2comma(str, r, dbgInf)==false){ return false; } break; }
		if(str[r]==0x0D && str[r+1]==0x0A){ r++; }	// Line feed code (Windows): ignore '0x0D'
		if(str[r]==0x0A){ dbgInf.LineNum++; }		// Line feed code (Unix)
		token += str[r];							// Both of the line feed codes (CR+LF or LF) are added as a LF. 
	}
	if(str[r]==0){ printf("ERROR: %s: Line(%u): Command of '\"\"' is not closed. ('\"' is required).\n", dbgInf.FileName.c_str(), dbgInf.LineNum); return false; }
	return true;
}

std::vector<std::string> getLine(bool& result, const uchar* str, uint& r, struct debugInformation& dbgInf){
	result=true;
	std::vector<std::string> line;
	std::string token;
	for(; str[r]!=0; ){
		if(str[r]==' '){ if(token.size()==0){ r++; continue; } } // skip ' ' just after ','
		if(str[r]==','){
			line.push_back(std::move(token));
			token.clear();
			r++;
			continue;
		}
		if(str[r]=='"'){ if(go2doubleQuotation(token, str, r, dbgInf)==false){ result=false; return std::vector<std::string>(0); } continue; } // Command of '""'.
		if(str[r]==0x0D && str[r+1]==0x0A){ r+=2; break; }	// Line feed code (Windows)
		if(str[r]==0x0A){ dbgInf.LineNum++; r++; break; }	// Line feed code (Unix)
		token += str[r];
		r++;
	}
	line.push_back(std::move(token));
	return line;
}

std::vector<std::vector<std::string>> sstd::parseCSV(const char* pReadFile){

	// r: read place
	uint r=0;
	
//	std::string str = sstd::readAll(pReadFile);
//	ignoreBOM(str, r); // Ignore BOM (BOM: byte order mark)
	std::string str = sstd::readAll_withoutBOM(pReadFile);
	
	std::vector<std::vector<std::string>> ret;

	struct debugInformation dbgInf;
	dbgInf.FileName = sstd::getFileName(pReadFile);
	dbgInf.LineNum  = 1;

	bool result;
	for(; str[r]!=0; ){
		std::vector<std::string> line = getLine(result, (uchar*)&str[0], r, dbgInf);
		eraseEmptyTail(line);
		ret.push_back(std::move(line));
		if(result==false){ return std::vector<std::vector<std::string>>(0); }
	}
	eraseEmptyTail(ret);
	
	return ret;
}
