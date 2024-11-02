#pragma once
#include "terp.hpp"

namespace sstd{
    void print       (const sstd::terp::var& rhs);
    void for_printn  (const sstd::terp::var& rhs);
    void print_for_vT(const sstd::terp::var& rhs);

    void print       (const sstd::terp::var* rhs); // TODO: write tests
    void for_printn  (const sstd::terp::var* rhs);
    void print_for_vT(const sstd::terp::var* rhs);
    
    void print       (const sstd::terp::path& rhs); // TODO: write tests
    void for_printn  (const sstd::terp::path& rhs);
    void print_for_vT(const sstd::terp::path& rhs);
}
