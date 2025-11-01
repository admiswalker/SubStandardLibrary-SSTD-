#include "print.hpp"
#include "../string/ssprintf.hpp"
#include "../string/strmatch.hpp"


//-----------------------------------------------------------------------------------------------------------------------------------------------

std::string sstd::to_string(const  void* rhs){ return sstd::ssprintf("%p", rhs); }
std::string sstd::to_string(const  bool  rhs){ return sstd::ssprintf("%s", (rhs ? "true" : "false")); }
std::string sstd::to_string(const  char  rhs){ return sstd::ssprintf("'%c'", rhs); }
std::string sstd::to_string(const  int8  rhs){ return sstd::ssprintf("%d", rhs); }
std::string sstd::to_string(const  int16 rhs){ return sstd::ssprintf("%d", rhs); }
std::string sstd::to_string(const  int32 rhs){ return sstd::ssprintf("%d", rhs); }
std::string sstd::to_string(const  int64 rhs){ return sstd::ssprintf("%ld", rhs); }
std::string sstd::to_string(const uint8  rhs){ return sstd::ssprintf("%u", rhs); }
std::string sstd::to_string(const uint16 rhs){ return sstd::ssprintf("%u", rhs); }
std::string sstd::to_string(const uint32 rhs){ return sstd::ssprintf("%u", rhs); }
std::string sstd::to_string(const uint64 rhs){ return sstd::ssprintf("%lu", rhs); }
std::string sstd::to_string(const float  rhs){
    std::string s = sstd::ssprintf("%g", rhs);
    if(! sstd::charIn('.', s) ){ s += '.'; }
    return sstd::ssprintf("%s", s.c_str());
}
std::string sstd::to_string(const double  rhs){
    std::string s = sstd::ssprintf("%g", rhs); // Note: Prioritize readability and do not display all effective digits of double-precision type.
    if(! sstd::charIn('.', s) ){ s += '.'; }
    return sstd::ssprintf("%s", s.c_str());
}
std::string sstd::to_string(const        char* rhs){ return sstd::ssprintf("\"%s\"", rhs); }
std::string sstd::to_string(const std::string& rhs){ return sstd::ssprintf("\"%s\"", rhs.c_str()); }
std::string sstd::to_string(const struct pathAndType& rhs){ return sstd::ssprintf("\"path: %s, type: %s\"", rhs.path.c_str(), (rhs.type=='f' ? "file" : "directory")); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
