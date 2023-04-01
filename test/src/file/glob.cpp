#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// glob

TEST(glob, glob_opt_f){
    const char* path = R"(./test/src/file/glob_test/*)";
    std::vector<std::string> v_path = sstd::glob(path, "f");

    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/src/file/glob_test/a.txt",
				    "./test/src/file/glob_test/a.zip",
				    "./test/src/file/glob_test/b.txt",
				    "./test/src/file/glob_test/b.zip",
				    "./test/src/file/glob_test/c.txt",
				    "./test/src/file/glob_test/c.zip"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_opt_f_txt){
    const char* path = R"(./test/src/file/glob_test/*.txt)";
    std::vector<std::string> v_path = sstd::glob(path, "f");

    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/src/file/glob_test/a.txt",
				    "./test/src/file/glob_test/b.txt",
				    "./test/src/file/glob_test/c.txt"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_opt_f_zip){
    const char* path = R"(./test/src/file/glob_test/*.zip)";
    std::vector<std::string> v_path = sstd::glob(path, "f");

    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/src/file/glob_test/a.zip",
				    "./test/src/file/glob_test/b.zip",
				    "./test/src/file/glob_test/c.zip"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_opt_d){
    const char* path = R"(./test/src/file/glob_test/*)";
    std::vector<std::string> v_path = sstd::glob(path, "d");

    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/src/file/glob_test/a",
				    "./test/src/file/glob_test/b",
				    "./test/src/file/glob_test/c"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_opt_dr){
    const char* path = R"(./test/src/file/glob_test/*)";
    std::vector<std::string> v_path = sstd::glob(path, "dr");
    
    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/src/file/glob_test/a",
				    "./test/src/file/glob_test/b",
				    "./test/src/file/glob_test/c",
				    "./test/src/file/glob_test/c/ca",
				    "./test/src/file/glob_test/c/ca/caa"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_opt_fr){
    const char* path = R"(./test/src/file/glob_test/*)";
    std::vector<std::string> v_path = sstd::glob(path, "fr");
    
    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/src/file/glob_test/a.txt",
				    "./test/src/file/glob_test/a.zip",
				    "./test/src/file/glob_test/a/a01.txt",
				    "./test/src/file/glob_test/a/a02.txt",
				    "./test/src/file/glob_test/a/a03.txt",
				    "./test/src/file/glob_test/b.txt",
				    "./test/src/file/glob_test/b.zip",
				    "./test/src/file/glob_test/b/b01.txt",
				    "./test/src/file/glob_test/b/b02.txt",
				    "./test/src/file/glob_test/b/b03.txt",
				    "./test/src/file/glob_test/c.txt",
				    "./test/src/file/glob_test/c.zip",
				    "./test/src/file/glob_test/c/c01.txt",
				    "./test/src/file/glob_test/c/c02.txt",
				    "./test/src/file/glob_test/c/c03.txt",
				    "./test/src/file/glob_test/c/ca/ca01.txt",
				    "./test/src/file/glob_test/c/ca/ca02.txt",
				    "./test/src/file/glob_test/c/ca/ca03.txt",
				    "./test/src/file/glob_test/c/ca/caa/caa01.txt",
				    "./test/src/file/glob_test/c/ca/caa/caa02.txt",
				    "./test/src/file/glob_test/c/ca/caa/caa03.txt"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_opt_dfr){
    const char* path = R"(./test/src/file/glob_test/*)";
    std::vector<std::string> v_path = sstd::glob(path, "dfr");
    
    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/src/file/glob_test/a",
				    "./test/src/file/glob_test/a.txt",
				    "./test/src/file/glob_test/a.zip",
				    "./test/src/file/glob_test/a/a01.txt",
				    "./test/src/file/glob_test/a/a02.txt",
				    "./test/src/file/glob_test/a/a03.txt",
				    "./test/src/file/glob_test/b",
				    "./test/src/file/glob_test/b.txt",
				    "./test/src/file/glob_test/b.zip",
				    "./test/src/file/glob_test/b/b01.txt",
				    "./test/src/file/glob_test/b/b02.txt",
				    "./test/src/file/glob_test/b/b03.txt",
				    "./test/src/file/glob_test/c",
				    "./test/src/file/glob_test/c.txt",
				    "./test/src/file/glob_test/c.zip",
				    "./test/src/file/glob_test/c/c01.txt",
				    "./test/src/file/glob_test/c/c02.txt",
				    "./test/src/file/glob_test/c/c03.txt",
				    "./test/src/file/glob_test/c/ca",
				    "./test/src/file/glob_test/c/ca/ca01.txt",
				    "./test/src/file/glob_test/c/ca/ca02.txt",
				    "./test/src/file/glob_test/c/ca/ca03.txt",
				    "./test/src/file/glob_test/c/ca/caa",
				    "./test/src/file/glob_test/c/ca/caa/caa01.txt",
				    "./test/src/file/glob_test/c/ca/caa/caa02.txt",
				    "./test/src/file/glob_test/c/ca/caa/caa03.txt"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_opt_dfpr_case01){
    const char* path = R"(./test/src/file/glob_test/*)";
    std::vector<std::string> v_path = sstd::glob(path, "dfpr");
    
    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/src/file/glob_test/a",
				    "./test/src/file/glob_test/a.txt",
				    "./test/src/file/glob_test/a.zip",
				    "./test/src/file/glob_test/b",
				    "./test/src/file/glob_test/b.txt",
				    "./test/src/file/glob_test/b.zip",
				    "./test/src/file/glob_test/c",
				    "./test/src/file/glob_test/c.txt",
				    "./test/src/file/glob_test/c.zip"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_opt_dfpr_case02){
    const char* path = R"(./test/src/file/glob_test/*/*)";
    std::vector<std::string> v_path = sstd::glob(path, "dfpr");
    
    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/src/file/glob_test/a/a01.txt",
				    "./test/src/file/glob_test/a/a02.txt",
				    "./test/src/file/glob_test/a/a03.txt",
				    "./test/src/file/glob_test/b/b01.txt",
				    "./test/src/file/glob_test/b/b02.txt",
				    "./test/src/file/glob_test/b/b03.txt",
				    "./test/src/file/glob_test/c/c01.txt",
				    "./test/src/file/glob_test/c/c02.txt",
				    "./test/src/file/glob_test/c/c03.txt",
				    "./test/src/file/glob_test/c/ca"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_all_file){
    const char* path = R"(./test/src/file/glob_test/*)";
    std::vector<std::string> v_path = sstd::glob(path);

    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/src/file/glob_test/a.txt",
				    "./test/src/file/glob_test/a.zip",
				    "./test/src/file/glob_test/b.txt",
				    "./test/src/file/glob_test/b.zip",
				    "./test/src/file/glob_test/c.txt",
				    "./test/src/file/glob_test/c.zip"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_txt){
    const char* path = R"(./test/src/file/glob_test/*.txt)";
    std::vector<std::string> v_path = sstd::glob(path);

    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/src/file/glob_test/a.txt",
				    "./test/src/file/glob_test/b.txt",
				    "./test/src/file/glob_test/c.txt"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}
TEST(glob, glob_zip){
    const char* path = R"(./test/src/file/glob_test/*.zip)";
    std::vector<std::string> v_path = sstd::glob(path);

    // compare v_path with v_ans
    std::vector<std::string> v_ans={"./test/src/file/glob_test/a.zip",
				    "./test/src/file/glob_test/b.zip",
				    "./test/src/file/glob_test/c.zip"};
    ASSERT_EQ(v_path.size(), v_ans.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].c_str(), v_ans[i].c_str());
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// glob_pt

TEST(glob, glob_pt_opt_f){
    const char* path = R"(./test/src/file/glob_test/*)";
    std::vector<struct sstd::pathAndType> v_path = sstd::glob_pt(path, "f");

    // compare v_path with v_ans
    std::vector<std::string> v_ans_path={"./test/src/file/glob_test/a.txt",
                                         "./test/src/file/glob_test/a.zip",
                                         "./test/src/file/glob_test/b.txt",
                                         "./test/src/file/glob_test/b.zip",
                                         "./test/src/file/glob_test/c.txt",
                                         "./test/src/file/glob_test/c.zip"};
    std::vector<char> v_ans_type={'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f'};
    ASSERT_EQ(v_ans_path.size(), v_ans_type.size());
    
    ASSERT_EQ(v_path.size(), v_ans_path.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].path.c_str(), v_ans_path[i].c_str());
	ASSERT_EQ(v_path[i].type, v_ans_type[i]);
    }
}
TEST(glob, glob_pt_opt_f_txt){
    const char* path = R"(./test/src/file/glob_test/*.txt)";
    std::vector<struct sstd::pathAndType> v_path = sstd::glob_pt(path, "f");

    // compare v_path with v_ans
    std::vector<std::string> v_ans_path={"./test/src/file/glob_test/a.txt",
                                         "./test/src/file/glob_test/b.txt",
                                         "./test/src/file/glob_test/c.txt"};
    std::vector<char> v_ans_type={'f',
                                  'f',
                                  'f'};
    ASSERT_EQ(v_ans_path.size(), v_ans_type.size());
    
    ASSERT_EQ(v_path.size(), v_ans_path.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].path.c_str(), v_ans_path[i].c_str());
	ASSERT_EQ(v_path[i].type, v_ans_type[i]);
    }
}
TEST(glob, glob_pt_opt_f_zip){
    const char* path = R"(./test/src/file/glob_test/*.zip)";
    std::vector<struct sstd::pathAndType> v_path = sstd::glob_pt(path, "f");

    // compare v_path with v_ans
    std::vector<std::string> v_ans_path={"./test/src/file/glob_test/a.zip",
                                         "./test/src/file/glob_test/b.zip",
                                         "./test/src/file/glob_test/c.zip"};
    std::vector<char> v_ans_type={'f',
                                  'f',
                                  'f'};
    ASSERT_EQ(v_ans_path.size(), v_ans_type.size());
    
    ASSERT_EQ(v_path.size(), v_ans_path.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].path.c_str(), v_ans_path[i].c_str());
	ASSERT_EQ(v_path[i].type, v_ans_type[i]);
    }
}
TEST(glob, glob_pt_opt_d){
    const char* path = R"(./test/src/file/glob_test/*)";
    std::vector<struct sstd::pathAndType> v_path = sstd::glob_pt(path, "d");

    // compare v_path with v_ans
    std::vector<std::string> v_ans_path={"./test/src/file/glob_test/a",
                                         "./test/src/file/glob_test/b",
                                         "./test/src/file/glob_test/c"};
    std::vector<char> v_ans_type={'d',
                                  'd',
                                  'd'};
    ASSERT_EQ(v_ans_path.size(), v_ans_type.size());
    
    ASSERT_EQ(v_path.size(), v_ans_path.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].path.c_str(), v_ans_path[i].c_str());
	ASSERT_EQ(v_path[i].type, v_ans_type[i]);
    }
}
TEST(glob, glob_pt_opt_dr){
    const char* path = R"(./test/src/file/glob_test/*)";
    std::vector<struct sstd::pathAndType> v_path = sstd::glob_pt(path, "dr");
    
    // compare v_path with v_ans
    std::vector<std::string> v_ans_path={"./test/src/file/glob_test/a",
                                         "./test/src/file/glob_test/b",
                                         "./test/src/file/glob_test/c",
                                         "./test/src/file/glob_test/c/ca",
                                         "./test/src/file/glob_test/c/ca/caa"};
    std::vector<char> v_ans_type={'d',
                                  'd',
                                  'd',
                                  'd',
                                  'd'};
    ASSERT_EQ(v_ans_path.size(), v_ans_type.size());
    
    ASSERT_EQ(v_path.size(), v_ans_path.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].path.c_str(), v_ans_path[i].c_str());
	ASSERT_EQ(v_path[i].type, v_ans_type[i]);
    }
}
TEST(glob, glob_pt_opt_fr){
    const char* path = R"(./test/src/file/glob_test/*)";
    std::vector<struct sstd::pathAndType> v_path = sstd::glob_pt(path, "fr");
    
    // compare v_path with v_ans
    std::vector<std::string> v_ans_path={"./test/src/file/glob_test/a.txt",
                                         "./test/src/file/glob_test/a.zip",
                                         "./test/src/file/glob_test/a/a01.txt",
                                         "./test/src/file/glob_test/a/a02.txt",
                                         "./test/src/file/glob_test/a/a03.txt",
                                         "./test/src/file/glob_test/b.txt",
                                         "./test/src/file/glob_test/b.zip",
                                         "./test/src/file/glob_test/b/b01.txt",
                                         "./test/src/file/glob_test/b/b02.txt",
                                         "./test/src/file/glob_test/b/b03.txt",
                                         "./test/src/file/glob_test/c.txt",
                                         "./test/src/file/glob_test/c.zip",
                                         "./test/src/file/glob_test/c/c01.txt",
                                         "./test/src/file/glob_test/c/c02.txt",
                                         "./test/src/file/glob_test/c/c03.txt",
                                         "./test/src/file/glob_test/c/ca/ca01.txt",
                                         "./test/src/file/glob_test/c/ca/ca02.txt",
                                         "./test/src/file/glob_test/c/ca/ca03.txt",
                                         "./test/src/file/glob_test/c/ca/caa/caa01.txt",
                                         "./test/src/file/glob_test/c/ca/caa/caa02.txt",
                                         "./test/src/file/glob_test/c/ca/caa/caa03.txt"};
    std::vector<char> v_ans_type={'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f'};
    ASSERT_EQ(v_ans_path.size(), v_ans_type.size());
    
    ASSERT_EQ(v_path.size(), v_ans_path.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].path.c_str(), v_ans_path[i].c_str());
	ASSERT_EQ(v_path[i].type, v_ans_type[i]);
    }
}
TEST(glob, glob_pt_opt_dfr){
    const char* path = R"(./test/src/file/glob_test/*)";
    std::vector<struct sstd::pathAndType> v_path = sstd::glob_pt(path, "dfr");
    
    // compare v_path with v_ans
    std::vector<std::string> v_ans_path={"./test/src/file/glob_test/a",
                                         "./test/src/file/glob_test/a.txt",
                                         "./test/src/file/glob_test/a.zip",
                                         "./test/src/file/glob_test/a/a01.txt",
                                         "./test/src/file/glob_test/a/a02.txt",
                                         "./test/src/file/glob_test/a/a03.txt",
                                         "./test/src/file/glob_test/b",
                                         "./test/src/file/glob_test/b.txt",
                                         "./test/src/file/glob_test/b.zip",
                                         "./test/src/file/glob_test/b/b01.txt",
                                         "./test/src/file/glob_test/b/b02.txt",
                                         "./test/src/file/glob_test/b/b03.txt",
                                         "./test/src/file/glob_test/c",
                                         "./test/src/file/glob_test/c.txt",
                                         "./test/src/file/glob_test/c.zip",
                                         "./test/src/file/glob_test/c/c01.txt",
                                         "./test/src/file/glob_test/c/c02.txt",
                                         "./test/src/file/glob_test/c/c03.txt",
                                         "./test/src/file/glob_test/c/ca",
                                         "./test/src/file/glob_test/c/ca/ca01.txt",
                                         "./test/src/file/glob_test/c/ca/ca02.txt",
                                         "./test/src/file/glob_test/c/ca/ca03.txt",
                                         "./test/src/file/glob_test/c/ca/caa",
                                         "./test/src/file/glob_test/c/ca/caa/caa01.txt",
                                         "./test/src/file/glob_test/c/ca/caa/caa02.txt",
                                         "./test/src/file/glob_test/c/ca/caa/caa03.txt"};
    std::vector<char> v_ans_type={'d',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'd',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'd',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'd',
                                  'f',
                                  'f',
                                  'f',
                                  'd',
                                  'f',
                                  'f',
                                  'f'};
    ASSERT_EQ(v_ans_path.size(), v_ans_type.size());
    
    ASSERT_EQ(v_path.size(), v_ans_path.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].path.c_str(), v_ans_path[i].c_str());
	ASSERT_EQ(v_path[i].type, v_ans_type[i]);
    }
}
TEST(glob, glob_pt_opt_dfpr_case01){
    const char* path = R"(./test/src/file/glob_test/*)";
    std::vector<struct sstd::pathAndType> v_path = sstd::glob_pt(path, "dfpr");
    
    // compare v_path with v_ans
    std::vector<std::string> v_ans_path={"./test/src/file/glob_test/a",
                                         "./test/src/file/glob_test/a.txt",
                                         "./test/src/file/glob_test/a.zip",
                                         "./test/src/file/glob_test/b",
                                         "./test/src/file/glob_test/b.txt",
                                         "./test/src/file/glob_test/b.zip",
                                         "./test/src/file/glob_test/c",
                                         "./test/src/file/glob_test/c.txt",
                                         "./test/src/file/glob_test/c.zip"};
    std::vector<char> v_ans_type={'d',
                                  'f',
                                  'f',
                                  'd',
                                  'f',
                                  'f',
                                  'd',
                                  'f',
                                  'f'};
    ASSERT_EQ(v_ans_path.size(), v_ans_type.size());
    
    ASSERT_EQ(v_path.size(), v_ans_path.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].path.c_str(), v_ans_path[i].c_str());
	ASSERT_EQ(v_path[i].type, v_ans_type[i]);
    }
}
TEST(glob, glob_pt_opt_dfpr_case02){
    const char* path = R"(./test/src/file/glob_test/*/*)";
    std::vector<struct sstd::pathAndType> v_path = sstd::glob_pt(path, "dfpr");
    
    // compare v_path with v_ans
    std::vector<std::string> v_ans_path={"./test/src/file/glob_test/a/a01.txt",
                                         "./test/src/file/glob_test/a/a02.txt",
                                         "./test/src/file/glob_test/a/a03.txt",
                                         "./test/src/file/glob_test/b/b01.txt",
                                         "./test/src/file/glob_test/b/b02.txt",
                                         "./test/src/file/glob_test/b/b03.txt",
                                         "./test/src/file/glob_test/c/c01.txt",
                                         "./test/src/file/glob_test/c/c02.txt",
                                         "./test/src/file/glob_test/c/c03.txt",
                                         "./test/src/file/glob_test/c/ca"};
    std::vector<char> v_ans_type={'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'd'};
    ASSERT_EQ(v_ans_path.size(), v_ans_type.size());
    
    ASSERT_EQ(v_path.size(), v_ans_path.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].path.c_str(), v_ans_path[i].c_str());
	ASSERT_EQ(v_path[i].type, v_ans_type[i]);
    }
}
TEST(glob, glob_pt_all_file){
    const char* path = R"(./test/src/file/glob_test/*)";
    std::vector<struct sstd::pathAndType> v_path = sstd::glob_pt(path);

    // compare v_path with v_ans
    std::vector<std::string> v_ans_path={"./test/src/file/glob_test/a.txt",
                                         "./test/src/file/glob_test/a.zip",
                                         "./test/src/file/glob_test/b.txt",
                                         "./test/src/file/glob_test/b.zip",
                                         "./test/src/file/glob_test/c.txt",
                                         "./test/src/file/glob_test/c.zip"};
    std::vector<char> v_ans_type={'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f',
                                  'f'};
    ASSERT_EQ(v_ans_path.size(), v_ans_type.size());
    
    ASSERT_EQ(v_path.size(), v_ans_path.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].path.c_str(), v_ans_path[i].c_str());
	ASSERT_EQ(v_path[i].type, v_ans_type[i]);
    }
}
TEST(glob, glob_pt_txt){
    const char* path = R"(./test/src/file/glob_test/*.txt)";
    std::vector<struct sstd::pathAndType> v_path = sstd::glob_pt(path);

    // compare v_path with v_ans
    std::vector<std::string> v_ans_path={"./test/src/file/glob_test/a.txt",
                                         "./test/src/file/glob_test/b.txt",
                                         "./test/src/file/glob_test/c.txt"};
    std::vector<char> v_ans_type={'f',
                                  'f',
                                  'f'};
    ASSERT_EQ(v_ans_path.size(), v_ans_type.size());
    
    ASSERT_EQ(v_path.size(), v_ans_path.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].path.c_str(), v_ans_path[i].c_str());
	ASSERT_EQ(v_path[i].type, v_ans_type[i]);
    }
}
TEST(glob, glob_pt_zip){
    const char* path = R"(./test/src/file/glob_test/*.zip)";
    std::vector<struct sstd::pathAndType> v_path = sstd::glob_pt(path);

    // compare v_path with v_ans
    std::vector<std::string> v_ans_path={"./test/src/file/glob_test/a.zip",
                                         "./test/src/file/glob_test/b.zip",
                                         "./test/src/file/glob_test/c.zip"};
    std::vector<char> v_ans_type={'f',
                                  'f',
                                  'f'};
    ASSERT_EQ(v_ans_path.size(), v_ans_type.size());
    
    ASSERT_EQ(v_path.size(), v_ans_path.size());
    for(uint i=0; i<v_path.size(); ++i){
	ASSERT_STREQ(v_path[i].path.c_str(), v_ans_path[i].c_str());
	ASSERT_EQ(v_path[i].type, v_ans_type[i]);
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
