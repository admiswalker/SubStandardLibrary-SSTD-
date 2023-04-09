#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
//*
TEST(mv, mv_f2f){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/01");
    sstd::mkdir(tmpDir+"/02");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/01/rand.bin bs=1024 count=1 > /dev/null 2>&1");
    std::string hash_src; sstd::system_stdout(hash_src, "sha256sum "+tmpDir+"/01/rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    
    sstd::mv(tmpDir+"/01/rand.bin", tmpDir+"/02/rand.bin");

    std::string hash_dst; sstd::system_stdout(hash_dst, "sha256sum "+tmpDir+"/02/rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm(tmpDir);
}
TEST(mv, mv_f2f_overwrite){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/01");
    sstd::mkdir(tmpDir+"/02");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/01/rand.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/02/rand.bin bs=1024 count=1 > /dev/null 2>&1");
    std::string hash_src; sstd::system_stdout(hash_src, "sha256sum "+tmpDir+"/01/rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    
    sstd::mv(tmpDir+"/01/rand.bin", tmpDir+"/02/rand.bin");

    std::string hash_dst; sstd::system_stdout(hash_dst, "sha256sum "+tmpDir+"/02/rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm(tmpDir);
}
TEST(mv, mv_f2d){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/01");
    sstd::mkdir(tmpDir+"/02");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/01/rand.bin bs=1024 count=1 > /dev/null 2>&1");
    std::string hash_src; sstd::system_stdout(hash_src, "sha256sum "+tmpDir+"/01/rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    
    sstd::mv(tmpDir+"/01/rand.bin", tmpDir+"/02");

    std::string hash_dst; sstd::system_stdout(hash_dst, "sha256sum "+tmpDir+"/02/rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm(tmpDir);
}
TEST(mv, mv_f2d_overwrite){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/01");
    sstd::mkdir(tmpDir+"/02");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/01/rand.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/02/rand.bin bs=1024 count=1 > /dev/null 2>&1");
    std::string hash_src; sstd::system_stdout(hash_src, "sha256sum "+tmpDir+"/01/rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    
    sstd::mv(tmpDir+"/01/rand.bin", tmpDir+"/02");

    std::string hash_dst; sstd::system_stdout(hash_dst, "sha256sum "+tmpDir+"/02/rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm(tmpDir);
}
TEST(mv, mv_d2d){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/01/a/b");
    sstd::mkdir(tmpDir+"/02");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/01/a/b/rand.bin bs=1024 count=1 > /dev/null 2>&1");
    std::string hash_src; sstd::system_stdout(hash_src, "sha256sum "+tmpDir+"/01/a/b/rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    
    sstd::mv(tmpDir+"/01", tmpDir+"/02");

    std::string hash_dst; sstd::system_stdout(hash_dst, "sha256sum "+tmpDir+"/02/01/a/b/rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm(tmpDir);
}
TEST(mv, mv_d2d_overwrite){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/01/a/b");
    sstd::mkdir(tmpDir+"/02/01");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/01/a/b/rand.bin bs=1024 count=1 > /dev/null 2>&1");
    std::string hash_src; sstd::system_stdout(hash_src, "sha256sum "+tmpDir+"/01/a/b/rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    
    sstd::mv(tmpDir+"/01", tmpDir+"/02");

    std::string hash_dst; sstd::system_stdout(hash_dst, "sha256sum "+tmpDir+"/02/01/a/b/rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm(tmpDir);
}
TEST(mv, mv_w2d){
    // Not Implimented
}

#define init()                                                          \
    SET_TMP_DIR_NAME();                                                 \
    sstd::mkdir(tmpDir+"/01");                                          \
    sstd::mkdir(tmpDir+"/02");                                          \
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/01/rand.bin bs=1024 count=1 > /dev/null 2>&1"); \
    std::string hash_src; sstd::system_stdout(hash_src, "sha256sum "+tmpDir+"/01/rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
#define fin()                                                           \
    std::string hash_dst; sstd::system_stdout(hash_dst, "sha256sum "+tmpDir+"/02/rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); \
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());                   \
    sstd::rm(tmpDir);
TEST(mv, mv_c_c){ init(); sstd::mv(            tmpDir+"/01/rand.bin" ,             tmpDir+"/02/rand.bin" ); fin(); }
TEST(mv, mv_s_c){ init(); sstd::mv(std::string(tmpDir+"/01/rand.bin"),             tmpDir+"/02/rand.bin" ); fin(); }
TEST(mv, mv_c_s){ init(); sstd::mv(            tmpDir+"/01/rand.bin" , std::string(tmpDir+"/02/rand.bin")); fin(); }
TEST(mv, mv_s_s){ init(); sstd::mv(std::string(tmpDir+"/01/rand.bin"), std::string(tmpDir+"/02/rand.bin")); fin(); }
#undef fin
#undef init
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
