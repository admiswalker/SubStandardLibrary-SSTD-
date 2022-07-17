#pragma once


#define test_hashSum_c(hashFn, hashFn_str)                              \
    const char* pFilePath = "./test/test.png";                          \
                                                                        \
    bool tf; std::string s; tf = sstd::hashFn(s, pFilePath);            \
    ASSERT_TRUE(tf);                                                    \
                                                                        \
    std::string hash_ans_s = sstd::system_stdout(sstd::ssprintf("%s %s | cut -d ' ' -f 1", hashFn_str, pFilePath)); sstd::stripAll_ow(hash_ans_s, "\r\n"); \
    ASSERT_STREQ(s.c_str(), hash_ans_s.c_str());
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, md5sum_c   ){ test_hashSum_c(md5sum,    "md5sum");    }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha1sum_c  ){ test_hashSum_c(sha1sum,   "sha1sum");   }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha224sum_c){ test_hashSum_c(sha224sum, "sha224sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha256sum_c){ test_hashSum_c(sha256sum, "sha256sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha384sum_c){ test_hashSum_c(sha384sum, "sha384sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha512sum_c){ test_hashSum_c(sha512sum, "sha512sum"); }
#undef test_hashSum_c

#define test_hashSum_s(hashFn, hashFn_str)                              \
    const std::string filePath = "./test/test.png";                     \
                                                                        \
    bool tf; std::string s; tf = sstd::hashFn(s, filePath);             \
    ASSERT_TRUE(tf);                                                    \
                                                                        \
    std::string hash_ans_s = sstd::system_stdout(sstd::ssprintf("%s %s | cut -d ' ' -f 1", hashFn_str, filePath.c_str())); sstd::stripAll_ow(hash_ans_s, "\r\n"); \
    ASSERT_STREQ(s.c_str(), hash_ans_s.c_str());
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, md5sum_s   ){ test_hashSum_s(md5sum,    "md5sum");    }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha1sum_s  ){ test_hashSum_s(sha1sum,   "sha1sum");   }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha224sum_s){ test_hashSum_s(sha224sum, "sha224sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha256sum_s){ test_hashSum_s(sha256sum, "sha256sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha384sum_s){ test_hashSum_s(sha384sum, "sha384sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha512sum_s){ test_hashSum_s(sha512sum, "sha512sum"); }
#undef test_hashSum_s
