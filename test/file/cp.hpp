#pragma once

/*
TEST(cp, copy_pChar_pChar_case01){
    sstd::mkdir("./tmpDir_cp");
    sstd::system("dd if=/dev/urandom of=./tmpDir_cp/test_rand.bin bs=1M count=10 > /dev/null 2>&1");
    
    sstd::copy("./tmpDir_cp/test_rand.bin", "./tmpDir_cp/test_rand_copy.bin");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back();

    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm("./tmpDir_cp");
}
TEST(cp, copy_pChar_pChar_case02_changeFileSize){
    sstd::mkdir("./tmpDir_cp");
    sstd::system("dd if=/dev/urandom of=./tmpDir_cp/test_rand.bin bs=1M count=10 > /dev/null 2>&1");
    
    sstd::copy("./tmpDir_cp/test_rand.bin", "./tmpDir_cp/test_rand_copy.bin");
    {   
        std::string hash_src = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
        std::string hash_dst = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back();
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    
    // change file size
    sstd::rm("./tmpDir_cp/test_rand.bin");
    sstd::system("dd if=/dev/urandom of=./tmpDir_cp/test_rand.bin bs=1M count=9 > /dev/null 2>&1");
    sstd::copy("./tmpDir_cp/test_rand.bin", "./tmpDir_cp/test_rand_copy.bin");
    {
        std::string hash_src = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
        std::string hash_dst = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back();
        
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    sstd::rm("./tmpDir_cp");
}

// Not implimented
//
//TEST(cp, copy_pChar_pChar_case03_permission){
//    sstd::mkdir("./tmpDir_cp_2");
//    sstd::system("touch ./tmpDir_cp/a.sh");
//    sstd::system("chmod +x ./tmpDir_cp/a.sh");
//    
//    sstd::copy("./tmpDir_cp/a.sh", "./tmpDir_cp/a_copy.sh");
//}

TEST(cp, copy_str_pChar){
    sstd::mkdir("./tmpDir_cp");
    sstd::system("dd if=/dev/urandom of=./tmpDir_cp/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");
    
    sstd::copy(std::string("./tmpDir_cp/test_rand.bin"), "./tmpDir_cp/test_rand_copy.bin");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back();

    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm("./tmpDir_cp");
}
TEST(cp, copy_pChar_str){
    sstd::mkdir("./tmpDir_cp");
    sstd::system("dd if=/dev/urandom of=./tmpDir_cp/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");
    
    sstd::copy("./tmpDir_cp/test_rand.bin", std::string("./tmpDir_cp/test_rand_copy.bin"));

    std::string hash_src = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back();

    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm("./tmpDir_cp");
}
TEST(cp, copy_str_str){
    sstd::mkdir("./tmpDir_cp");
    sstd::system("dd if=/dev/urandom of=./tmpDir_cp/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");
    
    sstd::copy(std::string("./tmpDir_cp/test_rand.bin"), std::string("./tmpDir_cp/test_rand_copy.bin"));

    std::string hash_src = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back();

    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm("./tmpDir_cp");
}
*/
TEST(cp, cp_case01){
    sstd::mkdir("./tmpDir_cp");
//    std::vector<std::string> vPath = sstd::glob("./sstd/*", "dfr");
//    sstd::printn(v_path);
    
    sstd::cp("./sstd", "./tmpDir_cp");
//    sstd::rm("./tmpDir_cp");
/*
    sstd::printn(sstd::getFileName("./a/b/c/sstd"));
    sstd::printn(sstd::getFileName("./a/b/c/sstd/"));
    sstd::printn(sstd::getFileName("./a/b/c/sstd/*"));
    printf("\n");
    
    sstd::printn(sstd::getFileName("/a/b/c/sstd"));
    sstd::printn(sstd::getFileName("/a/b/c/sstd/"));
    sstd::printn(sstd::getFileName("/a/b/c/sstd/*"));
    printf("\n");
    
    sstd::printn(sstd::glob("./sstd/lib/*"));
    sstd::printn(sstd::glob("/mnt/sd/documents/projects/SubStandardLibrary/sstd/lib/*"));
*/
}


