#pragma once

#include <stdio.h>
#include <string>

namespace sstd{ class file; }
class sstd::file{
private:
public:
	FILE* fp;
	file(){ fp=0; }
//	file(const char*& fileName, const char*& mode){ fopen(&fp, fileName, mode); } // コンストラクタでは，fopen の失敗を検知できないので，これは実装しないように!!!
	~file(){ if(fp!=0){ ::fclose(fp); } }
	
	bool fopen(const char* fileName, const char* mode);
	bool fopen(const std::string& fileName, const char* mode);
	bool fclose();
	size_t fread(void* ptr, const size_t& size, const size_t& nmemb);
	size_t fwrite(const void* ptr, const size_t& size, const size_t& nmemb);
	int fseek(const long& offset, const int& whence);
	long ftell();

	size_t fsize();
};

