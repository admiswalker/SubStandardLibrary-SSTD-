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


//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
