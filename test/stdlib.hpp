#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(stdlib, system_char){
    int ret;
    testing::internal::CaptureStdout();
    ret = sstd::system("ls"); if(WIFEXITED(ret)<=0){ printf("ERROR:\n"); } // <- want to test this line
    std::string test = testing::internal::GetCapturedStdout();
    
    testing::internal::CaptureStdout();
    ret = system("ls"); if(WIFEXITED(ret)<=0){ printf("ERROR:\n"); }
    std::string ans = testing::internal::GetCapturedStdout();
    
    ASSERT_STREQ(test.c_str(), ans.c_str());
}
TEST(stdlib, system_string){
    int ret;
    testing::internal::CaptureStdout();
    ret = sstd::system(std::string("ls")); if(WIFEXITED(ret)<=0){ printf("ERROR:\n"); }// <- want to test this line
    std::string test = testing::internal::GetCapturedStdout();
    
    testing::internal::CaptureStdout();
    ret = system("ls"); if(WIFEXITED(ret)<=0){ printf("ERROR:\n"); }
    std::string ans = testing::internal::GetCapturedStdout();
    
    ASSERT_STREQ(test.c_str(), ans.c_str());
}

TEST(stdlib, system_stdout_char){
    std::string test01 = sstd::system_stdout(R"(sh ./test/stdlib_system_stdout.sh)");
    ASSERT_STREQ(test01.c_str(), "hello-stdout\n");
    
    std::string test02 = sstd::system_stdout(R"(sh ./test/stdlib_system_stderr.sh)");
    ASSERT_STREQ(test02.c_str(), "");
}
TEST(stdlib, system_stdout_string){
    std::string test01 = sstd::system_stdout(std::string(R"(sh ./test/stdlib_system_stdout.sh)"));
    ASSERT_STREQ(test01.c_str(), "hello-stdout\n");
    
    std::string test02 = sstd::system_stdout(std::string(R"(sh ./test/stdlib_system_stderr.sh)"));
    ASSERT_STREQ(test02.c_str(), "");
}

TEST(stdlib, system_stderr_char){
    std::string test01 = sstd::system_stderr(R"(sh ./test/stdlib_system_stdout.sh)");
    ASSERT_STREQ(test01.c_str(), "");
    
    std::string test02 = sstd::system_stderr(R"(sh ./test/stdlib_system_stderr.sh)");
    ASSERT_STREQ(test02.c_str(), "hello-stderr\n");
}
TEST(stdlib, system_stderr_string){
    std::string test01 = sstd::system_stderr(std::string(R"(sh ./test/stdlib_system_stdout.sh)"));
    ASSERT_STREQ(test01.c_str(), "");
    
    std::string test02 = sstd::system_stderr(std::string(R"(sh ./test/stdlib_system_stderr.sh)"));
    ASSERT_STREQ(test02.c_str(), "hello-stderr\n");
}

TEST(stdlib, system_stdout_stderr_char){
    std::string test01 = sstd::system_stdout_stderr(R"(sh ./test/stdlib_system_stdout.sh)");
    ASSERT_STREQ(test01.c_str(), "hello-stdout\n");
    
    std::string test02 = sstd::system_stdout_stderr(R"(sh ./test/stdlib_system_stderr.sh)");
    ASSERT_STREQ(test02.c_str(), "hello-stderr\n");
}
TEST(stdlib, system_stdout_stderr_string){
    std::string test01 = sstd::system_stdout_stderr(std::string(R"(sh ./test/stdlib_system_stdout.sh)"));
    ASSERT_STREQ(test01.c_str(), "hello-stdout\n");
    
    std::string test02 = sstd::system_stdout_stderr(std::string(R"(sh ./test/stdlib_system_stderr.sh)"));
    ASSERT_STREQ(test02.c_str(), "hello-stderr\n");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

