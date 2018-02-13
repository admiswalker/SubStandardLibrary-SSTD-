#include "strEdit.hpp"
#include "file.hpp"
#include "pdbg.hpp"

//--------------------------------------------------------------------------------------------------------

// file exist
bool sstd::fexist(const char* pCheckFile){
	sstd::file fp;
	return fp.fopen(pCheckFile, "rb");
}
bool sstd::fexist(const std::string&  checkFile){
	return fexist(checkFile.c_str());
}

//--------------------------------------------------------------------------------------------------------

std::string sstd::readAll(const char* pReadFile){

	sstd::file fp;
	if(!fp.fopen(pReadFile, "rb")){ sstd::pdbg_always("ERROR: fopen was failed.\n"); }

	size_t size = fp.fsize(); // ファイルサイズを取得

	std::string str(size+1, 0);	//0で初期化	//終端コード分を余分に確保

	if(fp.fread(&str[0], sizeof(char), size)!=size){ sstd::pdbg_always("ERROR: fread was failed.\n"); }

	return str;
}
void ignoreBOM(uchar* str, uint& r){

	// UTF-8 以外の場合は，UTF-8 に変換するコードを追加するとよい．
	
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
	if(!fp.fopen(pReadFile, "rb")){ sstd::pdbg_always("ERROR: fopen was failed.\n"); }

	// check BOM (Byte Order Mark)
	uint BOM_len=0;
	uchar check_BOM[4];
	fp.fread(&check_BOM[0], sizeof(uchar), 4);
	ignoreBOM(check_BOM, BOM_len);

	size_t size = fp.fsize() - BOM_len;
	fp.fseek(BOM_len, SEEK_SET);	//ファイルポインタを先頭 + BOM_len に戻す。

	std::string str(size+1, 0);		//0で初期化	//終端コード分を余分に確保

	if(fp.fread(&str[0], sizeof(char), size)!=size){ sstd::pdbg_always("ERROR: fread was failed.\n"); }

	return str;
}

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

// 急場しのぎの実装．(これを元にして ',' の方も実装するとよい．)
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

// この関数，' ', ',', に対してスプリットした後，前後の余分な空白を削除するように作り直して，
// sstd に追加しておくと，後が楽．
std::vector<std::string> sstd::split(const char* str, const char X){
	if(X==' '){ return asASpcase(str);
	}else{
		std::vector<std::string> splitList;

		std::string buf;
		for(uint i=0; str[i]!=0; i++){
			if(X==str[i]){ splitList.push_back(buf); buf.clear();
			}    else    { buf+=str[i]; }
		}
		splitList.push_back(buf);
	
		return splitList;
	}

//	  X==',': -> ',' で分割したのち，前後の空白を削除する．
//	  X==' ': -> 任意個の ' ' に対して分割を行う．(例: "ABC DEF" -> ["ABC", "DEF"], " ABC   D EF  " -> ["ABC", "D", "EF"])
//	  
//	  ように，関数を修正しておく．
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
std::vector<std::string> sstd::removeSpace_of_HeadAndTail(const std::vector<std::string>& vec){
	std::vector<std::string> ret(vec.size()); ret.clear();
	
	for(uint i=0; i<vec.size(); i++){
		ret.push_back(sstd::removeSpace_of_HeadAndTail((const uchar*)vec[i].c_str()));
	}

	return ret;
}

//--------------------------------------------------------------------------------------------------------
