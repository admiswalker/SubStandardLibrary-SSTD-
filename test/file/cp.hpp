#pragma once


TEST(cp, copy_pChar_pChar){
    sstd::mkdir("./tmpDir_cp");
    sstd::system("dd if=/dev/urandom of=./tmpDir_cp/test_rand.bin bs=1M count=10 > /dev/null 2>&1");
    
    sstd::copy("./tmpDir_cp/test_rand.bin", "./tmpDir_cp/test_rand_copy.bin");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back();

    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm("./tmpDir_cp");
}
TEST(cp, copy_str_pChar){
}
TEST(cp, copy_pChar_str){
}
TEST(cp, copy_str_str){
}

TEST(cp, cp_case01){
//    std::vector<std::string> vPath = sstd::glob("./sstd/*", "dfr");
//    sstd::printn(v_path);
}


