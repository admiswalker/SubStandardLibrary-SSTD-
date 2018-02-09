#pragma once	//インクルードガード
#include <string>

namespace sstd{
	bool strmatch(
		const char* str,     // 比較する文字列
		const char* wildCard // ワイルドカード
	);
	bool strmatch_getWC(
		const char* str,      // 比較する文字列
		const char* wildCard, // ワイルドカード
		std::string& retWC    // ワイルドカード部分に一致する文字列を返却
	);
	

	bool isNum               (char rhs);
	bool isAlphabet          (char rhs);
	bool isAlphabet_onlyUpper(char rhs);
	bool isAlphabet_onlyLower(char rhs);
}
