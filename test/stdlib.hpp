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

//-----------------------------------------------------------------------------------------------------------------------------------------------

