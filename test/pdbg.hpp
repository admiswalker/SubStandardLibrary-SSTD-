#pragma once

// NOTE:
//   Don't change the file (this file) name.
//   And don't change the line number of pdbg() and pdbg_if() functions.
//   
//   Because of the macro is takeing the file name and line numbers.

TEST(pdbg, pdbg){
    testing::internal::CaptureStdout();
    sstd::pdbg("ERROR: example err msg.");
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "./test/pdbg.hpp: TestBody(11): \u001b[31mERROR: example err msg.\u001b[0m");
    //  \u001b[31m  :  set output red
    //  \u001b[0m   :  reset color
}
TEST(pdbg, pdbg_if_true){
    testing::internal::CaptureStdout();
    sstd::pdbg_if(true, "ERROR: example err msg.");
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "./test/pdbg.hpp: TestBody(18): \u001b[31mERROR: example err msg.\u001b[0m");
}
TEST(pdbg, pdbg_if_false){
    testing::internal::CaptureStdout();
    sstd::pdbg_if(false, "ERROR: example err msg.");
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "");
}
