#pragma once

#include "./macros.hpp"

#include <iostream>
#include "../typeDef.h"
#include "../MatrixStore_tmat/tmat.hpp"

// 8x8 bit matrix is column-major order, 
// and outside of the 8x8 martix is row-major order.

//--------------------------------------------------------------------------------------------------------

namespace sstd{ class bitMatrix; }
namespace bmat{
	
	void copy(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs);
	void move(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs);

	void printBitMatrix    (class sstd::bitMatrix bMat);	//	Called by "printbm()" macro.
	void printBitMatrix_all(class sstd::bitMatrix bMat);	//	Called by "printbm_all()" macro.

	void                   eye(class sstd::bitMatrix& bMat);
	void                  ones(class sstd::bitMatrix& bMat);
	void                 zeros(class sstd::bitMatrix& bMat);
	class sstd::bitMatrix   eye(uint row, uint col);
	class sstd::bitMatrix  ones(uint row, uint col);
	class sstd::bitMatrix zeros(uint row, uint col);
	class sstd::bitMatrix   eye(uint size);
	class sstd::bitMatrix  ones(uint size);
	class sstd::bitMatrix zeros(uint size);

	class sstd::bitMatrix LxShiftMat(uint size, uint xShift);	// square matrix [size x size]
	class sstd::bitMatrix RxShiftMat(uint size, uint xShift);	// square matrix [size x size]

	class sstd::bitMatrix       Tr(class sstd::bitMatrix& rhs);								// lhs = Transpose(rhs)
	void                Tr_myself(class sstd::bitMatrix& rhs);								// Transpose(rhs)

	class sstd::bitMatrix      add(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs);	// lhs + rhs (XOR)
	class sstd::bitMatrix      mul(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs);	// lhs * rhs
	class sstd::bitMatrix      pow(class sstd::bitMatrix  base, uint64 exponent);		    	// base^{exponent}
	void               add_myself(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs);	// lhs += rhs (XOR)
	void               mul_myself(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs);	// lhs *= rhs
	void               pow_myself(class sstd::bitMatrix& base, uint64 exponent);				// lhs ^= exponent

	class sstd::bitMatrix     and_(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs);	// lhs & rhs (AND)	// _ を付加しないと，何かと名前が衝突した．
	class sstd::bitMatrix      or_(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs);	// lhs | rhs (OR)	// _ を付加しないと，何かと名前が衝突した．
	class sstd::bitMatrix     not_(class sstd::bitMatrix& rhs);								// ~rhs (NOT)		// _ を付加しないと，何かと名前が衝突した．
	class sstd::bitMatrix     xor_(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs);	// lhs + rhs (XOR)	// _ を付加しないと，何かと名前が衝突した．
	void               and_myself(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs);	// lhs & rhs (AND)
	void                or_myself(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs);	// lhs | rhs (OR)

	bool                       eq(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs);	// lhs == rhs
	bool                       ne(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs);	// lhs != rhs

	class sstd::bitMatrix  REShift(class sstd::bitMatrix& rhs, uint ShiftNum);				// RightExpansionShift	// 行列拡大右シフト
	class sstd::bitMatrix  DEShift(class sstd::bitMatrix& rhs, uint ShiftNum);				// DownExpansionShift	// 行列拡大下シフト
	class sstd::bitMatrix horzcat2(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs);	// lhs << rhs
	class sstd::bitMatrix vertcat2(class sstd::bitMatrix&  us, class sstd::bitMatrix&  ds);	// us && ds    // upside, downside.
//	class sstd::bitMatrix horzcat (class sstd::bitMatrix& ...);	// horzcat(...)				// 可変長引数での受け渡し
//	class sstd::bitMatrix vertcat (class sstd::bitMatrix& ...);	// vertcat(...)				// 可変長引数での受け渡し

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

#include "./SwapByOneIndex.hpp"	// "namespace bmxs{};" の後 かつ "class bmxs::bitMatrix" で include すること!!!
#include "./SwapByTwoIndex.hpp"	// "namespace bmxs{};" の後 かつ "class bmxs::bitMatrix" で include すること!!!

//--------------------------------------------------------------------------------------------------------

class sstd::bitMatrix{
private:
public:
	uint rows;	// 行数 // たぶん一般的には，private へ入れて，誤って書き換えされてないようにするべき．値はpublic 関数から return して取得．(要修正)
	uint cols;	// 列数 // たぶん一般的には，private へ入れて，誤って書き換えされてないようにするべき．値はpublic 関数から return して取得．(要修正)
	sstd::typeMatrix<uint64> bMat8x8;	// 8x8 の BitMartix 行列の集合

	bitMatrix(): rows(0), cols(0) {}
	bitMatrix(uint row, uint col): rows(row), cols(col), bMat8x8((rows-1)/8+1, (cols-1)/8+1) {}
	bitMatrix(bitMatrix&  rhs): rows(0), cols(0) { bmat::copy(*this, rhs); } // called by "sstd::bitMatrix buf1(N, N), buf2; buf2 = buf1;" or "sstd::bitMatrix buf1, buf2; buf2 = buf1;".
	bitMatrix(bitMatrix&& rhs){ bmat::move(*this, rhs); } // called by "lhs = std::move(rhs);".
	~bitMatrix(){}

	class bitMatrix& operator= (class bitMatrix rhs){ bmat::copy(*this, rhs); return *this; }		// called by "lhs = bmat::add(A, B);".
	class bitMatrix  operator+ (class bitMatrix rhs){ return bmat::add(*this, rhs); }				// called by "lhs + rhs;".	// XOR
	class bitMatrix  operator* (class bitMatrix rhs){ return bmat::mul(*this, rhs); }				// called by "lhs * rhs;".	// mul
	class bitMatrix  operator^ (uint64 rhs)              { return bmat::pow(*this, rhs); }				// called by "lhs ^ rhs;".	// pow (not XOR)

	class bitMatrix  operator& (class bitMatrix rhs){ return bmat::and_(*this, rhs); }				// called by "lhs & rhs;".	// AND
	class bitMatrix  operator| (class bitMatrix rhs){ return bmat::or_ (*this, rhs); }				// called by "lhs | rhs;".	//  OR
	class bitMatrix  operator~ ()                        { return bmat::not_(*this);      }				// called by "~rhs;".		// NOT

	class bitMatrix& operator+=(class bitMatrix rhs){ bmat::add_myself(*this, rhs); return *this; }	// called by "lhs += rhs;".
	class bitMatrix& operator*=(class bitMatrix rhs){ bmat::mul_myself(*this, rhs); return *this; }	// called by "lhs *= rhs;".
	class bitMatrix& operator^=(uint64 rhs)              { bmat::pow_myself(*this, rhs); return *this; }	// called by "lhs ^= rhs;".
	class bitMatrix& operator&=(class bitMatrix rhs){ bmat::and_myself(*this, rhs); return *this; }	// called by "lhs &= rhs;".
	class bitMatrix& operator|=(class bitMatrix rhs){ bmat::or_myself (*this, rhs); return *this; }	// called by "lhs |= rhs;".

	bool                  operator==(class bitMatrix rhs){ return bmat::eq(*this, rhs); }				// called by "sstd::bitMatrix bMatA, bMatB; if(bMatA == bMatB){printf("same\n");}else{printf("different\n");}".
	bool                  operator!=(class bitMatrix rhs){ return bmat::ne(*this, rhs); }				// called by "sstd::bitMatrix bMatA, bMatB; if(bMatA == bMatB){printf("same\n");}else{printf("different\n");}".

	class bitMatrix  operator<<(class bitMatrix rhs){ return bmat::horzcat2(*this, rhs); }			// called by "sstd::bitMatrix bMatA, bMatB, bMatC; bMatC = bMatA << bMatB;". // Horizontal connection of matrix.
	class bitMatrix  operator&&(class bitMatrix  ds){ return bmat::vertcat2(*this,  ds); }			// called by "sstd::bitMatrix bMatA, bMatB, bMatC; bMatC = bMatA && bMatB;". // Vertical connection of matrix.

	class SwapByOneIndex  operator[](uint p){ return OpSwapByOneIndex(this, p); }	// col-major order	// called by "sstd::bitMatrix bMat; bool buf = bMat[0]; bool bMat[0] = buf;".
	class SwapByOneIndex  operator[]( int p){ return OpSwapByOneIndex(this, p); }	// col-major order	// called by "sstd::bitMatrix bMat; bool buf = bMat[0]; bool bMat[0] = buf;".

	class SwapByTwoIndex  operator()(uint p, uint q){ return OpSwapByTwoIndex(this, p, q); }			// called by "sstd::bitMatrix bMat; bool buf = bMat(0, 0); bool bMat(0, 0) = buf;".
	class SwapByTwoIndex  operator()( int p, uint q){ return OpSwapByTwoIndex(this, p, q); }			// called by "sstd::bitMatrix bMat; bool buf = bMat(0, 0); bool bMat(0, 0) = buf;".
	class SwapByTwoIndex  operator()(uint p,  int q){ return OpSwapByTwoIndex(this, p, q); }			// called by "sstd::bitMatrix bMat; bool buf = bMat(0, 0); bool bMat(0, 0) = buf;".
	class SwapByTwoIndex  operator()( int p,  int q){ return OpSwapByTwoIndex(this, p, q); }			// called by "sstd::bitMatrix bMat; bool buf = bMat(0, 0); bool bMat(0, 0) = buf;".
};
namespace sstd{
	using bmat = bitMatrix; // almost same mean as "typedef bmat bitMatrix"
}

//--------------------------------------------------------------------------------------------------------
