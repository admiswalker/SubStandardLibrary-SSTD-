#pragma once	//インクルードガード

#include "./typeDef.h"

namespace sstd{
	bool strmatch(
		const char *str,  // 比較する文字列
		const char *WildCard // ワイルドカード
	);

	bool isNum               (const char rhs);
	bool isAlphabet          (const char rhs);
	bool isAlphabet_onlyUpper(const char rhs);
	bool isAlphabet_onlyLower(const char rhs);
}
