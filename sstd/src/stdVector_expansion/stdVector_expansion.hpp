#pragma once
#include "../math.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd_stdVecEx{
	// operators for mathematics
	template <typename T>                   std::vector<T>  add   (const std::vector<T>& lhs, const std::vector<T>& rhs); // +
	template <typename T, typename rhsType> std::vector<T>  add   (const std::vector<T>& lhs, const        rhsType& rhs);
	template <typename T, typename lhsType> std::vector<T>  add   (const        lhsType& lhs, const std::vector<T>& rhs);
	template <typename T>                   std::vector<T>& add_eq(      std::vector<T>& lhs, const std::vector<T>& rhs); // +=
	template <typename T, typename rhsType> std::vector<T>& add_eq(      std::vector<T>& lhs, const        rhsType& rhs);
	
	template <typename T>                   std::vector<T>  sub   (const std::vector<T>& lhs, const std::vector<T>& rhs); // -
	template <typename T, typename rhsType> std::vector<T>  sub   (const std::vector<T>& lhs, const        rhsType& rhs);
	template <typename T, typename lhsType> std::vector<T>  sub   (const        lhsType& lhs, const std::vector<T>& rhs);
	template <typename T>                   std::vector<T>& sub_eq(      std::vector<T>& lhs, const std::vector<T>& rhs); // -=
	template <typename T, typename rhsType> std::vector<T>& sub_eq(      std::vector<T>& lhs, const        rhsType& rhs);
	
	template <typename T>                   std::vector<T>  mul   (const std::vector<T>& lhs, const std::vector<T>& rhs); // *
	template <typename T, typename rhsType> std::vector<T>  mul   (const std::vector<T>& lhs, const        rhsType& rhs);
	template <typename T, typename lhsType> std::vector<T>  mul   (const        lhsType& lhs, const std::vector<T>& rhs);
	template <typename T>                   std::vector<T>& mul_eq(      std::vector<T>& lhs, const std::vector<T>& rhs); // *=
	template <typename T, typename rhsType> std::vector<T>& mul_eq(      std::vector<T>& lhs, const        rhsType& rhs);
	
	template <typename T>                   std::vector<T>  div   (const std::vector<T>& lhs, const std::vector<T>& rhs); // /
	template <typename T, typename rhsType> std::vector<T>  div   (const std::vector<T>& lhs, const        rhsType& rhs);
	template <typename T, typename lhsType> std::vector<T>  div   (const        lhsType& lhs, const std::vector<T>& rhs);
	template <typename T>                   std::vector<T>& div_eq(      std::vector<T>& lhs, const std::vector<T>& rhs); // /=
	template <typename T, typename rhsType> std::vector<T>& div_eq(      std::vector<T>& lhs, const        rhsType& rhs);
	
	template <typename T>                   std::vector<T>  mod   (const std::vector<T>& lhs, const std::vector<T>& rhs); // %
	template <typename T, typename rhsType> std::vector<T>  mod   (const std::vector<T>& lhs, const        rhsType& rhs);
	template <typename T, typename lhsType> std::vector<T>  mod   (const        lhsType& lhs, const std::vector<T>& rhs);
	template <typename T>                   std::vector<T>& mod_eq(      std::vector<T>& lhs, const std::vector<T>& rhs); // %=
	template <typename T, typename rhsType> std::vector<T>& mod_eq(      std::vector<T>& lhs, const        rhsType& rhs);
	
	template <typename T>                   std::vector<T>  pow   (const std::vector<T>& lhs, const std::vector<T>& rhs); // ^
	template <typename T, typename rhsType> std::vector<T>  pow   (const std::vector<T>& lhs, const        rhsType& rhs);
	template <typename T, typename lhsType> std::vector<T>  pow   (const        lhsType& lhs, const std::vector<T>& rhs);
	template <typename T>                   std::vector<T>& pow_eq(      std::vector<T>& lhs, const std::vector<T>& rhs); // ^=
	template <typename T, typename rhsType> std::vector<T>& pow_eq(      std::vector<T>& lhs, const        rhsType& rhs);
	
	// operators for std::vector
	template <typename T>                   std::vector<T>  push_back   (const std::vector<T>& lhs, const std::vector<T>& rhs); // <<
	template <typename T, typename rhsType> std::vector<T>  push_back   (const std::vector<T>& lhs, const        rhsType& rhs);
	template <typename T, typename lhsType> std::vector<T>  push_back   (const        lhsType& lhs, const std::vector<T>& rhs);
	template <typename T>                   std::vector<T>& push_back_eq(      std::vector<T>& lhs, const std::vector<T>& rhs); // <<=
	template <typename T, typename rhsType> std::vector<T>& push_back_eq(      std::vector<T>& lhs, const        rhsType& rhs);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

// operators for mathematics
#define SSTD_DEF_stdVecEx_o(Func, Ope)								\
	template <typename T>												\
	inline std::vector<T> Func(const std::vector<T>& lhs, const std::vector<T>& rhs){ \
		std::vector<T> ret(lhs.size());									\
		for(uint p=0; p<ret.size(); p++){ ret[p]=lhs[p] Ope rhs[p]; }	\
		return ret;														\
	}																	\
	template <typename T, typename rhsType>								\
	inline std::vector<T> Func(const std::vector<T>& lhs, const rhsType& rhs){ \
		std::vector<T> ret(lhs.size());									\
		for(uint p=0; p<ret.size(); p++){ ret[p]=lhs[p] Ope rhs; }		\
		return ret;														\
	}																	\
	template <typename T, typename rhsType>								\
	inline std::vector<T> Func(const rhsType& lhs, const std::vector<T>& rhs){ \
		std::vector<T> ret(rhs.size());									\
		for(uint p=0; p<ret.size(); p++){ ret[p]=lhs Ope rhs[p]; }		\
		return ret;														\
	}
#define SSTD_DEF_stdVecEx_o_eq(Func, Ope)								\
	template <typename T>												\
	inline std::vector<T>& Func(std::vector<T>& lhs, const std::vector<T>& rhs){ \
		for(uint p=0; p<lhs.size(); p++){ lhs[p] Ope rhs[p]; }			\
		return lhs;														\
	}																	\
	template <typename T, typename rhsType>								\
	inline std::vector<T>& Func(std::vector<T>& lhs, const rhsType& rhs){ \
		for(uint p=0; p<lhs.size(); p++){ lhs[p] Ope rhs; }				\
		return lhs;														\
	}
#define SSTD_DEF_stdVecEx_f(Func, Func2)								\
	template <typename T>												\
	inline std::vector<T> Func(const std::vector<T>& lhs, const std::vector<T>& rhs){ \
		std::vector<T> ret(lhs.size());									\
		for(uint p=0; p<ret.size(); p++){ ret[p]=Func2(lhs[p], rhs[p]); } \
		return ret;														\
	}																	\
	template <typename T, typename rhsType>								\
	inline std::vector<T> Func(const std::vector<T>& lhs, const rhsType& rhs){ \
		std::vector<T> ret(lhs.size());									\
		for(uint p=0; p<ret.size(); p++){ ret[p]=Func2(lhs[p], rhs); }	\
		return ret;														\
	}																	\
	template <typename T, typename rhsType>								\
	inline std::vector<T> Func(const rhsType& lhs, const std::vector<T>& rhs){ \
		std::vector<T> ret(rhs.size());									\
		for(uint p=0; p<ret.size(); p++){ ret[p]=Func2(lhs, rhs[p]); }	\
		return ret;														\
	}
#define SSTD_DEF_stdVecEx_f_eq(Func, Func2)								\
	template <typename T>												\
	inline std::vector<T>& Func(std::vector<T>& lhs, const std::vector<T>& rhs){ \
		for(uint p=0; p<lhs.size(); p++){ lhs[p]=Func2(lhs[p], rhs[p]); } \
		return lhs;														\
	}																	\
	template <typename T, typename rhsType>								\
	inline std::vector<T>& Func(std::vector<T>& lhs, const rhsType& rhs){ \
		for(uint p=0; p<lhs.size(); p++){ lhs[p]=Func2(lhs[p], rhs); }	\
		return lhs;														\
	}
SSTD_DEF_stdVecEx_o   (sstd_stdVecEx::add   , + );
SSTD_DEF_stdVecEx_o_eq(sstd_stdVecEx::add_eq, +=);
SSTD_DEF_stdVecEx_o   (sstd_stdVecEx::sub   , - );
SSTD_DEF_stdVecEx_o_eq(sstd_stdVecEx::sub_eq, -=);
SSTD_DEF_stdVecEx_o   (sstd_stdVecEx::mul   , * );
SSTD_DEF_stdVecEx_o_eq(sstd_stdVecEx::mul_eq, *=);
SSTD_DEF_stdVecEx_o   (sstd_stdVecEx::div   , / );
SSTD_DEF_stdVecEx_o_eq(sstd_stdVecEx::div_eq, /=);
SSTD_DEF_stdVecEx_o   (sstd_stdVecEx::mod   , % );
SSTD_DEF_stdVecEx_o_eq(sstd_stdVecEx::mod_eq, %=);
SSTD_DEF_stdVecEx_f   (sstd_stdVecEx::pow   , sstd::pow); // ^
SSTD_DEF_stdVecEx_f_eq(sstd_stdVecEx::pow_eq, sstd::pow); // ^=
#undef SSTD_DEF_stdVecEx_o    // Deletion of used definition, in order not to pollute the namespace
#undef SSTD_DEF_stdVecEx_o_eq // Deletion of used definition, in order not to pollute the namespace
#undef SSTD_DEF_stdVecEx_f    // Deletion of used definition, in order not to pollute the namespace
#undef SSTD_DEF_stdVecEx_f_eq // Deletion of used definition, in order not to pollute the namespace

//---

// operators for std::vector
template <typename T>
inline std::vector<T> sstd_stdVecEx::push_back(const std::vector<T>& lhs, const std::vector<T>& rhs){
	std::vector<T> ret(lhs.size()+rhs.size());
	uint i=0;
	for(uint p=0; p<lhs.size(); p++){ ret[i]=lhs[p]; i++; }
	for(uint p=0; p<rhs.size(); p++){ ret[i]=lhs[p]; i++; }
	return ret;
}
template <typename T, typename rhsType>
inline std::vector<T> sstd_stdVecEx::push_back(const std::vector<T>& lhs, const rhsType& rhs){
	std::vector<T> ret(lhs.size()+1);
	for(uint p=0; p<lhs.size(); p++){ ret[p]=lhs[p]; }
	ret[lhs.size()]=rhs;
	return ret;
}
template <typename T, typename lhsType>
inline std::vector<T> sstd_stdVecEx::push_back(const lhsType& lhs, const std::vector<T>& rhs){
	std::vector<T> ret(rhs.size()+1);
	ret[0]=lhs;
	for(uint p=0; p<rhs.size(); p++){ ret[p+1]=rhs[p]; }
	return ret;
}

template <typename T>
inline std::vector<T>& sstd_stdVecEx::push_back_eq(std::vector<T>& lhs, const std::vector<T>& rhs){
	lhs.insert(lhs.end(), rhs.begin(), rhs.end());
	return lhs;
}
template <typename T, typename rhsType>
inline std::vector<T>& sstd_stdVecEx::push_back_eq(std::vector<T>& lhs, const rhsType& rhs){
	lhs.push_back(rhs);
	return lhs;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define SSTD_DEF_stdVecEx_Operator(Func, Ope)							\
	template <typename T>                   inline std::vector<T> operator Ope(const std::vector<T>& lhs, const std::vector<T>& rhs){ return Func<T>         (lhs, rhs); } \
	template <typename T, typename rhsType> inline std::vector<T> operator Ope(const std::vector<T>& lhs, const        rhsType& rhs){ return Func<T, rhsType>(lhs, rhs); } \
	template <typename T, typename lhsType> inline std::vector<T> operator Ope(const        lhsType& lhs, const std::vector<T>& rhs){ return Func<T, lhsType>(lhs, rhs); }
#define SSTD_DEF_stdVecEx_Operator_eq(Func, Ope)						\
	template <typename T>                   inline std::vector<T>& operator Ope(std::vector<T>& lhs, const std::vector<T>& rhs){ return Func<T>         (lhs, rhs); } \
	template <typename T, typename rhsType> inline std::vector<T>& operator Ope(std::vector<T>& lhs, const        rhsType& rhs){ return Func<T, rhsType>(lhs, rhs); }

// operators for mathematics
SSTD_DEF_stdVecEx_Operator   (sstd_stdVecEx::add   , + );
SSTD_DEF_stdVecEx_Operator_eq(sstd_stdVecEx::add_eq, +=);
SSTD_DEF_stdVecEx_Operator   (sstd_stdVecEx::sub   , - );
SSTD_DEF_stdVecEx_Operator_eq(sstd_stdVecEx::sub_eq, -=);
SSTD_DEF_stdVecEx_Operator   (sstd_stdVecEx::mul   , * );
SSTD_DEF_stdVecEx_Operator_eq(sstd_stdVecEx::mul_eq, *=);
SSTD_DEF_stdVecEx_Operator   (sstd_stdVecEx::div   , / );
SSTD_DEF_stdVecEx_Operator_eq(sstd_stdVecEx::div_eq, /=);
SSTD_DEF_stdVecEx_Operator   (sstd_stdVecEx::mod   , % );
SSTD_DEF_stdVecEx_Operator_eq(sstd_stdVecEx::mod_eq, %=);
SSTD_DEF_stdVecEx_Operator   (sstd_stdVecEx::pow   , ^ );
SSTD_DEF_stdVecEx_Operator_eq(sstd_stdVecEx::pow_eq, ^=);

// operators for std::vector
SSTD_DEF_stdVecEx_Operator   (sstd_stdVecEx::push_back   , << );
SSTD_DEF_stdVecEx_Operator_eq(sstd_stdVecEx::push_back_eq, <<=);

#undef SSTD_DEF_stdVecEx_Operator    // Deletion of used definition, in order not to pollute the namespace
#undef SSTD_DEF_stdVecEx_Operator_eq // Deletion of used definition, in order not to pollute the namespace

//---

template <typename T> inline std::vector<T>& operator++(std::vector<T>& rhs)     { for(uint p=0; p<rhs.size(); p++){ rhs[p]++; } return rhs; } // ++rhs
template <typename T> inline std::vector<T>& operator++(std::vector<T>& rhs, int){ for(uint p=0; p<rhs.size(); p++){ rhs[p]++; } return rhs; } //   rhs++
template <typename T> inline std::vector<T>& operator--(std::vector<T>& rhs)     { for(uint p=0; p<rhs.size(); p++){ rhs[p]--; } return rhs; } // --rhs
template <typename T> inline std::vector<T>& operator--(std::vector<T>& rhs, int){ for(uint p=0; p<rhs.size(); p++){ rhs[p]--; } return rhs; } //   rhs--

//-----------------------------------------------------------------------------------------------------------------------------------------------

