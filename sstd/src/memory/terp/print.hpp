#pragma once
#include "terp.hpp"

namespace sstd{
    std::string to_string(const sstd::terp::var& rhs);
    std::string to_string(const sstd::terp::var* rhs); // TODO: write tests
}
