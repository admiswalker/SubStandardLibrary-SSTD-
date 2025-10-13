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
                    "get",
                    "lines",
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
                          , sstd::arg_rule::cmd((int)CmdID::GET_LINES, vlineNum, {}, "get lines", -1)
                          , sstd::arg_rule::cmd((int)CmdID::GET_LINE , num,       0, "get line" ,  1)
                          , sstd::arg_rule::opt(rm_hs, false, "-h", "--rm-head-spaces", 0)
//                    , sstd::arg_rule::opt(rm_ts, false, "-t", "--rm-tail-spaces", 1)
                    );

    sstd::printn(ap._get_arg_stack());
    printf("\n");
    printf("\n");
    sstd::printn(ap._get_arg_hash_cmd());
    printf("\n");
    printf("\n");
    sstd::printn(ap._get_arg_hash_opt());
    printf("\n");
    printf("\n");
    sstd::printn(cmd_id);
    
    switch(cmd_id){
    case (int)CmdID::EMPTY : {
//        ap.print_help();
    } break;
    case (int)CmdID::GET_LINES: {
        sstd::printn(vlineNum);
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

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
