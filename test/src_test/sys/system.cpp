#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(system, system_char){
    int ret;
    
    testing::internal::CaptureStdout();
    ret = sstd::system("ls"); if(WIFEXITED(ret)<=0){ printf("ERROR:\n"); } // <- want to test this line
    std::string test = testing::internal::GetCapturedStdout();
    
    testing::internal::CaptureStdout();
    ret = system("ls"); if(WIFEXITED(ret)<=0){ printf("ERROR:\n"); }
    std::string ans = testing::internal::GetCapturedStdout();
    
    ASSERT_STREQ(test.c_str(), ans.c_str());
}
TEST(system, system_char_err){
    int ret;
    
    testing::internal::CaptureStdout();
    ret = sstd::system("sh ./test/src_test/sys/stdlib_system_stdout.sh"); if(WIFEXITED(ret)<=0){ printf("ERROR:\n"); } // <- want to test this line
    std::string test = testing::internal::GetCapturedStdout();
    ASSERT_EQ(WEXITSTATUS(ret), 0);
    
    testing::internal::CaptureStdout();
    ret = system("sh ./test/src_test/sys/stdlib_system_stdout.sh"); if(WIFEXITED(ret)<=0){ printf("ERROR:\n"); }
    std::string ans = testing::internal::GetCapturedStdout();
    ASSERT_EQ(WEXITSTATUS(ret), 0);
    
    ASSERT_STREQ(test.c_str(), ans.c_str());
}

TEST(system, system_string){
    int ret;
    
    testing::internal::CaptureStdout();
    ret = sstd::system(std::string("ls")); if(WIFEXITED(ret)<=0){ printf("ERROR:\n"); }// <- want to test this line
    std::string test = testing::internal::GetCapturedStdout();
    
    testing::internal::CaptureStdout();
    ret = system("ls"); if(WIFEXITED(ret)<=0){ printf("ERROR:\n"); }
    std::string ans = testing::internal::GetCapturedStdout();
    
    ASSERT_STREQ(test.c_str(), ans.c_str());
}
TEST(system, system_string_case02){
    int ret;
    
    testing::internal::CaptureStderr();
    ret = sstd::system(std::string("sh ./test/src_test/sys/stdlib_system_stderr.sh")); if(WIFEXITED(ret)<=0){ printf("ERROR:\n"); }// <- want to test this line
    std::string test = testing::internal::GetCapturedStderr();
    ASSERT_EQ(WEXITSTATUS(ret), 255);

    testing::internal::CaptureStderr();
    ret = system("sh ./test/src_test/sys/stdlib_system_stderr.sh"); if(WIFEXITED(ret)<=0){ printf("ERROR:\n"); }
    std::string ans = testing::internal::GetCapturedStderr();
    ASSERT_EQ(WEXITSTATUS(ret), 255);

    ASSERT_STREQ(test.c_str(), ans.c_str());
}

//---

TEST(system, system_stdout_char){
    int ret01; std::string test01;
    ret01 = sstd::system_stdout(test01, R"(sh ./test/src_test/sys/stdlib_system_stdout.sh)");
    ASSERT_EQ(ret01, 0);
    ASSERT_STREQ(test01.c_str(), "hello-stdout\n");
    
    int ret02; std::string test02;
    ret02 = sstd::system_stdout(test02, R"(sh ./test/src_test/sys/stdlib_system_stderr.sh)");
    ASSERT_EQ(WEXITSTATUS(ret02), 255);
    ASSERT_STREQ(test02.c_str(), "");
}
TEST(system, system_stdout_string){
    int ret01; std::string test01;
    ret01 = sstd::system_stdout(test01, std::string(R"(sh ./test/src_test/sys/stdlib_system_stdout.sh)"));
    ASSERT_EQ(ret01, 0);
    ASSERT_STREQ(test01.c_str(), "hello-stdout\n");
    
    int ret02; std::string test02;
    ret02 = sstd::system_stdout(test02, std::string(R"(sh ./test/src_test/sys/stdlib_system_stderr.sh)"));
    ASSERT_EQ(WEXITSTATUS(ret02), 255);
    ASSERT_STREQ(test02.c_str(), "");
}

//---

TEST(system, system_stderr_char){
    int ret01; std::string test01;
    ret01 = sstd::system_stderr(test01, R"(sh ./test/src_test/sys/stdlib_system_stdout.sh)");
    ASSERT_EQ(ret01, 0);
    ASSERT_STREQ(test01.c_str(), "");
    
    int ret02; std::string test02;
    ret02 = sstd::system_stderr(test02, R"(sh ./test/src_test/sys/stdlib_system_stderr.sh)");
    ASSERT_EQ(WEXITSTATUS(ret02), 255);
    ASSERT_STREQ(test02.c_str(), "hello-stderr\n");
}
TEST(system, system_stderr_string){
    int ret01; std::string test01;
    ret01 = sstd::system_stderr(test01, std::string(R"(sh ./test/src_test/sys/stdlib_system_stdout.sh)"));
    ASSERT_EQ(ret01, 0);
    ASSERT_STREQ(test01.c_str(), "");
    
    int ret02; std::string test02;
    ret02 = sstd::system_stderr(test02, std::string(R"(sh ./test/src_test/sys/stdlib_system_stderr.sh)"));
    ASSERT_EQ(WEXITSTATUS(ret02), 255);
    ASSERT_STREQ(test02.c_str(), "hello-stderr\n");
}

//---

TEST(system, system_stdout_stderr_char){
    int ret01; std::string test01;
    ret01 = sstd::system_stdout_stderr(test01, R"(sh ./test/src_test/sys/stdlib_system_stdout.sh)");
    ASSERT_EQ(ret01, 0);
    ASSERT_STREQ(test01.c_str(), "hello-stdout\n");
    
    int ret02; std::string test02;
    ret02 = sstd::system_stdout_stderr(test02, R"(sh ./test/src_test/sys/stdlib_system_stderr.sh)");
    ASSERT_EQ(WEXITSTATUS(ret02), 255);
    ASSERT_STREQ(test02.c_str(), "hello-stderr\n");
}
TEST(system, system_stdout_stderr_string){
    int ret01; std::string test01;
    ret01 = sstd::system_stdout_stderr(test01, std::string(R"(sh ./test/src_test/sys/stdlib_system_stdout.sh)"));
    ASSERT_EQ(ret01, 0);
    ASSERT_STREQ(test01.c_str(), "hello-stdout\n");
    
    int ret02; std::string test02;
    ret02 = sstd::system_stdout_stderr(test02, std::string(R"(sh ./test/src_test/sys/stdlib_system_stderr.sh)"));
    ASSERT_EQ(WEXITSTATUS(ret02), 255);
    ASSERT_STREQ(test02.c_str(), "hello-stderr\n");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
