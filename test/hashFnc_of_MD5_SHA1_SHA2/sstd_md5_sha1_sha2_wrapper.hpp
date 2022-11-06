#pragma once


std::string vecUint8_to_hexString(std::vector<uint8>& rhs){
    std::string ret;
    for(uint i=0; i<rhs.size(); i++){
        ret += sstd::ssprintf("%.2x", rhs[i]);
    }
    return ret;
}

#define test_hashFn(hashFn, hashFn_str)                                 \
    const char* pFilePath = "./test/test.png";                          \
    std::vector<uint8> data = sstd::read_bin(pFilePath);                \
                                                                        \
    std::vector<uint8> hash = sstd::hashFn(data);                       \
    std::string s = vecUint8_to_hexString(hash);                        \
                                                                        \
    std::string hash_ans_s = sstd::split(sstd::system_stdout(sstd::ssprintf("%s %s", hashFn_str, pFilePath)), ' ')[0]; \
    ASSERT_STREQ(s.c_str(), hash_ans_s.c_str());
TEST(hashFnc_of_MD5_SHA1_SHA2, md5   ){ test_hashFn(md5,   "md5sum"   ); }
TEST(hashFnc_of_MD5_SHA1_SHA2, sha1  ){ test_hashFn(sha1,  "sha1sum"  ); }
TEST(hashFnc_of_MD5_SHA1_SHA2, sha224){ test_hashFn(sha224,"sha224sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2, sha256){ test_hashFn(sha256,"sha256sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2, sha384){ test_hashFn(sha384,"sha384sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2, sha512){ test_hashFn(sha512,"sha512sum"); }
#undef test_hashFn
