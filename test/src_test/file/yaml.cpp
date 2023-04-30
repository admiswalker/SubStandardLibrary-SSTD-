#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// list

TEST(yaml, push_back_to_list){
    std::string s=R"(
- a # comment
- b

- c
)";
    sstd::terp::var yml = sstd::yaml_from_str(s); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// hash

TEST(yaml, push_back_to_hash){
    std::string s=R"(
k1: v1 # comment
k2: v2

k3: v3
)";
    sstd::terp::var yml = sstd::yaml_from_str(s); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "v1";
    ans["k2"] = "v2";
    ans["k3"] = "v3";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// complex test cases

TEST(yaml, push_back_to_list_hash_list){
}

TEST(yaml, push_back_to_hash_list_hash){
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
