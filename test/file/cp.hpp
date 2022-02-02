#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(cp, copy_pChar_pChar_case01){
    sstd::mkdir("./tmpDir_cp");
    sstd::system("dd if=/dev/urandom of=./tmpDir_cp/test_rand.bin bs=1M count=10 > /dev/null 2>&1");
    
    sstd::copy("./tmpDir_cp/test_rand.bin", "./tmpDir_cp/test_rand_copy.bin");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.

    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm("./tmpDir_cp");
}
TEST(cp, copy_pChar_pChar_case02_changeFileSize){
    sstd::mkdir("./tmpDir_cp");
    sstd::system("dd if=/dev/urandom of=./tmpDir_cp/test_rand.bin bs=1M count=10 > /dev/null 2>&1");
    
    sstd::copy("./tmpDir_cp/test_rand.bin", "./tmpDir_cp/test_rand_copy.bin");
    {   
        std::string hash_src = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
        std::string hash_dst = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    
    // change file size
    sstd::rm("./tmpDir_cp/test_rand.bin");
    sstd::system("dd if=/dev/urandom of=./tmpDir_cp/test_rand.bin bs=1M count=9 > /dev/null 2>&1");
    sstd::copy("./tmpDir_cp/test_rand.bin", "./tmpDir_cp/test_rand_copy.bin");
    {
        std::string hash_src = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
        std::string hash_dst = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
        
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    sstd::rm("./tmpDir_cp");
}
TEST(cp, copy_check_file_permission){
    sstd::mkdir("./tmpDir_cp");
    sstd::system("touch ./tmpDir_cp/exmaple.txt");
    sstd::system("chmod 644 ./tmpDir_cp/exmaple.txt");
    
    sstd::copy("./tmpDir_cp/exmaple.txt", "./tmpDir_cp/exmaple_copy.txt");
    
    std::string hash_src = sstd::system_stdout("ls -al ./tmpDir_cp/exmaple.txt | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("ls -al ./tmpDir_cp/exmaple_copy.txt | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmpDir_cp");
}
TEST(cp, copy_check_file_timestamp){
    sstd::mkdir("./tmpDir_cp");
    sstd::system("touch ./tmpDir_cp/exmaple.txt");
    sstd::system("chmod 644 ./tmpDir_cp/exmaple.txt");

    sstd::sleep_s(2);
    sstd::copy("./tmpDir_cp/exmaple.txt", "./tmpDir_cp/exmaple_copy.txt", "p");

    std::string date_src, date_dst;
    date_src = sstd::system_stdout("date \"+%Y/%m/%d %H:%M:%S\" -r ./tmpDir_cp/exmaple.txt"); date_src.pop_back(); // pop_back() is removing '\n'.
    date_dst = sstd::system_stdout("date \"+%Y/%m/%d %H:%M:%S\" -r ./tmpDir_cp/exmaple_copy.txt"); date_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(date_src.c_str(), date_dst.c_str());
    
    date_src = sstd::system_stdout("ls --full-time ./tmpDir_cp/exmaple.txt | cut -d \" \" -f 7"); date_src.pop_back(); // pop_back() is removing '\n'.
    date_dst = sstd::system_stdout("ls --full-time ./tmpDir_cp/exmaple_copy.txt | cut -d \" \" -f 7"); date_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(date_src.c_str(), date_dst.c_str());
    
    sstd::rm("./tmpDir_cp");
}

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

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(cp, cp_case01_checkhash){
    sstd::mkdir("./tmpDir_cp");
    sstd::system("dd if=/dev/urandom of=./tmpDir_cp/test_rand.bin bs=1M count=10 > /dev/null 2>&1");
    
    sstd::cp("./tmpDir_cp/test_rand.bin", "./tmpDir_cp/test_rand_copy.bin");
    {
        std::string hash_src = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
        std::string hash_dst = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back();
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    
    sstd::rm("./tmpDir_cp");
}
TEST(cp, cp_case01_file2file){
    sstd::mkdir("./tmpDir_cp");
    sstd::system("dd if=/dev/urandom of=./tmpDir_cp/test_rand.bin bs=1k count=1 > /dev/null 2>&1");
    
    sstd::cp("./tmpDir_cp/test_rand.bin", "./tmpDir_cp/test_rand_copy.bin");
    {
        std::string hash_src = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
        std::string hash_dst = sstd::system_stdout("sha256sum ./tmpDir_cp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back();
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    
    sstd::rm("./tmpDir_cp");
}
TEST(cp, cp_case01_file2dir){
    sstd::mkdir("./tmpDir_cp/a");
    sstd::mkdir("./tmpDir_cp/b");
    sstd::system("dd if=/dev/urandom of=./tmpDir_cp/a/test_rand.bin bs=1k count=1 > /dev/null 2>&1");
    
    sstd::cp("./tmpDir_cp/a/test_rand.bin", "./tmpDir_cp/b/");
    {
        std::string hash_src = sstd::system_stdout("sha256sum ./tmpDir_cp/a/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
        std::string hash_dst = sstd::system_stdout("sha256sum ./tmpDir_cp/b/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back();
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    
    sstd::rm("./tmpDir_cp");
}
TEST(cp, cp_case01_opt_p_check_timestamp){
    sstd::mkdir("./tmpDir_cp");

    sstd::cp("./sstd/LICENSE", "./tmpDir_cp/LICENSE", "p");
    {
        // check timestamp
        std::vector<sstd::pathAndType> vPath_ans = sstd::glob_pt("./sstd/LICENSE", "dfr");
        std::vector<sstd::pathAndType> vPath     = sstd::glob_pt("./tmpDir_cp/LICENSE", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        ASSERT_TRUE(vPath[0].st.st_atim.tv_sec  == vPath_ans[0].st.st_atim.tv_sec );
        ASSERT_TRUE(vPath[0].st.st_atim.tv_nsec == vPath_ans[0].st.st_atim.tv_nsec);
        ASSERT_TRUE(vPath[0].st.st_mtim.tv_sec  == vPath_ans[0].st.st_mtim.tv_sec );
        ASSERT_TRUE(vPath[0].st.st_mtim.tv_nsec == vPath_ans[0].st.st_mtim.tv_nsec);
    }
    sstd::rm("./tmpDir_cp");
}
TEST(cp, cp_case02){
    sstd::mkdir("./tmpDir_cp");
    
    sstd::cp("./sstd", "./tmpDir_cp");
    {
        // check path
        std::vector<std::string> vPath_ans = sstd::glob("./sstd/*", "dfr");
        std::vector<std::string> vPath     = sstd::glob("./tmpDir_cp/sstd/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            ASSERT_STREQ((char*)&vPath_ans[i][2], (char*)&vPath[i][12]);
        }
    }
    {
        // check file hash
        std::vector<std::string> vPath_ans = sstd::glob("./sstd/*", "fr");
        std::vector<std::string> vPath     = sstd::glob("./tmpDir_cp/sstd/*", "fr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            std::string hash_src = sstd::system_stdout(std::string("sha256sum ")+vPath_ans    [i]+" | cut -d \" \" -f 1"); hash_src.pop_back();
            std::string hash_dst = sstd::system_stdout(std::string("sha256sum ")+vPath[i]+" | cut -d \" \" -f 1"); hash_dst.pop_back();
            ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
        }
    }
    sstd::rm("./tmpDir_cp");
}
TEST(cp, cp_case02_02){
    sstd::mkdir("./tmpDir_cp");

    sstd::mkdir("./tmpDir_cp/01/a/b/c");
    sstd::system("touch ./tmpDir_cp/01/a/b/c/example.txt");
    
    sstd::cp("./tmpDir_cp/01", "./tmpDir_cp/02");
    {
        // check path
        std::vector<std::string> vPath_ans = sstd::glob("./tmpDir_cp/01/*", "dfr");
        std::vector<std::string> vPath     = sstd::glob("./tmpDir_cp/02/01/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            ASSERT_STREQ((char*)&vPath_ans[i][15], (char*)&vPath[i][18]);
        }
    }
    sstd::rm("./tmpDir_cp");
}
TEST(cp, cp_case02_opt_p_check_timestamp){
    sstd::mkdir("./tmpDir_cp");

    sstd::cp("./sstd", "./tmpDir_cp", "p");
    {
        // check timestamp
        std::vector<sstd::pathAndType> vPath_ans = sstd::glob_pt("./sstd/*", "dfr");
        std::vector<sstd::pathAndType> vPath     = sstd::glob_pt("./tmpDir_cp/sstd/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            ASSERT_TRUE(vPath[i].st.st_atim.tv_sec  == vPath_ans[i].st.st_atim.tv_sec );
            ASSERT_TRUE(vPath[i].st.st_atim.tv_nsec == vPath_ans[i].st.st_atim.tv_nsec);
            ASSERT_TRUE(vPath[i].st.st_mtim.tv_sec  == vPath_ans[i].st.st_mtim.tv_sec );
            ASSERT_TRUE(vPath[i].st.st_mtim.tv_nsec == vPath_ans[i].st.st_mtim.tv_nsec);
        }
    }
    {
        // check timestamp
        std::vector<sstd::pathAndType> vPath_ans = sstd::glob_pt("./sstd", "dfr");
        std::vector<sstd::pathAndType> vPath     = sstd::glob_pt("./tmpDir_cp/sstd", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
//      ASSERT_TRUE(vPath[0].st.st_atim.tv_sec  == vPath_ans[0].st.st_atim.tv_sec );
//      ASSERT_TRUE(vPath[0].st.st_atim.tv_nsec == vPath_ans[0].st.st_atim.tv_nsec);
        ASSERT_TRUE(vPath[0].st.st_mtim.tv_sec  == vPath_ans[0].st.st_mtim.tv_sec );
        ASSERT_TRUE(vPath[0].st.st_mtim.tv_nsec == vPath_ans[0].st.st_mtim.tv_nsec);
    }
    sstd::rm("./tmpDir_cp");
}
TEST(cp, cp_case03){
    sstd::mkdir("./tmpDir_cp");
    
    sstd::cp("./sstd/*", "./tmpDir_cp");
    {
        // check path
        std::vector<std::string> vPath_ans = sstd::glob("./sstd/*", "dfr");
        std::vector<std::string> vPath     = sstd::glob("./tmpDir_cp/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            ASSERT_STREQ((char*)&vPath_ans[i][7], (char*)&vPath[i][12]);
        }
    }
    {
        // check file hash
        std::vector<std::string> vPath_ans = sstd::glob("./sstd/*", "fr");
        std::vector<std::string> vPath     = sstd::glob("./tmpDir_cp/*", "fr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            std::string hash_src = sstd::system_stdout(std::string("sha256sum ")+vPath_ans[i]+" | cut -d \" \" -f 1"); hash_src.pop_back();
            std::string hash_dst = sstd::system_stdout(std::string("sha256sum ")+vPath    [i]+" | cut -d \" \" -f 1"); hash_dst.pop_back();
            ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
        }
    }
    sstd::rm("./tmpDir_cp");
}
TEST(cp, cp_case03_02){
    sstd::mkdir("./tmpDir_cp");

    sstd::mkdir("./tmpDir_cp/01/a/b/c");
    sstd::system("touch ./tmpDir_cp/01/a/b/c/example.txt");
    
    sstd::cp("./tmpDir_cp/01/*", "./tmpDir_cp/02");
    {
        // check path
        std::vector<std::string> vPath_ans = sstd::glob("./tmpDir_cp/01/*", "dfr");
        std::vector<std::string> vPath     = sstd::glob("./tmpDir_cp/02/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            ASSERT_STREQ((char*)&vPath_ans[i][15], (char*)&vPath[i][15]);
        }
    }
    sstd::rm("./tmpDir_cp");
}
TEST(cp, cp_case03_copy_empty_dir){
    sstd::mkdir("./tmpDir_cp");
    
    sstd::mkdir("./tmpDir_cp/a/01");
    sstd::mkdir("./tmpDir_cp/a/02");
    sstd::mkdir("./tmpDir_cp/b");
    
    sstd::cp("./tmpDir_cp/a/*", "./tmpDir_cp/b");
    {
        // check path
        std::vector<std::string> vPath_ans = sstd::glob("./tmpDir_cp/a/*", "dfr");
        std::vector<std::string> vPath     = sstd::glob("./tmpDir_cp/b/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            ASSERT_STREQ((char*)&vPath_ans[i][15], (char*)&vPath[i][15]);
        }
    }
    sstd::rm("./tmpDir_cp");
}
TEST(cp, cp_case03_opt_p_check_timestamp){
    sstd::mkdir("./tmpDir_cp");

    sstd::cp("./sstd/*", "./tmpDir_cp", "p");
    {
        // check timestamp
        std::vector<sstd::pathAndType> vPath_ans = sstd::glob_pt("./sstd/*", "dfr");
        std::vector<sstd::pathAndType> vPath     = sstd::glob_pt("./tmpDir_cp/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            ASSERT_TRUE(vPath[i].st.st_atim.tv_sec  == vPath_ans[i].st.st_atim.tv_sec );
            ASSERT_TRUE(vPath[i].st.st_atim.tv_nsec == vPath_ans[i].st.st_atim.tv_nsec);
            ASSERT_TRUE(vPath[i].st.st_mtim.tv_sec  == vPath_ans[i].st.st_mtim.tv_sec );
            ASSERT_TRUE(vPath[i].st.st_mtim.tv_nsec == vPath_ans[i].st.st_mtim.tv_nsec);
        }
    }
    sstd::rm("./tmpDir_cp");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
