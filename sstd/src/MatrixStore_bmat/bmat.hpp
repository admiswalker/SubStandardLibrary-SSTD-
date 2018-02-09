#pragma once

#include <iostream>
#include "../typeDef.h"
#include "../MatrixStore_mat/mat.hpp"

// 8x8 binary matrix is column-major order, 
// and outside of the 8x8 martix is row-major order.

//--------------------------------------------------------------------------------------------------------

namespace sstd{
	class bmat;

	void print    (const class sstd::bmat& bMat); // Called by "sstd::print()" function or "sstd::printn()" and "sstd::printn_all()" macros.
	void print_all(const class sstd::bmat& bMat); // Called by "sstd::print_all()" function. (for debug)

	// for sstd::printn(); and sstd::printn_all();.
	void for_printn(const sstd::bmat& bMat);
	
	void copy(class sstd::bmat& lhs, class sstd::bmat& rhs);
	void move(class sstd::bmat& lhs, class sstd::bmat& rhs);

	void               eye(class sstd::bmat& bMat);
	void              ones(class sstd::bmat& bMat);
	void             zeros(class sstd::bmat& bMat);
	class sstd::bmat   eye(const uint& row, const uint& col);
	class sstd::bmat  ones(const uint& row, const uint& col);
	class sstd::bmat zeros(const uint& row, const uint& col);
	class sstd::bmat   eye(const uint& size);
	class sstd::bmat  ones(const uint& size);
	class sstd::bmat zeros(const uint& size);

	class sstd::bmat LxShiftMat(uint size, uint xShift);	// square matrix [size x size]
	class sstd::bmat RxShiftMat(uint size, uint xShift);	// square matrix [size x size]

	class sstd::bmat       Tr(class sstd::bmat& rhs);							// lhs = Transpose(rhs)
	void            Tr_myself(class sstd::bmat& rhs);							// Transpose(rhs)

	class sstd::bmat      add(class sstd::bmat& lhs, class sstd::bmat& rhs);	// lhs + rhs (XOR)
	class sstd::bmat      mul(class sstd::bmat& lhs, class sstd::bmat& rhs);	// lhs * rhs
	class sstd::bmat      pow(class sstd::bmat  base, uint64 exponent);		    // base^{exponent}
	void           add_myself(class sstd::bmat& lhs, class sstd::bmat& rhs);	// lhs += rhs (XOR)
	void           mul_myself(class sstd::bmat& lhs, class sstd::bmat& rhs);	// lhs *= rhs
	void           pow_myself(class sstd::bmat& base, uint64 exponent);			// lhs ^= exponent

	class sstd::bmat     and_(class sstd::bmat& lhs, class sstd::bmat& rhs);	// lhs & rhs (AND)	// _ を付加しないと，何かと名前が衝突した．
	class sstd::bmat      or_(class sstd::bmat& lhs, class sstd::bmat& rhs);	// lhs | rhs (OR)	// _ を付加しないと，何かと名前が衝突した．
	class sstd::bmat     not_(class sstd::bmat& rhs);								// ~rhs (NOT)		// _ を付加しないと，何かと名前が衝突した．
	class sstd::bmat     xor_(class sstd::bmat& lhs, class sstd::bmat& rhs);	// lhs + rhs (XOR)	// _ を付加しないと，何かと名前が衝突した．
	void           and_myself(class sstd::bmat& lhs, class sstd::bmat& rhs);	// lhs & rhs (AND)
	void            or_myself(class sstd::bmat& lhs, class sstd::bmat& rhs);	// lhs | rhs (OR)

	bool                   eq(class sstd::bmat& lhs, class sstd::bmat& rhs);	// lhs == rhs
	bool                   ne(class sstd::bmat& lhs, class sstd::bmat& rhs);	// lhs != rhs

	class sstd::bmat  REShift(class sstd::bmat& rhs, uint ShiftNum);			// RightExpansionShift	// 行列拡大右シフト
	class sstd::bmat  DEShift(class sstd::bmat& rhs, uint ShiftNum);			// DownExpansionShift	// 行列拡大下シフト
	class sstd::bmat horzcat2(class sstd::bmat& lhs, class sstd::bmat& rhs);	// lhs << rhs
	class sstd::bmat vertcat2(class sstd::bmat&  us, class sstd::bmat&  ds);	// us && ds    // upside, downside.
//	class sstd::bmat horzcat (class sstd::bmat& ...);	// horzcat(...)			// 可変長引数での受け渡し
//	class sstd::bmat vertcat (class sstd::bmat& ...);	// vertcat(...)			// 可変長引数での受け渡し

//	   Tr();	// transpose
//	  add();	//       addition (足し算):  summation (和):   plus+ operator
//	  sub();	//    subtraction (引き算): difference (差):  minus- operator
//	  mul();	// multiplication (掛け算):            (積):  times* operator
//	  div();	//       division (割り算):   quotient (商): divide/ operator
//                        surplus (余り算):  remainder (余): modulo% operator
//	  pow();	//                (べき乗):            (  ):  power^ operator
//
//     ne();	// a != b
//     eq();	// a == b
//
//    and();	// 論理 AND: a & b
//     or();	// 論理  OR: a | b
//    not();	// 論理否定: ~a
//    xor();	// 論理 xor <- ???
};

//--------------------------------------------------------------------------------------------------------

#include "./SwapByOneIndex.hpp"	// "namespace bmxs{};" の後 かつ "class bmxs::bmat" で include すること!!!
#include "./SwapByTwoIndex.hpp"	// "namespace bmxs{};" の後 かつ "class bmxs::bmat" で include すること!!!

//--------------------------------------------------------------------------------------------------------

// binary martix
class sstd::bmat{
private:
	// need to soarted by initialized 
	// 初期化する順番で宣言する必要がある
	uint rowNum;	// 行数
	uint colNum;	// 列数
	sstd::mat<uint64> binMat8x8;	// 8x8 の BinMartix 行列の集合
	
public:
	bmat(): rowNum(0), colNum(0) {}
	bmat(const uint& row, const uint& col): rowNum(row), colNum(col), binMat8x8((rowNum-1)/8+1, (colNum-1)/8+1) {}
	bmat(class bmat&  rhs): rowNum(0), colNum(0) { sstd::copy(*this, rhs); } // called by "sstd::bmat buf1(N, N), buf2; buf2 = buf1;" or "sstd::bmat buf1, buf2; buf2 = buf1;".
	bmat(class bmat&& rhs): rowNum(0), colNum(0) { sstd::move(*this, rhs); } // called by "return std::move(rhs);" or "std::swap(lhs, rhs)".
	// std::move(lhs, rhs): "move to uninitalized object" will be called.
	// std::swap(lhs, rhs): "move to uninitalized object" -> "copy to lhs or rhs" -> "copy to lhs or rhs" will be called.
	~bmat(){}
	
	// inline sstd::mat<uint64> bMat8x8(){ return binMat8x8; } // Do not do this to avoid object copy
	inline const sstd::mat<uint64>& bMat8x8_R() const { return binMat8x8; }
	inline const uint rows() const { return rowNum; }
	inline const uint cols() const { return colNum; }

	// RW: read and write
	inline sstd::mat<uint64>& bMat8x8_RW(){ return binMat8x8; }
	inline uint& rows_RW(){ return rowNum; }
	inline uint& cols_RW(){ return colNum; }

	class bmat& operator= (const class bmat& rhs){        sstd::copy(*this, (class sstd::bmat&)rhs); return *this; }// called by "lhs = sstd::add(A, B);".
	class bmat  operator+ (const class bmat& rhs){ return sstd::add (*this, (class sstd::bmat&)rhs); }				// called by "lhs + rhs;".	// XOR
	class bmat  operator* (const class bmat& rhs){ return sstd::mul (*this, (class sstd::bmat&)rhs); }				// called by "lhs * rhs;".	// mul
	class bmat  operator^ (const uint64& rhs)    { return sstd::pow (*this, rhs); }									// called by "lhs ^ rhs;".	// pow (not XOR)

	class bmat  operator& (const class bmat& rhs){ return sstd::and_(*this, (class sstd::bmat&)rhs); }				// called by "lhs & rhs;".	// AND
	class bmat  operator| (const class bmat& rhs){ return sstd::or_ (*this, (class sstd::bmat&)rhs); }				// called by "lhs | rhs;".	//  OR
	class bmat  operator~ ()                     { return sstd::not_(*this);      }									// called by "~rhs;".		// NOT

	class bmat& operator+=(const class bmat& rhs){ sstd::add_myself(*this, (class sstd::bmat&)rhs); return *this; }	// called by "lhs += rhs;".
	class bmat& operator*=(const class bmat& rhs){ sstd::mul_myself(*this, (class sstd::bmat&)rhs); return *this; }	// called by "lhs *= rhs;".
	class bmat& operator^=(const uint64& rhs)    { sstd::pow_myself(*this, rhs); return *this; }					// called by "lhs ^= rhs;".
	class bmat& operator&=(const class bmat& rhs){ sstd::and_myself(*this, (class sstd::bmat&)rhs); return *this; }	// called by "lhs &= rhs;".
	class bmat& operator|=(const class bmat& rhs){ sstd::or_myself (*this, (class sstd::bmat&)rhs); return *this; }	// called by "lhs |= rhs;".

	bool        operator==(const class bmat& rhs){ return sstd::eq(*this, (class sstd::bmat&)rhs); }				// called by "sstd::bmat bMatA, bMatB; if(bMatA == bMatB){printf("same\n");}else{printf("different\n");}".
	bool        operator!=(const class bmat& rhs){ return sstd::ne(*this, (class sstd::bmat&)rhs); }				// called by "sstd::bmat bMatA, bMatB; if(bMatA == bMatB){printf("same\n");}else{printf("different\n");}".

	class bmat  operator<<(const class bmat& rhs){ return sstd::horzcat2(*this, (class sstd::bmat&)rhs); }			// called by "sstd::bmat bMatA, bMatB, bMatC; bMatC = bMatA << bMatB;". // Horizontal connection of matrix.
	class bmat  operator&&(const class bmat&  ds){ return sstd::vertcat2(*this, (class sstd::bmat&) ds); }			// called by "sstd::bmat bMatA, bMatB, bMatC; bMatC = bMatA && bMatB;". // Vertical connection of matrix.

	class SwapByOneIndex  operator[](const uint& p){ return OpSwapByOneIndex(this, p); }							// col-major order	// called by "sstd::bmat bMat; bool buf = bMat[0]; bool bMat[0] = buf;".
	class SwapByOneIndex  operator[](const  int& p){ return OpSwapByOneIndex(this, p); }							// col-major order	// called by "sstd::bmat bMat; bool buf = bMat[0]; bool bMat[0] = buf;".

	class SwapByTwoIndex  operator()(const uint& p, const uint& q){ return OpSwapByTwoIndex(this, p, q); }			// called by "sstd::bmat bMat; bool buf = bMat(0, 0); bool bMat(0, 0) = buf;".
	class SwapByTwoIndex  operator()(const  int& p, const uint& q){ return OpSwapByTwoIndex(this, p, q); }			// called by "sstd::bmat bMat; bool buf = bMat(0, 0); bool bMat(0, 0) = buf;".
	class SwapByTwoIndex  operator()(const uint& p, const  int& q){ return OpSwapByTwoIndex(this, p, q); }			// called by "sstd::bmat bMat; bool buf = bMat(0, 0); bool bMat(0, 0) = buf;".
	class SwapByTwoIndex  operator()(const  int& p, const  int& q){ return OpSwapByTwoIndex(this, p, q); }			// called by "sstd::bmat bMat; bool buf = bMat(0, 0); bool bMat(0, 0) = buf;".
};

//--------------------------------------------------------------------------------------------------------
