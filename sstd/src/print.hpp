#pragma once
#include <string>
#include <vector>
#include "typeDef.h"

namespace sstd{
	void print(const bool rhs);
	void print(const char rhs);
	void print(const int8 rhs);
	void print(const int16 rhs);
	void print(const int32 rhs);
	void print(const int64 rhs);
	void print(const uint8 rhs);
	void print(const uint16 rhs);
	void print(const uint32 rhs);
	void print(const uint64 rhs);
	void print(const float rhs);
	void print(const double rhs);
	void print(const char* rhs);
	void print(const std::string& rhs);
	
	void print(const std::vector<bool>& rhs);
	void print(const std::vector<char>& rhs);  // 文字として表示 printf("%c", rhs[i]);
	void print(const std::vector<int8>& rhs);
	void print(const std::vector<int16>& rhs);
	void print(const std::vector<int32>& rhs);
	void print(const std::vector<int64>& rhs);
	void print(const std::vector<uint8>& rhs);
	void print(const std::vector<uint16>& rhs);
	void print(const std::vector<uint32>& rhs);
	void print(const std::vector<uint64>& rhs);
	void print(const std::vector<float>& rhs);
	void print(const std::vector<double>& rhs);
	void print(const std::vector<std::string>& rhs);
	
	void print(const std::vector<std::vector<bool>>& rhs);
	void print(const std::vector<std::vector<char>>& rhs);  // 文字として表示 printf("%c", rhs[i]);
	void print(const std::vector<std::vector<int8>>& rhs);
	void print(const std::vector<std::vector<int16>>& rhs);
	void print(const std::vector<std::vector<int32>>& rhs);
	void print(const std::vector<std::vector<int64>>& rhs);
	void print(const std::vector<std::vector<uint8>>& rhs);
	void print(const std::vector<std::vector<uint16>>& rhs);
	void print(const std::vector<std::vector<uint32>>& rhs);
	void print(const std::vector<std::vector<uint64>>& rhs);
	void print(const std::vector<std::vector<float>>& rhs);
	void print(const std::vector<std::vector<double>>& rhs);
	void print(const std::vector<std::vector<std::string>>& rhs);
	
	//---
	
	void for_printn(bool rhs);
	void for_printn(char rhs);
	void for_printn(int8 rhs);
	void for_printn(int16 rhs);
	void for_printn(int32 rhs);
	void for_printn(int64 rhs);
	void for_printn(uint8 rhs);
	void for_printn(uint16 rhs);
	void for_printn(uint32 rhs);
	void for_printn(uint64 rhs);
	void for_printn(float rhs);
	void for_printn(double rhs);
	void for_printn(const char* rhs);
	void for_printn(const std::string& rhs);
	
	void for_printn(const std::vector<bool>& rhs);
	void for_printn(const std::vector<char>& rhs);  // 文字として表示 for_printnf("%c", rhs[i]);
	void for_printn(const std::vector<int8>& rhs);
	void for_printn(const std::vector<int16>& rhs);
	void for_printn(const std::vector<int32>& rhs);
	void for_printn(const std::vector<int64>& rhs);
	void for_printn(const std::vector<uint8>& rhs);
	void for_printn(const std::vector<uint16>& rhs);
	void for_printn(const std::vector<uint32>& rhs);
	void for_printn(const std::vector<uint64>& rhs);
	void for_printn(const std::vector<float>& rhs);
	void for_printn(const std::vector<double>& rhs);
	void for_printn(const std::vector<std::string>& rhs);
	
	void for_printn(const std::vector<std::vector<bool>>& rhs);
	void for_printn(const std::vector<std::vector<char>>& rhs);  // 文字として表示 for_printnf("%c", rhs[i]);
	void for_printn(const std::vector<std::vector<int8>>& rhs);
	void for_printn(const std::vector<std::vector<int16>>& rhs);
	void for_printn(const std::vector<std::vector<int32>>& rhs);
	void for_printn(const std::vector<std::vector<int64>>& rhs);
	void for_printn(const std::vector<std::vector<uint8>>& rhs);
	void for_printn(const std::vector<std::vector<uint16>>& rhs);
	void for_printn(const std::vector<std::vector<uint32>>& rhs);
	void for_printn(const std::vector<std::vector<uint64>>& rhs);
	void for_printn(const std::vector<std::vector<float>>& rhs);
	void for_printn(const std::vector<std::vector<double>>& rhs);
	void for_printn(const std::vector<std::vector<std::string>>& rhs);
}

//====================================================================================================
//====================================================================================================

namespace sstd{
	inline void printn_dummy(){}
	
	inline void printn(...){}
	inline void printn_all(...){}
}

#define printn(var) printn_dummy();{printf("%s", #var);sstd::for_printn(var);}
#define printn_all(var) printn_dummy();{printf("%s(%d): %s", __func__, __LINE__, #var);sstd::for_printn(var);}
#define printn_fflv(var) printn_dummy();{printf("%s: %s(%d): %s", __FILE__, __func__, __LINE__, #var);sstd::for_printn(var);}

