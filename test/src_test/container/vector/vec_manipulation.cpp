#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(vec_manipulation, rmEmpty){
    std::vector<std::string> v = {"", "- 1", "- 2", "- 3", "  "};
    std::vector<std::string> v_ans = {"- 1", "- 2", "- 3", "  "};
    ASSERT_TRUE(sstd::rmEmpty(v) == v_ans);
}
TEST(vec_manipulation, rmEmpty_02){
    std::vector<std::string> v = {"", "- 1", "- 2", "", "- 3", ""};
    std::vector<std::string> v_ans = {"- 1", "- 2", "- 3"};
    ASSERT_TRUE(sstd::rmEmpty(v) == v_ans);
}
TEST(vec_manipulation, rmEmpty_ow_01){
    std::vector<std::string> v = {"", "- 1", "- 2", "- 3", "  "};
    std::vector<std::string> v_ans = {"- 1", "- 2", "- 3", "  "};

    sstd::rmEmpty_ow(v);

    ASSERT_TRUE(v == v_ans);
}
TEST(vec_manipulation, rmEmpty_ow_02){
    std::vector<std::string> v = {"- 1", "- 2", "- 3", "  "};
    std::vector<std::string> v_ans = {"- 1", "- 2", "- 3", "  "};

    sstd::rmEmpty_ow(v);
    
    ASSERT_TRUE(v == v_ans);
}
TEST(vec_manipulation, rmEmpty_ow_multiple_vector_arguments_01){
    std::vector<std::string> v_base  = { "", "1", "2", "3", "4",  "", "5"};
    std::vector<std::string> v_1     = {"a", "b", "c", "d", "e", "f", "g"};
    std::vector<std::string> v_ans_b = {     "1", "2", "3", "4",      "5"};
    std::vector<std::string> v_ans_1 = {     "b", "c", "d", "e",      "g"};

    sstd::rmEmpty_ow(v_base, v_1);
    
    ASSERT_TRUE(v_base == v_ans_b);
    ASSERT_TRUE(v_1 == v_ans_1);
}

//---

TEST(vec_manipulation, rmEmpty_l){
    std::vector<std::string> v = {"", "- 1", "- 2", "- 3", ""};
    std::vector<std::string> v_ans = {"- 1", "- 2", "- 3", ""};

    std::vector<std::string> r = sstd::rmEmpty_l(v); // TEST THIS LINE
    
    ASSERT_TRUE(r == v_ans);
}
TEST(vec_manipulation, rmEmpty_l_copy){
    std::vector<std::string> v = {"- 1", "- 2", "- 3"};
    std::vector<std::string> v_ans = {"- 1", "- 2", "- 3"};

    std::vector<std::string> r = sstd::rmEmpty_l(v); // TEST THIS LINE
    
    ASSERT_TRUE(r == v_ans);
}
TEST(vec_manipulation, rmEmpty_l_empty){
    std::vector<std::string> v;
    std::vector<std::string> v_ans;

    std::vector<std::string> r = sstd::rmEmpty_l(v); // TEST THIS LINE
    
    ASSERT_TRUE(r == v_ans);
}

//---

TEST(vec_manipulation, rmEmpty_l_ow){
    std::vector<std::string> v = {"", "- 1", "- 2", "- 3", ""};
    std::vector<std::string> v_ans = {"- 1", "- 2", "- 3", ""};
    
    sstd::rmEmpty_l_ow(v); // TEST THIS LINE
    
    ASSERT_TRUE(v == v_ans);
}
TEST(vec_manipulation, rmEmpty_l_ow_copy){
    std::vector<std::string> v = {"- 1", "- 2", "- 3"};
    std::vector<std::string> v_ans = {"- 1", "- 2", "- 3"};

    sstd::rmEmpty_l_ow(v); // TEST THIS LINE
    
    ASSERT_TRUE(v == v_ans);
}
TEST(vec_manipulation, rmEmpty_l_ow_empty){
    std::vector<std::string> v;
    std::vector<std::string> v_ans;

    sstd::rmEmpty_l_ow(v); // TEST THIS LINE
    
    ASSERT_TRUE(v == v_ans);
}

//---

TEST(vec_manipulation, rmEmpty_r){
    std::vector<std::string> v     = {"", "- 1", "- 2", "- 3", ""};
    std::vector<std::string> v_ans = {"", "- 1", "- 2", "- 3"    };
    
    std::vector<std::string> r = sstd::rmEmpty_r(v); // TEST THIS LINE
    
    ASSERT_TRUE(r == v_ans);
}
TEST(vec_manipulation, rmEmpty_r_copy){
    std::vector<std::string> v     = {"- 1", "- 2", "- 3"};
    std::vector<std::string> v_ans = {"- 1", "- 2", "- 3"};
    
    std::vector<std::string> r = sstd::rmEmpty_r(v); // TEST THIS LINE
    
    ASSERT_TRUE(r == v_ans);
}
TEST(vec_manipulation, rmEmpty_r_empty){
    std::vector<std::string> v;
    std::vector<std::string> v_ans;
    
    std::vector<std::string> r = sstd::rmEmpty_r(v); // TEST THIS LINE
    
    ASSERT_TRUE(r == v_ans);
}

//---

TEST(vec_manipulation, rmEmpty_r_ow){
    std::vector<std::string> v     = {"", "- 1", "- 2", "- 3", ""};
    std::vector<std::string> v_ans = {"", "- 1", "- 2", "- 3"    };
    
    sstd::rmEmpty_r_ow(v); // TEST THIS LINE
    
    ASSERT_TRUE(v == v_ans);
}
TEST(vec_manipulation, rmEmpty_r_ow_copy){
    std::vector<std::string> v = {"- 1", "- 2", "- 3"};
    std::vector<std::string> v_ans = {"- 1", "- 2", "- 3"};

    sstd::rmEmpty_r_ow(v); // TEST THIS LINE
    
    ASSERT_TRUE(v == v_ans);
}
TEST(vec_manipulation, rmEmpty_r_ow_empty){
    std::vector<std::string> v;
    std::vector<std::string> v_ans;

    sstd::rmEmpty_r_ow(v); // TEST THIS LINE
    
    ASSERT_TRUE(v == v_ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(vec_manipulation, rmEmpty_ow_multiple_vector_arguments_02){
    std::vector<std::string> v_base  = { "", "1", "2", "3", "4",  "", "5"};
    std::vector<std::string> v_1     = {"a", "b", "c", "d", "e", "f", "g"};
    std::vector<std::string> v_2     = {"a", "b", "c", "d", "e", "f", "g"};
    std::vector<std::string> v_ans_b = {     "1", "2", "3", "4",      "5"};
    std::vector<std::string> v_ans_1 = {     "b", "c", "d", "e",      "g"};

    sstd::rmEmpty_ow(v_base, v_1, v_2);
    
    ASSERT_TRUE(v_base == v_ans_b);
    ASSERT_TRUE(v_1 == v_ans_1);
    ASSERT_TRUE(v_2 == v_ans_1);
}
TEST(vec_manipulation, rmEmpty_ow_multiple_vector_arguments_02_different_size_vec){
    std::vector<std::string> v_base  = { "", "1", "2", "3", "4",  "", "5"};
    std::vector<std::string> v_1     = {"a", "b", "c", "d", "e", "f", "g", "h"};
    std::vector<std::string> v_2     = {"a", "b", "c", "d", "e", "f"     };
    std::vector<std::string> v_ans_b = {     "1", "2", "3", "4",      "5"};
    std::vector<std::string> v_ans_1 = {     "b", "c", "d", "e",      "g"};
    std::vector<std::string> v_ans_2 = {     "b", "c", "d", "e"          };

    sstd::rmEmpty_ow(v_base, v_1, v_2);
    
    ASSERT_TRUE(v_base == v_ans_b);
    ASSERT_TRUE(v_1 == v_ans_1);
    ASSERT_TRUE(v_2 == v_ans_2);
}
TEST(vec_manipulation, rmEmpty_ow_multiple_vector_arguments_03){
    std::vector<std::string> v_base  = { "", "1", "2", "3", "4",  "", "5"};
    std::vector<uint>        v_1     = {  1,   2,   3,   4,   5,   6,   7};
    std::vector<std::string> v_ans_b = {     "1", "2", "3", "4",      "5"};
    std::vector<uint>        v_ans_1 = {       2,   3,   4,   5,        7};

    sstd::rmEmpty_ow(v_base, v_1);
    
    ASSERT_TRUE(v_base == v_ans_b);
    ASSERT_TRUE(v_1 == v_ans_1);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(vec_manipulation, cntEmpty){
    std::vector<std::string> v = {"", "- 1", "- 2", "- 3", ""};
    uint ans = 2;
    
    ASSERT_EQ(sstd::cntEmpty(v), ans);
}
TEST(vec_manipulation, cntEmpty_emtpy){
    std::vector<std::string> v;
    uint ans = 0;
    
    ASSERT_EQ(sstd::cntEmpty(v), ans);
}
TEST(vec_manipulation, cntEmpty_full){
    std::vector<std::string> v = {"- 1", "- 2", "- 3"};
    uint ans = 0;
    
    ASSERT_EQ(sstd::cntEmpty(v), ans);
}

//---

TEST(vec_manipulation, cntEmpty_l){
    std::vector<std::string> v = {"", "- 1", "- 2", "- 3", ""};
    uint ans = 1;
    
    ASSERT_EQ(sstd::cntEmpty_l(v), ans);
}
TEST(vec_manipulation, cntEmpty_l_emtpy){
    std::vector<std::string> v;
    uint ans = 0;
    
    ASSERT_EQ(sstd::cntEmpty_l(v), ans);
}
TEST(vec_manipulation, cntEmpty_l_full){
    std::vector<std::string> v = {"- 1", "- 2", "- 3"};
    uint ans = 0;
    
    ASSERT_EQ(sstd::cntEmpty_l(v), ans);
}

//---

TEST(vec_manipulation, cntEmpty_r){
    std::vector<std::string> v = {"", "- 1", "- 2", "- 3", ""};
    uint ans = 1;
    
    ASSERT_EQ(sstd::cntEmpty_r(v), ans);
}
TEST(vec_manipulation, cntEmpty_r_emtpy){
    std::vector<std::string> v;
    uint ans = 0;
    
    ASSERT_EQ(sstd::cntEmpty_r(v), ans);
}
TEST(vec_manipulation, cntEmpty_r_full){
    std::vector<std::string> v = {"- 1", "- 2", "- 3"};
    uint ans = 0;
    
    ASSERT_EQ(sstd::cntEmpty_r(v), ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
