#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

//*
TEST(cp, copy_pChar_pChar_case01){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand.bin bs=1M count=10 > /dev/null 2>&1");
    
    sstd::copy(tmpDir+"/test_rand.bin", tmpDir+"/test_rand_copy.bin");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.

    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    sstd::rm(tmpDir);
}
TEST(cp, copy_pChar_pChar_case02_changeFileSize){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand.bin bs=1M count=10 > /dev/null 2>&1");
    
    sstd::copy(tmpDir+"/test_rand.bin", tmpDir+"/test_rand_copy.bin");
    {   
        std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
        std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    
    // change file size
    sstd::rm(tmpDir+"/test_rand.bin");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand.bin bs=1M count=9 > /dev/null 2>&1");
    sstd::copy(tmpDir+"/test_rand.bin", tmpDir+"/test_rand_copy.bin");
    {
        std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
        std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
        
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    sstd::rm(tmpDir);
}
TEST(cp, copy_check_file_permission){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    sstd::system("touch "+tmpDir+"/exmaple.txt");
    sstd::system("chmod 644 "+tmpDir+"/exmaple.txt");
    
    sstd::copy(tmpDir+"/exmaple.txt", tmpDir+"/exmaple_copy.txt");
    
    std::string permission_src = sstd::system_stdout("ls -al "+tmpDir+"/exmaple.txt | cut -d \" \" -f 1"); permission_src.pop_back(); // pop_back() is removing '\n'.
    std::string permission_dst = sstd::system_stdout("ls -al "+tmpDir+"/exmaple_copy.txt | cut -d \" \" -f 1"); permission_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(permission_src.c_str(), permission_dst.c_str());
    
    sstd::rm(tmpDir);
}

TEST(cp, copy__opt_p__check_file_timestamp){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    sstd::system("touch "+tmpDir+"/exmaple.txt");

    sstd::sleep_s(2);
    sstd::copy(tmpDir+"/exmaple.txt", tmpDir+"/exmaple_copy.txt", "p");

    std::string date_src, date_dst;
    date_src = sstd::system_stdout("date \"+%Y/%m/%d %H:%M:%S\" -r "+tmpDir+"/exmaple.txt"); date_src.pop_back(); // pop_back() is removing '\n'.
    date_dst = sstd::system_stdout("date \"+%Y/%m/%d %H:%M:%S\" -r "+tmpDir+"/exmaple_copy.txt"); date_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(date_src.c_str(), date_dst.c_str());
    
    date_src = sstd::system_stdout("ls --full-time "+tmpDir+"/exmaple.txt | cut -d \" \" -f 7"); date_src.pop_back(); // pop_back() is removing '\n'.
    date_dst = sstd::system_stdout("ls --full-time "+tmpDir+"/exmaple_copy.txt | cut -d \" \" -f 7"); date_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(date_src.c_str(), date_dst.c_str());
    
    sstd::rm(tmpDir);
}

TEST(cp, copy__opt_u__update){
    // when a src is latest -> copy() function updates dst file
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_dst.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::sleep_s(2);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::copy(tmpDir+"/test_rand_src.bin", tmpDir+"/test_rand_dst.bin", "u");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}
TEST(cp, copy__opt_u__Not_update){
    // when a src is not latest -> copy() function dose Not update dst file
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::sleep_s(2);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_dst.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::copy(tmpDir+"/test_rand_src.bin", tmpDir+"/test_rand_dst.bin", "u");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STRNE(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}
TEST(cp, copy__opt_u__gen_new_file){
    // when dst file does not exist
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::copy(tmpDir+"/test_rand_src.bin", tmpDir+"/test_rand_dst.bin", "npu");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}

TEST(cp, copy__opt_n__update){
    // when a dst Not exit -> copy() function copies src file
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::copy(tmpDir+"/test_rand_src.bin", tmpDir+"/test_rand_dst.bin", "n");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}
TEST(cp, copy__opt_n__Not_update){
    // when a dst exit -> copy() function does Not copy src file
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_dst.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::copy(tmpDir+"/test_rand_src.bin", tmpDir+"/test_rand_dst.bin", "n");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STRNE(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}

#define init()                                                          \
    SET_TMP_DIR_NAME();                                                 \
    sstd::mkdir(tmpDir);                                                \
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/rand_src.bin bs=1024 count=1 > /dev/null 2>&1");
#define fin()                                                           \
    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); \
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); \
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());                   \
    sstd::rm(tmpDir);
TEST(cp, copy_opt_pChar_pChar){ init(); sstd::copy(            tmpDir+"/rand_src.bin" ,             tmpDir+"/rand_dst.bin" , "npu"); fin(); }
TEST(cp, copy_opt_str_pChar  ){ init(); sstd::copy(std::string(tmpDir+"/rand_src.bin"),             tmpDir+"/rand_dst.bin" , "npu"); fin(); }
TEST(cp, copy_opt_pChar_str  ){ init(); sstd::copy(            tmpDir+"/rand_src.bin" , std::string(tmpDir+"/rand_dst.bin"), "npu"); fin(); }
TEST(cp, copy_opt_str_str    ){ init(); sstd::copy(std::string(tmpDir+"/rand_src.bin"), std::string(tmpDir+"/rand_dst.bin"), "npu"); fin(); }

TEST(cp, copy_pChar_pChar){ init(); sstd::copy(            tmpDir+"/rand_src.bin" ,             tmpDir+"/rand_dst.bin" ); fin(); }
TEST(cp, copy_str_pChar  ){ init(); sstd::copy(std::string(tmpDir+"/rand_src.bin"),             tmpDir+"/rand_dst.bin" ); fin(); }
TEST(cp, copy_pChar_str  ){ init(); sstd::copy(            tmpDir+"/rand_src.bin" , std::string(tmpDir+"/rand_dst.bin")); fin(); }
TEST(cp, copy_str_str    ){ init(); sstd::copy(std::string(tmpDir+"/rand_src.bin"), std::string(tmpDir+"/rand_dst.bin")); fin(); }
#undef fin
#undef init
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
//*
TEST(cp, cp_case01_checkhash){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand.bin bs=1M count=10 > /dev/null 2>&1");
    
    sstd::cp(tmpDir+"/test_rand.bin", tmpDir+"/test_rand_copy.bin");
    {
        std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
        std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back();
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    
    sstd::rm(tmpDir);
}
TEST(cp, cp_case01_file2file){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand.bin bs=1k count=1 > /dev/null 2>&1");
    
    sstd::cp(tmpDir+"/test_rand.bin", tmpDir+"/test_rand_copy.bin");
    {
        std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
        std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_copy.bin | cut -d \" \" -f 1"); hash_dst.pop_back();
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    
    sstd::rm(tmpDir);
}
TEST(cp, cp_case01_file2dir){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/a");
    sstd::mkdir(tmpDir+"/b");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/a/test_rand.bin bs=1k count=1 > /dev/null 2>&1");
    
    sstd::cp(tmpDir+"/a/test_rand.bin", tmpDir+"/b/");
    {
        std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/a/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back();
        std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/b/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back();
        ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    }
    
    sstd::rm(tmpDir);
}
TEST(cp, cp_case01_opt_p_check_timestamp){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/src");
    sstd::mkdir(tmpDir+"/dst");

    sstd::system("cp -rp ./sstd/LICENSE "+tmpDir+"/src"); // copy file inorder not to change the access time stamp when calling sstd::glob_pt()
    sstd::cp(tmpDir+"/src/LICENSE", tmpDir+"/dst/LICENSE", "p");
    {
        // check timestamp
        std::vector<sstd::pathAndType> vPath_ans = sstd::glob_pt(tmpDir+"/src/LICENSE", "dfr");
        std::vector<sstd::pathAndType> vPath     = sstd::glob_pt(tmpDir+"/dst/LICENSE", "dfr");
        ASSERT_EQ(vPath_ans.size(), (uint)1);
        ASSERT_EQ(vPath.size(),     (uint)1);
        ASSERT_TRUE(vPath[0].st.st_atim.tv_sec  == vPath_ans[0].st.st_atim.tv_sec );
        ASSERT_TRUE(vPath[0].st.st_atim.tv_nsec == vPath_ans[0].st.st_atim.tv_nsec);
        ASSERT_TRUE(vPath[0].st.st_mtim.tv_sec  == vPath_ans[0].st.st_mtim.tv_sec );
        ASSERT_TRUE(vPath[0].st.st_mtim.tv_nsec == vPath_ans[0].st.st_mtim.tv_nsec);
    }
    sstd::rm(tmpDir);
}
TEST(cp, cp_case02){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    
    sstd::cp("./sstd", tmpDir);
    {
        // check path
        std::vector<std::string> vPath_ans = sstd::glob("./sstd/*", "dfr");
        std::vector<std::string> vPath     = sstd::glob(tmpDir+"/sstd/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            ASSERT_STREQ((char*)&vPath_ans[i][2], (char*)&vPath[i][tmpDir.size()+1]);
        }
    }
    {
        // check file hash
        std::vector<std::string> vPath_ans = sstd::glob("./sstd/*", "fr");
        std::vector<std::string> vPath     = sstd::glob(tmpDir+"/sstd/*", "fr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            std::string hash_src = sstd::system_stdout(std::string("sha256sum ")+vPath_ans[i]+" | cut -d \" \" -f 1"); hash_src.pop_back();
            std::string hash_dst = sstd::system_stdout(std::string("sha256sum ")+vPath    [i]+" | cut -d \" \" -f 1"); hash_dst.pop_back();
            ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
        }
    }
    sstd::rm(tmpDir);
}
TEST(cp, cp_case02_opt_p_check_timestamp){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/src");
    sstd::mkdir(tmpDir+"/dst");

    sstd::system("cp -rp ./sstd "+tmpDir+"/src"); // copy file inorder not to change the access time stamp when calling sstd::glob_pt()
    sstd::cp(tmpDir+"/src/sstd", tmpDir+"/dst", "p");
    {
        // check timestamp
        std::vector<sstd::pathAndType> vPath_ans = sstd::glob_pt(tmpDir+"/src/sstd/*", "dfr");
        std::vector<sstd::pathAndType> vPath     = sstd::glob_pt(tmpDir+"/dst/sstd/*", "dfr");
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
        std::vector<sstd::pathAndType> vPath_ans = sstd::glob_pt(tmpDir+"/src/sstd/*", "dfr");
        std::vector<sstd::pathAndType> vPath     = sstd::glob_pt(tmpDir+"/dst/sstd/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
//      ASSERT_TRUE(vPath[0].st.st_atim.tv_sec  == vPath_ans[0].st.st_atim.tv_sec );
//      ASSERT_TRUE(vPath[0].st.st_atim.tv_nsec == vPath_ans[0].st.st_atim.tv_nsec);
        ASSERT_TRUE(vPath[0].st.st_mtim.tv_sec  == vPath_ans[0].st.st_mtim.tv_sec );
        ASSERT_TRUE(vPath[0].st.st_mtim.tv_nsec == vPath_ans[0].st.st_mtim.tv_nsec);
    }
    sstd::rm(tmpDir);
}
TEST(cp, cp_case03){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    
    sstd::cp("./sstd/*", tmpDir);
    {
        // check path
        std::vector<std::string> vPath_ans = sstd::glob("./sstd/*", "dfr");
        std::vector<std::string> vPath     = sstd::glob(tmpDir+"/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            ASSERT_STREQ((char*)&vPath_ans[i][7], (char*)&vPath[i][tmpDir.size()+1]);
        }
    }
    {
        // check file hash
        std::vector<std::string> vPath_ans = sstd::glob("./sstd/*", "fr");
        std::vector<std::string> vPath     = sstd::glob(tmpDir+"/*", "fr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            std::string hash_src = sstd::system_stdout(std::string("sha256sum ")+vPath_ans[i]+" | cut -d \" \" -f 1"); hash_src.pop_back();
            std::string hash_dst = sstd::system_stdout(std::string("sha256sum ")+vPath    [i]+" | cut -d \" \" -f 1"); hash_dst.pop_back();
            ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
        }
    }
    sstd::rm(tmpDir);
}
TEST(cp, cp_case03_02){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);

    sstd::mkdir(tmpDir+"/01/a/b/c");
    sstd::system("touch "+tmpDir+"/01/a/b/c/example.txt");
    
    sstd::cp(tmpDir+"/01/*", tmpDir+"/02");
    {
        // check path
        std::vector<std::string> vPath_ans = sstd::glob(tmpDir+"/01/*", "dfr");
        std::vector<std::string> vPath     = sstd::glob(tmpDir+"/02/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            ASSERT_STREQ((char*)&vPath_ans[i][tmpDir.size()+1+3], (char*)&vPath[i][tmpDir.size()+1+3]);
        }
    }
    sstd::rm(tmpDir);
}
TEST(cp, cp_case03_copy_empty_dir){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    
    sstd::mkdir(tmpDir+"/a/01");
    sstd::mkdir(tmpDir+"/a/02");
    sstd::mkdir(tmpDir+"/b");
    
    sstd::cp(tmpDir+"/a/*", tmpDir+"/b");
    {
        // check path
        std::vector<std::string> vPath_ans = sstd::glob(tmpDir+"/a/*", "dfr");
        std::vector<std::string> vPath     = sstd::glob(tmpDir+"/b/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            ASSERT_STREQ((char*)&vPath_ans[i][tmpDir.size()+1+2], (char*)&vPath[i][tmpDir.size()+1+2]);
        }
    }
    sstd::rm(tmpDir);
}
TEST(cp, cp_case03_opt_p_check_timestamp){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/src");
    sstd::mkdir(tmpDir+"/dst");

    sstd::system("cp -rp ./sstd/* "+tmpDir+"/src");
    sstd::cp(tmpDir+"/src/*", tmpDir+"/dst", "p");
    {
        // check timestamp
        std::vector<sstd::pathAndType> vPath_ans = sstd::glob_pt(tmpDir+"/src/*", "dfr");
        std::vector<sstd::pathAndType> vPath     = sstd::glob_pt(tmpDir+"/dst/*", "dfr");
        ASSERT_EQ(vPath_ans.size(), vPath.size());
        for(uint i=0; i<vPath_ans.size(); ++i){
            if(vPath[i].type=='d'){ continue; }
            ASSERT_TRUE(vPath[i].st.st_atim.tv_sec  == vPath_ans[i].st.st_atim.tv_sec );
            ASSERT_TRUE(vPath[i].st.st_atim.tv_nsec == vPath_ans[i].st.st_atim.tv_nsec);
            ASSERT_TRUE(vPath[i].st.st_mtim.tv_sec  == vPath_ans[i].st.st_mtim.tv_sec );
            ASSERT_TRUE(vPath[i].st.st_mtim.tv_nsec == vPath_ans[i].st.st_mtim.tv_nsec);
        }
    }
    sstd::rm(tmpDir);
}

TEST(cp, cp_case01__opt_u__update){
    // when a src is latest -> copy() function updates dst file
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_dst.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::sleep_s(2);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp(tmpDir+"/test_rand_src.bin", tmpDir+"/test_rand_dst.bin", "u");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}
TEST(cp, cp_case01__opt_u__Not_update){
    // when a src is not latest -> copy() function does Not update dst file
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::sleep_s(2);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_dst.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp(tmpDir+"/test_rand_src.bin", tmpDir+"/test_rand_dst.bin", "u");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STRNE(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}
TEST(cp, cp_case02__opt_u__update){
    // when a src is latest -> copy() function updates dst file
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/01");
    sstd::mkdir(tmpDir+"/02/01");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/02/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::sleep_s(2);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp(tmpDir+"/01", tmpDir+"/02", "u");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/01/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/02/01/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}
TEST(cp, cp_case02__opt_u__Not_update){
    // when a src is not latest -> copy() function does Not update dst file
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/01");
    sstd::mkdir(tmpDir+"/02/01");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::sleep_s(2);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/02/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp(tmpDir+"/01", tmpDir+"/02", "u");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/01/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/02/01/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STRNE(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}
TEST(cp, cp_case03__opt_u__update){
    // when a src is latest -> copy() function updates dst file
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/01");
    sstd::mkdir(tmpDir+"/02");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/02/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::sleep_s(2);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp(tmpDir+"/01/*", tmpDir+"/02", "u");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/01/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/02/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}
TEST(cp, cp_case03__opt_u__Not_update){
    // when a src is not latest -> copy() function does Not update dst file
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/01");
    sstd::mkdir(tmpDir+"/02");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::sleep_s(2);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/02/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp(tmpDir+"/01/*", tmpDir+"/02", "u");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/01/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/02/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STRNE(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}

TEST(cp, cp_case01__opt_n__update){
    // when a dst Not exit -> copy() function copies src file
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp(tmpDir+"/test_rand_src.bin", tmpDir+"/test_rand_dst.bin", "n");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}
TEST(cp, cp_case01__opt_n__Not_update){
    // when a dst exit -> copy() function does Not copy src file
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_dst.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp(tmpDir+"/test_rand_src.bin", tmpDir+"/test_rand_dst.bin", "n");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STRNE(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}
TEST(cp, cp_case02__opt_n__update){
    // when a dst Not exit -> copy() function copies src file
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/01");
    sstd::mkdir(tmpDir+"/02");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp(tmpDir+"/01/", tmpDir+"/02", "n");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/01/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/02/01/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}
TEST(cp, cp_case02__opt_n__Not_update){
    // when a dst exit -> copy() function does Not copy src file
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_src.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/test_rand_dst.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp(tmpDir+"/test_rand_src.bin", tmpDir+"/test_rand_dst.bin", "n");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/test_rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STRNE(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}
TEST(cp, cp_case03__opt_n__update){
    // when a dst Not exit -> copy() function copies src file
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/01");
    sstd::mkdir(tmpDir+"/02");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp(tmpDir+"/01/*", tmpDir+"/02", "n");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/01/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/02/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}
TEST(cp, cp_case03__opt_n__Not_update){
    // when a dst exit -> copy() function does Not copy src file
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir+"/01");
    sstd::mkdir(tmpDir+"/02");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/01/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/02/test_rand.bin bs=1024 count=1 > /dev/null 2>&1");

    sstd::cp(tmpDir+"/01/*", tmpDir+"/02", "n");

    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/01/test_rand.bin | cut -d \" \" -f 1"); hash_src.pop_back(); // pop_back() is removing '\n'.
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/02/test_rand.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); // pop_back() is removing '\n'.
    ASSERT_STRNE(hash_src.c_str(), hash_dst.c_str());
    
    sstd::rm(tmpDir);
}

#define init()                                                          \
    SET_TMP_DIR_NAME();                                                 \
    sstd::mkdir(tmpDir);                                               \
    sstd::system("dd if=/dev/urandom of="+tmpDir+"/rand_src.bin bs=1024 count=1 > /dev/null 2>&1");
#define fin()                                                           \
    std::string hash_src = sstd::system_stdout("sha256sum "+tmpDir+"/rand_src.bin | cut -d \" \" -f 1"); hash_src.pop_back(); \
    std::string hash_dst = sstd::system_stdout("sha256sum "+tmpDir+"/rand_dst.bin | cut -d \" \" -f 1"); hash_dst.pop_back(); \
    ASSERT_STREQ(hash_src.c_str(), hash_dst.c_str());                   \
    sstd::rm(tmpDir);
TEST(cp, cp_opt_pChar_pChar){ init(); sstd::cp(            tmpDir+"/rand_src.bin" ,             tmpDir+"/rand_dst.bin" , "npu"); fin(); }
TEST(cp, cp_opt_str_pChar  ){ init(); sstd::cp(std::string(tmpDir+"/rand_src.bin"),             tmpDir+"/rand_dst.bin" , "npu"); fin(); }
TEST(cp, cp_opt_pChar_str  ){ init(); sstd::cp(            tmpDir+"/rand_src.bin" , std::string(tmpDir+"/rand_dst.bin"), "npu"); fin(); }
TEST(cp, cp_opt_str_str    ){ init(); sstd::cp(std::string(tmpDir+"/rand_src.bin"), std::string(tmpDir+"/rand_dst.bin"), "npu"); fin(); }

TEST(cp, cp_pChar_pChar){ init(); sstd::cp(            tmpDir+"/rand_src.bin" ,             tmpDir+"/rand_dst.bin" ); fin(); }
TEST(cp, cp_str_pChar  ){ init(); sstd::cp(std::string(tmpDir+"/rand_src.bin"),             tmpDir+"/rand_dst.bin" ); fin(); }
TEST(cp, cp_pChar_str  ){ init(); sstd::cp(            tmpDir+"/rand_src.bin" , std::string(tmpDir+"/rand_dst.bin")); fin(); }
TEST(cp, cp_str_str    ){ init(); sstd::cp(std::string(tmpDir+"/rand_src.bin"), std::string(tmpDir+"/rand_dst.bin")); fin(); }
#undef fin
#undef init
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
