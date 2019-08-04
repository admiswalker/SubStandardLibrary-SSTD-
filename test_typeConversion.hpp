#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(typeConversion, str2int){
	std::string s = "1234";
	int ans = 1234;
	int i = sstd::str2int(s);
	ASSERT_TRUE(i == ans);
}

//---

TEST(typeConversion, str2double){
	std::string s = "1.234";
	double ans = 1.234;
	double d = sstd::str2double(s);
	ASSERT_TRUE(d == ans);
}
TEST(typeConversion, str2double_vec){
	std::vector<std::string> vecStr = {"1.234", "2.345", "3.456"};
	std::vector<double> vecAns = {1.234, 2.345, 3.456};
	
	std::vector<double> vecDouble = sstd::str2double(vecStr);
	ASSERT_TRUE(vecDouble == vecAns);
}
TEST(typeConversion, str2double_vvec){
	std::vector<std::vector<std::string>> vvecStr = {{"1.234", "2.345", "3.456"}, {"7.8", "8.9"}, {"10.1", "11.2", "12.3"}};
	std::vector<std::vector<double>> vvecAns = {{1.234, 2.345, 3.456}, {7.8, 8.9}, {10.1, 11.2, 12.3}};
	
	std::vector<std::vector<double>> vvecDouble = sstd::str2double(vvecStr);
	ASSERT_TRUE(vvecDouble == vvecAns);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

//---

TEST(typeConversion, double2str){
	double d = 1.234;
	std::string s = sstd::double2str(d);
	std::string ans = "1.234000";
	ASSERT_TRUE(s == ans);
}
TEST(typeConversion, double2str_vec){
	std::vector<double> vecStr = {1.234, 2.345, 3.456};
	std::vector<std::string> vecAns = {"1.234000", "2.345000", "3.456000"};
	
	std::vector<std::string> vecDouble = sstd::double2str(vecStr);
	ASSERT_TRUE(vecDouble == vecAns);
}
TEST(typeConversion, double2str_vvec){
	std::vector<std::vector<double>> vvecStr = {{1.234, 2.345, 3.456}, {7.8, 8.9}, {10.1, 11.2, 12.3}};
	std::vector<std::vector<std::string>> vvecAns = {{"1.234000", "2.345000", "3.456000"}, {"7.800000", "8.900000"}, {"10.100000", "11.200000", "12.300000"}};
	
	std::vector<std::vector<std::string>> vvecDouble = sstd::double2str(vvecStr);
	ASSERT_TRUE(vvecDouble == vvecAns);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

