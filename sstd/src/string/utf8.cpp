#include "utf8.hpp"
#include <stdlib.h>
#include <string.h>


size_t sstd_utf8::utf8_to_len(uint8* pStr, size_t size){
    size_t len=0; // returning the string length of UTF-8.
	
    for(uint i=0; i<size; ++i){
        ;
    }
	
    return len;
}


sstd::utf8::utf8(): pStr(NULL), _size(0), _alloc_size(0), _len(0) {} // 01
sstd::utf8::utf8(const char* s_in){ // 02
    _size = strlen(s_in);
    _alloc_size = _size + 1;
    pStr = (uint8*)malloc( _alloc_size );
    memcpy(pStr, s_in, _size+1);
	
    //	len = sstd_utf8::utf8_to_len(pStr);
}
sstd::utf8::~utf8(){ free( pStr ); }
    
const char* sstd::utf8::begin(){ return (char*)pStr; }
const char* sstd::utf8::c_str(){ return (char*)pStr; }
//  const size_t end(){ retrun ; }
const size_t sstd::utf8::size      (){ return _size;       }
const size_t sstd::utf8::alloc_size(){ return _alloc_size; }
const size_t sstd::utf8::len       (){ return _len;        }
    
char& sstd::utf8::operator[](const uint i){ return (char&)pStr[i]; } // OPE.[] does Not guarantee the beginning of UTF-8 character code.
