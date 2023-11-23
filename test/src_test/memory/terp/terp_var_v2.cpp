#include <sstd/sstd.hpp>
#include "../../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::var_v2

TEST(memory_terp, var_v2_constructor){
    sstd::terp::var_v2 x;
}
TEST(memory_terp, var_v2_copy){
    sstd::terp::var_v2 x;
    sstd::terp::var_v2 x2 = sstd::terp::list_v2(3);
    printf("--- b\n");
    x.copy(x2);
    printf("--- e\n");
//    x[0] = "a";
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
