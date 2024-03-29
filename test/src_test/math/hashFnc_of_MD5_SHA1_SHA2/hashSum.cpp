#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

// arg: char
#define test_hashSum_c(hashFn, hashFn_str)                              \
    const char* pFilePath = "./test/src_test/test.png";                 \
                                                                        \
    std::string s = sstd::hashFn(pFilePath);                            \
    ASSERT_TRUE(s.size()!=0);                                           \
                                                                        \
    std::string retStr; sstd::system_stdout(retStr, sstd::ssprintf("%s %s", hashFn_str, pFilePath)); \
    std::string hash_ans_s = sstd::split(retStr, ' ')[0]; \
    ASSERT_STREQ(s.c_str(), hash_ans_s.c_str());
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, md5sum_c   ){ test_hashSum_c(md5sum,    "md5sum");    }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha1sum_c  ){ test_hashSum_c(sha1sum,   "sha1sum");   }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha224sum_c){ test_hashSum_c(sha224sum, "sha224sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha256sum_c){ test_hashSum_c(sha256sum, "sha256sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha384sum_c){ test_hashSum_c(sha384sum, "sha384sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha512sum_c){ test_hashSum_c(sha512sum, "sha512sum"); }
#undef test_hashSum_c

// arg: string
#define test_hashSum_s(hashFn, hashFn_str)                              \
    const std::string filePath = "./test/src_test/test.png";            \
                                                                        \
    std::string s = sstd::hashFn(filePath);                             \
    ASSERT_TRUE(s.size()!=0);                                           \
                                                                        \
    std::string retStr; sstd::system_stdout(retStr, sstd::ssprintf("%s %s", hashFn_str, filePath.c_str())); \
    std::string hash_ans_s = sstd::split(retStr, ' ')[0]; \
    ASSERT_STREQ(s.c_str(), hash_ans_s.c_str());
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, md5sum_s   ){ test_hashSum_s(md5sum,    "md5sum");    }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha1sum_s  ){ test_hashSum_s(sha1sum,   "sha1sum");   }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha224sum_s){ test_hashSum_s(sha224sum, "sha224sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha256sum_s){ test_hashSum_s(sha256sum, "sha256sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha384sum_s){ test_hashSum_s(sha384sum, "sha384sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum, sha512sum_s){ test_hashSum_s(sha512sum, "sha512sum"); }
#undef test_hashSum_s

// empty file
#define test_hashSum_emptyFile(hashFn, hashFn_str)                      \
    SET_TMP_DIR_NAME();                                                 \
    sstd::mkdir(tmpDir);                                                \
    const std::string filePath = tmpDir+"/emptyFile.txt";               \
    sstd::system(sstd::ssprintf("touch %s", filePath.c_str()));         \
                                                                        \
    std::string s = sstd::hashFn(filePath);                             \
                                                                        \
    std::string retStr; sstd::system_stdout(retStr, sstd::ssprintf("%s %s", hashFn_str, filePath.c_str())); \
    std::string hash_ans_s = sstd::split(retStr, ' ')[0]; \
    ASSERT_STREQ(s.c_str(), hash_ans_s.c_str());                        \
    sstd::rm(tmpDir);
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum_emptyFile, md5sum_s   ){ test_hashSum_emptyFile(md5sum,    "md5sum");    }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum_emptyFile, sha1sum_s  ){ test_hashSum_emptyFile(sha1sum,   "sha1sum");   }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum_emptyFile, sha224sum_s){ test_hashSum_emptyFile(sha224sum, "sha224sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum_emptyFile, sha256sum_s){ test_hashSum_emptyFile(sha256sum, "sha256sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum_emptyFile, sha384sum_s){ test_hashSum_emptyFile(sha384sum, "sha384sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum_emptyFile, sha512sum_s){ test_hashSum_emptyFile(sha512sum, "sha512sum"); }
#undef test_hashSum_emptyFile

// not existing file
#define test_hashSum_faileToReadFile(hashFn, hashFn_str)              \
    const std::string filePath = "./test/src_test/notExistingFile.png";      \
                                                                        \
    testing::internal::CaptureStdout();                                 \
    std::string s = sstd::hashFn(filePath);                             \
    ASSERT_TRUE(s.size()==0);                                           \
    std::string err_msg = testing::internal::GetCapturedStdout();       \
    ASSERT_TRUE(sstd::strIn("fopen was failed", err_msg));
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum_F, md5sum_s   ){ test_hashSum_faileToReadFile(md5sum,    "md5sum");    }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum_F, sha1sum_s  ){ test_hashSum_faileToReadFile(sha1sum,   "sha1sum");   }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum_F, sha224sum_s){ test_hashSum_faileToReadFile(sha224sum, "sha224sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum_F, sha256sum_s){ test_hashSum_faileToReadFile(sha256sum, "sha256sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum_F, sha384sum_s){ test_hashSum_faileToReadFile(sha384sum, "sha384sum"); }
TEST(hashFnc_of_MD5_SHA1_SHA2__hashSum_F, sha512sum_s){ test_hashSum_faileToReadFile(sha512sum, "sha512sum"); }
#undef test_hashSum_faileToReadFile

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
