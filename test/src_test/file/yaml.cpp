#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(yaml, push_back_to_list){
    std::string s=R"(
- a # comment
- b

- c
)";
    sstd::terp::var yml = sstd::yaml_from_str(s); // TEST THIS LINE
    sstd::printn(yml);
}
TEST(yaml, push_back_to_hash){
    std::string s=R"(
k1: v1 # comment
k2: v2

k3: v3
)";
    sstd::terp::var yml = sstd::yaml_from_str(s); // TEST THIS LINE
    sstd::printn(yml);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
