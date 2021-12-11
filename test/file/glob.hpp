#pragma once

// --- Old implimentation ---
//
//TEST(glob, glob_f){
//    const char* path = R"(./test/file/glob_test/*.txt)";
//    std::vector<std::string> v_path = sstd::glob_f(path);
//    
//    // compare v_path with v_ans
//    std::vector<std::string> v_ans={"./test/file/glob_test/a.txt",
//				    "./test/file/glob_test/b.txt",
//				    "./test/file/glob_test/c.txt"};
//    ASSERT_EQ(v_path.size(), v_ans.size());
//    for(uint i=0; i<v_path.size(); ++i){
//	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
//    }
//}

TEST(glob, glob_opt_f){
    const char* path = R"(./test/file/glob_test/*)";
    std::vector<std::string> v_path = sstd::glob(path, "f");

    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/file/glob_test/a.txt",
				    "./test/file/glob_test/a.zip",
				    "./test/file/glob_test/b.txt",
				    "./test/file/glob_test/b.zip",
				    "./test/file/glob_test/c.txt",
				    "./test/file/glob_test/c.zip"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_opt_f_txt){
    const char* path = R"(./test/file/glob_test/*.txt)";
    std::vector<std::string> v_path = sstd::glob(path, "f");

    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/file/glob_test/a.txt",
				    "./test/file/glob_test/b.txt",
				    "./test/file/glob_test/c.txt"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_opt_f_zip){
    const char* path = R"(./test/file/glob_test/*.zip)";
    std::vector<std::string> v_path = sstd::glob(path, "f");

    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/file/glob_test/a.zip",
				    "./test/file/glob_test/b.zip",
				    "./test/file/glob_test/c.zip"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_opt_d){
    const char* path = R"(./test/file/glob_test/*)";
    std::vector<std::string> v_path = sstd::glob(path, "d");

    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/file/glob_test/a",
				    "./test/file/glob_test/b",
				    "./test/file/glob_test/c"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_opt_dr){
    const char* path = R"(./test/file/glob_test/*)";
    std::vector<std::string> v_path = sstd::glob(path, "dr");
    
    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/file/glob_test/a",
				    "./test/file/glob_test/b",
				    "./test/file/glob_test/c",
				    "./test/file/glob_test/c/ca",
				    "./test/file/glob_test/c/ca/caa"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_opt_fr){
    const char* path = R"(./test/file/glob_test/*)";
    std::vector<std::string> v_path = sstd::glob(path, "fr");
    
    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/file/glob_test/a.txt",
				    "./test/file/glob_test/a.zip",
				    "./test/file/glob_test/a/a01.txt",
				    "./test/file/glob_test/a/a02.txt",
				    "./test/file/glob_test/a/a03.txt",
				    "./test/file/glob_test/b.txt",
				    "./test/file/glob_test/b.zip",
				    "./test/file/glob_test/b/b01.txt",
				    "./test/file/glob_test/b/b02.txt",
				    "./test/file/glob_test/b/b03.txt",
				    "./test/file/glob_test/c.txt",
				    "./test/file/glob_test/c.zip",
				    "./test/file/glob_test/c/c01.txt",
				    "./test/file/glob_test/c/c02.txt",
				    "./test/file/glob_test/c/c03.txt",
				    "./test/file/glob_test/c/ca/ca01.txt",
				    "./test/file/glob_test/c/ca/ca02.txt",
				    "./test/file/glob_test/c/ca/ca03.txt",
				    "./test/file/glob_test/c/ca/caa/caa01.txt",
				    "./test/file/glob_test/c/ca/caa/caa02.txt",
				    "./test/file/glob_test/c/ca/caa/caa03.txt"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_opt_dfr){
    const char* path = R"(./test/file/glob_test/*)";
    std::vector<std::string> v_path = sstd::glob(path, "dfr");
    
    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/file/glob_test/a",
				    "./test/file/glob_test/a.txt",
				    "./test/file/glob_test/a.zip",
				    "./test/file/glob_test/a/a01.txt",
				    "./test/file/glob_test/a/a02.txt",
				    "./test/file/glob_test/a/a03.txt",
				    "./test/file/glob_test/b",
				    "./test/file/glob_test/b.txt",
				    "./test/file/glob_test/b.zip",
				    "./test/file/glob_test/b/b01.txt",
				    "./test/file/glob_test/b/b02.txt",
				    "./test/file/glob_test/b/b03.txt",
				    "./test/file/glob_test/c",
				    "./test/file/glob_test/c.txt",
				    "./test/file/glob_test/c.zip",
				    "./test/file/glob_test/c/c01.txt",
				    "./test/file/glob_test/c/c02.txt",
				    "./test/file/glob_test/c/c03.txt",
				    "./test/file/glob_test/c/ca",
				    "./test/file/glob_test/c/ca/ca01.txt",
				    "./test/file/glob_test/c/ca/ca02.txt",
				    "./test/file/glob_test/c/ca/ca03.txt",
				    "./test/file/glob_test/c/ca/caa",
				    "./test/file/glob_test/c/ca/caa/caa01.txt",
				    "./test/file/glob_test/c/ca/caa/caa02.txt",
				    "./test/file/glob_test/c/ca/caa/caa03.txt"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_all_file){
    const char* path = R"(./test/file/glob_test/*)";
    std::vector<std::string> v_path = sstd::glob(path);

    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/file/glob_test/a.txt",
				    "./test/file/glob_test/a.zip",
				    "./test/file/glob_test/b.txt",
				    "./test/file/glob_test/b.zip",
				    "./test/file/glob_test/c.txt",
				    "./test/file/glob_test/c.zip"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_txt){
    const char* path = R"(./test/file/glob_test/*.txt)";
    std::vector<std::string> v_path = sstd::glob(path);

    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/file/glob_test/a.txt",
				    "./test/file/glob_test/b.txt",
				    "./test/file/glob_test/c.txt"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_zip){
    const char* path = R"(./test/file/glob_test/*.zip)";
    std::vector<std::string> v_path = sstd::glob(path);

    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/file/glob_test/a.zip",
				    "./test/file/glob_test/b.zip",
				    "./test/file/glob_test/c.zip"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
