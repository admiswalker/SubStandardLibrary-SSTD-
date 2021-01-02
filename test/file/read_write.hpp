#pragma once

//--------------------------------------------------------------------------------------------------------
// write

//    size_t                   write(const        char* path, const void* ptr, size_t type_size, size_t num);
//    size_t                   write(const std::string& path, const void* ptr, size_t type_size, size_t num);
//    size_t                   write(const        char*  path, const std::string& s);
//    size_t                   write(const std::string& path, const std::string& s);

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
