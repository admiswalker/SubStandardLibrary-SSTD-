#include "print.hpp"
#include <stdio.h>

//===

void sstd::print(bool rhs){ printf("%s\n", (rhs ? "true" : "false")); }
void sstd::print(char rhs){ printf("%c\n", rhs); }

void sstd::print(int8 rhs){ printf("%d\n", rhs); }
void sstd::print(int16 rhs){ printf("%d\n", rhs); }
void sstd::print(int32 rhs){ printf("%d\n", rhs); }
void sstd::print(int64 rhs){ printf("%ld\n", rhs); }

void sstd::print(uint8 rhs){ printf("%u\n", rhs); }
void sstd::print(uint16 rhs){ printf("%u\n", rhs); }
void sstd::print(uint32 rhs){ printf("%u\n", rhs); }
void sstd::print(uint64 rhs){ printf("%lu\n", rhs); }

void sstd::print(float rhs){ printf("%f\n", rhs); }
void sstd::print(double rhs){ printf("%lf\n", rhs); }

void sstd::print(const char* rhs){ printf("%s\n", rhs); }
void sstd::print(const std::string& rhs){ printf("%s\n", rhs.c_str()); }

//===

#define sstd_print_vec(option, rhs)								\
	printf("[ ");												\
	for(uint i=0; i<rhs.size(); i++){ printf(option, rhs[i]); }	\
	printf("]\n")

#define sstd_print_vvec(option, rhs)									\
	printf("[ ");														\
	for(uint p=0; p<rhs.size(); p++){									\
		printf("[ "); for(uint q=0; q<rhs[p].size(); q++){ printf(option, rhs[p][q]); } printf("] "); \
	}																	\
	printf("]\n")

void sstd::print(const std::vector<bool>& rhs){
	printf("[ ");
	for(uint i=0; i<rhs.size(); i++){ printf("%c ", (rhs[i] ? 'T' : 'F')); }
	printf("]\n");
}
void sstd::print(const std::vector<char>& rhs){ sstd_print_vec("%c ", rhs); }  // 文字として表示 printf("%c", rhs[i]);

void sstd::print(const std::vector<int8>& rhs){ sstd_print_vec("%d ", rhs); }
void sstd::print(const std::vector<int16>& rhs){ sstd_print_vec("%d ", rhs); }
void sstd::print(const std::vector<int32>& rhs){ sstd_print_vec("%d ", rhs); }
void sstd::print(const std::vector<int64>& rhs){ sstd_print_vec("%ld ", rhs); }

void sstd::print(const std::vector<uint8>& rhs){ sstd_print_vec("%u ", rhs); }
void sstd::print(const std::vector<uint16>& rhs){ sstd_print_vec("%u ", rhs); }
void sstd::print(const std::vector<uint32>& rhs){ sstd_print_vec("%u ", rhs); }
void sstd::print(const std::vector<uint64>& rhs){ sstd_print_vec("%lu ", rhs); }

void sstd::print(const std::vector<float>& rhs){ sstd_print_vec("%f ", rhs); }
void sstd::print(const std::vector<double>& rhs){ sstd_print_vec("%lf ", rhs); }

void sstd::print(const std::vector<std::string>& rhs){
	if(rhs.size()==0){ printf("[ empty ]\n"); }
	printf("[ ");
	for(uint i=0; i<rhs.size(); i++){ printf("[ %s ] ", rhs[i].c_str()); }
	printf("]\n");
}

//===

void sstd::print(const std::vector<std::vector<bool>>& rhs){
	printf("[ ");
	for(uint p=0; p<rhs.size(); p++){
		printf("[ "); for(uint q=0; q<rhs[p].size(); q++){ printf("%c ", (rhs[p][q] ? 'T' : 'F')); } printf("] ");
	}
	printf("]\n");
}
void sstd::print(const std::vector<std::vector<char>>& rhs){ sstd_print_vvec("%c ", rhs); }  // 文字として表示 printf("%c", rhs[i]);

void sstd::print(const std::vector<std::vector<int8>>& rhs){ sstd_print_vvec("%d ", rhs); }
void sstd::print(const std::vector<std::vector<int16>>& rhs){ sstd_print_vvec("%d ", rhs); }
void sstd::print(const std::vector<std::vector<int32>>& rhs){ sstd_print_vvec("%d ", rhs); }
void sstd::print(const std::vector<std::vector<int64>>& rhs){ sstd_print_vvec("%ld ", rhs); }

void sstd::print(const std::vector<std::vector<uint8>>& rhs){ sstd_print_vvec("%u ", rhs); }
void sstd::print(const std::vector<std::vector<uint16>>& rhs){ sstd_print_vvec("%u ", rhs); }
void sstd::print(const std::vector<std::vector<uint32>>& rhs){ sstd_print_vvec("%u ", rhs); }
void sstd::print(const std::vector<std::vector<uint64>>& rhs){ sstd_print_vvec("%lu ", rhs); }

void sstd::print(const std::vector<std::vector<float>>& rhs){ sstd_print_vvec("%f ", rhs); }
void sstd::print(const std::vector<std::vector<double>>& rhs){ sstd_print_vvec("%lf ", rhs); }

void sstd::print(const std::vector<std::vector<std::string>>& rhs){
	if(rhs.size()==0){ printf("[ [ empty ] ]\n"); }
	printf("[ ");
	for(uint p=0; p<rhs.size(); p++){
		printf("[ "); for(uint q=0; q<rhs[p].size(); q++){ printf("%s ", rhs[p][q].c_str()); } printf("] ");
	}
	printf("]\n");
}

//==============================================================================================================================

void sstd::for_printn(const char* rhs){ printf(" = %s\n", rhs); }

void sstd::for_printn(bool rhs){ printf(" = %s\n", (rhs ? "true" : "false")); }
void sstd::for_printn(char rhs){ printf(" = %c\n", rhs); }

void sstd::for_printn(int8 rhs){ printf(" = %d\n", rhs); }
void sstd::for_printn(int16 rhs){ printf(" = %d\n", rhs); }
void sstd::for_printn(int32 rhs){ printf(" = %d\n", rhs); }
void sstd::for_printn(int64 rhs){ printf(" = %ld\n", rhs); }

void sstd::for_printn(uint8 rhs){ printf(" = %u\n", rhs); }
void sstd::for_printn(uint16 rhs){ printf(" = %u\n", rhs); }
void sstd::for_printn(uint32 rhs){ printf(" = %u\n", rhs); }
void sstd::for_printn(uint64 rhs){ printf(" = %lu\n", rhs); }

void sstd::for_printn(float rhs){ printf(" = %f\n", rhs); }
void sstd::for_printn(double rhs){ printf(" = %lf\n", rhs); }

void sstd::for_printn(const std::string& rhs){ printf(" = %s\n", rhs.c_str()); }

#define sstd_for_printn_vec(option, rhs)\
	printf("[%lu] = [ ", rhs.size());\
	for(uint i=0; i<rhs.size(); i++){ printf(option, rhs[i]); }\
	printf("]\n")

#define sstd_for_printn_vvec(option, rhs)\
	printf("[%lu] = [ ", rhs.size());\
	for(uint p=0; p<rhs.size(); p++){\
		printf("[ "); for(uint q=0; q<rhs[p].size(); q++){ printf(option, rhs[p][q]); } printf("] ");\
	}\
	printf("]\n")

void sstd::for_printn(const std::vector<bool>& rhs){
	printf("[%lu] = [ ", rhs.size());
	for(uint i=0; i<rhs.size(); i++){ printf("%c ", (rhs[i] ? 'T' : 'F')); }
	printf("]\n");
}
void sstd::for_printn(const std::vector<char>& rhs){ sstd_for_printn_vec("%c ", rhs); }  // 文字として表示 printf("%c", rhs[i]);

void sstd::for_printn(const std::vector<int8>& rhs){ sstd_for_printn_vec("%d ", rhs); }
void sstd::for_printn(const std::vector<int16>& rhs){ sstd_for_printn_vec("%d ", rhs); }
void sstd::for_printn(const std::vector<int32>& rhs){ sstd_for_printn_vec("%d ", rhs); }
void sstd::for_printn(const std::vector<int64>& rhs){ sstd_for_printn_vec("%ld ", rhs); }

void sstd::for_printn(const std::vector<uint8>& rhs){ sstd_for_printn_vec("%u ", rhs); }
void sstd::for_printn(const std::vector<uint16>& rhs){ sstd_for_printn_vec("%u ", rhs); }
void sstd::for_printn(const std::vector<uint32>& rhs){ sstd_for_printn_vec("%u ", rhs); }
void sstd::for_printn(const std::vector<uint64>& rhs){ sstd_for_printn_vec("%lu ", rhs); }

void sstd::for_printn(const std::vector<float>& rhs){ sstd_for_printn_vec("%f ", rhs); }
void sstd::for_printn(const std::vector<double>& rhs){ sstd_for_printn_vec("%lf ", rhs); }

void sstd::for_printn(const std::vector<std::string>& rhs){
	printf("[%lu] = [ ", rhs.size());
	for(uint i=0; i<rhs.size(); i++){ printf("[ %s ] ", rhs[i].c_str()); }
	printf("]\n");
}

//===

void sstd::for_printn(const std::vector<std::vector<bool>>& rhs){
	printf("[%lu] = [ ", rhs.size());
	for(uint p=0; p<rhs.size(); p++){
		printf("[ "); for(uint q=0; q<rhs[p].size(); q++){ printf("%c ", (rhs[p][q] ? 'T' : 'F')); } printf("] ");
	}
	printf("]\n");
}
void sstd::for_printn(const std::vector<std::vector<char>>& rhs){ sstd_for_printn_vvec("%c ", rhs); }  // 文字として表示 printf("%c", rhs[i]);

void sstd::for_printn(const std::vector<std::vector<int8>>& rhs){ sstd_for_printn_vvec("%d ", rhs); }
void sstd::for_printn(const std::vector<std::vector<int16>>& rhs){ sstd_for_printn_vvec("%d ", rhs); }
void sstd::for_printn(const std::vector<std::vector<int32>>& rhs){ sstd_for_printn_vvec("%d ", rhs); }
void sstd::for_printn(const std::vector<std::vector<int64>>& rhs){ sstd_for_printn_vvec("%ld ", rhs); }

void sstd::for_printn(const std::vector<std::vector<uint8>>& rhs){ sstd_for_printn_vvec("%u ", rhs); }
void sstd::for_printn(const std::vector<std::vector<uint16>>& rhs){ sstd_for_printn_vvec("%u ", rhs); }
void sstd::for_printn(const std::vector<std::vector<uint32>>& rhs){ sstd_for_printn_vvec("%u ", rhs); }
void sstd::for_printn(const std::vector<std::vector<uint64>>& rhs){ sstd_for_printn_vvec("%lu ", rhs); }

void sstd::for_printn(const std::vector<std::vector<float>>& rhs){ sstd_for_printn_vvec("%f ", rhs); }
void sstd::for_printn(const std::vector<std::vector<double>>& rhs){ sstd_for_printn_vvec("%lf ", rhs); }

void sstd::for_printn(const std::vector<std::vector<std::string>>& rhs){
	printf(" = [ ");
	for(uint p=0; p<rhs.size(); p++){
		printf("[ "); for(uint q=0; q<rhs[p].size(); q++){ printf("%s ", rhs[p][q].c_str()); } printf("] ");
	}
	printf("]\n");
}
