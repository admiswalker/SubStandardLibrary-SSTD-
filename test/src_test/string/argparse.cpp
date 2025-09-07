#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define ARG_ID_NULL 0
#define ARG_ID_GET_LINES 1
#define ARG_ID_GET_LINE  2

TEST(argparse, example01){
    sstd::argparse ap;
    
    int res_dummy; std::vector<int> res_v; int res_i;
//    ap.add_required_arg(res_dummy, ARG_ID_NULL,  "",           0, int(0)              );
    ap.add_required_arg(res_v, ARG_ID_GET_LINES, "get lines", -1, std::vector<int>({}));
    ap.add_required_arg(res_i, ARG_ID_GET_LINE , "get line",   1, int(0)              );
    // Memo:     return value,           switch index, command, arg length, default value
    
    bool rm_hs=false, rm_ts=false;
    ap.add_optional_arg(rm_hs, "-h", "--rm-head-spaces", 1, false);
    ap.add_optional_arg(rm_ts, "-t", "--rm-tail-spaces", 1, false);
    
    int res = ap.parse(argc, argv);
    switch(res){
    case ARG_ID_GET_LINES: { /* process get lines */ } break;
    case ARG_ID_GET_LINE : { /* process get line */ } break;
    default : { printf("error: %s\n", ap.error.c_str()); }
    }
    
    return 0;
}

#undef ARG_ID_GET_LINES
#undef ARG_ID_GET_LINE

//---

TEST(argparse, example01_2){
    enum{
         ARG_ID_NULL,
         ARG_ID_GET_LINES,
         ARG_ID_GET_LINE
    };
    
    sstd::argparse ap;
    
    int res_dummy; std::vector<int> res_v; int res_i;
    ap.add_required_arg(res_dummy, ARG_ID_NULL     ,          "",  0, int(0)              );
    ap.add_required_arg(res_v,     ARG_ID_GET_LINES, "get lines", -1, std::vector<int>({}));
    ap.add_required_arg(res_i,     ARG_ID_GET_LINE , "get line" ,  1, int(0)              );
    // Memo:     return value,           switch index, command, arg length, default value
    
    bool rm_hs=false, rm_ts=false;
    ap.add_optional_arg(rm_hs, "-h", "--rm-head-spaces", 1, false);
    ap.add_optional_arg(rm_ts, "-t", "--rm-tail-spaces", 1, false);
    
    int res = ap.parse(argc, argv);
    switch(res){
    case ARG_ID_GET_LINES: { /* process get lines */ } break;
    case ARG_ID_GET_LINE : { /* process get line */ } break;
    default : { printf("error: %s\n", ap.error.c_str()); }
    }
    
    return 0;
}

//---

TEST(argparse, example01_2){
    sstd::argparse ap;
    
    int res_dummy; std::vector<int> res_v; int res_i;
    int SW_ID_NULL      = ap.add_required_arg(res_dummy, int(0)              ,          "",  0);
    int SW_ID_GET_LINES = ap.add_required_arg(res_v    , std::vector<int>({}), "get lines", -1);
    int SW_ID_GET_LINE  = ap.add_required_arg(res_i    , int(0)              , "get line" ,  1);
    // Memo:     return value,           switch index, command, arg length, default value
    
    bool res_rm_hs, res_rm_ts;
    ap.add_optional_arg(res_rm_hs, false, "-h", "--rm-head-spaces", 1);
    ap.add_optional_arg(res_rm_ts, false, "-t", "--rm-tail-spaces", 1);
    if(ap.error.size()!=0){
        print(ap.error.c_str());
    }
    
    int sw_id = ap.parse(argc, argv);
    switch(sw_id){
    case SW_ID_GET_NULL : { print_help(); } break;
    case SW_ID_GET_LINES: { /* process get lines */ } break;
    case SW_ID_GET_LINE : { /* process get line */ } break;
    default : { printf("error: %s\n", ap.error.c_str()); }
    }
    
    return 0;
}

//---

TEST(argparse, example02){
    sstd::argparse ap;
    ap.add_required_arg("get lines", -1);
    ap.add_required_arg("get line", 1);
    ap.add_optional_arg("-h", "--rm-head-spaces", 1);
    ap.add_optional_arg("-t", "--rm-tail-spaces", 1);
    
    std::vector<std::string> res_v;
    std::unordered_map<std::string, std::vector<std::string>> res_opt;
    bool res = ap.parse(res_v, res_opt, argc, argv);
    
    if(sstd::strcmp(res_v[0], "get")){
        if(sstd::strcmp(res_v[1], "lines")){
        }else if(sstd::strcmp(res_v[1], "line")){
        }else{
            print("error\n");
        }
    }else{
        print("error\n");
    }
}

//---

TEST(argparse, example03){
    std::vector<std::string> res_v;
    std::unordered_map<std::string, std::vector<std::string>> res_opt;
    bool res = sstd::argparse(res_v, res_opt, argc, argv);
    if(res){ printf("error\n"); return; }

    if(res_v.size()<=1){ printf("error\n"); return; }
    
    if(res_v[0]=="get")){
        if      (res_v[1]=="lines"){
            
        }else if(res_v[1], "line" ){
            
        }else{
            print("error\n");
        }
    }else{
        print("error\n");
    }
}

//---

TEST(argparse, example04){
}

//---

TEST(argparse, example05){
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
