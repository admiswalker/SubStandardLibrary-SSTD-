#define DEBUG
//#define use_sstd_pause		// Enable to switch "Pause" or "Not Pause" by "#define UseSysPause".
#define use_sstd_pauseIfWin32	// Enable to switch "Pause" or "Not Pause" by "#define UsePauseIfWin32".
#ifdef _WIN32
	#include "./sstd/sstd.hpp"
#else
	#include <sstd/sstd.hpp>
#endif

#include <gtest/gtest.h>

//-----------------------------------------------------------------------------------------------------------------------------------------------
// 順次 google test へ移行すること．

// sstd/src
//#include "test_measureTime.hpp"
void TEST_time();
void TEST_typeDef();
void TEST_pdbg();
// void pdbg(){ printf("======p\n"); } // #define DEBUG を定義しない場合でも，マクロでこの名前は使えなくなるので，名前空間を汚しており，本当はよくない．
//#include "./test_print_printn_printn_all.hpp"
void TEST_math();
void TEST_signal();
void TEST_file();
void TEST_file_c();
void TEST_mkdir();
void TEST_rm();
void TEST_str2num();
void TEST_ssprintf();
void TEST_strmatch();
void TEST_path();
void TEST_getFilePathInDir();
void TEST_strEdit();        // テストを書くように．
void TEST_tinyInterpreter();
void TEST_parseCSV();
void TEST_encode_decode();
void TEST_hashFnc();
void TEST_pause();
#include "./test_c2py.hpp"

// stdVector_expansion of operators
void TEST_stdVector_expansion();

// sstd/src/MatrixStore_mat
void TEST_mat_colMajor();
void TEST_mat_rowMajor();
void TEST_bmat();

//-----------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char** argv){
	printf("\n");
	printf("+---------------------------------------------------+\n");
	printf("|                                                   |\n");
	printf("|     Welcome to Sub Standard Library (SSTD) !      |\n");
	printf("|                                                   |\n");
	printf("+---------------------------------------------------+\n");
	printf("\n");
	printf("■ measureTime_start---------------\n\n"); time_m timem; sstd::measureTime_start(timem);
	::testing::InitGoogleTest(&argc, argv);
	
	auto ret = RUN_ALL_TESTS();
	
//	TEST_time();
//	TEST_typeDef();
//	TEST_pdbg();
//	TEST_math();
//	TEST_signal();
//	TEST_file();
//	TEST_file_c();
//	TEST_mkdir();
//	TEST_rm();
//	TEST_str2num();
//	TEST_ssprintf();
//	TEST_strmatch();
//	TEST_path();
//	TEST_getFilePathInDir();
//	TEST_strEdit();        // テストを書くように．
//	TEST_tinyInterpreter();
//	TEST_parseCSV();
//	TEST_encode_decode();
//	TEST_hashFnc();
//	TEST_pause();
	
//	TEST_stdVector_expansion();
	
//	TEST_mat_colMajor(); // TODO: write tests (zeros, Tr) // sstd::print 関数のテストを書くように
//	TEST_mat_rowMajor(); // TODO: write tests (zeros, Tr) // sstd::print 関数のテストを書くように
//	TEST_bmat();
	
	printf("\n");
	printf("■ measureTime_stop----------------\n");
	sstd::measureTime_stop_print(timem);
	sstd::pauseIfWin32();
	return ret;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

void TEST_time(){
	printf("■ time\n");
	time_t      c_time    = time(0); // get current time
	struct tm   c_tm      = sstd::time2tm(c_time);
	time_t      c_time_2  = sstd::tm2time(c_tm);
	double      unixday   = sstd::time2unixday(c_time);
	double      unixday_2 = sstd::tm2unixday(c_tm);
	printf("GMT: %s\n", sstd::tm2str(c_tm).c_str());
	printf("GMT: %s\n", sstd::time2str(c_time_2).c_str());
	printf("unixday: %lf\n", unixday);
	printf("unixday: %lf\n", unixday_2);
	printf("\n");

	struct tm   c_tm_l   = sstd::timeGm2tmLocal(c_time);
	time_t      c_time_3 = sstd::tmLocal2timeGm(c_tm_l);
	printf("local: %s\n",  sstd::tm2str(c_tm_l).c_str());
	printf("GMT: %s\n",    sstd::time2str(c_time_3).c_str());
	printf("\n");
	
	time_t c_time_yday  = sstd::yday2time(c_tm.tm_year+1900, c_tm.tm_yday+1);
	printf("GMT: %s\n",   sstd::time2str(c_time_yday).c_str());
	struct tm c_tm_yday = sstd::yday2tm(c_tm.tm_year+1900, c_tm.tm_yday+1);
	printf("GMT: %s\n",   sstd::tm2str(c_tm_yday).c_str());
	printf("\n");

	struct timeval time_sec_micro = sstd::getTimeval();
	printf("timeval: %lf\n",(time_sec_micro.tv_sec)+(time_sec_micro.tv_usec*1.0E-6));

	sstd::print(c_tm_yday);
	sstd::printn(c_tm_yday);
	sstd::printn_all(c_tm_yday);
}
void TEST_typeDef(){
	printf("■ typeDef\n");
	uchar   uc =  1; printf("uchar:  %u\n",     uc);
	uint    ui =  2; printf("uint:   %u\n",     ui);
	uint8   u8 =  8; printf("uint8:  %u\n",     u8);
	uint16 u16 = 16; printf("uint16: %u\n",    u16);
	uint32 u32 = 32; printf("uint32: %u\n",    u32);
	uint64 u64 = 64; printf("uint64: %lu\n\n", u64);
}
void TEST_pdbg(){
	printf("■ #define DEBUG\n");
	printf("  □ pdbg (printf debugger)\n");
	sstd::pdbg("abc\n");
	printf("true: "); sstd::pdbg_if(true, "print txt"); printf("\n");
	printf("false: "); sstd::pdbg_if(false, "not print txt"); printf("\n");
//	printf("true: "); sstd::pdbg_if_exit(true, "exit");
	printf("false: "); sstd::pdbg_if_exit(false, "not exit"); printf("\n");
//	printf("true: "); sstd::pdbg_if_stop_exit(true, "exit"); printf("\n");
//	printf("false: "); sstd::pdbg_if_stop_exit(false, "not exit"); printf("\n");
	sstd::dbg(printf("run debug code."););
	sstd::ndbg(printf("run ndebug code."););
	printf("\n");
}
#define TEST_vec_sort_sort_de(Type)									\
	std::vector<Type> buf = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4};	\
	std::vector<Type> sortDe = sstd::sort_de(buf);					\
	sstd::printn(sortDe);											\
	sstd::printn(sstd::sort(sortDe));								\
	printf("\n");
#define TEST_vec_sort_sort_de_u(Type)								\
	std::vector<Type> buf = {0, 1, 2, 3, 4};						\
	std::vector<Type> sortDe = sstd::sort_de(buf);					\
	sstd::printn(sortDe);											\
	sstd::printn(sstd::sort(sortDe));								\
	printf("\n");
void TEST_math(){
	printf("■ math\n");
		// 偶数への丸め (round to even)
	float  re_f1 = sstd::round2even(1.5); printf("round to even: %lf ≒ %lf\n", 1.5, re_f1);
	float  re_f2 = sstd::round2even(2.5); printf("round to even: %lf ≒ %lf\n", 2.5, re_f2);
	double re_d1 = sstd::round2even(1.5); printf("round to even: %lf ≒ %lf\n", 1.5, re_d1);
	double re_d2 = sstd::round2even(2.5); printf("round to even: %lf ≒ %lf\n", 2.5, re_d2);
		// 奇数への丸め (round to odd)
	float  ro_f1 = sstd::round2odd(1.5); printf("round to odd: %lf ≒ %lf\n", 1.5, ro_f1);
	float  ro_f2 = sstd::round2odd(2.5); printf("round to odd: %lf ≒ %lf\n", 2.5, ro_f2);
	double ro_d1 = sstd::round2odd(1.5); printf("round to odd: %lf ≒ %lf\n", 1.5, ro_d1);
	double ro_d2 = sstd::round2odd(2.5); printf("round to odd: %lf ≒ %lf\n", 2.5, ro_d2);
	printf("\n");

	std::vector<float> buf_f = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4};
	sstd::printn(buf_f);
	printf("sum: %f\n", sstd::sum(buf_f));
	printf("sum_abs: %f\n", sstd::sum_abs(buf_f));
	printf("ave: %f\n", sstd::ave(buf_f));
	printf("ave in the first 2 elements: %f\n", sstd::ave(buf_f, 2));
	printf("med: %f\n", sstd::med(buf_f));
	printf("max: %f\n", sstd::max(buf_f));
	printf("max_abs: %f\n", sstd::max_abs(buf_f));
	printf("min: %f\n", sstd::min(buf_f));
	printf("min_abs: %f\n", sstd::min_abs(buf_f));
	printf("var: %f\n", sstd::var(buf_f));
	printf("var_p: %f\n", sstd::var_p(buf_f));
	printf("stdev: %f\n", sstd::stdev(buf_f));
	printf("stdev_p: %f\n", sstd::stdev_p(buf_f));
	printf("\n");
	std::vector<float> sortDe_f = sstd::sort_de(buf_f);
	sstd::printn(sortDe_f);
	sstd::printn(sstd::sort(sortDe_f));
	printf("\n");
	
	std::vector<double> buf_d = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4};
	sstd::printn(buf_d);
	printf("sum: %f\n", sstd::sum(buf_d));
	printf("sum_abs: %f\n", sstd::sum_abs(buf_d));
	printf("ave: %f\n", sstd::ave(buf_d));
	printf("ave in the first 2 elements: %f\n", sstd::ave(buf_d, 2));
	printf("med: %f\n", sstd::med(buf_d));
	printf("max: %f\n", sstd::max(buf_d));
	printf("max_abs: %f\n", sstd::max_abs(buf_d));
	printf("min: %f\n", sstd::min(buf_d));
	printf("min_abs: %f\n", sstd::min_abs(buf_d));
	printf("var: %f\n", sstd::var(buf_d));
	printf("var_p: %f\n", sstd::var_p(buf_d));
	printf("stdev: %f\n", sstd::stdev(buf_d));
	printf("stdev_p: %f\n", sstd::stdev_p(buf_d));
	printf("\n");
	std::vector<double> sortDe_d = sstd::sort_de(buf_d);
	sstd::printn(sortDe_d);
	sstd::printn(sstd::sort(sortDe_d));
	printf("\n");

	/* test: Kahan summation algorithm 01 */
	std::vector<float> buf_f2 = {100000.0f, 0.0125f, 0.0125f, 0.0125f, 0.0125f, 0.0125f, 0.0125f, 0.0125f, 0.0125f}; // float の有効桁数 = 24/1og2(10) ≒ 7.224 ≒ 7
	printf("sum: %lf\n", sstd::sum(buf_f2));
	std::vector<double> buf_d2 = {100000000000000.0, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125}; // double の有効桁数 = 24/1og2(10) ≒ 15.955 ≒ 15
	printf("sum: %lf\n", sstd::sum(buf_d2));
	printf("\n");
	
	/* test: Kahan summation algorithm 02 */
	/*
	double d1=100000000.0;
	double d2=0.000000001;
	for(uint i=0; i<1000000000; i++){ d1+=d2; }
	printf("normal sum: %lf\n", d1);

	double lhs=d1;
	double del=0;
	for(uint i=0; i<1000000000; i++){
		double r1=d2-del;
		double r2=lhs+r1;
		del=(r2-lhs)-r1;
		lhs=r2;
	}
	printf(" Kahan sum: %lf\n", lhs);
	printf("\n");
	*/

	// get a list of prime number under rhs.
	std::vector<uint64> primeList = sstd::prime((uint)100);
	printf("primeList = "); sstd::print(primeList);
	printf("\n");

	uint64 fact_num = 2*2*3*3*5*5;
	std::vector<struct sstd::fact> factList = sstd::factor(fact_num);
	printf("%lu = %lu^%lu", fact_num, factList[0].prime, factList[0].num);
	for(uint i=1; i<factList.size(); i++){ printf(" + %lu^%lu", factList[i].prime, factList[i].num); }
	sstd::print(factList);
	sstd::printn(factList);
	sstd::printn_all(factList);
	printf("\n");

	uint div_num = 2*2*3*3*5*5;
	std::vector<uint64> divList = sstd::divisor(div_num);
	printf("divList = "); sstd::print(divList);
	printf("divList = "); sstd::print(sstd::divisor(factList));
	printf("\n");

	uint   ui  = sstd::pow((  uint)2, (  uint) 4); printf("%u\n",  ui );
	uint8  u8  = sstd::pow(( uint8)2, ( uint8) 4); printf("%u\n",  u8 );
	uint16 u16 = sstd::pow((uint16)2, (uint16) 8); printf("%u\n",  u16);
	uint32 u32 = sstd::pow((uint32)2, (uint32) 9); printf("%u\n",  u32);
	uint64 u64 = sstd::pow((uint64)2, (uint64)10); printf("%lu\n", u64);
	printf("\n");

	//-------------------------------------------------------------------------------------------------------------------------------------------
	
	{ std::vector< char > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("max: %i\n",  sstd::max(buf)); }
	{ std::vector< int8 > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("max: %i\n",  sstd::max(buf)); }
	{ std::vector< int16> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("max: %i\n",  sstd::max(buf)); }
	{ std::vector< int32> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("max: %i\n",  sstd::max(buf)); }
	{ std::vector< int64> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("max: %li\n", sstd::max(buf)); }
//	{ std::vector<uchar > buf={               0,1,2,3,4}; printf("max: %u\n",  sstd::max(buf)); }
	{ std::vector<uint8 > buf={               0,1,2,3,4}; printf("max: %u\n",  sstd::max(buf)); }
	{ std::vector<uint16> buf={               0,1,2,3,4}; printf("max: %u\n",  sstd::max(buf)); }
	{ std::vector<uint32> buf={               0,1,2,3,4}; printf("max: %u\n",  sstd::max(buf)); }
	{ std::vector<uint64> buf={               0,1,2,3,4}; printf("max: %lu\n", sstd::max(buf)); }
	printf("\n");
	
	{ std::vector< char > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("max_abs: %i\n",  sstd::max_abs(buf)); }
	{ std::vector< int8 > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("max_abs: %i\n",  sstd::max_abs(buf)); }
	{ std::vector< int16> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("max_abs: %i\n",  sstd::max_abs(buf)); }
	{ std::vector< int32> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("max_abs: %i\n",  sstd::max_abs(buf)); }
	{ std::vector< int64> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("max_abs: %li\n", sstd::max_abs(buf)); }
	printf("\n");
	
	{ std::vector< char > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("min: %i\n",  sstd::min(buf)); }
	{ std::vector< int8 > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("min: %i\n",  sstd::min(buf)); }
	{ std::vector< int16> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("min: %i\n",  sstd::min(buf)); }
	{ std::vector< int32> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("min: %i\n",  sstd::min(buf)); }
	{ std::vector< int64> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("min: %li\n", sstd::min(buf)); }
//	{ std::vector<uchar > buf={               0,1,2,3,4}; printf("min: %u\n",  sstd::min(buf)); }
	{ std::vector<uint8 > buf={               0,1,2,3,4}; printf("min: %u\n",  sstd::min(buf)); }
	{ std::vector<uint16> buf={               0,1,2,3,4}; printf("min: %u\n",  sstd::min(buf)); }
	{ std::vector<uint32> buf={               0,1,2,3,4}; printf("min: %u\n",  sstd::min(buf)); }
	{ std::vector<uint64> buf={               0,1,2,3,4}; printf("min: %lu\n", sstd::min(buf)); }
	printf("\n");
	
	{ std::vector< char > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("min_abs: %i\n",  sstd::min_abs(buf)); }
	{ std::vector< int8 > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("min_abs: %i\n",  sstd::min_abs(buf)); }
	{ std::vector< int16> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("min_abs: %i\n",  sstd::min_abs(buf)); }
	{ std::vector< int32> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("min_abs: %i\n",  sstd::min_abs(buf)); }
	{ std::vector< int64> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; printf("min_abs: %li\n", sstd::min_abs(buf)); }
	printf("\n");
	
	{ sstd::mat_c< char > buf={{-2, -1}, {0, 1}};           printf("max: %i\n",  sstd::max(buf)); }
	{ sstd::mat_c< int8 > buf={{-2, -1}, {0, 1}};           printf("max: %i\n",  sstd::max(buf)); }
	{ sstd::mat_c< int16> buf={{-2, -1}, {0, 1}};           printf("max: %i\n",  sstd::max(buf)); }
	{ sstd::mat_c< int32> buf={{-2, -1}, {0, 1}};           printf("max: %i\n",  sstd::max(buf)); }
	{ sstd::mat_c< int64> buf={{-2, -1}, {0, 1}};           printf("max: %li\n", sstd::max(buf)); }
	{ sstd::mat_c<uint8 > buf={{ 0,  1}, {2, 3}};           printf("max: %u\n",  sstd::max(buf)); }
	{ sstd::mat_c<uint16> buf={{ 0,  1}, {2, 3}};           printf("max: %u\n",  sstd::max(buf)); }
	{ sstd::mat_c<uint32> buf={{ 0,  1}, {2, 3}};           printf("max: %u\n",  sstd::max(buf)); }
	{ sstd::mat_c<uint64> buf={{ 0,  1}, {2, 3}};           printf("max: %lu\n", sstd::max(buf)); }
	{ sstd::mat_c< float> buf={{-2, -1}, {0, 1}};           printf("max: %f\n",  sstd::max(buf)); }
	{ sstd::mat_c<double> buf={{-2, -1}, {0, 1}};           printf("max: %lf\n", sstd::max(buf)); }
	printf("\n");
	
	{ sstd::mat_r< char > buf={{-2, -1}, {0, 1}};         printf("max: %i\n",  sstd::max(buf)); }
	{ sstd::mat_r< int8 > buf={{-2, -1}, {0, 1}};         printf("max: %i\n",  sstd::max(buf)); }
	{ sstd::mat_r< int16> buf={{-2, -1}, {0, 1}};         printf("max: %i\n",  sstd::max(buf)); }
	{ sstd::mat_r< int32> buf={{-2, -1}, {0, 1}};         printf("max: %i\n",  sstd::max(buf)); }
	{ sstd::mat_r< int64> buf={{-2, -1}, {0, 1}};         printf("max: %li\n", sstd::max(buf)); }
	{ sstd::mat_r<uint8 > buf={{ 0,  1}, {2, 3}};         printf("max: %u\n",  sstd::max(buf)); }
	{ sstd::mat_r<uint16> buf={{ 0,  1}, {2, 3}};         printf("max: %u\n",  sstd::max(buf)); }
	{ sstd::mat_r<uint32> buf={{ 0,  1}, {2, 3}};         printf("max: %u\n",  sstd::max(buf)); }
	{ sstd::mat_r<uint64> buf={{ 0,  1}, {2, 3}};         printf("max: %lu\n", sstd::max(buf)); }
	{ sstd::mat_r< float> buf={{-2, -1}, {0, 1}};         printf("max: %f\n",  sstd::max(buf)); }
	{ sstd::mat_r<double> buf={{-2, -1}, {0, 1}};         printf("max: %lf\n", sstd::max(buf)); }
	printf("\n");
	
	//-------------------------------------------------------------------------------------------------------------------------------------------
	
	{ TEST_vec_sort_sort_de  ( int8 ); }
	{ TEST_vec_sort_sort_de  ( int16); }
	{ TEST_vec_sort_sort_de  ( int32); }
	{ TEST_vec_sort_sort_de  ( int64); }
	{ TEST_vec_sort_sort_de_u(uint8 ); }
	{ TEST_vec_sort_sort_de_u(uint16); }
	{ TEST_vec_sort_sort_de_u(uint32); }
	{ TEST_vec_sort_sort_de_u(uint64); }
	
	//-------------------------------------------------------------------------------------------------------------------------------------------
}
void TEST_signal(){
	printf("■ generate signal\n");
	double freq2generate = 3; // Hz
	double freq2sample = 10;  // Hz
	uint len=10;              // 10 Hz 10 sample = 1 sec
	std::vector<double> sin_wave = sstd::sinWave(freq2generate, freq2sample, len);
	std::vector<double> cos_wave = sstd::cosWave(freq2generate, freq2sample, len);
}
void TEST_file(){
	printf("■ fopen\n");
	
	{
		sstd::file fp;
		const char* fileName = "./test_fopen.txt";

		if(!fp.fopen(fileName, "wb")){ // Enable to open file by the same code between MSVC++ and GCC.
			// falied
			printf("false\n\n");
		}else{
			// success
			printf("test_fopen.txt was made.\n\n");
			std::string buf="abc";
			fp.fwrite(buf.c_str(), 1, buf.size());
		}
	}

	{
		sstd::file fp;
		if(!fp.fopen(std::string("./test_fopen_std_string.txt"), "wb")){ // Enable to open file by the same code between MSVC++ and GCC.
		}
	}
}
void TEST_file_c(){
	// $ sha512sum ./test.png
	// 021c3d7da0cedd5aa780ca765f9071f210ed3e19db3c08ee74aa6531aaf6552c3daaa8d0f30abeb10a30793bffbb86d39e3b019b865d54c2793dbd3b62c243e6  ./test.png

	const char* pFilePath_c = "./test_file_c.png";
	{
		const char* pFilePath = "./test.png";
		std::vector<uint8> data = sstd::readAll_bin(pFilePath);
		
		sstd::file_c fp_c;
		if(!fp_c.fopen_wbp(pFilePath_c)){ sstd::pdbg("ERROR: sstd::file_c::fopen_wbp(%s) was failed.\n", pFilePath); return; }
		if(!fp_c.fwriteAll(data)       ){ sstd::pdbg("ERROR: sstd::file_c::fwriteAll(%s) was failed.\n", pFilePath); return; }
	}
	
	const char* pFilePath_c2f = "./test_file_c2f.png";
	{
		std::vector<uint8> data;
		
		sstd::file_c fp_c;
		if(!fp_c.fopen_rbp(pFilePath_c)){ sstd::pdbg("ERROR: sstd::file_c::fopen_rbp(%s) was failed.\n", pFilePath_c); return; }
		if(!fp_c.freadAll (data)       ){ sstd::pdbg("ERROR: sstd::file_c::freadAll() was failed.\n"); return; }

		if(!sstd::writeAll_bin(pFilePath_c2f, data)){ sstd::pdbg("ERROR: sstd::fwriteAll(%s) was failed.\n", pFilePath_c2f); return; }
	}
}
void TEST_mkdir(){
	printf("■ mkdir\n\n");
	sstd::mkdir("./test_mkdir/abc/def"); // enable to make multilayer directory by one step.
	sstd::mkdir(std::string("./test_mkdir/abc/def")); // enable to make multilayer directory by one step.
}
void TEST_rm(){
	printf("■ rm\n");
	printf("  □ unlink\n");
	{ sstd::file fp; fp.fopen("./unlink.txt", "w"); }
	sstd::printn(sstd::unlink("./unlink.txt"));
	printf("\n");

	printf("  □ rmdir\n");
	sstd::mkdir("./test_rmdir");
	sstd::printn(sstd::rmdir("./test_rmdir"));
	printf("\n");
	
	sstd::mkdir("./test_rm/abc/def");
	sstd::mkdir("./test_rm/abc2/def");
	{ sstd::file fp; fp.fopen("./test_rm/abc/def/abc.txt", "w"); }
	{ sstd::file fp; fp.fopen("./test_rm/abc/abc.txt",     "w"); }
	{ sstd::file fp; fp.fopen("./test_rm/abc/xxx",         "w"); }
	{ sstd::file fp; fp.fopen("./test_rm/abc2/xxx",        "w"); }
	{ sstd::file fp; fp.fopen("./test_rm/123.txt",         "w"); }
	
	printf("  □ getAllInDir\n");
	std::vector<struct sstd::pathAndType> ret;
	sstd::printn(sstd::getAllPath(ret, "./test_rm"));
	for(uint i=0; i<ret.size(); i++){
		if      (ret[i].type=='f'){ sstd::printn(sstd::ssprintf("type: file,      path: %s", ret[i].path.c_str()));
		}else if(ret[i].type=='d'){ sstd::printn(sstd::ssprintf("type: directory, path: %s", ret[i].path.c_str()));
		}          else           { sstd::pdbg("ERROR: sstd::getAllInDir() is failed.\n"); }
	}
	printf("\n");
	
	std::vector<std::string> retStr;
	sstd::printn(sstd::getAllPath(retStr, "./test_rm")); sstd::printn(retStr); printf("\n");
	sstd::printn(sstd::getAllFile(retStr, "./test_rm")); sstd::printn(retStr); printf("\n");
	sstd::printn(sstd::getAllDir (retStr, "./test_rm")); sstd::printn(retStr); printf("\n");
	printf("\n");
	
	printf("  □ rm\n");
	sstd::printn(sstd::rm("./test_rm")); // enable to delete not empty directory by one step.
}
void TEST_str2num(){
	std::string str = "1.5";
	sstd::printn(sstd::str2double(str));
	sstd::printn(sstd::str2int(str));
}
void TEST_ssprintf(){
	printf("■ ssprintf(const char* format, ...)\n");
	printf("%s", sstd::ssprintf("Num: %d, Str: %s\n\n", 1234, "abcd").c_str());
}
void TEST_strmatch(){
	printf("■ strmatch\n");
	const char* str = "abcdefghijk"; // str: 比較する文字列
	const char* WildCard1 = "abc*";
	const char* WildCard2 = "a?cdefghijk";
	const char* WildCard3 = "a?";
	printf("if(\"%s\" == \"%s\") -> %s\n", str, WildCard1, sstd::strmatch(str, WildCard1)?"true":"false");
	printf("if(\"%s\" == \"%s\") -> %s\n", str, WildCard2, sstd::strmatch(str, WildCard2)?"true":"false");
	printf("if(\"%s\" == \"%s\") -> %s\n", str, WildCard3, sstd::strmatch(str, WildCard3)?"true":"false");
	printf("\n");
	printf("■ strmatch_getWC\n");
	bool tf; std::string retWC;
	tf = sstd::strmatch_getWC(str, WildCard1, retWC); printf("if(\"%s\" == \"%s\") -> %s, retWC: %s\n", str, WildCard1, tf?"true":"false", retWC.c_str());
	tf = sstd::strmatch_getWC(str, WildCard2, retWC); printf("if(\"%s\" == \"%s\") -> %s, retWC: %s\n", str, WildCard2, tf?"true":"false", retWC.c_str());
	tf = sstd::strmatch_getWC(str, WildCard3, retWC); printf("if(\"%s\" == \"%s\") -> %s, retWC: %s\n", str, WildCard3, tf?"true":"false", retWC.c_str());
	printf("\n");

	printf("  □ isNum, isAlphabet\n");
	printf("    isNum               ('%c') -> %s\n", '0', sstd::isNum               ('0')?"true":"false");
	printf("    isAlphabet          ('%c') -> %s\n", 'a', sstd::isAlphabet          ('a')?"true":"false");
	printf("    isAlphabet_onlyUpper('%c') -> %s\n", 'A', sstd::isAlphabet_onlyUpper('A')?"true":"false");
	printf("    isAlphabet_onlyLower('%c') -> %s\n", 'a', sstd::isAlphabet_onlyLower('a')?"true":"false");
	printf("\n");
}
void TEST_path(){
	printf("■ path\n"); // <- 不足する関数を追加する必要がある．
	
	const char* pPath="./abc/def/text.abc.txt\0";
	
	printf("Input pPath: %s\n", pPath);
	printf("Output getPath: %s\n",                     sstd::getPath                     (pPath).c_str());
	printf("Output getFileName: %s\n",                 sstd::getFileName                 (pPath)        );
	printf("Output getFileNameWithoutExtension: %s\n", sstd::getFileName_withoutExtension(pPath).c_str());
	printf("Output getFileExtension: %s\n",            sstd::getExtension                (pPath)        );
	printf("\n");

	sstd::printn(sstd::parsePath(R"(C:\a\b)"));
	sstd::printn(sstd::parsePath(R"(/a/b)"));
	sstd::printn(sstd::parsePath(R"(./a/b)"));
	sstd::printn(sstd::parsePath(R"(../a/b)"));
	sstd::printn(sstd::parsePath(R"(../a/b/)"));
	sstd::printn(sstd::parsePath(R"(a/b/)"));
	printf("\n");

	sstd::printn(sstd::parsePath_withBase(R"(C:\a\b)"));
	sstd::printn(sstd::parsePath_withBase(R"(/a/b)"));
	sstd::printn(sstd::parsePath_withBase(R"(./a/b)"));
	sstd::printn(sstd::parsePath_withBase(R"(../a/b)"));
	sstd::printn(sstd::parsePath_withBase(R"(../a/b/)"));
	sstd::printn(sstd::parsePath_withBase(R"(a/b/)"));
	printf("\n");
	
	printf("  □ isFile\n");
	sstd::printn(sstd::isFile("./main.cpp"));
	sstd::printn(sstd::isFile("./notExist"));
	sstd::printn(sstd::isFile("./sstd"));
	printf("\n");
	
	printf("  □ isDir\n");
	sstd::printn(sstd::isDir("./main.cpp"));
	sstd::printn(sstd::isDir("./notExist"));
	sstd::printn(sstd::isDir("./sstd"));
	printf("\n");
	
	printf("  □ file exist\n");
	sstd::printn(sstd::fileExist("./main.cpp"));
	sstd::printn(sstd::fileExist("./notExist"));
	sstd::printn(sstd::fileExist("./sstd"));
	printf("\n");
	
	printf("  □ dir exist\n");
	sstd::printn(sstd::dirExist("./main.cpp"));
	sstd::printn(sstd::dirExist("./notExist"));
	sstd::printn(sstd::dirExist("./sstd"));
	printf("\n");
	
	printf("  □ path exist\n");
	sstd::printn(sstd::pathExist("./main.cpp"));
	sstd::printn(sstd::pathExist("./notExist"));
	sstd::printn(sstd::pathExist("./sstd"));
	printf("\n");
}
void TEST_getFilePathInDir(){
	printf("■ getFilePathInDir\n");
	
	const char* DirAndFileName_withWildCard = R"(./sstd/src/*.hpp)";
	printf("DirAndFileName_withWildCard: %s\n\n", DirAndFileName_withWildCard);
	std::vector<std::string> PathList = sstd::getFilePathInDir(DirAndFileName_withWildCard);
	for(uint i=0; i<PathList.size(); i++){ printf("%s\n", PathList[i].c_str()); } printf("\n");
}
void TEST_strEdit(){
	printf("■ strEdit\n");
	printf("  □ readAll_bin\n");
	std::vector<uint8> raw = sstd::readAll_bin("./test.png");
	sstd::printn_all(raw.size());
	printf("  □ writeAll_bin\n");
	if(!sstd::writeAll_bin("./test__writeAll_bin_char.png",             raw)){ sstd::pdbg("ERROR: sstd::writeAll_bin()\n"); }
	if(!sstd::writeAll_bin(std::string("./test__writeAll_bin_str.png"), raw)){ sstd::pdbg("ERROR: sstd::writeAll_bin()\n"); }
	
	printf("  □ readAll_withoutBOM & splitByLine\n");
//	std::string str_tI = sstd::readAll_withoutBOM(R"(./tinyInterpreter.txt)");
	std::string str_tI = sstd::readAll_withoutBOM(std::string(R"(./tinyInterpreter.txt)"));
	std::vector<std::string> splitLList = sstd::splitByLine(str_tI);
	printf("\n");
	printf("  tinyInterpreter.txt\n");
	printf("+----+----------------------------------------------------------------------------+\n");
	for(uint i=0; i<splitLList.size(); i++){
		printf("| %2d | %-74s |\n", i, splitLList[i].c_str());
	}
	printf("+----+----------------------------------------------------------------------------+\n");
	printf("\n");
	
	printf("  □ splitByX\n");
	std::vector<std::string> vecRow;
	vecRow = sstd::split("ABC DEF",       ' ');        sstd::printn(vecRow); // "ABC DEF" -> ["ABC", "DEF"]
	vecRow = sstd::split(" ABC   D EF  ", ' ');        sstd::printn(vecRow); // " ABC   D EF  " -> ["ABC", "D", "EF"]
	
	vecRow = sstd::split("ABC,DEF",              ','); sstd::printn(vecRow); // "ABC,DEF" -> ["ABC", "DEF"]
	vecRow = sstd::split(" ABC  , D,  EF ,GH  ", ','); sstd::printn(vecRow); // " ABC  , D,  EF ,GH  " -> ["ABC", "D", "EF",  "GH"]
	
	// テストを書くように．
	/*
	std::string sstd::removeHeadSpace(const uchar* str);
	void sstd::removeTailSpace(std::string& str);
	std::string              sstd::removeSpace_of_HeadAndTail(const uchar* str);
	void                     sstd::removeSpace_of_HeadAndTail(std::string& str);
	std::vector<std::string> sstd::removeSpace_of_HeadAndTail(const std::vector<std::string>& vec);
	//*/
}
/*
// 実装完了 (処理時間短縮のため，コメントアウト)
TEST(strEdit, strIn){
	{
		std::string lhs = "";
		std::string rhs = "";
		bool ret=sstd::strIn(lhs, rhs); ASSERT_TRUE(ret);
	}
	{
		std::string lhs = "ABCD";
		std::string rhs = "ABCDEFG";
		bool ret=sstd::strIn(lhs, rhs); ASSERT_TRUE(ret);
	}
	{
		std::string lhs = "BCD";
		std::string rhs = "ABCDEFG";
		bool ret=sstd::strIn(lhs, rhs); ASSERT_TRUE(ret);
	}
	{
		std::string lhs = "DEFG";
		std::string rhs = "ABCDEFG";
		bool ret=sstd::strIn(lhs, rhs); ASSERT_TRUE(ret);
	}
	{
		std::string lhs = "ABCDEFG";
		std::string rhs = "ABCDEFG";
		bool ret=sstd::strIn(lhs, rhs); ASSERT_TRUE(ret);
	}
	{
		std::string lhs = "AXCDEFG";
		std::string rhs = "ABCDEFG";
		bool ret=sstd::strIn(lhs, rhs); ASSERT_TRUE(!ret);
	}
}//*/
void TEST_tinyInterpreter(){
	printf("■ tinyInterpreter\n");
	printf("  □ getCommandList & splitByComma\n");
	std::vector<std::string> cmdList = sstd::getCommandList(R"(./tinyInterpreter.txt)");
	for(uint i=0; i<cmdList.size(); i++){
		std::vector<std::string> splitCList = sstd::splitByComma(cmdList[i]);
		for(uint n=0; n<splitCList.size(); n++){ printf("[%5s] ", splitCList[n].c_str()); } printf("\n");
	}
	printf("\n");
}
void TEST_parseCSV(){
	printf("■ parseCSV\n");
	std::vector<std::vector<std::string>> csv = sstd::parseCSV(R"(./parseCSV.csv)");
	sstd::printn(csv.size());
	printf("----\n");
	for(uint p=0; p<csv.size(); p++){
		for(uint q=0; q<csv[p].size(); q++){
			printf("%s,", csv[p][q].c_str());
		}
		printf("\n");
	}
	printf("----\n");
}
void TEST_encode_decode(){
	printf("■ encode_decode\n");
	
	//===

	printf("  □ base64_encode\n");
	std::string str_b64  = "#include \"./sstd/sstd.hpp\".+=ABCD";
	printf("    %s ->[base64 encode]-> %s\n", str_b64.c_str(), sstd::base64_encode((uchar*)str_b64.c_str(), str_b64.size()).c_str());
	printf("    %s ->[base64 encode]-> %s\n", str_b64.c_str(), sstd::base64_encode(str_b64).c_str());
	printf("    %s ->[base64 encode]-> %s\n", str_b64.c_str(), sstd::base64_encode(str_b64).c_str());

	printf("  □ base64_decode\n");
	std::string str_b64e = sstd::base64_encode(str_b64);
	printf("    %s ->[base64 decode]-> %s\n", str_b64e.c_str(), sstd::base64_decode((uchar*)str_b64e.c_str(), str_b64e.size()).c_str());
	printf("    %s ->[base64 decode]-> %s\n", str_b64e.c_str(), sstd::base64_decode(str_b64e.c_str()).c_str());
	printf("    %s ->[base64 decode]-> %s\n", str_b64e.c_str(), sstd::base64_decode(str_b64e).c_str());

	printf("  □ make_base64_decode_table\n");
	sstd::print_base64_decode_table(); // for developers
	printf("\n");

	//===

	printf("  □ url_encode\n");
	std::string str_url(256, 0); for(uint i=0; i<str_url.size(); i++){ str_url[i]=i; }
	printf("    [url encode]-> %s\n", sstd::url_encode(str_url.c_str(), str_url.size()).c_str());
	printf("    [url encode]-> %s\n", sstd::url_encode(str_url.c_str()).c_str()); // 先頭が 0 なので、終端だと判断されている。
	printf("    [url encode]-> %s\n", sstd::url_encode(str_url).c_str());
	printf("\n");

	sstd::url_encode_compare_speed(); // for developers
	printf("\n");
	
	printf("  □ url_decode\n");
	std::string str_url_d = sstd::url_encode("#include \"./sstd/sstd.hpp\".+=ABCD");
	printf("    %s ->[url encode]-> %s\n", "#include \"./sstd/sstd.hpp\".+=ABCD", str_url_d.c_str());
	printf("    %s ->[url decode]-> %s\n", str_url_d.c_str(), sstd::url_decode(str_url_d.c_str(), str_url_d.size()).c_str());
	printf("    %s ->[url decode]-> %s\n", str_url_d.c_str(), sstd::url_decode(str_url_d.c_str()).c_str());
	printf("    %s ->[url decode]-> %s\n", str_url_d.c_str(), sstd::url_decode(str_url_d).c_str());
	printf("\n");
	
	printf("  □ make_url_decode_table\n");
	sstd::print_url_decode_table();
	printf("\n");

	//===

	printf("■ utf8 <-> utf16\n");
	printf("  □ unicode escape (utf16) -> utf16 (binary)\n");
	std::string escaped_utf16 = R"(\u30e6\u30cb\u30b3\u30fc\u30c9)"; // "ユニコード"
//	std::string escaped_utf16 = R"(abcd_\u30e6\u30cb\u30b3\u30fc\u30c9)"; // "abcd_ユニコード" // <- これがバグる。 issue
	std::u16string utf16_bin = sstd::unicodeEscape_decode(escaped_utf16);
	for(uint i=0; i<utf16_bin.size(); i++){ printf("%X\n", utf16_bin[i]); }
	
	printf("  □ utf16 (binary) -> utf8\n");
	std::string utf8 = sstd::utf16_to_utf8(utf16_bin);
	printf("%s\n", utf8.c_str());

	std::u32string utf32_bin = sstd::utf8_to_utf32(utf8);
	std::u16string utf16_bin2 = sstd::utf32_to_utf16(utf32_bin);

	printf("  □ utf16 (binary) -> unicode escape (utf16)\n");
	printf("%s\n", sstd::unicodeEscape_encode(utf16_bin2).c_str());

	sstd::unicodeEscape_compare_speed(); // for developers
	printf("\n");

	printf("  □ make_unicodeEscape_decode_table\n");
	sstd::print_unicodeEscape_decode_table();
	printf("\n");
}

void print_vecUint8_hex(std::vector<uint8>& rhs){ for(uint i=0; i<rhs.size(); i++){ printf("%.2x", rhs[i]); } printf("\n"); }
void TEST_hashFnc(){
	
	const char* pFilePath = "./test.png";
	std::vector<uint8> data = sstd::readAll_bin(pFilePath);
	
	printf("fnc_MD5   ( %s ) = ", pFilePath); { std::vector<uint8> hash = sstd::md5   (data); print_vecUint8_hex(hash); }
	printf("fnc_SHA1  ( %s ) = ", pFilePath); { std::vector<uint8> hash = sstd::sha1  (data); print_vecUint8_hex(hash); }
	printf("fnc_SHA224( %s ) = ", pFilePath); { std::vector<uint8> hash = sstd::sha224(data); print_vecUint8_hex(hash); }
	printf("fnc_SHA256( %s ) = ", pFilePath); { std::vector<uint8> hash = sstd::sha256(data); print_vecUint8_hex(hash); }
	printf("fnc_SHA384( %s ) = ", pFilePath); { std::vector<uint8> hash = sstd::sha384(data); print_vecUint8_hex(hash); }
	printf("fnc_SHA512( %s ) = ", pFilePath); { std::vector<uint8> hash = sstd::sha512(data); print_vecUint8_hex(hash); }
}
// --- hash calculation by command ---
//
// $ md5sum ./test.png
// 80764a9c59629dca04ee00c125726a01  ./test.png
//
// $ sha1sum ./test.png
// 3361cc4368ae3369f3f115df78d186a887ee8b46  ./test.png
//
// $ sha224sum ./test.png
// b5d2e3bface35276977ededd5941b52c0547ba4aa63a9571a9a81ac7  ./test.png
//
// $ sha256sum ./test.png
// 58aeaf1a74a46e37bad7d2161d629537440df5e2fcb0ee97837209335cf1fee7  ./test.png
//
// $ sha384sum ./test.png
// bbc9239c8266ab4b86b7b9435d1ade6f7c47af11ffac78dbb5cdcbe15c3fdaf96e9e720e2c2fa14178d96304ec8185ef  ./test.png
//
// $ sha512sum ./test.png
// 021c3d7da0cedd5aa780ca765f9071f210ed3e19db3c08ee74aa6531aaf6552c3daaa8d0f30abeb10a30793bffbb86d39e3b019b865d54c2793dbd3b62c243e6  ./test.png

void TEST_pause(){
//	printf("■ #define UsePause\n");
	sstd::pause();
//	printf("■ #define UsePauseIfWin32\n");
	sstd::pauseIfWin32(); // win32 の場合のみ停止
//	printf("\n");
}

//-----------------------------------------------------------------------

void TEST_stdVector_expansion(){
	printf("== sstd_stdVector_expansion ==\n\n");
	
	// 算術演算子以外にも，<< 演算や，| 演算子によって，結合を定義するとよい．
	
	std::vector<double> lhs={1, 2, 3}, rhs={1, 2, 3};
//	std::vector<int> lhsInt={1, 2, 3}, rhsInt={1, 2, 3};
	std::vector<uint32> lhsInt={1, 2, 3}, rhsInt={1, 2, 3};

	printf("■ plus\n");
	sstd::printn_all(lhs+rhs);
	
	sstd::printn_all(lhs+(int8)10);
	sstd::printn_all(lhs+(uint32)10);
	sstd::printn_all(lhs+(double)10);
	sstd::printn_all(lhsInt+(double)10);
	
	sstd::printn_all((int8)10+lhs);
	// XXX 次はこれを実装する XXX
	sstd::printn_all(lhs+=rhs);
	sstd::printn_all(lhs+=(double)10);
	// ++
	printf("\n");
	
	printf("■ minus\n");
	sstd::printn_all(lhs-=(double)10);
	sstd::printn_all(lhs-=rhs);
	sstd::printn_all(lhs-rhs);
	sstd::printn_all(lhs-(int8)10);
	sstd::printn_all((int8)10-lhs);
	// XXX 次はこれを実装する XXX
	// --
	printf("\n");
	
	printf("■ multiplication\n");
	sstd::printn_all(lhs*rhs);
	sstd::printn_all(lhs*(int8)10);
	sstd::printn_all((int8)10*lhs);
	sstd::printn_all(lhs*=rhs);
	sstd::printn_all(lhs*=(double)10);
	printf("\n");
	
	printf("■ division\n");
	sstd::printn_all(lhs/=(double)10);
	sstd::printn_all(lhs/=rhs);
	sstd::printn_all(lhs/rhs);
	sstd::printn_all(lhs/(int8)10);
	sstd::printn_all((int8)10/lhs);
	printf("\n");
	
	printf("■ modulo\n");
	sstd::printn_all(lhsInt%rhsInt);
	sstd::printn_all(lhsInt%(int8)10);
	sstd::printn_all((int8)10%lhsInt);
	sstd::printn_all(lhsInt%=(int8)10);
	sstd::printn_all(lhsInt%=rhsInt);
	printf("\n");

	printf("■ power\n");
	sstd::printn_all(lhs^rhs);
	sstd::printn_all(lhsInt^rhsInt);
	sstd::printn_all(lhsInt^(uint32)2);
	sstd::printn_all((uint32)2^lhsInt);
	sstd::printn_all(lhs^=2);
	sstd::printn_all(lhs^=rhs);
	printf("\n");
	
	printf("■ inclement and decrement\n");
	sstd::printn_all(lhsInt++);
	sstd::printn_all(++lhsInt);
	sstd::printn_all(lhsInt--);
	sstd::printn_all(--lhsInt);
	printf("\n");
	
	printf("■ operator >>\n");
	sstd::printn_all(lhs<<rhs);
	sstd::printn_all(lhs<<(double)3.14);
	sstd::printn_all((double)3.14<<lhs);
	std::vector<double> buf={123};
	buf <<= lhs;
	buf <<= (double)1.23;
	sstd::printn_all(buf);
}

//-----------------------------------------------------------------------

void TEST_mat_colMajor(){
	printf("== sstd_src_MatrixStore_mat ==\n\n"); // col-major
	
	printf("■ Init sstd::eye()\n");
	{ sstd::mat_c<double> buf(3, 3); sstd::eye(buf); sstd::printn(buf); printf("\n"); }
	{ sstd::mat_c<double> buf(3, 2); sstd::eye(buf); sstd::printn(buf); printf("\n"); }
	{ sstd::mat_c<double> buf(2, 3); sstd::eye(buf); sstd::printn(buf); printf("\n"); }
		
	printf("■ Init sstd::ones()\n");
	{ sstd::mat_c<double> buf(3, 3); sstd::ones(buf); sstd::printn(buf); printf("\n"); }
	{ sstd::mat_c<double> buf(3, 2); sstd::ones(buf); sstd::printn(buf); printf("\n"); }
	{ sstd::mat_c<double> buf(2, 3); sstd::ones(buf); sstd::printn(buf); printf("\n"); }
		
	printf("■ Init sstd::zeros()\n");
	{ sstd::mat_c<double> buf(3, 3); sstd::zeros(buf); sstd::printn(buf); printf("\n"); }
	{ sstd::mat_c<double> buf(3, 2); sstd::zeros(buf); sstd::printn(buf); printf("\n"); }
	{ sstd::mat_c<double> buf(2, 3); sstd::zeros(buf); sstd::printn(buf); printf("\n"); }

	printf("■ Init sstd::mat_c<type> by \"std::initializer_list<T>\"\n");
	printf("\n");
	
	sstd::mat_c<double> matD_initializer{{1, 2, 3},{4, 5, 6},{7, 8, 9},{10, 11, 12}}; // これは，sstd::mat_c<T> 側にもテストを書くように．
	sstd::printn(matD_initializer);
	printf("\n");
	
	//===
	
	printf("■ Init sstd::mat_c<type>\n");
	printf("\n");
	
	sstd::mat_c<double> Matd(5, 3);
	printf("RowSize: %d\n", Matd.rows());
	printf("ColSize: %d\n", Matd.cols());
	printf("Length:  %d\n", Matd.size());

	printf("Indication of column major\n");
	uint i=0;
	for(uint q=0; q<Matd.cols(); q++){
		for(uint p=0; p<Matd.rows(); p++){
			Matd(p, q) = i; i++;
		}
	}
	sstd::print(Matd);
	printf("\n");
	
	//===
	
	i=0;
	for(uint q=0; q<Matd.size(); q++){ Matd[i] = i; i++; }
	sstd::print(Matd);
	printf("\n");

	//===
	
	sstd::mat_c<double>* pMatd = new sstd::mat_c<double>(5, 3);
	printf("RowSize: %d\n", pMatd->rows());
	printf("ColSize: %d\n", pMatd->cols());
	printf("Length:  %d\n", pMatd->size());

	printf("Indication of column major\n");
	i=0;
	for(uint q=0; q<pMatd->cols(); q++){
		for(uint p=0; p<pMatd->rows(); p++){
			(*pMatd)(p, q) = i; i++;
		}
	}

	sstd::print(*pMatd);
	printf("\n");
	delete pMatd;
	
	//===

	printf("■ copy\n");printf("\n");
	sstd::mat_c<double> Matd_copy = Matd;
	Matd_copy = Matd; // "sstd::copy(Matd_copy, Matd);" is called.
	sstd::print(Matd_copy); printf("\n");

	//===

	printf("■ copy row\n");printf("\n");
	sstd::mat_c<double> Matd_rowCopy(5, 3); sstd::zeros(Matd_rowCopy);
	Matd_rowCopy(1, ':') = Matd(1, ':');
	sstd::print(Matd_rowCopy); printf("\n");
	
	printf("■ copy col\n");printf("\n");
	sstd::mat_c<double> Matd_colCopy(5, 3); sstd::zeros(Matd_colCopy);
	Matd_colCopy(':', 2) = Matd(':', 2);
	sstd::print(Matd_colCopy); printf("\n");

	//===
	sstd::printn(Matd_colCopy); printf("\n");
	sstd::printn_all(Matd_colCopy); printf("\n");

	//===
	
	printf("■ print(type& rhs)\n");printf("\n");
	sstd::mat_c<bool> matB{{true, false, false},{false, true, false},{false, false, true},{true, false, false}};
	sstd::printn(matB);

	printf("■ print(type& rhs)\n");printf("\n");
	sstd::mat_c<std::string> matStr{{"a", "ab", "abc"},{"abcd", "abcde", "abcdef"},{"7", "8", "9"},{"10", "11", "12"}};
	sstd::printn(matStr);
	
	//===

	printf("■ Operators for linearAlgebra\n");printf("\n");
	{
		// このあたりは順次テストを書くこと
		
		sstd::mat_c<double> lhs={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
		sstd::mat_c<double> rhs={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
		
		sstd::mat_c<double> lhs23={{1,2,3}, {4, 5, 6}};
		sstd::mat_c<double> rhs32={{1,2}, {3, 4}, {5, 6}};
		
		sstd::mat_c<int> lhsInt={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
		sstd::mat_c<int> rhsInt={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
		
		printf("  □ plus\n");printf("\n");
		sstd::printn(lhs+rhs); printf("\n");
		sstd::printn(lhs+(uint)1); printf("\n");
		sstd::printn((uint)1+lhs); printf("\n");
		
		sstd::printn(lhs+(int)-1); printf("\n");
		sstd::printn((int)-1+lhs); printf("\n");
		
		printf("  □ minus\n");printf("\n");
		sstd::printn(lhs-rhs); printf("\n");
		
		sstd::printn(lhs-(int)1); printf("\n");
		sstd::printn((int)1-lhs); printf("\n");
		
		printf("  □ multiplication\n");printf("\n");
		sstd::printn(lhs*rhs); printf("\n");
		sstd::printn(lhs23*rhs32); printf("\n");
		sstd::printn(lhs23*(uint)2); printf("\n");
		sstd::printn((uint)2*lhs23); printf("\n");
		
		sstd::printn(lhs()*rhs()); printf("\n");
		sstd::printn(lhs  *rhs()); printf("\n");
		sstd::printn(lhs()*rhs  ); printf("\n");
		sstd::printn(lhs.vec()*rhs.vec()); printf("\n");
		
		printf("  □ division\n");printf("\n");
		sstd::printn(lhs()/rhs()); printf("\n");
		sstd::printn(lhs  /rhs()); printf("\n");
		sstd::printn(lhs()/rhs  ); printf("\n");

		printf("  □ power\n");printf("\n");
		sstd::printn(lhs^(uint32)0); printf("\n");
		sstd::printn(lhs^(uint32)1); printf("\n");
		sstd::printn(lhs^(uint32)2); printf("\n");
		sstd::printn(lhs*lhs); printf("\n");
		sstd::printn(lhs^(uint32)3); printf("\n");
		sstd::printn(lhs*lhs*lhs); printf("\n");

		
		sstd::printn(lhs^(int32)3); printf("\n");
		
		sstd::printn(lhs()^rhs()); printf("\n");
		sstd::printn(lhs  ^rhs()); printf("\n");
		sstd::printn(lhs()^rhs  ); printf("\n");
		
		// 未実装
		//sstd::printn(lhs^(int32)-1); printf("\n");
		//sstd::printn(lhs^(float)-1); printf("\n");
		//sstd::printn(lhs^(double)-1); printf("\n");
		
		printf("  □ modulo\n");printf("\n");
		sstd::printn(lhsInt % 2); printf("\n");
		
		sstd::printn(lhsInt()%rhsInt()); printf("\n");
		sstd::printn(lhsInt  %rhsInt()); printf("\n");
		sstd::printn(lhsInt()%rhsInt  ); printf("\n");
	}
}
/*
// 実装完了 (処理時間短縮のため，コメントアウト)

TEST(c2py, mat_ope_eq_ne){
	// sstd::mat_c (col-major)
	
	sstd::mat_c<double> matIn(5, 3);
	sstd::mat_c<double> ansT0(5, 3);
	sstd::mat_c<double> ansF0(5, 3);
	sstd::mat_c<double> ansF1(3, 5);
	
	for(uint i=0; i<matIn.size(); i++){
		matIn[i]=i;
		ansT0[i]=i;
		ansF0[i]=i;
		ansF1[i]=i;
	}
	ansF0[0]=(double)999;
	
	ASSERT_TRUE (matIn==ansT0);
	ASSERT_FALSE(matIn==ansF0);
	ASSERT_FALSE(matIn==ansF1);
	
	ASSERT_FALSE(matIn!=ansT0);
	ASSERT_TRUE (matIn!=ansF0);
	ASSERT_TRUE (matIn!=ansF1);
}
//*/
//-----------------------------------------------------------------------

void TEST_mat_rowMajor(){
	printf("== sstd_src_MatrixStore_mat_rowMajor ==\n\n");
	
	printf("■ Init sstd::mat_r<type> by \"std::initializer_list<T>\"\n");
	printf("\n");
	
	sstd::mat_r<double> matD_initializer{{1, 2, 3},{4, 5, 6},{7, 8, 9},{10, 11, 12}}; // これは，sstd::mat<T> 側にもテストを書くように．
	sstd::printn(matD_initializer);
	printf("\n");
	
	//===
	
	printf("■ Init sstd::mat_r<type>\n");
	printf("\n");
	
	sstd::mat_r<double> Matd(5, 3);
	printf("RowSize: %d\n", Matd.rows());
	printf("ColSize: %d\n", Matd.cols());
	printf("Length:  %d\n", Matd.size());

	printf("Indication of row major\n");
	uint i=0;
	for(uint p=0; p<Matd.rows(); p++){
		for(uint q=0; q<Matd.cols(); q++){
			Matd(p, q) = i; i++;
		}
	}
	sstd::print(Matd);
	printf("\n");
	
	//===
	
	i=0;
	for(uint q=0; q<Matd.size(); q++){ Matd[i] = i; i++; }
	sstd::print(Matd);
	printf("\n");

	//===
	
	sstd::mat_r<double>* pMatd = new sstd::mat_r<double>(5, 3);
	printf("RowSize: %d\n", pMatd->rows());
	printf("ColSize: %d\n", pMatd->cols());
	printf("Length:  %d\n", pMatd->size());

	printf("Indication of row major\n");
	i=0;
	for(uint p=0; p<pMatd->rows(); p++){
		for(uint q=0; q<pMatd->cols(); q++){
			(*pMatd)(p, q) = i; i++;
		}
	}

	sstd::print(*pMatd);
	printf("\n");
	delete pMatd;
	
	//===

	printf("■ copy\n");printf("\n");
	sstd::mat_r<double> Matd_copy = Matd;
	Matd_copy = Matd; // "sstd::copy(Matd_copy, Matd);" is called.
	sstd::print(Matd_copy); printf("\n");

	//===

	printf("■ copy row\n");printf("\n");
	sstd::mat_r<double> Matd_rowCopy(5, 3); sstd::zeros(Matd_rowCopy);
	Matd_rowCopy(1, ':') = Matd(1, ':');
	sstd::print(Matd_rowCopy); printf("\n");
	
	printf("■ copy col\n");printf("\n");
	sstd::mat_r<double> Matd_colCopy(5, 3); sstd::zeros(Matd_colCopy);
	Matd_colCopy(':', 2) = Matd(':', 2);
	sstd::print(Matd_colCopy); printf("\n");

	//===

	sstd::printn(Matd_colCopy); printf("\n");
	sstd::printn_all(Matd_colCopy); printf("\n");
	
	//===
	
	printf("■ print(type& rhs)\n");printf("\n");
	sstd::mat_r<bool> mat_rB{{true, false, false},{false, true, false},{false, false, true},{true, false, false}};
	sstd::printn(mat_rB);
	
	printf("■ print(type& rhs)\n");printf("\n");
	sstd::mat_r<std::string> mat_rStr{{"a", "ab", "abc"},{"abcd", "abcde", "abcdef"},{"7", "8", "9"},{"10", "11", "12"}};
	sstd::printn(mat_rStr);
	
	//===

	printf("■ Operators for linearAlgebra\n");printf("\n");
	{
		// このあたりは順次テストを書くこと
		
		sstd::mat_r<double> lhs={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
		sstd::mat_r<double> rhs={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
		
		sstd::mat_r<double> lhs23={{1,2,3}, {4, 5, 6}};
		sstd::mat_r<double> rhs32={{1,2}, {3, 4}, {5, 6}};
		
		sstd::mat_r<int> lhsInt={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
		sstd::mat_r<int> rhsInt={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
		
		printf("  □ plus\n");printf("\n");
		sstd::printn(lhs+rhs); printf("\n");
		sstd::printn(lhs+(uint)1); printf("\n");
		sstd::printn((uint)1+lhs); printf("\n");
		
		sstd::printn(lhs+(int)-1); printf("\n");
		sstd::printn((int)-1+lhs); printf("\n");
		
		printf("  □ minus\n");printf("\n");
		sstd::printn(lhs-rhs); printf("\n");
		
		sstd::printn(lhs-(int)1); printf("\n");
		sstd::printn((int)1-lhs); printf("\n");
		
		printf("  □ multiplication\n");printf("\n");
		sstd::printn(lhs*rhs); printf("\n");
		sstd::printn(lhs23*rhs32); printf("\n");
		sstd::printn(lhs23*(uint)2); printf("\n");
		sstd::printn((uint)2*lhs23); printf("\n");
		
		sstd::printn(lhs()*rhs()); printf("\n");
		sstd::printn(lhs  *rhs()); printf("\n");
		sstd::printn(lhs()*rhs  ); printf("\n");
		sstd::printn(lhs.vec()*rhs.vec()); printf("\n");
		
		printf("  □ division\n");printf("\n");
		sstd::printn(lhs()/rhs()); printf("\n");
		sstd::printn(lhs  /rhs()); printf("\n");
		sstd::printn(lhs()/rhs  ); printf("\n");
		
		printf("  □ power\n");printf("\n");
		sstd::printn(lhs^(uint32)0); printf("\n");
		sstd::printn(lhs^(uint32)1); printf("\n");
		sstd::printn(lhs^(uint32)2); printf("\n");
		sstd::printn(lhs*lhs); printf("\n");
		sstd::printn(lhs^(uint32)3); printf("\n");
		sstd::printn(lhs*lhs*lhs); printf("\n");

		
		sstd::printn(lhs^(int32)3); printf("\n");
		
		sstd::printn(lhs()^rhs()); printf("\n");
		sstd::printn(lhs  ^rhs()); printf("\n");
		sstd::printn(lhs()^rhs  ); printf("\n");
		
		// 未実装
		//sstd::printn(lhs^(int32)-1); printf("\n");
		//sstd::printn(lhs^(float)-1); printf("\n");
		//sstd::printn(lhs^(double)-1); printf("\n");
		
		printf("  □ modulo\n");printf("\n");
		sstd::printn(lhsInt % 2); printf("\n");
		
		sstd::printn(lhsInt()%rhsInt()); printf("\n");
		sstd::printn(lhsInt  %rhsInt()); printf("\n");
		sstd::printn(lhsInt()%rhsInt  ); printf("\n");
	}
}
/*
// 実装完了 (処理時間短縮のため，コメントアウト)

TEST(c2py, mat_r_ope_eq_ne){
	// sstd::mat (col-major)
	
	sstd::mat_r<double> matIn(5, 3);
	sstd::mat_r<double> ansT0(5, 3);
	sstd::mat_r<double> ansF0(5, 3);
	sstd::mat_r<double> ansF1(3, 5);
	
	for(uint i=0; i<matIn.size(); i++){
		matIn[i]=i;
		ansT0[i]=i;
		ansF0[i]=i;
		ansF1[i]=i;
	}
	ansF0[0]=(double)999;
	
	ASSERT_TRUE (matIn==ansT0);
	ASSERT_FALSE(matIn==ansF0);
	ASSERT_FALSE(matIn==ansF1);
	
	ASSERT_FALSE(matIn!=ansT0);
	ASSERT_TRUE (matIn!=ansF0);
	ASSERT_TRUE (matIn!=ansF1);
}
//*/

//-----------------------------------------------------------------------

void TEST_bmat(){
	//*
	// init test
	sstd::bmat bMat4x4(4, 4);
	sstd::eye(bMat4x4);   sstd::printn(bMat4x4);
	sstd::ones(bMat4x4);  sstd::printn(bMat4x4);
	sstd::zeros(bMat4x4); sstd::printn(bMat4x4);
	sstd::print(bMat4x4);     // for print debug
	sstd::print_all(bMat4x4); // for bmat debug // Internaly, the bit matrix is processed as a set of 8x8 matrices.
	//*/

	sstd::bmat bonded8x8 = sstd::zeros(4, 4) << sstd::eye(4, 4) &&
                           sstd::ones (4, 4) << sstd::eye(4, 4);
	sstd::printn(bonded8x8);

	sstd::bmat bonded8x8_2 = sstd::zeros(5, 5) << sstd::eye(3, 3) &&
                             sstd::ones (3, 5) << sstd::eye(3, 3);
	sstd::printn(bonded8x8_2);
	
	sstd::bmat bonded16x16_horzcat2_2 = sstd::ones(16, 16) << sstd::eye(16, 16);
	sstd::printn(bonded16x16_horzcat2_2);
	
	sstd::bmat bonded16x16_vertcat2_2 = sstd::ones(16, 16) &&
		                                sstd::eye (16, 16);
	sstd::printn(bonded16x16_vertcat2_2);
	
	sstd::bmat bonded16x16 = sstd::zeros(16, 16) << sstd::eye(16, 16) &&
                             sstd::ones (16, 16) << sstd::eye(16, 16);
	sstd::printn(bonded16x16);
	
	//*
	sstd::bmat bMat8x9 = sstd::eye(8, 9);
	sstd::printn(bMat8x9);
	sstd::print_all(bMat8x9); // for debug // Internaly, the bit matrix is processed as a set of 8x8 matrices.

	sstd::printn(bMat8x9.rows());
	sstd::printn(bMat8x9.cols());
	printf("\n");

	// access to elements
	sstd::bmat M = sstd::zeros(4, 4);
	M(0, 1) = 1;
	M(1, 2) = 1;
	M(2, 3) = 1;
	M(3, 4) = 1;
	sstd::printn(M);
	sstd::printn(M*M); // multi

	// tranpose
	sstd:: bmat M_tr = M; // copy
	sstd::Tr_myself(M_tr);
	sstd::printn(M_tr);
	sstd::printn(sstd::Tr(M));

	// pow test
	sstd::bmat L1 = sstd::LxShiftMat(16, 1);
	sstd::printn(L1);
	sstd::bmat L7 = L1^((uint64)7); // この計算は後で確認して！！！
	sstd::printn(L7);

	uint N = 32;
	sstd::bmat I(N, N); sstd::eye(I);
	sstd::bmat L15 = sstd::LxShiftMat(N, 15);
	sstd::bmat R17 = sstd::RxShiftMat(N, 17);
	sstd::bmat L13 = sstd::LxShiftMat(N, 13);
	sstd::bmat T = (I + L15)*(I + R17)*(I + L13);
	sstd::printn(T);
	sstd::bmat Tp = T^(4294967296-1); // XORSHIFT
	sstd::printn(Tp);
	
	printf("Tp==I: "); if(Tp==I){ printf("true\n");  }else{ printf("false\n"); }
	printf("Tp!=I: "); if(Tp!=I){ printf("true\n");  }else{ printf("false\n"); }

	printf("I(0, 0): "); if(I(0, 0)){printf("true\n");}else{printf("false\n");}
	printf("I(1, 0): "); if(I(1, 0)){printf("true\n");}else{printf("false\n");}
	printf("I(0, 1): "); if(I(0, 1)){printf("true\n");}else{printf("false\n");}
	printf("I(1, 1): "); if(I(1, 1)){printf("true\n");}else{printf("false\n");}

	I = sstd::eye(4, 4);
	sstd::printn(I);
	I(0, 0) = false;
	I(1, 1) = false;
	I(0, 1) = 1;
	I(0, 2) = 1000;	// "I(0, 2) = 1000;" に同じ．

//	I(1, 0) = I(2, 0) = I(2, 2);
	I(1, 0) = I(2, 0) = I(2, 2) = true;

	sstd::printn(I);

	sstd::printn(I);
	I[0] = false;
	I[1] = true;

	I[2] = I[3] = I[15];
	I[4] = I[5] = true;

	I[6] = I[7] = I(2, 2);
	I(2, 2) = I[0];

	sstd::printn(I);
	//*/
}


/*
#Include "./MatrixStore/Core/MatrixStore.hpp"


int main(){

	mxs::MatrixStore<double> MatA(3, 3); mxs::zeros(MatA);
	mxs::MatrixStore<double> MatB(3, 3); mxs::zeros(MatB);

	for(uint q=0; q<MatA.cols; q++){
		for(uint p=0; p<MatA.rows; p++){
			MatA(p, q) = (MatA.cols)*p + q;
		}
	}

	printm(MatA); printf("\n");

	MatB(':', 0) = MatA(':', 1);
//	MatB(':', 1) = MatA(':', 2);
//	MatB(':', 2) = MatA(':', 0);

	printm(MatB); printf("\n");

//	MatB(0, ':') = MatA(0, ':');
	MatB(1, ':') = MatB(0, ':') = MatA(0, ':');
//	MatB(1, ':') = MatA(1, ':');
//	MatB(2, ':') = MatA(2, ':');

	//MatA = MatA.array() * MatB.array();
	// MatA = MatA.a() * MatB.a();
	// MatA = MatA.arr() * MatB;
	// MatA = MatA * MatB.arr();

	// MatA = MatA .* MatB;
	// MatA = MatA ,* MatB;
	// MatA = MatA <dot> MatB;
	// MatA = MatA ("dot")* MatB;
	// MatA = MatA *(dot) MatB;
	// MatA.cols;
	// MatB.rows;

	printm(MatB);
}
*/
