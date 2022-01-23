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
    
    sstd::cp("./sstd", "./tmpDir_cp");
    {
        // check path
        std::vector<std::string> vPath = sstd::glob("./sstd/*", "dfr");
        std::vector<std::string> vPath_ans = sstd::glob("./tmpDir_cp/sstd/*", "dfr");
        ASSERT_EQ(vPath.size(), vPath_ans.size());
        for(uint i=0; i<vPath.size(); ++i){
            ASSERT_STREQ((char*)&vPath[i][2], (char*)&vPath_ans[i][12]);
        }
    }
    {
        // check file hash
        std::vector<std::string> vPath = sstd::glob("./sstd/*", "fr");
        std::vector<std::string> vPath_ans = sstd::glob("./tmpDir_cp/sstd/*", "fr");
        ASSERT_EQ(vPath.size(), vPath_ans.size());
        for(uint i=0; i<vPath.size(); ++i){
            std::string hash_src = sstd::system_stdout(std::string("sha256sum ")+vPath    [i]+" | cut -d \" \" -f 1"); hash_src.pop_back();
            std::string hash_dst = sstd::system_stdout(std::string("sha256sum ")+vPath_ans[i]+" | cut -d \" \" -f 1"); hash_dst.pop_back();
            ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
        }
    }
    sstd::rm("./tmpDir_cp");
}


