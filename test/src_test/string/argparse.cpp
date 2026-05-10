#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Complicated tests
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

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Normal testing for parsing / パーシング正常系

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

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Negative testing for parsing / パーシング異常系

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

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::opt(opt_a, false, "-a", "--option-a", 0)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_error);
    
    ASSERT_TRUE(sstd::strIn(R"(error: There are duplicated input in the arg. The duplicated options are follows: `--option-a (-a)`.)", ap.err()));
    ASSERT_TRUE(opt_a==false);
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
}
TEST(argparse, NT_opt_duplicated_short_1a){
    std::vector<const char*> args = {"./a.out", "-a", "-a"};
    const int argc = args.size();
    const char **argv = args.data();

    bool opt_a=true;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::opt(opt_a, false, "-a", "--option-a", 0)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_error);
    
    ASSERT_TRUE(sstd::strIn(R"(error: There are duplicated input in the arg. The duplicated options are follows: `--option-a (-a)`.)", ap.err()));
    ASSERT_TRUE(opt_a==false);
}
TEST(argparse, NT_opt_duplicated_short_1b){
    std::vector<const char*> args = {"./a.out", "-aa"};
    const int argc = args.size();
    const char **argv = args.data();

    bool opt_a=true;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::opt(opt_a, false, "-a", "--option-a", 0)
                          );
    ASSERT_EQ(cmd_id, sstd::arg_rule::num_error);
    
    ASSERT_TRUE(sstd::strIn(R"(error: There are duplicated input in the arg. The duplicated options are follows: `--option-a (-a)`.)", ap.err()));
    ASSERT_TRUE(opt_a==false);
}
TEST(argparse, NT_opt_duplicated_short_2a){
    std::vector<const char*> args = {"./a.out", "-a", "-a", "-b", "-b"};
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
}
TEST(argparse, NT_opt_duplicated_short_2b){
    std::vector<const char*> args = {"./a.out", "-aabb"};
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
}


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
}
TEST(argparse, NT_cmd_duplicated){
    std::vector<const char*> args = {"./a.out", "get-lines", "1", "3", "5", "get-lines", "7", "9", "10"};
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
    ASSERT_TRUE(sstd::strIn(R"(error: The number of input argument(s) is `7` (["get-lines" "1" "3" "5" "get-lines" "7" "9" "10"]). But `3` argument(s) are expected by the definition of sstd::arg_rule::opt().)", ap.err()));
    
    ASSERT_TRUE(vlineNum==std::vector<int>({9,8,7}));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Normal testing for value conversion / 正常系 (値変換)

//---
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

//---
// char
TEST(argparse, cmd_char){
    std::vector<const char*> args = {"./a.out", "cmd", "a"};
    const int argc = args.size();
    const char **argv = args.data();

    enum class CmdID{SAMPLE_CMD};
    
    char res;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::cmd((int)CmdID::SAMPLE_CMD, res, 'x', "cmd", -1)
                          );
    ASSERT_EQ(cmd_id, (int)CmdID::SAMPLE_CMD);
    ASSERT_TRUE(res=='a');
//    ASSERT_TRUE(false);
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
    ASSERT_EQ(cmd_id, (int)CmdID::SAMPLE_CMD);
    ASSERT_TRUE(v==std::vector<char>({'a','b','c'}));
}

//---
// uchar

// Skipp (same with uint8)

//---
// int8, int16, int32, int64, uint8, uint16, uint32, uint64, float, double

#define TEST_NUMERIC_TYPES_ARG0_DEFAULT(TYPE, DEFAULT)                  \
    std::vector<const char*> args = {"./a.out", "cmd"};                 \
    const int argc = args.size();                                       \
    const char **argv = args.data();                                    \
                                                                        \
    enum class CmdID{SAMPLE_CMD};                                       \
                                                                        \
    TYPE res;                                                           \
                                                                        \
    sstd::argparse ap;                                                  \
    int cmd_id = ap.parse(argc, argv                                    \
                          , sstd::arg_rule::cmd((int)CmdID::SAMPLE_CMD, res, DEFAULT, "cmd", 0) \
                          );                                            \
    ASSERT_EQ(cmd_id, (int)CmdID::SAMPLE_CMD);                          \
    ASSERT_EQ(res, (TYPE)DEFAULT);
#define TEST_NUMERIC_TYPES(TYPE, CNT, DEFAULT, ARG_STR, ANS)            \
    std::vector<const char*> args = {"./a.out", "cmd", ARG_STR};        \
    const int argc = args.size();                                       \
    const char **argv = args.data();                                    \
                                                                        \
    enum class CmdID{SAMPLE_CMD};                                       \
                                                                        \
    TYPE res;                                                           \
                                                                        \
    sstd::argparse ap;                                                  \
    int cmd_id = ap.parse(argc, argv                                    \
                          , sstd::arg_rule::cmd((int)CmdID::SAMPLE_CMD, res, DEFAULT, "cmd", CNT) \
                          );                                            \
    ASSERT_EQ(cmd_id, (int)CmdID::SAMPLE_CMD);                          \
    ASSERT_EQ(res, (TYPE)ANS);

TEST(argparse, cmd_i8_arg0_default ){ TEST_NUMERIC_TYPES_ARG0_DEFAULT(int8, ( int8 )127); }
TEST(argparse, cmd_i8_1 ){ TEST_NUMERIC_TYPES( int8,  1, ( int8 )-128, "0", 0); }
TEST(argparse, cmd_i8_2 ){ TEST_NUMERIC_TYPES( int8,  1, ( int8 ) 127, "0", 0); }
TEST(argparse, cmd_i8_3 ){ TEST_NUMERIC_TYPES( int8,  1, ( int8 )0, "-128", -128); }
TEST(argparse, cmd_i8_4 ){ TEST_NUMERIC_TYPES( int8,  1, ( int8 )0, "127", 127); }

TEST(argparse, cmd_i16_arg0_default ){ TEST_NUMERIC_TYPES_ARG0_DEFAULT(int16, ( int16)32767); }
TEST(argparse, cmd_i16_1){ TEST_NUMERIC_TYPES( int16, 1, ( int16)-32768, "0", 0); }
TEST(argparse, cmd_i16_2){ TEST_NUMERIC_TYPES( int16, 1, ( int16) 32767, "0", 0); }
TEST(argparse, cmd_i16_3){ TEST_NUMERIC_TYPES( int16, 1, ( int16)0, "-32768", -32768); }
TEST(argparse, cmd_i16_4){ TEST_NUMERIC_TYPES( int16, 1, ( int16)0, "32767", 32767); }

TEST(argparse, cmd_i32_arg0_default ){ TEST_NUMERIC_TYPES_ARG0_DEFAULT(int32, ( int32)2147483647); }
TEST(argparse, cmd_i32_1){ TEST_NUMERIC_TYPES( int32, 1, ( int32)-2147483648, "0", 0); }
TEST(argparse, cmd_i32_2){ TEST_NUMERIC_TYPES( int32, 1, ( int32) 2147483647, "0", 0); }
TEST(argparse, cmd_i32_3){ TEST_NUMERIC_TYPES( int32, 1, ( int32)0, "-2147483648", -2147483648); }
TEST(argparse, cmd_i32_4){ TEST_NUMERIC_TYPES( int32, 1, ( int32)0, "2147483647", 2147483647); }

TEST(argparse, cmd_i64_arg0_default ){ TEST_NUMERIC_TYPES_ARG0_DEFAULT(int64, ( int64)9223372036854775807ll); }
//TEST(argparse, cmd_i64_1){ TEST_NUMERIC_TYPES( int64, 1, ( int64)-9223372036854775808ll, "0", 0); } // Commenting out this line in order to suppress the bagged warning of GCC.
TEST(argparse, cmd_i64_2){ TEST_NUMERIC_TYPES( int64, 1, ( int64) 9223372036854775807ll, "0", 0); }
//TEST(argparse, cmd_i64_3){ TEST_NUMERIC_TYPES( int64, 1, ( int64)0, "-9223372036854775808", -9223372036854775808ll); } // Commenting out this line in order to suppress the bagged warning of GCC.
TEST(argparse, cmd_i64_4){ TEST_NUMERIC_TYPES( int64, 1, ( int64)0, "9223372036854775807", 9223372036854775807ll); }

TEST(argparse, cmd_u8_arg0_default ){ TEST_NUMERIC_TYPES_ARG0_DEFAULT(uint8, (uint8 )255); }
TEST(argparse, cmd_u8_1 ){ TEST_NUMERIC_TYPES(uint8,  1, (uint8 )255, "0", 0); }
TEST(argparse, cmd_u8_2 ){ TEST_NUMERIC_TYPES(uint8,  1, (uint8 )0, "255", 255); }

TEST(argparse, cmd_u16_arg0_default ){ TEST_NUMERIC_TYPES_ARG0_DEFAULT(uint16, (uint16)65535); }
TEST(argparse, cmd_u16_1){ TEST_NUMERIC_TYPES(uint16, 1, (uint16)65535, "0", 0); }
TEST(argparse, cmd_u16_2){ TEST_NUMERIC_TYPES(uint16, 1, (uint16)0, "65535", 65535); }

TEST(argparse, cmd_u32_arg0_default ){ TEST_NUMERIC_TYPES_ARG0_DEFAULT(uint32, (uint32)4294967295); }
TEST(argparse, cmd_u32_1){ TEST_NUMERIC_TYPES(uint32, 1, (uint32)4294967295, "0", 0); }
TEST(argparse, cmd_u32_2){ TEST_NUMERIC_TYPES(uint32, 1, (uint32)0, "4294967295", 4294967295); }

TEST(argparse, cmd_u64_arg0_default ){ TEST_NUMERIC_TYPES_ARG0_DEFAULT(uint64, (uint64)18446744073709551615ull); }
TEST(argparse, cmd_u64_1){ TEST_NUMERIC_TYPES(uint64, 1, (uint64)18446744073709551615ull, "0", 0); }
TEST(argparse, cmd_u64_2){ TEST_NUMERIC_TYPES(uint64, 1, (uint64)0, "18446744073709551615", 18446744073709551615ull); }

TEST(argparse, cmd_float_arg0_default ){ TEST_NUMERIC_TYPES_ARG0_DEFAULT(float, (float)1.234); }
TEST(argparse, cmd_float_1){ TEST_NUMERIC_TYPES(float, 1, (float)-1.234, "0.0", 0.0); }
TEST(argparse, cmd_float_2){ TEST_NUMERIC_TYPES(float, 1, (float) 1.234, "0.0", 0.0); }
TEST(argparse, cmd_float_3){ TEST_NUMERIC_TYPES(float, 1, (float) 0.0, "-1.234", -1.234); }
TEST(argparse, cmd_float_4){ TEST_NUMERIC_TYPES(float, 1, (float) 0.0, "1.234", 1.234); }

TEST(argparse, cmd_double_arg0_default ){ TEST_NUMERIC_TYPES_ARG0_DEFAULT(double, (double)1.234); }
TEST(argparse, cmd_double_1){ TEST_NUMERIC_TYPES(double, 1, (double)-1.234, "0.0", 0.0); }
TEST(argparse, cmd_double_2){ TEST_NUMERIC_TYPES(double, 1, (double) 1.234, "0.0", 0.0); }
TEST(argparse, cmd_double_3){ TEST_NUMERIC_TYPES(double, 1, (double) 0.0, "-1.234", -1.234); }
TEST(argparse, cmd_double_4){ TEST_NUMERIC_TYPES(double, 1, (double) 0.0, "1.234", 1.234); }

#undef TEST_NUMERIC_TYPES
#undef TEST_NUMERIC_TYPES_ARG0_DEFAULT

//---
// uint8
/*
TEST(argparse, cmd_uint8){
    std::vector<const char*> args = {"./a.out", "cmd", "255"};
    const int argc = args.size();
    const char **argv = args.data();

    enum class CmdID{SAMPLE_CMD};
    
    uint8 res;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::cmd((int)CmdID::SAMPLE_CMD, res, (uint8)0, "cmd", 1)
                          );
    ASSERT_EQ(cmd_id, (int)CmdID::SAMPLE_CMD);
    ASSERT_TRUE(res==(uint8)255);
}
*/

//---
// std::vector<T>. `T` is bool, char, int8, int16, int32, int64, uint8, uint16, uint32, uint64, float, double or std::string.
/*
#define TEST_VEC_NUMERIC_TYPES(TYPE, CNT, DEFAULT, ARG_STR, ANS)        \
    std::vector<const char*> args = {"./a.out", "cmd", ARG_STR};        \
    const int argc = args.size();                                       \
    const char **argv = args.data();                                    \
                                                                        \
    enum class CmdID{SAMPLE_CMD};                                       \
                                                                        \
    TYPE res;                                                           \
                                                                        \
    sstd::argparse ap;                                                  \
    int cmd_id = ap.parse(argc, argv                                    \
                          , sstd::arg_rule::cmd((int)CmdID::SAMPLE_CMD, res, DEFAULT, "cmd", CNT) \
                          );                                            \
    ASSERT_EQ(cmd_id, (int)CmdID::SAMPLE_CMD);                          \
    ASSERT_EQ(res, (TYPE)ANS);

#define TEST_VEC_NUMERIC_TYPES(TYPE, CNT, ...)                          \
    std::vector<const char*> args = {"./a.out", "cmd", __VA_ARGS__};
    const int argc = args.size();
    const char **argv = args.data();

    enum class CmdID{SAMPLE_CMD};
    
    std::vector<TYPE> res_v_u8;

    sstd::argparse ap;
    int cmd_id = ap.parse(argc, argv
                          , sstd::arg_rule::cmd((int)CmdID::SAMPLE_CMD, res_v_u8, std::vector<TYPE>({}), "cmd", -1)
                          );
// sstd::printn_all(ap.err());
    ASSERT_EQ(cmd_id, (int)CmdID::SAMPLE_CMD);
#define TEST_VEC_NUMERIC_TYPES_ANS(...)        \
    ASSERT_TRUE(res_v_u8==std::vector<uint8>({__VA_ARGS__}));

TEST(argparse, cmd_i8_1 ){ TEST_NUMERIC_TYPES( int8,  1, ( int8 )-128, "0", 0); }

#undef TEST_VEC_NUMERIC_TYPES_ANS
#undef TEST_VEC_NUMERIC_TYPES
//*/

// vec_uint8, vec_uint16, vec_uint32, vec_uint64
#define TEST_VEC_NUMERIC_TYPES(TYPE, ARGS, DEFAULT, ANS)                \
    std::vector<const char*> args = ARGS;                               \
    const int argc = args.size();                                       \
    const char **argv = args.data();                                    \
                                                                        \
    enum class CmdID{CMD_ID_NAME};                                      \
                                                                        \
    std::vector<TYPE> res_vec;                                          \
                                                                        \
    sstd::argparse ap;                                                  \
    int cmd_id = ap.parse(argc, argv                                    \
                          , sstd::arg_rule::cmd((int)CmdID::CMD_ID_NAME, res_vec, DEFAULT, "cmd", -1) \
                          );                                            \
    if(ap.err().size()!=0){ sstd::printn_all(ap.err()); }               \
    ASSERT_EQ(cmd_id, (int)CmdID::CMD_ID_NAME);                         \
    ASSERT_TRUE(res_vec==ANS);
TEST(argparse, cmd_v_bool_arg0_default_value){ std::vector<const char*> ARGS={"./a.out","cmd"}; std::vector<bool> DEFAULT={true,false,true}; std::vector<bool> ANS={true,false,true}; TEST_VEC_NUMERIC_TYPES(bool, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_bool_arg0){ std::vector<const char*> ARGS={"./a.out","cmd"            }; std::vector<bool> DEFAULT={}; std::vector<bool> ANS={               }; TEST_VEC_NUMERIC_TYPES(bool, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_bool_arg1){ std::vector<const char*> ARGS={"./a.out","cmd","T"        }; std::vector<bool> DEFAULT={}; std::vector<bool> ANS={true           }; TEST_VEC_NUMERIC_TYPES(bool, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_bool_arg2){ std::vector<const char*> ARGS={"./a.out","cmd","T","F"    }; std::vector<bool> DEFAULT={}; std::vector<bool> ANS={true,false     }; TEST_VEC_NUMERIC_TYPES(bool, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_bool_arg3){ std::vector<const char*> ARGS={"./a.out","cmd","T","F","T"}; std::vector<bool> DEFAULT={}; std::vector<bool> ANS={true,false,true}; TEST_VEC_NUMERIC_TYPES(bool, ARGS, DEFAULT, ANS); }

TEST(argparse, cmd_v_i8_arg0_default_value){ std::vector<const char*> ARGS={"./a.out","cmd"}; std::vector<int8> DEFAULT={-9,8,7}; std::vector<int8> ANS={-9,8,7}; TEST_VEC_NUMERIC_TYPES(int8, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_i8_arg0){ std::vector<const char*> ARGS={"./a.out","cmd"             }; std::vector<int8> DEFAULT={}; std::vector<int8> ANS={      }; TEST_VEC_NUMERIC_TYPES(int8, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_i8_arg1){ std::vector<const char*> ARGS={"./a.out","cmd","-1"        }; std::vector<int8> DEFAULT={}; std::vector<int8> ANS={-1    }; TEST_VEC_NUMERIC_TYPES(int8, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_i8_arg2){ std::vector<const char*> ARGS={"./a.out","cmd","-1","2"    }; std::vector<int8> DEFAULT={}; std::vector<int8> ANS={-1,2  }; TEST_VEC_NUMERIC_TYPES(int8, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_i8_arg3){ std::vector<const char*> ARGS={"./a.out","cmd","-1","2","3"}; std::vector<int8> DEFAULT={}; std::vector<int8> ANS={-1,2,3}; TEST_VEC_NUMERIC_TYPES(int8, ARGS, DEFAULT, ANS); }

TEST(argparse, cmd_v_i16_arg0_default_value){ std::vector<const char*> ARGS={"./a.out","cmd"}; std::vector<int16> DEFAULT={-9,8,7}; std::vector<int16> ANS={-9,8,7}; TEST_VEC_NUMERIC_TYPES(int16, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_i16_arg0){ std::vector<const char*> ARGS={"./a.out","cmd"             }; std::vector<int16> DEFAULT={}; std::vector<int16> ANS={      }; TEST_VEC_NUMERIC_TYPES(int16, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_i16_arg1){ std::vector<const char*> ARGS={"./a.out","cmd","-1"        }; std::vector<int16> DEFAULT={}; std::vector<int16> ANS={-1    }; TEST_VEC_NUMERIC_TYPES(int16, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_i16_arg2){ std::vector<const char*> ARGS={"./a.out","cmd","-1","2"    }; std::vector<int16> DEFAULT={}; std::vector<int16> ANS={-1,2  }; TEST_VEC_NUMERIC_TYPES(int16, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_i16_arg3){ std::vector<const char*> ARGS={"./a.out","cmd","-1","2","3"}; std::vector<int16> DEFAULT={}; std::vector<int16> ANS={-1,2,3}; TEST_VEC_NUMERIC_TYPES(int16, ARGS, DEFAULT, ANS); }

TEST(argparse, cmd_v_i32_arg0_default_value){ std::vector<const char*> ARGS={"./a.out","cmd"}; std::vector<int32> DEFAULT={-9,8,7}; std::vector<int32> ANS={-9,8,7}; TEST_VEC_NUMERIC_TYPES(int32, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_i32_arg0){ std::vector<const char*> ARGS={"./a.out","cmd"             }; std::vector<int32> DEFAULT={}; std::vector<int32> ANS={      }; TEST_VEC_NUMERIC_TYPES(int32, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_i32_arg1){ std::vector<const char*> ARGS={"./a.out","cmd","-1"        }; std::vector<int32> DEFAULT={}; std::vector<int32> ANS={-1    }; TEST_VEC_NUMERIC_TYPES(int32, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_i32_arg2){ std::vector<const char*> ARGS={"./a.out","cmd","-1","2"    }; std::vector<int32> DEFAULT={}; std::vector<int32> ANS={-1,2  }; TEST_VEC_NUMERIC_TYPES(int32, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_i32_arg3){ std::vector<const char*> ARGS={"./a.out","cmd","-1","2","3"}; std::vector<int32> DEFAULT={}; std::vector<int32> ANS={-1,2,3}; TEST_VEC_NUMERIC_TYPES(int32, ARGS, DEFAULT, ANS); }

TEST(argparse, cmd_v_i64_arg0_default_value){ std::vector<const char*> ARGS={"./a.out","cmd"}; std::vector<int64> DEFAULT={-9,8,7}; std::vector<int64> ANS={-9,8,7}; TEST_VEC_NUMERIC_TYPES(int64, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_i64_arg0){ std::vector<const char*> ARGS={"./a.out","cmd"             }; std::vector<int64> DEFAULT={}; std::vector<int64> ANS={      }; TEST_VEC_NUMERIC_TYPES(int64, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_i64_arg1){ std::vector<const char*> ARGS={"./a.out","cmd","-1"        }; std::vector<int64> DEFAULT={}; std::vector<int64> ANS={-1    }; TEST_VEC_NUMERIC_TYPES(int64, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_i64_arg2){ std::vector<const char*> ARGS={"./a.out","cmd","-1","2"    }; std::vector<int64> DEFAULT={}; std::vector<int64> ANS={-1,2  }; TEST_VEC_NUMERIC_TYPES(int64, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_i64_arg3){ std::vector<const char*> ARGS={"./a.out","cmd","-1","2","3"}; std::vector<int64> DEFAULT={}; std::vector<int64> ANS={-1,2,3}; TEST_VEC_NUMERIC_TYPES(int64, ARGS, DEFAULT, ANS); }

TEST(argparse, cmd_v_u8_arg0_default_value){ std::vector<const char*> ARGS={"./a.out","cmd"}; std::vector<uint8> DEFAULT={9,8,7}; std::vector<uint8> ANS={9,8,7}; TEST_VEC_NUMERIC_TYPES(uint8, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_u8_arg0){ std::vector<const char*> ARGS={"./a.out","cmd"            }; std::vector<uint8> DEFAULT={}; std::vector<uint8> ANS={     }; TEST_VEC_NUMERIC_TYPES(uint8, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_u8_arg1){ std::vector<const char*> ARGS={"./a.out","cmd","1"        }; std::vector<uint8> DEFAULT={}; std::vector<uint8> ANS={1    }; TEST_VEC_NUMERIC_TYPES(uint8, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_u8_arg2){ std::vector<const char*> ARGS={"./a.out","cmd","1","2"    }; std::vector<uint8> DEFAULT={}; std::vector<uint8> ANS={1,2  }; TEST_VEC_NUMERIC_TYPES(uint8, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_u8_arg3){ std::vector<const char*> ARGS={"./a.out","cmd","1","2","3"}; std::vector<uint8> DEFAULT={}; std::vector<uint8> ANS={1,2,3}; TEST_VEC_NUMERIC_TYPES(uint8, ARGS, DEFAULT, ANS); }

TEST(argparse, cmd_v_u16_arg0_default_value){ std::vector<const char*> ARGS={"./a.out","cmd"}; std::vector<uint16> DEFAULT={9,8,7}; std::vector<uint16> ANS={9,8,7}; TEST_VEC_NUMERIC_TYPES(uint16, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_u16_arg0){ std::vector<const char*> ARGS={"./a.out","cmd"            }; std::vector<uint16> DEFAULT={}; std::vector<uint16> ANS={     }; TEST_VEC_NUMERIC_TYPES(uint16, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_u16_arg1){ std::vector<const char*> ARGS={"./a.out","cmd","1"        }; std::vector<uint16> DEFAULT={}; std::vector<uint16> ANS={1    }; TEST_VEC_NUMERIC_TYPES(uint16, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_u16_arg2){ std::vector<const char*> ARGS={"./a.out","cmd","1","2"    }; std::vector<uint16> DEFAULT={}; std::vector<uint16> ANS={1,2  }; TEST_VEC_NUMERIC_TYPES(uint16, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_u16_arg3){ std::vector<const char*> ARGS={"./a.out","cmd","1","2","3"}; std::vector<uint16> DEFAULT={}; std::vector<uint16> ANS={1,2,3}; TEST_VEC_NUMERIC_TYPES(uint16, ARGS, DEFAULT, ANS); }

TEST(argparse, cmd_v_u32_arg0_default_value){ std::vector<const char*> ARGS={"./a.out","cmd"}; std::vector<uint32> DEFAULT={9,8,7}; std::vector<uint32> ANS={9,8,7}; TEST_VEC_NUMERIC_TYPES(uint32, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_u32_arg0){ std::vector<const char*> ARGS={"./a.out","cmd"            }; std::vector<uint32> DEFAULT={}; std::vector<uint32> ANS={     }; TEST_VEC_NUMERIC_TYPES(uint32, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_u32_arg1){ std::vector<const char*> ARGS={"./a.out","cmd","1"        }; std::vector<uint32> DEFAULT={}; std::vector<uint32> ANS={1    }; TEST_VEC_NUMERIC_TYPES(uint32, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_u32_arg2){ std::vector<const char*> ARGS={"./a.out","cmd","1","2"    }; std::vector<uint32> DEFAULT={}; std::vector<uint32> ANS={1,2  }; TEST_VEC_NUMERIC_TYPES(uint32, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_u32_arg3){ std::vector<const char*> ARGS={"./a.out","cmd","1","2","3"}; std::vector<uint32> DEFAULT={}; std::vector<uint32> ANS={1,2,3}; TEST_VEC_NUMERIC_TYPES(uint32, ARGS, DEFAULT, ANS); }

TEST(argparse, cmd_v_u64_arg0_default_value){ std::vector<const char*> ARGS={"./a.out","cmd"}; std::vector<uint64> DEFAULT={9,8,7}; std::vector<uint64> ANS={9,8,7}; TEST_VEC_NUMERIC_TYPES(uint64, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_u64_arg0){ std::vector<const char*> ARGS={"./a.out","cmd"            }; std::vector<uint64> DEFAULT={}; std::vector<uint64> ANS={     }; TEST_VEC_NUMERIC_TYPES(uint64, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_u64_arg1){ std::vector<const char*> ARGS={"./a.out","cmd","1"        }; std::vector<uint64> DEFAULT={}; std::vector<uint64> ANS={1    }; TEST_VEC_NUMERIC_TYPES(uint64, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_u64_arg2){ std::vector<const char*> ARGS={"./a.out","cmd","1","2"    }; std::vector<uint64> DEFAULT={}; std::vector<uint64> ANS={1,2  }; TEST_VEC_NUMERIC_TYPES(uint64, ARGS, DEFAULT, ANS); }
TEST(argparse, cmd_v_u64_arg3){ std::vector<const char*> ARGS={"./a.out","cmd","1","2","3"}; std::vector<uint64> DEFAULT={}; std::vector<uint64> ANS={1,2,3}; TEST_VEC_NUMERIC_TYPES(uint64, ARGS, DEFAULT, ANS); }
#undef TEST_VEC_NUMERIC_TYPES

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
