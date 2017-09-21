#pragma once

#include "macros.hpp"

#include <stdio.h>
#include <stdlib.h>
#include "../pdbg.hpp"
#include "../typeDef.h"

//--------------------------------------------------------------------------------------------------------

namespace sstd{ template <typename type> class typeMatrix; }
namespace tmat{
	template <typename type> void zeros(class sstd::typeMatrix<type>& Mat);
	template <typename type> void copy (class sstd::typeMatrix<type>& lhs, class sstd::typeMatrix<type>& rhs);
	template <typename type> void move (class sstd::typeMatrix<type>& lhs, class sstd::typeMatrix<type>& rhs);

	template <typename type> class sstd::typeMatrix<type> Tr(class sstd::typeMatrix<type>& rhs);		// lhs = Transpose(rhs)
	template <typename type> void                  Tr_myself(class sstd::typeMatrix<type>& rhs);		// Transpose(rhs)

	template <typename type> class sstd::typeMatrix<type>* copyRect(class sstd::typeMatrix<type>*& pMat, uint rowStart, uint rowEnd, uint colStart, uint colEnd);

	void print(class sstd::typeMatrix  <char>& Mat);
	void print(class sstd::typeMatrix <uchar>& Mat);
	void print(class sstd::typeMatrix   <int>& Mat);
	void print(class sstd::typeMatrix  <uint>& Mat);
	void print(class sstd::typeMatrix <float>& Mat);
	void print(class sstd::typeMatrix<double>& Mat);
}

//--------------------------------------------------------------------------------------------------------

#include "CopyRow.hpp"	// "namespace tmat{};" の後で include すること!!!
#include "CopyCol.hpp"	// "namespace tmat{};" の後で include すること!!!

//--------------------------------------------------------------------------------------------------------

template <typename type>
class sstd::typeMatrix{
private:
	type* MatX;
	uint rowNum;	// 行数
	uint colNum;	// 列数
	uint length;

public:
	inline typeMatrix(){ rowNum=0; colNum=0; length=0; MatX=0; }
	inline typeMatrix(class typeMatrix&  rhs){ rowNum=0; colNum=0; length=0; MatX=0; tmat::copy<type>(*this, rhs); }	// called by "tmat::tmat buf1(N, N), buf2; buf2 = buf1;" or "tmat::tmat buf1, buf2; buf2 = buf1;".
	inline typeMatrix(class typeMatrix&& rhs){ tmat::move<type>(*this, rhs); }	// called by "lhs = std::move(rhs);".
	inline typeMatrix(uint row, uint col){
		rowNum = row;
		colNum = col;
		length = row * col;
		MatX = (type*)malloc(sizeof(type)*length);
		sstd::pdbg_if_stop_exit(MatX==0, "ERROR: This pointer is not allocated.\n");
	}
	inline ~typeMatrix(){ free(MatX); }

	inline type* pMat(){ return MatX; }
	inline uint rows(){ return rowNum; }
	inline uint cols(){ return colNum; }
	inline uint len (){ return length; }

	// RW: read and write
	inline type*& pMat_RW(){ return MatX; }
	inline uint&  rows_RW(){ return rowNum; }
	inline uint&  cols_RW(){ return colNum; }
	inline uint&  len_RW (){ return length; }
	/*
	inline void MatX_write(type* rhs){ MatX = rhs; }
	inline void rows_write(uint rhs){ rowNum = rhs; }
	inline void cols_write(uint rhs){ colNum = rhs; }
	inline void len_write (uint rhs){ length = rhs; }
*/
	class typeMatrix& operator=(class typeMatrix rhs){ tmat::copy<type>(*this, rhs); return *this; }	// called by "lhs = tmat::tmat(3, 3);".

	type& operator[](uint p){ return MatX[      p]; }
	type& operator[]( int p){ return MatX[(uint)p]; }

	type& operator()(uint p, uint q){ return MatX[      p + rowNum*      q]; }
	type& operator()( int p, uint q){ return MatX[(uint)p + rowNum*      q]; }
	type& operator()(uint p,  int q){ return MatX[      p + rowNum*(uint)q]; }
	type& operator()( int p,  int q){ return MatX[(uint)p + rowNum*(uint)q]; }

	class CopyRow<type> operator()(uint p, const char c_dummy){ return OpCopyRow<type>(this, p, c_dummy); }
	class CopyRow<type> operator()( int p, const char c_dummy){ return OpCopyRow<type>(this, p, c_dummy); }

	class CopyCol<type> operator()(const char c_dummy, uint q){ return OpCopyCol<type>(this, c_dummy, q); }
	class CopyCol<type> operator()(const char c_dummy,  int q){ return OpCopyCol<type>(this, c_dummy, q); }
};
namespace sstd{
	template<typename T> using tmat = typeMatrix<T>; // almost same mean as "typedef tmat typeMatrix<T>"
}

//--------------------------------------------------------------------------------------------------------

template <typename type>
inline void tmat::zeros(class sstd::typeMatrix<type>& Mat){
	for(uint q=0; q<Mat.cols(); q++){
		for(uint p=0; p<Mat.rows(); p++){
			Mat(p, q) = (type)0;
		}
	}
}

//--------------------------------------------------------------------------------------------------------

template <typename type>
inline void copy_withoutAllocate(class sstd::typeMatrix<type>& lhs, class sstd::typeMatrix<type>& rhs){
	for(uint q=0; q<rhs.cols(); q++){
		for(uint p=0; p<rhs.rows(); p++){
			lhs(p, q) = rhs(p, q);
		}
	}
}
template <typename type>
inline void tmat::copy(class sstd::typeMatrix<type>& lhs, class sstd::typeMatrix<type>& rhs){

	if(lhs.len() != rhs.len()){
		free(lhs.pMat()); lhs.pMat_RW() = 0;
		if(rhs.len()!=0){ lhs.pMat_RW() = (type*)malloc(sizeof(type) * rhs.len()); }
	}

	lhs.rows_RW() = rhs.rows();
	lhs.cols_RW() = rhs.cols();
	lhs.len_RW()  = rhs.len();

	copy_withoutAllocate<type>(lhs, rhs);
}

//--------------------------------------------------------------------------------------------------------

template <typename type>
inline void tmat::move(class sstd::typeMatrix<type>& lhs, class sstd::typeMatrix<type>& rhs){

	lhs.rows_RW() = rhs.rows(); rhs.rows_RW() = 0;
	lhs.cols_RW() = rhs.cols(); rhs.cols_RW() = 0;
	lhs.len_RW()  = rhs.len();  rhs.len_RW()  = 0;

	free(lhs.pMat());
	lhs.pMat_RW() = rhs.pMat();
	rhs.pMat_RW() = 0;
}

//--------------------------------------------------------------------------------------------------------

template <typename type>
class sstd::typeMatrix<type> tmat::Tr(class sstd::typeMatrix<type>& rhs){
	class sstd::typeMatrix<type> lhs(rhs.cols(), rhs.rows());
	for(uint q=0; q<rhs.cols(); q++){
		for(uint p=0; p<rhs.rows(); p++){
			lhs(q, p) = rhs(p, q);
		}
	}
	return lhs;
}
template <typename type>
void tmat::Tr_myself(class sstd::typeMatrix<type>& rhs){
	class sstd::typeMatrix<type> lhs = tmat::Tr(rhs);
	tmat::move(rhs, lhs);
}

//--------------------------------------------------------------------------------------------------------

template <typename type>
inline class sstd::typeMatrix<type>* tmat::copyRect(class sstd::typeMatrix<type>*& pMat, uint rowStart, uint rowEnd, uint colStart, uint colEnd){

	class sstd::typeMatrix<type>* pMatBuf = new sstd::typeMatrix<type>(rowEnd-rowStart, colEnd-colStart);

	for(uint q=0; q<(colEnd-colStart); q++){
		for(uint p=0; p<(rowEnd-rowStart); p++){
			(*pMatBuf)(p, q) = (*pMat)(p+rowStart, q+colStart);
		}
	}

	return pMatBuf;
}

//--------------------------------------------------------------------------------------------------------

