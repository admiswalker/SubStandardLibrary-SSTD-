#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(tinyInterpreter, getCommandList_char){
    // reading "tinyInterpreter.txt" to vv_ret
    std::vector<std::string> v_line = sstd::getCommandList(R"(./test/src_test/file/tinyInterpreter.txt)");
    
    sstd::vvec<std::string> vv_ret(v_line.size());
    for(uint i=0; i<v_line.size(); ++i){
        std::vector<std::string> v_cmd = sstd::splitByComma(v_line[i]);
	for(uint n=0; n<v_cmd.size(); ++n){
	    vv_ret[i] <<= v_cmd[n];
	}
    }

    // compareing vv_ret with vv_ans
    sstd::vvec<std::string> vv_ans={{"cmd01", "cmd02",      "", "cmd04"},
				    {"cmd05", "cmd06", "cmd07"         },
				    {"cmd09", "cmd10", "cmd11", "cmd12"}};
    ASSERT_TRUE(vv_ret == vv_ans);
}
TEST(tinyInterpreter, getCommandList_str){
    // reading "tinyInterpreter.txt" to vv_ret
    std::string path = "./test/src_test/file/tinyInterpreter.txt";
    std::vector<std::string> v_line = sstd::getCommandList( path );
    
    sstd::vvec<std::string> vv_ret(v_line.size());
    for(uint i=0; i<v_line.size(); ++i){
        std::vector<std::string> v_cmd = sstd::splitByComma(v_line[i]);
	for(uint n=0; n<v_cmd.size(); ++n){
	    vv_ret[i] <<= v_cmd[n];
	}
    }

    // compareing vv_ret with vv_ans
    sstd::vvec<std::string> vv_ans={{"cmd01", "cmd02",      "", "cmd04"},
				    {"cmd05", "cmd06", "cmd07"         },
				    {"cmd09", "cmd10", "cmd11", "cmd12"}};
    ASSERT_TRUE(vv_ret == vv_ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(tinyInterpreter, _txt2vCmdList){
    std::string s;
    s += "// comment\n";        // lineNum 1
    s += "cmd1, cmd2, cmd3;\n"; // lineNum 2
    s += "\n";                  // lineNum 3
    s += "cmd4, cmd5, cmd6;\n"; // lineNum 4
    
    std::vector<uint> vLineNum;
    std::vector<std::vector<std::string>> vCmdList;
    const char* fileName = "example.txt";
    const uchar* str = (const uchar*)s.c_str();
    bool ret = sstd::_txt2vCmdList(vLineNum, vCmdList, fileName, str);
//    sstd::printn(ret);
//    sstd::printn(vCmdList);
//    sstd::printn(vLineNum);
    
    ASSERT_TRUE(ret);
    ASSERT_EQ(vLineNum[0], (uint)2);
    ASSERT_EQ(vLineNum[1], (uint)4);
    ASSERT_STREQ(vCmdList[0][0].c_str(), "cmd1");
    ASSERT_STREQ(vCmdList[0][1].c_str(), "cmd2");
    ASSERT_STREQ(vCmdList[0][2].c_str(), "cmd3");
    ASSERT_STREQ(vCmdList[1][0].c_str(), "cmd4");
    ASSERT_STREQ(vCmdList[1][1].c_str(), "cmd5");
    ASSERT_STREQ(vCmdList[1][2].c_str(), "cmd6");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define testInterface_init01                                            \
    std::string path = "./test/src_test/file/tinyInterpreter.txt";      \
    std::vector<std::vector<std::string>> vCmdList;
#define testInterface_runTest01                                         \
    sstd::vvec<std::string> vv_ans={{"cmd01", "cmd02",      "", "cmd04"}, \
				    {"cmd05", "cmd06", "cmd07"         }, \
				    {"cmd09", "cmd10", "cmd11", "cmd12"}}; \
    ASSERT_TRUE(ret);                                                   \
    ASSERT_TRUE(vCmdList == vv_ans);

TEST(tinyInterpreter, txt2vCmdList_c_wo_vLineNum){
    testInterface_init01;
    bool ret = sstd::txt2vCmdList(vCmdList, path.c_str());
    testInterface_runTest01;
}
TEST(tinyInterpreter, txt2vCmdList_s_wo_vLineNum){
    testInterface_init01;
    bool ret = sstd::txt2vCmdList(vCmdList, path);
    testInterface_runTest01;
}

#undef testInterface_runTest01
#undef testInterface_init01

//---

#define testInterface_init02                                            \
    std::string path = "./test/src_test/file/tinyInterpreter.txt";      \
    std::vector<uint> vLineNum;                                         \
    std::vector<std::vector<std::string>> vCmdList;
#define testInterface_runTest02                                         \
    sstd::vvec<std::string> vv_ans={{"cmd01", "cmd02",      "", "cmd04"}, \
				    {"cmd05", "cmd06", "cmd07"         }, \
				    {"cmd09", "cmd10", "cmd11", "cmd12"}}; \
    ASSERT_TRUE(ret);                                                   \
    ASSERT_EQ(vLineNum[0], (uint)15);                                   \
    ASSERT_EQ(vLineNum[1], (uint)16);                                   \
    ASSERT_EQ(vLineNum[2], (uint)17);                                   \
    ASSERT_TRUE(vCmdList == vv_ans);

TEST(tinyInterpreter, txt2vCmdList_c){
    testInterface_init02;
    bool ret = sstd::txt2vCmdList(vLineNum, vCmdList, path.c_str());
    testInterface_runTest02;
}
TEST(tinyInterpreter, txt2vCmdList_s){
    testInterface_init02;
    bool ret = sstd::txt2vCmdList(vLineNum, vCmdList, path);
    testInterface_runTest02;
}

#undef testInterface_runTest02
#undef testInterface_init02

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
