#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(vec_manipulation, rmEmpty){
    std::vector<std::string> v = {"", "- 1", "- 2", "- 3", "  "};
    std::vector<std::string> v_ans = {"- 1", "- 2", "- 3", "  "};
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

EXECUTE_TESTS();
