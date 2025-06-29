#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// tests of sub-functions

TEST(yaml, _split_quotes_by_control_chars_01){
    std::vector<std::string> ret;
    const char* str = " [ a, b , c , { k1:v1, k 2 : v 2 , k3:}] ";
    bool tf = sstd_yaml::_split_quotes_by_control_chars(ret, str, strlen(str)); // TEST THIS LINE
    
//    sstd::printn(tf);
//    sstd::printn(ret);
    
    std::vector<std::string> ret_ans = {"[", "a", ",", "b", ",", "c", ",", "{", "k1", ":", "v1", ",", "k 2", ":", "v 2", ",", "k3", ":", "}", "]"};
    ASSERT_TRUE(tf);
    ASSERT_TRUE(ret == ret_ans);
}
TEST(yaml, _split_quotes_by_control_chars_02){
    std::vector<std::string> ret;
    const char* str = " \" [ \", ' [ ] {} ' ,  a, b , c , { k1:v1, k 2 : v 2 , k3:}] ";
    bool tf = sstd_yaml::_split_quotes_by_control_chars(ret, str, strlen(str)); // TEST THIS LINE
    
//    sstd::printn(tf);
//    sstd::printn(ret);
    
    std::vector<std::string> ret_ans = {"\" [ \"", ",", "' [ ] {} '", ",", "a", ",", "b", ",", "c", ",", "{", "k1", ":", "v1", ",", "k 2", ":", "v 2", ",", "k3", ":", "}", "]"};
    ASSERT_TRUE(tf);
    ASSERT_TRUE(ret == ret_ans);
}

//---

// All the Test Cases of "sstd_yaml::_data_type_and_format()"
//
// ┌───────────┬────────────┬────────┬────────────────────┬────────────────────┬─────────┬────────────────────────────────────────┬────────────────────────────────────────────────┐
// │           │            │        │ (Black Style Side) │ (Black Style Side) │         │ Concrete Example                       │                                                │
// │ Test Case │ Input      │ Is Str │ Is List            │ Is Hash            │ Is Flow │ 01           02                        │ Note                                           │
// ├───────────┼────────────┼────────┼────────────────────┼────────────────────┼─────────┼────────────┼───────────────────────────┼────────────────────────────────────────────────┤
// │ Case01    │ v          │   T    │                    │                    │         │ v          │ "k: v"                    │ Default value                                  │
// ├───────────┼────────────┼────────┼────────────────────┼────────────────────┼─────────┼────────────┼───────────────────────────┼────────────────────────────────────────────────┤
// │ Case02    │ - v        │        │         T          │                    │         │ - v        │ - - - "k: v"              │                                                │
// ├───────────┼────────────┼────────┼────────────────────┼────────────────────┼─────────┼────────────┼───────────────────────────┼────────────────────────────────────────────────┤
// │ Case03    │ k: v       │        │                    │          T         │         │ k: v       │ "k[]{: }": "v[]{: }"      │                                                │
// ├───────────┼────────────┼────────┼────────────────────┼────────────────────┼─────────┼────────────┼───────────────────────────┼────────────────────────────────────────────────┤
// │ Case04    │ k[]: v[]   │        │                    │          T         │         │ k[]: v[]   │ k[:]: v[:]                │                                                │
// ├───────────┼────────────┼────────┼────────────────────┼────────────────────┼─────────┼────────────┼───────────────────────────┼────────────────────────────────────────────────┤
// │ Case05    │ k{}: v{}   │        │                    │          T         │         │ k{}: v{}   │ k{:}: v{:}                │                                                │
// ├───────────┼────────────┼────────┼────────────────────┼────────────────────┼─────────┼────────────┼───────────────────────────┼────────────────────────────────────────────────┤
// │ Case06    │ []         │   T    │                    │                    │    T    │ []         │ ["[]{}: "]                │ IsStr become `true` because of a default value │
// ├───────────┼────────────┼────────┼────────────────────┼────────────────────┼─────────┼────────────┼───────────────────────────┼────────────────────────────────────────────────┤
// │ Case07    │ {}         │   T    │                    │                    │    T    │ {}         │ {"[]{}: ": "[]{}: "}      │ IsStr become `true` because of a default value │
// ├───────────┼────────────┼────────┼────────────────────┼────────────────────┼─────────┼────────────┼───────────────────────────┼────────────────────────────────────────────────┤
// │ Case08    │ - []       │        │         T          │                    │    T    │ - []       │ - ["[]{}: "]              │                                                │
// ├───────────┼────────────┼────────┼────────────────────┼────────────────────┼─────────┼────────────┼───────────────────────────┼────────────────────────────────────────────────┤
// │ Case09    │ - {}       │        │         T          │                    │    T    │ - {}       │ - {"[]{}: ": "[]{}: "}    │                                                │
// ├───────────┼────────────┼────────┼────────────────────┼────────────────────┼─────────┼────────────┼───────────────────────────┼────────────────────────────────────────────────┤
// │ Case10    │ - k: v     │        │         T          │          T         │         │ - k: v     │ - "k[]{: }": "v[]{: }"    │                                                │
// ├───────────┼────────────┼────────┼────────────────────┼────────────────────┼─────────┼────────────┼───────────────────────────┼────────────────────────────────────────────────┤
// │ Case11    │ - k[]: v[] │        │         T          │          T         │         │ - k[]: v[] │ - k [:]: v[:]             │                                                │
// ├───────────┼────────────┼────────┼────────────────────┼────────────────────┼─────────┼────────────┼───────────────────────────┼────────────────────────────────────────────────┤
// │ Case12    │ - k{}: v{} │        │         T          │          T         │         │ - k{}: v{} │ - k {:}: v{:}             │                                                │
// ├───────────┼────────────┼────────┼────────────────────┼────────────────────┼─────────┼────────────┼───────────────────────────┼────────────────────────────────────────────────┤
// │ Case13    │ k: []      │        │                    │          T         │    T    │ k: []      │ k: ["[]{}: "]             │                                                │
// ├───────────┼────────────┼────────┼────────────────────┼────────────────────┼─────────┼────────────┼───────────────────────────┼────────────────────────────────────────────────┤
// │ Case14    │ k: {}      │        │                    │          T         │    T    │ k: {}      │ k: {"[]{}: ": "[]{}: "}   │                                                │
// ├───────────┼────────────┼────────┼────────────────────┼────────────────────┼─────────┼────────────┼───────────────────────────┼────────────────────────────────────────────────┤
// │ Case15    │ - k: []    │        │         T          │          T         │    T    │ - k: []    │ - k: ["[]{}: "]           │                                                │
// ├───────────┼────────────┼────────┼────────────────────┼────────────────────┼─────────┼────────────┼───────────────────────────┼────────────────────────────────────────────────┤
// │ Case16    │ - k: {}    │        │         T          │          T         │    T    │ - k: {}    │ - k: {"[]{}: ": "[]{}: "} │                                                │
// └───────────┴────────────┴────────┴────────────────────┴────────────────────┴─────────┴────────────┴───────────────────────────┴────────────────────────────────────────────────┘

//---
// Test _str2token() of data type and format

#define TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(IS_LIST, IS_HASH, IS_FLOW, LIST_TYPE_COUNT, S_IN) \
    std::string s = S_IN;                                               \
    std::vector<sstd_yaml::token> v_ret;                                \
    bool ret = sstd_yaml::_str2token(v_ret, s);                         \
    ASSERT_TRUE(ret);                                                   \
    ASSERT_EQ((uint)v_ret.size(), (uint)1);                             \
                                                                        \
    uint ans_type=sstd_yaml::type_str;                                  \
    if(IS_LIST){ ans_type += sstd_yaml::type_list; }                    \
    if(IS_HASH){ ans_type += sstd_yaml::type_hash; }                    \
    ASSERT_EQ(v_ret[0].type, (uint)ans_type);                           \
                                                                        \
    uint ans_flow = IS_FLOW ? sstd_yaml::format_flow_style : sstd_yaml::format_block_style; \
    ASSERT_EQ(v_ret[0].format, (uint)ans_flow);                         \
    ASSERT_EQ(v_ret[0].list_type_cnt, (uint)LIST_TYPE_COUNT);

TEST(yaml, _str2token__data_type_and_format_case01_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false, false, false, 0, "v"         ); }
TEST(yaml, _str2token__data_type_and_format_case02_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT( true, false, false, 1, "- v"       ); }
TEST(yaml, _str2token__data_type_and_format_case03_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true, false, 0, "k: v"      ); }
TEST(yaml, _str2token__data_type_and_format_case04_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true, false, 0, "k[]: v[]"  ); }
TEST(yaml, _str2token__data_type_and_format_case05_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true, false, 0, "k{}: v{}"  ); }
TEST(yaml, _str2token__data_type_and_format_case06_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false, false,  true, 0, "[]"        ); }
TEST(yaml, _str2token__data_type_and_format_case07_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false, false,  true, 0, "{}"        ); }
TEST(yaml, _str2token__data_type_and_format_case08_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT( true, false,  true, 1, "- []"      ); }
TEST(yaml, _str2token__data_type_and_format_case09_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT( true, false,  true, 1, "- {}"      ); }
TEST(yaml, _str2token__data_type_and_format_case10_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT( true,  true, false, 1, "- k: v"    ); }
TEST(yaml, _str2token__data_type_and_format_case11_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT( true,  true, false, 1, "- k[]: v[]"); }
TEST(yaml, _str2token__data_type_and_format_case12_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT( true,  true, false, 1, "- k{}: v{}"); }
TEST(yaml, _str2token__data_type_and_format_case13_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true,  true, 0, "k: []"     ); }
TEST(yaml, _str2token__data_type_and_format_case14_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true,  true, 0, "k: {}"     ); }
TEST(yaml, _str2token__data_type_and_format_case15_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT( true,  true,  true, 1, "- k: []"   ); }
TEST(yaml, _str2token__data_type_and_format_case16_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT( true,  true,  true, 1, "- k: {}"   ); }

//TEST(yaml, _str2token__data_type_and_format_case02_02){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT( true, false, false, 3, "- - - v"   ); } // 個別にテストケースを書く
TEST(yaml, _str2token__data_type_and_format_case03_02){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true, false, 0, "k : v"     ); }
TEST(yaml, _str2token__data_type_and_format_case04_02){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true, false, 0, "k[: v["    ); }
TEST(yaml, _str2token__data_type_and_format_case04_03){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true, false, 0, "k [: v ["  ); }
TEST(yaml, _str2token__data_type_and_format_case05_02){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true, false, 0, "k{: v{"    ); }
TEST(yaml, _str2token__data_type_and_format_case05_03){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true, false, 0, "k {: v {"  ); }
TEST(yaml, _str2token__data_type_and_format_case06_02){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false, false,  true, 0, "[{: }]"    ); } // Ex: [a, b, c, {k: v}]

//---
// Test _str2token() of val1 and val2

#define TEST_STR2TOKEN__KEY_VAL(KEY, VAL, S_IN) \
    std::string s = S_IN;                       \
    std::vector<sstd_yaml::token> v_ret;        \
    bool ret = sstd_yaml::_str2token(v_ret, s); \
    ASSERT_TRUE(ret);                           \
    ASSERT_EQ(v_ret.size(), (uint)1);           \
    ASSERT_STREQ(v_ret[0].key.c_str(), KEY);    \
    ASSERT_STREQ(v_ret[0].val.c_str(), VAL);

TEST(yaml, _str2token_val1_val2_list                    ){ TEST_STR2TOKEN__KEY_VAL("", "a", "- a"); }
TEST(yaml, _str2token_val1_val2_list_02                 ){ TEST_STR2TOKEN__KEY_VAL("", "a   ,", "- a   ,"); }
TEST(yaml, _str2token_val1_val2_list_hash               ){ TEST_STR2TOKEN__KEY_VAL("k", "v", "k: v"); }
TEST(yaml, _str2token_val1_val2_list_hash_02            ){ TEST_STR2TOKEN__KEY_VAL("k ,", "v   ,", "- k , : v   ,"); }
TEST(yaml, _str2token_val1_val2_list_hash_space         ){ TEST_STR2TOKEN__KEY_VAL("k {", "v {", "-  k { :  v { "); }
TEST(yaml, _str2token_val1_val2_flow                    ){ TEST_STR2TOKEN__KEY_VAL("", "[{k: v}]",   "[{k: v}]"); }

// mutliline flow stype notation
TEST(yaml, _str2token_val1_val2_multiline_flow          ){ TEST_STR2TOKEN__KEY_VAL("", "[\na,\nb,\nc\n]",   "[\na,\nb,\nc\n]"); }
TEST(yaml, _str2token_val1_val2_multiline_flow_list     ){ TEST_STR2TOKEN__KEY_VAL("", "[\na,\nb,\nc\n]", "- [\na,\nb,\nc\n]"); }
TEST(yaml, _str2token_val1_val2_multiline_flow_hash     ){ TEST_STR2TOKEN__KEY_VAL("k", "[\na,\nb,\nc\n]",   "k: [\na,\nb,\nc\n]"); }
TEST(yaml, _str2token_val1_val2_multiline_flow_list_hash){ TEST_STR2TOKEN__KEY_VAL("k", "[\na,\nb,\nc\n]", "- k: [\na,\nb,\nc\n]"); }

//---
// Test _str2token() of remove comments
//*
// remove comments
//TEST(yaml, _str2token_rm_comment_case01){ TEST_STR2TOKEN__KEY_VAL("", "a", "a\n# b"); } // あとで直す
TEST(yaml, _str2token_rm_comment_case02){ TEST_STR2TOKEN__KEY_VAL("", "a", "a # comment"); }
TEST(yaml, _str2token_rm_comment_case03){ TEST_STR2TOKEN__KEY_VAL("", "a # comment", "\"a # comment\""); }
//TEST(yaml, _str2token_rm_comment_case04){ TEST_STR2TOKEN__KEY_VAL("", "|\na\nb\nc", "- |\na # comment\nb # comment\nc # comment"); } // あとで直す
//*/
//---
//*
TEST(yaml, _str2token_multi_list_case00){
    std::string s = R"(
k_X: 
  k1: |+
     a
     
     c
     
k_Y: v_Y
)";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
//    sstd::printn(v_ret.size());
//    sstd::printn(v_ret);
    
    ASSERT_TRUE(ret);
    ASSERT_EQ(v_ret.size(), (uint)3);
    ASSERT_STREQ(v_ret[0].rawStr.c_str(), "k_X: ");
    ASSERT_STREQ(v_ret[0].val.c_str(),    ""     );
    ASSERT_STREQ(v_ret[1].rawStr.c_str(), "  k1: |+\n     a\n     \n     c\n     ");
    ASSERT_STREQ(v_ret[1].key.c_str(),      "k1" );
    ASSERT_STREQ(v_ret[1].val.c_str(),          "a\n\nc\n\n"); // "|+\n     a\n     \n     c\n     "
    ASSERT_STREQ(v_ret[2].rawStr.c_str(), "k_Y: v_Y");
    ASSERT_STREQ(v_ret[2].key.c_str(),    "k_Y");
    ASSERT_STREQ(v_ret[2].val.c_str(),    "v_Y");
}

//---

TEST(yaml, _str2token_multi_list_case01){
    std::string s = "- a\n- b\n- c";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
//    sstd::printn(v_ret);
    
    ASSERT_TRUE(ret);
    ASSERT_EQ(v_ret.size(), (uint)3);
    ASSERT_STREQ(v_ret[0].rawStr.c_str(), "- a");
    ASSERT_STREQ(v_ret[0].val.c_str(),     "a" );
    ASSERT_STREQ(v_ret[1].rawStr.c_str(), "- b");
    ASSERT_STREQ(v_ret[1].val.c_str(),     "b" );
    ASSERT_STREQ(v_ret[2].rawStr.c_str(), "- c");
    ASSERT_STREQ(v_ret[2].val.c_str(),     "c");
}
TEST(yaml, _str2token_multi_list_case02){
    std::string s = "- \"\"\n- \"\"\n- \"\"";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
//    sstd::printn(v_ret);
    
    ASSERT_TRUE(ret);
    ASSERT_EQ(v_ret.size(), (uint)3);
    ASSERT_STREQ(v_ret[0].rawStr.c_str(), "- \"\"");
    ASSERT_STREQ(v_ret[0].val.c_str(),          "");
    ASSERT_STREQ(v_ret[1].rawStr.c_str(), "- \"\"");
    ASSERT_STREQ(v_ret[1].val.c_str(),          "");
    ASSERT_STREQ(v_ret[2].rawStr.c_str(), "- \"\"");
    ASSERT_STREQ(v_ret[2].val.c_str(),          "");
}
TEST(yaml, _str2token_multi_list_case03){
    std::string s = "-\n  - a";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
//    sstd::printn(v_ret);
    
    ASSERT_TRUE(ret);
    ASSERT_EQ(v_ret.size(), (uint)2);
    ASSERT_STREQ(v_ret[0].rawStr.c_str(),     "-");
    ASSERT_STREQ(v_ret[0].val.c_str(),         "");
    ASSERT_STREQ(v_ret[1].rawStr.c_str(), "  - a");
    ASSERT_STREQ(v_ret[1].val.c_str(),        "a");
}
TEST(yaml, _str2token_multi_list_case04){
    std::string s = "- \n  - a";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
//    sstd::printn(v_ret);
    
    ASSERT_TRUE(ret);
    ASSERT_EQ(v_ret.size(), (uint)2);
    ASSERT_STREQ(v_ret[0].rawStr.c_str(),    "- ");
    ASSERT_STREQ(v_ret[0].val.c_str(),         "");
    ASSERT_STREQ(v_ret[1].rawStr.c_str(), "  - a");
    ASSERT_STREQ(v_ret[1].val.c_str(),        "a");
}

//---

TEST(yaml, _str2token_multi_list_case05){
    std::string s = "- [{\nk11: v11,\nk12:v12,\nk13:v13\n}]\n- [{\nk21: v21,\nk22:v22,\nk23:v23\n}]";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
//    sstd::printn(v_ret);

    ASSERT_TRUE(ret);
    ASSERT_EQ(v_ret.size(), (uint)2);
    ASSERT_STREQ(v_ret[0].rawStr.c_str(), "- [{\nk11: v11,\nk12:v12,\nk13:v13\n}]");
    ASSERT_STREQ(v_ret[0].val.c_str(),      "[{\nk11: v11,\nk12:v12,\nk13:v13\n}]");
    ASSERT_STREQ(v_ret[1].rawStr.c_str(), "- [{\nk21: v21,\nk22:v22,\nk23:v23\n}]");
    ASSERT_STREQ(v_ret[1].val.c_str(),      "[{\nk21: v21,\nk22:v22,\nk23:v23\n}]");
}

//---

TEST(yaml, _str2token_multi_list_case06){
    std::string s = "- - - a";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
//    sstd::printn(v_ret);
    
    ASSERT_TRUE(ret);
    ASSERT_EQ(v_ret.size(), (uint)3);
    ASSERT_STREQ(v_ret[0].rawStr.c_str(), "- - - a");
    ASSERT_STREQ(v_ret[0].val.c_str(),           "");
    ASSERT_STREQ(v_ret[1].val.c_str(),           "");
    ASSERT_STREQ(v_ret[2].val.c_str(),          "a");
    ASSERT_EQ(v_ret[0].list_type_cnt, (uint)1);
    ASSERT_EQ(v_ret[1].list_type_cnt, (uint)1);
    ASSERT_EQ(v_ret[2].list_type_cnt, (uint)1);
}

//---

TEST(yaml, _str2token_multi_list_case07){
    std::string s=R"(
- a # comment
- |
  b1
  b2
  b3

- c
- d
)";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
//    sstd::printn(v_ret);
    
    ASSERT_TRUE(ret);
    ASSERT_EQ(v_ret.size(), (uint)4);
    ASSERT_STREQ(v_ret[0].rawStr.c_str(), "- a # comment");
    ASSERT_STREQ(v_ret[0].val.c_str(),   "a");
//    sstd::printn(v_ret[1].rawStr.c_str());
    ASSERT_STREQ(v_ret[1].rawStr.c_str(), R"(- |
  b1
  b2
  b3
)");
//    sstd::printn(v_ret[1].val.c_str());
    ASSERT_STREQ(v_ret[1].val.c_str(), "b1\nb2\nb3\n"); // "|\n  b1\n  b2\n  b3\n"
}
TEST(yaml, _str2token_multi_list_case08){
    std::string s=R"(
- a # comment
- k: |+
   b1
   b2
   b3

- c
- d
)";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
//    sstd::printn(v_ret);
    
    ASSERT_TRUE(ret);
    ASSERT_EQ(v_ret.size(), (uint)4);
    ASSERT_STREQ(v_ret[0].rawStr.c_str(), "- a # comment");
    ASSERT_STREQ(v_ret[0].val.c_str(),   "a");
//    sstd::printn(v_ret[1].rawStr.c_str());
    ASSERT_STREQ(v_ret[1].rawStr.c_str(), R"(- k: |+
   b1
   b2
   b3
)");
//    sstd::printn(v_ret[1].val.c_str());
//    sstd::printn(v_ret[1].val.c_str());
    ASSERT_STREQ(v_ret[1].key.c_str(), "k");
    ASSERT_STREQ(v_ret[1].val.c_str(), "b1\nb2\nb3\n\n"); // "|+\n   b1\n   b2\n   b3\n"
}
TEST(yaml, _str2token_multi_list_case09){
    std::string s=R"(
- a # comment
- k:|
   b1
   b2
   b3

- c
- d
)";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
//    sstd::printn(v_ret);
    
    ASSERT_TRUE(ret);
    ASSERT_EQ(v_ret.size(), (uint)4);
//    sstd::printn(v_ret[0].val.c_str());
    ASSERT_STREQ(v_ret[0].val.c_str(), "a");
//    sstd::printn(v_ret[1].rawStr.c_str());
    ASSERT_STREQ(v_ret[1].rawStr.c_str(), R"(- k:|
   b1
   b2
   b3
)");
//    sstd::printn(v_ret[1].val.c_str());
    ASSERT_STREQ(v_ret[1].val.c_str(), "k:| b1 b2 b3"); // "k:|\n   b1\n   b2\n   b3\n"
    ASSERT_STREQ(v_ret[2].val.c_str(), "c");
    ASSERT_STREQ(v_ret[3].val.c_str(), "d");
}
TEST(yaml, _str2token_multi_list_case10){
    std::string s=R"(
- a
 - a
)";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
//    sstd::printn(v_ret);
    
    ASSERT_TRUE(ret);
    ASSERT_EQ(v_ret.size(), (uint)1);
//    sstd::printn(v_ret[0].rawStr.c_str());
//    ASSERT_STREQ(v_ret[0].rawStr.c_str(), R"()");
//    sstd::printn(v_ret[0].val.c_str());
    ASSERT_STREQ(v_ret[0].val.c_str(), "a - a"); // "a\n - a"
}
TEST(yaml, _str2token_multi_list_case11){
    std::string s=R"(
- x
  - - a
  - b
  - c
)";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
    //sstd::printn(v_ret);
    
    ASSERT_TRUE(ret);
    ASSERT_EQ(v_ret.size(), (uint)1);
    ASSERT_STREQ(v_ret[0].val.c_str(), "x - - a - b - c"); // "a\n - a"
}

//---

//TEST(yaml, _str2token_multi_list_except_pipe_or_inequality_sign_case01){
//}

//---



//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// Test _format_mult_line_str()
//*
TEST(yaml, _format_mult_line_str__pipeSymbol__last_line_breaks_case01){ // '|'
    std::string s=R"(|
  a)";
    std::string ret;
    const uint hsc_base_yaml=0;
    const bool has_next_token = false;
    bool ret_TF = sstd_yaml::_format_mult_line_str(ret, s, hsc_base_yaml, has_next_token);
    //sstd::printn(ret_TF);
    //sstd::printn(ret);
    
    ASSERT_TRUE(ret_TF);
    ASSERT_STREQ(ret.c_str(), "a");
}
TEST(yaml, _format_mult_line_str__pipeSymbol__last_line_breaks_case02){ // '|'
    std::string s=R"(|
  a
)";
    std::string ret;
    const uint hsc_base_yaml=0;
    const bool has_next_token = false;
    bool ret_TF = sstd_yaml::_format_mult_line_str(ret, s, hsc_base_yaml, has_next_token);
    //sstd::printn(ret_TF);
    //sstd::printn(ret);
    
    ASSERT_TRUE(ret_TF);
    ASSERT_STREQ(ret.c_str(), "a\n");
}
TEST(yaml, _format_mult_line_str__pipeSymbol__last_line_breaks_case03){ // '|'
    std::string s=R"(|
  a

)";
    std::string ret;
    const uint hsc_base_yaml=0;
    const bool has_next_token = false;
    bool ret_TF = sstd_yaml::_format_mult_line_str(ret, s, hsc_base_yaml, has_next_token);
    //sstd::printn(ret_TF);
    //sstd::printn(ret);
    
    ASSERT_TRUE(ret_TF);
    ASSERT_STREQ(ret.c_str(), "a\n");
}
TEST(yaml, _format_mult_line_str__pipeSymbol__last_line_breaks_case04){ // '|+'
    std::string s=R"(|+
  a)";
    std::string ret;
    const uint hsc_base_yaml=0;
    const bool has_next_token = false;
    bool ret_TF = sstd_yaml::_format_mult_line_str(ret, s, hsc_base_yaml, has_next_token);
    //sstd::printn(ret_TF);
    //sstd::printn(ret);
    
    ASSERT_TRUE(ret_TF);
    ASSERT_STREQ(ret.c_str(), "a");
}
TEST(yaml, _format_mult_line_str__pipeSymbol__last_line_breaks_case05){ // '|+'
    std::string s=R"(|+
  a
)";
    std::string ret;
    const uint hsc_base_yaml=0;
    const bool has_next_token = false;
    bool ret_TF = sstd_yaml::_format_mult_line_str(ret, s, hsc_base_yaml, has_next_token);
    //sstd::printn(ret_TF);
    //sstd::printn(ret);
    
    ASSERT_TRUE(ret_TF);
    ASSERT_STREQ(ret.c_str(), "a\n");
}
TEST(yaml, _format_mult_line_str__pipeSymbol__last_line_breaks_case06){ // '|+'
    std::string s=R"(|+
  a

)";
    std::string ret;
    const uint hsc_base_yaml=0;
    const bool has_next_token = false;
    bool ret_TF = sstd_yaml::_format_mult_line_str(ret, s, hsc_base_yaml, has_next_token);
    //sstd::printn(ret_TF);
    //sstd::printn(ret);
    
    ASSERT_TRUE(ret_TF);
    ASSERT_STREQ(ret.c_str(), "a\n\n");
}

//---

TEST(yaml, _format_mult_line_str__pipeSymbol__NoPlusOrMinus__case01){ // '|1'
    std::string s=R"(|1
  b1
 b2
 b3
  
 b4

)";
    std::string ret;
    const uint hsc_base_yaml=0;
    const bool has_next_token = false;
    bool ret_TF = sstd_yaml::_format_mult_line_str(ret, s, hsc_base_yaml, has_next_token);
//    sstd::printn(ret_TF);
//    sstd::printn(ret);
    
    ASSERT_TRUE(ret_TF);
    ASSERT_STREQ(ret.c_str(), R"( b1
b2
b3
 
b4
)");
}
TEST(yaml, _format_mult_line_str__pipeSymbol__PipeSymbol__case01){ // '|+1'
    std::string s=R"(|+1
  b1
 b2
 b3
  
 b4

)";
    std::string ret;
    const uint hsc_base_yaml=0;
    const bool has_next_token = false;
    bool ret_TF = sstd_yaml::_format_mult_line_str(ret, s, hsc_base_yaml, has_next_token);
//    sstd::printn(ret_TF);
//    sstd::printn(ret);
    
    ASSERT_TRUE(ret_TF);
    ASSERT_STREQ(ret.c_str(), R"( b1
b2
b3
 
b4

)");
}
TEST(yaml, _format_mult_line_str__pipeSymbol__MinusSymbol__case01){ // '|-1'
    std::string s=R"(|-1
  b1
 b2
 b3
  
 b4

)";
    std::string ret;
    const uint hsc_base_yaml=0;
    const bool has_next_token = false;
    bool ret_TF = sstd_yaml::_format_mult_line_str(ret, s, hsc_base_yaml, has_next_token);
//    sstd::printn(ret_TF);
//    sstd::printn(ret);
    
    ASSERT_TRUE(ret_TF);
    ASSERT_STREQ(ret.c_str(), R"( b1
b2
b3
 
b4)");
}

//---

TEST(yaml, _format_mult_line_str__GreaterThanSymbol__NoPlusOrMinus__case01){ // '>1'
    std::string s=R"(>1
  b1
  b2
  b3)";
    std::string ret;
    const uint hsc_base_yaml=0;
    const bool has_next_token = false;
    bool ret_TF = sstd_yaml::_format_mult_line_str(ret, s, hsc_base_yaml, has_next_token);
//    sstd::printn(ret_TF);
//    sstd::printn(ret);
    
    ASSERT_TRUE(ret_TF);
    ASSERT_STREQ(ret.c_str(), " b1\n b2\n b3");
}
TEST(yaml, _format_mult_line_str__GreaterThanSymbol__NoPlusOrMinus__case02){ // '>1'
    std::string s=R"(>1
 b1
 b2
 b3)";
    std::string ret;
    const uint hsc_base_yaml=0;
    const bool has_next_token = false;
    bool ret_TF = sstd_yaml::_format_mult_line_str(ret, s, hsc_base_yaml, has_next_token);
//    sstd::printn(ret_TF);
//    sstd::printn(ret);
    
    ASSERT_TRUE(ret_TF);
    ASSERT_STREQ(ret.c_str(), "b1 b2 b3");
}
TEST(yaml, _format_mult_line_str__GreaterThanSymbol__NoPlusOrMinus__case03){ // '>1'
    std::string s=R"(>1
 b1
  b2
 b3
 b4)";
    std::string ret;
    const uint hsc_base_yaml=0;
    const bool has_next_token = false;
    bool ret_TF = sstd_yaml::_format_mult_line_str(ret, s, hsc_base_yaml, has_next_token);
//    sstd::printn(ret_TF);
//    sstd::printn(ret);
    
    ASSERT_TRUE(ret_TF);
    //ASSERT_STREQ(ret.c_str(), "b1\n b2\nb3 b4");
    ASSERT_STREQ(ret.c_str(), "b1\n b2\nb3 b4");
}
TEST(yaml, _format_mult_line_str__GreaterThanSymbol__NoPlusOrMinus__case04){ // '>1'
    std::string s=R"(>1
    b1
    b2
    b3

)";
    std::string ret;
    const uint hsc_base_yaml=2;
    const bool has_next_token = false;
    bool ret_TF = sstd_yaml::_format_mult_line_str(ret, s, hsc_base_yaml, has_next_token);
//    sstd::printn(ret_TF);
//    sstd::printn(ret);
    
    ASSERT_TRUE(ret_TF);
    ASSERT_STREQ(ret.c_str(), " b1\n b2\n b3\n");
}

//---

TEST(yaml, _format_mult_line_str__NoSymbol__case01){
    std::string s=R"(k:|x
  a
 b
)";
    std::string ret;
    const uint hsc_base_yaml=0;
    const bool has_next_token = false;
    bool ret_TF = sstd_yaml::_format_mult_line_str(ret, s, hsc_base_yaml, has_next_token);
//    sstd::printn(ret_TF);
//    sstd::printn(ret);
    
    ASSERT_TRUE(ret_TF);
    ASSERT_STREQ(ret.c_str(), "k:|x a b");
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
//*
TEST(yaml, _token2cmd_usual_cases){
    std::string s = R"(
- k1: v11
- k2:
  - v21
  - v22
  - k23: # null
  - k24: v241
- k3: v31
- k5: # null
  k51: v511
- # null
- # null
-
  -
    -
      - v8111
- v9
)";
    std::vector<sstd_yaml::token> ret_v_token;
    std::vector<sstd_yaml::command> ret_v_cmd;
    bool ret = false;
    ret = sstd_yaml::_str2token(ret_v_token, s);
    //printf("------------------------------------------------------\n");
    //sstd::printn(ret_v_token);
    ret = sstd_yaml::_token2cmd(ret_v_cmd, ret_v_token);
    //printf("------------------------------------------------------\n");
    //sstd::printn(ret_v_cmd);
    //printf("------------------------------------------------------\n");
    
    ASSERT_TRUE(ret);

    uint idx=0;
    // -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)0);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_stack); // stack
    ++idx;
    // k1:
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)2);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_hash);
    ASSERT_STREQ(ret_v_cmd[idx].val.c_str(), "k1");
    ++idx;
    //     v11
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_assign);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_str);
    ASSERT_EQ(ret_v_cmd[idx].format, sstd_yaml::format_block_style);
    ASSERT_STREQ(ret_v_cmd[idx].val.c_str(), "v11");
    ++idx;

    // -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)0);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_stack); // stack
    ++idx;
    //   k2:
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)2);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_hash);
    ASSERT_STREQ(ret_v_cmd[idx].val.c_str(), "k2");
    ++idx;
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_stack); // stack
    ++idx;
    
    //   -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)2);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    //     v21
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_assign);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_str);
    ASSERT_EQ(ret_v_cmd[idx].format, sstd_yaml::format_block_style);
    ASSERT_STREQ(ret_v_cmd[idx].val.c_str(), "v21");
    ++idx;
    
    //   -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)2);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    //     v22
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_assign);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_str);
    ASSERT_EQ(ret_v_cmd[idx].format, sstd_yaml::format_block_style);
    ASSERT_STREQ(ret_v_cmd[idx].val.c_str(), "v22");
    ++idx;
    
    //   -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)2);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_stack); // stack
    ++idx;
    //     k23:
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)4);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_hash);
    ASSERT_STREQ(ret_v_cmd[idx].val.c_str(), "k23");
    ++idx;
    
    //   -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)2);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_stack); // stack
    ++idx;
    //     k24:
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)4);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_hash);
    ASSERT_STREQ(ret_v_cmd[idx].val.c_str(), "k24");
    ++idx;
    //          v241
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_assign);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_str);
    ASSERT_EQ(ret_v_cmd[idx].format, sstd_yaml::format_block_style);
    ASSERT_STREQ(ret_v_cmd[idx].val.c_str(), "v241");
    ++idx;
    
    // -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)0);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_stack); // stack
    ++idx;
    //   k3:
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)2);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_hash);
    ASSERT_STREQ(ret_v_cmd[idx].val.c_str(), "k3");
    ++idx;
    //       v31
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_assign);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_str);
    ASSERT_EQ(ret_v_cmd[idx].format, sstd_yaml::format_block_style);
    ASSERT_STREQ(ret_v_cmd[idx].val.c_str(), "v31");
    ++idx;
    
    // -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)0);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_stack); // stack
    ++idx;
    //   k5: #null
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)2);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_hash);
    ASSERT_STREQ(ret_v_cmd[idx].val.c_str(), "k5");
    ++idx;
    
    //   k51:
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)2);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_hash);
    ASSERT_STREQ(ret_v_cmd[idx].val.c_str(), "k51");
    ++idx;
    //        v511
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_assign);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_str);
    ASSERT_EQ(ret_v_cmd[idx].format, sstd_yaml::format_block_style);
    ASSERT_STREQ(ret_v_cmd[idx].val.c_str(), "v511");
    ++idx;
    
    // - # null
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)0);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    
    // - # null
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)0);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    
    // -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)0);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_stack); // stack
    ++idx;
    //   -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)2);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_stack); // stack
    ++idx;
    //     -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)4);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_stack); // stack
    ++idx;
    //       -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)6);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    //         v8111
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_assign);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_str);
    ASSERT_EQ(ret_v_cmd[idx].format, sstd_yaml::format_block_style);
    ASSERT_STREQ(ret_v_cmd[idx].val.c_str(), "v8111");
    ++idx;
    // -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].hsc, (uint)0);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    //   v9
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_assign);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_str);
    ASSERT_EQ(ret_v_cmd[idx].format, sstd_yaml::format_block_style);
    ASSERT_STREQ(ret_v_cmd[idx].val.c_str(), "v9");
    ++idx;
}

//---

TEST(yaml, _token2cmd_null_values_case01){
    std::string s = R"(
- 
- 
)";
    std::vector<sstd_yaml::token> ret_v_token;
    std::vector<sstd_yaml::command> ret_v_cmd;
    bool ret = false;
    ret = sstd_yaml::_str2token(ret_v_token, s);
    ret = sstd_yaml::_token2cmd(ret_v_cmd, ret_v_token);
//    sstd::printn(ret_v_cmd);
    ASSERT_TRUE(ret);
    
    uint idx=0;
    // -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    // -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
}
TEST(yaml, _token2cmd_null_values_case02){
    std::string s = R"(
k1:
k2:
)";
    std::vector<sstd_yaml::token> ret_v_token;
    std::vector<sstd_yaml::command> ret_v_cmd;
    bool ret = false;
    ret = sstd_yaml::_str2token(ret_v_token, s);
    ret = sstd_yaml::_token2cmd(ret_v_cmd, ret_v_token);
//    sstd::printn(ret_v_cmd);
    ASSERT_TRUE(ret);

    uint idx=0;
    // k1:
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_hash);
    ++idx;
    // k2:
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_hash);
    ++idx;
}
TEST(yaml, _token2cmd_null_values_case03){
    std::string s = R"(
- k1:
- k2:
)";
    std::vector<sstd_yaml::token> ret_v_token;
    std::vector<sstd_yaml::command> ret_v_cmd;
    bool ret = false;
    ret = sstd_yaml::_str2token(ret_v_token, s);
    ret = sstd_yaml::_token2cmd(ret_v_cmd, ret_v_token);
//    sstd::printn(ret_v_cmd);
    ASSERT_TRUE(ret);

    uint idx=0;
    // -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_stack); // stack
    ++idx;
    // k1:
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_hash);
    ++idx;
    // -
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_list);
    ++idx;
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_stack); // stack
    ++idx;
    // k2:
    ASSERT_EQ(ret_v_cmd[idx].ope, sstd_yaml::ope_alloc);
    ASSERT_EQ(ret_v_cmd[idx].type, sstd_yaml::type_hash);
    ++idx;
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// comments
//*
TEST(yaml, comments_str){
    std::string s=R"(
a # comment
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = "a";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, comments_str_quotes){
    std::string s=R"(
"a # not-comment" # comment
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = "a # not-comment";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, comments_list){
    std::string s=R"(
- a # comment
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "a";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, comments_list_quotes){
    std::string s=R"(
- "a # not-comment" # comment
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "a # not-comment";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, comments_hash){
    std::string s=R"(
k: v # comment
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k"] = "v";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, comments_hash_quotes){
    std::string s=R"(
"k # not-comment": "v # not-comment" # comment
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k # not-comment"] = "v # not-comment";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// var
//*
TEST(yaml, var_str_1_line){
    std::string s=R"(
a # comment
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = "a";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, var_str_2_lines_err){
    // I feeel it is difficult to read which method is appropriate for the handling of multi -line comments from the specifications.
    // Memo: checking again: "Example 6.11 Multi-Line Comments" at the specification (https://yaml.org/spec/1.2.2/#rule-ns-hex-digit)
    
    std::string s=R"(
a # comment
b
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    //testing::internal::CaptureStdout();
    //sstd::terp::var yml; ASSERT_FALSE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //std::string ret = testing::internal::GetCapturedStdout().c_str();
    //sstd::printn(ret);
    //ASSERT_TRUE(sstd::strIn("OverWritting the existing data.", ret.c_str()));
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = "a b";
    
    //---
    
    ASSERT_TRUE(ret);
    ASSERT_TRUE(yml==ans);
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// list
//*
TEST(yaml, list_depth1){
    std::string s=R"(
- a # comment
- b

- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = "c";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, list_depth2){
    std::string s=R"(
- a # comment
- b
- 
  - c
  - d
- e
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(4);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = sstd::terp::list(2);
    ans[2][0] = "c";
    ans[2][1] = "d";
    ans[3] = "e";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---
// Corner case(s)

TEST(yaml, list_colon){
    std::string s=R"(
- a:a
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "a:a";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, list_flow_style_brackets){
    std::string s=R"(
- a[] # OK
- a{} # OK
#- []a # NG
#- {}a # NG
#- ][a # NG
#- }{a # NG
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = "a[]";
    ans[1] = "a{}";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, list_null){
    std::string s=R"(
-
-
-
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, list_str_listStr_listStrEnd){ // depth1
    std::string s=R"(
- a - b - c -
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);
//    sstd::printn(yml.size());
    
    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "a - b - c -";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// hash
//*
TEST(yaml, hash_depth1){
    std::string s=R"(
k1: v1 # comment
k2: v2

k3: v3
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "v1";
    ans["k2"] = "v2";
    ans["k3"] = "v3";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, hash_depth2){
    std::string s=R"(
k1: v1 # comment
k2: v2
k3: 
  k31: v31
  k32: v32
k4: v4
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "v1";
    ans["k2"] = "v2";
    ans["k3"] = sstd::terp::hash();
    ans["k3"]["k31"] = "v31";
    ans["k3"]["k32"] = "v32";
    ans["k4"] = "v4";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---
// Corner case(s)

TEST(yaml, hash_null_case01){
    std::string s=R"(
k1:
)";
    sstd::terp::var yml; bool ret_tf = sstd::yaml_load(yml, s); // TEST THIS LINE
//    sstd::printn(yml);
    ASSERT_TRUE(ret_tf);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"];
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, hash_null_case02){
    std::string s=R"(
k1:
k2:
)";
    sstd::terp::var yml; bool ret_tf = sstd::yaml_load(yml, s); // TEST THIS LINE
//    sstd::printn(yml);
    ASSERT_TRUE(ret_tf);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"];
    ans["k2"];
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
//*
TEST(yaml, hash_with_colon_01){
    std::string s=R"(
k:1: v:1
)";
    sstd::terp::var yml; bool ret_tf = sstd::yaml_load(yml, s); // TEST THIS LINE
    //sstd::printn(yml);
    ASSERT_TRUE(ret_tf);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k:1"] = "v:1";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, hash_with_colon_02){
    std::string s=R"(
k:1:: v:1
)";
    sstd::terp::var yml; bool ret_tf = sstd::yaml_load(yml, s); // TEST THIS LINE
    //sstd::printn(yml);
    ASSERT_TRUE(ret_tf);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k:1:"] = "v:1";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, hash_with_colon_03){
    std::string s=R"(
k:1::: v:1
)";
    sstd::terp::var yml; bool ret_tf = sstd::yaml_load(yml, s); // TEST THIS LINE
    //sstd::printn(yml);
    ASSERT_TRUE(ret_tf);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k:1::"] = "v:1";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, hash_with_colon_04){
    std::string s=R"(
k:1: a":":a
)";
    sstd::terp::var yml; bool ret_tf = sstd::yaml_load(yml, s); // TEST THIS LINE
    //sstd::printn(yml);
    ASSERT_TRUE(ret_tf);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k:1"] = "a\":\":a";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, hash_flow_style_brackets){
    std::string s=R"(
k[]{}: v[]{} # OK
#[]k: []v # NG
#][k: ][v # NG
#{}k: {}v # NG
#}{k: }{v # NG
)";
    sstd::terp::var yml; bool ret_tf = sstd::yaml_load(yml, s); // TEST THIS LINE
    //sstd::printn(yml);
    ASSERT_TRUE(ret_tf);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k[]{}"] = "v[]{}";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, hash_multiple_line_01){
    std::string s = R"(
h1:

  a

  b

  c

)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["h1"] = "a\nb\nc";
//    sstd::printn_all(ans);

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, hash_multiple_line_02){
    std::string s = R"(
h1:

  k1: v1
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["h1"] = sstd::terp::hash();
    ans["h1"]["k1"] = "v1";
    sstd::printn_all(ans);

    ASSERT_TRUE(yml == ans);
}

//---

TEST(yaml, hash_duplicated_err){ // TODO: ここの仕様を直す
    std::string s=R"(
k1: val1
k1: valX
)";
    testing::internal::CaptureStdout();
    sstd::terp::var yml; bool ret_tf = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret_tf==false);
    std::string ret = testing::internal::GetCapturedStdout().c_str();
    ASSERT_TRUE(sstd::strIn("Detecting the duplicated hash key.", ret.c_str())); // Do NOT check
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "val1";
    //ans["k1"] = "valX";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// list and hash

TEST(yaml, list_and_hash__NUM_LIST_AND_HASH){
    std::string s=R"(
- k1: v1
)";
    sstd::terp::var yml; bool ret_tf = sstd::yaml_load(yml, s); // TEST THIS LINE
//    sstd::printn(yml);
    ASSERT_TRUE(ret_tf);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::hash();
    ans[0]["k1"] = "v1";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, list_and_hash__conbined){
    std::string s=R"(
- k1:
  - v11
  - v12
- v2
)";
    sstd::terp::var yml; bool ret_tf = sstd::yaml_load(yml, s); // TEST THIS LINE
//    sstd::printn(yml);
    ASSERT_TRUE(ret_tf);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = sstd::terp::hash();
    ans[0]["k1"] = sstd::terp::list(2);
    ans[0]["k1"][0] = "v11";
    ans[0]["k1"][1] = "v12";
    ans[1] = "v2";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---
// Corner case(s)

TEST(yaml, list_and_hash__colon){
    std::string s=R"(
- k:1::: a":":a
)";
    sstd::terp::var yml; bool ret_tf = sstd::yaml_load(yml, s); // TEST THIS LINE
    //sstd::printn(yml);
    ASSERT_TRUE(ret_tf);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::hash();
    ans[0]["k:1::"] = "a\":\":a";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, list_and_hash_flow_style_brackets){
    std::string s=R"(
- a[]: a[] # OK
- a{}: a{} # OK
#- []a: []a # NG (Invalid)
#- ][a: ][a # NG (Invalid)
#- {}a: {}a # NG (Invalid)
#- }{a: }{a # NG (Invalid)
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = sstd::terp::hash();
    ans[0]["a[]"] = "a[]";
    ans[1] = sstd::terp::hash();
    ans[1]["a{}"] = "a{}";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// complex test cases
//*
TEST(yaml, list_hash_case01_01){ // depth2
    std::string s=R"(
- k1: v1
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);
    
    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::hash();
    ans[0]["k1"] = "v1";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, list_hash_case01_02){ // depth2
    std::string s=R"(
- k1: v1
- k2: v2
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);
    
    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = sstd::terp::hash();
    ans[0]["k1"] = "v1";
    ans[1] = sstd::terp::hash();
    ans[1]["k2"] = "v2";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, list_hash_case01_03){ // depth2
    std::string s=R"(
- k1: v1
- k2: v2
- k3: v3
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);
    
    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = sstd::terp::hash();
    ans[0]["k1"] = "v1";
    ans[1] = sstd::terp::hash();
    ans[1]["k2"] = "v2";
    ans[2] = sstd::terp::hash();
    ans[2]["k3"] = "v3";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, list_hash_case01_04){ // depth2
    std::string s=R"(
- 
  - k1: v1
  - k2: v2
- k3: v3
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);
    
    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = sstd::terp::list(2);
    ans[0][0] = sstd::terp::hash();
    ans[0][0]["k1"] = "v1";
    ans[0][1] = sstd::terp::hash();
    ans[0][1]["k2"] = "v2";
    ans[1] = sstd::terp::hash();
    ans[1]["k3"] = "v3";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, list_hash_case02){ // depth2
    std::string s=R"(
- a # comment
- b

- k1: v1
  k2: v2
  k3: v3
- k3:
  k4: v4
- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);
    
    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(5);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = sstd::terp::hash();
    ans[2]["k1"] = "v1";
    ans[2]["k2"] = "v2";
    ans[2]["k3"] = "v3";
    ans[3] = sstd::terp::hash();
    ans[3]["k3"];
    ans[3]["k4"] = "v4";
    ans[4] = "c";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, hash_list){ // depth2
    std::string s=R"(
k1: v1 # comment
k2: v2
k3: 
  - v31
  - v32
k4: v4
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "v1";
    ans["k2"] = "v2";
    ans["k3"] = sstd::terp::list(2);
    ans["k3"][0] = "v31";
    ans["k3"][1] = "v32";
    ans["k4"] = "v4";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, list_hash_list_case01){ // depth3
    std::string s=R"(
- a # comment
- b

- k1: v1
  k2:
    - v21
    - v22
    - v23
  k3: v3
- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);
    
    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(4);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = sstd::terp::hash();
    ans[2]["k1"] = "v1";
    ans[2]["k2"] = sstd::terp::list(3);
    ans[2]["k2"][0] = "v21";
    ans[2]["k2"][1] = "v22";
    ans[2]["k2"][2] = "v23";
    ans[2]["k3"] = "v3";
    ans[3] = "c";
//    Sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, list_hash_list_case02){ // depth3
    std::string s=R"(
          # hsc_lx, hsc_hx
- a       #      0, 2
- b       #      0, 2

- k1:     #      0, 2
    - v11 #      4, 4
    - v12 #      4, 4
    - v13 #      4, 4
  k2:     #      2, 2
    - v21 #      4, 4
    - v22 #      4, 4
    - v23 #      4, 4
  k3: v3  #      2, 2
- c       #      0, 2
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);
    
    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(4);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = sstd::terp::hash();
    ans[2]["k1"] = sstd::terp::list(3);
    ans[2]["k1"][0] = "v11";
    ans[2]["k1"][1] = "v12";
    ans[2]["k1"][2] = "v13";
    ans[2]["k2"] = sstd::terp::list(3);
    ans[2]["k2"][0] = "v21";
    ans[2]["k2"][1] = "v22";
    ans[2]["k2"][2] = "v23";
    ans[2]["k3"] = "v3";
    ans[3] = "c";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, hash_list_hash){ // depth3
    std::string s=R"(
k1: v1 # comment
k2: v2
k3: 
  - v31
  - k32: v321
  - v33
k4: v4
)";
    sstd::terp::var yml; bool ret_tf = sstd::yaml_load(yml, s); // TEST THIS LINE
//    sstd::printn(yml);
    ASSERT_TRUE(ret_tf);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "v1";
    ans["k2"] = "v2";
    ans["k3"] = sstd::terp::list(3);
    ans["k3"][0] = "v31";
    ans["k3"][1] = sstd::terp::hash();
    ans["k3"][1]["k32"] = "v321";
    ans["k3"][2] = "v33";
    ans["k4"] = "v4";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, list_hash_list_hash){ // depth4
}

//---

TEST(yaml, hash_list_hash_list){ // depth4
    std::string s=R"(
k1: v1 # comment
k2: v2
k3: 
  - v31
  - k32:
    - v321
    - v322
    - v323
  - v33
k4: v4
)";
    sstd::terp::var yml; bool ret_tf = sstd::yaml_load(yml, s); // TEST THIS LINE
//    sstd::printn(yml);
    ASSERT_TRUE(ret_tf);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "v1";
    ans["k2"] = "v2";
    ans["k3"] = sstd::terp::list(3);
    ans["k3"][0] = "v31";
    ans["k3"][1] = sstd::terp::hash();
    ans["k3"][1]["k32"] = sstd::terp::list(3);
    ans["k3"][1]["k32"][0] = "v321";
    ans["k3"][1]["k32"][1] = "v322";
    ans["k3"][1]["k32"][2] = "v323";
    ans["k3"][2] = "v33";
    ans["k4"] = "v4";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// ignore ! option


//-----------------------------------------------------------------------------------------------------------------------------------------------
// TypeConversion

// Note. TypeConversion segment is implemented and tested on terp.cpp/hpp.

// to<bool>
// to<char>
// to<int>
// to<int8>
// to<int16>
// to<int32>
// to<int64>
// to<uint>
// to<uint8>
// to<uint16>
// to<uint32>
// to<uint64>
// to<float>
// to<double>
// to<const char*>
// to<std::string>

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Multi line string for list
//*
TEST(yaml, multi_line_str_by_list_vertical_line){ // - |
    std::string s=R"(
- a # comment
- |
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1\nb2\nb3\n";
    ans[2] = "c";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_vertical_line_minus){ // - |-
    std::string s=R"(
- a # comment
- |-
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1\nb2\nb3";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_vertical_line_plus){ // - |+
    std::string s=R"(
- a # comment
- |+
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1\nb2\nb3\n\n\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_list_vertical_line_num_0){ // - |0 (Can't set 0. Because of the indent under list struct is equal or larger than 1)
// }

TEST(yaml, multi_line_str_by_list_vertical_line_num_1){ // - |1
    std::string s=R"(
- a # comment
- |1
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = " b1\n b2\n b3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_vertical_line_num_1_case02){ // - |1
    std::string s=R"(
- a # comment
- |1
 b1
  b2
 b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1\n b2\nb3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_vertical_line_num_2){ // - |2
    std::string s=R"(
- a # comment
- |2
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1\nb2\nb3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_list_vertical_line_minus_num_0){ // - |-0 (Can't set 0. Because of the indent under list struct is equal or larger than 1)
// }

TEST(yaml, multi_line_str_by_list_vertical_line_minus_num_1){
    std::string s=R"(
- a # comment
- |-1
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = " b1\n b2\n b3";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_list_vertical_line_plus_num_0){ // - |+0 (Can't set 0. Because of the indent under list struct is equal or larger than 1)
// }

TEST(yaml, multi_line_str_by_list_vertical_line_plus_num_1){
    std::string s=R"(
- a # comment
- |+1
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = " b1\n b2\n b3\n\n\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_vertical_line_with_different_head_spaces__vertical){
    std::string s=R"(
- |
  a
  b
    c
    d
  e
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "a\nb\n  c\n  d\ne\n";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, multi_line_str_by_list_vertical_line_with_different_head_spaces__vertical_1){
    std::string s=R"(
- |1
  a
  b
    c
    d
  e
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = " a\n b\n   c\n   d\n e\n";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, multi_line_str_by_list_vertical_line_with_different_head_spaces__vertical_minus){
    std::string s=R"(
- |-
  a
  b
    c
    d
  e
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "a\nb\n  c\n  d\ne";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, multi_line_str_by_list_greater){ // - >
    std::string s=R"(
- a # comment
- >
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1 b2 b3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_greater_minus){ // - >-
    std::string s=R"(
- a # comment
- >-
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1 b2 b3";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_greater_plus){ // - >+
    std::string s=R"(
- a # comment
- >+
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1 b2 b3\n\n\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_list_greater_num_0){ // - >0 (Can't set 0. Because of the indent under list struct is equal or larger than 1)
// }

TEST(yaml, multi_line_str_by_list_greater_num_1){ // - >1
    std::string s=R"(
- a # comment
- >1
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = " b1\n b2\n b3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, multi_line_str_by_list_greater_num_1_case02){ // - >1
    std::string s=R"(
- a # comment
- 
  - >1
    b1
    b2
    b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = sstd::terp::list(1);
    ans[1][0] = " b1\n b2\n b3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, multi_line_str_by_list_greater_num_2){ // - >2
    std::string s=R"(
- a # comment
- >2
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1 b2 b3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_greater_num_4){ // - >4
    std::string s=R"(
- a # comment
- 
  - >4
      b1
      b2
      b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = sstd::terp::list(1);
    ans[1][0] = "b1 b2 b3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_greater_minus_num_1){ // - >-1
    std::string s=R"(
- a # comment
- >-1
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = " b1\n b2\n b3";
    ans[2] = "c";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_list_greater_minus_num_2){ // - >-2
// }

// TEST(yaml, multi_line_str_by_list_greater_plus_num_1){ // - >-1
// }

// TEST(yaml, multi_line_str_by_list_greater_plus_num_2){ // - >-2
// }
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// Multi line string for hash
//*
TEST(yaml, multi_line_str_by_hash_vertical_line){ // : |
    std::string s=R"(
k1: a # comment
k2: |
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = "b1\nb2\nb3\n";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_hash_vertical_line_minus){ // : |-
    std::string s=R"(
k1: a # comment
k2: |-
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = "b1\nb2\nb3";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_hash_vertical_line_plus){ // : |+
    std::string s=R"(
k1: a # comment
k2: |+
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = "b1\nb2\nb3\n\n\n";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_hash_vertical_line_num_0){ // : |0 (Can't set 0. Because of the indent under hash struct is equal or larger than 1)
// }

TEST(yaml, multi_line_str_by_hash_vertical_line_num_1){ // : |1
    std::string s=R"(
k1: a # comment
k2: |1
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = " b1\n b2\n b3\n";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_hash_vertical_line_num_2){ // : |2
    std::string s=R"(
k1: a # comment
k2: |2
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = "b1\nb2\nb3\n";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_hash_vertical_line_minus_num_1){ // : |-1
    std::string s=R"(
k1: a # comment
k2: |-1
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = " b1\n b2\n b3";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_hash_vertical_line_minus_num_2){ // : |-2
// }

// TEST(yaml, multi_line_str_by_hash_vertical_line_plus_num_1){ // : |+1
// }

// TEST(yaml, multi_line_str_by_hash_vertical_line_plus_num_2){ // : |+2
// }

//---

TEST(yaml, multi_line_str_by_hash_greater){ // : >
    std::string s=R"(
k1: a # comment
k2: >
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = "b1 b2 b3\n";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_hash_greater_minus){ // : >-
    std::string s=R"(
k1: a # comment
k2: >-
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = "b1 b2 b3";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_hash_greater_plus){ // : >+
    std::string s=R"(
k1: a # comment
k2: >+
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = "b1 b2 b3\n\n\n";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_hash_greater_num_0){ // : >0 (Can't set 0. Because of the indent under hash struct is equal or larger than 1)
// }

TEST(yaml, multi_line_str_by_hash_greater_num_1){ // : >1
    std::string s=R"(
k1: a # comment
k2: >1
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = " b1\n b2\n b3\n";
    ans["k3"] = "c";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_hash_greater_num_2){ // : >2
    std::string s=R"(
k1: a # comment
k2: >2
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = "b1 b2 b3\n";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_hash_greater_minus_num_1){ // : >-1
// }

// TEST(yaml, multi_line_str_by_hash_greater_minus_num_2){ // : >-2
// }


// TEST(yaml, multi_line_str_by_hash_greater_plus_num_1){ // : >+1
// }

// TEST(yaml, multi_line_str_by_hash_greater_plus_num_2){ // : >+2
// }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Double quotation "" and Single quotation ''

TEST(yaml, double_quotation_NUM_STR){
    std::string s=R"(
"a: b c\"

def
g"
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans=R"(a: b c"
def g)";
    // "a: b c\"\ndef g"
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_NUM_STR_xx){
    std::string s=R"(a

b
c)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans="a\nb c";
    // "a: b c\"\ndef g"
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, double_quotation_list_NUM_LIST_case01){
    std::string s=R"(
- "a: b c "
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "a: b c ";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_list_NUM_LIST_case02){ // WIP
    // See "5.7. Escaped Characters" at https://yaml.org/spec/1.2.2/#57-escaped-characters
    
    std::string s=R"(
- "\
   abc\
   def"
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "abcdef";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, double_quotation_list_NUM_HASH_dq_case01){
    std::string s=R"(
"key1": "a: b c "
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["key1"] = "a: b c ";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_list_NUM_HASH_dq_case02){ // escape \" and non escape '
    std::string s=R"(
"key1 \"'": " a: b c \"' "
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans[R"(key1 "')"] = R"( a: b c "' )";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, single_quotation_list_NUM_HASH_sq_case01){
    std::string s=R"(
'key1': 'a: b c '
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["key1"] = "a: b c ";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, single_quotation_list_NUM_HASH_sq_case02){ // escape \' and non escape "
    std::string s=R"(
'key1 \'"': ' a: b c \'" '
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["key1 '\""] = " a: b c '\" ";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, double_quotation_list_NUM_LIST_AND_HASH_dq_case01){
    std::string s=R"(
- "key1": "a: b c "
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::hash();
    ans[0]["key1"] = "a: b c ";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, single_quotation_list_NUM_LIST_AND_HASH_sq_case01){
    std::string s=R"(
- 'key1': 'a: b c '
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::hash();
    ans[0]["key1"] = "a: b c ";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, double_quotation_list_case01){
    std::string s=R"(
- "a: b"
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "a: b";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_list_case02){
    std::string s=R"(
- "a b c"
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "a b c";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_list_case03){
    std::string s=R"(
- "- a"
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "- a";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_list_case04){
    std::string s=R"(
" - a "
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = " - a ";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---
// NULL case

TEST(yaml, double_quotation_empty_list_case01){
    std::string s=R"(
- ""
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_empty_list_hash_case01){
    std::string s=R"(
- "": ""
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::hash();
    ans[0][""] = "";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_empty_hash_case01){
    std::string s=R"(
"": ""
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans[""] = "";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// Complicated test
//*
// Double quotation "" and Single quotation ''

TEST(yaml, double_quotation_complicated_multiline_test_case01){
    std::string s=R"(
- "I am a cat.\
    There is no name yet."
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "I am a cat.There is no name yet.";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_complicated_multiline_test_case02){
    std::string s=R"(
- "I am a cat. \
    There is no name yet."
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "I am a cat. There is no name yet.";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_complicated_multiline_test_case03){
    std::string s=R"(
- "I am a cat.
    There is no name yet."
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "I am a cat. There is no name yet.";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_complicated_multiline_test_case04){
    std::string s=R"(
- "I am a cat. 
    There is no name yet."
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "I am a cat. There is no name yet.";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_complicated_multiline_test_case05){
    std::string s=R"(
- "I am a cat.  
    There is no name yet."
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "I am a cat. There is no name yet.";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_complicated_multiline_test_case06){
    std::string s=R"(
- "I am a cat.   \
    There is no name yet."
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "I am a cat.   There is no name yet.";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_complicated_multiline_test_case07){
    std::string s=R"(
- "  I am a cat.
    There is no name yet."
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "  I am a cat. There is no name yet.";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_complicated_multiline_test_case08){
    std::string s=R"(
- "  I am a cat.
   
   
 
    There is no name yet. "
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "  I am a cat.\n\n\nThere is no name yet. ";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_complicated_multiline_test_case09){
    std::string s=R"(
- "\
    I am a cat.\
    There is no name yet."
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "I am a cat.There is no name yet.";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_complicated_multiline_test_case10){
    std::string s=R"(
- "
    I am a cat.\
    There is no name yet."
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = " I am a cat.There is no name yet.";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_complicated_multiline_test_case11){
    std::string s=R"(
- "   \
    I am a cat.\
    There is no name yet."
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "   I am a cat.There is no name yet.";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, double_quotation_complicated_multiline_test_case12){
    std::string s=R"(
- key1: "\
    I am a cat.\
    There is no name yet."
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::hash();
    ans[0]["key1"] = "I am a cat.There is no name yet.";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// Multipul list indication
//*
TEST(yaml, multipul_list_indication_case01){
    std::string s=R"(
- - a
#- 
#  - a
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::list(1);
    ans[0][0] = "a";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, multipul_list_indication_case02a){
    std::string s=R"(
- - - a
  - b
#- 
#  - 
#    - a
#  - b
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::list(2);
    ans[0][0] = sstd::terp::list(1);
    ans[0][0][0] = "a";
    ans[0][1] = "b";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, multipul_list_indication_case02b){
    std::string s=R"(
#- - - a
#  - b
- 
  - 
    - a
  - b
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::list(2);
    ans[0][0] = sstd::terp::list(1);
    ans[0][0][0] = "a";
    ans[0][1] = "b";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, multipul_list_indication_case03){
    std::string s=R"(
- - - k1: v1
  - k2: v2
#- 
#  - 
#    - k1: v1
#  - k2: v2
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::list(2);
    ans[0][0] = sstd::terp::list(1);
    ans[0][0][0] = sstd::terp::hash();
    ans[0][0][0]["k1"] = "v1";
    ans[0][1] = sstd::terp::hash();
    ans[0][1]["k2"] = "v2";
//    sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, multipul_list_indication_case04){
    std::string s=R"(
- 
  - a
  - - b # TEST THIS LINE
#- 
#  - a
#  - 
#    - b # TEST THIS LINE
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::list(2);
    ans[0][0] = "a";
    ans[0][1] = sstd::terp::list(1);
    ans[0][1][0] = "b";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, multipul_list_indication_case05){
    std::string s=R"(
- - - a
#- 
#  - 
#    - a
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::list(1);
    ans[0][0] = sstd::terp::list(1);
    ans[0][0][0] = "a";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, multipul_list_indication_case06){
    std::string s=R"(
- - a
  - - - - b
#- 
#  - a
#  - 
#    - 
#      - 
#        - b
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::list(2);
    ans[0][0] = "a";
    ans[0][1] = sstd::terp::list(1);
    ans[0][1][0] = sstd::terp::list(1);
    ans[0][1][0][0] = sstd::terp::list(1);
    ans[0][1][0][0][0] = "b";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, multipul_list_indication_case07){
    std::string s=R"(
- - key1: val1
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::list(1);
    ans[0][0] = sstd::terp::hash();
    ans[0][0]["key1"] = "val1";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, multipul_list_indication_case08){
    std::string s=R"(
- a
- b
- - c1
  - c2
  - c3
- - d1: d2
- - - - e1
      - e2
      - e3
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(5);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = sstd::terp::list(3);
    ans[2][0] = "c1";
    ans[2][1] = "c2";
    ans[2][2] = "c3";
    ans[3] = sstd::terp::list(1);
    ans[3][0] = sstd::terp::hash();
    ans[3][0]["d1"] = "d2";
    ans[4] = sstd::terp::list(1);
    ans[4][0] = sstd::terp::list(1);
    ans[4][0][0] = sstd::terp::list(3);
    ans[4][0][0][0] = "e1";
    ans[4][0][0][1] = "e2";
    ans[4][0][0][2] = "e3";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// flow style notation

//---
//*
TEST(yaml, block_list_and_flow_list_01){
    std::string s=R"(
- [a, b, c]
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::list(3);
    ans[0][0] = "a";
    ans[0][1] = "b";
    ans[0][2] = "c";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, block_list_and_flow_list_02){
    std::string s=R"(
-   [a, b, c]
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::list(3);
    ans[0][0] = "a";
    ans[0][1] = "b";
    ans[0][2] = "c";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, block_list_and_flow_hash){
    std::string s=R"(
- {k1:v1, k2:v2, k3:v3}
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::hash();
    ans[0]["k1"] = "v1";
    ans[0]["k2"] = "v2";
    ans[0]["k3"] = "v3";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, block_hash_and_flow_list){
    std::string s=R"(
k1: [a, b, c]
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = sstd::terp::list(3);
    ans["k1"][0] = "a";
    ans["k1"][1] = "b";
    ans["k1"][2] = "c";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, block_hash_and_flow_hash){}
TEST(yaml, block_list_hash_and_flow_list){}
TEST(yaml, block_list_hash_and_flow_hash){}

//---

TEST(yaml, flow_style_notation_list_01){
    std::string s=R"(
[a, b, c]
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = "c";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, flow_style_notation_list_02){
    std::string s=R"(
[a, [b], c, [d, [e]], f]
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(5);
    ans[0] = "a";
    ans[1] = sstd::terp::list(1);
    ans[1][0] = "b";
    ans[2] = "c";
    ans[3] = sstd::terp::list(2);
    ans[3][0] = "d";
    ans[3][1] = sstd::terp::list(1);
    ans[3][1][0] = "e";
    ans[4] = "f";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, flow_style_notation_hash_01){
    std::string s=R"(
{k1: v1}
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "v1";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, flow_style_notation_hash_02){
    std::string s=R"(
{k1: v1, k2: v2}
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "v1";
    ans["k2"] = "v2";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, flow_style_notation_hash_03){
    std::string s=R"(
{k1: {k11: v11}}
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = sstd::terp::hash();;
    ans["k1"]["k11"] = "v11";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, flow_style_notation_hash_04){
    std::string s=R"(
{k1: {k11: {k111: v111}}, k2:v2}
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = sstd::terp::hash();
    ans["k1"]["k11"] = sstd::terp::hash();
    ans["k1"]["k11"]["k111"] = "v111";
    ans["k2"] = "v2";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, flow_style_notation_hash_null_01){
    std::string s=R"(
{k1}
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"];
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, flow_style_notation_hash_null_02){
    std::string s=R"(
{k1:, k2}
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"];
    ans["k2"];
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, flow_style_notation_hash_without_value_01){
    std::string s=R"(
- {k1}
- {k2:}
- {k3,k4}
- {k5,k6:,k7}
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(4);
    ans[0] = sstd::terp::hash();
    ans[0]["k1"];
    ans[1] = sstd::terp::hash();
    ans[1]["k2"];
    ans[2] = sstd::terp::hash();
    ans[2]["k3"];
    ans[2]["k4"];
    ans[3] = sstd::terp::hash();
    ans[3]["k5"];
    ans[3]["k6"];
    ans[3]["k7"];
//    sstd::printn(ans);

    //---
    
    ASSERT_TRUE(ret);
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, flow_style_notation_hash_without_value_01b){
    std::string s=R"(
[{k1},{k2:},{k3,k4},{k5,k6:,k7}]
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
//    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(4);
    ans[0] = sstd::terp::hash();
    ans[0]["k1"];
    ans[1] = sstd::terp::hash();
    ans[1]["k2"];
    ans[2] = sstd::terp::hash();
    ans[2]["k3"];
    ans[2]["k4"];
    ans[3] = sstd::terp::hash();
    ans[3]["k5"];
    ans[3]["k6"];
    ans[3]["k7"];
//    sstd::printn(ans);

    //---
    
    ASSERT_TRUE(ret);
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, flow_style_notation_list_multiline){
    std::string s=R"(
[a, 
b
, c]
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = "c";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, flow_style_notation_hash_multiline){
    std::string s=R"(
{k:
v}
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k"] = "v";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, flow_style_notation_list_hash){
    std::string s=R"([a, {k:v}])";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = "a";
    ans[1] = sstd::terp::hash();
    ans[1]["k"] = "v";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, flow_style_notation_list_hash_02){
    std::string s=R"([a, b, c, {k: v}])";
    //std::string s=R"([a, b, c, [k]])";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(4);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = "c";
    ans[3] = sstd::terp::hash();
    ans[3]["k"] = "v";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, flow_style_notation_list_hash_03){
    std::string s=R"([a,b,{k:v},c])";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(4);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = sstd::terp::hash();
    ans[2]["k"] = "v";
    ans[3] = "c";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, flow_style_notation_hash_list){
    std::string s=R"({k:[a,b,c]})";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k"] = sstd::terp::list(3);
    ans["k"][0] = "a";
    ans["k"][1] = "b";
    ans["k"][2] = "c";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, flow_style_notation_hash_multiline_str){
    std::string s=R"({k: "a  
  b  
  c  "})";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k"] = "a b c  ";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

// following 2 notations are same meaning
//
// [k: v]
// [{k: v}]
TEST(yaml, flow_style_notation_list_hash_type1){
    std::string s=R"([{k: v}])";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::hash();
    ans[0]["k"] = "v";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, flow_style_notation_list_hash_type2_Abbreviated){ // NOT SUPPORTED YET
    std::string s=R"([k: v])";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::hash();
    ans[0]["k"] = "v";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

//---
// Tests for sstd::yaml_load_all()

TEST(yaml, flow_style_notation_hash__for__yaml_load_all){
    std::string s=R"(
{k1: v1}
---
{k2:v2}
)";
    std::vector<sstd::terp::var> vYml; ASSERT_TRUE(sstd::yaml_load_all(vYml, s)); // TEST THIS LINE
    //sstd::printn(vYml);

    //---
    
    sstd::terp::var ans1;
    ans1 = sstd::terp::hash();
    ans1["k1"] = "v1";

    sstd::terp::var ans2;
    ans2 = sstd::terp::hash();
    ans2["k2"] = "v2";

    //---
    
    ASSERT_EQ(vYml.size(), (uint)2);
    ASSERT_TRUE(vYml[0]==ans1);
    ASSERT_TRUE(vYml[1]==ans2);
}
TEST(yaml, flow_style_notation_list_hash__for__yaml_load_all){
    std::string s=R"(
[a1, b1, c1, {k1: v1}]
---
[a2, b2, c2, {k2:v2}]
)";
    std::vector<sstd::terp::var> vYml; ASSERT_TRUE(sstd::yaml_load_all(vYml, s)); // TEST THIS LINE
    //sstd::printn(vYml);

    //---
    
    sstd::terp::var ans1;
    ans1 = sstd::terp::list(4);
    ans1[0] = "a1";
    ans1[1] = "b1";
    ans1[2] = "c1";
    ans1[3] = sstd::terp::hash();
    ans1[3]["k1"] = "v1";

    sstd::terp::var ans2;
    ans2 = sstd::terp::list(4);
    ans2[0] = "a2";
    ans2[1] = "b2";
    ans2[2] = "c2";
    ans2[3] = sstd::terp::hash();
    ans2[3]["k2"] = "v2";

    //---
    
    ASSERT_EQ(vYml.size(), (uint)2);
    ASSERT_TRUE(vYml[0]==ans1);
    ASSERT_TRUE(vYml[1]==ans2);
}/*
TEST(yaml, flow_style_notation_hash__for__yaml_load_all__error01__WIP){
    std::string s=R"(
{k1: v1
#---
#{k2:v2}
)";
    //std::vector<sstd::terp::var> vYml; ASSERT_TRUE(sstd::yaml_load_all(vYml, s)); // TEST THIS LINE
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    sstd::printn(yml);
}
TEST(yaml, flow_style_notation_hash__for__yaml_load_all__error02__WIP){
    std::string s=R"(
{k1: v1}
#---
{k2:v2
)";
    //std::vector<sstd::terp::var> vYml; ASSERT_TRUE(sstd::yaml_load_all(vYml, s)); // TEST THIS LINE
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    sstd::printn(yml);
}
*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// End marker ...
//*
TEST(yaml, end_marker){
    std::string s=R"(
- a # comment
- b

... # end marker

- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = "a";
    ans[1] = "b";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// Split file ---
//*
TEST(yaml, yaml_load_all){
    std::string s=R"(
- a1 # comment
- b1
- c1

--- # separator

- a2 # comment
- b2
- c2
)";
    std::vector<sstd::terp::var> vYml; ASSERT_TRUE(sstd::yaml_load_all(vYml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans1;
    ans1 = sstd::terp::list(3);
    ans1[0] = "a1";
    ans1[1] = "b1";
    ans1[2] = "c1";

    sstd::terp::var ans2;
    ans2 = sstd::terp::list(3);
    ans2[0] = "a2";
    ans2[1] = "b2";
    ans2[2] = "c2";

    //---
    
    ASSERT_EQ(vYml.size(), (uint)2);
    ASSERT_TRUE(vYml[0]==ans1);
    ASSERT_TRUE(vYml[1]==ans2);
}

// TEST(yaml, yaml_load_all_fp){ // Define at yaml_load(fp) section
// }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// yaml_load(fp)

TEST(yaml, yaml_load_fp){
    
    //sstd::printn(sstd::system("pwd"));
    sstd::file fp;
    ASSERT_TRUE(fp.fopen("./test/src_test/file/yaml_test/test.yaml", "r"));
    
    sstd::terp::var yml;
    ASSERT_TRUE(sstd::yaml_load(yml, fp)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, yaml_load_all_fp){
    //sstd::printn(sstd::system("pwd"));
    sstd::file fp;
    ASSERT_TRUE(fp.fopen("./test/src_test/file/yaml_test/test_yaml_load_all.yaml", "r"));
    
    std::vector<sstd::terp::var> vYml; ASSERT_TRUE(sstd::yaml_load_all(vYml, fp)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans1;
    ans1 = sstd::terp::list(3);
    ans1[0] = "a1";
    ans1[1] = "b1";
    ans1[2] = "c1";

    sstd::terp::var ans2;
    ans2 = sstd::terp::list(3);
    ans2[0] = "a2";
    ans2[1] = "b2";
    ans2[2] = "c2";

    //---
    
    ASSERT_EQ(vYml.size(), (uint)2);
    ASSERT_TRUE(vYml[0]==ans1);
    ASSERT_TRUE(vYml[1]==ans2);
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// anchor and alias

TEST(yaml, _str2token__multi_list__anchor_and_alias__case1){
    std::string s=R"(
- &ll
  - a
- *ll
)";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
//    sstd::printn_all(ret);
//    sstd::printn_all(v_ret.size());
//    sstd::printn_all(v_ret);
    
    //---
    
    ASSERT_TRUE(ret);
    ASSERT_EQ(v_ret.size(), (uint)3);
    
    ASSERT_STREQ(v_ret[0].rawStr.c_str(), "- &ll"  );
    ASSERT_STREQ(v_ret[0].key.c_str(),    ""       );
    ASSERT_STREQ(v_ret[0].val.c_str(),    ""       );
    ASSERT_STREQ(v_ret[0].aa_val.c_str(), "ll"     );
    ASSERT_EQ   (v_ret[0].ref_type,       (uint)  0);
    
    ASSERT_STREQ(v_ret[1].rawStr.c_str(), "  - a"  );
    ASSERT_STREQ(v_ret[1].key.c_str(),    ""       );
    ASSERT_STREQ(v_ret[1].val.c_str(),    "a"      );
    ASSERT_STREQ(v_ret[1].aa_val.c_str(), ""       );
    ASSERT_EQ   (v_ret[1].ref_type,       (uint)255);
    
    ASSERT_STREQ(v_ret[2].rawStr.c_str(), "- *ll"  );
    ASSERT_STREQ(v_ret[2].key.c_str(),    ""       );
    ASSERT_STREQ(v_ret[2].val.c_str(),    ""       );
    ASSERT_STREQ(v_ret[2].aa_val.c_str(), "ll"     );
    ASSERT_EQ   (v_ret[2].ref_type,       (uint)  1);
}
TEST(yaml, _str2token__multi_list__anchor_and_alias__case2){
    std::string s = R"(
- &ll
  - - a
  - b
  - c
- *ll
)";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
//    sstd::printn_all(ret);
//    sstd::printn_all(v_ret.size());
//    sstd::printn_all(v_ret);
    
    ASSERT_TRUE(ret);
    ASSERT_EQ(v_ret.size(), (uint)6);
    
    ASSERT_STREQ(v_ret[0].rawStr.c_str(), "- &ll"  );
    ASSERT_STREQ(v_ret[0].key.c_str(),    ""       );
    ASSERT_STREQ(v_ret[0].val.c_str(),    ""       );
    ASSERT_STREQ(v_ret[0].aa_val.c_str(), "ll"     );
    ASSERT_EQ   (v_ret[0].ref_type,       (uint)  0);
    
    ASSERT_STREQ(v_ret[1].rawStr.c_str(), "  - - a");
    ASSERT_STREQ(v_ret[1].key.c_str(),    ""       );
    ASSERT_STREQ(v_ret[1].val.c_str(),    ""       );
    ASSERT_STREQ(v_ret[1].aa_val.c_str(), ""       );
    ASSERT_EQ   (v_ret[1].ref_type,       (uint)255);
    
    ASSERT_STREQ(v_ret[2].rawStr.c_str(), "  - - a");
    ASSERT_STREQ(v_ret[2].key.c_str(),    ""       );
    ASSERT_STREQ(v_ret[2].val.c_str(),    "a"      );
    ASSERT_STREQ(v_ret[2].aa_val.c_str(), ""       );
    ASSERT_EQ   (v_ret[2].ref_type,       (uint)255);
    
    ASSERT_STREQ(v_ret[3].rawStr.c_str(), "  - b"  );
    ASSERT_STREQ(v_ret[3].key.c_str(),    ""       );
    ASSERT_STREQ(v_ret[3].val.c_str(),    "b"      );
    ASSERT_STREQ(v_ret[3].aa_val.c_str(), ""       );
    ASSERT_EQ   (v_ret[3].ref_type,       (uint)255);
    
    ASSERT_STREQ(v_ret[4].rawStr.c_str(), "  - c"  );
    ASSERT_STREQ(v_ret[4].key.c_str(),    ""       );
    ASSERT_STREQ(v_ret[4].val.c_str(),    "c"      );
    ASSERT_STREQ(v_ret[4].aa_val.c_str(), ""       );
    ASSERT_EQ   (v_ret[4].ref_type,       (uint)255);

    ASSERT_STREQ(v_ret[5].rawStr.c_str(), "- *ll"  );
    ASSERT_STREQ(v_ret[5].key.c_str(),    ""       );
    ASSERT_STREQ(v_ret[5].val.c_str(),    ""       );
    ASSERT_STREQ(v_ret[5].aa_val.c_str(), "ll"     );
    ASSERT_EQ   (v_ret[5].ref_type,       (uint)  1);
}

//---

TEST(yaml, anchor_and_alias__case01){
    std::string s=R"(
- &ll
  - a
- *ll
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE

    //---

    ASSERT_TRUE(ret);

    ASSERT_EQ(yml.size(), (uint)2);
    ASSERT_EQ(yml[0].size(), (uint)1);
    ASSERT_EQ(yml[1].size(), (uint)1);

    ASSERT_STREQ(yml[0][0].to<std::string>().c_str(), "a");
    ASSERT_STREQ(yml[1][0].to<std::string>().c_str(), "a");

    ASSERT_EQ(yml[0].is_reference(), false);
    ASSERT_EQ(yml[1].is_reference(), true );
    
    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = sstd::terp::list(1);
    ans[0][0] = "a";
    ans[1] = &ans[0];

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case02){
    std::string s = R"(
- &rr
  - - a
  - b
  - c
- *rr
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);
//    sstd::printn_all(yml.size());

    //---

    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = sstd::terp::list(3);
    ans[0][0] = sstd::terp::list(1);
    ans[0][0][0] = "a";
    ans[0][1] = "b";
    ans[0][2] = "c";
    ans[1] = &ans[0];

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case03){
    std::string s = R"(
- &r a  x # anchor
- *r # alias
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = "a  x";
    ans[1] = &ans[0];

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case04){
    std::string s = R"(
- &r a
- [*r]
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
    //sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = "a";
    ans[1] = sstd::terp::list(1);
    ans[1][0] = &ans[0];

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case05_hash_key){
    std::string s = R"(
- &r a
- {*r}
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = "a";
    ans[1] = sstd::terp::hash();
    ans[1]["a"];

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case06_hash_value){
    std::string s = R"(
- &r a
- {key: *r}
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = "a";
    ans[1] = sstd::terp::hash();
    ans[1]["key"] = &ans[0];
//    sstd::printn_all(ans);

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case07a_list){
    std::string s = R"(
- &r [a, b, c]
- *r
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = sstd::terp::list(3);
    ans[0][0] = "a";
    ans[0][1] = "b";
    ans[0][2] = "c";
    ans[1] = &ans[0];
//    sstd::printn_all(ans);

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case07b_list){
    std::string s = R"(
- &r
  [a, b, c]
- *r
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = sstd::terp::list(3);
    ans[0][0] = "a";
    ans[0][1] = "b";
    ans[0][2] = "c";
    ans[1] = &ans[0];
    sstd::printn_all(ans);

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case08a_hash){
    std::string s = R"(
- &r {k: v}
- *r
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = sstd::terp::hash();
    ans[0]["k"] = "v";
    ans[1] = &ans[0];
//    sstd::printn_all(ans);

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case08b_hash){
    std::string s = R"(
- &r
  {k: v}
- *r
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = sstd::terp::hash();
    ans[0]["k"] = "v";
    ans[1] = &ans[0];
//    sstd::printn_all(ans);

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case09_hash){
    std::string s = R"(
h1: &h1
  k1: v1
h2: *h1
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["h1"] = sstd::terp::hash();
    ans["h1"]["k1"] = "v1";
    ans["h2"] = &ans["h1"];
//    sstd::printn_all(ans);

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case09b_hash){
    std::string s = R"(
h1:
  &h1
  k1: v1
h2: *h1
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["h1"] = sstd::terp::hash();
    ans["h1"]["k1"] = "v1";
    ans["h2"] = &ans["h1"];
//    sstd::printn_all(ans);

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case09b2_hash){
    std::string s = R"(
h1:
         &h1
  k1: v1
h2: *h1
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["h1"] = sstd::terp::hash();
    ans["h1"]["k1"] = "v1";
    ans["h2"] = &ans["h1"];
//    sstd::printn_all(ans);

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case09error01_hash){
    std::string s = R"(
h1: &h1
  &h2
  k1: v1
h2: *h2
)";
    sstd::terp::var yml;

    testing::internal::CaptureStdout();
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    std::string err_msg = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(sstd::strIn("Duplicated anchor (&) definition.", err_msg));
    
    ASSERT_FALSE(ret);
}
TEST(yaml, anchor_and_alias__case09error02_hash){
    std::string s = R"(
h1:
  &h2
  &h3
  k1: v1
h2: *h2
)";
    sstd::terp::var yml;

    testing::internal::CaptureStdout();
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    std::string err_msg = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(sstd::strIn("Duplicated anchor (&) definition.", err_msg));
    
    ASSERT_FALSE(ret);
}
TEST(yaml, anchor_and_alias__case09error03_hash){
    std::string s = R"(
h1: &h1
  &h2
  &h3
  k1: v1
h2: *h2
)";
    sstd::terp::var yml;

    testing::internal::CaptureStdout();
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    std::string err_msg = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(sstd::strIn("Duplicated anchor (&) definition.", err_msg));
    
    ASSERT_FALSE(ret);
}
TEST(yaml, anchor_and_alias__case09c_hash){
    std::string s = R"(
h1:

  &h1

  k1: v1
h2: *h1
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["h1"] = sstd::terp::hash();
    ans["h1"]["k1"] = "v1";
    ans["h2"] = &ans["h1"];
//    sstd::printn_all(ans);

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case09d_hash){
    std::string s = R"(
h1:

  &h1
  k1: v1

h2: *h1
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["h1"] = sstd::terp::hash();
    ans["h1"]["k1"] = "v1";
    ans["h2"] = &ans["h1"];
//    sstd::printn_all(ans);

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case09e_hash){
    std::string s = R"(
h1: &h1
  k1: v1
h2:
  *h1
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["h1"] = sstd::terp::hash();
    ans["h1"]["k1"] = "v1";
    ans["h2"] = &ans["h1"];
//    sstd::printn_all(ans);

    ASSERT_TRUE(yml == ans);
}

//---

TEST(yaml, anchor_and_alias__case10_hash_list){
    std::string s = R"(
h1:

  &h1_val

  - v1
h2: *h1_val
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["h1"] = sstd::terp::list(1);
    ans["h1"][0] = "v1";
    ans["h2"] = &ans["h1"];
//    sstd::printn_all(ans);

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case11_list){ // For more comfirmation of the case, "TEST(yaml, _str2token_multi_list_case10)".
    std::string s = R"(
- &a
 - a
- *a
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
//    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = sstd::terp::list(1);
    ans[0][0] = "a";
    ans[1] = &ans[0];
//    sstd::printn_all(ans);

    ASSERT_TRUE(yml == ans);
}
TEST(yaml, anchor_and_alias__case12_list_hash){
    std::string s = R"(
- h1: &h1
    k1: v1
    k2: v2
- h2: *h1
)";
    sstd::terp::var yml;
    bool ret = sstd::yaml_load(yml, s); // TEST THIS LINE
    ASSERT_TRUE(ret);
    sstd::printn_all(yml);

    //---

    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = sstd::terp::hash();
    ans[0]["h1"] = sstd::terp::hash();
    ans[0]["h1"]["k1"] = "v1";
    ans[0]["h1"]["k2"] = "v2";
    ans[1] = sstd::terp::hash();
    ans[1]["h2"] = &ans[0]["h1"];
    sstd::printn_all(ans);

    ASSERT_TRUE(yml == ans);
}

//---
/*
    std::string s = R"(
hx: &hx
  k1: v1
h2:
  <<: *hx
  k2: v2
)";
*/

//--
// TODO
/*
&h1_key h1: v1
h2: *h1_key
*/
/*
h1:
  &h1
  &k1 k1: v1
h2: *h1
h3: *k1
*/
/*
h1: &h1
  k1: v1
h2: &h2 // よく考えると、h1 を使えばよいだけでは？
  *h1
h3:
  *h2
*/
//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();

