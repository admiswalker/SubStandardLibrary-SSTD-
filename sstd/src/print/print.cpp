#include "print.hpp"
#include "../string/ssprintf.hpp"
#include "../string/strmatch.hpp"


//-----------------------------------------------------------------------------------------------------------------------------------------------

void sstd::print_base(const  void* rhs){ printf("%p", rhs); }
void sstd::print_base(const  bool  rhs){ printf("%s", (rhs ? "true" : "false")); }
void sstd::print_base(const  char  rhs){ printf("'%c'", rhs); }
void sstd::print_base(const  int8  rhs){ printf("%d", rhs); }
void sstd::print_base(const  int16 rhs){ printf("%d", rhs); }
void sstd::print_base(const  int32 rhs){ printf("%d", rhs); }
void sstd::print_base(const  int64 rhs){ printf("%ld", rhs); }
void sstd::print_base(const uint8  rhs){ printf("%u", rhs); }
void sstd::print_base(const uint16 rhs){ printf("%u", rhs); }
void sstd::print_base(const uint32 rhs){ printf("%u", rhs); }
void sstd::print_base(const uint64 rhs){ printf("%lu", rhs); }
void sstd::print_base(const float  rhs){
    std::string s = sstd::ssprintf("%g", rhs);
    if(! sstd::charIn('.', s) ){ s += '.'; }
    printf("%s", s.c_str());
}
void sstd::print_base(const double  rhs){
    std::string s = sstd::ssprintf("%g", rhs); // Note: Prioritize readability and do not display all effective digits of double-precision type.
    if(! sstd::charIn('.', s) ){ s += '.'; }
    printf("%s", s.c_str());
}
void sstd::print_base(const        char* rhs){ printf("\"%s\"", rhs); }
void sstd::print_base(const std::string& rhs){ printf("\"%s\"", rhs.c_str()); }
void sstd::print_base(const struct pathAndType& rhs){ printf("\"path: %s, type: %s\"", rhs.path.c_str(), (rhs.type=='f' ? "file" : "directory")); }


void sstd::for_printn( void* rhs){ printf(" = "); sstd::print(rhs); }
void sstd::for_printn( bool  rhs){ printf(" = "); sstd::print(rhs); }
void sstd::for_printn( char  rhs){ printf(" = "); sstd::print(rhs); }
void sstd::for_printn( int8  rhs){ printf(" = "); sstd::print(rhs); }
void sstd::for_printn( int16 rhs){ printf(" = "); sstd::print(rhs); }
void sstd::for_printn( int32 rhs){ printf(" = "); sstd::print(rhs); }
void sstd::for_printn( int64 rhs){ printf(" = "); sstd::print(rhs); }
void sstd::for_printn(uint8  rhs){ printf(" = "); sstd::print(rhs); }
void sstd::for_printn(uint16 rhs){ printf(" = "); sstd::print(rhs); }
void sstd::for_printn(uint32 rhs){ printf(" = "); sstd::print(rhs); }
void sstd::for_printn(uint64 rhs){ printf(" = "); sstd::print(rhs); }
void sstd::for_printn( float rhs){ printf(" = "); sstd::print(rhs); }
void sstd::for_printn(double rhs){ printf(" = "); sstd::print(rhs); }
void sstd::for_printn(const        char* rhs){ printf(" = "); sstd::print(rhs); }
void sstd::for_printn(const std::string& rhs){ printf(" = "); sstd::print(rhs); }
void sstd::for_printn(const struct pathAndType& rhs){ printf(" = "); sstd::print(rhs); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
