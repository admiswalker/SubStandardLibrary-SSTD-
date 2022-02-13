#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------
//*

//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
//*
TEST(mv, mv_f2f){
    sstd::mkdir("./tmp/01");
    sstd::mkdir("./tmp/02");
    sstd::system("dd if=/dev/urandom of=./tmp/01/rand.bin bs=1024 count=1 > /dev/null 2>&1");
    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/01/rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    
    sstd::mv("./tmp/01/rand.bin", "./tmp/02/rand.bin");

    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/02/rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm("./tmp");
}
TEST(mv, mv_f2f_overwrite){
    sstd::mkdir("./tmp/01");
    sstd::mkdir("./tmp/02");
    sstd::system("dd if=/dev/urandom of=./tmp/01/rand.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::system("dd if=/dev/urandom of=./tmp/02/rand.bin bs=1024 count=1 > /dev/null 2>&1");
    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/01/rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    
    sstd::mv("./tmp/01/rand.bin", "./tmp/02/rand.bin");

    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/02/rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm("./tmp");
}
TEST(mv, mv_f2d){
    sstd::mkdir("./tmp/01");
    sstd::mkdir("./tmp/02");
    sstd::system("dd if=/dev/urandom of=./tmp/01/rand.bin bs=1024 count=1 > /dev/null 2>&1");
    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/01/rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    
    sstd::mv("./tmp/01/rand.bin", "./tmp/02");

    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/02/rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm("./tmp");
}
TEST(mv, mv_f2d_overwrite){
    sstd::mkdir("./tmp/01");
    sstd::mkdir("./tmp/02");
    sstd::system("dd if=/dev/urandom of=./tmp/01/rand.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::system("dd if=/dev/urandom of=./tmp/02/rand.bin bs=1024 count=1 > /dev/null 2>&1");
    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/01/rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    
    sstd::mv("./tmp/01/rand.bin", "./tmp/02");

    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/02/rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm("./tmp");
}
TEST(mv, mv_d2d){
    sstd::mkdir("./tmp/01/a/b");
    sstd::mkdir("./tmp/02");
    sstd::system("dd if=/dev/urandom of=./tmp/01/a/b/rand.bin bs=1024 count=1 > /dev/null 2>&1");
    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/01/a/b/rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    
    sstd::mv("./tmp/01", "./tmp/02");

    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/02/01/a/b/rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm("./tmp");
}
TEST(mv, mv_d2d_overwrite){
    sstd::mkdir("./tmp/01/a/b");
    sstd::mkdir("./tmp/02/01");
    sstd::system("dd if=/dev/urandom of=./tmp/01/a/b/rand.bin bs=1024 count=1 > /dev/null 2>&1");
    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/01/a/b/rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    
    sstd::mv("./tmp/01", "./tmp/02");

    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/02/01/a/b/rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm("./tmp");
}
TEST(mv, mv_w2d){
    // Not Implimented
}

#define init()                                                          \
    sstd::mkdir("./tmp/01");                                            \
    sstd::mkdir("./tmp/02");                                            \
    sstd::system("dd if=/dev/urandom of=./tmp/01/rand.bin bs=1024 count=1 > /dev/null 2>&1"); \
    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/01/rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
#define fin()                                                           \
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/02/rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); \
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());                   \
    sstd::rm("./tmp");
TEST(mv, mv_c_c){ init(); sstd::mv(            "./tmp/01/rand.bin" ,             "./tmp/02/rand.bin" ); fin(); }
TEST(mv, mv_s_c){ init(); sstd::mv(std::string("./tmp/01/rand.bin"),             "./tmp/02/rand.bin" ); fin(); }
TEST(mv, mv_c_s){ init(); sstd::mv(            "./tmp/01/rand.bin" , std::string("./tmp/02/rand.bin")); fin(); }
TEST(mv, mv_s_s){ init(); sstd::mv(std::string("./tmp/01/rand.bin"), std::string("./tmp/02/rand.bin")); fin(); }
#undef fin
#undef init
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
