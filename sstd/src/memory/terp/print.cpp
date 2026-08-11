#include "print.hpp"

#include "../../definitions/typeNum.hpp"
#include "../../print/pdbg.hpp"

#include "../../print/print.hpp" // for debug

//-----------------------------------------------------------------------------------------------------------------------------------------------
// define internal functjions

std::string _to_string_terp_str(const sstd::terp::var& rhs);
std::string _to_string_terp_list_internal(const sstd::terp::var& rhs);
std::string _to_string_terp_list(const sstd::terp::var& rhs);
std::string _to_string_terp_hash(const sstd::terp::var& rhs);

//-----------------------------------------------------------------------------------------------------------------------------------------------

std::string _to_string_terp_str(const sstd::terp::var& rhs){
    return sstd::ssprintf("\"%s\"", rhs.to<std::string>().c_str());
}
std::string _to_string_terp_list_internal(const sstd::terp::var& rhs){
    std::string res;
    switch(rhs.typeNum()){
    case sstd::num_str          : { res+=_to_string_terp_str (rhs); } break;
    case sstd::num_vec_terp_var : { res+=_to_string_terp_list(rhs); } break;
    case sstd::num_hash_terp_var: { res+=_to_string_terp_hash(rhs); } break;
    case sstd::num_null: {} break;
    default: { res+=sstd::pdbg_err_str("ERROR"); } break;
    }
    return res;
}
std::string _to_string_terp_list(const sstd::terp::var& rhs){
    std::string res;
    res += "[";
    if(rhs.size()>=1){
        for(uint i=0; i<rhs.size()-1; ++i){ res+=_to_string_terp_list_internal(rhs[i]); res+=" "; }
        res += _to_string_terp_list_internal( rhs[rhs.size()-1] );
    }
    res += "]";
    return res;
}
std::string _to_string_terp_hash(const sstd::terp::var& rhs){
    std::string res;
    res += "{";
    for(auto itr=rhs.begin(); itr!=rhs.end(); ++itr){
        if(itr!=rhs.begin()){ res+=", "; }
        res += sstd::ssprintf("\"%s\": ", itr.first_to<std::string>().c_str()); // _to_string_terp_list_internal(itr.first());
        res += _to_string_terp_list_internal(itr.second());
    }
    res += "}";
    return res;
}

//---

std::string sstd::to_string(const sstd::terp::var& rhs){
    std::string res;
    switch(rhs.typeNum()){
    case sstd::num_str          : { res+=_to_string_terp_str (rhs); } break;
    case sstd::num_vec_terp_var : { res+=_to_string_terp_list(rhs); } break;
    case sstd::num_hash_terp_var: { res+=_to_string_terp_hash(rhs); } break;
    case sstd::num_null: {} break;
    default: { res+=sstd::pdbg_err_str("ERROR"); } break;
    }
    return res;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

std::string sstd::to_string(const sstd::terp::var* rhs){
    return sstd::ssprintf("%p", rhs); 
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
