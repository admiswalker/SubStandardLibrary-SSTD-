#include "./print_new.hpp"
#include "./ssprintf.hpp"
#include "./strmatch.hpp" // for dev
//#include <stdio.h>

//-----------------------------------------------------------------------------------------------------------------------------------------------

// woLF: without line feed code ('\n')
void sstd::print_woLF_new(const  bool  rhs){ printf("%c", (rhs ? 'T' : 'F')); }
void sstd::print_woLF_new(const  char  rhs){ printf("'%c'", rhs); }
void sstd::print_woLF_new(const  int8  rhs){ printf("%d", rhs); }
void sstd::print_woLF_new(const  int16 rhs){ printf("%d", rhs); }
void sstd::print_woLF_new(const  int32 rhs){ printf("%d", rhs); }
void sstd::print_woLF_new(const  int64 rhs){ printf("%ld", rhs); }
void sstd::print_woLF_new(const uint8  rhs){ printf("%u", rhs); }
void sstd::print_woLF_new(const uint16 rhs){ printf("%u", rhs); }
void sstd::print_woLF_new(const uint32 rhs){ printf("%u", rhs); }
void sstd::print_woLF_new(const uint64 rhs){ printf("%lu", rhs); }
void sstd::print_woLF_new(const float  rhs){
    std::string s = sstd::ssprintf("%g", rhs);
    if(! sstd::charIn('.', s) ){ s += '.'; }
    printf("%s", s.c_str());
}
void sstd::print_woLF_new(const double  rhs){
    std::string s = sstd::ssprintf("%g", rhs); // Note: Prioritize readability and do not display all effective digits of double-precision type.
    if(! sstd::charIn('.', s) ){ s += '.'; }
    printf("%s", s.c_str());
}
void sstd::print_woLF_new(const        char* rhs){ printf("\"%s\"", rhs); }
void sstd::print_woLF_new(const std::string& rhs){ printf("\"%s\"", rhs.c_str()); }
    
// with line feed code ('\n')
void sstd::print_new(const  bool  rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
void sstd::print_new(const  char  rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
void sstd::print_new(const  int8  rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
void sstd::print_new(const  int16 rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
void sstd::print_new(const  int32 rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
void sstd::print_new(const  int64 rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
void sstd::print_new(const uint8  rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
void sstd::print_new(const uint16 rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
void sstd::print_new(const uint32 rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
void sstd::print_new(const uint64 rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
void sstd::print_new(const float  rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
void sstd::print_new(const double rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
void sstd::print_new(const        char* rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
void sstd::print_new(const std::string& rhs){ sstd::print_woLF_new(rhs); printf("\n"); }
    
void sstd::for_printn_new( bool  rhs){ printf(" = "); sstd::print_new(rhs); }
void sstd::for_printn_new( char  rhs){ printf(" = "); sstd::print_new(rhs); }
void sstd::for_printn_new( int8  rhs){ printf(" = "); sstd::print_new(rhs); }
void sstd::for_printn_new( int16 rhs){ printf(" = "); sstd::print_new(rhs); }
void sstd::for_printn_new( int32 rhs){ printf(" = "); sstd::print_new(rhs); }
void sstd::for_printn_new( int64 rhs){ printf(" = "); sstd::print_new(rhs); }
void sstd::for_printn_new(uint8  rhs){ printf(" = "); sstd::print_new(rhs); }
void sstd::for_printn_new(uint16 rhs){ printf(" = "); sstd::print_new(rhs); }
void sstd::for_printn_new(uint32 rhs){ printf(" = "); sstd::print_new(rhs); }
void sstd::for_printn_new(uint64 rhs){ printf(" = "); sstd::print_new(rhs); }
void sstd::for_printn_new( float rhs){ printf(" = "); sstd::print_new(rhs); }
void sstd::for_printn_new(double rhs){ printf(" = "); sstd::print_new(rhs); }
void sstd::for_printn_new(const        char* rhs){ printf(" = "); sstd::print_new(rhs); }
void sstd::for_printn_new(const std::string& rhs){ printf(" = "); sstd::print_new(rhs); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
