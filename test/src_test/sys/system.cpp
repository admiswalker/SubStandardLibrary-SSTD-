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
    ASSERT_TRUE(WEXITSTATUS(ret)==0);
    
    testing::internal::CaptureStdout();
    ret = system("sh ./test/src_test/sys/stdlib_system_stdout.sh"); if(WIFEXITED(ret)<=0){ printf("ERROR:\n"); }
    std::string ans = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(WEXITSTATUS(ret)==0);
    
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
    ASSERT_TRUE(WEXITSTATUS(ret)!=0);

    testing::internal::CaptureStderr();
    ret = system("sh ./test/src_test/sys/stdlib_system_stderr.sh"); if(WIFEXITED(ret)<=0){ printf("ERROR:\n"); }
    std::string ans = testing::internal::GetCapturedStderr();
    ASSERT_TRUE(WEXITSTATUS(ret)!=0);

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
    ASSERT_TRUE(WEXITSTATUS(ret02)!=0);
    ASSERT_STREQ(test02.c_str(), "");
}
TEST(system, system_stdout_string){
    int ret01; std::string test01;
    ret01 = sstd::system_stdout(test01, std::string(R"(sh ./test/src_test/sys/stdlib_system_stdout.sh)"));
    ASSERT_EQ(ret01, 0);
    ASSERT_STREQ(test01.c_str(), "hello-stdout\n");
    
    int ret02; std::string test02;
    ret02 = sstd::system_stdout(test02, std::string(R"(sh ./test/src_test/sys/stdlib_system_stderr.sh)"));
    ASSERT_TRUE(WEXITSTATUS(ret02)!=0);
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
    ASSERT_TRUE(WEXITSTATUS(ret02)!=0);
    ASSERT_STREQ(test02.c_str(), "hello-stderr\n");
}
TEST(system, system_stderr_string){
    int ret01; std::string test01;
    ret01 = sstd::system_stderr(test01, std::string(R"(sh ./test/src_test/sys/stdlib_system_stdout.sh)"));
    ASSERT_EQ(ret01, 0);
    ASSERT_STREQ(test01.c_str(), "");
    
    int ret02; std::string test02;
    ret02 = sstd::system_stderr(test02, std::string(R"(sh ./test/src_test/sys/stdlib_system_stderr.sh)"));
    ASSERT_TRUE(WEXITSTATUS(ret02)!=0);
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
    ASSERT_TRUE(WEXITSTATUS(ret02)!=0);
    ASSERT_STREQ(test02.c_str(), "hello-stderr\n");
}
TEST(system, system_stdout_stderr_string){
    int ret01; std::string test01;
    ret01 = sstd::system_stdout_stderr(test01, std::string(R"(sh ./test/src_test/sys/stdlib_system_stdout.sh)"));
    ASSERT_EQ(ret01, 0);
    ASSERT_STREQ(test01.c_str(), "hello-stdout\n");
    
    int ret02; std::string test02;
    ret02 = sstd::system_stdout_stderr(test02, std::string(R"(sh ./test/src_test/sys/stdlib_system_stderr.sh)"));
    ASSERT_TRUE(WEXITSTATUS(ret02)!=0);
    ASSERT_STREQ(test02.c_str(), "hello-stderr\n");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Below functions are the not recommended to use. (Below functions will be delete on sstd ver 3.x.x).

TEST(system_old_imp_delete_on_ver3xx, system_stdout_char){
    std::string test01 = sstd::system_stdout(R"(sh ./test/src_test/sys/stdlib_system_stdout.sh)");
    ASSERT_STREQ(test01.c_str(), "hello-stdout\n");
    
    std::string test02 = sstd::system_stdout(R"(sh ./test/src_test/sys/stdlib_system_stderr.sh)");
    ASSERT_STREQ(test02.c_str(), "");
}
TEST(system_old_imp_delete_on_ver3xx, system_stdout_string){
    std::string test01 = sstd::system_stdout(std::string(R"(sh ./test/src_test/sys/stdlib_system_stdout.sh)"));
    ASSERT_STREQ(test01.c_str(), "hello-stdout\n");
    
    std::string test02 = sstd::system_stdout(std::string(R"(sh ./test/src_test/sys/stdlib_system_stderr.sh)"));
    ASSERT_STREQ(test02.c_str(), "");
}

TEST(system_old_imp_delete_on_ver3xx, system_stderr_char){
    std::string test01 = sstd::system_stderr(R"(sh ./test/src_test/sys/stdlib_system_stdout.sh)");
    ASSERT_STREQ(test01.c_str(), "");
    
    std::string test02 = sstd::system_stderr(R"(sh ./test/src_test/sys/stdlib_system_stderr.sh)");
    ASSERT_STREQ(test02.c_str(), "hello-stderr\n");
}
TEST(system_old_imp_delete_on_ver3xx, system_stderr_string){
    std::string test01 = sstd::system_stderr(std::string(R"(sh ./test/src_test/sys/stdlib_system_stdout.sh)"));
    ASSERT_STREQ(test01.c_str(), "");
    
    std::string test02 = sstd::system_stderr(std::string(R"(sh ./test/src_test/sys/stdlib_system_stderr.sh)"));
    ASSERT_STREQ(test02.c_str(), "hello-stderr\n");
}

TEST(system_old_imp_delete_on_ver3xx, system_stdout_stderr_char){
    std::string test01 = sstd::system_stdout_stderr(R"(sh ./test/src_test/sys/stdlib_system_stdout.sh)");
    ASSERT_STREQ(test01.c_str(), "hello-stdout\n");
    
    std::string test02 = sstd::system_stdout_stderr(R"(sh ./test/src_test/sys/stdlib_system_stderr.sh)");
    ASSERT_STREQ(test02.c_str(), "hello-stderr\n");
}
TEST(system_old_imp_delete_on_ver3xx, system_stdout_stderr_string){
    std::string test01 = sstd::system_stdout_stderr(std::string(R"(sh ./test/src_test/sys/stdlib_system_stdout.sh)"));
    ASSERT_STREQ(test01.c_str(), "hello-stdout\n");
    
    std::string test02 = sstd::system_stdout_stderr(std::string(R"(sh ./test/src_test/sys/stdlib_system_stderr.sh)"));
    ASSERT_STREQ(test02.c_str(), "hello-stderr\n");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
