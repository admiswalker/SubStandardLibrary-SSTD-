#include "strmatch.hpp"
#include "./typeDef.h"

//　ワイルドカード ('*', '?') の使用可能な文字列比較関数を作る。
//　'*' は任意の文字列と一致し、'?' は空文字('\0')を除く任意の一文字と一致する。

bool sstd::strmatch(
		const char* str,     // 比較する文字列
		const char* wildCard // ワイルドカード
){
	if      (*wildCard=='\0'){ return '\0' == *str;
	}else if(*wildCard=='*' ){ return strmatch(str, wildCard+1) || (('\0' != *str) && strmatch(str+1, wildCard));
	}else if(*wildCard=='?' ){ return ('\0' != *str) && strmatch(str+1, wildCard+1);
	}          else          { return ((uchar)*wildCard == (uchar)*str) && strmatch(str+1, wildCard+1);
	}
}


bool getWC_entity(
		const char* str,      // 比較する文字列
		const char* wildCard, // ワイルドカード
		std::string& retWC    // ワイルドカード部分に一致する文字列を返却
){
	if      (*wildCard=='\0'){ return '\0' == *str;
	}else if(*wildCard=='*' ){ retWC += *str;
 		                       return getWC_entity(str, wildCard+1, retWC) || (('\0' != *str) && getWC_entity(str+1, wildCard, retWC));
	}else if(*wildCard=='?' ){ retWC += *str;
		                       return ('\0' != *str) && getWC_entity(str+1, wildCard+1, retWC);
	}          else          { return ((uchar)*wildCard == (uchar)*str) && getWC_entity(str+1, wildCard+1, retWC);
	}
}
bool sstd::strmatch_getWC(
		const char* str,      // 比較する文字列
		const char* wildCard, // ワイルドカード
		std::string& retWC    // ワイルドカード部分に一致する文字列を返却
){
	retWC.clear();
	bool ret = getWC_entity(str, wildCard, retWC);
	if(!ret){ retWC.clear(); }
	return ret;
}


bool sstd::isNum               (char rhs){ return ('0'<=rhs && rhs<='9'); }
bool sstd::isAlphabet          (char rhs){ return ('a'<=rhs && rhs<='z') || ('A'<=rhs && rhs<='Z'); }
bool sstd::isAlphabet_onlyUpper(char rhs){ return ('A'<=rhs && rhs<='Z'); }
bool sstd::isAlphabet_onlyLower(char rhs){ return ('a'<=rhs && rhs<='z'); }

