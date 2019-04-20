#pragma once

// todo:
//   - sstdf::file, fp; sstd::fopen, sstd::fread, sstd::write, 
//     C言語関数辞典: stdio.h (http://www.c-tipsref.com/reference/stdio.html) を参考に実装するとよい．
//   - loadImg(); tiff (lzw, jpg), gif, png, jpg, bmp あたりに対応できるとよいのでは>?
//   - loadWave(); wave. (mp3 は，後回しでよいだろう・・・)
//   - zip の展開・圧縮
//   - std::move, std::swap() における動作確認．(tmat, tmat_r, bmat)

//#include "./src/FileReader.hpp"
//#include "./src/FileWriter.hpp"
//#include "./src/LineFeedCode.h"

// C:\Users\username\Documents\Visual Studio 2015\Projects\FileNameTranslator_Ver00.00_00\FileNameTranslator_Ver00.00_00
// の main.cpp 内の文字列比較関数．

// 以下は恐らく，Cygwin ではなく，ネイティブの環境が必要．(thread 等の問題)
// makeConnection // win32 and linux
// sendMail
// serial communication interface // win and linux
// getTimeOfSNTP

// save/load as a wave
// save/load as a bitmap, tiff, jpg, png
// tiff, png 画像の読み込み (lzw 圧縮のみに対応予定？)

// 数値計算系の関数 (スプライン補完等)

#include "./src/measureTime.hpp"
#include "./src/sleep.hpp" // use_sstd_gcc4_4_7
#include "./src/time.hpp"
#include "./src/typeDef.h"
//#include "./src/pdbg.hpp" // 後ろで include しないと，extern での定義を置換してしまう．
//#include "./src/print.hpp" // 後ろで include しないと，extern での定義を置換してしまう．
#include "./src/math.hpp"
#include "./src/signal.hpp"
#include "./src/file.hpp"
#include "./src/file_c.hpp"
#include "./src/mkdir.hpp"
#include "./src/rm.hpp"
#include "./src/str2num.hpp"
#include "./src/ssprintf.hpp"
#include "./src/strmatch.hpp"
#include "./src/path.hpp"
#include "./src/getFilePathInDir.hpp"
#include "./src/strEdit.hpp"
#include "./src/tinyInterpreter.hpp"
#include "./src/csv.hpp"
#include "./src/encode_decode.hpp"
#include "./src/hashFnc_of_MD5_SHA1_SHA2/sstd_md5_sha1_sha2_wrapper.hpp"
#include "./src/pause.hpp"
#include "./src/pid.hpp"

namespace sstd{

	// #include "./src/measureTime.hpp"
	extern void        measureTime_start     (      time_m& startTime);
	extern double      measureTime_stop_s    (const time_m& startTime); // sec
	extern double      measureTime_stop_ms   (const time_m& startTime); // milli sec
	extern double      measureTime_stop_us   (const time_m& startTime); // micro sec
	extern double      measureTime_stop_ns   (const time_m& startTime); // nano sec
	extern std::string measureTime_stop_str  (const time_m& startTime);
	extern void        measureTime_stop_print(const time_m& startTime);
	
	// #include "./src/sleep.hpp"
	extern void sleep_hour(uint rhs);
	extern void sleep_min (uint rhs);
	extern void sleep_s   (uint rhs);
	extern void sleep_ms  (uint rhs);
	extern void sleep_us  (uint rhs);
	extern void sleep_ns  (uint rhs);

	// #include "./src/time.hpp"
	extern struct tm time2tm(time_t unixtime);
	extern time_t    tm2time(struct tm& rhs);
	extern struct tm timeGm2tmLocal(time_t unixtime);
	extern time_t    tmLocal2timeGm(struct tm& rhs);
	extern std::string time2str(time_t unixtime);
	extern std::string   tm2str(struct tm& rhs);
	extern double      time2unixday(time_t unixtime);
	extern double        tm2unixday(struct tm& rhs);
	
	extern time_t    yday2time(uint year, uint yday);
	extern struct tm yday2tm  (uint year, uint yday);

	extern struct timeval getTimeval();

	extern void print(const struct tm& rhs);
	
	// #include "./src/pdbg.hpp"     // printf debugger
//	extern void pdbg();              // This function is enabled when DEBUG is #define d.
//	extern void pdbg_if();           // This function is enabled when DEBUG is #define d.
//	extern void pdbg_if_exit();      // This function is enabled when DEBUG is #define d.
//	extern void pdbg_if_stop_exit(); // This function is enabled when DEBUG is #define d.
//	extern void  dbg();              // This function is enabled when DEBUG is #define d.
//	extern void ndbg();              // This function is enabled when DEBUG is #define d.

	// #include "./src/print.hpp"
	extern void print  (bool rhs);
	
	extern void print  (int8  rhs);
	extern void print  (int16 rhs);
	extern void print  (int32 rhs);
	extern void print  (int64 rhs);

	extern void print  (uint8  rhs);
	extern void print  (uint16 rhs);
	extern void print  (uint32 rhs);
	extern void print  (uint64 rhs);

	extern void print  (float  rhs);
	extern void print  (double rhs);

	extern void print  (const char*        rhs);
	extern void print  (const std::string& rhs);
	//===
	extern void print  (const std::vector<char>&  rhs);
	extern void print  (const std::vector<int>&   rhs);
	extern void print  (const std::vector<int8>&  rhs);
	extern void print  (const std::vector<int16>& rhs);
	extern void print  (const std::vector<int32>& rhs);
	extern void print  (const std::vector<int64>& rhs);
	
	extern void print  (const std::vector<uchar>&  rhs);
	extern void print  (const std::vector<uint>&   rhs);
	extern void print  (const std::vector<uint8>&  rhs);
	extern void print  (const std::vector<uint16>& rhs);
	extern void print  (const std::vector<uint32>& rhs);
	extern void print  (const std::vector<uint64>& rhs);

	extern void print  (const std::vector<float>&  rhs);
	extern void print  (const std::vector<double>& rhs);

	extern void print  (const std::vector<std::string>& rhs);

	extern void print_c(const std::vector<char>&  rhs); // 文字として表示 printf("%c", rhs[i]);
	extern void print_c(const std::vector<uchar>& rhs); // 文字として表示 printf("%c", rhs[i]);
	//===
	extern void print  (const std::vector<std::vector<int>>&   rhs);
	extern void print  (const std::vector<std::vector<int8>>&  rhs);
	extern void print  (const std::vector<std::vector<int16>>& rhs);
	extern void print  (const std::vector<std::vector<int32>>& rhs);
	extern void print  (const std::vector<std::vector<int64>>& rhs);
	
	extern void print  (const std::vector<std::vector<uint>>&   rhs);
	extern void print  (const std::vector<std::vector<uint8>>&  rhs);
	extern void print  (const std::vector<std::vector<uint16>>& rhs);
	extern void print  (const std::vector<std::vector<uint32>>& rhs);
	extern void print  (const std::vector<std::vector<uint64>>& rhs);
	
	extern void print  (const std::vector<std::vector<float>>&  rhs);
	extern void print  (const std::vector<std::vector<double>>& rhs);

	extern void print  (const std::vector<std::vector<std::string>>& rhs);
	extern void print_c(const std::vector<std::vector<char>>&  rhs); // 文字として表示 printf("%c", rhs[i]);
	extern void print_c(const std::vector<std::vector<uchar>>& rhs); // 文字として表示 printf("%c", rhs[i]);

	// print with a variable name
	extern void printn(...);       // dummy function
	extern void printn_all(...);   // dummy function
	
	// print with function name, linu number and variable name
	extern void printn_c(...);     // dummy function
	extern void printn_all_c(...); // dummy function
	
	// #include "./src/math.hpp"
		// 偶数への丸め (round to even)
	extern float  round2even(float  n);
	extern double round2even(double n);
		// 奇数への丸め (round to odd)
	extern float  round2odd(float  n);
	extern double round2odd(double n);

	extern float  sum    (const std::vector<float>&  rhs);
	extern float  sum    (const std::vector<float>&  rhs, uint a, uint b); // 配列の a 番目から b 番目までの合計. sum of the a th to b th of array.
	extern float  sum_abs(const std::vector<float>&  rhs);
	extern float  ave    (const std::vector<float>&  rhs);           // 平均値: average
	extern float  ave    (const std::vector<float>&  rhs, uint num); // 平均値: average in the first num elements.
	extern float  med    (      std::vector<float>   rhs);           // 中央値: median // copy rhs // If rhs.size () is even, average of the two median values is returned.
//	extern float  mod    (const std::vector<float>&  rhs);           // 最頻値: mode <- これは、やりにくい。(ビンサイズをどのように扱うのか？)
	extern float  max    (const std::vector<float>&  rhs);
	extern float  max_abs(const std::vector<float>&  rhs);
	extern float  min    (const std::vector<float>&  rhs);
	extern float  min_abs(const std::vector<float>&  rhs);
	extern float  var    (const std::vector<float>&  rhs); // 不偏分散/標本分散 (variance): u^2 = (1/(n-1))*Σ(x_i-μ)^2
	extern float  var_p  (const std::vector<float>&  rhs); // 母分散 (variance population): σ^2 = (1/n)*Σ(x_i-μ)^2
	extern float  stdev  (const std::vector<float>&  rhs); // 標本標準偏差 (sample standard deviation): u = SQRT( (1/(n-1))*Σ(x_i-μ)^2 )
	extern float  stdev_p(const std::vector<float>&  rhs); // 標準偏差 (standard deviation): σ = SQRT( (1/n)*Σ(x_i-μ)^2 )
	
	extern double sum    (const std::vector<double>& rhs);
	extern double sum    (const std::vector<double>& rhs, uint a, uint b); // 配列の a 番目から b 番目までの合計. sum of the a th to b th of array.
	extern double sum_abs(const std::vector<double>& rhs);
	extern double ave    (const std::vector<double>& rhs);           // 平均値: average
	extern double ave    (const std::vector<double>& rhs, uint num); // 平均値: average in the first num elements.
	extern double med    (      std::vector<double>  rhs);           // 中央値: median // copy rhs // If rhs.size () is even, average of the two median values is returned.
//	extern double mod    (const std::vector<double>& rhs);           // 最頻値: mode <- これは、やりにくい。(ビンサイズをどのように扱うのか？)
	extern double max    (const std::vector<double>& rhs);
	extern double max_abs(const std::vector<double>& rhs);
	extern double min    (const std::vector<double>& rhs);
	extern double min_abs(const std::vector<double>& rhs);
	extern double var    (const std::vector<double>& rhs); // 不偏分散/標本分散 (variance): u^2 = (1/(n-1))*Σ(x_i-μ)^2
	extern double var_p  (const std::vector<double>& rhs); // 母分散 (variance population): σ^2 = (1/n)*Σ(x_i-μ)^2
	extern double stdev  (const std::vector<double>& rhs); // 標本標準偏差 (sample standard deviation): u = SQRT( (1/(n-1))*Σ(x_i-μ)^2 )
	extern double stdev_p(const std::vector<double>& rhs); // 標準偏差 (standard deviation): σ = SQRT( (1/n)*Σ(x_i-μ)^2 )

	//------------------------------------------------------------------------
	
	extern   char max    (const std::vector< char >& rhs);
	extern   int8 max    (const std::vector< int8 >& rhs);
	extern  int16 max    (const std::vector< int16>& rhs);
	extern  int32 max    (const std::vector< int32>& rhs);
	extern  int64 max    (const std::vector< int64>& rhs);
//	extern  uchar max    (const std::vector<uchar >& rhs); // same as a uint8
	extern  uint8 max    (const std::vector<uint8 >& rhs);
	extern uint16 max    (const std::vector<uint16>& rhs);
	extern uint32 max    (const std::vector<uint32>& rhs);
	extern uint64 max    (const std::vector<uint64>& rhs);
	extern   char max_abs(const std::vector< char >& rhs);
	extern   int8 max_abs(const std::vector< int8 >& rhs);
	extern  int16 max_abs(const std::vector< int16>& rhs);
	extern  int32 max_abs(const std::vector< int32>& rhs);
	extern  int64 max_abs(const std::vector< int64>& rhs);
	
	extern   char min    (const std::vector< char >& rhs);
	extern   int8 min    (const std::vector< int8 >& rhs);
	extern  int16 min    (const std::vector< int16>& rhs);
	extern  int32 min    (const std::vector< int32>& rhs);
	extern  int64 min    (const std::vector< int64>& rhs);
//	extern  uchar min    (const std::vector<uchar >& rhs); // same as a uint8
	extern  uint8 min    (const std::vector<uint8 >& rhs);
	extern uint16 min    (const std::vector<uint16>& rhs);
	extern uint32 min    (const std::vector<uint32>& rhs);
	extern uint64 min    (const std::vector<uint64>& rhs);
	extern   char min_abs(const std::vector< char >& rhs);
	extern   int8 min_abs(const std::vector< int8 >& rhs);
	extern  int16 min_abs(const std::vector< int16>& rhs);
	extern  int32 min_abs(const std::vector< int32>& rhs);
	extern  int64 min_abs(const std::vector< int64>& rhs);
	
	extern   char max    (const sstd::mat_c< char >& rhs);
	extern   int8 max    (const sstd::mat_c< int8 >& rhs);
	extern  int16 max    (const sstd::mat_c< int16>& rhs);
	extern  int32 max    (const sstd::mat_c< int32>& rhs);
	extern  int64 max    (const sstd::mat_c< int64>& rhs);
//	extern  uchar max    (const sstd::mat_c<uchar >& rhs); // same as a uint8
	extern  uint8 max    (const sstd::mat_c<uint8 >& rhs);
	extern uint16 max    (const sstd::mat_c<uint16>& rhs);
	extern uint32 max    (const sstd::mat_c<uint32>& rhs);
	extern uint64 max    (const sstd::mat_c<uint64>& rhs);
	extern  float max    (const sstd::mat_c< float>& rhs);
	extern double max    (const sstd::mat_c<double>& rhs);
	extern   char max_abs(const sstd::mat_c< char >& rhs);
	extern   int8 max_abs(const sstd::mat_c< int8 >& rhs);
	extern  int16 max_abs(const sstd::mat_c< int16>& rhs);
	extern  int32 max_abs(const sstd::mat_c< int32>& rhs);
	extern  int64 max_abs(const sstd::mat_c< int64>& rhs);
	extern  float max_abs(const sstd::mat_c< float>& rhs);
	extern double max_abs(const sstd::mat_c<double>& rhs);
	
	extern   char min    (const sstd::mat_c< char >& rhs);
	extern   int8 min    (const sstd::mat_c< int8 >& rhs);
	extern  int16 min    (const sstd::mat_c< int16>& rhs);
	extern  int32 min    (const sstd::mat_c< int32>& rhs);
	extern  int64 min    (const sstd::mat_c< int64>& rhs);
//	extern  uchar min    (const sstd::mat_c<uchar >& rhs); // same as a uint8
	extern  uint8 min    (const sstd::mat_c<uint8 >& rhs);
	extern uint16 min    (const sstd::mat_c<uint16>& rhs);
	extern uint32 min    (const sstd::mat_c<uint32>& rhs);
	extern uint64 min    (const sstd::mat_c<uint64>& rhs);
	extern  float min    (const sstd::mat_c< float>& rhs);
	extern double min    (const sstd::mat_c<double>& rhs);
	extern   char min_abs(const sstd::mat_c< char >& rhs);
	extern   int8 min_abs(const sstd::mat_c< int8 >& rhs);
	extern  int16 min_abs(const sstd::mat_c< int16>& rhs);
	extern  int32 min_abs(const sstd::mat_c< int32>& rhs);
	extern  int64 min_abs(const sstd::mat_c< int64>& rhs);
	extern  float min_abs(const sstd::mat_c< float>& rhs);
	extern double min_abs(const sstd::mat_c<double>& rhs);
	
	extern   char max    (const sstd::mat_r< char >& rhs);
	extern   int8 max    (const sstd::mat_r< int8 >& rhs);
	extern  int16 max    (const sstd::mat_r< int16>& rhs);
	extern  int32 max    (const sstd::mat_r< int32>& rhs);
	extern  int64 max    (const sstd::mat_r< int64>& rhs);
//	extern  uchar max    (const sstd::mat_r<uchar >& rhs); // same as a uint8
	extern  uint8 max    (const sstd::mat_r<uint8 >& rhs);
	extern uint16 max    (const sstd::mat_r<uint16>& rhs);
	extern uint32 max    (const sstd::mat_r<uint32>& rhs);
	extern uint64 max    (const sstd::mat_r<uint64>& rhs);
	extern  float max    (const sstd::mat_r< float>& rhs);
	extern double max    (const sstd::mat_r<double>& rhs);
	extern   char max_abs(const sstd::mat_r< char >& rhs);
	extern   int8 max_abs(const sstd::mat_r< int8 >& rhs);
	extern  int16 max_abs(const sstd::mat_r< int16>& rhs);
	extern  int32 max_abs(const sstd::mat_r< int32>& rhs);
	extern  int64 max_abs(const sstd::mat_r< int64>& rhs);
	extern  float max_abs(const sstd::mat_r< float>& rhs);
	extern double max_abs(const sstd::mat_r<double>& rhs);
	
	extern   char min    (const sstd::mat_r< char >& rhs);
	extern   int8 min    (const sstd::mat_r< int8 >& rhs);
	extern  int16 min    (const sstd::mat_r< int16>& rhs);
	extern  int32 min    (const sstd::mat_r< int32>& rhs);
	extern  int64 min    (const sstd::mat_r< int64>& rhs);
//	extern  uchar min    (const sstd::mat_r<uchar >& rhs); // same as a uint8
	extern  uint8 min    (const sstd::mat_r<uint8 >& rhs);
	extern uint16 min    (const sstd::mat_r<uint16>& rhs);
	extern uint32 min    (const sstd::mat_r<uint32>& rhs);
	extern uint64 min    (const sstd::mat_r<uint64>& rhs);
	extern  float min    (const sstd::mat_r< float>& rhs);
	extern double min    (const sstd::mat_r<double>& rhs);
	extern   char min_abs(const sstd::mat_r< char >& rhs);
	extern   int8 min_abs(const sstd::mat_r< int8 >& rhs);
	extern  int16 min_abs(const sstd::mat_r< int16>& rhs);
	extern  int32 min_abs(const sstd::mat_r< int32>& rhs);
	extern  int64 min_abs(const sstd::mat_r< int64>& rhs);
	extern  float min_abs(const sstd::mat_r< float>& rhs);
	extern double min_abs(const sstd::mat_r<double>& rhs);
	
	//------------------------------------------------------------------------
	
//	std::vector<T> sort   (std::vector<T> rhs); // Ascending: 昇順: 0, 1, 2, ...
//	std::vector<T> sort_de(std::vector<T> rhs); // Descending: 降順: 9, 8, 7, ...
	
	//------------------------------------------------------------------------
	
	extern std::vector<uint64> prime(uint64 rhs);                                  // get a list of prime number
	extern std::vector<struct fact> factor(uint64 rhs);                            // get a list of prime factorization
	extern void print     (const std::vector<struct fact>& factList);
	extern void for_printn(const std::vector<struct fact>& factList);
	extern std::vector<uint64> divisor(const std::vector<struct sstd::fact>& rhs); // get a list of all divisors
	extern std::vector<uint64> divisor(uint64 rhs);                                // get a list of all divisors
	
	extern uint8  pow(const uint8 & base, const uint8 & exp);
	extern uint16 pow(const uint16& base, const uint16& exp);
	extern uint32 pow(const uint32& base, const uint32& exp);
	extern uint64 pow(const uint64& base, const uint64& exp);
	extern  float pow(const  float& base, const  float& exp);
	extern double pow(const double& base, const double& exp);
	
	// #include "signal.hpp"
	extern std::vector<double> sinWave(double freq2generate, double freq2sample, uint len);
	extern std::vector<double> cosWave(double freq2generate, double freq2sample, uint len);

	// #include "./src/file.hpp"
//	class file;
//    fopen(), fclose(), fread(), fwrite(), fseek(), ftell()
//	There is no needing to call "fclose", because destructor call "fclose" at end of the scope.
	// #include "./src/file_c.hpp"
//	class file_c;
	
	// #include "./src/mkdir.hpp"
	extern void mkdir(const char*        pPath);
	extern void mkdir(const std::string&  path);

	// #include "./src/rm.hpp"
	extern bool unlink(const char*        pPath); // delete file
	extern bool unlink(const std::string&  path); // delete file
	extern bool rmdir (const char*        pPath); // delete empty directory
	extern bool rmdir (const std::string&  path); // delete empty directory
	extern bool rm    (const char*        pPath); // delete all under the pPath
	extern bool rm    (const std::string&  path); // delete all under the path
	extern bool getAllPath(std::vector<struct sstd::pathAndType>& ret, const char* pPath); // get all path in the directory
	extern bool getAllPath(std::vector<std::string>& ret, const char* pPath);              // get all path in the directory
	extern bool getAllFile(std::vector<std::string>& ret, const char* pPath);              // get all file path in the directory
	extern bool getAllDir (std::vector<std::string>& ret, const char* pPath);              // get all directory path in the directory
	
	// #include "./src/str2num.hpp" // using std::stod and std::stoi, but probably it might be slow in parse.
	extern double str2double(const std::string& rhs);
	extern int str2int(const std::string& rhs); // 小数点以下，切り捨て

	// #include "./src/ssprintf.hpp"
	extern std::string ssprintf(const char* format, ...);

	// #include "./src/strmatch.hpp"
	extern bool strmatch      (const char *str, const char *wildCard);                     // str: 比較する文字列 // wildCard: ワイルドカード
	extern bool strmatch_getWC(const char *str, const char *wildCard, std::string& retWC); // str: 比較する文字列 // wildCard: ワイルドカード // retWC: ワイルドカード部分に一致する文字列を返却
	extern bool isNum               (char rhs);
	extern bool isAlphabet          (char rhs);
	extern bool isAlphabet_onlyUpper(char rhs);
	extern bool isAlphabet_onlyLower(char rhs);

	// #include "./src/path.hpp" // <- 不足する関数を追加する必要がある．
	// GetDirectoryName
	extern std::string  getPath                     (const char* pPath);
	extern        char* getFileName                 (const char* pPath);
	extern std::string  getFileName_withoutExtension(const char* pPath);
	extern        char* getExtension                (const char* pPath);
	// getPathRoot
	// getFullPath
	// hasExtension
	// isPathRooted
	// getDirectoryRoot
	// getParent
	extern std::vector<std::string> parsePath         (const char* pPath);
	extern std::vector<std::string> parsePath_withBase(const char* pPath);

	extern bool isFile(const char*        pPath);
	extern bool isFile(const std::string&  path);
	extern bool isDir (const char*        pPath);
	extern bool isDir (const std::string&  path);
	
	extern bool fileExist(const char*        pPath);
	extern bool fileExist(const std::string&  path);
	extern bool  dirExist(const char*        pPath);
	extern bool  dirExist(const std::string&  path);
	extern bool pathExist(const char*        pPath);
	extern bool pathExist(const std::string&  path);
//   dirExist
//	bool pathExist(const char* path){ return fileExist(path) || dirExist(path); }
//	命名規則に関しては，"http://docs.python.jp/2/library/os.path.html" 等を参考にしてもよさそう．
	

	// #include "./src/getFilePathInDir.hpp"
	extern std::vector<std::string> getFilePathInDir(const char* DirAndFileName_withWildCard);
	
	// #include "./src/strEdit.hpp"
	extern std::vector<uint8> readAll_bin         (const char*        pReadFile); // read all of the file as a binary
	extern std::vector<uint8> readAll_bin         (const std::string&  readFile); // read all of the file as a binary
	extern bool               writeAll_bin        (const char*        pWritePath, std::vector<uint8>& rhs);
	extern bool               writeAll_bin        (const std::string&  writePath, std::vector<uint8>& rhs);
	extern std::string readAll                    (const char*        pReadFile); // readAll_str()
	extern std::string readAll                    (const std::string&  readFile); // readAll_str()
	extern std::string readAll_withoutBOM         (const char*        pReadFile);
	extern std::string readAll_withoutBOM         (const std::string&  readFile);
	extern std::vector<std::string> getCommandList(const char* pReadFile);
	
	extern std::vector<std::string> splitByLine   (const std::string& str);
	extern std::vector<std::string> split         (const char*        str, const char X);
	extern std::vector<std::string> split         (const std::string& str, const char X);
	
	extern std::string              removeHeadSpace(const uchar* str);
	extern void                     removeTailSpace(std::string& str);
	extern std::string              removeSpace_of_HeadAndTail(const uchar* str);
	extern void                     removeSpace_of_HeadAndTail(std::string& str);
	extern std::vector<std::string> removeSpace_of_HeadAndTail(const std::vector<std::string>& vec);
	
	extern bool strcmp(const char*        str1, const char*        str2);
	extern bool strcmp(const char*        str1, const std::string& str2);
	extern bool strcmp(const std::string& str1, const char*        str2);
	extern bool strcmp(const std::string& str1, const std::string& str2);
	
	// #include "./src/tinyInterpreter.hpp"
		// How to use GetCommandList(); function.
		//
		// TinyInterPrinter define middle of "/*~*/" and before "//" as a commnet.
		// And a ";" mean the end of command. Return value is the list of command.
	extern std::vector<std::string> splitByComma  (const std::string& str);	// str をカンマで分割する

	// #include "./src/csv.hpp"
	extern std::vector<std::vector<std::string>> parseCSV(const char* pReadFile);

	// #include "./src/encode_decode.hpp"
	extern std::string base64_encode(const uchar* str, size_t strLen);
	extern std::string base64_encode(const uchar* str);
	extern std::string base64_encode(const std::string& str);

	extern std::string base64_decode(const uchar* str, size_t strLen); // when it was error, return 0 size std::string.
	extern std::string base64_decode(const uchar* str);                // when it was error, return 0 size std::string.
	extern std::string base64_decode(const std::string& str);          // when it was error, return 0 size std::string.

	extern const  char bin2str_table[256][3];
	extern const uchar str2bin_table[256];
	extern std::string url_encode(const char* str, size_t strLen);
	extern std::string url_encode(const char* str);
	extern std::string url_encode(std::string& str);

	extern std::string url_decode(const char* str, size_t strLen); // when it was error, return 0 size std::string.
	extern std::string url_decode(const char* str);                // when it was error, return 0 size std::string.
	extern std::string url_decode(std::string& str);               // when it was error, return 0 size std::string.

//	extern std::string utf16_to_utf8(const char* str, const size_t strLen);
//	extern std::string utf8_to_utf16(const char* str, const size_t strLen);
	// utf functions are not checked yet.
	extern std::u32string utf16_to_utf32(const std::u16string& str); // when it was error, return 0 size of std::u32string.
	extern std::u16string utf32_to_utf16(const std::u32string& str); // when it was error, return 0 size of std::u16string.
	extern std::   string utf32_to_utf8 (const std::u32string& str); // when it was error, return 0 size of std::string.
	extern std::u32string  utf8_to_utf32(const std::   string& str); // when it was error, return 0 size of std::u32string.
	extern std::u16string  utf8_to_utf16(const std::   string& str); // when it was error, return 0 size of std::u16string.
	extern std::   string utf16_to_utf8 (const std::u16string& str); // when it was error, return 0 size of std::string.

	extern std::string    unicodeEscape_encode(const std::u16string& str);             // "abc_ユニコード" <-> R"(abcd_\u30e6\u30cb\u30b3\u30fc\u30c9)" の処理がバグっている
	extern std::u16string unicodeEscape_decode(const char* str, size_t strLen);
	extern std::u16string unicodeEscape_decode(const char* str);
	extern std::u16string unicodeEscape_decode(const std::string& str);

	// #include "./src/MD5_SHA1_SHA2/sstd_MD5_sha1_sha2_wrapper.hpp"
	extern std::vector<uint8> md5   (const uchar* in, size_t in_len);
	extern std::vector<uint8> sha1  (const uchar* in, size_t in_len);
	extern std::vector<uint8> sha224(const uchar* in, size_t in_len);
	extern std::vector<uint8> sha256(const uchar* in, size_t in_len);
	extern std::vector<uint8> sha384(const uchar* in, size_t in_len);
	extern std::vector<uint8> sha512(const uchar* in, size_t in_len);
	
	extern std::vector<uint8> md5   (const std::vector<uint8>& in);
	extern std::vector<uint8> sha1  (const std::vector<uint8>& in);
	extern std::vector<uint8> sha224(const std::vector<uint8>& in);
	extern std::vector<uint8> sha256(const std::vector<uint8>& in);
	extern std::vector<uint8> sha384(const std::vector<uint8>& in);
	extern std::vector<uint8> sha512(const std::vector<uint8>& in);
	
	// #include "./src/pause.h"
	extern void pause();
	extern void pauseIfWin32();
}


#include "./src/linearAlgebra/matCal.hpp"
#include "./src/matrixContainer_binary/bmat.hpp"
#include "./src/stdVector_expansion/stdVector_expansion.hpp"
#include "./src/matrixContainer_colMajor/mat_c.hpp" // Because of this header use "pdbg.hpp", we need to define after namespace sstd{}.
#include "./src/matrixContainer_rowMajor/mat_r.hpp" // Because of this header use "pdbg.hpp", we need to define after namespace sstd{}.

#include "./src/pdbg.hpp"                           // In order to avoid conflict of "pdbg.hpp", we need to define after namespace sstd{}.
#include "./src/print.hpp"                          // In order to avoid conflict of "print.hpp", we need to define after namespace sstd{}.

#include "./compileOption.hpp"
#ifndef use_sstd_pdbg
	#undef pdbg
	#undef pdbg_if
	#undef pdbg_if_exit
	#undef pdbg_if_stop_exit
	#undef  dbg
	#undef ndbg
	#undef pdbg_alway
	#undef pdbg_always_stop_exit
#endif
#ifndef use_sstd_printn
	#undef printn
	#undef printn_all
	#undef printn_c
	#undef printn_all_c
#endif

// 上記で関数を示さない応用ライブラリは下記に列挙する
#include "./src/c2py.hpp"
