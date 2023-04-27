#include <sstd/sstd.hpp>
#include "../../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::var
//*

// print
TEST(memory_terp_print, var_num_null){
    sstd::terp::var a;

    testing::internal::CaptureStdout();
    sstd::print(a); // TEST THIS LINE
    std::string ret = testing::internal::GetCapturedStdout().c_str();
    ASSERT_STREQ(ret.c_str(), "\n");
}
TEST(memory_terp_print, var_num_str){
    sstd::terp::var a;
    
    a = "test";

    testing::internal::CaptureStdout();
    sstd::print(a); // TEST THIS LINE
    std::string ret = testing::internal::GetCapturedStdout().c_str();
    ASSERT_STREQ(ret.c_str(), "test\n");
}

//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::list
//*

// print
TEST(memory_terp_print, list){
    sstd::terp::var a;
    a = sstd::terp::list(3);
    a[0] = "v0";
    a[1] = "v1";
    a[2] = "v2";

    sstd::print(a);
}

//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::hash
//*

// print()
TEST(memory_terp_print, hash){
}

//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
