#pragma once
#include "../itr.hpp" // definition of sstd::begin() and sstd::end()

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd_vecSc{
	struct slice_ii;
	struct slice_iu;
	struct slice_ui;
	struct slice_uu;
	
	struct slice_bi;
	struct slice_bu;
	struct slice_ie;
	struct slice_ue;
	struct slice_be;
}
#define DEF_slice_xx(structName, lhsType, rhsType)			\
private:													\
public:														\
	lhsType lhs;											\
	rhsType rhs;											\
	structName(lhsType lhs_in, rhsType rhs_in){ lhs=lhs_in; rhs=rhs_in; }	\
	~structName(){}
struct sstd_vecSc::slice_ii{ DEF_slice_xx(slice_ii,  int,  int); };
struct sstd_vecSc::slice_iu{ DEF_slice_xx(slice_iu,  int, uint); };
struct sstd_vecSc::slice_ui{ DEF_slice_xx(slice_ui, uint,  int); };
struct sstd_vecSc::slice_uu{ DEF_slice_xx(slice_uu, uint, uint); };
#undef DEF_slice_xx

#define DEF_slice_be(structName, type)						\
private:													\
public:														\
	type val;												\
	structName(type val_in){ val=val_in; }					\
	~structName(){}
struct sstd_vecSc::slice_bi{ DEF_slice_be(slice_bi,  int); };
struct sstd_vecSc::slice_bu{ DEF_slice_be(slice_bu, uint); };
struct sstd_vecSc::slice_ie{ DEF_slice_be(slice_ie,  int); };
struct sstd_vecSc::slice_ue{ DEF_slice_be(slice_ue, uint); };
#undef DEF_slice_be

#define DEF_slice_be_none(structName)					\
private:												\
public:													\
	structName(){}										\
	~structName(){}
struct sstd_vecSc::slice_be{ DEF_slice_be_none(slice_be); };
#undef DEF_slice_be_none

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
//	sstd_vecSc::slice slice(const         int rhs);
//	sstd_vecSc::slice slice(const        uint rhs);
	
	sstd_vecSc::slice_ii slice(const         int lhs, const       int rhs){ return sstd_vecSc::slice_ii(lhs, rhs); }
	sstd_vecSc::slice_iu slice(const         int lhs, const      uint rhs){ return sstd_vecSc::slice_iu(lhs, rhs); }
	sstd_vecSc::slice_ui slice(const        uint lhs, const       int rhs){ return sstd_vecSc::slice_ui(lhs, rhs); }
	sstd_vecSc::slice_uu slice(const        uint lhs, const      uint rhs){ return sstd_vecSc::slice_uu(lhs, rhs); }
	
	//*
	sstd_vecSc::slice_bi slice(const sstd::begin lhs, const       int rhs){ return sstd_vecSc::slice_bi(rhs); }
	sstd_vecSc::slice_bu slice(const sstd::begin lhs, const      uint rhs){ return sstd_vecSc::slice_bu(rhs); }
	sstd_vecSc::slice_ie slice(const         int lhs, const sstd::end rhs){ return sstd_vecSc::slice_ie(lhs); }
	sstd_vecSc::slice_ue slice(const        uint lhs, const sstd::end rhs){ return sstd_vecSc::slice_ue(lhs); }
	sstd_vecSc::slice_be slice(const sstd::begin lhs, const sstd::end rhs){ return sstd_vecSc::slice_be();    }
	//*/
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define int2loc(i) /* integer2location */		\
	if(i<0){ i+=(int)vec.size(); }
#define DEF_slice_xx_base(lhsLen, rhsLen)								\
	std::vector<T> ret((uint)rhsLen-(uint)lhsLen);						\
	for(uint r=0, i=(uint)lhsLen; i<(uint)rhsLen; r++,i++){	ret[r] = vec[i]; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_ii s){ int2loc(s.lhs); int2loc(s.rhs); DEF_slice_xx_base(s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_iu s){ int2loc(s.lhs);                 DEF_slice_xx_base(s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_ui s){                 int2loc(s.rhs); DEF_slice_xx_base(s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_uu s){                                 DEF_slice_xx_base(s.lhs, s.rhs); return ret; }
#undef DEF_slice_xx_base
#undef int2len

//---

#define int2loc(i) /* integer2location */		\
	if(i<0){ i+=(int)vec.size(); }
#define DEF_slice_be_base(lhsLen, rhsLen)								\
	std::vector<T> ret((uint)rhsLen-(uint)lhsLen);						\
	for(uint r=0, i=(uint)lhsLen; i<(uint)rhsLen; r++,i++){	ret[r] = vec[i]; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_bi s){ DEF_slice_be_base((uint)0,      s.val); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_bu s){ DEF_slice_be_base((uint)0,      s.val); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_ie s){ DEF_slice_be_base(  s.val,    (uint)0); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_ue s){ DEF_slice_be_base(  s.val,    (uint)0); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, sstd_vecSc::slice_be s){ DEF_slice_be_base((uint)0, vec.size()); return ret; }
#undef DEF_slice_be_base
#undef int2len


/*
template <typename T> inline std::vector<T> operator&&(std::vector<T>& lhs, const sstd_vecSc::slice_mv    rhs){ return Func<T>(lhs, rhs); }
template <typename T> inline std::vector<T> operator&&(std::vector<T>& lhs, const sstd_vecSc::slice_mv_b  rhs){ return Func<T>(lhs, rhs); }
template <typename T> inline std::vector<T> operator&&(std::vector<T>& lhs, const sstd_vecSc::slice_mv_e  rhs){ return Func<T>(lhs, rhs); }
template <typename T> inline std::vector<T> operator&&(std::vector<T>& lhs, const sstd_vecSc::slice_mv_be rhs){ return Func<T>(lhs, rhs); }
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------------------------------




