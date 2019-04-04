#include "strEdit.hpp"
#include "file.hpp"
#include "pdbg.hpp"
#include <string.h> // for ::strcmp()

//--------------------------------------------------------------------------------------------------------

// read all of the file as a binary
std::vector<uint8> sstd::readAll_bin(const char* pReadFile){
	sstd::file fp; if(!fp.fopen(pReadFile, "rb")){ sstd::pdbg("ERROR: fopen was failed.\n"); return std::vector<uint8>(); }
	size_t size = fp.fsize(); // ファイルサイズを取得
	std::vector<uint8> raw(size, 0); //0で初期化
	if(fp.fread((uchar*)&raw[0], sizeof(char), size)!=size){ sstd::pdbg("ERROR: fread was failed.\n"); return std::vector<uint8>(); }
	return raw;
}
std::vector<uint8> sstd::readAll_bin(const std::string& readFile){ return sstd::readAll_bin(readFile.c_str()); }

//--------------------------------------------------------------------------------------------------------

// write all data to one file as a binary
bool sstd::writeAll_bin(const char* pWritePath, std::vector<uint8>& rhs){
	sstd::file fp;
	if(!fp.fopen(pWritePath, "wb")){ sstd::pdbg("ERROR: sstd::file::fopen(%s) was failed.\n", pWritePath); return false; }
	if(!fp.fwrite(&rhs[0], sizeof(char), rhs.size())){ sstd::pdbg("ERROR: sstd::file::fwrite(%s) was failed.\n", pWritePath); return false; }
	return true;
}
bool sstd::writeAll_bin(const std::string& writePath, std::vector<uint8>& rhs){ return sstd::writeAll_bin(writePath.c_str(), rhs); }

//--------------------------------------------------------------------------------------------------------

std::string sstd::readAll(const char* pReadFile){
	sstd::file fp; if(!fp.fopen(pReadFile, "rb")){ sstd::pdbg("ERROR: fopen was failed.\n"); return std::string(); }
	size_t size = fp.fsize(); // ファイルサイズを取得
	std::string str(size+1, 0);	//0で初期化	//終端コード分を余分に確保
	if(fp.fread((uchar*)&str[0], sizeof(char), size)!=size){ sstd::pdbg("ERROR: fread was failed.\n"); return std::string(); }
	return str;
}
std::string sstd::readAll(const std::string& readFile){ return sstd::readAll(readFile.c_str()); }

void ignoreBOM(uchar* str, uint& r){

	// UTF-8 以外の場合は，UTF-8 に変換するコードを追加するとよい．
	// it will be better to add functions which will translate to UTF-8 while input file is not UTF-8.
	
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

	sstd::file fp;
	if(!fp.fopen(pReadFile, "rb")){ sstd::pdbg("ERROR: fopen was failed.\n"); }

	// check BOM (Byte Order Mark)
	uint BOM_len=0;
	uchar check_BOM[4];
	fp.fread(&check_BOM[0], sizeof(uchar), 4);
	ignoreBOM(check_BOM, BOM_len);

	size_t size = fp.fsize() - BOM_len;
	fp.fseek(BOM_len, SEEK_SET);	//ファイルポインタを先頭 + BOM_len に戻す。

	std::string str(size+1, 0);		//0で初期化	//終端コード分を余分に確保

	if(fp.fread(&str[0], sizeof(char), size)!=size){ sstd::pdbg("ERROR: fread was failed.\n"); }

	return str;
}
std::string sstd::readAll_withoutBOM(const std::string& readFile){ return sstd::readAll_withoutBOM(readFile.c_str()); }

//--------------------------------------------------------------------------------------------------------

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
		ret.push_back(std::move(buf));
	}
	
	return ret;
}

//--------------------------------------------------------------------------------------------------------

std::vector<std::string> asASpcase(const char* str){
	std::vector<std::string> splitList;
	
	std::string buf;
	uint i=0;
	while(str[i]!=0){ if(' '==str[i]){i++;}else{break;} } // skip space
	while(str[i]!=0){
		if(' '==str[i]){
			splitList.push_back(buf); buf.clear();
			i++;
			while(str[i]!=0){ if(' '==str[i]){i++;}else{break;} } // skip space
		}else{
			buf+=str[i];
			i++;
		}
	}
	if(buf.size()!=0){ splitList.push_back(buf); }
	return splitList;
}
std::vector<std::string> asAX(const char* str, const char X){
	std::vector<std::string> splitList;
	
	std::string buf;
	uint i=0;
	while(str[i]!=0){ if(' '==str[i]){i++;}else{break;} } // skip space
	while(str[i]!=0){
		if(X==str[i]){
			sstd::removeTailSpace(buf); splitList.push_back(buf); buf.clear();
			i++;
			while(str[i]!=0){ if(' '==str[i]){i++;}else{break;} } // skip space
		}else{
			buf+=str[i];
			i++;
		}
	}
	if(buf.size()!=0){ sstd::removeTailSpace(buf); splitList.push_back(buf); }
	return splitList;
}
std::vector<std::string> sstd::split(const char* str, const char X){
	if(X==' '){ return asASpcase(str);
	}  else   { return asAX     (str, X); }
}
std::vector<std::string> sstd::split(const std::string& str, const char X){
	return std::move(sstd::split(str.c_str(), X));
}

//--------------------------------------------------------------------------------------------------------

std::string sstd::removeHeadSpace(const uchar* str){
	std::string ret;

	uint r=0;
	for(; str[r]!=0; r++){
		if(str[r]==' '){
		}     else     { break; }
	}
	for(; str[r]!=0; r++){ ret+=str[r]; }
	
	return ret;
}
void sstd::removeTailSpace(std::string& str){
	for(int r=str.size()-1; r>=0; r--){
		if(str[r]==' '){ str.erase(r);
		}     else     { break; }
	}
}
std::string sstd::removeSpace_of_HeadAndTail(const uchar* str){
	std::string ret = sstd::removeHeadSpace(str);
	sstd::removeTailSpace(ret);
	return ret;
}
void sstd::removeSpace_of_HeadAndTail(std::string& str){
	str = sstd::removeHeadSpace((const uchar*)str.c_str());
	sstd::removeTailSpace(str);
}
std::vector<std::string> sstd::removeSpace_of_HeadAndTail(const std::vector<std::string>& vec){
	std::vector<std::string> ret(vec.size()); ret.clear();
	
	for(uint i=0; i<vec.size(); i++){
		ret.push_back(sstd::removeSpace_of_HeadAndTail((const uchar*)vec[i].c_str()));
	}
	
	return ret;
}

//--------------------------------------------------------------------------------------------------------

bool sstd::strcmp(const char*        str1, const char*        str2){ return (::strcmp(str1,         str2        )==0); }
bool sstd::strcmp(const char*        str1, const std::string& str2){ return (::strcmp(str1,         str2.c_str())==0); }
bool sstd::strcmp(const std::string& str1, const char*        str2){ return (::strcmp(str1.c_str(), str2        )==0); }
bool sstd::strcmp(const std::string& str1, const std::string& str2){ return (::strcmp(str1.c_str(), str2.c_str())==0); }

//--------------------------------------------------------------------------------------------------------

bool sstd::strIn(const char*        lhs, const char*        rhs){
	bool ret=true;
	uint l=0, r=0;
	for(;;){
		if(lhs[l]=='\0'){ return ret;   }
		if(rhs[r]=='\0'){ return false; }
		
		if(lhs[l]==rhs[r]){ ret=true;
		}       else      { ret=false; l=0; }
		
		l++; r++;
	}
}
bool sstd::strIn(const char*        lhs, const std::string& rhs){ return sstd::strIn(lhs        , rhs.c_str()); }
bool sstd::strIn(const std::string& lhs, const char*        rhs){ return sstd::strIn(lhs.c_str(), rhs        ); }
bool sstd::strIn(const std::string& lhs, const std::string& rhs){ return sstd::strIn(lhs.c_str(), rhs.c_str()); }

//--------------------------------------------------------------------------------------------------------

