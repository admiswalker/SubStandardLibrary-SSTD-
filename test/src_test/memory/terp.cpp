#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(memory_terp, constructor){
    sstd::terp::var a;
}
TEST(memory_terp, ope_eq_str){
    sstd::terp::var a;
    a = "test";
    ASSERT_STREQ(a.to<std::string>().c_str(), "test");
}
TEST(memory_terp, ope_eq_list){
    sstd::terp::var a;
    a = sstd::terp::list(1);
    //a.push_back("test");

    //a.resize(1);
    a[0] = "test";
    
    ASSERT_STREQ(a[0].to<std::string>().c_str(), "test");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(memory_terp, push_back){
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
