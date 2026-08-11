#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(argstack, argstack_vi){
    std::vector<int> vi;
    sstd::argstack(vi, 1, 2, 3);
    ASSERT_EQ(vi, std::vector<int>({1,2,3}));
}
TEST(argstack, argstack_vs){
    std::vector<std::string> vs;
    sstd::argstack(vs, std::string("A"), std::string("B"), std::string("C"));
    ASSERT_EQ(vs, std::vector<std::string>({"A","B","C"}));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(argstack, argstack_tuple_vi_vs){
    std::vector<int> vi;
    std::vector<std::string> vs;
    
    sstd::argstack(std::make_tuple(&vi, &vs), 1, 2, std::string("A"), 3, std::string("B"), std::string("C"));
    ASSERT_EQ(vi, std::vector<int>({1,2,3}));
    ASSERT_EQ(vs, std::vector<std::string>({"A","B","C"}));
}
TEST(argstack, argstack_tuple_vi_vs_vd){
    std::vector<int> vi;
    std::vector<std::string> vs;
    std::vector<double> vd;
    
    sstd::argstack(std::make_tuple(&vi, &vs, &vd), 1.0, 2.0, 3.0, 1, 2, std::string("A"), 3, std::string("B"), std::string("C"));
    ASSERT_EQ(vi, std::vector<int>({1,2,3}));
    ASSERT_EQ(vs, std::vector<std::string>({"A","B","C"}));
    ASSERT_EQ(vd, std::vector<double>({1.0,2.0,3.0}));
}
TEST(argstack, argstack_tuple_vi_and_empty_vs_vd){
    std::vector<int> vi;
    std::vector<std::string> vs;
    std::vector<double> vd;
    
    sstd::argstack(std::make_tuple(&vi, &vs, &vd), 1);
    ASSERT_EQ(vi, std::vector<int>({1}));
    ASSERT_EQ(vs, std::vector<std::string>({}));
    ASSERT_EQ(vd, std::vector<double>({}));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
