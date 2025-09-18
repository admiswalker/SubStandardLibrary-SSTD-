#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
//*
TEST(argparse, example01){
    sstd::argparse ap;
    
    std::vector<int> res_v; int res_i;
    int SW_ID_NULL      = ap.add_required_arg("");
    int SW_ID_GET_LINES = ap.add_required_arg("get lines", -1, res_v, {});
    int SW_ID_GET_LINE  = ap.add_required_arg("get line" ,  1, res_i,  0);
    // Memo:                                      command, arg length, return value, default value
    
    bool res_rm_hs, res_rm_ts;
    ap.add_optional_arg("-h", "--rm-head-spaces", 1, res_rm_hs, false);
    ap.add_optional_arg("-t", "--rm-tail-spaces", 1, res_rm_ts, false);
    
    int sw_id = ap.parse(argc, argv);
    switch(sw_id){
    case SW_ID_GET_NULL : { print_help(); } break;
    case SW_ID_GET_LINES: { // process get lines
    } break;
    case SW_ID_GET_LINE : { // process get line
    } break;
    default : { printf("error: %s\n", ap.error.c_str()); }
    }
    
    return 0;
}
//*/

//---

//*
enum class CmdID {
                  NULL,
                  GET_LINES,
                  GET_LINE
};
enum class OptID {
                  rmHS,
                  rmTS
};

TEST(argparse, example03){
    sstd::argparse ap;
    
    ap.add_cmd_rule(CmdID::NULL,      "");
    ap.add_cmd_rule(CmdID::GET_LINES, "get lines", -1, {});
    ap.add_cmd_rule(CmdID::GET_LINE,  "get line" ,  1,  0);
    // Memo:        switch ID, command, arg length
    
    ap.add_optional_rule(OptID::rmHS, "-h", "--rm-head-spaces", 1); // bool|std::string|int
    ap.add_optional_rule(OptID::rmTS, "-t", "--rm-tail-spaces", 1);
    
    std::tuple<int,std::vector<std::string>,std::vector<std::string>>
    (sw_id, v_cmd_arg, v_opt) = ap.parse(argc, argv);
    switch(sw_id){
    case CmdID::GET_NULL : { print_help(); } break;
    case CmdID::GET_LINES: { // process get lines
        std::vector<int> vlineNum; if(!sstd::s2i(vlineNum, v_arg){ printf("error\n"); return -1; }
        bool opt_h; if(!sstd::s2b(opt_h, v_opt[OptID::rmHS])){ printf("error\n"); return -1; }
        
        
        
    } break;
    case CmdID::GET_LINE : { // process get line
        int res_i;
    } break;
    default : { printf("error: %s\n", ap.error.c_str()); }
    }
    
    return 0;
}
//*/

//---

//*
enum class CmdID {
                  NULL,
                  GET_LINES,
                  GET_LINE
};
enum class OptID {
                  RM_HEAD_SPACE,
                  RM_TAIL_SPACE
};

TEST(argparse, example03){
    sstd::argparse ap;
    
    ap.add_cmd_rule(CmdID::NULL,      "");
    ap.add_cmd_rule(CmdID::GET_LINES, "get lines", -1, {});
    ap.add_cmd_rule(CmdID::GET_LINE,  "get line" ,  1,  0);
    // Memo:        switch ID, command, arg length
    
    ap.add_optional_rule(OptID::RM_HEAD_SPACE, "-h", "--rm-head-spaces", 1); // bool|std::string|int
    ap.add_optional_rule(OptID::RM_TAIL_SPACE, "-t", "--rm-tail-spaces", 1);
    
    int cmd_id = ap.parse(argc, argv);
    std::vector<int> vlineNum = ap.get_cmd(CmdID::GET_LINES); // 中間クラスを作成して，キャスト演算子で対応
    int              num      = ap.get_cmd(CmdID::GET_LINE );
    bool opt_rm_hs = ap.get_opt(OptID::RM_HEAD_SPACE);
    bool opt_rm_ts = ap.get_opt(OptID::RM_TAIL_SPACE);
    
    switch(cmd_id){
    case CmdID::GET_NULL : { print_help(); } break;
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

//*
enum class CmdID {
                  NULL,
                  GET_LINES,
                  GET_LINE
};

TEST(argparse, example04){
    sstd::argparse ap(argc, argv);

    // Optional rules must be parsed first
    bool opt_rm_hs = ap.add_optional_rule("-h", "--rm-head-spaces", 1); // bool|std::string|int
    bool opt_rm_ts = ap.add_optional_rule("-t", "--rm-tail-spaces", 1);
    
    std::string      filePath = ap.add_cmd_rule(CmdID::NULL,      "",           1, "");
    std::vector<int> vlineNum = ap.add_cmd_rule(CmdID::GET_LINES, "get lines", -1, {}); // 戻り値は，中間クラスを作成して，キャスト演算子で対応
    int              num      = ap.add_cmd_rule(CmdID::GET_LINE,  "get line" ,  1,  0);
    // Memo:                                             cmd ID, command, arg length, default value

    // これができたらいいんだけど，cmd が複雑だと，長い cmd から処理しないと，cmd が複数の意味を取る場合にバグるので，よくない．
    
    int cmd_id = ap.parse(argc, argv);
    switch(cmd_id){
    case CmdID::NULL : { print_help(); } break;
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


//*
enum class CmdID {
                  EMPTY,
                  GET_LINES,
                  GET_LINE
};

TEST(argparse, example05){

    bool rm_hs, rm_ts;
    std::vector<int> vlineNum;
    int num;
    
    int cmd_id = sstd::argparse(argc, argv,
                                sstd::argparse::cmd_rule(CmdID::EMPTY),
                                sstd::argparse::cmd_rule(CmdID::GET_LINES, "get lines", -1, vlineNum, {}),
                                sstd::argparse::cmd_rule(CmdID::GET_LINE,  "get line" ,  1, num,       0),
                                sstd::argparse::opt_rule("-h", "--rm-head-spaces", 1, rm_hs, false),
                                sstd::argparse::opt_rule("-t", "--rm-tail-spaces", 1, rm_ts, false)
                                );
    
    switch(cmd_id){
    case CmdID::EMPTY : { print_help(); } break;
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

TEST(argparse, hello){
    printf("hello\n");
    
    sstd::argparse ap;

    std::vector<int> res_v; int res_i; // Mandatory arguments for each comamnd switched
    std::vector<int> init_val;
//    int SW_ID_NULL = ap.add_switch_rule("get lines", -1, res_v, init_val); // regiesters the switching command
    int SW_ID_NULL = ap.add_switch_rule("get lines", (int)-1, res_v); // regiesters the switching command

    ;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
