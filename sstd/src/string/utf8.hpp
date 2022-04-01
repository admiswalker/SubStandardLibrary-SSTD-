#pragma once
#include <stdio.h>
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
    
    size_t utf8_to_len(uint8* pStr, size_t size);
}

class sstd::utf8{
private:
    uint8* pStr; // pointer to the allocated memory
    size_t _size; // used size of pStr (wiht '\0' code).
    size_t _alloc_size; // allocated memory size
    
    size_t _len; // length of unicode string // calculated after input.
    
public:
    utf8();
    utf8(const char* s_in);
    ~utf8();
    
    const char* begin();
    const char* c_str();
//  const size_t end();
    const size_t size      ();
    const size_t alloc_size();
    const size_t len       ();
    
    char& operator[](const uint i);
    
    // ==
    // !=
    
    // ++itr;
    // itr++;
    // --itr;
    // itr--;
    // itr.index()
    // u8[itr.index()]
};
