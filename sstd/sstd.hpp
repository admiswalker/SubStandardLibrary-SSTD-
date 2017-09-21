#pragma once

//#include "./src/FileReader.hpp"
//#include "./src/FileWriter.hpp"
//#include "./src/LineFeedCode.h"

// C:\Users\asano\Documents\Visual Studio 2015\Projects\FileNameTranslator_Ver00.00_00\FileNameTranslator_Ver00.00_00
// の main.cpp 内の文字列比較関数．

// getPrime
// primeFactorization
// getDivisors

// 以下は恐らく，Cygwin ではなく，ネイティブの環境が必要．(thread 等の問題)
// makeConnection // win32 and linux
// sendMail
// serial communication interface // win and linux
// getTimeOfSNTP

// save/load as a wave
// save/load as a bitmap, tiff, jpg, png

// Eigen::MatrixXd <- eigen の場合
// sstd::mat<double> <- MartixStore/Core
// sstd::bmat
// sstd::rmat
// sstd::cmat
// sstd::irmat // 区間演算
// sstd::icmat // 区間演算
// sstd::rmul // (MPFR を使うと，GPL ライセンスになるから・・・多少遅くとも，内製するか・・・？(IEEE754に準拠できるかが問題))
// sstd::cmul // (MPFR を使うと，GPL ライセンスになるから・・・多少遅くとも，内製するか・・・？(IEEE754に準拠できるかが問題))
// sstd::rmmat // real multi mat
// sstd::cmmat // real multi mat (MPFR を使うと，GPL ライセンスになるから・・・書けるなら書く)
// sstd::irmmat // 区間演算
// sstd::icmmat // 区間演算

// src_mat_b
// src_mat_c
// src_mat_ci
// src_mat_cm
// src_mat_cmi
// src_mat_r
// src_mat_ri
// src_mat_rm
// src_mat_rmi
// src_mat_t

// 数値計算系の関数 (スプライン補完等)

// sstd::print(); <- printv, printm, 等を多重定義する．
// sstd::printv();
// sstd::printm();

#include "./src/measureTime.hpp"
#include "./src/sleep.hpp"
#include "./src/typeDef.h"
//#include "./src/pdbg.hpp" // 後ろで include しないと，extern での定義を置換してしまう．
#include "./src/math.hpp"
#include "./src/file.hpp"
#include "./src/mkdir.hpp"
#include "./src/ssprintf.hpp"
#include "./src/strmatch.hpp"
#include "./src/pathNameExtractor.hpp"
#include "./src/getFilePathInDir.hpp"
#include "./src/tinyInterpreter.hpp"
#include "./src/encode_decode.hpp"
#include "./src/pause.hpp"


namespace sstd{

	// #include "./src/measureTime.hpp"
	extern void measureTime_start(time_m& StartTime);
	extern void measureTime_stop (time_m& StartTime);

	// #include "./src/sleep.hpp"
	extern void sleep_hour(uint rhs);
	extern void sleep_min (uint rhs);
	extern void sleep_s   (uint rhs);
	extern void sleep_ms  (uint rhs);
	extern void sleep_us  (uint rhs);
	extern void sleep_ns  (uint rhs);

	// #include "./src/pdbg.hpp"     // printf debugger
	extern void pdbg();              // This function is enabled when DEBUG is #define d.
	extern void pdbg_if();           // This function is enabled when DEBUG is #define d.
	extern void pdbg_if_exit();      // This function is enabled when DEBUG is #define d.
	extern void pdbg_if_stop_exit(); // This function is enabled when DEBUG is #define d.
	extern void dbg();               // This function is enabled when DEBUG is #define d.
	extern void ndbg();              // This function is enabled when DEBUG is #define d.

	extern void pdbg_always();
	extern void pdbg_always_stop_exit();

	// #include "./src/print"
	// 変数名も一緒に表示するように、マクロを組むこと。
	// print(value);
	// -> value[5] = [0, 0, 0, 0, 0]
//	extern void printc(std::vector<char>& rhs); // 文字として表示 printf("%c", rhs[i]);
//	extern void printc(std::vector<uchar>& rhs); // 文字として表示 printf("%c", rhs[i]);
//
//	extern void print(std::vector<char>& rhs);
//	extern void print(std::vector<int>& rhs);
//	extern void print(std::vector<int8>& rhs);
//	extern void print(std::vector<int16>& rhs);
//	extern void print(std::vector<int32>& rhs);
//	extern void print(std::vector<int64>& rhs);
//
//	extern void print(std::vector<uchar>& rhs);
//	extern void print(std::vector<uint>& rhs);
//	extern void print(std::vector<uint8>& rhs);
//	extern void print(std::vector<uint16>& rhs);
//	extern void print(std::vector<uint32>& rhs);
//	extern void print(std::vector<uint64>& rhs);
//
//	extern void print(std::vector<float>& rhs);
//	extern void print(std::vector<double>& rhs);

	// #include "./src/math.hpp"
		// 偶数への丸め (round to even)
	extern float  round2even(float  n);
	extern double round2even(double n);
		// 奇数への丸め (round to odd)
	extern float  round2odd(float  n);
	extern double round2odd(double n);

	extern float  sum    (std::vector<float>&  rhs);
	extern float  sum_abs(std::vector<float>&  rhs);
	extern float  ave    (std::vector<float>&  rhs); // 平均値: average
//	extern float  med    (std::vector<float>&  rhs); // 中央値: median <- ソートして、中央の値。(偶数の場合はどれが中央？)
//	extern float  mod    (std::vector<float>&  rhs); // 最頻値: mode <- これは、やりにくい。(ビンサイズをどのように扱うのか？)
	extern float  max    (std::vector<float>&  rhs);
	extern float  max_abs(std::vector<float>&  rhs);
	extern float  min    (std::vector<float>&  rhs);
	extern float  min_abs(std::vector<float>&  rhs);
	extern float  var    (std::vector<float>&  rhs); // 不偏分散/標本分散 (variance): u^2 = (1/(n-1))*Σ(x_i-μ)^2
	extern float  var_p  (std::vector<float>&  rhs); // 母分散 (variance population): σ^2 = (1/n)*Σ(x_i-μ)^2
	extern float  stdev  (std::vector<float>&  rhs); // 標本標準偏差 (sample standard deviation): u = SQRT( (1/(n-1))*Σ(x_i-μ)^2 )
	extern float  stdev_p(std::vector<float>&  rhs); // 標準偏差 (standard deviation): σ = SQRT( (1/n)*Σ(x_i-μ)^2 )

	extern double sum    (std::vector<double>& rhs);
	extern double sum_abs(std::vector<double>& rhs);
	extern double ave    (std::vector<double>& rhs); // 平均値: average
//	extern double med    (std::vector<double>& rhs); // 中央値: median <- ソートして、中央の値。(偶数の場合はどれが中央？)
//	extern double mod    (std::vector<double>& rhs); // 最頻値: mode <- これは、やりにくい。(ビンサイズをどのように扱うのか？)
	extern double max    (std::vector<double>& rhs);
	extern double max_abs(std::vector<double>& rhs);
	extern double min    (std::vector<double>& rhs);
	extern double min_abs(std::vector<double>& rhs);
	extern double var    (std::vector<double>& rhs); // 不偏分散/標本分散 (variance): u^2 = (1/(n-1))*Σ(x_i-μ)^2
	extern double var_p  (std::vector<double>& rhs); // 母分散 (variance population): σ^2 = (1/n)*Σ(x_i-μ)^2
	extern double stdev  (std::vector<double>& rhs); // 標本標準偏差 (sample standard deviation): u = SQRT( (1/(n-1))*Σ(x_i-μ)^2 )
	extern double stdev_p(std::vector<double>& rhs); // 標準偏差 (standard deviation): σ = SQRT( (1/n)*Σ(x_i-μ)^2 )

	// #include "./src/file.hpp"
	extern bool fopen(FILE** fp, const char* FileName, const char* mode);

	// #include "./src/mkdir.hpp"
	extern void mkdir(const char* path);	// <- 再帰的にディレクトリを生成できるようにすること

	// #include "./src/ssprintf.hpp"
	extern std::string ssprintf(const char* format, ...);

	// #include "./src/strmatch.hpp"
	extern bool strmatch(const char *str, const char *WildCard); // str: 比較する文字列 // WildCard: ワイルドカード
	extern bool isNum               (const char rhs);
	extern bool isAlphabet          (const char rhs);
	extern bool isAlphabet_onlyUpper(const char rhs);
	extern bool isAlphabet_onlyLower(const char rhs);

	// #include "./src/pathNameExtractor.hpp" // <- 不足する関数を追加する必要がある．
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

	// #include "./src/getFilePathInDir.hpp"
	extern std::vector<std::string> getFilePathInDir(const char* DirAndFileName_withWildCard);

	// #include "./src/tinyInterpreter.hpp"
		// How to use GetCommandList(); function.
		//
		// TinyInterPrinter define middle of "/*~*/" and before "//" as a commnet.
		// And a ";" mean the end of command. Return value is the list of command.
	extern std::string readAll                    (const char* pReadFile);
	extern std::string readAll_withoutBOM         (const char* pReadFile);
	extern std::vector<std::string> getCommandList(const char* pReadFile);
	extern std::vector<std::string> splitByComma  (const std::string& str);	// str をカンマで分割する
	extern std::vector<std::string> splitByLine   (const std::string& str);

	// #include "./src/encode_decode.hpp"
	extern std::string base64_encode(const char* str, const size_t strLen);
	extern std::string base64_encode(const char* str);
	extern std::string base64_encode(std::string& str);

	extern std::string base64_decode(const char* str, const size_t strLen); // when it was error, return 0 size std::string.
	extern std::string base64_decode(const char* str);                      // when it was error, return 0 size std::string.
	extern std::string base64_decode(std::string& str);                     // when it was error, return 0 size std::string.

	extern const  char bin2str_table[256][3];
	extern const uchar str2bin_table[256];
	extern std::string url_encode(const char* str, const size_t strLen);
	extern std::string url_encode(const char* str);
	extern std::string url_encode(std::string& str);

	extern std::string url_decode(const char* str, const size_t strLen); // when it was error, return 0 size std::string.
	extern std::string url_decode(const char* str);                      // when it was error, return 0 size std::string.
	extern std::string url_decode(std::string& str);                     // when it was error, return 0 size std::string.

	extern std::string utf16_to_utf8(const char* str, const size_t strLen);
//	extern std::string utf8_to_utf16(const char* str, const size_t strLen);

	extern std::string unicodeEscape_encode(const std::u16string& str);
	extern std::u16string unicodeEscape_decode(const char* str, const size_t strLen);
	extern std::u16string unicodeEscape_decode(const char* str);
	extern std::u16string unicodeEscape_decode(const std::string& str);

	// #include "./src/pause.h"
	extern void pause();
	extern void pauseIfWin32();
}


#include "./src/pdbg.hpp"                  // In order to avoid conflict of "pdbg.hpp", we need to define after namespace sstd{}.
#include "./src/MatrixStore_tmat/tmat.hpp" // Because of this header use "pdbg.hpp", we need to define after namespace sstd{}.
#include "./src/MatrixStore_bmat/bmat.hpp"
