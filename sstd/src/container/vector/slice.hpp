#pragma once
#include <stddef.h>
#include <vector>
#include "../../definitions/typeDef.h"
#include "../../definitions/itr.hpp" // definition of sstd::begin() and sstd::end()

//-----------------------------------------------------------------------------------------------------------------------------------------------

// i: int
// u: uint
// s: size_t
// b: sstd::begin()
// e: sstd::end()

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define DEF_slice_empty(structName)             \
    private:                                    \
    public:                                     \
    structName(){}                              \
    ~structName(){}

#define DEF_slice_x(structName, type)           \
    private:                                    \
    public:                                     \
    type val;                                   \
    structName(type val_in): val(val_in) {}     \
    ~structName(){}

#define DEF_slice_xx(structName, lhsType, rhsType)                      \
    private:                                                            \
    public:                                                             \
    lhsType lhs;                                                        \
    rhsType rhs;                                                        \
    structName(lhsType lhs_in, rhsType rhs_in){ lhs=lhs_in; rhs=rhs_in; } \
    ~structName(){}

namespace sstd_vecSc{
    struct slice_i { DEF_slice_x (slice_i,    int); };
    struct slice_u { DEF_slice_x (slice_u,   uint); };
    struct slice_s { DEF_slice_x (slice_s, size_t); };
    struct slice_b { DEF_slice_empty(slice_b);      };
    struct slice_e { DEF_slice_empty(slice_e);      };
    struct slice_vi{ DEF_slice_x (slice_vi, const std::vector< int>&); };
    struct slice_vu{ DEF_slice_x (slice_vu, const std::vector<uint>&); };
    
    struct slice_ii{ DEF_slice_xx(slice_ii,    int,    int); };
    struct slice_iu{ DEF_slice_xx(slice_iu,    int,   uint); };
    struct slice_is{ DEF_slice_xx(slice_is,    int, size_t); };
    struct slice_ui{ DEF_slice_xx(slice_ui,   uint,    int); };
    struct slice_uu{ DEF_slice_xx(slice_uu,   uint,   uint); };
    struct slice_us{ DEF_slice_xx(slice_us,   uint, size_t); };
    struct slice_si{ DEF_slice_xx(slice_si, size_t,    int); };
    struct slice_su{ DEF_slice_xx(slice_su, size_t,   uint); };
    struct slice_ss{ DEF_slice_xx(slice_ss, size_t, size_t); };
    
    struct slice_bi{ DEF_slice_x (slice_bi,    int); };
    struct slice_bu{ DEF_slice_x (slice_bu,   uint); };
    struct slice_bs{ DEF_slice_x (slice_bs, size_t); };
    struct slice_ie{ DEF_slice_x (slice_ie,    int); };
    struct slice_ue{ DEF_slice_x (slice_ue,   uint); };
    struct slice_se{ DEF_slice_x (slice_se, size_t); };
    struct slice_be{ DEF_slice_empty(slice_be);      };
    
    //---
    
    struct slice_mv_i { DEF_slice_x (slice_mv_i,    int); };
    struct slice_mv_u { DEF_slice_x (slice_mv_u,   uint); };
    struct slice_mv_s { DEF_slice_x (slice_mv_s, size_t); };
    struct slice_mv_b { DEF_slice_empty(slice_mv_b);      };
    struct slice_mv_e { DEF_slice_empty(slice_mv_e);      };
    struct slice_mv_vi{ DEF_slice_x (slice_mv_vi, const std::vector< int>&); };
    struct slice_mv_vu{ DEF_slice_x (slice_mv_vu, const std::vector<uint>&); };
    
    struct slice_mv_ii{ DEF_slice_xx(slice_mv_ii,    int,    int); };
    struct slice_mv_iu{ DEF_slice_xx(slice_mv_iu,    int,   uint); };
    struct slice_mv_is{ DEF_slice_xx(slice_mv_is,    int, size_t); };
    struct slice_mv_ui{ DEF_slice_xx(slice_mv_ui,   uint,    int); };
    struct slice_mv_uu{ DEF_slice_xx(slice_mv_uu,   uint,   uint); };
    struct slice_mv_us{ DEF_slice_xx(slice_mv_us,   uint, size_t); };
    struct slice_mv_si{ DEF_slice_xx(slice_mv_si, size_t,    int); };
    struct slice_mv_su{ DEF_slice_xx(slice_mv_su, size_t,   uint); };
    struct slice_mv_ss{ DEF_slice_xx(slice_mv_ss, size_t, size_t); };
    
    struct slice_mv_bi{ DEF_slice_x (slice_mv_bi,    int); };
    struct slice_mv_bu{ DEF_slice_x (slice_mv_bu,   uint); };
    struct slice_mv_bs{ DEF_slice_x (slice_mv_bs, size_t); };
    struct slice_mv_ie{ DEF_slice_x (slice_mv_ie,    int); };
    struct slice_mv_ue{ DEF_slice_x (slice_mv_ue,   uint); };
    struct slice_mv_se{ DEF_slice_x (slice_mv_se, size_t); };
    struct slice_mv_be{ DEF_slice_empty(slice_mv_be);      };
}

#undef DEF_slice_empty
#undef DEF_slice_x
#undef DEF_slice_xx

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
    sstd_vecSc::slice_i  slice(const         int val);
    sstd_vecSc::slice_u  slice(const        uint val);
    sstd_vecSc::slice_s  slice(const      size_t val);
    sstd_vecSc::slice_b  slice(const sstd::begin val);
    sstd_vecSc::slice_e  slice(const sstd::end   val);
    sstd_vecSc::slice_vi slice(const std::vector< int>& val);
    sstd_vecSc::slice_vu slice(const std::vector<uint>& val);
    
    sstd_vecSc::slice_ii slice(const         int lhs, const       int rhs);
    sstd_vecSc::slice_iu slice(const         int lhs, const      uint rhs);
    sstd_vecSc::slice_is slice(const         int lhs, const    size_t rhs);
    sstd_vecSc::slice_ui slice(const        uint lhs, const       int rhs);
    sstd_vecSc::slice_uu slice(const        uint lhs, const      uint rhs);
    sstd_vecSc::slice_us slice(const        uint lhs, const    size_t rhs);
    sstd_vecSc::slice_si slice(const      size_t lhs, const       int rhs);
    sstd_vecSc::slice_su slice(const      size_t lhs, const      uint rhs);
    sstd_vecSc::slice_ss slice(const      size_t lhs, const    size_t rhs);
    
    sstd_vecSc::slice_bi slice(const sstd::begin lhs, const       int rhs);
    sstd_vecSc::slice_bu slice(const sstd::begin lhs, const      uint rhs);
    sstd_vecSc::slice_bs slice(const sstd::begin lhs, const    size_t rhs);
    sstd_vecSc::slice_ie slice(const         int lhs, const sstd::end rhs);
    sstd_vecSc::slice_ue slice(const        uint lhs, const sstd::end rhs);
    sstd_vecSc::slice_se slice(const      size_t lhs, const sstd::end rhs);
    sstd_vecSc::slice_be slice(const sstd::begin lhs, const sstd::end rhs);
    
    //---
    
    sstd_vecSc::slice_mv_i  slice_mv(const         int val);
    sstd_vecSc::slice_mv_u  slice_mv(const        uint val);
    sstd_vecSc::slice_mv_s  slice_mv(const      size_t val);
    sstd_vecSc::slice_mv_b  slice_mv(const sstd::begin val);
    sstd_vecSc::slice_mv_e  slice_mv(const sstd::end   val);
    sstd_vecSc::slice_mv_vi slice_mv(const std::vector< int>& val);
    sstd_vecSc::slice_mv_vu slice_mv(const std::vector<uint>& val);
    
    sstd_vecSc::slice_mv_ii slice_mv(const         int lhs, const       int rhs);
    sstd_vecSc::slice_mv_iu slice_mv(const         int lhs, const      uint rhs);
    sstd_vecSc::slice_mv_is slice_mv(const         int lhs, const    size_t rhs);
    sstd_vecSc::slice_mv_ui slice_mv(const        uint lhs, const       int rhs);
    sstd_vecSc::slice_mv_uu slice_mv(const        uint lhs, const      uint rhs);
    sstd_vecSc::slice_mv_us slice_mv(const        uint lhs, const    size_t rhs);
    sstd_vecSc::slice_mv_si slice_mv(const      size_t lhs, const       int rhs);
    sstd_vecSc::slice_mv_su slice_mv(const      size_t lhs, const      uint rhs);
    sstd_vecSc::slice_mv_ss slice_mv(const      size_t lhs, const    size_t rhs);
    
    sstd_vecSc::slice_mv_bi slice_mv(const sstd::begin lhs, const       int rhs);
    sstd_vecSc::slice_mv_bu slice_mv(const sstd::begin lhs, const      uint rhs);
    sstd_vecSc::slice_mv_bs slice_mv(const sstd::begin lhs, const    size_t rhs);
    sstd_vecSc::slice_mv_ie slice_mv(const         int lhs, const sstd::end rhs);
    sstd_vecSc::slice_mv_ue slice_mv(const        uint lhs, const sstd::end rhs);
    sstd_vecSc::slice_mv_se slice_mv(const      size_t lhs, const sstd::end rhs);
    sstd_vecSc::slice_mv_be slice_mv(const sstd::begin lhs, const sstd::end rhs);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define int2loc(i) /* integer2location */       \
    if(i<0){ i+=(int)vec.size(); }
#define DEF_slice_x_base(CAST_VAL, valLoc)                          \
    std::vector<T> ret = std::vector<T>{ (CAST_VAL)(vec[valLoc]) };
#define DEF_slice_xx_base(CAST_VAL, lhsLoc, rhsLoc)                     \
    std::vector<T> ret((uint)rhsLoc-(uint)lhsLoc);                      \
    for(uint r=0, i=(uint)lhsLoc; i<(uint)rhsLoc; ++r,++i){ ret[r] = (CAST_VAL)(vec[i]); }
#define DEF_slice_i_index_base(CAST_VAL, val)                           \
    std::vector<T> ret(val.size()); for(uint i=0; i<val.size(); ++i){  int idx=val[i]; int2loc(idx); ret[i]=(CAST_VAL)(vec[idx]); }
#define DEF_slice_u_index_base(CAST_VAL, val)                           \
    std::vector<T> ret(val.size()); for(uint i=0; i<val.size(); ++i){ uint idx=val[i];               ret[i]=(CAST_VAL)(vec[idx]); }

template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_i  s){ int2loc(s.val); DEF_slice_x_base(T,        s.val); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_u  s){                 DEF_slice_x_base(T,        s.val); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_s  s){                 DEF_slice_x_base(T,        s.val); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_b  s){                 DEF_slice_x_base(T,      (uint)0); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_e  s){                 DEF_slice_x_base(T, vec.size()-1); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_vi s){                 DEF_slice_i_index_base(T,  s.val); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_vu s){                 DEF_slice_u_index_base(T,  s.val); return ret; }

template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_ii s){ int2loc(s.lhs); int2loc(s.rhs); DEF_slice_xx_base(T, s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_iu s){ int2loc(s.lhs);                 DEF_slice_xx_base(T, s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_is s){ int2loc(s.lhs);                 DEF_slice_xx_base(T, s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_ui s){                 int2loc(s.rhs); DEF_slice_xx_base(T, s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_uu s){                                 DEF_slice_xx_base(T, s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_us s){                                 DEF_slice_xx_base(T, s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_si s){                 int2loc(s.rhs); DEF_slice_xx_base(T, s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_su s){                                 DEF_slice_xx_base(T, s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_ss s){                                 DEF_slice_xx_base(T, s.lhs, s.rhs); return ret; }

template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_bi s){                 int2loc(s.val); DEF_slice_xx_base(T, (uint)0,      s.val); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_bu s){                                 DEF_slice_xx_base(T, (uint)0,      s.val); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_bs s){                                 DEF_slice_xx_base(T, (uint)0,      s.val); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_ie s){ int2loc(s.val);                 DEF_slice_xx_base(T,   s.val, vec.size()); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_ue s){                                 DEF_slice_xx_base(T,   s.val, vec.size()); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_se s){                                 DEF_slice_xx_base(T,   s.val, vec.size()); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_be s){                                 DEF_slice_xx_base(T, (uint)0, vec.size()); return ret; }

//---

template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_i  s){ int2loc(s.val); DEF_slice_x_base(std::move,        s.val); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_u  s){                 DEF_slice_x_base(std::move,        s.val); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_s  s){                 DEF_slice_x_base(std::move,        s.val); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_b  s){                 DEF_slice_x_base(std::move,      (uint)0); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_e  s){                 DEF_slice_x_base(std::move, vec.size()-1); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_vi s){                 DEF_slice_i_index_base(std::move,  s.val); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_vu s){                 DEF_slice_u_index_base(std::move,  s.val); return ret; }

template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_ii s){ int2loc(s.lhs); int2loc(s.rhs); DEF_slice_xx_base(std::move, s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_iu s){ int2loc(s.lhs);                 DEF_slice_xx_base(std::move, s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_is s){ int2loc(s.lhs);                 DEF_slice_xx_base(std::move, s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_ui s){                 int2loc(s.rhs); DEF_slice_xx_base(std::move, s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_uu s){                                 DEF_slice_xx_base(std::move, s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_us s){                                 DEF_slice_xx_base(std::move, s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_si s){                 int2loc(s.rhs); DEF_slice_xx_base(std::move, s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_su s){                                 DEF_slice_xx_base(std::move, s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_ss s){                                 DEF_slice_xx_base(std::move, s.lhs, s.rhs); return ret; }

template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_bi s){                 int2loc(s.val); DEF_slice_xx_base(std::move, (uint)0,      s.val); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_bu s){                                 DEF_slice_xx_base(std::move, (uint)0,      s.val); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_bs s){                                 DEF_slice_xx_base(std::move, (uint)0,      s.val); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_ie s){ int2loc(s.val);                 DEF_slice_xx_base(std::move,   s.val, vec.size()); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_ue s){                                 DEF_slice_xx_base(std::move,   s.val, vec.size()); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_se s){                                 DEF_slice_xx_base(std::move,   s.val, vec.size()); return ret; }
template <typename T> inline std::vector<T> operator&&(      std::vector<T>& vec, sstd_vecSc::slice_mv_be s){                                 DEF_slice_xx_base(std::move, (uint)0, vec.size()); return ret; }

#undef DEF_slice_u_index_base
#undef DEF_slice_i_index_base
#undef DEF_slice_xx_base
#undef DEF_slice_x_base
#undef int2len

//-----------------------------------------------------------------------------------------------------------------------------------------------
