#define DEBUG
//#define use_sstd_pause		// Enable to switch "Pause" or "Not Pause" by "#define UseSysPause".
#define use_sstd_pauseIfWin32	// Enable to switch "Pause" or "Not Pause" by "#define UsePauseIfWin32".
#define use_sstd_measureTime
#ifdef _WIN32
	#include "./sstd/sstd.hpp"
#else
	#include <sstd/sstd.hpp>
#endif

// sstd/src
void TEST_measureTime_sleep();
void TEST_time();
void TEST_typeDef();
void TEST_pdbg();
// void pdbg(){ printf("======p\n"); } // #define DEBUG を定義しない場合でも，マクロでこの名前は使えなくなるので，名前空間を汚しており，本当はよくない．
void TEST_print();
void TEST_printn();
void TEST_printn_all();
void TEST_math();
void TEST_signal();
void TEST_file();
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
void TEST_pause();
void TEST_c2py();

// sstd/src/MatrixStore_mat
void TEST_mat_colMajor();
void TEST_mat_rowMajor();
void TEST_bmat();


int main(){
	printf("\n");
	printf("+---------------------------------------------------+\n");
	printf("|                                                   |\n");
	printf("|         Welcome to Sub Standard Library !         |\n");
	printf("|                                                   |\n");
	printf("+---------------------------------------------------+\n");
	printf("\n");
	printf("■ measureTime_start---------------\n\n"); time_m timem; sstd::measureTime_start(timem);

	
	printf("== sstd_src ==\n\n");
//	TEST_measureTime_sleep();
//	TEST_time();
//	TEST_typeDef();
//	TEST_pdbg();
//	TEST_print();
//	TEST_printn();
//	TEST_printn_all();
//	TEST_math();
//	TEST_signal();
//	TEST_file();
//	TEST_mkdir();
//	TEST_rm();
//	TEST_str2num();
//	TEST_ssprintf();
//	TEST_strmatch();
//	TEST_path();
//	TEST_getFilePathInDir();
	TEST_strEdit();        // テストを書くように．
//	TEST_tinyInterpreter();
//	TEST_parseCSV();
//	TEST_encode_decode();
//	TEST_pause();
//	TEST_c2py();
	
	
//	TEST_mat_colMajor(); // TODO: write tests (zeros, Tr) // sstd::print 関数のテストを書くように
//	TEST_mat_rowMajor(); // TODO: write tests (zeros, Tr) // sstd::print 関数のテストを書くように
//	TEST_bmat();

	
	printf("\n■ measureTime_stop----------------\n"); sstd::measureTime_stop(timem); sstd::pauseIfWin32();
	return 0;
}

//-----------------------------------------------------------------------

void TEST_measureTime_sleep(){
	printf("■ measureTime_start---------------\n\n");
	time_m timem; sstd::measureTime_start(timem);

	// something you want to mesure time.
	printf("■ sleep\n\n");
//	sstd::sleep_hour(1);
//	sstd::sleep_min (1);
	sstd::sleep_s   (1);
	sstd::sleep_ms  (1000);
	sstd::sleep_us  (1000*1000);
	sstd::sleep_ns  (1000*1000*1000);

	printf("■ measureTime_stop----------------\n");
	sstd::measureTime_stop(timem);
	printf("\n");
}
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
void TEST_print(){
	sstd::print("■ sstd::print");

	//===

	bool tf1 = true;  sstd::print(tf1);
	bool tf2 = false; sstd::print(tf2);
	
	//===
	
	char c = 'c';  sstd::print(c);
	
	//===

	// signed
	int8  s8  = -1; sstd::print(s8);
	int16 s16 = -2; sstd::print(s16);
	int32 s32 = -3; sstd::print(s32);
	int64 s64 = -4; sstd::print(s64);

	// unsigned
	uint8  u8  = 1; sstd::print(u8);
	uint16 u16 = 2; sstd::print(u16);
	uint32 u32 = 3; sstd::print(u32);
	uint64 u64 = 4; sstd::print(u64);

	float  f  = -1.23; sstd::print(f);
	double d  = -1.23; sstd::print(d);

	sstd::print("char*");
	sstd::print(std::string("std::string"));
	sstd::print(sstd::ssprintf("std::string"));
	
	//===

	std::vector<bool> v_bool = {true, false, true, false}; sstd::print(v_bool);
	std::vector<char> v_char = {'a', 'b', 'c', 'd'}; sstd::print(v_char);

	std::vector<int8>  v_s8  = {-1, 2, 3, 4}; sstd::print(v_s8);
	std::vector<int16> v_s16 = {1, -2, 3, 4}; sstd::print(v_s16);
	std::vector<int32> v_s32 = {1, 2, -3, 4}; sstd::print(v_s32);
	std::vector<int64> v_s64 = {1, 2, 3, -4}; sstd::print(v_s64);

	std::vector<uint8>  v_u8  = {1, 2, 3, 4}; sstd::print(v_u8);
	std::vector<uint16> v_u16 = {1, 2, 3, 4}; sstd::print(v_u16);
	std::vector<uint32> v_u32 = {1, 2, 3, 4}; sstd::print(v_u32);
	std::vector<uint64> v_u64 = {1, 2, 3, 4}; sstd::print(v_u64);

	std::vector<float>  v_f = {1.1f, 2.2f, 3.3f, 4.4f}; sstd::print(v_f);
	std::vector<double> v_d = {1.1, 2.2, 3.3, 4.4}; sstd::print(v_d);

	std::vector<std::string> v_str = {"abc", "def"}; sstd::print(v_str);
	
	//===

	std::vector<std::vector<bool>> vv_bool = {{true, false, true, false}, {false, true, false, true}}; sstd::print(vv_bool);
	std::vector<std::vector<char>> vv_char = {{'a', 'b'}, {'c', 'd'}}; sstd::print(vv_char);
	
	std::vector<std::vector<int8>>  vv_s8  = {{-1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::print(vv_s8);
	std::vector<std::vector<int16>> vv_s16 = {{1, -2, 3, 4}, {5, 6, 7, 8}}; sstd::print(vv_s16);
	std::vector<std::vector<int32>> vv_s32 = {{1, 2, -3, 4}, {5, 6, 7, 8}}; sstd::print(vv_s32);
	std::vector<std::vector<int64>> vv_s64 = {{1, 2, 3, -4}, {5, 6, 7, 8}}; sstd::print(vv_s64);
	
	std::vector<std::vector<uint8>>  vv_u8  = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::print(vv_u8);
	std::vector<std::vector<uint16>> vv_u16 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::print(vv_u16);
	std::vector<std::vector<uint32>> vv_u32 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::print(vv_u32);
	std::vector<std::vector<uint64>> vv_u64 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::print(vv_u64);

	std::vector<std::vector<float>>  vv_f = {{1.1f, 2.2f, 3.3f, 4.4f}, {5.5f, 6.6f, 7.7f, 8.8f}}; sstd::print(vv_f);
	std::vector<std::vector<double>> vv_d = {{1.1, 2.2, 3.3, 4.4}, {5.5, 6.6, 7.7, 8.8}}; sstd::print(vv_d);
	
//	std::vector<std::vector<std::string>> vv_str = {{"abc", "def"}, {"ghi", "jkl"}}; sstd::print(vv_str); // gcc 5.4.0
	std::vector<std::vector<std::string>> vv_str = {{std::string("abc"), std::string("def")}, {std::string("ghi"), std::string("jkl")}}; sstd::print(vv_str); // gcc 4.4.7
	printf("\n");
}
void TEST_printn(){
	sstd::print("■ sstd::printn");
	
	//===

	bool tf1 = true;  sstd::printn(tf1);
	bool tf2 = false; sstd::printn(tf2);
	
	//===

	char c = 'c';  sstd::printn(c);
	
	//===

	// signed
	int8  s8  = -1; sstd::printn(s8);
	int16 s16 = -2; sstd::printn(s16);
	int32 s32 = -3; sstd::printn(s32);
	int64 s64 = -4; sstd::printn(s64);

	// unsigned
	uint8  u8  = 1; sstd::printn(u8);
	uint16 u16 = 2; sstd::printn(u16);
	uint32 u32 = 3; sstd::printn(u32);
	uint64 u64 = 4; sstd::printn(u64);

	float  f  = -1.23; sstd::printn(f);
	double d  = -1.23; sstd::printn(d);

	sstd::printn("char*");
	sstd::printn(std::string("std::string"));
	
	//===

	std::vector<bool> v_bool = {true, false, true, false}; sstd::printn(v_bool);
	std::vector<char> v_char = {'a', 'b', 'c', 'd'}; sstd::printn(v_char);

	std::vector<int8>  v_s8  = {-1, 2, 3, 4}; sstd::printn(v_s8);
	std::vector<int16> v_s16 = {1, -2, 3, 4}; sstd::printn(v_s16);
	std::vector<int32> v_s32 = {1, 2, -3, 4}; sstd::printn(v_s32);
	std::vector<int64> v_s64 = {1, 2, 3, -4}; sstd::printn(v_s64);

	std::vector<uint8>  v_u8  = {1, 2, 3, 4}; sstd::printn(v_u8);
	std::vector<uint16> v_u16 = {1, 2, 3, 4}; sstd::printn(v_u16);
	std::vector<uint32> v_u32 = {1, 2, 3, 4}; sstd::printn(v_u32);
	std::vector<uint64> v_u64 = {1, 2, 3, 4}; sstd::printn(v_u64);

	std::vector<float>  v_f = {1.1f, 2.2f, 3.3f, 4.4f}; sstd::printn(v_f);
	std::vector<double> v_d = {1.1, 2.2, 3.3, 4.4}; sstd::printn(v_d);

	std::vector<std::string> v_str = {"abc", "def"}; sstd::printn(v_str);
	
	//===

	std::vector<std::vector<bool>> vv_bool = {{true, false, true, false}, {false, true, false, true}}; sstd::printn(vv_bool);
	std::vector<std::vector<char>> vv_char = {{'a', 'b'}, {'c', 'd'}}; sstd::printn(vv_char);
	
	std::vector<std::vector<int8>>  vv_s8  = {{-1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn(vv_s8);
	std::vector<std::vector<int16>> vv_s16 = {{1, -2, 3, 4}, {5, 6, 7, 8}}; sstd::printn(vv_s16);
	std::vector<std::vector<int32>> vv_s32 = {{1, 2, -3, 4}, {5, 6, 7, 8}}; sstd::printn(vv_s32);
	std::vector<std::vector<int64>> vv_s64 = {{1, 2, 3, -4}, {5, 6, 7, 8}}; sstd::printn(vv_s64);
	
	std::vector<std::vector<uint8>>  vv_u8  = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn(vv_u8);
	std::vector<std::vector<uint16>> vv_u16 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn(vv_u16);
	std::vector<std::vector<uint32>> vv_u32 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn(vv_u32);
	std::vector<std::vector<uint64>> vv_u64 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn(vv_u64);

	std::vector<std::vector<float>>  vv_f = {{1.1f, 2.2f, 3.3f, 4.4f}, {5.5f, 6.6f, 7.7f, 8.8f}}; sstd::printn(vv_f);
	std::vector<std::vector<double>> vv_d = {{1.1, 2.2, 3.3, 4.4}, {5.5, 6.6, 7.7, 8.8}}; sstd::printn(vv_d);
	
//	std::vector<std::vector<std::string>> vv_str = {{"abc", "def"}, {"ghi", "jkl"}}; sstd::printn(vv_str); // gcc 5.4.0
	std::vector<std::vector<std::string>> vv_str = {{std::string("abc"), std::string("def")}, {std::string("ghi"), std::string("jkl")}}; sstd::printn(vv_str); // gcc 4.4.7
	printf("\n");
}
void TEST_printn_all(){
	sstd::print("■ sstd::printn_all");

	//===

	bool tf1 = true;  sstd::printn_all(tf1);
	bool tf2 = false; sstd::printn_all(tf2);
	
	//===

	char c = 'c'; sstd::printn_all(c);
	
	//===

	// signed
	int8  s8  = -1; sstd::printn_all(s8);
	int16 s16 = -2; sstd::printn_all(s16);
	int32 s32 = -3; sstd::printn_all(s32);
	int64 s64 = -4; sstd::printn_all(s64);

	// unsigned
	uint8  u8  = 1; sstd::printn_all(u8);
	uint16 u16 = 2; sstd::printn_all(u16);
	uint32 u32 = 3; sstd::printn_all(u32);
	uint64 u64 = 4; sstd::printn_all(u64);

	float  f  = -1.23; sstd::printn_all(f);
	double d  = -1.23; sstd::printn_all(d);

	sstd::printn_all("char*");
	sstd::printn_all(std::string("std::string"));
	
	//===

	std::vector<bool> v_bool = {true, false, true, false}; sstd::printn_all(v_bool);
	std::vector<char> v_char = {'a', 'b', 'c', 'd'}; sstd::printn_all(v_char);

	std::vector<int8>  v_s8  = {-1, 2, 3, 4}; sstd::printn_all(v_s8);
	std::vector<int16> v_s16 = {1, -2, 3, 4}; sstd::printn_all(v_s16);
	std::vector<int32> v_s32 = {1, 2, -3, 4}; sstd::printn_all(v_s32);
	std::vector<int64> v_s64 = {1, 2, 3, -4}; sstd::printn_all(v_s64);

	std::vector<uint8>  v_u8  = {1, 2, 3, 4}; sstd::printn_all(v_u8);
	std::vector<uint16> v_u16 = {1, 2, 3, 4}; sstd::printn_all(v_u16);
	std::vector<uint32> v_u32 = {1, 2, 3, 4}; sstd::printn_all(v_u32);
	std::vector<uint64> v_u64 = {1, 2, 3, 4}; sstd::printn_all(v_u64);

	std::vector<float>  v_f = {1.1f, 2.2f, 3.3f, 4.4f}; sstd::printn_all(v_f);
	std::vector<double> v_d = {1.1, 2.2, 3.3, 4.4}; sstd::printn_all(v_d);

	std::vector<std::string> v_str = {"abc", "def"}; sstd::printn_all(v_str);
	
	//===

	std::vector<std::vector<bool>> vv_bool = {{true, false, true, false}, {false, true, false, true}}; sstd::printn_all(vv_bool);
	std::vector<std::vector<char>> vv_char = {{'a', 'b'}, {'c', 'd'}}; sstd::printn_all(vv_char);

	std::vector<std::vector<int8>>  vv_s8  = {{-1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn_all(vv_s8);
	std::vector<std::vector<int16>> vv_s16 = {{1, -2, 3, 4}, {5, 6, 7, 8}}; sstd::printn_all(vv_s16);
	std::vector<std::vector<int32>> vv_s32 = {{1, 2, -3, 4}, {5, 6, 7, 8}}; sstd::printn_all(vv_s32);
	std::vector<std::vector<int64>> vv_s64 = {{1, 2, 3, -4}, {5, 6, 7, 8}}; sstd::printn_all(vv_s64);
	
	std::vector<std::vector<uint8>>  vv_u8  = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn_all(vv_u8);
	std::vector<std::vector<uint16>> vv_u16 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn_all(vv_u16);
	std::vector<std::vector<uint32>> vv_u32 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn_all(vv_u32);
	std::vector<std::vector<uint64>> vv_u64 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn_all(vv_u64);

	std::vector<std::vector<float>>  vv_f = {{1.1f, 2.2f, 3.3f, 4.4f}, {5.5f, 6.6f, 7.7f, 8.8f}}; sstd::printn_all(vv_f);
	std::vector<std::vector<double>> vv_d = {{1.1, 2.2, 3.3, 4.4}, {5.5, 6.6, 7.7, 8.8}}; sstd::printn_all(vv_d);
	
//	std::vector<std::vector<std::string>> vv_str = {{"abc", "def"}, {"ghi", "jkl"}}; sstd::printn_all(vv_str); // gcc 5.4.0
	std::vector<std::vector<std::string>> vv_str = {{std::string("abc"), std::string("def")}, {std::string("ghi"), std::string("jkl")}}; sstd::printn_all(vv_str); // gcc 4.4.7
	printf("\n");
}
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
void TEST_mkdir(){
	printf("■ mkdir\n\n");
	sstd::mkdir("./test_mkdir/abc/def"); // enable to make multilayer directory by one step.
	sstd::mkdir(std::string("./test_mkdir/abc/def")); // enable to make multilayer directory by one step.
}
void TEST_rm(){
	printf("■ rm\n\n");

	sstd::mkdir("./test_rm/abc/def");
	sstd::mkdir("./test_rm/abc2/def");
	{ sstd::file fp; fp.fopen("./test_rm/abc/def/abc.txt", "w"); }
	{ sstd::file fp; fp.fopen("./test_rm/abc/abc.txt",     "w"); }
	{ sstd::file fp; fp.fopen("./test_rm/abc/xxx",         "w"); }
	{ sstd::file fp; fp.fopen("./test_rm/abc2/xxx",        "w"); }
	{ sstd::file fp; fp.fopen("./test_rm/123.txt",         "w"); }

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
	printf("  □ readAll_withoutBOM & splitByLine\n");
	std::string str_tI = sstd::readAll_withoutBOM(R"(./tinyInterpreter.txt)");
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
	std::string sstd::removeSpace_of_HeadAndTail(const uchar* str);
	std::vector<std::string> sstd::removeSpace_of_HeadAndTail(const std::vector<std::string>& vec);
	//*/
}
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
void TEST_pause(){
//	printf("■ #define UsePause\n");
	sstd::pause();
//	printf("■ #define UsePauseIfWin32\n");
	sstd::pauseIfWin32(); // win32 の場合のみ停止
//	printf("\n");
}

//-----------------------------------------------------------------------

#define TEST_c2py_builtIn(type, typeTEST, pConstTypeTEST, pTypeTEST, builtinTypeTEST, pBuiltinTypeTEST)	\
	type buf_builtIn=(type)0; buf_builtIn=~buf_builtIn;					\
																		\
	sstd::c2py<type> py_builtIn("./tmpDir", "test_functions", "py_builtIn", typeTEST); \
	type ret;															\
	sstd::printn(buf_builtIn==py_builtIn(&ret, buf_builtIn));			\
	sstd::printn(ret);													\
	printf("\n");														\
																		\
	std::vector<type> vecBuiltIn={buf_builtIn, (type)(buf_builtIn-1), (type)(buf_builtIn-2), 0, 1, 2}; \
																		\
	sstd::c2py<void> py_pBuiltIn_const("./tmpDir", "test_functions", "py_pBuiltIn", pConstTypeTEST); /*書き戻しを行わない*/ \
	py_pBuiltIn_const(&vecBuiltIn[0], vecBuiltIn.size());				\
	sstd::printn(vecBuiltIn);											\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pBuiltIn("./tmpDir", "test_functions", "py_pBuiltIn", pTypeTEST); /*書き戻しを行う*/ \
	py_pBuiltIn(&vecBuiltIn[0], vecBuiltIn.size());						\
	sstd::printn(vecBuiltIn);											\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pBuiltIn_cnvBuiltin("./tmpDir", "test_functions", "py_pBuiltIn_cnvBuiltin", builtinTypeTEST); /*書き戻しを行う*/ \
	py_pBuiltIn_cnvBuiltin(&vecBuiltIn[0], vecBuiltIn.size());			\
	sstd::printn(vecBuiltIn);											\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pBuiltIn_pCnvBuiltin("./tmpDir", "test_functions", "py_pBuiltIn_pCnvBuiltin", pBuiltinTypeTEST); /*書き戻しを行う*/ \
	py_pBuiltIn_pCnvBuiltin(&vecBuiltIn[0], vecBuiltIn.size());			\
	sstd::printn(vecBuiltIn);											\
	printf("\n");

#define TEST_c2py_floatXX(type, typeTEST, pConstTypeTEST, pTypeTEST, builtinTypeTEST, pBuiltinTypeTEST)	\
	sstd::c2py<type> py_float("./tmpDir", "test_functions", "py_floatXX", typeTEST); \
	type ret;															\
	sstd::printn(py_float(&ret, (type)1.2345));							\
	sstd::printn(ret);													\
	printf("\n");														\
																		\
	std::vector<type> vecFloat={1.23, 4.56, 7.0, 0, 1, 2};				\
																		\
	sstd::c2py<void> py_pFloat_const("./tmpDir", "test_functions", "py_pFloatXX", pConstTypeTEST); /*書き戻しを行わない*/ \
	py_pFloat_const(&vecFloat[0], vecFloat.size());						\
	sstd::printn(vecFloat);												\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pFloat("./tmpDir", "test_functions", "py_pFloatXX", pTypeTEST); /*書き戻しを行う*/ \
	py_pFloat(&vecFloat[0], vecFloat.size());							\
	sstd::printn(vecFloat);												\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pFloat_cnvBuiltin("./tmpDir", "test_functions", "py_pFloatXX_cnvBuiltin", builtinTypeTEST); /*書き戻しを行う*/ \
	py_pFloat_cnvBuiltin(&vecFloat[0], vecFloat.size());				\
	sstd::printn(vecFloat);												\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pFloat_pCnvBuiltin("./tmpDir", "test_functions", "py_pFloatXX_pCnvBuiltin", pBuiltinTypeTEST); /*書き戻しを行う*/ \
	py_pFloat_pCnvBuiltin(&vecFloat[0], vecFloat.size());				\
	sstd::printn(vecFloat);												\
	printf("\n");

#define TEST_c2py_vecXXX(type, typeTEST, pConstTypeTEST, pTypeTEST, builtinTypeTEST, pBuiltinTypeTEST) \
	type buf_builtIn=(type)0; buf_builtIn=~buf_builtIn;					\
																		\
	std::vector<type> vecXXX={buf_builtIn, (type)(buf_builtIn-1), (type)(buf_builtIn-2), 0, 1, 2, 3}; \
	sstd::printn(vecXXX);												\
	printf("\n");														\
																		\
	sstd::c2py<std::vector<type>> py_vecXXX("./tmpDir", "test_functions", "py_vecX", typeTEST); \
	std::vector<type> ret;												\
	sstd::printn(py_vecXXX(&ret, vecXXX));								\
	sstd::printn(ret);													\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pVecXXX_const("./tmpDir", "test_functions", "py_pVecX_const", pConstTypeTEST); /*書き戻しを行わない*/ \
	py_pVecXXX_const(&vecXXX);											\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pVecXXX_cnvBuiltin("./tmpDir", "test_functions", "py_pVecX", builtinTypeTEST); /*書き戻しを行う*/ \
	py_pVecXXX_cnvBuiltin(&vecXXX); /*ndarray で渡した場合は，追記できない*/ \
	sstd::printn(vecXXX);												\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pVecXXX_pCnvBuiltin("./tmpDir", "test_functions", "py_pVecX_pCnvBuiltin", pBuiltinTypeTEST); /*書き戻しを行う*/ \
	py_pVecXXX_pCnvBuiltin(&vecXXX); /*ndarray で渡した場合は，追記できない*/ \
	sstd::printn(vecXXX);												\
	printf("\n");

#define TEST_c2py_vecFolatXX(type, typeTEST, pConstTypeTEST, pTypeTEST, builtinTypeTEST, pBuiltinTypeTEST)	\
	std::vector<type> vecXXX={-3, -2, -1, 0, 1, 2, 3};					\
	sstd::printn(vecXXX);												\
	printf("\n");														\
																		\
	sstd::c2py<std::vector<type>> py_vecXXX("./tmpDir", "test_functions", "py_vecX", typeTEST); \
	std::vector<type> ret;												\
	sstd::printn(py_vecXXX(&ret, vecXXX));								\
	sstd::printn(ret);													\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pVecXXX_const("./tmpDir", "test_functions", "py_pVecX_const", pConstTypeTEST); /*書き戻しを行わない*/ \
	py_pVecXXX_const(&vecXXX);											\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pVecXXX("./tmpDir", "test_functions", "py_pVecX", pTypeTEST); /*書き戻しを行う*/ \
	py_pVecXXX(&vecXXX); /*ndarray で渡した場合は，追記できない*/		\
	sstd::printn(vecXXX);												\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pVecXXX_cnvBuiltin("./tmpDir", "test_functions", "py_pVecX", builtinTypeTEST); /*書き戻しを行う*/ \
	py_pVecXXX_cnvBuiltin(&vecXXX); /*ndarray で渡した場合は，追記できない*/ \
	sstd::printn(vecXXX);												\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pVecXXX_pCnvBuiltin("./tmpDir", "test_functions", "py_pVecX_pCnvBuiltin", pBuiltinTypeTEST); /*書き戻しを行う*/ \
	py_pVecXXX_pCnvBuiltin(&vecXXX); /*ndarray で渡した場合は，追記できない*/ \
	sstd::printn(vecXXX);												\
	printf("\n");

#define TEST_c2py_matBool(typeMat, type, typeTEST, pConstTypeTEST, pTypeTEST, builtinTypeTEST, pBuiltinTypeTEST) \
	typeMat<type> matB{{true, false, false},{false, true, false},{false, false, true},{true, false, false}}; \
	sstd::printn(matB);													\
	printf("\n");														\
																		\
	sstd::c2py<typeMat<type>> py_matB("./tmpDir", "test_functions", "py_matX", typeTEST); \
	typeMat<type> ret;													\
	sstd::printn(py_matB(&ret, matB));									\
	sstd::printn(ret);													\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatB_const("./tmpDir", "test_functions", "py_pMatX_const", pConstTypeTEST); /*書き戻しを行わない*/	\
	py_pMatB_const(&matB);												\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatB("./tmpDir", "test_functions", "py_pMatBool", pTypeTEST); /*書き戻しを行う*/ \
	py_pMatB(&matB); /*ndarray で渡した場合は，追記できない*/			\
	sstd::printn(matB);													\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatB_cnvBuiltin("./tmpDir", "test_functions", "py_pMatBool", builtinTypeTEST); /*書き戻しを行う*/ \
	py_pMatB_cnvBuiltin(&matB); /*ndarray で渡した場合は，追記できない*/			\
	sstd::printn(matB);													\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatB_pCnvBuiltin("./tmpDir", "test_functions", "py_pMatBool_pCnvBuiltin", pBuiltinTypeTEST); /*書き戻しを行う*/ \
	py_pMatB_pCnvBuiltin(&matB); /*ndarray で渡した場合は，追記できない*/ \
	sstd::printn(matB);													\
	printf("\n");

#define TEST_c2py_matChar(typeMat, type, typeTEST, pConstTypeTEST, pTypeTEST, builtinTypeTEST, pBuiltinTypeTEST) \
	typeMat<type> matC{{'a', 'b', 'c'},{'d', 'e', 'f'},{'g', 'h', 'i'},{'j', 'k', 'l'}}; \
	sstd::printn(matC);													\
	printf("\n");														\
																		\
	sstd::c2py<typeMat<type>> py_matX("./tmpDir", "test_functions", "py_matX", typeTEST); \
	typeMat<type> ret;													\
	sstd::printn(py_matX(&ret, matC));									\
	sstd::printn(ret);													\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatC_const("./tmpDir", "test_functions", "py_pMatX_const", pConstTypeTEST); /*書き戻しを行わない*/	\
	py_pMatC_const(&matC);												\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatC("./tmpDir", "test_functions", "py_pMatChar", pTypeTEST); /*書き戻しを行う*/ \
	py_pMatC(&matC); /*ndarray で渡した場合は，追記できない*/			\
	sstd::printn(matC);													\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatC_cnvBuiltin("./tmpDir", "test_functions", "py_pMatChar", builtinTypeTEST); /*書き戻しを行う*/ \
	py_pMatC_cnvBuiltin(&matC); /*ndarray で渡した場合は，追記できない*/ \
	sstd::printn(matC);													\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatC_pCnvBuiltin("./tmpDir", "test_functions", "py_pMatChar_pCnvBuiltin", pBuiltinTypeTEST); /*書き戻しを行う*/ \
	py_pMatC_pCnvBuiltin(&matC); /*ndarray で渡した場合は，追記できない*/ \
	sstd::printn(matC);													\
	printf("\n");

#define TEST_c2py_matXXX(typeMat, type, typeTEST, pConstTypeTEST, pTypeTEST, builtinTypeTEST, pBuiltinTypeTEST) \
	type buf_builtIn=(type)0; buf_builtIn=~buf_builtIn;					\
																		\
	typeMat<type> matD{{buf_builtIn, (type)(buf_builtIn-1), 3},{4, 5, 6},{7, 8, 9},{10, 11, 12}}; \
	sstd::printn(matD);													\
	printf("\n");														\
																		\
	sstd::c2py<typeMat<type>> py_matX("./tmpDir", "test_functions", "py_matX", typeTEST); \
	typeMat<type> ret;													\
	sstd::printn(py_matX(&ret, matD));									\
	sstd::printn(ret);													\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatX_const("./tmpDir", "test_functions", "py_pMatX_const", pConstTypeTEST); /*書き戻しを行わない*/ \
	py_pMatX_const(&matD);												\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatX("./tmpDir", "test_functions", "py_pMatX", pTypeTEST); /*書き戻しを行う*/ \
	py_pMatX(&matD); /*ndarray で渡した場合は，追記できない*/			\
	sstd::printn(matD);													\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatX_cnvBuiltin("./tmpDir", "test_functions", "py_pMatX", builtinTypeTEST); /*書き戻しを行う*/ \
	py_pMatX_cnvBuiltin(&matD); /*ndarray で渡した場合は，追記できない*/ \
	sstd::printn(matD);													\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatX_pCnvBuiltin("./tmpDir", "test_functions", "py_pMatX_pCnvBuiltin", pBuiltinTypeTEST); /*書き戻しを行う*/ \
	py_pMatX_pCnvBuiltin(&matD); /*ndarray で渡した場合は，追記できない*/ \
	sstd::printn(matD);													\
	printf("\n");

#define TEST_c2py_matFolatXX(typeMat, type, typeTEST, pConstTypeTEST, pTypeTEST, builtinTypeTEST, pBuiltinTypeTEST) \
	typeMat<type> matD{{1, 2, 3},{4, 5, 6},{7, 8, 9},{10, 11, 12}};		\
	sstd::printn(matD);													\
	printf("\n");														\
																		\
	sstd::c2py<typeMat<type>> py_matX("./tmpDir", "test_functions", "py_matX", typeTEST); \
	typeMat<type> ret;													\
	sstd::printn(py_matX(&ret, matD));									\
	sstd::printn(ret);													\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatX_const("./tmpDir", "test_functions", "py_pMatX_const", pConstTypeTEST); /*書き戻しを行わない*/ \
	py_pMatX_const(&matD);												\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatX("./tmpDir", "test_functions", "py_pMatX", pTypeTEST); /*書き戻しを行う*/ \
	py_pMatX(&matD); /*ndarray で渡した場合は，追記できない*/			\
	sstd::printn(matD);													\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatX_cnvBuiltin("./tmpDir", "test_functions", "py_pMatX", pTypeTEST); /*書き戻しを行う*/ \
	py_pMatX_cnvBuiltin(&matD); /*ndarray で渡した場合は，追記できない*/ \
	sstd::printn(matD);													\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatX_pCnvBuiltin("./tmpDir", "test_functions", "py_pMatX_pCnvBuiltin", pTypeTEST); /*書き戻しを行う*/ \
	py_pMatX_pCnvBuiltin(&matD); /*ndarray で渡した場合は，追記できない*/ \
	sstd::printn(matD);													\
	printf("\n");

#define TEST_c2py_matStr(typeMat, type, typeTEST, pConstTypeTEST, pTypeTEST, builtinTypeTEST, pBuiltinTypeTEST) \
	typeMat<type> matStr{{"a", "ab", "abc"},{"abcd", "abcde", "abcdef"},{"7", "8", "9"},{"10", "11", "12"}}; \
	sstd::printn(matStr);												\
	printf("\n");														\
																		\
	/* mat<str> 引数は，不可．恐らく，gcc 5.4.0 の可変長引数の実装が，そもそもクラス型を想定していないので，バグを踏む．-> ポインタ渡しなら問題ない．*/ \
	/* sstd::c2py<sstd::mat<std::string>> py_matStr("./tmpDir", "test_functions", "py_matX", "mat<str>, mat<str>"); */ \
	/* sstd::printn(py_matStr(matStr)); */								\
	/* printf("\n"); */													\
	sstd::c2py<typeMat<type>> py_matStr("./tmpDir", "test_functions", "py_matX", typeTEST); \
	typeMat<type> ret;													\
	sstd::printn(py_matStr(&ret, &matStr));								\
	sstd::printn(ret);													\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatX_const("./tmpDir", "test_functions", "py_pVecX_const", pConstTypeTEST); /*書き戻しを行わない*/ \
	py_pMatX_const(&matStr);											\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatX("./tmpDir", "test_functions", "py_pMatStr", pTypeTEST); /*書き戻しを行う*/ \
	py_pMatX(&matStr); /* ndarray で渡した場合は，追記できない*/ 		\
	sstd::printn(matStr);												\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatX_cnvBuiltin("./tmpDir", "test_functions", "py_pMatStr", builtinTypeTEST); /*書き戻しを行う*/ \
	py_pMatX_cnvBuiltin(&matStr); /* ndarray で渡した場合は，追記できない*/	\
	sstd::printn(matStr);												\
	printf("\n");														\
																		\
	sstd::c2py<void> py_pMatX_pCnvBuiltin("./tmpDir", "test_functions", "py_pMatStr_pCnvBuiltin", pBuiltinTypeTEST); /*書き戻しを行う*/ \
	py_pMatX_pCnvBuiltin(&matStr); /* ndarray で渡した場合は，追記できない*/ \
	sstd::printn(matStr);												\
	printf("\n");

void TEST_c2py(){
	printf("■ C++ to Python. (Running any python function from C++.)\n");
	// テストを書きながら開発を進める．

	//*
	{
		printf("  □ empty args\n");
		sstd::c2py<void> py_emptyArg("./tmpDir", "test_functions", "py_emptyArg", "void");
		py_emptyArg();
		printf("\n");
	}
	//*/
	/*
	{
		printf("  □ empty args (other dir)\n");
		sstd::c2py<void> py_emptyArg("./tmpDir", "./testPy/test_functions", "py_emptyArg", "void");
		py_emptyArg();
		printf("\n");
	}
	//*/
	
	//*
	// measure time 01
	{
		printf("■ measureTime_start---------------\n\n"); time_m timem; sstd::measureTime_start(timem);
		
		sstd::c2py<void> py_empty("./tmpDir", "test_functions", "py_empty", "void");
		for(uint i=0; i<100; i++){ py_empty(); }
		
		printf("\n■ measureTime_stop----------------\n"); sstd::measureTime_stop(timem); sstd::pauseIfWin32();
	}
	//*/
	
	/*
	// measure time 02
	{
		printf("■ measureTime_start---------------\n\n"); time_m timem; sstd::measureTime_start(timem);
		
		for(uint i=0; i<100; i++){
			sstd::c2py<void> py_empty("./tmpDir", "test_functions", "py_empty", "void");
			py_empty();
		}
		
		printf("\n■ measureTime_stop----------------\n"); sstd::measureTime_stop(timem); sstd::pauseIfWin32();
	}
	//*/
	
	//-----------------------------------------------------------------------
	
	/*
	{
		printf("  □ bool, const bool*, bool*\n");

		sstd::c2py<bool> py_bool("./tmpDir", "test_functions", "py_bool", "bool, ret bool*, bool");
		bool ret=false;
		sstd::printn( true==py_bool(&ret,  true)); sstd::printn(ret);
		sstd::printn(false==py_bool(&ret, false)); sstd::printn(ret);
		printf("\n");

		bool boolArr[] = {true, false, true, false, false, true}; bool* pBool = &boolArr[0];

		sstd::c2py<void> py_pBool_const("./tmpDir", "test_functions", "py_pBool", "void, const bool*, len"); // 書き戻しを行わない
		py_pBool_const(pBool, 6);
		for(uint i=0; i<6; i++){ if(pBool[i]){printf("T ");}else{printf("F ");} }printf("\n");
		printf("\n");

		sstd::c2py<void> py_pBool("./tmpDir", "test_functions", "py_pBool", "void, bool*, len"); // 書き戻しを行う
		py_pBool(pBool, 6);
		for(uint i=0; i<6; i++){ if(pBool[i]){printf("T ");}else{printf("F ");} }printf("\n");
		printf("\n");
	
		//---
	
		sstd::c2py<void> py_pBool_builtin("./tmpDir", "test_functions", "py_pBool_builtin", "void, bool*|~, len"); // 書き戻しを行う
		py_pBool_builtin(pBool, 6);
		for(uint i=0; i<6; i++){ if(pBool[i]){printf("T ");}else{printf("F ");} }printf("\n");
		printf("\n");

		sstd::c2py<void> py_pBool_pBuiltin("./tmpDir", "test_functions", "py_pBool_pBuiltin", "void, bool*|*~, len"); // 書き戻しを行う
		py_pBool_pBuiltin(pBool, 6);
		for(uint i=0; i<6; i++){ if(pBool[i]){printf("T ");}else{printf("F ");} }printf("\n");
		printf("\n");
	}
	//*/
	
	//-----------------------------------------------------------------------
	
	/*
	{
		printf("  □ char, const char*, char*\n");

		sstd::c2py<char> py_char("./tmpDir", "test_functions", "py_char", "char, ret char*, char");
		char ret='0';
		sstd::printn('C'==py_char(&ret, 'C')); sstd::printn(ret);
		printf("\n");
	
		//	sstd::c2py<void> py_pChar_const("./tmpDir", "test_functions", "py_pChar", "void, const char*, len"); // この場合，エラーを表示する．
		sstd::c2py<void> py_pChar_const("./tmpDir", "test_functions", "py_pChar", "void, const char*"); // 書き戻しを行わない
		py_pChar_const("string");
		printf("\n");
	
		std::string str_pChar="string";
		char* pChar=&str_pChar[0];
	
		sstd::c2py<void> py_pChar("./tmpDir", "test_functions", "py_pChar", "void, char*"); // 書き戻しを行う // Python says [TypeError: 'str' object does not support item assignment] so, this might be impossible.
		py_pChar(pChar);
		sstd::printn(pChar);
		printf("\n");

		//---

		sstd::c2py<void> py_pChar_builtin("./tmpDir", "test_functions", "py_pChar", "void, char*|~"); // 書き戻しを行う // Python says [TypeError: 'str' object does not support item assignment] so, this might be impossible.
		py_pChar_builtin(pChar);
		sstd::printn(pChar);
		printf("\n");

		sstd::c2py<void> py_pChar_pBuiltin("./tmpDir", "test_functions", "py_pChar_pBuiltin", "void, char*|*~"); // 書き戻しを行う // Python says [TypeError: 'str' object does not support item assignment] so, this might be impossible.
		py_pChar_pBuiltin(pChar);
		sstd::printn(pChar);
		printf("\n");
	}
	//*/
	
	//-----------------------------------------------------------------------

	/*
	printf("  ■ uchar, const uchar*, uchar*\n"   ); { TEST_c2py_builtIn(uchar,  "uchar, ret uchar*, uchar",    "void, const uchar*, len",  "void, uchar*, len" , "void, uchar*|~, len",  "void, uchar*|*~, len" ); }
	printf("  ■ int8, const int8*, int8*\n"      ); { TEST_c2py_builtIn(int8,   "int8, ret int8*, int8",       "void, const int8*, len",   "void, int8*, len",   "void, int8*|~, len",   "void, int8*|*~, len"  ); }
	printf("  ■ int16, const int16*, int16*\n"   ); { TEST_c2py_builtIn(int16,  "int16, ret int16*, int16",    "void, const int16*, len",  "void, int16*, len",  "void, int16*|~, len",  "void, int16*|*~, len" ); }
	printf("  ■ int32, const int32*, int32*\n"   ); { TEST_c2py_builtIn(int32,  "int32, ret int32*, int32",    "void, const int32*, len",  "void, int32*, len",  "void, int32*|~, len",  "void, int32*|*~, len" ); }
	printf("  ■ int64, const int64*, int64*\n"   ); { TEST_c2py_builtIn(int64,  "int64, ret int64*, int64",    "void, const int64*, len",  "void, int64*, len",  "void, int64*|~, len",  "void, int64*|*~, len" ); }
	printf("  ■ uint8, const uint8*, uint8*\n"   ); { TEST_c2py_builtIn(uint8,  "uint8, ret uint8*, uint8",    "void, const uint8*, len",  "void, uint8*, len",  "void, uint8*|~, len",  "void, uint8*|*~, len" ); }
	printf("  ■ uint16, const uint16*, uint16*\n"); { TEST_c2py_builtIn(uint16, "uint16, ret uint16*, uint16", "void, const uint16*, len", "void, uint16*, len", "void, uint16*|~, len", "void, uint16*|*~, len"); }
	printf("  ■ uint32, const uint32*, uint32*\n"); { TEST_c2py_builtIn(uint32, "uint32, ret uint32*, uint32", "void, const uint32*, len", "void, uint32*, len", "void, uint32*|~, len", "void, uint32*|*~, len"); }
	printf("  ■ uint64, const uint64*, uint64*\n"); { TEST_c2py_builtIn(uint64, "uint64, ret uint64*, uint64", "void, const uint64*, len", "void, uint64*, len", "void, uint64*|~, len", "void, uint64*|*~, len"); }
	
	printf("  ■ float\n" ); { TEST_c2py_floatXX(float, "float, ret float*, float",     "void, const float*, len",  "void, float*, len",  "void, float*|~, len",  "void, float*|*~, len" ); }
	printf("  ■ double\n"); { TEST_c2py_floatXX(double, "double, ret double*, double", "void, const double*, len", "void, double*, len", "void, double*|~, len", "void, double*|*~, len"); }
	//*/
	
	//-----------------------------------------------------------------------
	
	/*
	{
		printf("  □ std::string\n");
	
		std::string str="01234abcdABCD";
	
		sstd::c2py<std::string> py_str("./tmpDir", "test_functions", "py_str", "str, ret str*, str");
		std::string ret;
		sstd::printn(py_str(&ret, str));
		sstd::printn(ret);
		printf("\n");

		sstd::c2py<void> py_pStr_const("./tmpDir", "test_functions", "py_pStr", "void, const str*"); // 書き戻しを行わない
		py_pStr_const(&str);
		sstd::printn(str);
		printf("\n");

		sstd::c2py<void> py_pStr("./tmpDir", "test_functions", "py_pStr", "void, str*"); // 書き戻しを行う // Python says "'str' object does not support item assignment".
		py_pStr(&str);
		sstd::printn(str);
		printf("\n");

		//---
	
		sstd::c2py<void> py_pStr_cnvBuiltin("./tmpDir", "test_functions", "py_pStr", "void, str*|~"); // 書き戻しを行う // Python says "'str' object does not support item assignment".
		py_pStr_cnvBuiltin(&str);
		sstd::printn(str);
		printf("\n");

		sstd::c2py<void> py_pStr_pCnvBuiltin("./tmpDir", "test_functions", "py_pStr_pCnvBuiltin", "void, str*|*~"); // 書き戻しを行う
		py_pStr_pCnvBuiltin(&str);
		sstd::printn(str);
		printf("\n");
	}
	//*/
	
	//-----------------------------------------------------------------------

	// std::vector<T>

	/*
	{
		printf("  ■ std::vector<bool>\n");
	
		std::vector<bool> vecBool={true, false, false, true};
		sstd::printn(vecBool);
		printf("\n");

		sstd::c2py<std::vector<bool>> py_vecBool("./tmpDir", "test_functions", "py_vecBool", "vec<bool>, ret vec<bool>*, vec<bool>");
		std::vector<bool> ret;
		sstd::printn(py_vecBool(&ret, vecBool));
		sstd::printn(ret);
		printf("\n");
	
		sstd::c2py<void> py_pVecBool_const("./tmpDir", "test_functions", "py_pVecBool_const", "void, const vec<bool>*"); // 書き戻しを行わない
		py_pVecBool_const(&vecBool);
		printf("\n");

		sstd::c2py<void> py_pVecBool("./tmpDir", "test_functions", "py_pVecBool", "void, vec<bool>*"); // 書き戻しを行う
		py_pVecBool(&vecBool);
		sstd::printn(vecBool);
		printf("\n");

		//---
	
		sstd::c2py<void> py_pVecBool_cnvBuiltin("./tmpDir", "test_functions", "py_pVecBool", "void, vec<bool>*|~"); // 書き戻しを行う
		py_pVecBool_cnvBuiltin(&vecBool);
		sstd::printn(vecBool);
		printf("\n");

		sstd::c2py<void> py_pVecBool_pCnvBuiltin("./tmpDir", "test_functions", "py_pVecBool_pCnvBuiltin", "void, vec<bool>*|*~"); // 書き戻しを行う
		py_pVecBool_pCnvBuiltin(&vecBool);
		sstd::printn(vecBool);
		printf("\n");
	}
	//*/
	
	/*
	{
		printf("  ■ std::vector<char>\n" );
	
		std::vector<char> vecChar={'a', 'b', 'c', 'd'};
		sstd::printn(vecChar);
		printf("\n");

		sstd::c2py<std::vector<char>> py_vecChar("./tmpDir", "test_functions", "py_vecChar", "vec<char>, vec<char>");
		sstd::printn(py_vecChar(vecChar));
		printf("\n");

		sstd::c2py<void> py_pVecChar_const("./tmpDir", "test_functions", "py_pVecChar_const", "void, const vec<char>*"); // 書き戻しを行わない
		py_pVecChar_const(&vecChar);
		printf("\n");

		sstd::c2py<void> py_pVecChar("./tmpDir", "test_functions", "py_pVecChar", "void, vec<char>*"); // 書き戻しを行う
		py_pVecChar(&vecChar);
		sstd::printn(vecChar);
		printf("\n");

		//---
	
		sstd::c2py<void> py_pVecChar_cnvBuiltin("./tmpDir", "test_functions", "py_pVecChar", "void, vec<char>*|~"); // 書き戻しを行う
		py_pVecChar_cnvBuiltin(&vecChar);
		sstd::printn(vecChar);
		printf("\n");
	
		sstd::c2py<void> py_pVecChar_pCnvBuiltin("./tmpDir", "test_functions", "py_pVecChar_pCnvBuiltin", "void, vec<char>*|*~"); // 書き戻しを行う
		py_pVecChar_pCnvBuiltin(&vecChar);
		sstd::printn(vecChar);
		printf("\n");
	}
	//*/
	
	/*
	printf("  ■ std::vector<uchar>\n" ); { TEST_c2py_vecXXX( uchar, "vec<uchar>, ret vec<uchar>*, vec<uchar>",    "void, const vec<uchar>*",  "void, vec<uchar>*" , "void, vec<uchar>*|~" , "void, vec<uchar>*|*~" ); }
	printf("  ■ std::vector<int8>\n"  ); { TEST_c2py_vecXXX(  int8, "vec<int8>, ret vec<int8>*, vec<int8>",       "void, const vec<int8>*",   "void, vec<int8>*"  , "void, vec<int8>*|~"  , "void, vec<int8>*|*~"  ); }
	printf("  ■ std::vector<int16>\n" ); { TEST_c2py_vecXXX( int16, "vec<int16>, ret vec<int16>*, vec<int16>",    "void, const vec<int16>*",  "void, vec<int16>*" , "void, vec<int16>*|~" , "void, vec<int16>*|*~" ); }
	printf("  ■ std::vector<int32>\n" ); { TEST_c2py_vecXXX( int32, "vec<int32>, ret vec<int32>*, vec<int32>",    "void, const vec<int32>*",  "void, vec<int32>*" , "void, vec<int32>*|~" , "void, vec<int32>*|*~" ); }
	printf("  ■ std::vector<int64>\n" ); { TEST_c2py_vecXXX( int64, "vec<int64>, ret vec<int64>*, vec<int64>",    "void, const vec<int64>*",  "void, vec<int64>*" , "void, vec<int64>*|~" , "void, vec<int64>*|*~" ); }
	printf("  ■ std::vector<uint8>\n" ); { TEST_c2py_vecXXX( uint8, "vec<uint8>, ret vec<uint8>*, vec<uint8>",    "void, const vec<uint8>*",  "void, vec<uint8>*" , "void, vec<uint8>*|~" , "void, vec<uint8>*|*~" ); }
	printf("  ■ std::vector<uint16>\n"); { TEST_c2py_vecXXX(uint16, "vec<uint16>, ret vec<uint16>*, vec<uint16>", "void, const vec<uint16>*", "void, vec<uint16>*", "void, vec<uint16>*|~", "void, vec<uint16>*|*~"); }
	printf("  ■ std::vector<uint32>\n"); { TEST_c2py_vecXXX(uint32, "vec<uint32>, ret vec<uint32>*, vec<uint32>", "void, const vec<uint32>*", "void, vec<uint32>*", "void, vec<uint32>*|~", "void, vec<uint32>*|*~"); }
	printf("  ■ std::vector<uint64>\n"); { TEST_c2py_vecXXX(uint64, "vec<uint64>, ret vec<uint64>*, vec<uint64>", "void, const vec<uint64>*", "void, vec<uint64>*", "void, vec<uint64>*|~", "void, vec<uint64>*|*~"); }

	printf("  ■ std::vector<float>\n" ); { TEST_c2py_vecFolatXX( float, "vec<float>, ret vec<float>*, vec<float>",   "void, const vec<float>*",  "void, vec<float>*" ,  "void, vec<float>*|~" ,  "void, vec<float>*|*~" ); }
	printf("  ■ std::vector<double>\n"); { TEST_c2py_vecFolatXX(double, "vec<double>, ret vec<double>*, vec<double>", "void, const vec<double>*", "void, vec<double>*", "void, vec<double>*|~", "void, vec<double>*|*~"); }
	//*/
	
	/*
	{
		printf("  ■ std::vector<std::string>\n");
		std::vector<std::string> vecStr={"ABCD", "EF", "GHIJKLMNO"};
		sstd::printn(vecStr.size());
		printf("\n");
	
		sstd::c2py<std::vector<std::string>> py_vecStr("./tmpDir", "test_functions", "py_vecStr", "vec<str>, ret vec<str>*, vec<str>");
		std::vector<std::string> ret;
		sstd::printn(py_vecStr(&ret, vecStr));
		sstd::printn(ret);
		printf("\n");

		sstd::c2py<void> py_pVecStr_const("./tmpDir", "test_functions", "py_pVecStr_const", "void, const vec<str>*"); // 書き戻しを行わない
		py_pVecStr_const(&vecStr);
		printf("\n");

		sstd::c2py<void> py_pVecStr("./tmpDir", "test_functions", "py_pVecStr", "void, vec<str>*"); // 書き戻しを行う // Python says "'str' object does not support item assignment".
		py_pVecStr(&vecStr);
		printf("\n");

		sstd::c2py<void> py_pVecStr_cnvBuiltin("./tmpDir", "test_functions", "py_pVecStr", "void, vec<str>*|~"); // 書き戻しを行う // Python says "'str' object does not support item assignment".
		py_pVecStr_cnvBuiltin(&vecStr);
		printf("\n");

		sstd::c2py<void> py_pVecStr_pCnvBuiltin("./tmpDir", "test_functions", "py_pVecStr_pCnvBuiltin", "void, vec<str>*|*~"); // 書き戻しを行う
		py_pVecStr_pCnvBuiltin(&vecStr);
		sstd::printn(vecStr);
		printf("\n");
	}
	//*/
	
	//-----------------------------------------------------------------------

	// std::mat<T>
	/*
	printf("  ■ sstd::mat<bool>\n"       ); { TEST_c2py_matBool   (sstd::mat, bool,        "mat<bool>, ret mat<bool>*, mat<bool>",       "void, const mat<bool>*",   "void, mat<bool>*",   "void, mat<bool>*|~",   "void, mat<bool>*|*~"  ); }
	printf("  ■ sstd::mat<char>\n"       ); { TEST_c2py_matChar   (sstd::mat, char,        "mat<char>, ret mat<char>*, mat<char>",       "void, const mat<char>*",   "void, mat<char>*",   "void, mat<char>*|~",   "void, mat<char>*|*~"  ); }
	printf("  ■ sstd::mat<int8>\n"       ); { TEST_c2py_matXXX    (sstd::mat, int8,        "mat<int8>, ret mat<int8>*, mat<int8>",       "void, const mat<int8>*",   "void, mat<int8>*",   "void, mat<int8>*|~",   "void, mat<int8>*|*~"  ); }
	printf("  ■ sstd::mat<int16>\n"      ); { TEST_c2py_matXXX    (sstd::mat, int16,       "mat<int16>, ret mat<int16>*, mat<int16>",    "void, const mat<int16>*",  "void, mat<int16>*",  "void, mat<int16>*|~",  "void, mat<int16>*|*~" ); }
	printf("  ■ sstd::mat<int32>\n"      ); { TEST_c2py_matXXX    (sstd::mat, int32,       "mat<int32>, ret mat<int32>*, mat<int32>",    "void, const mat<int32>*",  "void, mat<int32>*" , "void, mat<int32>*|~" , "void, mat<int32>*|*~" ); }
	printf("  ■ sstd::mat<int64>\n"      ); { TEST_c2py_matXXX    (sstd::mat, int64,       "mat<int64>, ret mat<int64>*, mat<int64>",    "void, const mat<int64>*",  "void, mat<int64>*",  "void, mat<int64>*|~",  "void, mat<int64>*|*~" ); }
	printf("  ■ sstd::mat<uint8>\n"      ); { TEST_c2py_matXXX    (sstd::mat, uint8,       "mat<uint8>, ret mat<uint8>*, mat<uint8>",    "void, const mat<uint8>*",  "void, mat<uint8>*",  "void, mat<uint8>*|~",  "void, mat<uint8>*|*~" ); }
	printf("  ■ sstd::mat<uint16>\n"     ); { TEST_c2py_matXXX    (sstd::mat, uint16,      "mat<uint16>, ret mat<uint16>*, mat<uint16>", "void, const mat<uint16>*", "void, mat<uint16>*", "void, mat<uint16>*|~", "void, mat<uint16>*|*~"); }
	printf("  ■ sstd::mat<uint32>\n"     ); { TEST_c2py_matXXX    (sstd::mat, uint32,      "mat<uint32>, ret mat<uint32>*, mat<uint32>", "void, const mat<uint32>*", "void, mat<uint32>*", "void, mat<uint32>*|~", "void, mat<uint32>*|*~"); }
	printf("  ■ sstd::mat<uint64>\n"     ); { TEST_c2py_matXXX    (sstd::mat, uint64,      "mat<uint64>, ret mat<uint64>*, mat<uint64>", "void, const mat<uint64>*", "void, mat<uint64>*", "void, mat<uint64>*|~", "void, mat<uint64>*|*~"); }
	printf("  ■ sstd::mat<float>\n"      ); { TEST_c2py_matFolatXX(sstd::mat, float,       "mat<float>, ret mat<float>*, mat<float>",    "void, const mat<float>*",  "void, mat<float>*" , "void, mat<float>*|~",  "void, mat<float>*|*~" ); }
	printf("  ■ sstd::mat<double>\n"     ); { TEST_c2py_matFolatXX(sstd::mat, double,      "mat<double>, ret mat<double>*, mat<double>", "void, const mat<double>*", "void, mat<double>*", "void, mat<double>*|~", "void, mat<double>*|*~"); }
	printf("  ■ sstd::mat<std::string>\n"); { TEST_c2py_matStr    (sstd::mat, std::string, "mat<str>, ret mat<str>*, mat<str>*",         "void, const mat<str>*",    "void, mat<str>*",    "void, mat<str>*|~",    "void, mat<str>*|*~"   ); } // "mat<str>, mat<str>" は，C++ の可変長引数で受け渡そうとすると，segmentation fault で落ちる．少なくとも gcc 5.4.0 では対応していないので，ポインタで渡しておく．
	//*/
	
	//-----------------------------------------------------------------------
	
	// std::mat_r<T>
	/*
	printf("  ■ sstd::mat_r<bool>\n"       ); { TEST_c2py_matBool   (sstd::mat_r, bool,        "mat_r<bool>, ret mat_r<bool>*, mat_r<bool>",       "void, const mat_r<bool>*",   "void, mat_r<bool>*",   "void, mat_r<bool>*|~",   "void, mat_r<bool>*|*~"  ); }
	printf("  ■ sstd::mat_r<char>\n"       ); { TEST_c2py_matChar   (sstd::mat_r, char,        "mat_r<char>, ret mat_r<char>*, mat_r<char>",       "void, const mat_r<char>*",   "void, mat_r<char>*",   "void, mat_r<char>*|~",   "void, mat_r<char>*|*~"  ); }
	printf("  ■ sstd::mat_r<int8>\n"       ); { TEST_c2py_matXXX    (sstd::mat_r, int8,        "mat_r<int8>, ret mat_r<int8>*, mat_r<int8>",       "void, const mat_r<int8>*",   "void, mat_r<int8>*",   "void, mat_r<int8>*|~",   "void, mat_r<int8>*|*~"  ); }
	printf("  ■ sstd::mat_r<int16>\n"      ); { TEST_c2py_matXXX    (sstd::mat_r, int16,       "mat_r<int16>, ret mat_r<int16>*, mat_r<int16>",    "void, const mat_r<int16>*",  "void, mat_r<int16>*",  "void, mat_r<int16>*|~",  "void, mat_r<int16>*|*~" ); }
	printf("  ■ sstd::mat_r<int32>\n"      ); { TEST_c2py_matXXX    (sstd::mat_r, int32,       "mat_r<int32>, ret mat_r<int32>*, mat_r<int32>",    "void, const mat_r<int32>*",  "void, mat_r<int32>*",  "void, mat_r<int32>*|~",  "void, mat_r<int32>*|*~" ); }
	printf("  ■ sstd::mat_r<int64>\n"      ); { TEST_c2py_matXXX    (sstd::mat_r, int64,       "mat_r<int64>, ret mat_r<int64>*, mat_r<int64>",    "void, const mat_r<int64>*",  "void, mat_r<int64>*",  "void, mat_r<int64>*|~",  "void, mat_r<int64>*|*~" ); }
	printf("  ■ sstd::mat_r<uint8>\n"      ); { TEST_c2py_matXXX    (sstd::mat_r, uint8,       "mat_r<uint8>, ret mat_r<uint8>*, mat_r<uint8>",    "void, const mat_r<uint8>*",  "void, mat_r<uint8>*",  "void, mat_r<uint8>*|~",  "void, mat_r<uint8>*|*~" ); }
	printf("  ■ sstd::mat_r<uint16>\n"     ); { TEST_c2py_matXXX    (sstd::mat_r, uint16,      "mat_r<uint16>, ret mat_r<uint16>*, mat_r<uint16>", "void, const mat_r<uint16>*", "void, mat_r<uint16>*", "void, mat_r<uint16>*|~", "void, mat_r<uint16>*|*~"); }
	printf("  ■ sstd::mat_r<uint32>\n"     ); { TEST_c2py_matXXX    (sstd::mat_r, uint32,      "mat_r<uint32>, ret mat_r<uint32>*, mat_r<uint32>", "void, const mat_r<uint32>*", "void, mat_r<uint32>*", "void, mat_r<uint32>*|~", "void, mat_r<uint32>*|*~"); }
	printf("  ■ sstd::mat_r<uint64>\n"     ); { TEST_c2py_matXXX    (sstd::mat_r, uint64,      "mat_r<uint64>, ret mat_r<uint64>*, mat_r<uint64>", "void, const mat_r<uint64>*", "void, mat_r<uint64>*", "void, mat_r<uint64>*|~", "void, mat_r<uint64>*|*~"); }
	printf("  ■ sstd::mat_r<float>\n"      ); { TEST_c2py_matFolatXX(sstd::mat_r, float,       "mat_r<float>, ret mat_r<float>*, mat_r<float>",    "void, const mat_r<float>*",  "void, mat_r<float>*",  "void, mat_r<float>*|~",  "void, mat_r<float>*|*~" ); }
	printf("  ■ sstd::mat_r<double>\n"     ); { TEST_c2py_matFolatXX(sstd::mat_r, double,      "mat_r<double>, ret mat_r<double>*, mat_r<double>", "void, const mat_r<double>*", "void, mat_r<double>*", "void, mat_r<double>*|~", "void, mat_r<double>*|*~"); }
	printf("  ■ sstd::mat_r<std::string>\n"); { TEST_c2py_matStr    (sstd::mat_r, std::string, "mat_r<str>, ret mat_r<str>*, mat_r<str>*",         "void, const mat_r<str>*",    "void, mat_r<str>*",    "void, mat_r<str>*|~",    "void, mat_r<str>*|*~"   ); } // "mat<str>_r, mat<str>_r" は，C++ の可変長引数で受け渡そうとすると，segmentation fault で落ちる．少なくとも gcc 5.4.0 では対応していないので，ポインタで渡しておく．
	//*/

	//-----------------------------------------------------------------------
	
	/*
	{
		//         int                          plusAandB(int a, int b){ return a+b; } // <- you can write this as a python function.
		sstd::c2py<int32> plus_A_B("./tmpDir", "test_functions", "plus_A_B", "int32, int32, int32");
		int32 a = 1, b = 2;
		int32 c = plus_A_B(a, b);
		sstd::printn(c);
	}
	//*/
	
	/*
	{
		sstd::c2py<std::vector<double>> plus_vecA_vecB("./tmpDir", "test_functions", "plus_vecA_vecB", "vec<double>, vec<double>, vec<double>");
		std::vector<double> vecA = {1.0, 2.0, 3.0}, vecB = {4.0, 5.0, 6.0};
		std::vector<double> vecC = plus_vecA_vecB(vecA, vecB);
		sstd::printn(vecC);
	}
	//*/

	/*
	{
		// write back test
		//	sstd::c2py<int> writeBack_vecA("./tmpDir", "test_functions", "writeBack_vecA", "int, const vec<double>*"); // const assignment will not be written back.
		//	sstd::c2py<int> writeBack_vecA("./tmpDir", "./test_c2py/test_functions", "writeBack_vecA", "int, vec<double>*");
		sstd::c2py<int> writeBack_vecA("./tmpDir", "test_functions", "writeBack_vecA", "int, vec<double>*");
		std::vector<double> vecA = {1.0, 2.0, 3.0};
		int ret = writeBack_vecA(&vecA);
		sstd::printn(ret);
		sstd::printn(vecA);
	}
	//*/
	
	/*
	{
		// numpy は行優先のため，列優先の行列を渡すと，python 側で転置処理が発生する．
		sstd::mat<double> matA{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}, {11.0, 12.0, 13.0}};
		sstd::printn(matA);
		sstd::c2py<int> mat2print("./tmpDir", "test_functions", "mat2print", "int, mat<double>");
		mat2print(matA);
	}
	//*/
	
	/*
	{
		sstd::mat<double> mat_rA{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}, {11.0, 12.0, 13.0}};
		sstd::printn(mat_rA);
		sstd::c2py<int> mat_r2print("./tmpDir", "test_functions", "mat_r2print", "int, mat_r<double>");
		mat_r2print(mat_rA);
	}
	//*/

	/*
	{
		sstd::mat<double> mat_rA{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}, {11.0, 12.0, 13.0}};
		sstd::printn(mat_rA);
		sstd::c2py<sstd::mat_r<double>> ret_mat_r("./tmpDir", "test_functions", "ret_mat_r", "mat_r<double>, mat_r<double>");
		sstd::printn(ret_mat_r(mat_rA));
	}
	//*/

	//-----------------------------------------------------------------------

	/*
	{
		sstd::c2py<void> py_vecDouble_cnv2builtIn("./tmpDir", "test_functions", "py_vecDouble_cnv2builtIn", "void, vec<double>*|~");
		std::vector<double> inOut={1.0, 2.0, 3.0};
		py_vecDouble_cnv2builtIn(&inOut);
		sstd::printn(inOut);
	}
	{
		sstd::c2py<void> py_vecDouble_pointer("./tmpDir", "test_functions", "py_vecDouble_pointer", "void, vec<double>*|*");
		std::vector<double> inOut={1.0, 2.0, 3.0};
		py_vecDouble_pointer(&inOut);
		sstd::printn(inOut);
	}
	//*/
	
	//-----------------------------------------------------------------------
	
	/*
	{
		sstd::c2py<void> py_ret("./tmpDir", "test_functions", "py_ret", "void, ret double*, ret double*, len, ret vec<double>*, vec<double>*|*~");
		double ret1=0.0;
		double ret2[]={0.0, 0.0};
		std::vector<double> ret3;
		std::vector<double> inOut={0.0};
		py_ret(&ret1, &ret2, 2, &ret3, &inOut);
		sstd::printn(ret1   );
		sstd::printn(ret2[0]);
		sstd::printn(ret2[1]);
		sstd::printn(ret3   );
		sstd::printn(inOut  );
	}
	//*/
	
	//-----------------------------------------------------------------------

	/*
	{
		double freq2generate = 0.1; // 0.1 Hz sin wave
		double freq2sample = 10;    // 10 Hz sampling
		uint len=60*10 + 1;         // 60 sec
		std::vector<double> vecY = sstd::sinWave(freq2generate, freq2sample, len);
		std::vector<double> vecX(len); for(uint i=0; i<vecX.size(); i++){ vecX[i]=(double)i*(1/freq2sample); }
	
		sstd::c2py<int> vec2graph("./tmpDir", "test_functions", "vec2graph", "int, const char*, vec<double>, vec<double>");
		vec2graph("./sin.png", vecX, vecY);
	}
	//*/
	
	/*
	{
		sstd::c2py<void> imgPath2mat_rRGB("./tmpDir", "test_functions", "imgPath2mat_rRGB", "void, ret mat_r<uint8>*, ret mat_r<uint8>*, ret mat_r<uint8>*, const char*");
		sstd::mat_r<uint8> imgR, imgG, imgB;
		imgPath2mat_rRGB(&imgR, &imgG, &imgB, "./test.png");

		for(uint p=0; p<imgG.rows(); p++){
			for(uint q=0; q<imgG.cols(); q++){
				imgG(p, q) = sstd::round2even(0.5*((double)imgG(p, q)));
			}
		}
	
		sstd::c2py<void> mat_rRGB2img("./tmpDir", "test_functions", "mat_rRGB2img", "void, const char*, mat_r<uint8>*, mat_r<uint8>*, mat_r<uint8>*");
		mat_rRGB2img("./test_reCombined.png", &imgR, &imgG, &imgB);
	}
	//*/

	//-----------------------------------------------------------------------
}

//-----------------------------------------------------------------------

void TEST_mat_colMajor(){
	printf("== sstd_src_MatrixStore_mat ==\n\n"); // col-major

	printf("■ Init sstd::mat<type> by \"std::initializer_list<T>\"\n");
	printf("\n");
	
	sstd::mat<double> matD_initializer{{1, 2, 3},{4, 5, 6},{7, 8, 9},{10, 11, 12}}; // これは，sstd::mat<T> 側にもテストを書くように．
	sstd::printn(matD_initializer);
	printf("\n");
	
	//===
	
	printf("■ Init sstd::mat<type>\n");
	printf("\n");
	
	sstd::mat<double> Matd(5, 3);
	printf("RowNum: %d\n", Matd.rows());
	printf("ColNum: %d\n", Matd.cols());
	printf("Length: %d\n", Matd.len());

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
	for(uint q=0; q<Matd.len(); q++){ Matd[i] = i; i++; }
	sstd::print(Matd);
	printf("\n");

	//===
	
	sstd::mat<double>* pMatd = new sstd::mat<double>(5, 3);
	printf("RowNum: %d\n", pMatd->rows());
	printf("ColNum: %d\n", pMatd->cols());
	printf("Length: %d\n", pMatd->len());

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
	sstd::mat<double> Matd_copy = Matd;
	Matd_copy = Matd; // "sstd::copy(Matd_copy, Matd);" is called.
	sstd::print(Matd_copy); printf("\n");

	//===

	printf("■ copy row\n");printf("\n");
	sstd::mat<double> Matd_rowCopy(5, 3); sstd::zeros(Matd_rowCopy);
	Matd_rowCopy(1, ':') = Matd(1, ':');
	sstd::print(Matd_rowCopy); printf("\n");
	
	printf("■ copy col\n");printf("\n");
	sstd::mat<double> Matd_colCopy(5, 3); sstd::zeros(Matd_colCopy);
	Matd_colCopy(':', 2) = Matd(':', 2);
	sstd::print(Matd_colCopy); printf("\n");

	//===
	sstd::printn(Matd_colCopy); printf("\n");
	sstd::printn_all(Matd_colCopy); printf("\n");

	//===
	
	printf("■ print(type& rhs)\n");printf("\n");
	sstd::mat<bool> matB{{true, false, false},{false, true, false},{false, false, true},{true, false, false}};
	sstd::printn(matB);

	printf("■ print(type& rhs)\n");printf("\n");
	sstd::mat<std::string> matStr{{"a", "ab", "abc"},{"abcd", "abcde", "abcdef"},{"7", "8", "9"},{"10", "11", "12"}};
	sstd::printn(matStr);
}

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
	printf("RowNum: %d\n", Matd.rows());
	printf("ColNum: %d\n", Matd.cols());
	printf("Length: %d\n", Matd.len());

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
	for(uint q=0; q<Matd.len(); q++){ Matd[i] = i; i++; }
	sstd::print(Matd);
	printf("\n");

	//===
	
	sstd::mat_r<double>* pMatd = new sstd::mat_r<double>(5, 3);
	printf("RowNum: %d\n", pMatd->rows());
	printf("ColNum: %d\n", pMatd->cols());
	printf("Length: %d\n", pMatd->len());

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
}


void TEST_bmat(){
	// init test
	sstd::bmat bMat4x4(4, 4);
	sstd::eye(bMat4x4);   sstd::printn(bMat4x4);
	sstd::ones(bMat4x4);  sstd::printn(bMat4x4);
	sstd::zeros(bMat4x4); sstd::printn(bMat4x4);
	sstd::print(bMat4x4);     // for print debug
	sstd::print_all(bMat4x4); // for bmat debug // Internaly, the bit matrix is processed as a set of 8x8 matrices.

	sstd::bmat bonded8x8 = sstd::zeros(4, 4) << sstd::eye(4, 4) &&
                           sstd::ones(4, 4)  << sstd::eye(4, 4);
	sstd::printn(bonded8x8);
	
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
