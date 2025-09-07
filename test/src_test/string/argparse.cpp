#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(argparse, example01){
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
    
    std::vector<int> res_v; int res_i;
    int SW_ID_NULL      = ap.add_required_arg("");
    int SW_ID_GET_LINES = ap.add_required_arg("get lines", -1, res_v, std::vector<int>({}));
    int SW_ID_GET_LINE  = ap.add_required_arg("get line" ,  1, res_i, int(0)              );
    // Memo:     return value,           switch index, command, arg length, default value
    
    bool res_rm_hs, res_rm_ts;
    ap.add_optional_arg("-h", "--rm-head-spaces", 1, res_rm_hs, false);
    ap.add_optional_arg("-t", "--rm-tail-spaces", 1, res_rm_ts, false);
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

TEST(argparse, example03){
    sstd::argparse ap;
    
    int SW_ID_NULL      = ap.add_required_arg("");
    int SW_ID_GET_LINES = ap.add_required_arg("get lines", -1, std::vector<int>({}));
    int SW_ID_GET_LINE  = ap.add_required_arg("get line" ,  1, int(0)              );
    // Memo:     return value,           switch index, command, arg length, default value
    
    int OPT_ID_H = ap.add_optional_arg("-h", "--rm-head-spaces", 1, false);
    int OPT_ID_T = ap.add_optional_arg("-t", "--rm-tail-spaces", 1, false);
    if(ap.error.size()!=0){
        print(ap.error.c_str());
    }
    
    int sw_id = ap.parse(argc, argv);
    switch(sw_id){
    case SW_ID_GET_NULL : { print_help(); } break;
    case SW_ID_GET_LINES: {
        /* process get lines */
        
        std::vector<int>& res_v = ap[SW_ID_GET_LINES];
        bool& res_rm_hs = ap[OPT_ID_H];
        bool& res_rm_ts = ap[OPT_ID_T];
        
        
    } break;
    case SW_ID_GET_LINE : {
        /* process get line */
        
        int& res_i = ap[SW_ID_GET_LINE];
        
    } break;
    default : { printf("error: %s\n", ap.error.c_str()); }
    }
    
    return 0;
}

//---

TEST(argparse, example03){
    sstd::argparse ap;
    
    int SW_ID_NULL      = ap.add_required_arg("");
    int SW_ID_GET_LINES = ap.add_required_arg("get lines", -1);
    int SW_ID_GET_LINE  = ap.add_required_arg("get line" ,  1);
    // Memo:     return value,           switch index, command, arg length, default value
    
    bool res_rm_hs, res_rm_ts;
    ap.add_optional_arg("-h", "--rm-head-spaces", 1, res_rm_hs, false);
    ap.add_optional_arg("-t", "--rm-tail-spaces", 1, res_rm_ts, false);
//    int OPT_ID_H = ap.add_optional_arg("-h", "--rm-head-spaces", 1, false);
//    int OPT_ID_T = ap.add_optional_arg("-t", "--rm-tail-spaces", 1, false);
    if(ap.error.size()!=0){
        print(ap.error.c_str());
    }
    
    std::vector<std::string> res_vs;
    int sw_id = ap.parse(res_vs, argc, argv);
    
    switch(sw_id){
    case SW_ID_GET_NULL : { print_help(); } break;
    case SW_ID_GET_LINES: {
        /* process get lines */
        
        std::vector<int> arg_vi;
        if(!sstd::s2i(res_vs)){ printf("error\n"); }
        
        
    } break;
    case SW_ID_GET_LINE : {
        /* process get line */
        
        int arg_i = sstd::s2i(res_vs[0]);
        
    } break;
    default : { printf("error: %s\n", ap.error.c_str()); }
    }
    
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
