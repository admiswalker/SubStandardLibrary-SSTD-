#include "./sstd_md5_sha1_sha2_wrapper.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for MD5

#include "./md5.hpp"

std::vector<uint8> sstd::md5(const uint8* in, size_t in_len){
	std::vector<uint8> hash(MD5_DIGEST_LENGTH);
	
	struct md5_state md;
	md5_init   (md);
	md5_process(md, in, in_len);
	md5_done   (md, &hash[0]);
	return hash;
}
std::vector<uint8> sstd::md5(const std::vector<uint8>& in){ return sstd::md5(&in[0], in.size()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for SHA-1 and SHA-2

#include "./sha1.hpp"
#include "./sha224.hpp"
#include "./sha256.hpp"
#include "./sha384.hpp"
#include "./sha512.hpp"

template <typename sha_state, uint SHA_DIGEST_LENGTH>
inline std::vector<uint8> sstd_sha(const uint8* in, const size_t in_len){
	std::vector<uint8> hash(SHA_DIGEST_LENGTH);
	
	sha_state md;
	sha_init   (md);
	sha_process(md, in, in_len);
	sha_done   (md, &hash[0]  );
	return hash;
}

std::vector<uint8> sstd::sha1  (const uint8* in, size_t in_len){ return sstd_sha<struct sha1_state,   SHA1_DIGEST_LENGTH  >(in, in_len); }
std::vector<uint8> sstd::sha224(const uint8* in, size_t in_len){ return sstd_sha<struct sha224_state, SHA224_DIGEST_LENGTH>(in, in_len); }
std::vector<uint8> sstd::sha256(const uint8* in, size_t in_len){ return sstd_sha<struct sha256_state, SHA256_DIGEST_LENGTH>(in, in_len); }
std::vector<uint8> sstd::sha384(const uint8* in, size_t in_len){ return sstd_sha<struct sha384_state, SHA384_DIGEST_LENGTH>(in, in_len); }
std::vector<uint8> sstd::sha512(const uint8* in, size_t in_len){ return sstd_sha<struct sha512_state, SHA512_DIGEST_LENGTH>(in, in_len); }

std::vector<uint8> sstd::sha1  (const std::vector<uint8>& in){ return sstd::sha1  (&in[0], in.size()); }
std::vector<uint8> sstd::sha224(const std::vector<uint8>& in){ return sstd::sha224(&in[0], in.size()); }
std::vector<uint8> sstd::sha256(const std::vector<uint8>& in){ return sstd::sha256(&in[0], in.size()); }
std::vector<uint8> sstd::sha384(const std::vector<uint8>& in){ return sstd::sha384(&in[0], in.size()); }
std::vector<uint8> sstd::sha512(const std::vector<uint8>& in){ return sstd::sha512(&in[0], in.size()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

