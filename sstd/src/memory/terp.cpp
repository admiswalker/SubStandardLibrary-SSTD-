#include "terp.hpp"

#include "../definitions/typeNum.hpp"
#include "../print/pdbg.hpp"


//-----------------------------------------------------------------------------------------------------------------------------------------------
// for user

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for internal use

//-----------------------------------------------------------------------------------------------------------------------------------------------
// iterator

void sstd::terp::_to(std::string& dst, const sstd::void_ptr& src){ dst = (*(std::string*)src.ptr()); }
void sstd::terp::_to(std::string& dst, const std::string   & src){ dst =                 src       ; }

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

std::vector<sstd::void_ptr>*                    sstd::terp::cast2vec (void* rhs){ return (std::vector<sstd::void_ptr>*)rhs; }
std::unordered_map<std::string,sstd::void_ptr>* sstd::terp::cast2hash(void* rhs){ return (std::unordered_map<std::string,sstd::void_ptr>*)rhs; }

//-----------------------------------------------------------------------------------------------------------------------------------------------

