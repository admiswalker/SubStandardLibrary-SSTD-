#include "ssprintf.hpp"

std::string sstd::ssprintf(const char* format, ...){
	// sprintf()がchar型に提供する機能を、str_sprintf()はstd::string型で提供する。
	// ただし、引数の位置は異なるので注意。(この方が、戻り値を「+=」演算でバッファに追加書き込みしたり、「<<」演算に渡したりできるので、便利。)
	//
	//   const char* format : %d,%s,%c,%f,%lf,%x,%X,...などで、可変引数に渡すフォーマットを指定する。
	//   ...                : 可変引数
	//
	//   return             : std::string

	// retrieve the variable arguments
	// 可変変数の引数を取得する。
	va_list args;			// 可変長引数を扱うときのお約束
	va_start(args, format);	// 可変長引数を扱うときのお約束

	char* buf;

#ifdef _WIN32	// windows環境の場合は「_WIN32」が定義されているので、こちら。
	// 必要なメモリサイズを計算
	int len = _vscprintf(format, args)		// _vscprintf doesn't count
									+ 1;	// terminating '\0'
    
	// メモリの確保
	buf = (char*)malloc(len * sizeof(char));

	vsprintf_s(buf, len, format, args);

	/*
	 * 下記のようにリファクタリングする．(linux 環境については，要検討)
	 * 
	 * // メモリの確保
	 * std::string result(len, 0);	//0で初期化
	 * vsprintf_s(&result[0], len, format, args);
	 * 
	 * return result;
	 */

#else			// Linux 環境の場合は、"_WIN32" が定義されていないので、こちら。
	if(vasprintf(&buf, format, args) == -1){ //vasprintf() は、内部的にメモリを確保しているので、使用後に解放する必要がある。
		return std::string("");
	}
#endif

	// std::string へ copy
	std::string ret = buf;

	// メモリの解放
	free(buf);

	va_end(args);

	return ret;
}
