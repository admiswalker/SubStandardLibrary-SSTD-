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
    int argc = 0;
    char *argv[] = {
                    "./a.out",
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
                          , sstd::arg_rule::cmd("in1")
                          , sstd::arg_rule::cmd("in2")
                          , sstd::arg_rule::cmd("in3")
                          , sstd::arg_rule::cmd((int)CmdID::EMPTY, "", 0)
//                    , sstd::argparse::cmd_rule(CmdID::GET_LINES, vlineNum, {}, "get lines", -1)
//                    , sstd::argparse::cmd_rule(CmdID::GET_LINE , num,       0, "get line" ,  1)
//                    , sstd::argparse::opt_rule(rm_hs, false, "-h", "--rm-head-spaces", 1)
//                    , sstd::argparse::opt_rule(rm_ts, false, "-t", "--rm-tail-spaces", 1)
                    );

    sstd::printn(ap._get_arg_stack());
    
    /*
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
    //*/
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
