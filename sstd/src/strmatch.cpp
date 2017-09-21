#include "strmatch.hpp"
#include "./typeDef.h"

//　ワイルドカード ('*', '?') の使用可能な文字列比較関数を作る。
//　'*' は任意の文字列と一致し、'?' は空文字('\0')を除く任意の一文字と一致する。

bool sstd::strmatch(
		const char *str,		// 比較する文字列
		const char *wildCard	// ワイルドカード
){
	if      (*wildCard=='\0'){ return '\0' == *str;
	}else if(*wildCard=='*' ){ return strmatch(str, wildCard+1) || (('\0' != *str) && strmatch(str+1, wildCard));
	}else if(*wildCard=='?' ){ return ('\0' != *str) && strmatch(str+1, wildCard+1);
	}          else          { return ((uchar)*wildCard == (uchar)*str) && strmatch(str+1, wildCard+1);
	}
}

//===

bool sstd::isNum               (const char rhs){ return ('0'<=rhs && rhs<='9'); }
bool sstd::isAlphabet          (const char rhs){ return ('a'<=rhs && rhs<='z') || ('A'<=rhs && rhs<='Z'); }
bool sstd::isAlphabet_onlyUpper(const char rhs){ return ('A'<=rhs && rhs<='Z'); }
bool sstd::isAlphabet_onlyLower(const char rhs){ return ('a'<=rhs && rhs<='z'); }

