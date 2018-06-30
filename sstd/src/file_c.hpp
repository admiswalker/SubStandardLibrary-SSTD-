#pragma once
#include <string.h> // for strerror(errno)
#include "./typeDef.h"
#include "./pdbg.hpp"
#include "./file.hpp"
#include "./hashFnc_of_MD5_SHA1_SHA2/sstd_md5_sha1_sha2_wrapper.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{ class file_c; } // file_c: file consistent
class sstd::file_c{
private:
public:
	sstd::file fp;
	file_c();
	~file_c();
	
	bool fopen_rbp(const char*        pFileName);
	bool fopen_rbp(const std::string&  fileName);
	bool fopen_wbp(const char*        pFileName);
	bool fopen_wbp(const std::string&  fileName);
//	bool fclose();
	
	bool freadAll (std::vector<uint8>& retRaw);
	bool fwriteAll(std::vector<uint8>& retRaw);
};

//-----------------------------------------------------------------------------------------------------------------------------------------------

