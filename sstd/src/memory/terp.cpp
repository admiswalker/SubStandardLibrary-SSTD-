#include "terp.hpp"

#include "../definitions/typeNum.hpp"
#include "../print/pdbg.hpp"


//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::list

sstd::terp::var sstd::terp::list(uint allocate_size){
    sstd::terp::var r;
    r.p()->overwrite(new std::vector<sstd::void_ptr>(allocate_size));
    return r;
}
sstd::terp::var sstd::terp::list(){ return sstd::terp::list(0); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::hash

sstd::terp::var sstd::terp::hash(uint allocate_size){
    sstd::terp::var r;
    r.p()->overwrite(new std::unordered_map<std::string, sstd::void_ptr>(allocate_size));
    return r;
}
sstd::terp::var sstd::terp::hash(){ return sstd::terp::hash(0); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// cast

std::vector<sstd::void_ptr>*                    sstd::terp::cast_vec_void_ptr     (void* rhs){ return (std::vector<sstd::void_ptr>*)rhs; }
std::unordered_map<std::string,sstd::void_ptr>* sstd::terp::cast_hash_str_void_ptr(void* rhs){ return (std::unordered_map<std::string,sstd::void_ptr>*)rhs; }

//-----------------------------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------------------------------

