#pragma once

#include <stddef.h>
#include "../definitions/typeDef.h"

namespace sstd{
    bool file_size(size_t& ret_size, const char* path);
}
