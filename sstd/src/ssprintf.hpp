#pragma once	//インクルードガード

#include <stdarg.h>	//va_start()

#ifdef _WIN32	//windows環境の場合は「_WIN32」が定義されているので、こちら。
	#include <string>	//std::stringに必要
#else			//Linux環境の場合は、「_WIN32」が定義されていないので、こちら。
	#ifndef _GNU_SOURCE
		#define _GNU_SOURCE	//vasprintfに必要	//これは他のインクルードより先に定義しておく必要がある
	#endif
	#include <string>	//vasprintfに必要	//std::stringに必要
	#include <stdio.h>	//vasprintfに必要
	#include <stdlib.h>	//free()
#endif

namespace sstd{
	std::string ssprintf(const char* format, ...);
		//sprintf()がchar型に提供する機能を、str_sprintf()はstd::string型で提供する。
		//ただし、引数の位置は異なるので注意。(この方が、戻り値を「+=」演算でバッファに追加書き込みしたり、「<<」演算に渡したりできるので、便利。)
		//
		// const char* format : %d,%s,%c,%f,%lf,%x,%X,...などで、可変引数に渡すフォーマットを指定する。
		// ...                   : 可変引数
		//
		// return             : std::string
}
