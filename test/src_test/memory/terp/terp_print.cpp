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
    ASSERT_STREQ(ret.c_str(), "\"test\"\n");
}

//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::list
//*

// print
TEST(memory_terp_print, list_depth1){
    sstd::terp::var a;
    a = sstd::terp::list(3);
    a[0] = "v0";
    a[1] = "v1";
    a[2] = "v2";

    testing::internal::CaptureStdout();
    sstd::print(a); // TEST THIS LINE
    std::string ret = testing::internal::GetCapturedStdout().c_str();
    ASSERT_STREQ(ret.c_str(), "[\"v0\" \"v1\" \"v2\"]\n");
}
TEST(memory_terp_print, list_depth2){
    sstd::terp::var a;
    a = sstd::terp::list(4);
    a[0] = "v0";
    a[1] = "v1";
    a[2] = "v2";
    a[3] = sstd::terp::list(3);
    a[3][0] = "v30";
    a[3][1] = "v31";
    a[3][2] = "v32";

    testing::internal::CaptureStdout();
    sstd::print(a); // TEST THIS LINE
    std::string ret = testing::internal::GetCapturedStdout().c_str();
    ASSERT_STREQ(ret.c_str(), "[\"v0\" \"v1\" \"v2\" [\"v30\" \"v31\" \"v32\"]]\n");
}

//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::hash
//*

// print()
TEST(memory_terp_print, hash_depth1){
    sstd::terp::var a;
    a = sstd::terp::hash();
    a["k0"] = "v0";
    a["k1"] = "v1";
    a["k2"] = "v2";
    
    //testing::internal::CaptureStdout();
    sstd::print(a); // TEST THIS LINE
    //std::string ret = testing::internal::GetCapturedStdout().c_str();
    //ASSERT_STREQ(ret.c_str(), "[v0 v1 v2]\n");
}

//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
