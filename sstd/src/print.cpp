#include "./print.hpp"
#include "./ssprintf.hpp"
#include "./strmatch.hpp"


//-----------------------------------------------------------------------------------------------------------------------------------------------

void sstd::print(const  bool  rhs){ printf("%s\n", (rhs ? "true" : "false")); }
void sstd::print(const  char  rhs){ printf("'%c'\n", rhs); }
void sstd::print(const  int8  rhs){ printf("%d\n", rhs); }
void sstd::print(const  int16 rhs){ printf("%d\n", rhs); }
void sstd::print(const  int32 rhs){ printf("%d\n", rhs); }
void sstd::print(const  int64 rhs){ printf("%ld\n", rhs); }
void sstd::print(const uint8  rhs){ printf("%u\n", rhs); }
void sstd::print(const uint16 rhs){ printf("%u\n", rhs); }
void sstd::print(const uint32 rhs){ printf("%u\n", rhs); }
void sstd::print(const uint64 rhs){ printf("%lu\n", rhs); }
void sstd::print(const float  rhs){
    std::string s = sstd::ssprintf("%g", rhs);
    if(! sstd::charIn('.', s) ){ s += '.'; }
    printf("%s\n", s.c_str());
}
void sstd::print(const double  rhs){
    std::string s = sstd::ssprintf("%g", rhs); // Note: Prioritize readability and do not display all effective digits of double-precision type.
    if(! sstd::charIn('.', s) ){ s += '.'; }
    printf("%s\n", s.c_str());
}
void sstd::print(const        char* rhs){ printf("\"%s\"\n", rhs); }
void sstd::print(const std::string& rhs){ printf("\"%s\"\n", rhs.c_str()); }


void sstd::print_for_vT(const  bool  rhs){ printf("%s", (rhs ? "true" : "false")); }
void sstd::print_for_vT(const  char  rhs){ printf("'%c'", rhs); }
void sstd::print_for_vT(const  int8  rhs){ printf("%d", rhs); }
void sstd::print_for_vT(const  int16 rhs){ printf("%d", rhs); }
void sstd::print_for_vT(const  int32 rhs){ printf("%d", rhs); }
void sstd::print_for_vT(const  int64 rhs){ printf("%ld", rhs); }
void sstd::print_for_vT(const uint8  rhs){ printf("%u", rhs); }
void sstd::print_for_vT(const uint16 rhs){ printf("%u", rhs); }
void sstd::print_for_vT(const uint32 rhs){ printf("%u", rhs); }
void sstd::print_for_vT(const uint64 rhs){ printf("%lu", rhs); }
void sstd::print_for_vT(const float  rhs){
    std::string s = sstd::ssprintf("%g", rhs);
    if(! sstd::charIn('.', s) ){ s += '.'; }
    printf("%s", s.c_str());
}
void sstd::print_for_vT(const double  rhs){
    std::string s = sstd::ssprintf("%g", rhs); // Note: Prioritize readability and do not display all effective digits of double-precision type.
    if(! sstd::charIn('.', s) ){ s += '.'; }
    printf("%s", s.c_str());
}
void sstd::print_for_vT(const        char* rhs){ printf("\"%s\"", rhs); }
void sstd::print_for_vT(const std::string& rhs){ printf("\"%s\"", rhs.c_str()); }


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

//-----------------------------------------------------------------------------------------------------------------------------------------------
