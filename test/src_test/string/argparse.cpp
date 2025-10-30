#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
/*
enum class CmdID{
                 EMPTY,
                 GET_LINES,
                 GET_LINE
};
TEST(argparse, example01){

    bool rm_hs, rm_ts;
    std::vector<int> vlineNum;
    int num;

    sstd::argparse ap;
    int cmd_id = ap(argc, argv,
                    sstd::argparse::cmd_rule(CmdID::EMPTY, "", 0),
                    sstd::argparse::cmd_rule(CmdID::GET_LINES, vlineNum, {}, "get lines", -1),
                    sstd::argparse::cmd_rule(CmdID::GET_LINE , num,       0, "get line" ,  1),
                    sstd::argparse::opt_rule(rm_hs, false, "-h", "--rm-head-spaces", 1),
                    sstd::argparse::opt_rule(rm_ts, false, "-t", "--rm-tail-spaces", 1)
                    );
    
    switch(cmd_id){
    case CmdID::EMPTY : { ap.print_help(); } break;
    case CmdID::GET_LINES: { // process get lines
    } break;
    case CmdID::GET_LINE : { // process get line
    } break;
    default : { printf("error: %s\n", ap.error.c_str()); }
    }
    
    return 0;
}
//*/

//---

TEST(argparse, argc_0){

    // example input
    std::vector<const char*> args = {
                    "./a.out",
                    "get-lines",
                    "1",
                    "3",
                    "5",
                    "--rm-head-spaces"
    };
    const int argc = args.size();
    const char **argv = args.data();
    
    enum class CmdID{
                     EMPTY,
                     GET_LINE,
                     GET_LINES
    };
    
    bool rm_hs, rm_ts;
    std::vector<int> vlineNum;
    int num;
    
    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::cmd((int)CmdID::EMPTY, "", 0)
                          , sstd::arg_rule::cmd((int)CmdID::GET_LINES, vlineNum, {}, "get-lines", -1)
                          , sstd::arg_rule::cmd((int)CmdID::GET_LINE , num,       0, "get-line" ,  1)
                          , sstd::arg_rule::opt(rm_hs, true, "-h", "--rm-head-spaces", 0)
//                          , sstd::arg_rule::opt(rm_ts, false, "-t", "--rm-tail-spaces", 1)
                    );

    printf("\n");
    sstd::printn_all(cmd_id);
    
    switch(cmd_id){
    case (int)CmdID::EMPTY : {
//        ap.print_help();
    } break;
    case (int)CmdID::GET_LINES: {
        sstd::printn_all(vlineNum);
        sstd::printn_all(rm_hs);
        // process get lines
    } break;
    case (int)CmdID::GET_LINE : {
        // process get line
    } break;
    default : {
//        printf("error: %s\n", ap.error.c_str());
    }
    }
}

//---

TEST(argparse, cmd_expect_m1_in_3){
    std::vector<const char*> args = {"./a.out", "get-lines", "1", "3", "5"};
    const int argc = args.size();
    const char **argv = args.data();
    
    enum class CmdID{
                     EMPTY,
                     GET_LINE,
                     GET_LINES
    };
    
    std::vector<int> vlineNum;
    
    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::cmd((int)CmdID::GET_LINES, vlineNum, {}, "get-lines", -1)
                          );

    ASSERT_EQ(cmd_id, (int)CmdID::GET_LINES);
    ASSERT_TRUE(vlineNum==std::vector<int>({1,3,5}));
}

//---
// Normal testing / 正常系

#define TEST_OPT_BOOL(ARGS, DEFAULT, CNT, ANS)                          \
    const int argc = ARGS.size();                                       \
    const char **argv = ARGS.data();                                    \
                                                                        \
    bool rm_hs=!ANS;                                                    \
                                                                        \
    sstd::argparse ap;                                                  \
    int cmd_id = ap.parse(argc, argv                                    \
                          , sstd::arg_rule::opt(rm_hs, DEFAULT, "-o", "--option", CNT) \
                          );                                            \
    ASSERT_EQ(cmd_id, -2);                                              \
    ASSERT_TRUE(rm_hs==ANS);
TEST(argparse, opt_bool_full_true_as_default ){ std::vector<const char*> args = {"./a.out", "--option"}; TEST_OPT_BOOL(args, true,  0, true);   }
TEST(argparse, opt_bool_full_false_as_default){ std::vector<const char*> args = {"./a.out", "--option"}; TEST_OPT_BOOL(args, false, 0, false); }

TEST(argparse, opt_bool_full_true_1){ std::vector<const char*> args = {"./a.out", "--option", "true"}; TEST_OPT_BOOL(args, false, 1, true); }
TEST(argparse, opt_bool_full_True_1){ std::vector<const char*> args = {"./a.out", "--option", "True"}; TEST_OPT_BOOL(args, false, 1, true); }
TEST(argparse, opt_bool_full_T_1   ){ std::vector<const char*> args = {"./a.out", "--option", "T"};    TEST_OPT_BOOL(args, false, 1, true); }
TEST(argparse, opt_bool_full_1_1   ){ std::vector<const char*> args = {"./a.out", "--option", "1"};    TEST_OPT_BOOL(args, false, 1, true); }
TEST(argparse, opt_bool_full_false_1){ std::vector<const char*> args = {"./a.out", "--option", "false"}; TEST_OPT_BOOL(args, true, 1, false); }
TEST(argparse, opt_bool_full_False_1){ std::vector<const char*> args = {"./a.out", "--option", "False"}; TEST_OPT_BOOL(args, true, 1, false); }
TEST(argparse, opt_bool_full_F_1    ){ std::vector<const char*> args = {"./a.out", "--option", "F"    }; TEST_OPT_BOOL(args, true, 1, false); }
TEST(argparse, opt_bool_full_0_1    ){ std::vector<const char*> args = {"./a.out", "--option", "0"    }; TEST_OPT_BOOL(args, true, 1, false); }

//---
// Negative testing / 異常系

TEST(argparse, NT_opt_invalid_arg){
    std::vector<const char*> args = {"./a.out", "--option", "xxx"};
    
    const int argc = args.size();
    const char **argv = args.data();

    bool rm_hs=false;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::opt(rm_hs, false, "-o", "--option", 1)
                          );
    sstd::printn_all(ap.err());
    
    ASSERT_EQ(cmd_id, -2);
    ASSERT_TRUE(rm_hs==true);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
