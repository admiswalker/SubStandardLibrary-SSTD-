#include "./file_c.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

sstd::file_c::file_c(){}
sstd::file_c::~file_c(){}

bool sstd::file_c::fopen_rbp(const char* pFileName){ return fp.fopen(pFileName, "rb+"); }
bool sstd::file_c::fopen_wbp(const char* pFileName){ return fp.fopen(pFileName, "wb+"); }
bool sstd::file_c::fopen_rbp(const std::string& fileName){ return sstd::file_c::fopen_rbp(fileName.c_str()); }
bool sstd::file_c::fopen_wbp(const std::string& fileName){ return sstd::file_c::fopen_wbp(fileName.c_str()); }

// for debug
//void print_pUint8(const uchar* pRhs, const uint len){ for(uint i=0; i<len; i++){ printf("%.2x", pRhs[i]); } printf("\n"); }
//void print_vUint8(std::vector<uint8>& rhs){ print_pUint8(&rhs[0], rhs.size()); }

bool isEqual(uint8* hash1, uint8* hash2, uint len){
	for(uint i=0; i<len; i++){ if(hash1[i]!=hash2[i]){return false;} }
	return true;
}
bool sstd::file_c::freadAll(std::vector<uint8>& rawOut){
	// get hash size
	uint32 hashSize;
	if(fp.fread((uchar*)&hashSize, sizeof(char), 4)!=4){ sstd::pdbg("ERROR: fread() was failed.\n"); return false; }
	if(hashSize>64){ return false; }
	
	// get hash value
	uint8 pHashVal[64];
	if(fp.fread((uchar*)pHashVal, sizeof(char), hashSize)!=hashSize){ sstd::pdbg("ERROR: fread() was failed.\n"); return false; }
	
	// get file size
	size_t size = fp.fsize();
	int64 rawSize = size-4-hashSize;
	if(!(rawSize>=0)){ return false; }
	
	// get raw data
	rawOut.resize(rawSize); // rawOut.reserve(rawSize); こっちだとバグる
	if((int64)fp.fread((uchar*)&rawOut[0], sizeof(char), rawOut.size())!=rawSize){ sstd::pdbg("ERROR: fread() was failed: %s\n", strerror(errno)); return false; }
	
	// check hash value
	std::vector<uint8> hashNow;
	if      (hashSize==   MD5_DIGEST_LENGTH){ hashNow = sstd::md5   (rawOut);
	}else if(hashSize==  SHA1_DIGEST_LENGTH){ hashNow = sstd::sha1  (rawOut);
	}else if(hashSize==SHA224_DIGEST_LENGTH){ hashNow = sstd::sha224(rawOut);
	}else if(hashSize==SHA256_DIGEST_LENGTH){ hashNow = sstd::sha256(rawOut);
	}else if(hashSize==SHA384_DIGEST_LENGTH){ hashNow = sstd::sha384(rawOut);
	}else if(hashSize==SHA512_DIGEST_LENGTH){ hashNow = sstd::sha512(rawOut);
	}else{ sstd::pdbg("ERROR: while checking hash value, undefined hash type was selected.\n"); return false; }
	
	if(!isEqual(pHashVal, &hashNow[0], hashNow.size())){ sstd::pdbg("ERROR: hash value is not consistent.\n"); return false; }
	
	return true;
}
bool sstd::file_c::fwriteAll(std::vector<uint8>& rawIn){
	// calculate hash value
	std::vector<uint8> hashVal = sstd::sha512(rawIn);
	
	// write hash size
	uint32 hashSize = SHA512_DIGEST_LENGTH;
	if(fp.fwrite((uchar*)&hashSize, sizeof(char), 4)!=4){ sstd::pdbg("ERROR: fwrite() was failed.\n"); return false; }
	
	// write hash value
	if(fp.fwrite((uchar*)&hashVal[0], sizeof(char), hashVal.size())!=hashVal.size()){ sstd::pdbg("ERROR: fwrite() was failed.\n"); return false; }
	
	// write raw data
	if(fp.fwrite((uchar*)&rawIn[0], sizeof(char), rawIn.size())!=rawIn.size()){ sstd::pdbg("ERROR: fwrite() was failed.\n"); return false; }
	
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

