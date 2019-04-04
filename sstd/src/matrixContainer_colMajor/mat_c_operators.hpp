#pragma once

#include "./mat_c.hpp"
#include "./mat_c_elements.hpp" // for element operations (elements multiplication)
#include "../math.hpp"
#include "../pdbg.hpp"
#include "../typeDef.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
	// #include "./mat.hpp"
	template <typename T>
	extern void eye(sstd::mat_c<T>& rhs);
	
	// #include "../math.hpp"
	extern uint8  pow(const uint8 & base, const uint8 & exp);
	extern uint16 pow(const uint16& base, const uint16& exp);
	extern uint32 pow(const uint32& base, const uint32& exp);
	extern uint64 pow(const uint64& base, const uint64& exp);
	extern  float pow(const  float& base, const  float& exp);
	extern double pow(const double& base, const double& exp);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
	// Operators for linearAlgebra
	template <typename T>                   sstd::mat_c<T> add  (const sstd::mat_c<T>& lhs, const sstd::mat_c<T>& rhs);
	template <typename T, typename rhsType> sstd::mat_c<T> add  (const sstd::mat_c<T>& lhs, const      rhsType& rhs);
	template <typename T, typename lhsType> sstd::mat_c<T> add  (const      lhsType& lhs, const sstd::mat_c<T>& rhs);
	template <typename T>                   sstd::mat_c<T> add_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c_elements<T>& rhs);
	template <typename T>                   sstd::mat_c<T> add_e(const sstd::mat_c         <T>& lhs, const sstd::mat_c_elements<T>& rhs);
	template <typename T>                   sstd::mat_c<T> add_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c         <T>& rhs);
	
	template <typename T>                   sstd::mat_c<T> sub  (const sstd::mat_c<T>& lhs, const sstd::mat_c<T>& rhs);
	template <typename T, typename rhsType> sstd::mat_c<T> sub  (const sstd::mat_c<T>& lhs, const      rhsType& rhs);
	template <typename T, typename lhsType> sstd::mat_c<T> sub  (const      lhsType& lhs, const sstd::mat_c<T>& rhs);
	template <typename T>                   sstd::mat_c<T> sub_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c_elements<T>& rhs);
	template <typename T>                   sstd::mat_c<T> sub_e(const sstd::mat_c         <T>& lhs, const sstd::mat_c_elements<T>& rhs);
	template <typename T>                   sstd::mat_c<T> sub_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c         <T>& rhs);
	
	template <typename T>                   sstd::mat_c<T> mul  (const sstd::mat_c<T>& lhs, const sstd::mat_c<T>& rhs);
	template <typename T, typename rhsType> sstd::mat_c<T> mul  (const sstd::mat_c<T>& lhs, const      rhsType& rhs);
	template <typename T, typename lhsType> sstd::mat_c<T> mul  (const      lhsType& lhs, const sstd::mat_c<T>& rhs);
	template <typename T>                   sstd::mat_c<T> mul_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c_elements<T>& rhs);
	template <typename T>                   sstd::mat_c<T> mul_e(const sstd::mat_c         <T>& lhs, const sstd::mat_c_elements<T>& rhs);
	template <typename T>                   sstd::mat_c<T> mul_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c         <T>& rhs);
	
	template <typename T>                   sstd::mat_c<T> div  (const sstd::mat_c<T>& lhs, const sstd::mat_c<T>& rhs);
	template <typename T>                   sstd::mat_c<T> div_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c_elements<T>& rhs);
	template <typename T>                   sstd::mat_c<T> div_e(const sstd::mat_c         <T>& lhs, const sstd::mat_c_elements<T>& rhs);
	template <typename T>                   sstd::mat_c<T> div_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c         <T>& rhs);
	
	template <typename T>                   sstd::mat_c<T> mod  (const sstd::mat_c<T>& lhs, const sstd::mat_c<T>& rhs);
	template <typename T, typename rhsType> sstd::mat_c<T> mod  (const sstd::mat_c<T>& lhs, const      rhsType& rhs);
	template <typename T, typename lhsType> sstd::mat_c<T> mod  (const      lhsType& lhs, const sstd::mat_c<T>& rhs);
	template <typename T>                   sstd::mat_c<T> mod_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c_elements<T>& rhs);
	template <typename T>                   sstd::mat_c<T> mod_e(const sstd::mat_c         <T>& lhs, const sstd::mat_c_elements<T>& rhs);
	template <typename T>                   sstd::mat_c<T> mod_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c         <T>& rhs);
	
//	template <typename T> sstd::mat_c<T> pow  (const sstd::mat_c<T>& lhs, const sstd::mat_c<T>& rhs); // 定義されるのか不明 (行列指数関数? -> sciLab 等で実験してみるのがよい)
	template <typename T>                   sstd::mat_c<T> pow  (const sstd::mat_c<T>& lhs, const        char& rhs); // テンプレートの部分特殊化が可能なのはクラステンプレートのみである。関数テンプレートは部分特殊化できず、明示的特殊化のみ可能である。しかし多くの場合、関数テンプレートの部分特殊化は多重定義によって代用できる。(Ref: https://ja.wikipedia.org/wiki/%E3%83%86%E3%83%B3%E3%83%97%E3%83%AC%E3%83%BC%E3%83%88%E3%81%AE%E9%83%A8%E5%88%86%E7%89%B9%E6%AE%8A%E5%8C%96)
	template <typename T>                   sstd::mat_c<T> pow  (const sstd::mat_c<T>& lhs, const       int8 & rhs);
	template <typename T>                   sstd::mat_c<T> pow  (const sstd::mat_c<T>& lhs, const       int16& rhs);
	template <typename T>                   sstd::mat_c<T> pow  (const sstd::mat_c<T>& lhs, const       int32& rhs);
	template <typename T>                   sstd::mat_c<T> pow  (const sstd::mat_c<T>& lhs, const       int64& rhs);
	template <typename T>                   sstd::mat_c<T> pow  (const sstd::mat_c<T>& lhs, const      uint8 & rhs);
	template <typename T>                   sstd::mat_c<T> pow  (const sstd::mat_c<T>& lhs, const      uint16& rhs);
	template <typename T>                   sstd::mat_c<T> pow  (const sstd::mat_c<T>& lhs, const      uint32& rhs);
	template <typename T>                   sstd::mat_c<T> pow  (const sstd::mat_c<T>& lhs, const      uint64& rhs);
	template <typename T>                   sstd::mat_c<T> pow  (const sstd::mat_c<T>& lhs, const       float& rhs);
	template <typename T>                   sstd::mat_c<T> pow  (const sstd::mat_c<T>& lhs, const      double& rhs);
	template <typename T>                   sstd::mat_c<T> pow_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c_elements<T>& rhs);
	template <typename T>                   sstd::mat_c<T> pow_e(const sstd::mat_c         <T>& lhs, const sstd::mat_c_elements<T>& rhs);
	template <typename T>                   sstd::mat_c<T> pow_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c         <T>& rhs);
	
	// Relational operators
	template <typename T>                   bool eq  (const sstd::mat_c<T>& lhs, const sstd::mat_c<T>& rhs);
	template <typename T, typename rhsType> bool eq  (const sstd::mat_c<T>& lhs, const      rhsType& rhs);
	template <typename T, typename lhsType> bool eq  (const      lhsType& lhs, const sstd::mat_c<T>& rhs);
	template <typename T>                   bool eq_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c_elements<T>& rhs);
	template <typename T>                   bool eq_e(const sstd::mat_c         <T>& lhs, const sstd::mat_c_elements<T>& rhs);
	template <typename T>                   bool eq_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c         <T>& rhs);
	
	template <typename T>                   bool ne  (const sstd::mat_c<T>& lhs, const sstd::mat_c<T>& rhs);
	template <typename T, typename rhsType> bool ne  (const sstd::mat_c<T>& lhs, const      rhsType& rhs);
	template <typename T, typename lhsType> bool ne  (const      lhsType& lhs, const sstd::mat_c<T>& rhs);
	template <typename T>                   bool ne_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c_elements<T>& rhs);
	template <typename T>                   bool ne_e(const sstd::mat_c         <T>& lhs, const sstd::mat_c_elements<T>& rhs);
	template <typename T>                   bool ne_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c         <T>& rhs);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

// Operators for linearAlgebra

#define SSTD_DEF_mat_o(Func, Ope)										\
	template <typename T>												\
	inline sstd::mat_c<T> Func(const sstd::mat_c<T>& lhs, const sstd::mat_c<T>& rhs){ \
		sstd::mat_c<T> ret(lhs.rows(), lhs.cols());						\
		for(uint p=0; p<ret.size(); p++){ ret[p]=lhs[p] Ope rhs[p]; }	\
		return ret;														\
	}																	\
	template <typename T, typename rhsType>								\
	inline sstd::mat_c<T> Func(const sstd::mat_c<T>& lhs, const rhsType& rhs){ \
		sstd::mat_c<T> ret(lhs.rows(), lhs.cols());						\
		for(uint p=0; p<ret.size(); p++){ ret[p]=lhs[p] Ope rhs; }		\
		return ret;														\
	}																	\
	template <typename T, typename rhsType>								\
	inline sstd::mat_c<T> Func(const rhsType& lhs, const sstd::mat_c<T>& rhs){ \
		sstd::mat_c<T> ret(rhs.rows(), rhs.cols());						\
		for(uint p=0; p<ret.size(); p++){ ret[p]=lhs Ope rhs[p]; }		\
		return ret;														\
	}

//---

#define SSTD_DEF_mat_f(Func, Func2)										\
	template <typename T>												\
	inline sstd::mat_c<T> Func(const sstd::mat_c<T>& lhs, const sstd::mat_c<T>& rhs){ \
		sstd::mat_c<T> ret(lhs.rows(), lhs.cols());						\
		for(uint p=0; p<ret.size(); p++){ ret[p]=Func2(lhs[p], rhs[p]); } \
		return ret;														\
	}																	\
	template <typename T, typename rhsType>								\
	inline sstd::mat_c<T> Func(const sstd::mat_c<T>& lhs, const rhsType& rhs){ \
		sstd::mat_c<T> ret(lhs.rows(), lhs.cols());						\
		for(uint p=0; p<ret.size(); p++){ ret[p]=Func2(lhs[p], rhs); }	\
		return ret;														\
	}																	\
	template <typename T, typename rhsType>								\
	inline sstd::mat_c<T> Func(const rhsType& lhs, const sstd::mat_c<T>& rhs){ \
		sstd::mat_c<T> ret(rhs.rows(), rhs.cols());						\
		for(uint p=0; p<ret.size(); p++){ ret[p]=Func2(lhs, rhs[p]); }	\
		return ret;														\
	}

//---

#define SSTD_DEF_mat_elements_o(Func, Ope)								\
	template <typename T>												\
	inline sstd::mat_c<T> Func(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c_elements<T>& rhs){ \
		sstd::mat_c<T> ret(lhs.rows(), lhs.cols());						\
		for(uint p=0; p<ret.size(); p++){ ret[p]=lhs[p] Ope rhs[p]; }	\
		return ret;														\
	}																	\
	template <typename T>												\
	inline sstd::mat_c<T> Func(const sstd::mat_c<T>& lhs, const sstd::mat_c_elements<T>& rhs){ \
		sstd::mat_c<T> ret(lhs.rows(), lhs.cols());						\
		for(uint p=0; p<ret.size(); p++){ ret[p]=lhs[p] Ope rhs[p]; }	\
		return ret;														\
	}																	\
	template <typename T>												\
	inline sstd::mat_c<T> Func(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c<T>& rhs){ \
		sstd::mat_c<T> ret(rhs.rows(), rhs.cols());						\
		for(uint p=0; p<ret.size(); p++){ ret[p]=lhs[p] Ope rhs[p]; }	\
		return ret;														\
	}

//---

#define SSTD_DEF_mat_elements_f(Func, Func2)								\
	template <typename T>												\
	inline sstd::mat_c<T> Func(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c_elements<T>& rhs){ \
		sstd::mat_c<T> ret(lhs.rows(), lhs.cols());						\
		for(uint p=0; p<ret.size(); p++){ ret[p]=Func2(lhs[p], rhs[p]); } \
		return ret;														\
	}																	\
	template <typename T>												\
	inline sstd::mat_c<T> Func(const sstd::mat_c<T>& lhs, const sstd::mat_c_elements<T>& rhs){ \
		sstd::mat_c<T> ret(lhs.rows(), lhs.cols());						\
		for(uint p=0; p<ret.size(); p++){ ret[p]=Func2(lhs[p], rhs[p]); } \
		return ret;														\
	}																	\
	template <typename T>												\
	inline sstd::mat_c<T> Func(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c<T>& rhs){ \
		sstd::mat_c<T> ret(rhs.rows(), rhs.cols());						\
		for(uint p=0; p<ret.size(); p++){ ret[p]=Func2(lhs[p], rhs[p]); } \
		return ret;														\
	}

//---

// plus
SSTD_DEF_mat_o(sstd::add, +);
SSTD_DEF_mat_elements_o(sstd::add_e, +);

// minus
SSTD_DEF_mat_o(sstd::sub, -);
SSTD_DEF_mat_elements_o(sstd::sub_e, -);

// multiplication
template <typename T>
inline sstd::mat_c<T> sstd::mul(const sstd::mat_c<T>& lhs, const sstd::mat_c<T>& rhs){
	sstd::mat_c<T> ret(lhs.rows(), rhs.cols());
	for(uint q=0; q<ret.cols(); q++){
		for(uint p=0; p<ret.rows(); p++){
			ret(p, q) = lhs(p, 0) * rhs(0, q);
			for(uint i=1; i<lhs.cols(); i++){ ret(p, q) += lhs(p, i) * rhs(i, q); }
		}
	}
	return ret;
//	// 上記のように最適化
//	sstd::mat_c<T> ret(lhs.rows(), rhs.cols());
//	zeros(ret);
//	for(uint q=0; q<ret.cols(); q++){
//		for(uint p=0; p<ret.rows(); p++){
//			for(uint i=0; i<lhs.cols(); i++){ ret(p, q) += lhs(p, i) * rhs(i, q); }
//		}
//	}
//	return ret;
}
template <typename T, typename rhsType>
inline sstd::mat_c<T> sstd::mul(const sstd::mat_c<T>& lhs, const rhsType& rhs){
	sstd::mat_c<T> ret(lhs.rows(), lhs.cols());
	for(uint p=0; p<ret.size(); p++){ ret[p]=lhs[p]*rhs; }
	return ret;
}
template <typename T, typename lhsType>
inline sstd::mat_c<T> sstd::mul(const lhsType& lhs, const sstd::mat_c<T>& rhs){
	sstd::mat_c<T> ret(rhs.rows(), rhs.cols());
	for(uint p=0; p<ret.size(); p++){ ret[p]=lhs*rhs[p]; }
	return ret;
}
SSTD_DEF_mat_elements_o(sstd::mul_e, *);

// division
template <typename T, typename rhsType>
inline sstd::mat_c<T> sstd::div(const sstd::mat_c<T>& lhs, const rhsType& rhs){
	sstd::mat_c<T> ret(lhs.rows(), lhs.cols());
	for(uint p=0; p<ret.size(); p++){ ret[p]=lhs[p]/rhs; }
	return ret;
}
SSTD_DEF_mat_elements_o(sstd::div_e, /);

// modulo
SSTD_DEF_mat_o(sstd::mod, %);
SSTD_DEF_mat_elements_o(sstd::mod_e, %);

// power
template <typename T, typename rhsType>
inline void pow_int_calculation(sstd::mat_c<T>& base, rhsType& exponent){
	for(; exponent>(rhsType)0; exponent>>=1){
		if(exponent & 1){
			if(exponent==(rhsType)1){ return; }
			break;
		}
		base = sstd::mul(base, base);
	}
	sstd::mat_c<T> buf = base;
	buf = sstd::mul(buf, buf);
	exponent>>=1;
	
	for(;;exponent>>=1){
		if(exponent & 1){
			base = sstd::mul(base, buf);
			if(exponent==(rhsType)1){ return; }
		}
		buf = sstd::mul(buf, buf);
	}
}
template <typename T, typename rhsType>
inline sstd::mat_c<T> pow_signedInt(sstd::mat_c<T> base, rhsType exponent){
	if(exponent==(rhsType)0){ sstd::eye(base); return base; }
	if(exponent>=(rhsType)0){ pow_int_calculation(base, exponent);
	}          else         { sstd::pdbg("ERROR: not implemented.\n");     }
	return base;
}
template <typename T> inline sstd::mat_c<T> sstd::pow(const sstd::mat_c<T>& lhs, const  char& rhs){ return pow_signedInt<T, int8 >(lhs, (int8)rhs); }
template <typename T> inline sstd::mat_c<T> sstd::pow(const sstd::mat_c<T>& lhs, const int8 & rhs){ return pow_signedInt<T, int8 >(lhs, rhs); }
template <typename T> inline sstd::mat_c<T> sstd::pow(const sstd::mat_c<T>& lhs, const int16& rhs){ return pow_signedInt<T, int16>(lhs, rhs); }
template <typename T> inline sstd::mat_c<T> sstd::pow(const sstd::mat_c<T>& lhs, const int32& rhs){ return pow_signedInt<T, int32>(lhs, rhs); }
template <typename T> inline sstd::mat_c<T> sstd::pow(const sstd::mat_c<T>& lhs, const int64& rhs){ return pow_signedInt<T, int64>(lhs, rhs); }

template <typename T, typename rhsType>
inline sstd::mat_c<T> pow_unsignedInt(sstd::mat_c<T> base, rhsType exponent){
	if(exponent==(rhsType)0){ sstd::eye(base); return base; }
	pow_int_calculation(base, exponent);
	return base;
}
template <typename T> inline sstd::mat_c<T> sstd::pow(const sstd::mat_c<T>& lhs, const uint8 & rhs){ return pow_unsignedInt<T, uint8 >(lhs, rhs); }
template <typename T> inline sstd::mat_c<T> sstd::pow(const sstd::mat_c<T>& lhs, const uint16& rhs){ return pow_unsignedInt<T, uint16>(lhs, rhs); }
template <typename T> inline sstd::mat_c<T> sstd::pow(const sstd::mat_c<T>& lhs, const uint32& rhs){ return pow_unsignedInt<T, uint32>(lhs, rhs); }
template <typename T> inline sstd::mat_c<T> sstd::pow(const sstd::mat_c<T>& lhs, const uint64& rhs){ return pow_unsignedInt<T, uint64>(lhs, rhs); }

template <typename T> inline sstd::mat_c<T> sstd::pow(const sstd::mat_c<T>& lhs, const  float& rhs){ sstd::pdbg("ERROR: not implemented.\n"); return lhs; }
template <typename T> inline sstd::mat_c<T> sstd::pow(const sstd::mat_c<T>& lhs, const double& rhs){ sstd::pdbg("ERROR: not implemented.\n"); return lhs; }

SSTD_DEF_mat_elements_f(sstd::pow_e, sstd::pow);

//---

#undef SSTD_DEF_mat_o
#undef SSTD_DEF_mat_f
#undef SSTD_DEF_mat_elements_o
#undef SSTD_DEF_mat_elements_f

//---

// Relational operators

#define SSTD_DEF_eq_mm(matL, matR)					\
	if(matL.rows()!=matR.rows()){ return false; }	\
	if(matL.cols()!=matR.cols()){ return false; }	\
													\
	for(uint i=0; i<matL.size(); i++){					\
		if(matL[i]!=matR[i]){ return false; }			\
	}													\
	return true;

#define SSTD_DEF_eq_ms(mat, scalar)					\
	for(uint i=0; i<mat.size(); i++){				\
		if(mat[i]!=scalar){ return false; }			\
	}												\
	return true;

#define SSTD_DEF_eq_sm(scalar, mat)					\
	for(uint i=0; i<mat.size(); i++){				\
		if(mat[i]!=scalar){ return false; }			\
	}												\
	return true;

template <typename T>                   inline bool sstd::eq   (const sstd::mat_c<T>& lhs, const sstd::mat_c<T>& rhs){ SSTD_DEF_eq_mm(lhs, rhs); }
template <typename T, typename rhsType> inline bool sstd::eq   (const sstd::mat_c<T>& lhs, const      rhsType& rhs){ SSTD_DEF_eq_ms(lhs, rhs); }
template <typename T, typename lhsType> inline bool sstd::eq   (const      lhsType& lhs, const sstd::mat_c<T>& rhs){ SSTD_DEF_eq_sm(lhs, rhs); }
template <typename T>                   inline bool sstd::eq_e (const sstd::mat_c_elements<T>& lhs, const sstd::mat_c_elements<T>& rhs){ SSTD_DEF_eq_mm(lhs, rhs); }
template <typename T>                   inline bool sstd::eq_e (const sstd::mat_c         <T>& lhs, const sstd::mat_c_elements<T>& rhs){ SSTD_DEF_eq_mm(lhs, rhs); }
template <typename T>                   inline bool sstd::eq_e (const sstd::mat_c_elements<T>& lhs, const sstd::mat_c         <T>& rhs){ SSTD_DEF_eq_mm(lhs, rhs); }

#undef SSTD_DEF_eq_mm
#undef SSTD_DEF_eq_ms
#undef SSTD_DEF_eq_sm

template <typename T>                   inline bool sstd::ne  (const sstd::mat_c<T>& lhs, const sstd::mat_c<T>& rhs)                  { return !sstd::eq(lhs, rhs); }
template <typename T, typename rhsType> inline bool sstd::ne  (const sstd::mat_c<T>& lhs, const      rhsType& rhs)                  { return !sstd::eq(lhs, rhs); }
template <typename T, typename lhsType> inline bool sstd::ne  (const      lhsType& lhs, const sstd::mat_c<T>& rhs)                  { return !sstd::eq(lhs, rhs); }
template <typename T>                   inline bool sstd::ne_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c_elements<T>& rhs){ return !sstd::eq(lhs, rhs); }
template <typename T>                   inline bool sstd::ne_e(const sstd::mat_c         <T>& lhs, const sstd::mat_c_elements<T>& rhs){ return !sstd::eq(lhs, rhs); }
template <typename T>                   inline bool sstd::ne_e(const sstd::mat_c_elements<T>& lhs, const sstd::mat_c         <T>& rhs){ return !sstd::eq(lhs, rhs); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

// Operators for linearAlgebra

#define SSTD_DEF_mat_Operator(Ret, Array, Ope, Func)						\
	template <typename T>                   inline Ret operator Ope(const Array<T>& lhs, const Array<T>& rhs){ return Func<T>         (lhs, rhs); } \
	template <typename T, typename rhsType> inline Ret operator Ope(const Array<T>& lhs, const  rhsType& rhs){ return Func<T, rhsType>(lhs, rhs); } \
	template <typename T, typename lhsType> inline Ret operator Ope(const  lhsType& lhs, const Array<T>& rhs){ return Func<T, lhsType>(lhs, rhs); }

#define SSTD_DEF_mat_Operator_e(Ret, Array, Array_e, Ope, Func)			\
	template <typename T> inline Ret operator Ope(const Array_e<T>& lhs, const Array_e<T>& rhs){ return Func(lhs, rhs); } \
	template <typename T> inline Ret operator Ope(const Array  <T>& lhs, const Array_e<T>& rhs){ return Func(lhs, rhs); } \
	template <typename T> inline Ret operator Ope(const Array_e<T>& lhs, const Array  <T>& rhs){ return Func(lhs, rhs); }

// plus
SSTD_DEF_mat_Operator(sstd::mat_c<T>, sstd::mat_c, +, sstd::add);
SSTD_DEF_mat_Operator_e(sstd::mat_c<T>, sstd::mat_c, sstd::mat_c_elements, +, sstd::add_e);

// minus
SSTD_DEF_mat_Operator(sstd::mat_c<T>, sstd::mat_c, -, sstd::sub);
SSTD_DEF_mat_Operator_e(sstd::mat_c<T>, sstd::mat_c, sstd::mat_c_elements, -, sstd::sub_e);

// multiplication
SSTD_DEF_mat_Operator(sstd::mat_c<T>, sstd::mat_c, *, sstd::mul);
SSTD_DEF_mat_Operator_e(sstd::mat_c<T>, sstd::mat_c, sstd::mat_c_elements, *, sstd::mul_e);

// division
SSTD_DEF_mat_Operator_e(sstd::mat_c<T>, sstd::mat_c, sstd::mat_c_elements, /, sstd::div_e);

// modulo
SSTD_DEF_mat_Operator(sstd::mat_c<T>, sstd::mat_c, %, sstd::mod);
SSTD_DEF_mat_Operator_e(sstd::mat_c<T>, sstd::mat_c, sstd::mat_c_elements, %, sstd::mod_e);

// power
template <typename T> inline sstd::mat_c<T> operator^(const sstd::mat_c<T>& lhs, const  char & rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat_c<T> operator^(const sstd::mat_c<T>& lhs, const  int8 & rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat_c<T> operator^(const sstd::mat_c<T>& lhs, const  int16& rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat_c<T> operator^(const sstd::mat_c<T>& lhs, const  int32& rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat_c<T> operator^(const sstd::mat_c<T>& lhs, const  int64& rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat_c<T> operator^(const sstd::mat_c<T>& lhs, const uint8 & rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat_c<T> operator^(const sstd::mat_c<T>& lhs, const uint16& rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat_c<T> operator^(const sstd::mat_c<T>& lhs, const uint32& rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat_c<T> operator^(const sstd::mat_c<T>& lhs, const uint64& rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat_c<T> operator^(const sstd::mat_c<T>& lhs, const  float& rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat_c<T> operator^(const sstd::mat_c<T>& lhs, const double& rhs){ return sstd::pow<T>(lhs, rhs); }
SSTD_DEF_mat_Operator_e(sstd::mat_c<T>, sstd::mat_c, sstd::mat_c_elements, ^, sstd::pow_e);

//---

// Relational operators

// equal
SSTD_DEF_mat_Operator(bool, sstd::mat_c, ==, sstd::eq);
SSTD_DEF_mat_Operator_e(bool, sstd::mat_c, sstd::mat_c_elements, ==, sstd::eq_e);

// not equal
SSTD_DEF_mat_Operator(bool, sstd::mat_c, !=, sstd::ne);
SSTD_DEF_mat_Operator_e(bool, sstd::mat_c, sstd::mat_c_elements, !=, sstd::ne_e);

//---

// Deletion of used definition, in order not to pollute the namespace
#undef SSTD_DEF_mat_Operator
#undef SSTD_DEF_mat_Operator_e

//-----------------------------------------------------------------------------------------------------------------------------------------------

