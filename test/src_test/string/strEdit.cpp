#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(strEdit, theOthers){
    SET_TMP_DIR_NAME();
    sstd::mkdir(tmpDir);
    printf("■ strEdit\n");
    printf("  □ readA_bin\n");
    std::vector<uint8> raw = sstd::read_bin("./test/src_test/test.png");
    sstd::printn_all(raw.size());
    printf("  □ write_bin\n");
    if(!sstd::write_bin(tmpDir+"/test__write_bin_char.png",             raw)){ sstd::pdbg_err("sstd::write_bin()\n"); }
    if(!sstd::write_bin(std::string(tmpDir+"/test__write_bin_str.png"), raw)){ sstd::pdbg_err("sstd::write_bin()\n"); }
    
    printf("  □ read_withoutBOM & splitByLine\n");
//    std::string str_tI = sstd::read_withoutBOM(R"(./test/tinyInterpreter.txt)");
    std::string str_tI = sstd::read_withoutBOM(std::string(R"(./test/src_test/file/tinyInterpreter.txt)"));
    std::vector<std::string> splitLList = sstd::splitByLine(str_tI);
    printf("\n");
    printf("  ./test/src_test/tinyInterpreter.txt\n");
    printf("+----+---------------------------------------------------------------------+\n");
    for(uint i=0; i<splitLList.size(); ++i){
        printf("| %2d | %-67s |\n", i, splitLList[i].c_str());
    }
    printf("+----+---------------------------------------------------------------------+\n");
    printf("\n");
    sstd::rm(tmpDir);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(strEdit, extract_quoted){
    std::vector<std::string> ret_vs;
    std::string s = R"(

abcdef
"AB
CD"

'ghi'

)";
    std::vector<std::string> ans_vs = {"AB\nCD", "ghi"};
    bool ret_tf = sstd::extract_quoted(ret_vs, s); // TEST THIS LINE
    //sstd::printn(ret_tf);
    //sstd::printn(ret_vs);

    ASSERT_TRUE( ret_tf );
    ASSERT_TRUE( ret_vs == ans_vs );
}
TEST(strEdit, extract_quoted_escaped){
    std::vector<std::string> ret_vs;
    std::string s = R"(

abcdef
\"AB
CD\"

\'ghi\'

)";
    std::vector<std::string> ans_vs;
    bool ret_tf = sstd::extract_quoted(ret_vs, s); // TEST THIS LINE
    //sstd::printn(ret_tf);
    //sstd::printn(ret_vs);

    ASSERT_TRUE( ret_tf );
    ASSERT_TRUE( ret_vs == ans_vs );
}
TEST(strEdit, extract_quoted__false_unclosed_double_quate){
    std::vector<std::string> ret_vs;
    std::string s = R"( "ABCD )";
    std::vector<std::string> ans_vs;
    bool ret_tf = sstd::extract_quoted(ret_vs, s); // TEST THIS LINE
    //sstd::printn(ret_tf);
    //sstd::printn(ret_vs);

    ASSERT_FALSE( ret_tf );
}
TEST(strEdit, extract_quoted__false_unclosed_single_quate){
    std::vector<std::string> ret_vs;
    std::string s = R"( 'ABCD )";
    std::vector<std::string> ans_vs;
    bool ret_tf = sstd::extract_quoted(ret_vs, s); // TEST THIS LINE
    //sstd::printn(ret_tf);
    //sstd::printn(ret_vs);

    ASSERT_FALSE( ret_tf );
}

//---

TEST(strEdit, extract_unquoted){
    std::string ret_s;
    std::string s = R"(

abcdef
"AB
CD"

'ghi'

)";
    std::string ans_s = R"(

abcdef




)";
    bool ret_tf = sstd::extract_unquoted(ret_s, s); // TEST THIS LINE
    //sstd::printn(ret_tf);
    //sstd::printn(ret_s);

    ASSERT_TRUE( ret_tf );
    ASSERT_STREQ(ret_s.c_str(), ans_s.c_str());
}
TEST(strEdit, extract_unquoted_escaped){
    std::string ret_s;
    std::string s = R"(

abcdef
\"AB
CD\"

\'ghi\'

)";
    std::string ans_s = R"(

abcdef
\"AB
CD\"

\'ghi\'

)";
    bool ret_tf = sstd::extract_unquoted(ret_s, s); // TEST THIS LINE
    //sstd::printn(ret_tf);
    //sstd::printn(ret_s);

    ASSERT_TRUE( ret_tf );
    ASSERT_STREQ(ret_s.c_str(), ans_s.c_str());
}
TEST(strEdit, extract_unquoted__false){
    std::string ret_s;
    std::string s = R"( "ABCD )";
    std::string ans_s;
    bool ret_tf = sstd::extract_unquoted(ret_s, s); // TEST THIS LINE
    //sstd::printn(ret_tf);
    //sstd::printn(ret_s);

    ASSERT_FALSE( ret_tf );
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

//splitByLine

//TEST(strEdit, splitByLine){}

TEST(strEdit, splitByLine_quotes){
    
    std::vector<std::string> ret_v;
    std::string s = R"(
"abc
def"

"ghi"

)";
    bool ret_tf = sstd::splitByLine_quotes(ret_v, s); // TEST THIS LINE
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

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define TEST_SPLIT_CS(S_IN, ...)                                        \
    std::vector<std::string> ret_v = sstd::split(S_IN); /* TEST THIS LINE */ \
    /* sstd::printn(ret_v); */                                          \
    ASSERT_TRUE(ret_v == std::vector<std::string>({__VA_ARGS__}) );

TEST(strEdit, split_c_0){ TEST_SPLIT_CS(" a  b, c", "a", "b,", "c"); }
TEST(strEdit, split_c_1){ TEST_SPLIT_CS(" a  b, c ", "a", "b,", "c"); }
TEST(strEdit, split_c_2){ TEST_SPLIT_CS("  a  b, c  ", "a", "b,", "c"); }
TEST(strEdit, split_s){ TEST_SPLIT_CS(std::string(" a  b, c"), "a", "b,", "c"); }

#undef TEST_SPLIT_CS

//---

#define TEST_SPLIT_CS_X(X_IN, S_IN, ...)                                 \
    std::vector<std::string> ret_v = sstd::split(S_IN, X_IN); /* TEST THIS LINE */ \
    /* sstd::printn(ret_v); */                                          \
    ASSERT_TRUE(ret_v == std::vector<std::string>({__VA_ARGS__}) );

TEST(strEdit, split_c_c_space_0){ TEST_SPLIT_CS_X(' ', "a  b, c", "a", "", "b,", "c"); }
TEST(strEdit, split_c_c_space_1){ TEST_SPLIT_CS_X(' ', " a  b, c ", "", "a", "", "b,", "c", ""); }
TEST(strEdit, split_c_c_space_2){ TEST_SPLIT_CS_X(' ', "  a  b, c  ", "", "", "a", "", "b,", "c", "", ""); }
TEST(strEdit, split_c_c_comma){ TEST_SPLIT_CS_X(',', " a  b, c", " a  b", " c"); }

TEST(strEdit, split_s_c){ TEST_SPLIT_CS_X(' ', std::string(" a  b, c"), "", "a", "", "b,", "c"); }

#undef TEST_SPLIT_CS_X

//---

#define TEST_SPLIT_SS_X(X_IN, S_IN, ...)                                 \
    std::vector<std::string> ret_v = sstd::split(S_IN, X_IN); /* TEST THIS LINE */ \
    /* sstd::printn(ret_v); */                                          \
    ASSERT_TRUE(ret_v == std::vector<std::string>({__VA_ARGS__}) );

TEST(strEdit, split_s_s_space_1_0){ TEST_SPLIT_SS_X(",", "a,b,c", "a", "b", "c"); }

TEST(strEdit, split_s_s_space_m_0){ TEST_SPLIT_SS_X("xxx", "123abcabs456", "123abcabs456"); }
TEST(strEdit, split_s_s_space_m_1){ TEST_SPLIT_SS_X("abc", "123abcabs456", "123", "abs456"); }
TEST(strEdit, split_s_s_space_m_2a){ TEST_SPLIT_SS_X("abc", "123abc456abc789", "123", "456", "789"); }
TEST(strEdit, split_s_s_space_m_2b){ TEST_SPLIT_SS_X("abc", "123abc456abc789abc", "123", "456", "789", ""); }

TEST(strEdit, split_s_s){ TEST_SPLIT_SS_X(std::string("abc"), std::string("123abc456abc789"), std::string("123"), std::string("456"), std::string("789")); }

#undef TEST_SPLIT_SS_X

//---

#define TEST_SPLIT_RMSPACE_CS(S_IN, ...)                                \
    std::vector<std::string> ret_v = sstd::split_rmSpace(S_IN); /* TEST THIS LINE */ \
    /* sstd::printn(ret_v); */                                          \
    ASSERT_TRUE(ret_v == std::vector<std::string>({__VA_ARGS__}) );

TEST(strEdit, split_rmSpace_c){ TEST_SPLIT_RMSPACE_CS(" a  b, c", "a", "b,", "c"); }
TEST(strEdit, split_rmSpace_s){ TEST_SPLIT_RMSPACE_CS(std::string(" a  b, c"), "a", "b,", "c"); }

#undef TEST_SPLIT_RMSPACE_CS

//---

#define TEST_SPLIT_RMSPACE_CS_X(X_IN, S_IN, ...)                        \
    std::vector<std::string> ret_v = sstd::split_rmSpace(S_IN, X_IN); /* TEST THIS LINE */ \
    /* sstd::printn(ret_v); */                                          \
    ASSERT_TRUE(ret_v == std::vector<std::string>({__VA_ARGS__}) );

TEST(strEdit, split_rmSpace_c_c_space){ TEST_SPLIT_RMSPACE_CS_X(' ', " a  b, c", "a", "b,", "c"); }
TEST(strEdit, split_rmSpace_c_c_comma){ TEST_SPLIT_RMSPACE_CS_X(',', " a  b, c", "a  b", "c"); }
TEST(strEdit, split_rmSpace_s_c_space){ TEST_SPLIT_RMSPACE_CS_X(' ', std::string(" a  b, c"), "a", "b,", "c"); }

#undef TEST_SPLIT_RMSPACE_CS_X

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define TEST_SPLIT_QUOTES_VS_CS(RESULT, S_IN, ...)                      \
    bool ret_tf;                                                        \
    std::vector<std::string> ret_v;                                     \
    ret_tf = sstd::split_quotes(ret_v, S_IN); /* TEST THIS LINE */      \
    /* sstd::printn(ret_v); */                                          \
                                                                        \
    ASSERT_TRUE(ret_tf == RESULT);                                      \
    ASSERT_TRUE(ret_v == std::vector<std::string>({__VA_ARGS__}) );

TEST(strEdit, split_quotes_vs_s){ TEST_SPLIT_QUOTES_VS_CS(true, std::string("a  b  c d"), "a", "b", "c", "d"); }

TEST(strEdit, split_quotes_vs_c__case_true_space_0){ TEST_SPLIT_QUOTES_VS_CS(true, "a  b  c d", "a", "b", "c", "d"); }
TEST(strEdit, split_quotes_vs_c__case_true_space_1){ TEST_SPLIT_QUOTES_VS_CS(true, " a  b  c d ", "a", "b", "c", "d"); }
TEST(strEdit, split_quotes_vs_c__case_true_space_2){ TEST_SPLIT_QUOTES_VS_CS(true, "  a  b  c d  ", "a", "b", "c", "d"); }

#undef TEST_SPLIT_QUOTES_VS_CS

//---

#define TEST_SPLIT_QUOTES_VS_CS_X(RESULT, X_IN, S_IN, ...)              \
    bool ret_tf;                                                        \
    std::vector<std::string> ret_v;                                     \
    ret_tf = sstd::split_quotes(ret_v, S_IN, X_IN); /* TEST THIS LINE */ \
    /* sstd::printn(ret_v); */                                          \
                                                                        \
    ASSERT_TRUE(ret_tf == RESULT);                                      \
    ASSERT_TRUE(ret_v == std::vector<std::string>({__VA_ARGS__}) );

TEST(strEdit, split_quotes_vs_c_s){ TEST_SPLIT_QUOTES_VS_CS_X(true, ' ', std::string("a  b  c d"), "a", "", "b", "", "c", "d"); }

//TEST(strEdit, split_quotes_vs_c_x__case_true_null){ TEST_SPLIT_QUOTES_VS_CS_X(true, ' ', "", ""); } // for compatible with Python split()

TEST(strEdit, split_quotes_vs_c_x__case_true_space_0){ TEST_SPLIT_QUOTES_VS_CS_X(true, ' ', "a  b  c d", "a", "", "b", "", "c", "d"); }
TEST(strEdit, split_quotes_vs_c_x__case_true_space_1){ TEST_SPLIT_QUOTES_VS_CS_X(true, ' ', " a  b  c d ", "", "a", "", "b", "", "c", "d", ""); }
TEST(strEdit, split_quotes_vs_c_x__case_true_space_2){ TEST_SPLIT_QUOTES_VS_CS_X(true, ' ', "  a  b  c d  ", "", "", "a", "", "b", "", "c", "d", "", ""); }

//TEST(strEdit, split_quotes_vs_c_x__case_true_0){ TEST_SPLIT_QUOTES_VS_CS_X(true, ':', "", ""); } // for compatible with Python split()
TEST(strEdit, split_quotes_vs_c_x__case_true_1){ TEST_SPLIT_QUOTES_VS_CS_X(true, ':', " abc ", " abc "); }
TEST(strEdit, split_quotes_vs_c_x__case_true_2){ TEST_SPLIT_QUOTES_VS_CS_X(true, ':', " abc : def ", " abc ", " def "); }
TEST(strEdit, split_quotes_vs_c_x__case_true_3){ TEST_SPLIT_QUOTES_VS_CS_X(true, ':', " abc : def : ghi ", " abc ", " def ", " ghi "); }

TEST(strEdit, split_quotes_vs_c_x__case_true_sq){ TEST_SPLIT_QUOTES_VS_CS_X(true, ':', "' a:b:c ':' d:ef ':' gh:i '", "' a:b:c '", "' d:ef '", "' gh:i '"); }
TEST(strEdit, split_quotes_vs_c_x__case_true_dq){ TEST_SPLIT_QUOTES_VS_CS_X(true, ':', R"(" a:b:c ":" d:ef ":" gh:i ")", R"(" a:b:c ")", R"(" d:ef ")", R"(" gh:i ")"); }

TEST(strEdit, split_quotes_vs_c_x__case_false_sq_01){ TEST_SPLIT_QUOTES_VS_CS_X(false, ':', R"(' a:b:c : d:ef )"); }
TEST(strEdit, split_quotes_vs_c_x__case_false_sq_02){ TEST_SPLIT_QUOTES_VS_CS_X(false, ':', R"( a:b:c : d:ef ')"); }
TEST(strEdit, split_quotes_vs_c_x__case_false_dq_01){ TEST_SPLIT_QUOTES_VS_CS_X(false, ':', R"(" a:b:c : d:ef )"); }
TEST(strEdit, split_quotes_vs_c_x__case_false_dq_02){ TEST_SPLIT_QUOTES_VS_CS_X(false, ':', R"( a:b:c : d:ef ")"); }

#undef TEST_SPLIT_QUOTES_VS_CS_X

//---

#define TEST_SPLIT_QUOTES_VS_CS_XCS(RESULT, X_IN, S_IN, ...)            \
    bool ret_tf;                                                        \
    std::vector<std::string> ret_v;                                     \
    ret_tf = sstd::split_quotes(ret_v, S_IN, X_IN); /* TEST THIS LINE */ \
    /* sstd::printn(ret_v); */                                          \
                                                                        \
    ASSERT_TRUE(ret_tf == RESULT);                                      \
    ASSERT_TRUE(ret_v == std::vector<std::string>({__VA_ARGS__}) );

TEST(strEdit, split_quotes_vs_c_s_xc){ std::vector<std::string> ret_v; sstd::split_quotes(ret_v, "", ""); }
TEST(strEdit, split_quotes_vs_c_s_xs){ std::vector<std::string> ret_v; sstd::split_quotes(ret_v, "", ""); }
TEST(strEdit, split_quotes_vs_c_s_xcs_00){ TEST_SPLIT_QUOTES_VS_CS_XCS(true, " ", "a  b  c d", "a", "", "b", "", "c", "d"); }
TEST(strEdit, split_quotes_vs_c_s_xcs_01){ TEST_SPLIT_QUOTES_VS_CS_XCS(true, ": ", "k:1:2: v:1:2:", "k:1:2", "v:1:2:"); }
TEST(strEdit, split_quotes_vs_c_s_xcs_02){ TEST_SPLIT_QUOTES_VS_CS_XCS(true, ": ", ": k:1:2: v:1:2: ", "", "k:1:2", "v:1:2", ""); }
TEST(strEdit, split_quotes_vs_c_s_xcs_03){ TEST_SPLIT_QUOTES_VS_CS_XCS(true, ": ", ": : k:1:2: v:1:2: : ", "", "", "k:1:2", "v:1:2", "", ""); }

#undef TEST_SPLIT_QUOTES_VS_CS_XCS

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(strEdit, lstrip){
    std::string str_in  = " \t abcd \t ";
    std::string str_ans =     "abcd \t ";
    ASSERT_TRUE(sstd::lstrip(str_in.c_str()) == str_ans);
    ASSERT_TRUE(sstd::lstrip(str_in        ) == str_ans);
}
TEST(strEdit, lstrip_ow){
    std::string str_in  = " \t abcd \t ";
    std::string str_ans =     "abcd \t ";
    sstd::lstrip_ow(str_in);
    ASSERT_TRUE(str_in == str_ans);
}
TEST(strEdit, rstrip){
    std::string str_in  = " \t abcd \t ";
    std::string str_ans = " \t abcd";
    ASSERT_TRUE(sstd::rstrip(str_in.c_str()) == str_ans);
    ASSERT_TRUE(sstd::rstrip(str_in        ) == str_ans);
}
TEST(strEdit, rstrip_ow){
    std::string str_in  = " \t abcd \t ";
    std::string str_ans = " \t abcd";
    sstd::rstrip_ow(str_in);
    ASSERT_TRUE(str_in == str_ans);
}
TEST(strEdit, strip){
    std::string str_in  = " \t abcd \t ";
    std::string str_ans = "abcd";
    ASSERT_TRUE(sstd::strip(str_in.c_str()) == str_ans);
    ASSERT_TRUE(sstd::strip(str_in        ) == str_ans);
}
TEST(strEdit, strip_vec){
    std::vector<std::string> vecStr_in  = {" \t abcd01 \t ", " \t abcd02 \t ", " \t abcd03 \t "};
    std::vector<std::string> vecStr_ans = {"abcd01", "abcd02", "abcd03"};
    ASSERT_TRUE(sstd::strip(vecStr_in) == vecStr_ans);
}
TEST(strEdit, strip_ow){
    std::string str_in  = " \t abcd \t ";
    std::string str_ans = "abcd";
    sstd::strip_ow(str_in);
    ASSERT_TRUE(str_in == str_ans);
}
TEST(strEdit, strip_vec_ow){
    std::vector<std::string> vecStr_in  = {" \t abcd01 \t ", " \t abcd02 \t ", " \t abcd03 \t "};
    std::vector<std::string> vecStr_ans = {"abcd01", "abcd02", "abcd03"};
    sstd::strip_ow(vecStr_in);
    ASSERT_TRUE(vecStr_in == vecStr_ans);
}


//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(strEdit, lstrip_c_cc){
    std::string str_in  = "  abcd  ";
    std::string str_ans =   "abcd  ";
    std::string ret = sstd::lstrip(str_in.c_str(), ' ');
    ASSERT_STREQ(ret.c_str(), str_ans.c_str());
}
TEST(strEdit, lstrip_c_sc){
    std::string str_in  = "  abcd  ";
    std::string str_ans =   "abcd  ";
    std::string ret = sstd::lstrip(str_in, ' ');
    ASSERT_STREQ(ret.c_str(), str_ans.c_str());
}
TEST(strEdit, lstrip_c_sc_02){
    std::string str_in  = "  ";
    std::string str_ans = "";
    std::string ret = sstd::lstrip(str_in, ' ');
    ASSERT_STREQ(ret.c_str(), str_ans.c_str());
}
TEST(strEdit, lstrip_c_sc_03){
    std::string str_in  = "";
    std::string str_ans = "";
    std::string ret = sstd::lstrip(str_in, ' ');
    ASSERT_STREQ(ret.c_str(), str_ans.c_str());
}
TEST(strEdit, lstrip_vec_01){
    std::vector<std::string> v = {" a ", " b ", "c", ""};
    std::vector<std::string> v_ans = {"a ", "b ", "c", ""};
    ASSERT_TRUE(sstd::lstrip(v)==v_ans);
}

TEST(strEdit, lstrip_ow_c){
    std::string str_in  = "  abcd  ";
    std::string str_ans =   "abcd  ";
    sstd::lstrip_ow(str_in, ' ');
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, lstrip_ow_c_02){
    std::string str_in  = "  ";
    std::string str_ans = "";
    sstd::lstrip_ow(str_in, ' ');
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, lstrip_ow_vec_01){
    std::vector<std::string> v = {" a ", " b ", "c", ""};
    std::vector<std::string> v_ans = {"a ", "b ", "c", ""};
    sstd::lstrip_ow(v);
    ASSERT_TRUE(v==v_ans);
}

//---

TEST(strEdit, rstrip_c_cc){
    std::string str_in  = "  abcd  ";
    std::string str_ans = "  abcd";
    std::string ret = sstd::rstrip(str_in.c_str(), ' ');
    ASSERT_STREQ(ret.c_str(), str_ans.c_str());
}
TEST(strEdit, rstrip_c_sc){
    std::string str_in  = "  abcd  ";
    std::string str_ans = "  abcd";
    std::string ret = sstd::rstrip(str_in, ' ');
    ASSERT_STREQ(ret.c_str(), str_ans.c_str());
}
TEST(strEdit, rstrip_c_sc_02){
    std::string str_in  = "  ";
    std::string str_ans = "";
    std::string ret = sstd::rstrip(str_in, ' ');
    ASSERT_STREQ(ret.c_str(), str_ans.c_str());
}
TEST(strEdit, rstrip_c_sc_03){
    std::string str_in  = "";
    std::string str_ans = "";
    std::string ret = sstd::rstrip(str_in, ' ');
    ASSERT_STREQ(ret.c_str(), str_ans.c_str());
}
TEST(strEdit, rstrip_vec_01){
    std::vector<std::string> v = {" a ", " b ", "c", ""};
    std::vector<std::string> v_ans = {" a", " b", "c", ""};
    ASSERT_TRUE(sstd::rstrip(v)==v_ans);
}

TEST(strEdit, rstrip_ow_c){
    std::string str_in  = "  abcd  ";
    std::string str_ans = "  abcd";
    sstd::rstrip_ow(str_in, ' ');
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, rstrip_ow_c_02){
    std::string str_in  = "  ";
    std::string str_ans = "";
    sstd::rstrip_ow(str_in, ' ');
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, rstrip_ow_vec_01){
    std::vector<std::string> v = {" a ", " b ", "c", ""};
    std::vector<std::string> v_ans = {" a", " b", "c", ""};
    sstd::rstrip_ow(v);
    ASSERT_TRUE(v==v_ans);
}

//---

TEST(strEdit, strip_c_cc){
    std::string str_in  = "  abcd  ";
    std::string str_ans = "abcd";
    std::string ret = sstd::strip(str_in.c_str(), ' ');
    ASSERT_STREQ(ret.c_str(), str_ans.c_str());
}
TEST(strEdit, strip_c_cc_02){
    std::string str_in  = "   ";
    std::string str_ans = "";
    std::string ret = sstd::strip(str_in.c_str(), ' ');
    ASSERT_STREQ(ret.c_str(), str_ans.c_str());
}
TEST(strEdit, strip_c_cc_03){
    std::string str_in  = "";
    std::string str_ans = "";
    std::string ret = sstd::strip(str_in.c_str(), ' ');
    ASSERT_STREQ(ret.c_str(), str_ans.c_str());
}
TEST(strEdit, strip_c_sc){
    std::string str_in  = "  abcd  ";
    std::string str_ans = "abcd";
    std::string ret = sstd::strip(str_in, ' ');
    ASSERT_STREQ(ret.c_str(), str_ans.c_str());
}

TEST(strEdit, strip_ow_c_sc){
    std::string str_in  = "  abcd  ";
    std::string str_ans = "abcd";
    sstd::strip_ow(str_in, ' ');
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, strip_ow_c_sc_02){
    std::string str_in  = "    ";
    std::string str_ans = "";
    sstd::strip_ow(str_in, ' ');
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, strip_ow_c_sc_03){
    std::string str_in  = "";
    std::string str_ans = "";
    sstd::strip_ow(str_in, ' ');
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(strEdit, stripAllc_cc_01){
    std::string str_in  = "0a0b0cx0d0xe0f0g0";
    std::string str_ans = "abcxdxefg";
    std::string ret = sstd::stripAll(str_in.c_str(), '0');
    ASSERT_STREQ(ret.c_str(), str_ans.c_str());
}
TEST(strEdit, stripAllc_cc_02){
    std::string str_in  = "0a0b0cx0d0xe0f0g0";
    std::string str_ans = "abcdefg";
    std::string ret;
    ret = sstd::stripAll(str_in.c_str(), '0');
    ret = sstd::stripAll(   ret.c_str(), 'x');
    ASSERT_STREQ(ret.c_str(), str_ans.c_str());
}
TEST(strEdit, stripAllc_sc){
    std::string str_in  = "0a0b0cx0d0xe0f0g0";
    std::string str_ans = "abcxdxefg";
    std::string ret = sstd::stripAll(str_in, '0');
    ASSERT_STREQ(ret.c_str(), str_ans.c_str());
}

TEST(strEdit, stripAllc_ow_sc){
    std::string str_in  = "0a0b0cx0d0xe0f0g0";
    std::string str_ans = "abcxdxefg";
    sstd::stripAll_ow(str_in, '0');
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(strEdit, stripAll_case01_01){
    std::string str_in  = "0a0b0cx0d0xe0f0g0";
    std::string str_ans = "abcdefg";
    std::string ret = sstd::stripAll(str_in.c_str(), "x0");
    ASSERT_TRUE(ret == str_ans);
}
TEST(strEdit, stripAll_case01_02){
    std::string str_in  = "\r\nabc\r\n\r\ndefg\r\n";
    std::string str_ans = "abcdefg";
    std::string ret = sstd::stripAll(str_in.c_str(), "\r\n");
    ASSERT_TRUE(ret == str_ans);
}
TEST(strEdit, stripAll_case02){
    std::string str_in  = "0a0b0cx0d0xe0f0g00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x";
    std::string str_ans = "abcdefg";
    std::string ret = sstd::stripAll(str_in.c_str(), "x0");
    ASSERT_TRUE(ret == str_ans);
}

#define strEdit_stripAll_check_io(LHS, RHS)                     \
    std::string str_in  = "0a0b0cx0d0xe0f0g0";                  \
    std::string str_ans = "abcdefg";                            \
    std::string ret = sstd::stripAll(LHS, RHS);                 \
    ASSERT_TRUE(ret == str_ans);
TEST(strEdit, stripAll_cc){ strEdit_stripAll_check_io(str_in.c_str(),             "x0" ); }
TEST(strEdit, stripAll_sc){ strEdit_stripAll_check_io(str_in,                     "x0" ); }
TEST(strEdit, stripAll_cs){ strEdit_stripAll_check_io(str_in.c_str(), std::string("x0")); }
TEST(strEdit, stripAll_ss){ strEdit_stripAll_check_io(str_in,         std::string("x0")); }
#undef strEdit_stripAll_check_io

//-----------------------------------------------------------------------------------------------------------------------------------------------
// rstripAll_ow(), lstripAll_ow(), stripAll_ow()

TEST(strEdit, lstripAll_ow_sc_case01_01a){
    std::string str_in  = "0a0b0cx0d0xe0f0g0";
    std::string str_ans = "a0b0cx0d0xe0f0g0";
    sstd::lstripAll_ow(str_in, "x0");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, lstripAll_ow_sc__case01_01b){
    std::string str_in  = "0a0b0cx0d0xe0f0g0";
    std::string str_ans = "";
    sstd::lstripAll_ow(str_in, "0a0b0cx0d0xe0f0g0");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, lstripAll_ow_sc_case01_02){
    std::string str_in  = "";
    std::string str_ans = "";
    sstd::lstripAll_ow(str_in, "x0");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, lstripAll_ow_sc_case01_03){
    std::string str_in  = "";
    std::string str_ans = "";
    sstd::lstripAll_ow(str_in, "");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, lstripAll_ow_sc_case02){
    std::string str_in  = "0000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x0a0b0cx0d0xe0f0g0x";
    std::string str_ans = "a0b0cx0d0xe0f0g0x";
    sstd::lstripAll_ow(str_in, "x0");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}

TEST(strEdit, lstripAll_ow_ss_case01_01){
    std::string str_in  = "0a0b0cx0d0xe0f0g0";
    std::string str_ans = "a0b0cx0d0xe0f0g0";
    sstd::lstripAll_ow(str_in, std::string("x0"));
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}

//---

TEST(strEdit, rstripAll_ow_sc_case01_01a){
    std::string str_in  = "0a0b0cx0d0xe0f0g0";
    std::string str_ans = "0a0b0cx0d0xe0f0g";
    sstd::rstripAll_ow(str_in, "x0");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, rstripAll_ow_sc__case01_01b){
    std::string str_in  = "0a0b0cx0d0xe0f0g0";
    std::string str_ans = "";
    sstd::rstripAll_ow(str_in, "abcdefgx0");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, rstripAll_ow_sc_case01_02){
    std::string str_in  = "";
    std::string str_ans = "";
    sstd::rstripAll_ow(str_in, "x0");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, rstripAll_ow_sc_case01_03){
    std::string str_in  = "";
    std::string str_ans = "";
    sstd::rstripAll_ow(str_in, "");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, rstripAll_ow_sc_case02){
    std::string str_in  = "0a0b0cx0d0xe0f0g00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x";
    std::string str_ans = "0a0b0cx0d0xe0f0g";
    sstd::rstripAll_ow(str_in, "x0");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}

TEST(strEdit, rstripAll_ow_ss_case01_01){
    std::string str_in  = "0a0b0cx0d0xe0f0g0";
    std::string str_ans = "0a0b0cx0d0xe0f0g";
    sstd::rstripAll_ow(str_in, std::string("x0"));
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}

//---

TEST(strEdit, stripAll_ow_case01_01){
    std::string str_in  = "0a0b0cx0d0xe0f0g0";
    std::string str_ans = "abcdefg";
    sstd::stripAll_ow(str_in, "x0");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, stripAll_ow_case01_02){
    std::string str_in  = "";
    std::string str_ans = "";
    sstd::stripAll_ow(str_in, "x0");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, stripAll_ow_case01_03){
    std::string str_in  = "";
    std::string str_ans = "";
    sstd::stripAll_ow(str_in, "");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, stripAll_ow_case02){
    std::string str_in  = "0a0b0cx0d0xe0f0g00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x";
    std::string str_ans = "abcdefg";
    sstd::stripAll_ow(str_in, "x0");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define TEST_strip_quotes__ret_ret_c(ANS_STR, ANS_RET_SQ, ANS_RET_DQ, STR_IN) \
    const char* s = STR_IN;                                             \
                                                                        \
    bool ret_sq;                                                        \
    bool ret_dq;                                                        \
    std::string ret_s = sstd::strip_quotes(ret_sq, ret_dq, s); /* TEST THIS LINE */ \
                                                                        \
    ASSERT_TRUE(ret_s == std::string(ANS_STR) );                        \
    ASSERT_TRUE(ret_sq == ANS_RET_SQ);                                  \
    ASSERT_TRUE(ret_dq == ANS_RET_DQ);

TEST(strEdit, strip_quotes__ret_ret_c_01){
    TEST_strip_quotes__ret_ret_c("abcdef", false, false, R"(abcdef)");
}
TEST(strEdit, strip_quotes__ret_ret_c_02){
    TEST_strip_quotes__ret_ret_c("abcdef", false, false, R"(   abcdef   )");
}
TEST(strEdit, strip_quotes__ret_ret_c_sq_01){
    TEST_strip_quotes__ret_ret_c("abcdef", true, false, R"('abcdef')");
}
TEST(strEdit, strip_quotes__ret_ret_c_sq_02){
    TEST_strip_quotes__ret_ret_c(" abcdef ", true, false, R"(   ' abcdef '   )");
}
TEST(strEdit, strip_quotes__ret_ret_c_sq_single_l){
    TEST_strip_quotes__ret_ret_c("'abcdef", false, false, R"('abcdef)");
}
TEST(strEdit, strip_quotes__ret_ret_c_sq_single_r){
    TEST_strip_quotes__ret_ret_c("abcdef'", false, false, R"(abcdef')");
}
TEST(strEdit, strip_quotes__ret_ret_c_dq_01){
    TEST_strip_quotes__ret_ret_c("abcdef", false, true, R"("abcdef")");
}
TEST(strEdit, strip_quotes__ret_ret_c_dq_02){
    TEST_strip_quotes__ret_ret_c(" abcdef ", false, true, R"(  " abcdef "  )");
}
TEST(strEdit, strip_quotes__ret_ret_c_dq_single_l){
    TEST_strip_quotes__ret_ret_c(R"("abcdef)", false, false, R"("abcdef)");
}
TEST(strEdit, strip_quotes__ret_ret_c_dq_single_r){
    TEST_strip_quotes__ret_ret_c(R"(abcdef")", false, false, R"(abcdef")");
}

#undef TEST_strip_quotes__ret_ret_c

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(strEdit, join_c_0){
    std::vector<std::string> v_in = {};
    std::string ans = "";
    ASSERT_STREQ(sstd::join(v_in,',').c_str(), ans.c_str());
}
TEST(strEdit, join_c_1){
    std::vector<std::string> v_in = {"a"};
    std::string ans = "a";
    ASSERT_STREQ(sstd::join(v_in,',').c_str(), ans.c_str());
}
TEST(strEdit, join_c_2){
    std::vector<std::string> v_in = {"a", "b"};
    std::string ans = "a,b";
    ASSERT_STREQ(sstd::join(v_in,',').c_str(), ans.c_str());
}
TEST(strEdit, join_c_3){
    std::vector<std::string> v_in = {"a", "b", "c"};
    std::string ans = "a,b,c";
    ASSERT_STREQ(sstd::join(v_in,',').c_str(), ans.c_str());
}

//---

TEST(strEdit, join_s_0){
    std::vector<std::string> v_in = {};
    std::string ans = "";
    ASSERT_STREQ(sstd::join(v_in,std::string(", ")).c_str(), ans.c_str());
}
TEST(strEdit, join_s_1){
    std::vector<std::string> v_in = {"a"};
    std::string ans = "a";
    ASSERT_STREQ(sstd::join(v_in,std::string(", ")).c_str(), ans.c_str());
}
TEST(strEdit, join_s_2){
    std::vector<std::string> v_in = {"a", "b"};
    std::string ans = "a, b";
    ASSERT_STREQ(sstd::join(v_in,std::string(", ")).c_str(), ans.c_str());
}
TEST(strEdit, join_s_3){
    std::vector<std::string> v_in = {"a", "b", "c"};
    std::string ans = "a, b, c";
    ASSERT_STREQ(sstd::join(v_in,std::string(", ")).c_str(), ans.c_str());
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
