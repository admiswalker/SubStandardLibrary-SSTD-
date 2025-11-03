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

TEST(argparse, complicated_test_01){

    // example input
    std::vector<const char*> args = {
                    "./a.out",
                    "get-lines",
                    "1",
                    "3",
                    "5",
                    "--rm-head-spaces",
                    "--rm-tail-spaces"
    };
    const int argc = args.size();
    const char **argv = args.data();
    
    enum class CmdID{
                     EMPTY,
                     GET_LINE,
                     GET_LINES
    };
    
    bool rm_hs=false, rm_ts=false;
    std::vector<int> vlineNum;
    int num;
    
    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::cmd((int)CmdID::EMPTY, "", 0)
                          , sstd::arg_rule::cmd((int)CmdID::GET_LINES, vlineNum, {}, "get-lines", -1)
                          , sstd::arg_rule::cmd((int)CmdID::GET_LINE , num,       0, "get-line" ,  1)
                          , sstd::arg_rule::opt(rm_hs, true, "-h", "--rm-head-spaces", 0)
                          , sstd::arg_rule::opt(rm_ts, true, "-t", "--rm-tail-spaces", 0)
                    );
//    sstd::printn_all(cmd_id);
    ASSERT_EQ(cmd_id, (int)CmdID::GET_LINES);
    
    switch(cmd_id){
    case (int)CmdID::EMPTY : {
//        ap.print_help();
    } break;
    case (int)CmdID::GET_LINES: {
        // process get lines
        ASSERT_TRUE(vlineNum==std::vector<int>({1,3,5}));
        ASSERT_TRUE(rm_hs==true);
        ASSERT_TRUE(rm_ts==true);
    } break;
    case (int)CmdID::GET_LINE : {
        // process get line
    } break;
    case (int)sstd::arg_rule::num_error : {
        sstd::pdbg_err("%s", ap.err().c_str());
    } break;
    default : {
        sstd::pdbg_err("Unexpected error.");
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

// bool
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
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_command_does_not_exist);      \
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

TEST(argparse, short_opt_1){
    std::vector<const char*> args = {"./a.out", "-a"};
    const int argc = args.size();
    const char **argv = args.data();

    bool opt_a=false;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::opt(opt_a, true, "-a", "--option-a", 0)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_command_does_not_exist);
    ASSERT_TRUE(opt_a==true);
}
TEST(argparse, short_opt_2){
    std::vector<const char*> args = {"./a.out", "-ab"};
    const int argc = args.size();
    const char **argv = args.data();

    bool opt_a=false;
    bool opt_b=false;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::opt(opt_a, true, "-a", "--option-a", 0)
                          , sstd::arg_rule::opt(opt_b, true, "-b", "--option-b", 0)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_command_does_not_exist);
    ASSERT_TRUE(opt_a==true);
    ASSERT_TRUE(opt_b==true);
}
TEST(argparse, short_opt_3){
    std::vector<const char*> args = {"./a.out", "-abc"};
    const int argc = args.size();
    const char **argv = args.data();

    bool opt_a=false;
    bool opt_b=false;
    bool opt_c=false;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::opt(opt_a, true, "-a", "--option-a", 0)
                          , sstd::arg_rule::opt(opt_b, true, "-b", "--option-b", 0)
                          , sstd::arg_rule::opt(opt_c, true, "-c", "--option-c", 0)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_command_does_not_exist);
    ASSERT_TRUE(opt_a==true);
    ASSERT_TRUE(opt_b==true);
    ASSERT_TRUE(opt_c==true);
}

TEST(argparse, short_opt_arg_1){
    std::vector<const char*> args = {"./a.out", "-o", "T"};
    const int argc = args.size();
    const char **argv = args.data();

    bool opt=true;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::opt(opt, false, "-o", "--option", 1)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_command_does_not_exist);
    ASSERT_TRUE(opt==true);
}

/*
// char
TEST(argparse, cmd_char){
}
TEST(argparse, cmd_vchar){
    std::vector<const char*> args = {"./a.out", "cmd", "a", "b", "c"};
    const int argc = args.size();
    const char **argv = args.data();

    enum class CmdID{SAMPLE_CMD};
    
    std::vector<char> v;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::cmd((int)CmdID::SAMPLE_CMD, v, {}, "cmd", -1)
                          );
    sstd::printn(ap.err());
    ASSERT_EQ(cmd_id, (int)CmdID::SAMPLE_CMD);
    ASSERT_TRUE(v==std::vector<char>({'a','b','c'}));
}
*/
//---
// Negative testing / 異常系

// options
TEST(argparse, NT_opt_undefined_opt){
    std::vector<const char*> args = {"./a.out", "--undefined-opt", "xxx"};
    const int argc = args.size();
    const char **argv = args.data();

    bool opt=true;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::opt(opt, false, "-o", "--option", 0)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_error);
    
    ASSERT_TRUE(sstd::strIn(R"(error: The input argument(s) of `["--undefined-opt" "xxx"]` is NOT defnied by sstd::arg_rule::opt() as an input option.)", ap.err()));
    ASSERT_TRUE(opt==false);
}
TEST(argparse, NT_opt_undefined_opt_short){
    std::vector<const char*> args = {"./a.out", "--d"};
    const int argc = args.size();
    const char **argv = args.data();

    bool opt_a=true;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::opt(opt_a, false, "-o", "--option", 0)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_error);
    
    ASSERT_TRUE(sstd::strIn(R"(error: The input argument(s) of `["--d"]` is NOT defnied by sstd::arg_rule::opt() as an input option.)", ap.err()));
    ASSERT_TRUE(opt_a==false);
}
TEST(argparse, NT_opt_invalid_arg){
    std::vector<const char*> args = {"./a.out", "--option", "xxx"};
    const int argc = args.size();
    const char **argv = args.data();

    bool opt=true;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::opt(opt, false, "-o", "--option", 1)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_error);
    
    ASSERT_TRUE(sstd::strIn(R"(error: The input arguments of `["--option" "xxx"]` is failed to convert to `bool` type.)", ap.err()));
    ASSERT_TRUE(opt==false);
}
TEST(argparse, NT_opt_less_arg){
    std::vector<const char*> args = {"./a.out", "--option"};
    const int argc = args.size();
    const char **argv = args.data();

    bool opt=true;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::opt(opt, false, "-o", "--option", 1)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_error);
    
    ASSERT_TRUE(sstd::strIn(R"(error: The number of input argument(s) is `0` (["--option"]). But `1` argument(s) are expected by the definition of sstd::arg_rule::opt().)", ap.err()));
    ASSERT_TRUE(opt==false);
}
TEST(argparse, NT_opt_more_arg){
    std::vector<const char*> args = {"./a.out", "--option", "A", "B"};
    const int argc = args.size();
    const char **argv = args.data();

    bool opt=true;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::opt(opt, false, "-o", "--option", 1)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_error);
    
    ASSERT_TRUE(sstd::strIn(R"(error: The number of input argument(s) is `2` (["--option" "A" "B"]). But `1` argument(s) are expected by the definition of sstd::arg_rule::opt().)", ap.err()));
    ASSERT_TRUE(opt==false);
}
TEST(argparse, NT_opt_invalid_arg_short_1){
    std::vector<const char*> args = {"./a.out", "-ab", "T", "T"};
    const int argc = args.size();
    const char **argv = args.data();

    bool opt_a=true;
    bool opt_b=true;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::opt(opt_a, false, "-a", "--option-a", 1)
                          , sstd::arg_rule::opt(opt_b, false, "-b", "--option-b", 1)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_error);
    
    ASSERT_TRUE(sstd::strIn(R"(error: The multiple short options defined by sstd::arg_rule::opt() can NOT take arguments inputted as `["-ab" "T" "T"]`. Please separate the short options inputted if you want to use them with arguments.)", ap.err()));
    ASSERT_TRUE(opt_a==false);
    ASSERT_TRUE(opt_b==false);
}
TEST(argparse, NT_opt_duplicated_1){
    std::vector<const char*> args = {"./a.out", "--option-a", "--option-a"};
    const int argc = args.size();
    const char **argv = args.data();

    bool opt_a=true;
    bool opt_b=true;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::opt(opt_a, false, "-a", "--option-a", 0)
                          , sstd::arg_rule::opt(opt_b, false, "-b", "--option-b", 0)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_error);
    
    ASSERT_TRUE(sstd::strIn(R"(error: There are duplicated input in the arg. The duplicated options are follows: `--option-a (-a)`.)", ap.err()));
    ASSERT_TRUE(opt_a==false);
    ASSERT_TRUE(opt_b==false);
}
TEST(argparse, NT_opt_duplicated_2){
    std::vector<const char*> args = {"./a.out", "--option-a", "--option-a", "--option-b", "--option-b"};
    const int argc = args.size();
    const char **argv = args.data();

    bool opt_a=true;
    bool opt_b=true;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::opt(opt_a, false, "-a", "--option-a", 0)
                          , sstd::arg_rule::opt(opt_b, false, "-b", "--option-b", 0)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_error);
    
    ASSERT_TRUE(sstd::strIn(R"(error: There are duplicated input in the arg. The duplicated options are follows: )", ap.err()));
    ASSERT_TRUE(sstd::strIn(R"(`--option-b (-b)`)", ap.err()));
    ASSERT_TRUE(sstd::strIn(R"(`--option-a (-a)`)", ap.err()));
    ASSERT_TRUE(opt_a==false);
    ASSERT_TRUE(opt_b==false);
}/*
TEST(argparse, NT_opt_duplicated_short){
    std::vector<const char*> args = {"./a.out", "-aa"};
}
*/

// commands
TEST(argparse, NT_cmd_invalid_arg){
    std::vector<const char*> args = {"./a.out", "get-lines", "a", "b", "c"};
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
                          , sstd::arg_rule::cmd((int)CmdID::GET_LINES, vlineNum, {9, 8, 7}, "get-lines", -1)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_error);
    ASSERT_TRUE(sstd::strIn(R"(error: The input arguments of `["get-lines" "a" "b" "c"]` is failed to convert to `vec_int32` type.)", ap.err()));
    
    ASSERT_TRUE(vlineNum==std::vector<int>({9,8,7}));
}
TEST(argparse, NT_cmd_less_arg){
    std::vector<const char*> args = {"./a.out", "get-lines", "1", "3"};
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
                          , sstd::arg_rule::cmd((int)CmdID::GET_LINES, vlineNum, {9, 8, 7}, "get-lines", 3)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_error);
    ASSERT_TRUE(sstd::strIn(R"(error: The number of input argument(s) is `2` (["get-lines" "1" "3"]). But `3` argument(s) are expected by the definition of sstd::arg_rule::opt().)", ap.err()));
    
    ASSERT_TRUE(vlineNum==std::vector<int>({9,8,7}));
}
TEST(argparse, NT_cmd_more_arg){
    std::vector<const char*> args = {"./a.out", "get-lines", "1", "3", "5", "7"};
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
                          , sstd::arg_rule::cmd((int)CmdID::GET_LINES, vlineNum, {9, 8, 7}, "get-lines", 3)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_error);
    ASSERT_TRUE(sstd::strIn(R"(error: The number of input argument(s) is `4` (["get-lines" "1" "3" "5" "7"]). But `3` argument(s) are expected by the definition of sstd::arg_rule::opt().)", ap.err()));
    
    ASSERT_TRUE(vlineNum==std::vector<int>({9,8,7}));
}/*
TEST(argparse, NT_cmd_duplicated){
    std::vector<const char*> args = {"./a.out", "get-lines", "1", "3", "5", "get-lines", "7", "9", "10"};
}
*/
//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
