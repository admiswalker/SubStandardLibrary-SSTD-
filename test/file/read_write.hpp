#pragma once

//--------------------------------------------------------------------------------------------------------
// read_bin

#define read_bin_base(ARG2)                                             \
    sstd::mkdir("tmp");                                                 \
                                                                        \
    std::string f_path = "./tmp/test_read_write.txt";                   \
    std::string s = "abcdef\nGHIJK";                                    \
    size_t w_size = sstd::write(f_path.c_str(), &s[0], sizeof(char), s.size()); \
    ASSERT_EQ(w_size, (uint)12);                                        \
                                                                        \
    bool tf; std::vector<uint8> u8_read; tf = sstd::read_bin(u8_read, ARG2); /* testing this line */ \
    ASSERT_TRUE(tf);                                                    \
    ASSERT_EQ(u8_read.size(), s.size());                                \
    for(uint i=0; i<s.size(); ++i){                                     \
    ASSERT_TRUE(s[i]==(const char)u8_read[i]);                          \
    }                                                                   \
                                                                        \
    sstd::rm("tmp");
TEST(read_write, read_bin_bcv){ read_bin_base(f_path.c_str()); }
TEST(read_write, read_bin_bsv){ read_bin_base(f_path); }
#undef read_bin_base

#define read_bin_base_F(ARG2)                                           \
    std::string f_path = "./tmp/notExistingFile.txt";                   \
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

//--------------------------------------------------------------------------------------------------------
// write_bin

TEST(read_write, write_bin_cv){
}
TEST(read_write, write_bin_sv){
}

//--------------------------------------------------------------------------------------------------------
// read

TEST(read_write, read_01){
    sstd::mkdir("./tmp");
    
    std::string f_path = "./tmp/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path.c_str(), &s[0], sizeof(char), s.size()); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::string s_read = sstd::read(f_path.c_str());
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    ASSERT_EQ(s.size(), s_read.size());
    
    sstd::rm("./tmp");
}
TEST(read_write, read_02){
    sstd::mkdir("./tmp");
    
    std::string f_path = "./tmp/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path.c_str(), &s[0], sizeof(char), s.size()); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::string s_read = sstd::read(f_path);
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    ASSERT_EQ(s.size(), s_read.size());
    
    sstd::rm("./tmp");
}

//--------------------------------------------------------------------------------------------------------
// read_woBOM

TEST(read_write, read_woBOM_sc){
    sstd::mkdir("./tmp");
    
    std::string f_path = "./tmp/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path.c_str(), &s[0], sizeof(char), s.size()); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::string s_read;
    bool ret = sstd::read_woBOM(s_read, f_path.c_str());
    ASSERT_TRUE(ret);
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    ASSERT_EQ(s.size(), s_read.size());
    
    sstd::rm("./tmp");
}
TEST(read_write, read_woBOM_ss){
    sstd::mkdir("./tmp");
    
    std::string f_path = "./tmp/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path.c_str(), &s[0], sizeof(char), s.size()); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::string s_read;
    bool ret = sstd::read_woBOM(s_read, f_path);
    ASSERT_TRUE(ret);
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    ASSERT_EQ(s.size(), s_read.size());
    
    sstd::rm("./tmp");
}

//--------------------------------------------------------------------------------------------------------
// write

TEST(read_write, write_01){
    sstd::mkdir("./tmp");
    
    std::string f_path = "./tmp/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path.c_str(), &s[0], sizeof(char), s.size()); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::vector<uint8> read = sstd::read_bin(f_path.c_str());
    std::string s_read = std::string(read.begin(), read.end());
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    
    sstd::rm("./tmp");
}
TEST(read_write, write_02){
    sstd::mkdir("./tmp");
    
    std::string f_path = "./tmp/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path, &s[0], sizeof(char), s.size()); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::vector<uint8> read = sstd::read_bin(f_path.c_str());
    std::string s_read = std::string(read.begin(), read.end());
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    
    sstd::rm("./tmp");
}
TEST(read_write, write_03){
    sstd::mkdir("./tmp");
    
    std::string f_path = "./tmp/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path.c_str(), s); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::vector<uint8> read = sstd::read_bin(f_path.c_str());
    std::string s_read = std::string(read.begin(), read.end());
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    
    sstd::rm("./tmp");
}
TEST(read_write, write_04){
    sstd::mkdir("./tmp");
    
    std::string f_path = "./tmp/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path, s.c_str()); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::vector<uint8> read = sstd::read_bin(f_path.c_str());
    std::string s_read = std::string(read.begin(), read.end());
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    
    sstd::rm("./tmp");
}
TEST(read_write, write_05){
    sstd::mkdir("./tmp");
    
    std::string f_path = "./tmp/test_read_write.txt";
    std::string s = "abcdef\nGHIJK";
    size_t w_size = sstd::write(f_path, s); // testing this line
    ASSERT_EQ(w_size, (uint)12);
    
    std::vector<uint8> read = sstd::read_bin(f_path.c_str());
    std::string s_read = std::string(read.begin(), read.end());
    ASSERT_STREQ(s.c_str(), s_read.c_str());
    
    sstd::rm("./tmp");
}

//--------------------------------------------------------------------------------------------------------
