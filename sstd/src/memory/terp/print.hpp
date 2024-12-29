#pragma once
#include "terp.hpp"

namespace sstd{
    void print_base(const sstd::terp::var& rhs);
    void print_base(const sstd::terp::var* rhs); // TODO: write tests
}
