/*
#pragma once
#include "../typeDef.h"


namespace sstd{ class utf8; }

namespace sstd_utf8{
    // check: Unicode Character Category
//    bool is_Cc(); // "Cc" (other, control). 制御コード文字
//    bool is_Cf(); // "Cf" (other, format). 形式指定文字
//    bool is_ZWJ(); // Zero Width Joiner. ZWJ is included in "Cf".
//    bool is_Cn(); // "Cn" (other, not assigned). 未定義領域
//    bool is_Co(); // "Co" (other, private use). 私的領域
//    bool is_Cs(); // "Cs" (other, surrogate). 上位サロゲート文字または下位サロゲート文字


//  rm_CX(); // remove C (Other). C (Other) means "Cc", "Cf", "Cn", "Co" and "Cs".
//  rm_CX_owZWJ(); // without ZWJ
    
    size_t utf8_to_len(uint8* pStr, size_t size){
	size_t len=0; // returning the string length of UTF-8.
	
	for(uint i=0; i<size; ++i){
	    ;
	}
	
	return len;
    }
}

class sstd::utf8{
private:
    uint8* pStr; // pointer to the allocated memory
    size_t _size; // used size of pStr (wiht '\0' code).
    size_t _alloc_size; // allocated memory size
    
    size_t _len; // length of unicode string // calculated after input.
    
public:
    utf8(): pStr(NULL), _size(0), _alloc_size(0), _len(0) {} // 01
    utf8(const char* s_in){ // 02
	_size = strlen(s_in);
	_alloc_size = _size + 1;
	pStr = (uint8*)malloc( _alloc_size );
	memcpy(pStr, s_in, _size+1);
	
//	len = sstd_utf8::utf8_to_len(pStr);
    }
    ~utf8(){ free( pStr ); }
    
    const char* begin(){ return (char*)pStr; }
    const char* c_str(){ return (char*)pStr; }
//  const size_t end(){ retrun ; }
    const size_t size      (){ return _size;       }
    const size_t alloc_size(){ return _alloc_size; }
    const size_t len       (){ return _len;        }
    
    char& operator[](const uint i){ return (char&)pStr[i]; } // OPE.[] does Not guarantee the beginning of UTF-8 character code.
    
    // ==
    // !=
    
    // ++itr;
    // itr++;
    // --itr;
    // itr--;
    // itr.index()
    // u8[itr.index()]
};
//*/
