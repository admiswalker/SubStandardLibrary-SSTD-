#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

// NOTE:
//   Don't change the file (this file) name.
//   And don't change the line number of pdbg() and pdbg_if() functions.
//   
//   Because of the macro is takeing the file name and line numbers.

TEST(pdbg, pdbg){
    testing::internal::CaptureStdout();
    sstd::pdbg("example msg.");
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "\x1B[1m\x1B[31m../test/src/print/pdbg.cpp:14 TestBody(): \x1B[0mexample msg.");
    //  \u001b[31m  :  set output red
    //  \u001b[0m   :  reset color
}
TEST(pdbg, pdbg_err){
    testing::internal::CaptureStdout();
    sstd::pdbg_err("example err msg.");
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "\x1B[1m../test/src/print/pdbg.cpp:21 TestBody(): \x1B[31merror: \x1B[0mexample err msg.");
    //  \u001b[31m  :  set output red
    //  \u001b[0m   :  reset color
}
TEST(pdbg, pdbg_if_true){
    testing::internal::CaptureStdout();
    sstd::pdbg_if(true, "example msg.");
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "\x1B[1m\x1B[31m../test/src/print/pdbg.cpp:28 TestBody(): \x1B[0mexample msg.");
}
TEST(pdbg, pdbg_if_false){
    testing::internal::CaptureStdout();
    sstd::pdbg_if(false, "ERROR: example err msg.");
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
