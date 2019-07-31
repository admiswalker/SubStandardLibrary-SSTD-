#pragma once
//#include "../itr.hpp" // definition of sstd::begin() and sstd::end()

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd_vecSc{
	struct slice_ii;
	struct slice_iu;
	struct slice_ui;
	struct slice_uu;
}
#define DEF_slice_xx(structName, lhsType, rhsType)						\
private:													\
	lhsType lhs;											\
	rhsType rhs;											\
public:														\
	structName(int64 lhs_in, int64 rhs_in){ lhs=lhs_in; rhs=rhs_in; }	\
	~structName(){}
struct sstd_vecSc::slice_ii{ DEF_slice_xx(slice_ii,  int,  int); };
struct sstd_vecSc::slice_iu{ DEF_slice_xx(slice_iu,  int, uint); };
struct sstd_vecSc::slice_ui{ DEF_slice_xx(slice_ui, uint,  int); };
struct sstd_vecSc::slice_uu{ DEF_slice_xx(slice_uu, uint, uint); };
#undef DEF_slice_xx

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
//	sstd_vecSc::slice slice(const         int rhs);
//	sstd_vecSc::slice slice(const        uint rhs);
	
	sstd_vecSc::slice_ii slice(const         int lhs, const       int rhs){ return sstd_vecSc::slice_ii(lhs, rhs); }
	sstd_vecSc::slice_iu slice(const         int lhs, const      uint rhs){ return sstd_vecSc::slice_iu(lhs, rhs); }
	sstd_vecSc::slice_ui slice(const        uint lhs, const       int rhs){ return sstd_vecSc::slice_ui(lhs, rhs); }
	sstd_vecSc::slice_uu slice(const        uint lhs, const      uint rhs){ return sstd_vecSc::slice_uu(lhs, rhs); }
	
	/*
	sstd_vecSc::slice_b  slice(const sstd::being lhs, const       int rhs);
	sstd_vecSc::slice_b  slice(const sstd::being lhs, const      uint rhs);
	sstd_vecSc::slice_e  slice(const         int lhs, const sstd::end rhs);
	sstd_vecSc::slice_e  slice(const        uint lhs, const sstd::end rhs);
	sstd_vecSc::slice_be slice(const sstd::being lhs, const sstd::end rhs);
	//*/
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
/*
class sstd::slice{
private:
	uint begin;
	uint end;
public:
	slice(){}
	slice(uint begin, uint end){}
	~slice(){}
};
//*/

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define int2len(i)								\
	if(i<0){ i+=typeof(i)vec.size(); }
#define DEF_slice_xx_base(lhsLen, rhsLen)								\
	std::vector<T> ret((uint)rhsLen-(uint)lhsLen);						\
	for(uint r=0, i=(uint)lhsLen; i<(uint)rhsLen; r++,i++){	ret[r] = vec[i]; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, const sstd_vecSc::slice_ii s){ int2len(s.lhs); int2len(s.rhs); DEF_slice_xx_base(s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, const sstd_vecSc::slice_iu s){ int2len(s.lhs);                 DEF_slice_xx_base(s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, const sstd_vecSc::slice_ui s){                 int2len(s.rhs); DEF_slice_xx_base(s.lhs, s.rhs); return ret; }
template <typename T> inline std::vector<T> operator&&(const std::vector<T>& vec, const sstd_vecSc::slice_uu s){                                 DEF_slice_xx_base(s.lhs, s.rhs); return ret; }
#undef DEF_slice_xx_base
#undef int2len

//template <typename T> inline std::vector<T> operator&&(const std::vector<T>& lhs, const sstd_vecSc::slice    rhs){ return Func<T>(lhs, rhs); }
//template <typename T> inline std::vector<T> operator&&(const std::vector<T>& lhs, const sstd_vecSc::slice_b  rhs){ return Func<T>(lhs, rhs); }
//template <typename T> inline std::vector<T> operator&&(const std::vector<T>& lhs, const sstd_vecSc::slice_e  rhs){ return Func<T>(lhs, rhs); }
//template <typename T> inline std::vector<T> operator&&(const std::vector<T>& lhs, const sstd_vecSc::slice_be rhs){ return Func<T>(lhs, rhs); }
/*
template <typename T> inline std::vector<T> operator&&(std::vector<T>& lhs, const sstd_vecSc::slice_mv    rhs){ return Func<T>(lhs, rhs); }
template <typename T> inline std::vector<T> operator&&(std::vector<T>& lhs, const sstd_vecSc::slice_mv_b  rhs){ return Func<T>(lhs, rhs); }
template <typename T> inline std::vector<T> operator&&(std::vector<T>& lhs, const sstd_vecSc::slice_mv_e  rhs){ return Func<T>(lhs, rhs); }
template <typename T> inline std::vector<T> operator&&(std::vector<T>& lhs, const sstd_vecSc::slice_mv_be rhs){ return Func<T>(lhs, rhs); }
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------

	/*
	sstd::slice_slice slice(const         int rhs);
	sstd::slice_slice slice(const        uint rhs);
	
	sstd::slice_slice slice(const         int lhs, const       int rhs);
	sstd::slice_slice slice(const         int lhs, const      uint rhs);
	sstd::slice_slice slice(const        uint lhs, const       int rhs);
	sstd::slice_slice slice(const        uint lhs, const      uint rhs);
	//*/
	/*
	sstd::slice_slice slice(const sstd::being lhs, const       int rhs);
	sstd::slice_slice slice(const sstd::being lhs, const      uint rhs);
	sstd::slice_slice slice(const         int lhs, const sstd::end rhs);
	sstd::slice_slice slice(const        uint lhs, const sstd::end rhs);
	sstd::slice_slice slice(const sstd::being lhs, const sstd::end rhs);
	//*/
	/*
	sstd::slice_slice_mv slice_mv(const         int rhs);
	sstd::slice_slice_mv slice_mv(const        uint rhs);
	
	sstd::slice_slice_mv slice_mv(const         int lhs, const       int rhs);
	sstd::slice_slice_mv slice_mv(const         int lhs, const      uint rhs);
	sstd::slice_slice_mv slice_mv(const        uint lhs, const       int rhs);
	sstd::slice_slice_mv slice_mv(const        uint lhs, const      uint rhs);
	
	sstd::slice_slice_mv slice_mv(const sstd::being lhs, const       int rhs);
	sstd::slice_slice_mv slice_mv(const sstd::being lhs, const      uint rhs);
	sstd::slice_slice_mv slice_mv(const         int lhs, const sstd::end rhs);
	sstd::slice_slice_mv slice_mv(const        uint lhs, const sstd::end rhs);
	sstd::slice_slice_mv slice_mv(const sstd::being lhs, const sstd::end rhs);
	//*/

/*
template <typename T>
inline std::vector<T> operator [](std::vector<T>& rhs, sstd::slice_slice lhs){
//inline std::vector<T> operator +(std::vector<T>& rhs, sstd::slice_slice lhs){
//std::vector<T> operator[](std::vector<T> rhs, sstd::slice_slice lhs){
//inline std::vector<T> sstd::operator[](const sstd::slice_slice& rhs){
//inline std::vector<T> operator[](const sstd::slice_slice& rhs){
//	for(uint p=0; p<rhs.size(); p++){ rhs[p]--; }
	return std::vector<T>();
}//*/

/*
template <typename T>
inline std::vector<T> operator[](const sstd::slice_slice& rhs){
//	for(uint p=0; p<rhs.size(); p++){ rhs[p]--; }
//	return rhs;
}//*/

// まずは，演算子が呼び出せるところまで実装して，様子を伺う．

//-----------------------------------------------------------------------------------------------------------------------------------------------




