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
    
    testing::internal::CaptureStdout();
    sstd::print(a); // TEST THIS LINE
    std::string ret = testing::internal::GetCapturedStdout().c_str();
    ASSERT_STREQ(ret.c_str(), "{\"k2\": \"v2\", \"k1\": \"v1\", \"k0\": \"v0\"}\n");
}
TEST(memory_terp_print, hash_depth2){
    sstd::terp::var a;
    a = sstd::terp::hash();
    a["k0"] = "v0";
    a["k1"] = "v1";
    a["k2"] = "v2";
    a["k3"] = sstd::terp::hash();
    a["k3"]["k0"] = "v0";
    a["k3"]["k1"] = "v1";
    a["k3"]["k2"] = "v2";
    
    testing::internal::CaptureStdout();
    sstd::print(a); // TEST THIS LINE
    std::string ret = testing::internal::GetCapturedStdout().c_str();
    ASSERT_STREQ(ret.c_str(), "{\"k3\": {\"k2\": \"v2\", \"k1\": \"v1\", \"k0\": \"v0\"}, \"k2\": \"v2\", \"k1\": \"v1\", \"k0\": \"v0\"}\n");
}

//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// complex test cases

// print()
TEST(memory_terp_print, list_hash_list){
    sstd::terp::var a;
    a = sstd::terp::list(2);
    a[0] = "v0";
    a[1] = sstd::terp::hash();
    a[1]["k10"] = "v10";
    a[1]["k11"] = sstd::terp::list(2);
    a[1]["k11"][0] = "v110";
    a[1]["k11"][1] = "v111";
    
    testing::internal::CaptureStdout();
    sstd::print(a); // TEST THIS LINE
    std::string ret = testing::internal::GetCapturedStdout().c_str();
    ASSERT_STREQ(ret.c_str(), "[\"v0\" {\"k11\": [\"v110\" \"v111\"], \"k10\": \"v10\"}]\n");
}
TEST(memory_terp_print, hash_list_hash){
    sstd::terp::var a;
    a = sstd::terp::hash();
    a["k0"] = "v0";
    a["k1"] = sstd::terp::list(2);
    a["k1"][0] = "v10";
    a["k1"][1] = sstd::terp::hash();
    a["k1"][1]["k110"] = "v110";
    a["k1"][1]["k111"] = "v111";
    
    testing::internal::CaptureStdout();
    sstd::print(a); // TEST THIS LINE
    std::string ret = testing::internal::GetCapturedStdout().c_str();
    ASSERT_STREQ(ret.c_str(), "{\"k1\": [\"v10\" {\"k111\": \"v111\", \"k110\": \"v110\"}], \"k0\": \"v0\"}\n");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for_printn

TEST(memory_terp_print, for_printn){
    sstd::terp::var a;
    a = "string";
    
    testing::internal::CaptureStdout();
    sstd::for_printn(a); // TEST THIS LINE
    std::string ret = testing::internal::GetCapturedStdout().c_str();
    ASSERT_STREQ(ret.c_str(), " = \"string\"\n");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// print_for_vT

TEST(memory_terp_print, print_for_vT){
    sstd::terp::var a;
    a = "string";
    
    testing::internal::CaptureStdout();
    sstd::print_for_vT(a); // TEST THIS LINE
    std::string ret = testing::internal::GetCapturedStdout().c_str();
    ASSERT_STREQ(ret.c_str(), "\"string\"");
}
TEST(memory_terp_print, print_for_vT_by_template){
    std::vector<sstd::terp::var> a;
    a.push_back("s1");
    a.push_back("s2");
    a.push_back("s3");
    
    testing::internal::CaptureStdout();
    sstd::print_for_vT(a); // TEST THIS LINE
    std::string ret = testing::internal::GetCapturedStdout().c_str();
    ASSERT_STREQ(ret.c_str(), "[\"s1\" \"s2\" \"s3\"]");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
