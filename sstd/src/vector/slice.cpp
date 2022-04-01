#include "slice.hpp"


sstd_vecSc::slice_i  sstd::slice(const         int val){ return sstd_vecSc::slice_i(val); }
sstd_vecSc::slice_u  sstd::slice(const        uint val){ return sstd_vecSc::slice_u(val); }
sstd_vecSc::slice_s  sstd::slice(const      size_t val){ return sstd_vecSc::slice_s(val); }
sstd_vecSc::slice_b  sstd::slice(const sstd::begin val){ return sstd_vecSc::slice_b();    }
sstd_vecSc::slice_e  sstd::slice(const sstd::end   val){ return sstd_vecSc::slice_e();    }
sstd_vecSc::slice_vi sstd::slice(const std::vector< int>& val){ return sstd_vecSc::slice_vi(val); }
sstd_vecSc::slice_vu sstd::slice(const std::vector<uint>& val){ return sstd_vecSc::slice_vu(val); }
    
sstd_vecSc::slice_ii sstd::slice(const         int lhs, const       int rhs){ return sstd_vecSc::slice_ii(lhs, rhs); }
sstd_vecSc::slice_iu sstd::slice(const         int lhs, const      uint rhs){ return sstd_vecSc::slice_iu(lhs, rhs); }
sstd_vecSc::slice_is sstd::slice(const         int lhs, const    size_t rhs){ return sstd_vecSc::slice_is(lhs, rhs); }
sstd_vecSc::slice_ui sstd::slice(const        uint lhs, const       int rhs){ return sstd_vecSc::slice_ui(lhs, rhs); }
sstd_vecSc::slice_uu sstd::slice(const        uint lhs, const      uint rhs){ return sstd_vecSc::slice_uu(lhs, rhs); }
sstd_vecSc::slice_us sstd::slice(const        uint lhs, const    size_t rhs){ return sstd_vecSc::slice_us(lhs, rhs); }
sstd_vecSc::slice_si sstd::slice(const      size_t lhs, const       int rhs){ return sstd_vecSc::slice_si(lhs, rhs); }
sstd_vecSc::slice_su sstd::slice(const      size_t lhs, const      uint rhs){ return sstd_vecSc::slice_su(lhs, rhs); }
sstd_vecSc::slice_ss sstd::slice(const      size_t lhs, const    size_t rhs){ return sstd_vecSc::slice_ss(lhs, rhs); }
    
sstd_vecSc::slice_bi sstd::slice(const sstd::begin lhs, const       int rhs){ return sstd_vecSc::slice_bi(rhs); }
sstd_vecSc::slice_bu sstd::slice(const sstd::begin lhs, const      uint rhs){ return sstd_vecSc::slice_bu(rhs); }
sstd_vecSc::slice_bs sstd::slice(const sstd::begin lhs, const    size_t rhs){ return sstd_vecSc::slice_bs(rhs); }
sstd_vecSc::slice_ie sstd::slice(const         int lhs, const sstd::end rhs){ return sstd_vecSc::slice_ie(lhs); }
sstd_vecSc::slice_ue sstd::slice(const        uint lhs, const sstd::end rhs){ return sstd_vecSc::slice_ue(lhs); }
sstd_vecSc::slice_se sstd::slice(const      size_t lhs, const sstd::end rhs){ return sstd_vecSc::slice_se(lhs); }
sstd_vecSc::slice_be sstd::slice(const sstd::begin lhs, const sstd::end rhs){ return sstd_vecSc::slice_be();    }
    
//---
    
sstd_vecSc::slice_mv_i  sstd::slice_mv(const         int val){ return sstd_vecSc::slice_mv_i(val); }
sstd_vecSc::slice_mv_u  sstd::slice_mv(const        uint val){ return sstd_vecSc::slice_mv_u(val); }
sstd_vecSc::slice_mv_s  sstd::slice_mv(const      size_t val){ return sstd_vecSc::slice_mv_s(val); }
sstd_vecSc::slice_mv_b  sstd::slice_mv(const sstd::begin val){ return sstd_vecSc::slice_mv_b();    }
sstd_vecSc::slice_mv_e  sstd::slice_mv(const sstd::end   val){ return sstd_vecSc::slice_mv_e();    }
sstd_vecSc::slice_mv_vi sstd::slice_mv(const std::vector< int>& val){ return sstd_vecSc::slice_mv_vi(val); }
sstd_vecSc::slice_mv_vu sstd::slice_mv(const std::vector<uint>& val){ return sstd_vecSc::slice_mv_vu(val); }
    
sstd_vecSc::slice_mv_ii sstd::slice_mv(const         int lhs, const       int rhs){ return sstd_vecSc::slice_mv_ii(lhs, rhs); }
sstd_vecSc::slice_mv_iu sstd::slice_mv(const         int lhs, const      uint rhs){ return sstd_vecSc::slice_mv_iu(lhs, rhs); }
sstd_vecSc::slice_mv_is sstd::slice_mv(const         int lhs, const    size_t rhs){ return sstd_vecSc::slice_mv_is(lhs, rhs); }
sstd_vecSc::slice_mv_ui sstd::slice_mv(const        uint lhs, const       int rhs){ return sstd_vecSc::slice_mv_ui(lhs, rhs); }
sstd_vecSc::slice_mv_uu sstd::slice_mv(const        uint lhs, const      uint rhs){ return sstd_vecSc::slice_mv_uu(lhs, rhs); }
sstd_vecSc::slice_mv_us sstd::slice_mv(const        uint lhs, const    size_t rhs){ return sstd_vecSc::slice_mv_us(lhs, rhs); }
sstd_vecSc::slice_mv_si sstd::slice_mv(const      size_t lhs, const       int rhs){ return sstd_vecSc::slice_mv_si(lhs, rhs); }
sstd_vecSc::slice_mv_su sstd::slice_mv(const      size_t lhs, const      uint rhs){ return sstd_vecSc::slice_mv_su(lhs, rhs); }
sstd_vecSc::slice_mv_ss sstd::slice_mv(const      size_t lhs, const    size_t rhs){ return sstd_vecSc::slice_mv_ss(lhs, rhs); }
    
sstd_vecSc::slice_mv_bi sstd::slice_mv(const sstd::begin lhs, const       int rhs){ return sstd_vecSc::slice_mv_bi(rhs); }
sstd_vecSc::slice_mv_bu sstd::slice_mv(const sstd::begin lhs, const      uint rhs){ return sstd_vecSc::slice_mv_bu(rhs); }
sstd_vecSc::slice_mv_bs sstd::slice_mv(const sstd::begin lhs, const    size_t rhs){ return sstd_vecSc::slice_mv_bs(rhs); }
sstd_vecSc::slice_mv_ie sstd::slice_mv(const         int lhs, const sstd::end rhs){ return sstd_vecSc::slice_mv_ie(lhs); }
sstd_vecSc::slice_mv_ue sstd::slice_mv(const        uint lhs, const sstd::end rhs){ return sstd_vecSc::slice_mv_ue(lhs); }
sstd_vecSc::slice_mv_se sstd::slice_mv(const      size_t lhs, const sstd::end rhs){ return sstd_vecSc::slice_mv_se(lhs); }
sstd_vecSc::slice_mv_be sstd::slice_mv(const sstd::begin lhs, const sstd::end rhs){ return sstd_vecSc::slice_mv_be();    }
