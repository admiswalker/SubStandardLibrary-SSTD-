#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------
//*
TEST(cp, copy_pChar_pChar_case01){
    sstd::mkdir("./tmp");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand.bin bs=1M count=10 > /dev/null 2>&1");
    
    sstd::copy("./tmp/test_rand.bin", "./tmp/test_rand_copy.bin");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.

    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm("./tmp");
}
TEST(cp, copy_pChar_pChar_case02_changeFileSize){
    sstd::mkdir("./tmp");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand.bin bs=1M count=10 > /dev/null 2>&1");
    
    sstd::copy("./tmp/test_rand.bin", "./tmp/test_rand_copy.bin");
    {   
        std::string hash_src = sstd::system_stdout("sha256sum ./tmp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
        std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    
    // change file size
    sstd::rm("./tmp/test_rand.bin");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand.bin bs=1M count=9 > /dev/null 2>&1");
    sstd::copy("./tmp/test_rand.bin", "./tmp/test_rand_copy.bin");
    {
        std::string hash_src = sstd::system_stdout("sha256sum ./tmp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
        std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
        
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    sstd::rm("./tmp");
}
TEST(cp, copy_check_file_permission){
    sstd::mkdir("./tmp");
    sstd::system("touch ./tmp/exmaple.txt");
    sstd::system("chmod 644 ./tmp/exmaple.txt");
    
    sstd::copy("./tmp/exmaple.txt", "./tmp/exmaple_copy.txt");
    
    std::string permission_src = sstd::system_stdout("ls -al ./tmp/exmaple.txt | cut -d \" \" -f 1"); permission_src.pop_back(); // pop_back() is removing '\n'.
    std::string permission_dst = sstd::system_stdout("ls -al ./tmp/exmaple_copy.txt | cut -d \" \" -f 1"); permission_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(permission_src.c_str(), permission_dst.c_str());
    
    sstd::rm("./tmp");
}

TEST(cp, copy__opt_p__check_file_timestamp){
    sstd::mkdir("./tmp");
    sstd::system("touch ./tmp/exmaple.txt");

    sstd::sleep_s(2);
    sstd::copy("./tmp/exmaple.txt", "./tmp/exmaple_copy.txt", "p");

    std::string date_src, date_dst;
    date_src = sstd::system_stdout("date \"+%Y/%m/%d %H:%M:%S\" -r ./tmp/exmaple.txt"); date_src.pop_back(); // pop_back() is removing '\n'.
    date_dst = sstd::system_stdout("date \"+%Y/%m/%d %H:%M:%S\" -r ./tmp/exmaple_copy.txt"); date_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(date_src.c_str(), date_dst.c_str());
    
    date_src = sstd::system_stdout("ls --full-time ./tmp/exmaple.txt | cut -d \" \" -f 7"); date_src.pop_back(); // pop_back() is removing '\n'.
    date_dst = sstd::system_stdout("ls --full-time ./tmp/exmaple_copy.txt | cut -d \" \" -f 7"); date_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(date_src.c_str(), date_dst.c_str());
    
    sstd::rm("./tmp");
}

TEST(cp, copy__opt_u__update){
    // when a src is latest -> copy() function updates dst file
    sstd::mkdir("./tmp");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_dst.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::sleep_s(2);
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::copy("./tmp/test_rand_src.bin", "./tmp/test_rand_dst.bin", "u");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}
TEST(cp, copy__opt_u__Not_update){
    // when a src is not latest -> copy() function dose Not update dst file
    sstd::mkdir("./tmp");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::sleep_s(2);
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_dst.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::copy("./tmp/test_rand_src.bin", "./tmp/test_rand_dst.bin", "u");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STRNE(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}
TEST(cp, copy__opt_u__gen_new_file){
    // when dst file does not exist
    sstd::mkdir("./tmp");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::copy("./tmp/test_rand_src.bin", "./tmp/test_rand_dst.bin", "npu");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}

TEST(cp, copy__opt_n__update){
    // when a dst Not exit -> copy() function copies src file
    sstd::mkdir("./tmp");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::copy("./tmp/test_rand_src.bin", "./tmp/test_rand_dst.bin", "n");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}
TEST(cp, copy__opt_n__Not_update){
    // when a dst exit -> copy() function does Not copy src file
    sstd::mkdir("./tmp");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_dst.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::copy("./tmp/test_rand_src.bin", "./tmp/test_rand_dst.bin", "n");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STRNE(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}

#define init()                                                          \
    sstd::mkdir("./tmp");                                               \
    sstd::system("dd if=/dev/urandom of=./tmp/rand_src.bin bs=1024 count=1 > /dev/null 2>&1");
#define fin()                                                           \
    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); \
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); \
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());                   \
    sstd::rm("./tmp");
TEST(cp, copy_opt_pChar_pChar){ init(); sstd::copy(            "./tmp/rand_src.bin" ,             "./tmp/rand_dst.bin" , "npu"); fin(); }
TEST(cp, copy_opt_str_pChar  ){ init(); sstd::copy(std::string("./tmp/rand_src.bin"),             "./tmp/rand_dst.bin" , "npu"); fin(); }
TEST(cp, copy_opt_pChar_str  ){ init(); sstd::copy(            "./tmp/rand_src.bin" , std::string("./tmp/rand_dst.bin"), "npu"); fin(); }
TEST(cp, copy_opt_str_str    ){ init(); sstd::copy(std::string("./tmp/rand_src.bin"), std::string("./tmp/rand_dst.bin"), "npu"); fin(); }

TEST(cp, copy_pChar_pChar){ init(); sstd::copy(            "./tmp/rand_src.bin" ,             "./tmp/rand_dst.bin" ); fin(); }
TEST(cp, copy_str_pChar  ){ init(); sstd::copy(std::string("./tmp/rand_src.bin"),             "./tmp/rand_dst.bin" ); fin(); }
TEST(cp, copy_pChar_str  ){ init(); sstd::copy(            "./tmp/rand_src.bin" , std::string("./tmp/rand_dst.bin")); fin(); }
TEST(cp, copy_str_str    ){ init(); sstd::copy(std::string("./tmp/rand_src.bin"), std::string("./tmp/rand_dst.bin")); fin(); }
#undef fin
#undef init
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
//*
TEST(cp, cp_case01_checkhash){
    sstd::mkdir("./tmp");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand.bin bs=1M count=10 > /dev/null 2>&1");
    
    sstd::cp("./tmp/test_rand.bin", "./tmp/test_rand_copy.bin");
    {
        std::string hash_src = sstd::system_stdout("sha256sum ./tmp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
        std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back();
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    
    sstd::rm("./tmp");
}
TEST(cp, cp_case01_file2file){
    sstd::mkdir("./tmp");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand.bin bs=1k count=1 > /dev/null 2>&1");
    
    sstd::cp("./tmp/test_rand.bin", "./tmp/test_rand_copy.bin");
    {
        std::string hash_src = sstd::system_stdout("sha256sum ./tmp/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
        std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back();
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    
    sstd::rm("./tmp");
}
TEST(cp, cp_case01_file2dir){
    sstd::mkdir("./tmp/a");
    sstd::mkdir("./tmp/b");
    sstd::system("dd if=/dev/urandom of=./tmp/a/test_rand.bin bs=1k count=1 > /dev/null 2>&1");
    
    sstd::cp("./tmp/a/test_rand.bin", "./tmp/b/");
    {
        std::string hash_src = sstd::system_stdout("sha256sum ./tmp/a/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
        std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/b/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back();
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    
    sstd::rm("./tmp");
}
TEST(cp, cp_case01_opt_p_check_timestamp){
    sstd::mkdir("./tmp");

    sstd::cp("./sstd/LICENSE", "./tmp/LICENSE", "p");
    {
        // check timestamp
        std::vector<sstd::pathAndType> vPath_ans = sstd::glob_pt("./sstd/LICENSE", "dfr");
        std::vector<sstd::pathAndType> vPath     = sstd::glob_pt("./tmp/LICENSE", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        ASSERT_TRUE(vPath[0].st.st_atim.tv_sec  == vPath_ans[0].st.st_atim.tv_sec );
        ASSERT_TRUE(vPath[0].st.st_atim.tv_nsec == vPath_ans[0].st.st_atim.tv_nsec);
        ASSERT_TRUE(vPath[0].st.st_mtim.tv_sec  == vPath_ans[0].st.st_mtim.tv_sec );
        ASSERT_TRUE(vPath[0].st.st_mtim.tv_nsec == vPath_ans[0].st.st_mtim.tv_nsec);
    }
    sstd::rm("./tmp");
}
TEST(cp, cp_case02){
    sstd::mkdir("./tmp");
    
    sstd::cp("./sstd", "./tmp");
    {
        // check path
        std::vector<std::string> vPath_ans = sstd::glob("./sstd/*", "dfr");
        std::vector<std::string> vPath     = sstd::glob("./tmp/sstd/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            ASSERT_STREQ((char*)&vPath_ans[i][2], (char*)&vPath[i][6]);
        }
    }
    {
        // check file hash
        std::vector<std::string> vPath_ans = sstd::glob("./sstd/*", "fr");
        std::vector<std::string> vPath     = sstd::glob("./tmp/sstd/*", "fr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            std::string hash_src = sstd::system_stdout(std::string("sha256sum ")+vPath_ans    [i]+" | cut -d \" \" -f 1"); hash_src.pop_back();
            std::string hash_dst = sstd::system_stdout(std::string("sha256sum ")+vPath[i]+" | cut -d \" \" -f 1"); hash_dst.pop_back();
            ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
        }
    }
    sstd::rm("./tmp");
}
TEST(cp, cp_case02_opt_p_check_timestamp){
    sstd::mkdir("./tmp");

    sstd::cp("./sstd", "./tmp", "p");
    {
        // check timestamp
        std::vector<sstd::pathAndType> vPath_ans = sstd::glob_pt("./sstd/*", "dfr");
        std::vector<sstd::pathAndType> vPath     = sstd::glob_pt("./tmp/sstd/*", "dfr");
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
        std::vector<sstd::pathAndType> vPath     = sstd::glob_pt("./tmp/sstd", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
//      ASSERT_TRUE(vPath[0].st.st_atim.tv_sec  == vPath_ans[0].st.st_atim.tv_sec );
//      ASSERT_TRUE(vPath[0].st.st_atim.tv_nsec == vPath_ans[0].st.st_atim.tv_nsec);
        ASSERT_TRUE(vPath[0].st.st_mtim.tv_sec  == vPath_ans[0].st.st_mtim.tv_sec );
        ASSERT_TRUE(vPath[0].st.st_mtim.tv_nsec == vPath_ans[0].st.st_mtim.tv_nsec);
    }
    sstd::rm("./tmp");
}
TEST(cp, cp_case03){
    sstd::mkdir("./tmp");
    
    sstd::cp("./sstd/*", "./tmp");
    {
        // check path
        std::vector<std::string> vPath_ans = sstd::glob("./sstd/*", "dfr");
        std::vector<std::string> vPath     = sstd::glob("./tmp/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            ASSERT_STREQ((char*)&vPath_ans[i][7], (char*)&vPath[i][6]);
        }
    }
    {
        // check file hash
        std::vector<std::string> vPath_ans = sstd::glob("./sstd/*", "fr");
        std::vector<std::string> vPath     = sstd::glob("./tmp/*", "fr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            std::string hash_src = sstd::system_stdout(std::string("sha256sum ")+vPath_ans[i]+" | cut -d \" \" -f 1"); hash_src.pop_back();
            std::string hash_dst = sstd::system_stdout(std::string("sha256sum ")+vPath    [i]+" | cut -d \" \" -f 1"); hash_dst.pop_back();
            ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
        }
    }
    sstd::rm("./tmp");
}
TEST(cp, cp_case03_02){
    sstd::mkdir("./tmp");

    sstd::mkdir("./tmp/01/a/b/c");
    sstd::system("touch ./tmp/01/a/b/c/example.txt");
    
    sstd::cp("./tmp/01/*", "./tmp/02");
    {
        // check path
        std::vector<std::string> vPath_ans = sstd::glob("./tmp/01/*", "dfr");
        std::vector<std::string> vPath     = sstd::glob("./tmp/02/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            ASSERT_STREQ((char*)&vPath_ans[i][9], (char*)&vPath[i][9]);
        }
    }
    sstd::rm("./tmp");
}
TEST(cp, cp_case03_copy_empty_dir){
    sstd::mkdir("./tmp");
    
    sstd::mkdir("./tmp/a/01");
    sstd::mkdir("./tmp/a/02");
    sstd::mkdir("./tmp/b");
    
    sstd::cp("./tmp/a/*", "./tmp/b");
    {
        // check path
        std::vector<std::string> vPath_ans = sstd::glob("./tmp/a/*", "dfr");
        std::vector<std::string> vPath     = sstd::glob("./tmp/b/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            ASSERT_STREQ((char*)&vPath_ans[i][7], (char*)&vPath[i][7]);
        }
    }
    sstd::rm("./tmp");
}
TEST(cp, cp_case03_opt_p_check_timestamp){
    sstd::mkdir("./tmp");

    sstd::cp("./sstd/*", "./tmp", "p");
    {
        // check timestamp
        std::vector<sstd::pathAndType> vPath_ans = sstd::glob_pt("./sstd/*", "dfr");
        std::vector<sstd::pathAndType> vPath     = sstd::glob_pt("./tmp/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            ASSERT_TRUE(vPath[i].st.st_atim.tv_sec  == vPath_ans[i].st.st_atim.tv_sec );
            ASSERT_TRUE(vPath[i].st.st_atim.tv_nsec == vPath_ans[i].st.st_atim.tv_nsec);
            ASSERT_TRUE(vPath[i].st.st_mtim.tv_sec  == vPath_ans[i].st.st_mtim.tv_sec );
            ASSERT_TRUE(vPath[i].st.st_mtim.tv_nsec == vPath_ans[i].st.st_mtim.tv_nsec);
        }
    }
    sstd::rm("./tmp");
}

TEST(cp, cp_case01__opt_u__update){
    // when a src is latest -> copy() function updates dst file
    sstd::mkdir("./tmp");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_dst.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::sleep_s(2);
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp("./tmp/test_rand_src.bin", "./tmp/test_rand_dst.bin", "u");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}
TEST(cp, cp_case01__opt_u__Not_update){
    // when a src is not latest -> copy() function does Not update dst file
    sstd::mkdir("./tmp");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::sleep_s(2);
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_dst.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp("./tmp/test_rand_src.bin", "./tmp/test_rand_dst.bin", "u");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STRNE(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}
TEST(cp, cp_case02__opt_u__update){
    // when a src is latest -> copy() function updates dst file
    sstd::mkdir("./tmp/01");
    sstd::mkdir("./tmp/02/01");
    sstd::system("dd if=/dev/urandom of=./tmp/02/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::sleep_s(2);
    sstd::system("dd if=/dev/urandom of=./tmp/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp("./tmp/01", "./tmp/02", "u");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/01/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/02/01/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}
TEST(cp, cp_case02__opt_u__Not_update){
    // when a src is not latest -> copy() function does Not update dst file
    sstd::mkdir("./tmp/01");
    sstd::mkdir("./tmp/02/01");
    sstd::system("dd if=/dev/urandom of=./tmp/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::sleep_s(2);
    sstd::system("dd if=/dev/urandom of=./tmp/02/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp("./tmp/01", "./tmp/02", "u");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/01/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/02/01/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STRNE(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}
TEST(cp, cp_case03__opt_u__update){
    // when a src is latest -> copy() function updates dst file
    sstd::mkdir("./tmp/01");
    sstd::mkdir("./tmp/02");
    sstd::system("dd if=/dev/urandom of=./tmp/02/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::sleep_s(2);
    sstd::system("dd if=/dev/urandom of=./tmp/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp("./tmp/01/*", "./tmp/02", "u");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/01/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/02/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}
TEST(cp, cp_case03__opt_u__Not_update){
    // when a src is not latest -> copy() function does Not update dst file
    sstd::mkdir("./tmp/01");
    sstd::mkdir("./tmp/02");
    sstd::system("dd if=/dev/urandom of=./tmp/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::sleep_s(2);
    sstd::system("dd if=/dev/urandom of=./tmp/02/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp("./tmp/01/*", "./tmp/02", "u");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/01/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/02/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STRNE(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}

TEST(cp, cp_case01__opt_n__update){
    // when a dst Not exit -> copy() function copies src file
    sstd::mkdir("./tmp");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp("./tmp/test_rand_src.bin", "./tmp/test_rand_dst.bin", "n");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}
TEST(cp, cp_case01__opt_n__Not_update){
    // when a dst exit -> copy() function does Not copy src file
    sstd::mkdir("./tmp");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_dst.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp("./tmp/test_rand_src.bin", "./tmp/test_rand_dst.bin", "n");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STRNE(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}
TEST(cp, cp_case02__opt_n__update){
    // when a dst Not exit -> copy() function copies src file
    sstd::mkdir("./tmp/01");
    sstd::mkdir("./tmp/02");
    sstd::system("dd if=/dev/urandom of=./tmp/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp("./tmp/01/", "./tmp/02", "n");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/01/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/02/01/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}
TEST(cp, cp_case02__opt_n__Not_update){
    // when a dst exit -> copy() function does Not copy src file
    sstd::mkdir("./tmp");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::system("dd if=/dev/urandom of=./tmp/test_rand_dst.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp("./tmp/test_rand_src.bin", "./tmp/test_rand_dst.bin", "n");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STRNE(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}
TEST(cp, cp_case03__opt_n__update){
    // when a dst Not exit -> copy() function copies src file
    sstd::mkdir("./tmp/01");
    sstd::mkdir("./tmp/02");
    sstd::system("dd if=/dev/urandom of=./tmp/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp("./tmp/01/*", "./tmp/02", "n");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/01/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/02/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}
TEST(cp, cp_case03__opt_n__Not_update){
    // when a dst exit -> copy() function does Not copy src file
    sstd::mkdir("./tmp/01");
    sstd::mkdir("./tmp/02");
    sstd::system("dd if=/dev/urandom of=./tmp/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::system("dd if=/dev/urandom of=./tmp/02/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp("./tmp/01/*", "./tmp/02", "n");

    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/01/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/02/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STRNE(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm("./tmp");
}

#define init()                                                          \
    sstd::mkdir("./tmp");                                               \
    sstd::system("dd if=/dev/urandom of=./tmp/rand_src.bin bs=1024 count=1 > /dev/null 2>&1");
#define fin()                                                           \
    std::string hash_src = sstd::system_stdout("sha256sum ./tmp/rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); \
    std::string hash_dst = sstd::system_stdout("sha256sum ./tmp/rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); \
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());                   \
    sstd::rm("./tmp");
TEST(cp, cp_opt_pChar_pChar){ init(); sstd::cp(            "./tmp/rand_src.bin" ,             "./tmp/rand_dst.bin" , "npu"); fin(); }
TEST(cp, cp_opt_str_pChar  ){ init(); sstd::cp(std::string("./tmp/rand_src.bin"),             "./tmp/rand_dst.bin" , "npu"); fin(); }
TEST(cp, cp_opt_pChar_str  ){ init(); sstd::cp(            "./tmp/rand_src.bin" , std::string("./tmp/rand_dst.bin"), "npu"); fin(); }
TEST(cp, cp_opt_str_str    ){ init(); sstd::cp(std::string("./tmp/rand_src.bin"), std::string("./tmp/rand_dst.bin"), "npu"); fin(); }

TEST(cp, cp_pChar_pChar){ init(); sstd::cp(            "./tmp/rand_src.bin" ,             "./tmp/rand_dst.bin" ); fin(); }
TEST(cp, cp_str_pChar  ){ init(); sstd::cp(std::string("./tmp/rand_src.bin"),             "./tmp/rand_dst.bin" ); fin(); }
TEST(cp, cp_pChar_str  ){ init(); sstd::cp(            "./tmp/rand_src.bin" , std::string("./tmp/rand_dst.bin")); fin(); }
TEST(cp, cp_str_str    ){ init(); sstd::cp(std::string("./tmp/rand_src.bin"), std::string("./tmp/rand_dst.bin")); fin(); }
#undef fin
#undef init
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
