#pragma once

#include "./mat.hpp"
#include "./mat_elements.hpp" // for element operations (elements multiplication)
#include "../math.hpp"
#include "../pdbg.hpp"
#include "../typeDef.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
	// #include "./mat.hpp"
	template <typename T>
	extern void eye(sstd::mat<T>& rhs);
	
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
	template <typename T>                   sstd::mat<T> add  (const sstd::mat<T>& lhs, const sstd::mat<T>& rhs);
	template <typename T, typename rhsType> sstd::mat<T> add  (const sstd::mat<T>& lhs, const      rhsType& rhs);
	template <typename T, typename lhsType> sstd::mat<T> add  (const      lhsType& lhs, const sstd::mat<T>& rhs);
	template <typename T>                   sstd::mat<T> add_e(const sstd::mat_elements<T>& lhs, const sstd::mat_elements<T>& rhs);
	template <typename T>                   sstd::mat<T> add_e(const sstd::mat         <T>& lhs, const sstd::mat_elements<T>& rhs);
	template <typename T>                   sstd::mat<T> add_e(const sstd::mat_elements<T>& lhs, const sstd::mat         <T>& rhs);
	
	template <typename T>                   sstd::mat<T> sub  (const sstd::mat<T>& lhs, const sstd::mat<T>& rhs);
	template <typename T, typename rhsType> sstd::mat<T> sub  (const sstd::mat<T>& lhs, const      rhsType& rhs);
	template <typename T, typename lhsType> sstd::mat<T> sub  (const      lhsType& lhs, const sstd::mat<T>& rhs);
	template <typename T>                   sstd::mat<T> sub_e(const sstd::mat_elements<T>& lhs, const sstd::mat_elements<T>& rhs);
	template <typename T>                   sstd::mat<T> sub_e(const sstd::mat         <T>& lhs, const sstd::mat_elements<T>& rhs);
	template <typename T>                   sstd::mat<T> sub_e(const sstd::mat_elements<T>& lhs, const sstd::mat         <T>& rhs);
	
	template <typename T>                   sstd::mat<T> mul  (const sstd::mat<T>& lhs, const sstd::mat<T>& rhs);
	template <typename T, typename rhsType> sstd::mat<T> mul  (const sstd::mat<T>& lhs, const      rhsType& rhs);
	template <typename T, typename lhsType> sstd::mat<T> mul  (const      lhsType& lhs, const sstd::mat<T>& rhs);
	template <typename T>                   sstd::mat<T> mul_e(const sstd::mat_elements<T>& lhs, const sstd::mat_elements<T>& rhs);
	template <typename T>                   sstd::mat<T> mul_e(const sstd::mat         <T>& lhs, const sstd::mat_elements<T>& rhs);
	template <typename T>                   sstd::mat<T> mul_e(const sstd::mat_elements<T>& lhs, const sstd::mat         <T>& rhs);
	
	template <typename T>                   sstd::mat<T> div  (const sstd::mat<T>& lhs, const sstd::mat<T>& rhs);
	template <typename T>                   sstd::mat<T> div_e(const sstd::mat_elements<T>& lhs, const sstd::mat_elements<T>& rhs);
	template <typename T>                   sstd::mat<T> div_e(const sstd::mat         <T>& lhs, const sstd::mat_elements<T>& rhs);
	template <typename T>                   sstd::mat<T> div_e(const sstd::mat_elements<T>& lhs, const sstd::mat         <T>& rhs);
	
	template <typename T>                   sstd::mat<T> mod  (const sstd::mat<T>& lhs, const sstd::mat<T>& rhs);
	template <typename T, typename rhsType> sstd::mat<T> mod  (const sstd::mat<T>& lhs, const      rhsType& rhs);
	template <typename T, typename lhsType> sstd::mat<T> mod  (const      lhsType& lhs, const sstd::mat<T>& rhs);
	template <typename T>                   sstd::mat<T> mod_e(const sstd::mat_elements<T>& lhs, const sstd::mat_elements<T>& rhs);
	template <typename T>                   sstd::mat<T> mod_e(const sstd::mat         <T>& lhs, const sstd::mat_elements<T>& rhs);
	template <typename T>                   sstd::mat<T> mod_e(const sstd::mat_elements<T>& lhs, const sstd::mat         <T>& rhs);
	
//	template <typename T> sstd::mat<T> pow  (const sstd::mat<T>& lhs, const sstd::mat<T>& rhs); // 定義されるのか不明 (行列指数関数? -> sciLab 等で実験してみるのがよい)
	template <typename T>                   sstd::mat<T> pow  (const sstd::mat<T>& lhs, const        char& rhs); // テンプレートの部分特殊化が可能なのはクラステンプレートのみである。関数テンプレートは部分特殊化できず、明示的特殊化のみ可能である。しかし多くの場合、関数テンプレートの部分特殊化は多重定義によって代用できる。(Ref: https://ja.wikipedia.org/wiki/%E3%83%86%E3%83%B3%E3%83%97%E3%83%AC%E3%83%BC%E3%83%88%E3%81%AE%E9%83%A8%E5%88%86%E7%89%B9%E6%AE%8A%E5%8C%96)
	template <typename T>                   sstd::mat<T> pow  (const sstd::mat<T>& lhs, const       int8 & rhs);
	template <typename T>                   sstd::mat<T> pow  (const sstd::mat<T>& lhs, const       int16& rhs);
	template <typename T>                   sstd::mat<T> pow  (const sstd::mat<T>& lhs, const       int32& rhs);
	template <typename T>                   sstd::mat<T> pow  (const sstd::mat<T>& lhs, const       int64& rhs);
	template <typename T>                   sstd::mat<T> pow  (const sstd::mat<T>& lhs, const      uint8 & rhs);
	template <typename T>                   sstd::mat<T> pow  (const sstd::mat<T>& lhs, const      uint16& rhs);
	template <typename T>                   sstd::mat<T> pow  (const sstd::mat<T>& lhs, const      uint32& rhs);
	template <typename T>                   sstd::mat<T> pow  (const sstd::mat<T>& lhs, const      uint64& rhs);
	template <typename T>                   sstd::mat<T> pow  (const sstd::mat<T>& lhs, const       float& rhs);
	template <typename T>                   sstd::mat<T> pow  (const sstd::mat<T>& lhs, const      double& rhs);
	template <typename T>                   sstd::mat<T> pow_e(const sstd::mat_elements<T>& lhs, const sstd::mat_elements<T>& rhs);
	template <typename T>                   sstd::mat<T> pow_e(const sstd::mat         <T>& lhs, const sstd::mat_elements<T>& rhs);
	template <typename T>                   sstd::mat<T> pow_e(const sstd::mat_elements<T>& lhs, const sstd::mat         <T>& rhs);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

// Operators for linearAlgebra

#define SSTD_DEF_mat_o(Func, Ope)										\
	template <typename T>												\
	inline sstd::mat<T> Func(const sstd::mat<T>& lhs, const sstd::mat<T>& rhs){ \
		sstd::mat<T> ret(lhs.rows(), lhs.cols());						\
		for(uint p=0; p<ret.len(); p++){ ret[p]=lhs[p] Ope rhs[p]; }	\
		return ret;														\
	}																	\
	template <typename T, typename rhsType>								\
	inline sstd::mat<T> Func(const sstd::mat<T>& lhs, const rhsType& rhs){ \
		sstd::mat<T> ret(lhs.rows(), lhs.cols());						\
		for(uint p=0; p<ret.len(); p++){ ret[p]=lhs[p] Ope rhs; }		\
		return ret;														\
	}																	\
	template <typename T, typename rhsType>								\
	inline sstd::mat<T> Func(const rhsType& lhs, const sstd::mat<T>& rhs){ \
		sstd::mat<T> ret(rhs.rows(), rhs.cols());						\
		for(uint p=0; p<ret.len(); p++){ ret[p]=lhs Ope rhs[p]; }		\
		return ret;														\
	}

//---

#define SSTD_DEF_mat_f(Func, Func2)										\
	template <typename T>												\
	inline sstd::mat<T> Func(const sstd::mat<T>& lhs, const sstd::mat<T>& rhs){ \
		sstd::mat<T> ret(lhs.rows(), lhs.cols());						\
		for(uint p=0; p<ret.len(); p++){ ret[p]=Func2(lhs[p], rhs[p]); } \
		return ret;														\
	}																	\
	template <typename T, typename rhsType>								\
	inline sstd::mat<T> Func(const sstd::mat<T>& lhs, const rhsType& rhs){ \
		sstd::mat<T> ret(lhs.rows(), lhs.cols());						\
		for(uint p=0; p<ret.len(); p++){ ret[p]=Func2(lhs[p], rhs); }	\
		return ret;														\
	}																	\
	template <typename T, typename rhsType>								\
	inline sstd::mat<T> Func(const rhsType& lhs, const sstd::mat<T>& rhs){ \
		sstd::mat<T> ret(rhs.rows(), rhs.cols());						\
		for(uint p=0; p<ret.size(); p++){ ret[p]=Func2(lhs, rhs[p]); }	\
		return ret;														\
	}

//---

#define SSTD_DEF_mat_elements_o(Func, Ope)								\
	template <typename T>												\
	inline sstd::mat<T> Func(const sstd::mat_elements<T>& lhs, const sstd::mat_elements<T>& rhs){ \
		sstd::mat<T> ret(lhs.rows(), lhs.cols());						\
		for(uint p=0; p<ret.len(); p++){ ret[p]=lhs[p] Ope rhs[p]; }	\
		return ret;														\
	}																	\
	template <typename T>												\
	inline sstd::mat<T> Func(const sstd::mat<T>& lhs, const sstd::mat_elements<T>& rhs){ \
		sstd::mat<T> ret(lhs.rows(), lhs.cols());						\
		for(uint p=0; p<ret.len(); p++){ ret[p]=lhs[p] Ope rhs[p]; }	\
		return ret;														\
	}																	\
	template <typename T>												\
	inline sstd::mat<T> Func(const sstd::mat_elements<T>& lhs, const sstd::mat<T>& rhs){ \
		sstd::mat<T> ret(rhs.rows(), rhs.cols());						\
		for(uint p=0; p<ret.len(); p++){ ret[p]=lhs[p] Ope rhs[p]; }	\
		return ret;														\
	}

//---

#define SSTD_DEF_mat_elements_f(Func, Func2)								\
	template <typename T>												\
	inline sstd::mat<T> Func(const sstd::mat_elements<T>& lhs, const sstd::mat_elements<T>& rhs){ \
		sstd::mat<T> ret(lhs.rows(), lhs.cols());						\
		for(uint p=0; p<ret.len(); p++){ ret[p]=Func2(lhs[p], rhs[p]); } \
		return ret;														\
	}																	\
	template <typename T>												\
	inline sstd::mat<T> Func(const sstd::mat<T>& lhs, const sstd::mat_elements<T>& rhs){ \
		sstd::mat<T> ret(lhs.rows(), lhs.cols());						\
		for(uint p=0; p<ret.len(); p++){ ret[p]=Func2(lhs[p], rhs[p]); } \
		return ret;														\
	}																	\
	template <typename T>												\
	inline sstd::mat<T> Func(const sstd::mat_elements<T>& lhs, const sstd::mat<T>& rhs){ \
		sstd::mat<T> ret(rhs.rows(), rhs.cols());						\
		for(uint p=0; p<ret.len(); p++){ ret[p]=Func2(lhs[p], rhs[p]); } \
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
inline sstd::mat<T> sstd::mul(const sstd::mat<T>& lhs, const sstd::mat<T>& rhs){
	sstd::mat<T> ret(lhs.rows(), rhs.cols());
	for(uint q=0; q<ret.cols(); q++){
		for(uint p=0; p<ret.rows(); p++){
			ret(p, q) = lhs(p, 0) * rhs(0, q);
			for(uint i=1; i<lhs.cols(); i++){ ret(p, q) += lhs(p, i) * rhs(i, q); }
		}
	}
	return ret;
//	// 上記のように最適化
//	sstd::mat<T> ret(lhs.rows(), rhs.cols());
//	zeros(ret);
//	for(uint q=0; q<ret.cols(); q++){
//		for(uint p=0; p<ret.rows(); p++){
//			for(uint i=0; i<lhs.cols(); i++){ ret(p, q) += lhs(p, i) * rhs(i, q); }
//		}
//	}
//	return ret;
}
template <typename T, typename rhsType>
inline sstd::mat<T> sstd::mul(const sstd::mat<T>& lhs, const rhsType& rhs){
	sstd::mat<T> ret(lhs.rows(), lhs.cols());
	for(uint p=0; p<ret.len(); p++){ ret[p]=lhs[p]*rhs; }
	return ret;
}
template <typename T, typename lhsType>
inline sstd::mat<T> sstd::mul(const lhsType& lhs, const sstd::mat<T>& rhs){
	sstd::mat<T> ret(rhs.rows(), rhs.cols());
	for(uint p=0; p<ret.len(); p++){ ret[p]=lhs*rhs[p]; }
	return ret;
}
SSTD_DEF_mat_elements_o(sstd::mul_e, *);

// division
template <typename T, typename rhsType>
inline sstd::mat<T> sstd::div(const sstd::mat<T>& lhs, const rhsType& rhs){
	sstd::mat<T> ret(lhs.rows(), lhs.cols());
	for(uint p=0; p<ret.len(); p++){ ret[p]=lhs[p]/rhs; }
	return ret;
}
SSTD_DEF_mat_elements_o(sstd::div_e, /);

// modulo
SSTD_DEF_mat_o(sstd::mod, %);
SSTD_DEF_mat_elements_o(sstd::mod_e, %);

// power
template <typename T, typename rhsType>
inline void pow_int_calculation(sstd::mat<T>& base, rhsType& exponent){
	for(; exponent>(rhsType)0; exponent>>=1){
		if(exponent & 1){
			if(exponent==(rhsType)1){ return; }
			break;
		}
		base = sstd::mul(base, base);
	}
	sstd::mat<T> buf = base;
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
inline sstd::mat<T> pow_signedInt(sstd::mat<T> base, rhsType exponent){
	if(exponent==(rhsType)0){ sstd::eye(base); return base; }
	if(exponent>=(rhsType)0){ pow_int_calculation(base, exponent);
	}          else         { sstd::pdbg("ERROR: not implemented.\n");     }
	return base;
}
template <typename T> inline sstd::mat<T> sstd::pow(const sstd::mat<T>& lhs, const  char& rhs){ return pow_signedInt<T, int8 >(lhs, (int8)rhs); }
template <typename T> inline sstd::mat<T> sstd::pow(const sstd::mat<T>& lhs, const int8 & rhs){ return pow_signedInt<T, int8 >(lhs, rhs); }
template <typename T> inline sstd::mat<T> sstd::pow(const sstd::mat<T>& lhs, const int16& rhs){ return pow_signedInt<T, int16>(lhs, rhs); }
template <typename T> inline sstd::mat<T> sstd::pow(const sstd::mat<T>& lhs, const int32& rhs){ return pow_signedInt<T, int32>(lhs, rhs); }
template <typename T> inline sstd::mat<T> sstd::pow(const sstd::mat<T>& lhs, const int64& rhs){ return pow_signedInt<T, int64>(lhs, rhs); }

template <typename T, typename rhsType>
inline sstd::mat<T> pow_unsignedInt(sstd::mat<T> base, rhsType exponent){
	if(exponent==(rhsType)0){ sstd::eye(base); return base; }
	pow_int_calculation(base, exponent);
	return base;
}
template <typename T> inline sstd::mat<T> sstd::pow(const sstd::mat<T>& lhs, const uint8 & rhs){ return pow_unsignedInt<T, uint8 >(lhs, rhs); }
template <typename T> inline sstd::mat<T> sstd::pow(const sstd::mat<T>& lhs, const uint16& rhs){ return pow_unsignedInt<T, uint16>(lhs, rhs); }
template <typename T> inline sstd::mat<T> sstd::pow(const sstd::mat<T>& lhs, const uint32& rhs){ return pow_unsignedInt<T, uint32>(lhs, rhs); }
template <typename T> inline sstd::mat<T> sstd::pow(const sstd::mat<T>& lhs, const uint64& rhs){ return pow_unsignedInt<T, uint64>(lhs, rhs); }

template <typename T> inline sstd::mat<T> sstd::pow(const sstd::mat<T>& lhs, const  float& rhs){ sstd::pdbg("ERROR: not implemented.\n"); return lhs; }
template <typename T> inline sstd::mat<T> sstd::pow(const sstd::mat<T>& lhs, const double& rhs){ sstd::pdbg("ERROR: not implemented.\n"); return lhs; }

SSTD_DEF_mat_elements_f(sstd::pow_e, sstd::pow);

//---

#undef SSTD_DEF_mat_o
#undef SSTD_DEF_mat_f
#undef SSTD_DEF_mat_elements_o
#undef SSTD_DEF_mat_elements_f

//-----------------------------------------------------------------------------------------------------------------------------------------------

// Operators for linearAlgebra

#define SSTD_DEF_mat_Operator(Array, Ope, Func)							\
	template <typename T>                   inline Array<T> operator Ope(const Array<T>& lhs, const Array<T>& rhs){ return Func<T>         (lhs, rhs); } \
	template <typename T, typename rhsType> inline Array<T> operator Ope(const Array<T>& lhs, const  rhsType& rhs){ return Func<T, rhsType>(lhs, rhs); } \
	template <typename T, typename lhsType> inline Array<T> operator Ope(const  lhsType& lhs, const Array<T>& rhs){ return Func<T, lhsType>(lhs, rhs); }

#define SSTD_DEF_mat_Operator_e(Array, Array_e, Ope, Func)				\
	template <typename T> inline Array<T> operator Ope(const Array_e<T>& lhs, const Array_e<T>& rhs){ return Func(lhs, rhs); } \
	template <typename T> inline Array<T> operator Ope(const Array  <T>& lhs, const Array_e<T>& rhs){ return Func(lhs, rhs); } \
	template <typename T> inline Array<T> operator Ope(const Array_e<T>& lhs, const Array  <T>& rhs){ return Func(lhs, rhs); }

// plus
SSTD_DEF_mat_Operator(sstd::mat, +, sstd::add);
SSTD_DEF_mat_Operator_e(sstd::mat, sstd::mat_elements, +, sstd::add_e);

// minus
SSTD_DEF_mat_Operator(sstd::mat, -, sstd::sub);
SSTD_DEF_mat_Operator_e(sstd::mat, sstd::mat_elements, -, sstd::sub_e);

// multiplication
SSTD_DEF_mat_Operator(sstd::mat, *, sstd::mul);
SSTD_DEF_mat_Operator_e(sstd::mat, sstd::mat_elements, *, sstd::mul_e);

// division
SSTD_DEF_mat_Operator_e(sstd::mat, sstd::mat_elements, /, sstd::div_e);

// modulo
SSTD_DEF_mat_Operator(sstd::mat, %, sstd::mod);
SSTD_DEF_mat_Operator_e(sstd::mat, sstd::mat_elements, %, sstd::mod_e);

// power
template <typename T> inline sstd::mat<T> operator^(const sstd::mat<T>& lhs, const  char & rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat<T> operator^(const sstd::mat<T>& lhs, const  int8 & rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat<T> operator^(const sstd::mat<T>& lhs, const  int16& rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat<T> operator^(const sstd::mat<T>& lhs, const  int32& rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat<T> operator^(const sstd::mat<T>& lhs, const  int64& rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat<T> operator^(const sstd::mat<T>& lhs, const uint8 & rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat<T> operator^(const sstd::mat<T>& lhs, const uint16& rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat<T> operator^(const sstd::mat<T>& lhs, const uint32& rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat<T> operator^(const sstd::mat<T>& lhs, const uint64& rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat<T> operator^(const sstd::mat<T>& lhs, const  float& rhs){ return sstd::pow<T>(lhs, rhs); }
template <typename T> inline sstd::mat<T> operator^(const sstd::mat<T>& lhs, const double& rhs){ return sstd::pow<T>(lhs, rhs); }
SSTD_DEF_mat_Operator_e(sstd::mat, sstd::mat_elements, ^, sstd::pow_e);

//---

// Deletion of used definition, in order not to pollute the namespace
#undef SSTD_DEF_mat_Operator
#undef SSTD_DEF_mat_Operator_e

//-----------------------------------------------------------------------------------------------------------------------------------------------

