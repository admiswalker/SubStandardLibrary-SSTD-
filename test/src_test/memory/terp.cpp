#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::var
//*
TEST(memory_terp, var_constructor){
    sstd::terp::var a;
}
TEST(memory_terp, var_ope_eq_str){
    sstd::terp::var a;
    a = "test";
    ASSERT_STREQ(a.to<std::string>().c_str(), "test");
}
TEST(memory_terp, var_ope_eq_list){
    sstd::terp::var a;
    a = sstd::terp::list(1);
    a[0] = "test"; // TEST THIS LINE
    
    ASSERT_STREQ(a[0].to<std::string>().c_str(), "test");
}
TEST(memory_terp, var_ope_eq_list_case02){
    sstd::terp::var a;
    a = sstd::terp::list();
    a.resize(1);
    a[0] = "test"; // TEST THIS LINE
    
    ASSERT_STREQ(a[0].to<std::string>().c_str(), "test");
}

// typeNum()
TEST(memory_terp, var_typeNum_null){
    sstd::terp::var a;
    ASSERT_STREQ(sstd::typeNum2str(a.typeNum()).c_str(), "null"); // TEST THIS LINE
}
TEST(memory_terp, var_typeNum_c){
    sstd::terp::var a;
    a = "test";
    ASSERT_STREQ(sstd::typeNum2str(a.typeNum()).c_str(), "str"); // TEST THIS LINE
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::list
//*
// constructors
// size()
TEST(memory_terp, list_arg_null){
    sstd::terp::var a;
    a = sstd::terp::list();
    ASSERT_EQ(a.size(), (uint)0);
}
TEST(memory_terp, list_arg_10){
    sstd::terp::var a;
    a = sstd::terp::list(10);
    ASSERT_EQ(a.size(), (uint)10);
}

// resize()
TEST(memory_terp, list_resize){
    sstd::terp::var a;
    a = sstd::terp::list();
    ASSERT_EQ(a.size(), (uint)0);
    a.resize(10);
    ASSERT_EQ(a.size(), (uint)10);
}

// push_back()
TEST(memory_terp, list_push_back_c){
    sstd::terp::var a;
    a = sstd::terp::list();
    a.push_back("test"); // TEST THIS LINE
    
    ASSERT_STREQ(a[0].to<std::string>().c_str(), "test");
}

// typeNum()
TEST(memory_terp, list_typeNum){
    sstd::terp::var a;
    a = sstd::terp::list();
    ASSERT_STREQ(sstd::typeNum2str(a.typeNum()).c_str(), "vec_void_ptr"); // TEST THIS LINE
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::hash
//*
// constructors
// size()
TEST(memory_terp, hash_arg_null){
    sstd::terp::var a;
    a = sstd::terp::hash();
    ASSERT_EQ(a.size(), (uint)0);
    
    a["k1"] = "v1"; // TEST THIS LINE
    
    ASSERT_EQ(a.size(), (uint)1);
    ASSERT_STREQ(a["k1"].to<std::string>().c_str(), "v1");
}
TEST(memory_terp, hash_arg_10){
    sstd::terp::var a;
    a = sstd::terp::hash(14);
    ASSERT_EQ(a.bucket_count(), (uint)17); // std::unordered_map allocates the prime number size, equal or nearest larger than the allocating size.
}

// typeNum()
TEST(memory_terp, hash_typeNum){
    sstd::terp::var a;
    a = sstd::terp::hash();
    ASSERT_STREQ(sstd::typeNum2str(a.typeNum()).c_str(), "hash_str_void_ptr"); // TEST THIS LINE
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
