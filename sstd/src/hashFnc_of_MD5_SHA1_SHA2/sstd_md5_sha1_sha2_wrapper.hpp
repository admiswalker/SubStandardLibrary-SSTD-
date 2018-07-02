#pragma once

#include "../typeDef.h"
#include <stddef.h>
#include <vector>

#define    MD5_DIGEST_LENGTH 16
#define   SHA1_DIGEST_LENGTH 20
#define SHA224_DIGEST_LENGTH 28
#define SHA256_DIGEST_LENGTH 32
#define SHA384_DIGEST_LENGTH 48
#define SHA512_DIGEST_LENGTH 64

namespace sstd{
	std::vector<uint8> md5   (const uchar* in, size_t in_len);
	std::vector<uint8> md5   (const std::vector<uint8>& in);
	
	std::vector<uint8> sha1  (const uchar* in, size_t in_len);
	std::vector<uint8> sha1  (const std::vector<uint8>& in);
	
	std::vector<uint8> sha224(const uchar* in, size_t in_len);
	std::vector<uint8> sha256(const uchar* in, size_t in_len);
	std::vector<uint8> sha384(const uchar* in, size_t in_len);
	std::vector<uint8> sha512(const uchar* in, size_t in_len);
	
	std::vector<uint8> sha224(const std::vector<uint8>& in);
	std::vector<uint8> sha256(const std::vector<uint8>& in);
	std::vector<uint8> sha384(const std::vector<uint8>& in);
	std::vector<uint8> sha512(const std::vector<uint8>& in);
}

// sstd_MD5_sha1_sha2_wrapper is wrapped below libraries ([1], [2], [3]).
// The origin of md5.cpp, md5.hpp is from [1].
// The origin of sha1.cpp, sha1.hpp is from [2].
// The origin of sha224.cpp, sha224.hpp, sha256.cpp, sha256.hpp, sha384.cpp, sha384.hpp, sha512.cpp, sha512.hpp is from [3].
// 
// Reference:
//   [1] MD5 (Public domain MD5 processor) - https://github.com/kalven/md5
//       version: kalven committed on 1 Jan 2014
//   [2] WjCryptLib (Public Domain C Library of Cryptographic functions. Including: MD5, SHA1, SHA256, SHA512, RC4, AES, AES-CTR, AES-OFB, AES-CBC http://waterjuice.org) - https://github.com/WaterJuice/WjCryptLib
//       version: WaterJuice committed on 16 Mar
//   [3] SHA-2 (Public domain SHA-2 processors) - https://github.com/kalven/sha-2
//       version: kalven committed on 27 Aug 2012
//   [4] SHAシリーズの比較 wiki - https://ja.wikipedia.org/wiki/SHA-2#SHA%E3%82%B7%E3%83%AA%E3%83%BC%E3%82%BA%E3%81%AE%E6%AF%94%E8%BC%83

