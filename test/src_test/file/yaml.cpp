#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// tests of sub-functions

//---

TEST(yaml, _splitByLine_quotes_brackets_case01){
    
    std::vector<std::string> ret_v;
    std::string s = R"(
"abc
def"

"ghi"

)";
    bool ret_tf = sstd_yaml::_splitByLine_quotes_brackets(ret_v, s); // TEST THIS LINE
    //sstd::printn(ret_v);

    ASSERT_TRUE( ret_tf );
    ASSERT_TRUE( ret_v == std::vector<std::string>({
R"()",
R"("abc
def")",
R"()",
R"("ghi")",
R"()"}) );
}

TEST(yaml, _splitByLine_quotes_brackets_case02){
    
    std::vector<std::string> ret_v;
    std::string s = R"(
[a,
b,
c]

)";
    bool ret_tf = sstd_yaml::_splitByLine_quotes_brackets(ret_v, s); // TEST THIS LINE
    //sstd::printn(ret_v);

    ASSERT_TRUE( ret_tf );
    ASSERT_TRUE( ret_v == std::vector<std::string>({
R"()",
R"([a,
b,
c])",
R"()"}) );
}

TEST(yaml, _splitByLine_quotes_brackets_case03){
    
    std::vector<std::string> ret_v;
    std::string s = R"(
{
k:v
}

)";
    bool ret_tf = sstd_yaml::_splitByLine_quotes_brackets(ret_v, s); // TEST THIS LINE
    //sstd::printn(ret_v);

    ASSERT_TRUE( ret_tf );
    ASSERT_TRUE( ret_v == std::vector<std::string>({
R"()",
R"({
k:v
})",
R"()"}) );
}

TEST(yaml, _splitByLine_quotes_brackets_case04){
    
    std::vector<std::string> ret_v;
    std::string s = R"(
[[a,
b,
c,{k:
v}]]

)";
    bool ret_tf = sstd_yaml::_splitByLine_quotes_brackets(ret_v, s); // TEST THIS LINE
    //sstd::printn(ret_v);

    ASSERT_TRUE( ret_tf );
    ASSERT_TRUE( ret_v == std::vector<std::string>({
R"()",
R"([[a,
b,
c,{k:
v}]])",
R"()"}) );
}

//---

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

#define TEST_DATA_TYPE_AND_FORMAT(IS_STR, IS_LIST, IS_HASH, IS_FLOW, LIST_TYPE_COUNT, S_IN) \
    std::string s = S_IN;                                               \
    uint type=sstd_yaml::num_null, format=sstd_yaml::num_block_style_base, list_type_cnt=0; \
    bool ret = sstd_yaml::_data_type_and_format(type, format, list_type_cnt, s); \
    ASSERT_TRUE(ret);                                                   \
                                                                        \
    uint ans_type=sstd_yaml::num_str;                                   \
    if(IS_LIST){ ans_type += sstd_yaml::num_list; }                     \
    if(IS_HASH){ ans_type += sstd_yaml::num_hash; }                     \
    ASSERT_TRUE(type==ans_type);                                        \
                                                                        \
    uint ans_flow = IS_FLOW ? sstd_yaml::num_flow_style_base : sstd_yaml::num_block_style_base; \
    ASSERT_TRUE(format==ans_flow);                                      \
    ASSERT_TRUE(list_type_cnt==LIST_TYPE_COUNT);

TEST(yaml, _data_type_and_format_case01_01){ TEST_DATA_TYPE_AND_FORMAT( true, false, false, false, 0, "v"         ); }
TEST(yaml, _data_type_and_format_case02_01){ TEST_DATA_TYPE_AND_FORMAT(false,  true, false, false, 1, "- v"       ); }
TEST(yaml, _data_type_and_format_case03_01){ TEST_DATA_TYPE_AND_FORMAT(false, false,  true, false, 0, "k: v"      ); }
TEST(yaml, _data_type_and_format_case04_01){ TEST_DATA_TYPE_AND_FORMAT(false, false,  true, false, 0, "k[]: v[]"  ); }
TEST(yaml, _data_type_and_format_case05_01){ TEST_DATA_TYPE_AND_FORMAT(false, false,  true, false, 0, "k{}: v{}"  ); }
TEST(yaml, _data_type_and_format_case06_01){ TEST_DATA_TYPE_AND_FORMAT( true, false, false,  true, 0, "[]"        ); }
TEST(yaml, _data_type_and_format_case07_01){ TEST_DATA_TYPE_AND_FORMAT( true, false, false,  true, 0, "{}"        ); }
TEST(yaml, _data_type_and_format_case08_01){ TEST_DATA_TYPE_AND_FORMAT(false,  true, false,  true, 1, "- []"      ); }
TEST(yaml, _data_type_and_format_case09_01){ TEST_DATA_TYPE_AND_FORMAT(false,  true, false,  true, 1, "- {}"      ); }
TEST(yaml, _data_type_and_format_case10_01){ TEST_DATA_TYPE_AND_FORMAT(false,  true,  true, false, 1, "- k: v"    ); }
TEST(yaml, _data_type_and_format_case11_01){ TEST_DATA_TYPE_AND_FORMAT(false,  true,  true, false, 1, "- k[]: v[]"); }
TEST(yaml, _data_type_and_format_case12_01){ TEST_DATA_TYPE_AND_FORMAT(false,  true,  true, false, 1, "- k{}: v{}"); }
TEST(yaml, _data_type_and_format_case13_01){ TEST_DATA_TYPE_AND_FORMAT(false, false,  true,  true, 0, "k: []"     ); }
TEST(yaml, _data_type_and_format_case14_01){ TEST_DATA_TYPE_AND_FORMAT(false, false,  true,  true, 0, "k: {}"     ); }
TEST(yaml, _data_type_and_format_case15_01){ TEST_DATA_TYPE_AND_FORMAT( false, true,  true,  true, 1, "- k: []"   ); }
TEST(yaml, _data_type_and_format_case16_01){ TEST_DATA_TYPE_AND_FORMAT( false, true,  true,  true, 1, "- k: {}"   ); }

TEST(yaml, _data_type_and_format_case02_02){ TEST_DATA_TYPE_AND_FORMAT(false,  true, false, false, 3, "- - - v"   ); }
TEST(yaml, _data_type_and_format_case03_02){ TEST_DATA_TYPE_AND_FORMAT(false, false,  true, false, 0, "k : v"     ); }
TEST(yaml, _data_type_and_format_case04_02){ TEST_DATA_TYPE_AND_FORMAT(false, false,  true, false, 0, "k[: v["    ); }
//TEST(yaml, _data_type_and_format_case04_03){ TEST_DATA_TYPE_AND_FORMAT(false, false,  true, false, 0, "k [: v ["    ); }
TEST(yaml, _data_type_and_format_case05_02){ TEST_DATA_TYPE_AND_FORMAT(false, false,  true, false, 0, "k{: v{"    ); }
//TEST(yaml, _data_type_and_format_case05_03){ TEST_DATA_TYPE_AND_FORMAT(false, false,  true, false, 0, "k {: v {"    ); }
TEST(yaml, _data_type_and_format_case06_02){ TEST_DATA_TYPE_AND_FORMAT( true, false, false,  true, 0, "[{: }]"    ); } // Ex: [a, b, c, {k: v}]

//---
// Test _str2token() of data type and format

#define TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(IS_STR, IS_LIST, IS_HASH, IS_FLOW, LIST_TYPE_COUNT, S_IN) \
    std::string s = S_IN;                                               \
    std::vector<sstd_yaml::token> v_ret;                                \
    bool ret = sstd_yaml::_str2token(v_ret, s);                         \
    ASSERT_TRUE(ret);                                                   \
    ASSERT_EQ(v_ret.size(), 1);                                         \
                                                                        \
    uint ans_type=sstd_yaml::num_str;                                   \
    if(IS_LIST){ ans_type += sstd_yaml::num_list; }                     \
    if(IS_HASH){ ans_type += sstd_yaml::num_hash; }                     \
    ASSERT_EQ(v_ret[0].type, ans_type);                                 \
                                                                        \
    uint ans_flow = IS_FLOW ? sstd_yaml::num_flow_style_base : sstd_yaml::num_block_style_base; \
    ASSERT_EQ(v_ret[0].format, ans_flow);                               \
    ASSERT_EQ(v_ret[0].list_type_cnt, LIST_TYPE_COUNT);

TEST(yaml, _str2token__data_type_and_format_case01_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT( true, false, false, false, 0, "v"         ); }
TEST(yaml, _str2token__data_type_and_format_case02_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true, false, false, 1, "- v"       ); }
TEST(yaml, _str2token__data_type_and_format_case03_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false, false,  true, false, 0, "k: v"      ); }
TEST(yaml, _str2token__data_type_and_format_case04_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false, false,  true, false, 0, "k[]: v[]"  ); }
TEST(yaml, _str2token__data_type_and_format_case05_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false, false,  true, false, 0, "k{}: v{}"  ); }
TEST(yaml, _str2token__data_type_and_format_case06_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT( true, false, false,  true, 0, "[]"        ); }
TEST(yaml, _str2token__data_type_and_format_case07_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT( true, false, false,  true, 0, "{}"        ); }
TEST(yaml, _str2token__data_type_and_format_case08_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true, false,  true, 1, "- []"      ); }
TEST(yaml, _str2token__data_type_and_format_case09_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true, false,  true, 1, "- {}"      ); }
TEST(yaml, _str2token__data_type_and_format_case10_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true,  true, false, 1, "- k: v"    ); }
TEST(yaml, _str2token__data_type_and_format_case11_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true,  true, false, 1, "- k[]: v[]"); }
TEST(yaml, _str2token__data_type_and_format_case12_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true,  true, false, 1, "- k{}: v{}"); }
TEST(yaml, _str2token__data_type_and_format_case13_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false, false,  true,  true, 0, "k: []"     ); }
TEST(yaml, _str2token__data_type_and_format_case14_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false, false,  true,  true, 0, "k: {}"     ); }
TEST(yaml, _str2token__data_type_and_format_case15_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT( false, true,  true,  true, 1, "- k: []"   ); }
TEST(yaml, _str2token__data_type_and_format_case16_01){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT( false, true,  true,  true, 1, "- k: {}"   ); }

TEST(yaml, _str2token__data_type_and_format_case02_02){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false,  true, false, false, 3, "- - - v"   ); }
TEST(yaml, _str2token__data_type_and_format_case03_02){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false, false,  true, false, 0, "k : v"     ); }
TEST(yaml, _str2token__data_type_and_format_case04_02){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false, false,  true, false, 0, "k[: v["    ); }
TEST(yaml, _str2token__data_type_and_format_case04_03){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false, false,  true, false, 0, "k [: v ["  ); }
TEST(yaml, _str2token__data_type_and_format_case05_02){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false, false,  true, false, 0, "k{: v{"    ); }
TEST(yaml, _str2token__data_type_and_format_case05_03){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT(false, false,  true, false, 0, "k {: v {"  ); }
TEST(yaml, _str2token__data_type_and_format_case06_02){ TEST_STR2TOKEN__DATA_TYPE_AND_FORMAT( true, false, false,  true, 0, "[{: }]"    ); } // Ex: [a, b, c, {k: v}]

//---
// Test _str2token() of val1 and val2

#define TEST_STR2TOKEN__VAL1_VAL2(VAL1, VAL2, S_IN)     \
    std::string s = S_IN;                               \
    std::vector<sstd_yaml::token> v_ret;                \
    bool ret = sstd_yaml::_str2token(v_ret, s);         \
    sstd::printn(v_ret);                                \
    ASSERT_TRUE(ret);                                   \
    ASSERT_EQ(v_ret.size(), 1);                         \
    ASSERT_STREQ(v_ret[0].val1.c_str(), VAL1);          \
    ASSERT_STREQ(v_ret[0].val2.c_str(), VAL2);

TEST(yaml, _str2token_val1_val2_list                    ){ TEST_STR2TOKEN__VAL1_VAL2("a", "", "- a"); }
TEST(yaml, _str2token_val1_val2_list_02                 ){ TEST_STR2TOKEN__VAL1_VAL2("a   ,", "", "- a   ,"); }
TEST(yaml, _str2token_val1_val2_list_hash               ){ TEST_STR2TOKEN__VAL1_VAL2("k", "v", "k: v"); }
TEST(yaml, _str2token_val1_val2_list_hash_02            ){ TEST_STR2TOKEN__VAL1_VAL2("k ,", "v   ,", "- k , : v   ,"); }
TEST(yaml, _str2token_val1_val2_list_hash_space         ){ TEST_STR2TOKEN__VAL1_VAL2("k {", "v {", "-  k { :  v { "); }
TEST(yaml, _str2token_val1_val2_flow                    ){ TEST_STR2TOKEN__VAL1_VAL2("[{k: v}]", "",   "[{k: v}]"); }

// mutliline flow stype notation
TEST(yaml, _str2token_val1_val2_multiline_flow          ){ TEST_STR2TOKEN__VAL1_VAL2("[\na,\nb,\nc\n]", "",   "[\na,\nb,\nc\n]"); }
TEST(yaml, _str2token_val1_val2_multiline_flow_list     ){ TEST_STR2TOKEN__VAL1_VAL2("[\na,\nb,\nc\n]", "", "- [\na,\nb,\nc\n]"); }
TEST(yaml, _str2token_val1_val2_multiline_flow_hash     ){ TEST_STR2TOKEN__VAL1_VAL2("k", "[\na,\nb,\nc\n]",   "k: [\na,\nb,\nc\n]"); }
TEST(yaml, _str2token_val1_val2_multiline_flow_list_hash){ TEST_STR2TOKEN__VAL1_VAL2("k", "[\na,\nb,\nc\n]", "- k: [\na,\nb,\nc\n]"); }

// mutliline YAML notation
TEST(yaml, _str2token_val1_val2_multiline_list     ){ TEST_STR2TOKEN__VAL1_VAL2("|+123\na\nb\nc",  "", "- |+123\na\nb\nc"); }
TEST(yaml, _str2token_val1_val2_multiline_hash     ){ TEST_STR2TOKEN__VAL1_VAL2("k", "|+123\na\nb\nc",   "k: |+123\na\nb\nc"); }
TEST(yaml, _str2token_val1_val2_multiline_list_hash){ TEST_STR2TOKEN__VAL1_VAL2("k", "|+123\na\nb\nc", "- k: |+123\na\nb\nc"); }

//---
// Test _str2token() of remove comments

// remove comments
TEST(yaml, _str2token_rm_comment_case01){ TEST_STR2TOKEN__VAL1_VAL2("a", "", "a # comment"); }
TEST(yaml, _str2token_rm_comment_case02){ TEST_STR2TOKEN__VAL1_VAL2("\"a # comment\"", "", "\"a # comment\""); }
TEST(yaml, _str2token_rm_comment_case03){ TEST_STR2TOKEN__VAL1_VAL2("|\na\nb\nc", "", "- |\na # comment\nb # comment\nc # comment"); }

//---

TEST(yaml, _str2token_multi_list_case01){
    std::string s = "- a\n- b\n- c";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
    sstd::printn(v_ret);
}
TEST(yaml, _str2token_multi_list_case02){
    std::string s = "- \"\"\n- \"\"\n- \"\"";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
    sstd::printn(v_ret);
}
TEST(yaml, _str2token_multi_list_case03){
    std::string s = "-\n  - a";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
    sstd::printn(v_ret);
}
TEST(yaml, _str2token_multi_list_case04){
    std::string s = "- \n  - a";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
    sstd::printn(v_ret);
}

//---

TEST(yaml, _str2token_multi_list_case05){
    std::string s = "- [{\nk11: v11,\nk12:v12,\nk13:v13\n}]\n- [{\nk21: v21,\nk22:v22,\nk23:v23\n}]";
    std::vector<sstd_yaml::token> v_ret;
    bool ret = sstd_yaml::_str2token(v_ret, s);
    sstd::printn(v_ret);

    ASSERT_EQ(v_ret.size(), 2);
}

//*/

//-----------------------------------------------------------------------------------------------------------------------------------------------
// comments
/*
TEST(yaml, comments_str){
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
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k"] = "v";
    
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
    ans["k"] = "v";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// var

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
    std::string s=R"(
a # comment
b
)";
    testing::internal::CaptureStdout();
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    std::string ret = testing::internal::GetCapturedStdout().c_str();
    ASSERT_TRUE(sstd::strIn("OverWritting the existing data. (String data type can only take one data.)", ret.c_str()));
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = "a";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// list

TEST(yaml, list_depth1){
    std::string s=R"(
- a # comment
- b

- c
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
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(4);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = sstd::terp::list(2);
    ans[2][0] = "c";
    ans[2][1] = "d";
    ans[3] = "e";
    
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

//-----------------------------------------------------------------------------------------------------------------------------------------------
// hash

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
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "v1";
    ans["k2"] = "v2";
    ans["k3"] = sstd::terp::hash();
    ans["k3"]["k31"] = "v31";
    ans["k3"]["k32"] = "v32";
    ans["k4"] = "v4";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---
// Corner case(s)

TEST(yaml, hash_null){
    std::string s=R"(
k1:
)";
    sstd::terp::var yml; bool ret_tf = sstd::yaml_load(yml, s); // TEST THIS LINE
    //sstd::printn(yml);
    ASSERT_TRUE(ret_tf);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"];
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
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

//-----------------------------------------------------------------------------------------------------------------------------------------------
// list and hash

TEST(yaml, list_and_hash__NUM_LIST_AND_HASH){
    std::string s=R"(
- k1: v1
)";
    sstd::terp::var yml; bool ret_tf = sstd::yaml_load(yml, s); // TEST THIS LINE
    //sstd::printn(yml);
    ASSERT_TRUE(ret_tf);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::hash();
    ans[0]["k1"] = "v1";
    //sstd::printn(ans);
    
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

//-----------------------------------------------------------------------------------------------------------------------------------------------
// complex test cases

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
    //sstd::printn(yml);
    
    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = sstd::terp::hash();
    ans[0]["k1"] = "v1";
    ans[1] = sstd::terp::hash();
    ans[1]["k2"] = "v2";
    
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
- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);
    
    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(4);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = sstd::terp::hash();
    ans[2]["k1"] = "v1";
    ans[2]["k2"] = "v2";
    ans[3] = "c";
    
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
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "v1";
    ans["k2"] = "v2";
    ans["k3"] = sstd::terp::list(2);
    ans["k3"][0] = "v31";
    ans["k3"][1] = "v32";
    ans["k4"] = "v4";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, list_hash_list){ // depth3
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
    //sstd::printn(yml);
    
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
    //sstd::printn(ans);
    
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
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

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
    //sstd::printn(ans);
    
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
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

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
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

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
    //sstd::printn(yml);

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
    //sstd::printn(yml);

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

// TEST(yaml, multi_line_str_by_list_greater_minus_num_2){ // - >-2
// }

// TEST(yaml, multi_line_str_by_list_greater_plus_num_1){ // - >-1
// }

// TEST(yaml, multi_line_str_by_list_greater_plus_num_2){ // - >-2
// }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Multi line string for hash

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
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans=R"(a: b c"
def g)";
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

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Complicated test

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

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Multipul list indication

TEST(yaml, multipul_list_indication_case01){
    std::string s=R"(
- - a
#- 
#  - a
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::list(1);
    ans[0][0] = "a";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, multipul_list_indication_case02){
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
TEST(yaml, multipul_list_indication_case03){
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
TEST(yaml, multipul_list_indication_case04){
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
TEST(yaml, multipul_list_indication_case05){
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
TEST(yaml, multipul_list_indication_case06){
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

//-----------------------------------------------------------------------------------------------------------------------------------------------
// flow style notation

//---

TEST(yaml, block_list_and_flow_list){
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
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

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
    //sstd::printn(ans);

    //---
    
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
//*
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
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// End marker ...

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

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Split file ---

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

//-----------------------------------------------------------------------------------------------------------------------------------------------
//*/
EXECUTE_TESTS();
