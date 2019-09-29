#include <stdlib.h>
#include <string>

#include "./stdlib.hpp"

int sstd::system(const        char* str){ return ::system(str        ); }
int sstd::system(const std::string& str){ return ::system(str.c_str()); }

