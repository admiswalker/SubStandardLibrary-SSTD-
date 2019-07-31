#pragma once
//#include "../itr.hpp" // definition of sstd::begin() and sstd::end()

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd_vecRg{
	struct range_ii;
	struct range_iu;
	struct range_ui;
	struct range_uu;
}
#define DEF_range_xx(structName, lhsType, rhsType)						\
private:													\
	lhsType lhs;											\
	rhsType rhs;											\
public:														\
	structName(int64 lhs_in, int64 rhs_in){ lhs=lhs_in; rhs=rhs_in; }	\
	~structName(){}
struct sstd_vecRg::range_ii{ DEF_range_xx(range_ii,  int,  int); };
struct sstd_vecRg::range_iu{ DEF_range_xx(range_iu,  int, uint); };
struct sstd_vecRg::range_ui{ DEF_range_xx(range_ui, uint,  int); };
struct sstd_vecRg::range_uu{ DEF_range_xx(range_uu, uint, uint); };
#undef DEF_range_xx

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
//	sstd_vecRg::range range(const         int rhs);
//	sstd_vecRg::range range(const        uint rhs);
	
	sstd_vecRg::range_ii range(const         int lhs, const       int rhs){ return sstd_vecRg::range_ii(lhs, rhs); }
	sstd_vecRg::range_iu range(const         int lhs, const      uint rhs){ return sstd_vecRg::range_iu(lhs, rhs); }
	sstd_vecRg::range_ui range(const        uint lhs, const       int rhs){ return sstd_vecRg::range_ui(lhs, rhs); }
	sstd_vecRg::range_uu range(const        uint lhs, const      uint rhs){ return sstd_vecRg::range_uu(lhs, rhs); }
	
	/*
	sstd_vecRg::range_b  range(const sstd::being lhs, const       int rhs);
	sstd_vecRg::range_b  range(const sstd::being lhs, const      uint rhs);
	sstd_vecRg::range_e  range(const         int lhs, const sstd::end rhs);
	sstd_vecRg::range_e  range(const        uint lhs, const sstd::end rhs);
	sstd_vecRg::range_be range(const sstd::being lhs, const sstd::end rhs);
	//*/
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
/*
class sstd::range{
private:
	uint begin;
	uint end;
public:
	range(){}
	range(uint begin, uint end){}
	~range(){}
};
//*/

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define int2len(i)										\
	if(i<0){
}else{
	
 }

#define DEF_range_xx_base(lhsLen, rhsLen)		\
	;


template <typename T> inline std::vector<T> operator&&(const std::vector<T>& lhs, const sstd_vecRg::range_ii rg){ uint l,r; DEF_range_xx_base(rg.lhs, rg.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& lhs, const sstd_vecRg::range_iu rg){ uint l  ; DEF_range_xx_base(l     , rg.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& lhs, const sstd_vecRg::range_ui rg){ uint   r; DEF_range_xx_base(rg.lhs, r     ); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& lhs, const sstd_vecRg::range_uu rg){           DEF_range_xx_base(rg.lhs, rg.rhs); return ret; }



//template <typename T> inline std::vector<T> operator&&(const std::vector<T>& lhs, const sstd_vecRg::range    rhs){ return Func<T>(lhs, rhs); }
//template <typename T> inline std::vector<T> operator&&(const std::vector<T>& lhs, const sstd_vecRg::range_b  rhs){ return Func<T>(lhs, rhs); }
//template <typename T> inline std::vector<T> operator&&(const std::vector<T>& lhs, const sstd_vecRg::range_e  rhs){ return Func<T>(lhs, rhs); }
//template <typename T> inline std::vector<T> operator&&(const std::vector<T>& lhs, const sstd_vecRg::range_be rhs){ return Func<T>(lhs, rhs); }
/*
template <typename T> inline std::vector<T> operator&&(std::vector<T>& lhs, const sstd_vecRg::range_mv    rhs){ return Func<T>(lhs, rhs); }
template <typename T> inline std::vector<T> operator&&(std::vector<T>& lhs, const sstd_vecRg::range_mv_b  rhs){ return Func<T>(lhs, rhs); }
template <typename T> inline std::vector<T> operator&&(std::vector<T>& lhs, const sstd_vecRg::range_mv_e  rhs){ return Func<T>(lhs, rhs); }
template <typename T> inline std::vector<T> operator&&(std::vector<T>& lhs, const sstd_vecRg::range_mv_be rhs){ return Func<T>(lhs, rhs); }
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------

	/*
	sstd::slice_range slice(const         int rhs);
	sstd::slice_range slice(const        uint rhs);
	
	sstd::slice_range slice(const         int lhs, const       int rhs);
	sstd::slice_range slice(const         int lhs, const      uint rhs);
	sstd::slice_range slice(const        uint lhs, const       int rhs);
	sstd::slice_range slice(const        uint lhs, const      uint rhs);
	//*/
	/*
	sstd::slice_range slice(const sstd::being lhs, const       int rhs);
	sstd::slice_range slice(const sstd::being lhs, const      uint rhs);
	sstd::slice_range slice(const         int lhs, const sstd::end rhs);
	sstd::slice_range slice(const        uint lhs, const sstd::end rhs);
	sstd::slice_range slice(const sstd::being lhs, const sstd::end rhs);
	//*/
	/*
	sstd::slice_range_mv slice_mv(const         int rhs);
	sstd::slice_range_mv slice_mv(const        uint rhs);
	
	sstd::slice_range_mv slice_mv(const         int lhs, const       int rhs);
	sstd::slice_range_mv slice_mv(const         int lhs, const      uint rhs);
	sstd::slice_range_mv slice_mv(const        uint lhs, const       int rhs);
	sstd::slice_range_mv slice_mv(const        uint lhs, const      uint rhs);
	
	sstd::slice_range_mv slice_mv(const sstd::being lhs, const       int rhs);
	sstd::slice_range_mv slice_mv(const sstd::being lhs, const      uint rhs);
	sstd::slice_range_mv slice_mv(const         int lhs, const sstd::end rhs);
	sstd::slice_range_mv slice_mv(const        uint lhs, const sstd::end rhs);
	sstd::slice_range_mv slice_mv(const sstd::being lhs, const sstd::end rhs);
	//*/

/*
template <typename T>
inline std::vector<T> operator [](std::vector<T>& rhs, sstd::slice_range lhs){
//inline std::vector<T> operator +(std::vector<T>& rhs, sstd::slice_range lhs){
//std::vector<T> operator[](std::vector<T> rhs, sstd::slice_range lhs){
//inline std::vector<T> sstd::operator[](const sstd::slice_range& rhs){
//inline std::vector<T> operator[](const sstd::slice_range& rhs){
//	for(uint p=0; p<rhs.size(); p++){ rhs[p]--; }
	return std::vector<T>();
}//*/

/*
template <typename T>
inline std::vector<T> operator[](const sstd::slice_range& rhs){
//	for(uint p=0; p<rhs.size(); p++){ rhs[p]--; }
//	return rhs;
}//*/

// まずは，演算子が呼び出せるところまで実装して，様子を伺う．

//-----------------------------------------------------------------------------------------------------------------------------------------------




