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
    printf("hello\n");

    // example input
//    int argc = 1;
    const int argc = 6;
    const char *argv[] = {
                    "./a.out",
                    "get-lines",
                    "1",
                    "3",
                    "5",
                    "--rm-head-spaces"
    };
//    sstd::printn(argc);
//    sstd::printn(argv[0]);
    
    enum class CmdID{
                     EMPTY,
                     GET_LINES,
                     GET_LINE
    };
//    sstd::printn((int)CmdID::EMPTY);
//    sstd::printn((int)CmdID::GET_LINES);
//    sstd::printn((int)CmdID::GET_LINE);
    
    bool rm_hs, rm_ts;
    std::vector<int> vlineNum;
    int num;
    
    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::cmd((int)CmdID::EMPTY, "", 0)
                          , sstd::arg_rule::cmd((int)CmdID::GET_LINES, vlineNum, {}, "get-lines", -1)
                          , sstd::arg_rule::cmd((int)CmdID::GET_LINE , num,       0, "get-line" ,  1)
                          , sstd::arg_rule::opt(rm_hs, true, "-h", "--rm-head-spaces", 0)
//                    , sstd::arg_rule::opt(rm_ts, false, "-t", "--rm-tail-spaces", 1)
                    );

//    printf("\n");
//    printf("\n");
    sstd::printn(ap._get_arg_vCmd());
//    printf("\n");
//    printf("\n");
    sstd::printn(ap._get_arg_vOpt());
//    printf("\n");
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

#define TEST_OPT_BOOL(args, DEF, CNT, ANS)                              \
    const int argc = args.size();                                       \
    const char **argv = args.data();                                    \
                                                                        \
    bool rm_hs=!ANS;                                                    \
                                                                        \
    sstd::argparse ap;                                                  \
    int cmd_id = ap.parse(argc, argv                                    \
                          , sstd::arg_rule::opt(rm_hs, DEF, "-o", "--option", CNT) \
                          );                                            \
                                                                        \
    ASSERT_EQ(cmd_id, -2);                                              \
    ASSERT_TRUE(rm_hs==ANS);
TEST(argparse, opt_bool_full_true_as_default){
    std::vector<const char*> args = {"./a.out", "--option"};
    TEST_OPT_BOOL(args, true, 0, true);
}
TEST(argparse, opt_bool_full_false_as_default){
    std::vector<const char*> args = {"./a.out", "--option"};
    TEST_OPT_BOOL(args, false, 0, false);
}
TEST(argparse, opt_bool_full_true_1){
    std::vector<const char*> args = {"./a.out", "--option", "true"};
    TEST_OPT_BOOL(args, true, 1, true);
}
TEST(argparse, opt_bool_full_false_1){
    std::vector<const char*> args = {"./a.out", "--option", "false"};
    TEST_OPT_BOOL(args, true, 1, false);
}

//---

TEST(argparse, opt_bool_short_true_0){
    std::vector<const char*> args = {"./a.out", "-o"};
    TEST_OPT_BOOL(args, true, 0, true);
}
TEST(argparse, opt_bool_short_false_0){
    std::vector<const char*> args = {"./a.out", "-o"};
    TEST_OPT_BOOL(args, false, 0, false);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
