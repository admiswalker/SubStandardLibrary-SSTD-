#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(path, path2basePath_case01){
    const char* pPath="";
    ASSERT_STREQ(sstd::path2basePath(pPath).c_str(), "");
}
TEST(path, path2basePath_case02){
    const char* pPath="/";
    ASSERT_STREQ(sstd::path2basePath(pPath).c_str(), "");
}
TEST(path, path2basePath_case03){
    const char* pPath="./";
    ASSERT_STREQ(sstd::path2basePath(pPath).c_str(), ".");
}
TEST(path, path2basePath_case04){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(sstd::path2basePath(pPath).c_str(), "./abc/def");
}


TEST(path, path2basePath_ss_case01){
    std::string path="";
    ASSERT_STREQ(sstd::path2basePath(path).c_str(), "");
}


TEST(path, path2basePath_woWC_case01){
    const char* pPath="";
    ASSERT_STREQ(sstd::path2basePath_woWC(pPath).c_str(), "");
}
TEST(path, path2basePath_woWC_case02){
    const char* pPath="/";
    ASSERT_STREQ(sstd::path2basePath_woWC(pPath).c_str(), "");
}
TEST(path, path2basePath_woWC_case03){
    const char* pPath="./";
    ASSERT_STREQ(sstd::path2basePath_woWC(pPath).c_str(), ".");
}
TEST(path, path2basePath_woWC_case04){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(sstd::path2basePath_woWC(pPath).c_str(), "./abc/def");
}
TEST(path, path2basePath_woWC_case05){
    const char* pPath="./abc/d*f/text.abc.txt";
    ASSERT_STREQ(sstd::path2basePath_woWC(pPath).c_str(), "./abc");
}
TEST(path, path2basePath_woWC_case06){
    const char* pPath="./abc/d?f/text.abc.txt";
    ASSERT_STREQ(sstd::path2basePath_woWC(pPath).c_str(), "./abc");
}

TEST(path, path2basePath_woWC_ss_case01){
    std::string path="";
    ASSERT_STREQ(sstd::path2basePath_woWC(path).c_str(), "");
}

//---

TEST(path, path2dirName_case01){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(sstd::path2dirName(pPath).c_str(), "text.abc.txt");

    // This type of path refered as a direcotry.
    // If you want to parse this type of path, write
    //   | std::string tmp = sstd::path2basePath(pPath);
    //   | sstd::path2dirName(tmp.c_str());
    // instead.
}
TEST(path, path2dirName_case02){
    const char* pPath="./abc/def";
    ASSERT_STREQ(sstd::path2dirName(pPath).c_str(), "def");
}
TEST(path, path2dirName_case03){
    const char* pPath="./abc/def/";
    ASSERT_STREQ(sstd::path2dirName(pPath).c_str(), "def");
}

TEST(path, path2dirName_ss_case03){
    std::string path="./abc/def/";
    ASSERT_STREQ(sstd::path2dirName(path).c_str(), "def");
}


TEST(path, path2dirName_begin_idx_case01){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(&pPath[sstd::path2dirName_begin_idx(pPath)], "text.abc.txt");

    // This type of path refered as a direcotry.
    // If you want to parse this type of path, write
    //   | std::string tmp = sstd::path2basePath(pPath);
    //   | sstd::path2dirName(tmp.c_str());
    // instead.
}
TEST(path, path2dirName_begin_idx_case02){
    const char* pPath="./abc/def";
    ASSERT_STREQ(&pPath[sstd::path2dirName_begin_idx(pPath)], "def");
}
TEST(path, path2dirName_begin_idx_case03){
    const char* pPath="./abc/def/";
    ASSERT_STREQ(&pPath[sstd::path2dirName_begin_idx(pPath)], "def/");
}

TEST(path, path2dirName_begin_idx_us_case03){
    std::string path="./abc/def/";
    ASSERT_STREQ(&path[sstd::path2dirName_begin_idx(path)], "def/");
}


TEST(path, path2dirName_end_idx_case01){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(&pPath[sstd::path2dirName_end_idx(pPath)], "text.abc.txt");

    // This type of path refered as a direcotry.
    // If you want to parse this type of path, write
    //   | std::string tmp = sstd::path2basePath(pPath);
    //   | sstd::path2dirName(tmp.c_str());
    // instead.
}
TEST(path, path2dirName_end_idx_case02){
    const char* pPath="./abc/def";
    ASSERT_STREQ(&pPath[sstd::path2dirName_end_idx(pPath)], "def");
}
TEST(path, path2dirName_end_idx_case03){
    const char* pPath="./abc/def/";
    ASSERT_STREQ(&pPath[sstd::path2dirName_end_idx(pPath)], "");
}

TEST(path, path2dirName_end_idx_us_case03){
    std::string path="./abc/def/";
    ASSERT_STREQ(&path[sstd::path2dirName_end_idx(path)], "");
}


TEST(path, path2dirName_end_idx_owWC_case01){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(&pPath[sstd::path2dirName_end_idx(pPath)], "text.abc.txt");

    // This type of path refered as a direcotry.
    // If you want to parse this type of path, write
    //   | std::string tmp = sstd::path2basePath(pPath);
    //   | sstd::path2dirName(tmp.c_str());
    // instead.
}
TEST(path, path2dirName_end_idx_woWC_case02){
    const char* pPath="./abc/def";
    ASSERT_STREQ(&pPath[sstd::path2dirName_end_idx_woWC(pPath)], "def");
}
TEST(path, path2dirName_end_idx_woWC_case03){
    const char* pPath="./abc/def/";
    ASSERT_STREQ(&pPath[sstd::path2dirName_end_idx_woWC(pPath)], "");
}
TEST(path, path2dirName_end_idx_woWC_case04){
    const char* pPath="./abc/def/*";
    ASSERT_STREQ(&pPath[sstd::path2dirName_end_idx_woWC(pPath)], "*");
}
TEST(path, path2dirName_end_idx_woWC_case05){
    const char* pPath="./abc/def/?";
    ASSERT_STREQ(&pPath[sstd::path2dirName_end_idx_woWC(pPath)], "?");
}
TEST(path, path2dirName_end_idx_woWC_case06){
    const char* pPath="./abc/de*/?";
    ASSERT_STREQ(&pPath[sstd::path2dirName_end_idx_woWC(pPath)], "de*/?");
}

TEST(path, path2dirName_end_idx_woWC_us_case06){
    std::string path="./abc/de*/?";
    ASSERT_STREQ(&path[sstd::path2dirName_end_idx_woWC(path)], "de*/?");
}

//---

TEST(path, path2fileName_cc){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(sstd::path2fileName(pPath), "text.abc.txt");
}
TEST(path, path2fileName_ss){
    std::string path="./abc/def/text.abc.txt";
    ASSERT_STREQ(sstd::path2fileName(path).c_str(), "text.abc.txt");
}


TEST(path, path2fileName_woExt){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(sstd::path2fileName_woExt(pPath).c_str(), "text.abc");
}


TEST(path, path2fileExt_cc){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(sstd::path2fileExt(pPath), "txt");
}
TEST(path, path2fileExt_ss){
    std::string path="./abc/def/text.abc.txt";
    ASSERT_STREQ(sstd::path2fileExt(path).c_str(), "txt");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(path, parsePath_case01){
    std::vector<std::string> v = sstd::parsePath(R"(C:\a\b)");
    std::vector<std::string> v_ans = {"C:", "a", "b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}
TEST(path, parsePath_case02){
    std::vector<std::string> v = sstd::parsePath(R"(/a/b)");
    std::vector<std::string> v_ans = {"a", "b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}
TEST(path, parsePath_case03){
    std::vector<std::string> v = sstd::parsePath(R"(./a/b)");
    std::vector<std::string> v_ans = {".", "a", "b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}
TEST(path, parsePath_case04){
    std::vector<std::string> v = sstd::parsePath(R"(../a/b)");
    std::vector<std::string> v_ans = {"..", "a", "b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}
TEST(path, parsePath_case05){
    std::vector<std::string> v = sstd::parsePath(R"(../a/b/)");
    std::vector<std::string> v_ans = {"..", "a", "b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}
TEST(path, parsePath_case06){
    std::vector<std::string> v = sstd::parsePath(R"(a/b/)");
    std::vector<std::string> v_ans = {"a", "b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}


TEST(path, parsePath_wBasePath_case01){
    std::vector<std::string> v = sstd::parsePath_wBasePath(R"(C:\a\b)");
    std::vector<std::string> v_ans = {"C:", "C:/a", "C:/a/b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}
TEST(path, parsePath_wBasePath_case02){
    std::vector<std::string> v = sstd::parsePath_wBasePath(R"(/a/b)");
    std::vector<std::string> v_ans = {"/a", "/a/b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}
TEST(path, parsePath_wBasePath_case03){
    std::vector<std::string> v = sstd::parsePath_wBasePath(R"(./a/b)");
    std::vector<std::string> v_ans = {".", "./a", "./a/b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}
TEST(path, parsePath_wBasePath_case04){
    std::vector<std::string> v = sstd::parsePath_wBasePath(R"(../a/b)");
    std::vector<std::string> v_ans = {"..", "../a", "../a/b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}
TEST(path, parsePath_wBasePath_case05){
    std::vector<std::string> v = sstd::parsePath_wBasePath(R"(../a/b/)");
    std::vector<std::string> v_ans = {"..", "../a", "../a/b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}
TEST(path, parsePath_wBasePath_case06){
    std::vector<std::string> v = sstd::parsePath_wBasePath(R"(a/b/)");
    std::vector<std::string> v_ans = {"a", "a/b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(path, isFile_pChar){
    ASSERT_TRUE(sstd::isFile("./main.cpp"));
    ASSERT_FALSE(sstd::isFile("./notExist"));
    ASSERT_FALSE(sstd::isFile("./sstd"));
}
TEST(path, isFile_str){
    ASSERT_TRUE(sstd::isFile(std::string("./main.cpp")));
    ASSERT_FALSE(sstd::isFile(std::string("./notExist")));
    ASSERT_FALSE(sstd::isFile(std::string("./sstd")));
}
TEST(path, isDir_pChar){
    ASSERT_FALSE(sstd::isDir("./main.cpp"));
    ASSERT_FALSE(sstd::isDir("./notExist"));
    ASSERT_TRUE(sstd::isDir("./sstd"));
}
TEST(path, isDir_str){
    ASSERT_FALSE(sstd::isDir(std::string("./main.cpp")));
    ASSERT_FALSE(sstd::isDir(std::string("./notExist")));
    ASSERT_TRUE(sstd::isDir(std::string("./sstd")));
}
TEST(path, fileExist_pChar){
    ASSERT_TRUE(sstd::fileExist("./main.cpp"));
    ASSERT_FALSE(sstd::fileExist("./notExist"));
    ASSERT_FALSE(sstd::fileExist("./sstd"));
}
TEST(path, fileExist_str){
    ASSERT_TRUE(sstd::fileExist(std::string("./main.cpp")));
    ASSERT_FALSE(sstd::fileExist(std::string("./notExist")));
    ASSERT_FALSE(sstd::fileExist(std::string("./sstd")));
}
TEST(path, dirExist_pChar){
    ASSERT_FALSE(sstd::dirExist("./main.cpp"));
    ASSERT_FALSE(sstd::dirExist("./notExist"));
    ASSERT_TRUE(sstd::dirExist("./sstd"));
}
TEST(path, dirExist_str){
    ASSERT_FALSE(sstd::dirExist(std::string("./main.cpp")));
    ASSERT_FALSE(sstd::dirExist(std::string("./notExist")));
    ASSERT_TRUE(sstd::dirExist(std::string("./sstd")));
}
TEST(path, pathExist_pChar){
    ASSERT_TRUE(sstd::pathExist("./main.cpp"));
    ASSERT_FALSE(sstd::pathExist("./notExist"));
    ASSERT_TRUE(sstd::pathExist("./sstd"));
}
TEST(path, pathExist_str){
    ASSERT_TRUE(sstd::pathExist(std::string("./main.cpp")));
    ASSERT_FALSE(sstd::pathExist(std::string("./notExist")));
    ASSERT_TRUE(sstd::pathExist(std::string("./sstd")));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Below functions are the not recommended to use. (Below functions will be delete on sstd ver 3.x.x).

TEST(path, getPath_case01){
    const char* pPath="";
    ASSERT_STREQ(sstd::getPath(pPath).c_str(), "");
}
TEST(path, getPath_case02){
    const char* pPath="/";
    ASSERT_STREQ(sstd::getPath(pPath).c_str(), "");
}
TEST(path, getPath_case03){
    const char* pPath="./";
    ASSERT_STREQ(sstd::getPath(pPath).c_str(), ".");
}
TEST(path, getPath_case04){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(sstd::getPath(pPath).c_str(), "./abc/def");
}


TEST(path, getPath_woWC_case01){
    const char* pPath="";
    ASSERT_STREQ(sstd::getPath_woWC(pPath).c_str(), "");
}
TEST(path, getPath_woWC_case02){
    const char* pPath="/";
    ASSERT_STREQ(sstd::getPath_woWC(pPath).c_str(), "");
}
TEST(path, getPath_woWC_case03){
    const char* pPath="./";
    ASSERT_STREQ(sstd::getPath_woWC(pPath).c_str(), ".");
}
TEST(path, getPath_woWC_case04){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(sstd::getPath_woWC(pPath).c_str(), "./abc/def");
}
TEST(path, getPath_woWC_case05){
    const char* pPath="./abc/d*f/text.abc.txt";
    ASSERT_STREQ(sstd::getPath_woWC(pPath).c_str(), "./abc");
}
TEST(path, getPath_woWC_case06){
    const char* pPath="./abc/d?f/text.abc.txt";
    ASSERT_STREQ(sstd::getPath_woWC(pPath).c_str(), "./abc");
}


TEST(path, getDirName_case01){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(sstd::getDirName(pPath).c_str(), "text.abc.txt");

    // This type of path refered as a direcotry.
    // If you want to parse this type of path, write
    //   | std::string tmp = sstd::getPath(pPath);
    //   | sstd::getDirName(tmp.c_str());
    // instead.
}
TEST(path, getDirName_case02){
    const char* pPath="./abc/def";
    ASSERT_STREQ(sstd::getDirName(pPath).c_str(), "def");
}
TEST(path, getDirName_case03){
    const char* pPath="./abc/def/";
    ASSERT_STREQ(sstd::getDirName(pPath).c_str(), "def");
}


TEST(path, getDirName_begin_idx_case01){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(&pPath[sstd::getDirName_begin_idx(pPath)], "text.abc.txt");

    // This type of path refered as a direcotry.
    // If you want to parse this type of path, write
    //   | std::string tmp = sstd::getPath(pPath);
    //   | sstd::getDirName(tmp.c_str());
    // instead.
}
TEST(path, getDirName_begin_idx_case02){
    const char* pPath="./abc/def";
    ASSERT_STREQ(&pPath[sstd::getDirName_begin_idx(pPath)], "def");
}
TEST(path, getDirName_begin_idx_case03){
    const char* pPath="./abc/def/";
    ASSERT_STREQ(&pPath[sstd::getDirName_begin_idx(pPath)], "def/");
}


TEST(path, getDirName_end_idx_case01){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(&pPath[sstd::getDirName_end_idx(pPath)], "text.abc.txt");

    // This type of path refered as a direcotry.
    // If you want to parse this type of path, write
    //   | std::string tmp = sstd::getPath(pPath);
    //   | sstd::getDirName(tmp.c_str());
    // instead.
}
TEST(path, getDirName_end_idx_case02){
    const char* pPath="./abc/def";
    ASSERT_STREQ(&pPath[sstd::getDirName_end_idx(pPath)], "def");
}
TEST(path, getDirName_end_idx_case03){
    const char* pPath="./abc/def/";
    ASSERT_STREQ(&pPath[sstd::getDirName_end_idx(pPath)], "");
}


TEST(path, getDirName_end_idx_owWC_case01){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(&pPath[sstd::getDirName_end_idx(pPath)], "text.abc.txt");

    // This type of path refered as a direcotry.
    // If you want to parse this type of path, write
    //   | std::string tmp = sstd::getPath(pPath);
    //   | sstd::getDirName(tmp.c_str());
    // instead.
}
TEST(path, getDirName_end_idx_woWC_case02){
    const char* pPath="./abc/def";
    ASSERT_STREQ(&pPath[sstd::getDirName_end_idx_woWC(pPath)], "def");
}
TEST(path, getDirName_end_idx_woWC_case03){
    const char* pPath="./abc/def/";
    ASSERT_STREQ(&pPath[sstd::getDirName_end_idx_woWC(pPath)], "");
}
TEST(path, getDirName_end_idx_woWC_case04){
    const char* pPath="./abc/def/*";
    ASSERT_STREQ(&pPath[sstd::getDirName_end_idx_woWC(pPath)], "*");
}
TEST(path, getDirName_end_idx_woWC_case05){
    const char* pPath="./abc/def/?";
    ASSERT_STREQ(&pPath[sstd::getDirName_end_idx_woWC(pPath)], "?");
}
TEST(path, getDirName_end_idx_woWC_case06){
    const char* pPath="./abc/de*/?";
    ASSERT_STREQ(&pPath[sstd::getDirName_end_idx_woWC(pPath)], "de*/?");
}


TEST(path, getFileName){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(sstd::getFileName(pPath), "text.abc.txt");
}



TEST(path, getFileName_withoutExtension){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(sstd::getFileName_withoutExtension(pPath).c_str(), "text.abc");
}


TEST(path, getExtension){
    const char* pPath="./abc/def/text.abc.txt";
    ASSERT_STREQ(sstd::getExtension(pPath), "txt");
}

//---

TEST(path, parsePath_withBase_case01){
    std::vector<std::string> v = sstd::parsePath_withBase(R"(C:\a\b)");
    std::vector<std::string> v_ans = {"C:", "C:/a", "C:/a/b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}
TEST(path, parsePath_withBase_case02){
    std::vector<std::string> v = sstd::parsePath_withBase(R"(/a/b)");
    std::vector<std::string> v_ans = {"/a", "/a/b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}
TEST(path, parsePath_withBase_case03){
    std::vector<std::string> v = sstd::parsePath_withBase(R"(./a/b)");
    std::vector<std::string> v_ans = {".", "./a", "./a/b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}
TEST(path, parsePath_withBase_case04){
    std::vector<std::string> v = sstd::parsePath_withBase(R"(../a/b)");
    std::vector<std::string> v_ans = {"..", "../a", "../a/b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}
TEST(path, parsePath_withBase_case05){
    std::vector<std::string> v = sstd::parsePath_withBase(R"(../a/b/)");
    std::vector<std::string> v_ans = {"..", "../a", "../a/b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}
TEST(path, parsePath_withBase_case06){
    std::vector<std::string> v = sstd::parsePath_withBase(R"(a/b/)");
    std::vector<std::string> v_ans = {"a", "a/b"};
    
    ASSERT_EQ(v.size(), v_ans.size());
    for(uint i=0; i<v.size(); ++i){
        ASSERT_STREQ(v[i].c_str(), v_ans[i].c_str());
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
