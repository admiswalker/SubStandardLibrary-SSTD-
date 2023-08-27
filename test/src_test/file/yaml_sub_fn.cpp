#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
/*
TEST(yaml_sub_fn, _splitByLine_dq_sq__dq){
    std::string s=R"(
"a: b c

def
g"

)";
    std::vector<std::string> l = sstd::_splitByLine_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::vector<std::string> ans;
    ans.push_back("");
    ans.push_back(R"("a: b c

def
g")");
    ans.push_back("");
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_sub_fn, _splitByLine_dq_sq__dq_escape){
    std::string s=R"(\"
"a: b c\"

def'
g"

)";
    std::vector<std::string> l = sstd::_splitByLine_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::vector<std::string> ans;
    ans.push_back(R"(\")");
    ans.push_back(R"("a: b c\"

def'
g")");
    ans.push_back("");
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}

//---

TEST(yaml_sub_fn, _splitByLine_dq_sq__sq){
    std::string s=R"(
'a: b c

def
g'

)";
    std::vector<std::string> l = sstd::_splitByLine_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::vector<std::string> ans;
    ans.push_back("");
    ans.push_back(R"('a: b c

def
g')");
    ans.push_back("");
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_sub_fn, _splitByLine_dq_sq__sq_escape){
    std::string s=R"(\"
'a: b c\'

def"
g'

)";
    std::vector<std::string> l = sstd::_splitByLine_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::vector<std::string> ans;
    ans.push_back(R"(\")");
    ans.push_back(R"('a: b c\'

def"
g')");
    ans.push_back("");
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(yaml_sub_fn, _strip_dq_sq_0_case01){
    std::string s=R"()";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"()";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_sub_fn, _strip_dq_sq_0_case02){
    std::string s=R"("")";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"()";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_sub_fn, _strip_dq_sq_0_case03){
    std::string s=R"('')";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"()";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_sub_fn, _strip_dq_sq_1_case01){
    std::string s=R"(a)";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(a)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_sub_fn, _strip_dq_sq_1_case02){
    std::string s=R"(" a ")";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"( a )";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_sub_fn, _strip_dq_sq_2){
    std::string s=R"(ab)";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(ab)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_sub_fn, _strip_dq_sq_3){
    std::string s=R"(abc)";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(abc)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}

//---

TEST(yaml_sub_fn, _strip_dq_sq__non_dq_sq_case01){
    std::string s=R"(abc)";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(abc)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}

//---

TEST(yaml_sub_fn, _strip_dq_sq__non_dq_sq_case00){
    std::string s=R"("abc")";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(abc)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_sub_fn, _extract_dq_sq_value__dq_escape_case01){
    std::string s=R"(  "abc
def
ghi"   )";
    std::string l = sstd::_extract_dq_sq_value(sstd::_strip_dq_sq(s)); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(abc def ghi)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_sub_fn, _extract_dq_sq_value__dq_escape_case02){
    std::string s=R"("abc\
def
ghi"   )";
    std::string l = sstd::_extract_dq_sq_value(sstd::_strip_dq_sq(s)); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(abcdef ghi)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_sub_fn, _extract_dq_sq_value__dq_escape_case03){
    std::string s=R"("abc


def
ghi"   )";
    std::string l = sstd::_extract_dq_sq_value(sstd::_strip_dq_sq(s)); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(abc

def ghi)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_sub_fn, _extract_dq_sq_value__dq_escape_case04){
    std::string s=R"("abc\


def
ghi"   )";
    std::string l = sstd::_extract_dq_sq_value(sstd::_strip_dq_sq(s)); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(abc

def ghi)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_sub_fn, _extract_dq_sq_value__dq_escape_case05){
    std::string s=R"("\
   abc\
   def")";
    std::string l = sstd::_extract_dq_sq_value(sstd::_strip_dq_sq(s)); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(abcdef)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_sub_fn, _extract_dq_sq_value__dq_escape_case06){
    std::string s=R"("
   abc
   def")";
    std::string l = sstd::_extract_dq_sq_value(sstd::_strip_dq_sq(s)); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"( abc def)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_sub_fn, _extract_dq_sq_value__dq_escape_case07){
    std::string s=R"("a: b c'

def\"
g"   )";
    std::string l = sstd::_extract_dq_sq_value(sstd::_strip_dq_sq(s)); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(a: b c'
def" g)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}

//---

TEST(yaml_sub_fn, _extract_dq_sq_value__sq_escape_case07){
    std::string s=R"('a: b c\'

def"
g'   )";
    std::string l = sstd::_extract_dq_sq_value(sstd::_strip_dq_sq(s)); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(a: b c'
def" g)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
*/
//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();

