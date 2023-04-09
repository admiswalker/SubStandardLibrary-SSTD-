#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// read_bin

#define read_bin_base(ARG2)                                             \
    SET_TMP_DIR_NAME();                                                 \
    sstd::mkdir(tmpDir);                                                \
                                                                        \
    std::string f_path = tmpDir+"/test_read_write.txt";                 \
    std::string s = "abcdef\nGHIJK";                                    \
    size_t w_size = sstd::write(f_path.c_str(), &s[0], sizeof(char), s.size()); \
    ASSERT_EQ(w_size, (uint)12);                                        \
                                                                        \
    bool tf; std::vector<uint8> u8_read; tf = sstd::read_bin(u8_read, ARG2); /* testing this line */ \
    ASSERT_TRUE(tf);                                                    \
    ASSERT_EQ(u8_read.size(), s.size());                                \
    for(uint i=0; i<s.size(); ++i){                                     \
        ASSERT_TRUE(s[i]==(const char)u8_read[i]);                      \
    }                                                                   \
                                                                        \
    sstd::rm(tmpDir);
TEST(read_write, read_bin_bcv){ read_bin_base(f_path.c_str()); }
TEST(read_write, read_bin_bsv){ read_bin_base(f_path); }
#undef read_bin_base

#define read_bin_base_F(ARG2)                                           \
    SET_TMP_DIR_NAME();                                                 \
    std::string f_path = tmpDir+"/notExistingFile.txt";                 \
                                                                        \
    testing::internal::CaptureStdout();                                 \
    bool tf; std::vector<uint8> u8_read; tf = sstd::read_bin(u8_read, ARG2); /* testing this line */ \
    ASSERT_FALSE(tf);                                                   \
    ASSERT_EQ(u8_read.size(), (uint)0);                                 \
    std::string err_msg = testing::internal::GetCapturedStdout();       \
    ASSERT_TRUE(sstd::strIn("fopen was failed", err_msg));
TEST(read_write, read_bin_bcv_F){ read_bin_base_F(f_path.c_str()); }
TEST(read_write, read_bin_bsv_F){ read_bin_base_F(f_path); }
#undef read_bin_base_F

//-----------------------------------------------------------------------------------------------------------------------------------------------
// write_bin

TEST(read_write, write_bin_cv){
}
TEST(read_write, write_bin_sv){
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// read

TEST(read_write, read_01){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    
    std::string f_path = tmpDir+"/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path.c_str(), &s[0], sizeof(char), s.size()); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::string s_read = sstd::read(f_path.c_str());
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    ASSERT_EQ(s.size(), s_read.size());
    
    sstd::rm(tmpDir);
}
TEST(read_write, read_02){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    
    std::string f_path = tmpDir+"/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path.c_str(), &s[0], sizeof(char), s.size()); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::string s_read = sstd::read(f_path);
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    ASSERT_EQ(s.size(), s_read.size());
    
    sstd::rm(tmpDir);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// read_woBOM

TEST(read_write, read_woBOM_sc){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    
    std::string f_path = tmpDir+"/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path.c_str(), &s[0], sizeof(char), s.size()); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::string s_read;
    bool ret = sstd::read_woBOM(s_read, f_path.c_str());
    ASSERT_TRUE(ret);
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    ASSERT_EQ(s.size(), s_read.size());
    
    sstd::rm(tmpDir);
}
TEST(read_write, read_woBOM_ss){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    
    std::string f_path = tmpDir+"/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path.c_str(), &s[0], sizeof(char), s.size()); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::string s_read;
    bool ret = sstd::read_woBOM(s_read, f_path);
    ASSERT_TRUE(ret);
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    ASSERT_EQ(s.size(), s_read.size());
    
    sstd::rm(tmpDir);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// write

TEST(read_write, write_01){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    
    std::string f_path = tmpDir+"/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path.c_str(), &s[0], sizeof(char), s.size()); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::vector<uint8> read = sstd::read_bin(f_path.c_str());
    std::string s_read = std::string(read.begin(), read.end());
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    
    sstd::rm(tmpDir);
}
TEST(read_write, write_02){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    
    std::string f_path = tmpDir+"/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path, &s[0], sizeof(char), s.size()); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::vector<uint8> read = sstd::read_bin(f_path.c_str());
    std::string s_read = std::string(read.begin(), read.end());
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    
    sstd::rm(tmpDir);
}
TEST(read_write, write_03){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    
    std::string f_path = tmpDir+"/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path.c_str(), s); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::vector<uint8> read = sstd::read_bin(f_path.c_str());
    std::string s_read = std::string(read.begin(), read.end());
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    
    sstd::rm(tmpDir);
}
TEST(read_write, write_04){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    
    std::string f_path = tmpDir+"/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path, s.c_str()); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::vector<uint8> read = sstd::read_bin(f_path.c_str());
    std::string s_read = std::string(read.begin(), read.end());
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    
    sstd::rm(tmpDir);
}
TEST(read_write, write_05){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    
    std::string f_path = tmpDir+"/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path, s); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::vector<uint8> read = sstd::read_bin(f_path.c_str());
    std::string s_read = std::string(read.begin(), read.end());
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    
    sstd::rm(tmpDir);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
