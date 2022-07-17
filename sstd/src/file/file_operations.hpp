#pragma once

#include "../typeDef.h"
//#include <sys/stat.h>
//#include <vector>

namespace sstd{
    bool file_size(uint64& ret_size, const char* path);
}
