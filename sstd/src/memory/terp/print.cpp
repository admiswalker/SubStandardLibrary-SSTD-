#include "print.hpp"

#include "../../definitions/typeNum.hpp"
#include "../../print/pdbg.hpp"

#include "../../print/print.hpp" // for debug

//-----------------------------------------------------------------------------------------------------------------------------------------------
// define internal functjions

void _print_terp_str(const sstd::terp::var& rhs);
void _print_terp_list_internal(const sstd::terp::var& rhs);
void _print_terp_list(const sstd::terp::var& rhs);
void _print_terp_hash(const sstd::terp::var& rhs);

//-----------------------------------------------------------------------------------------------------------------------------------------------

void _print_terp_str(const sstd::terp::var& rhs){
    printf("%s", rhs.to<std::string>().c_str());
}
void _print_terp_list_internal(const sstd::terp::var& rhs){
    switch(rhs.typeNum()){
    case sstd::num_str              : { _print_terp_str (rhs); } break;
    case sstd::num_vec_void_ptr     : { _print_terp_list(rhs); } break;
    case sstd::num_hash_str_void_ptr: { _print_terp_hash(rhs); } break;
    case sstd::num_null: {} break;
    default: { sstd::pdbg("ERROR"); } break;
    }
}
void _print_terp_list(const sstd::terp::var& rhs){
    printf("[");
    if(rhs.size()>=1){
        for(uint i=0; i<rhs.size()-1; ++i){ _print_terp_list_internal(rhs[i]); printf(" "); }
        _print_terp_list_internal( rhs[rhs.size()-1] );
    }
    printf("]");
}
void _print_terp_hash(const sstd::terp::var& rhs){
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

void sstd::print(const sstd::terp::var& rhs){
    switch(rhs.typeNum()){
    case sstd::num_str              : { _print_terp_str (rhs); } break;
    case sstd::num_vec_void_ptr     : { _print_terp_list(rhs); } break;
    case sstd::num_hash_str_void_ptr: { _print_terp_hash(rhs); } break;
    case sstd::num_null: {} break;
    default: { sstd::pdbg("ERROR"); } break;
    }
    printf("\n");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
