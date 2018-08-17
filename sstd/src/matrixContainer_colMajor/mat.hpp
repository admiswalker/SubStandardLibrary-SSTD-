#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <initializer_list>
#include "./mat_operators.hpp"
#include "./mat_elements.hpp" // for element operations (elements multiplication)
#include "../math.hpp"
#include "../pdbg.hpp"
#include "../typeDef.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
	template <typename T> class mat;
	template <typename T> void copy(sstd::mat<T>& lhs, const sstd::mat<T>& rhs);
	template <typename T> void move(sstd::mat<T>& lhs,       sstd::mat<T>& rhs);
	template <typename T> void swap(sstd::mat<T>& lhs,       sstd::mat<T>& rhs);

	template <typename T> void   eye(sstd::mat<T>& rhs);
	template <typename T> void  ones(sstd::mat<T>& rhs);
	template <typename T> void zeros(sstd::mat<T>& mat);
	template <typename T> sstd::mat<T> Tr       (sstd::mat<T>& rhs); // lhs = Transpose(rhs)
	template <typename T> void         Tr_myself(sstd::mat<T>& rhs); // Transpose(rhs)
	template <typename T> sstd::mat<T>* copyRect(sstd::mat<T>*& pMat, const uint& rowStart, const uint& rowEnd, const uint& colStart, const uint& colEnd);
	
	void print(const sstd::mat<       bool>& mat);
	void print(const sstd::mat<       char>& mat);
//	void print(const sstd::mat<      uchar>& mat); // same as uint8
	void print(const sstd::mat<       int8>& mat);
	void print(const sstd::mat<      int16>& mat);
	void print(const sstd::mat<      int32>& mat);
	void print(const sstd::mat<      int64>& mat);
	void print(const sstd::mat<      uint8>& mat);
	void print(const sstd::mat<     uint16>& mat);
	void print(const sstd::mat<     uint32>& mat);
	void print(const sstd::mat<     uint64>& mat);
	void print(const sstd::mat<      float>& mat);
	void print(const sstd::mat<     double>& mat);
	void print(const sstd::mat<std::string>& mat);
	
	// for sstd::printn(); and sstd::printn_all();.
	void for_printn(const sstd::mat<       bool>& mat);
	void for_printn(const sstd::mat<       char>& mat);
//	void for_printn(const sstd::mat<      uchar>& mat); // same as uint8
	void for_printn(const sstd::mat<       int8>& mat);
	void for_printn(const sstd::mat<      int16>& mat);
	void for_printn(const sstd::mat<      int32>& mat);
	void for_printn(const sstd::mat<      int64>& mat);
	void for_printn(const sstd::mat<      uint8>& mat);
	void for_printn(const sstd::mat<     uint16>& mat);
	void for_printn(const sstd::mat<     uint32>& mat);
	void for_printn(const sstd::mat<     uint64>& mat);
	void for_printn(const sstd::mat<      float>& mat);
	void for_printn(const sstd::mat<     double>& mat);
	void for_printn(const sstd::mat<std::string>& mat);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

#include "CopyRow.hpp"	// "namespace mat{};" の後で include すること!!!
#include "CopyCol.hpp"	// "namespace mat{};" の後で include すること!!!

//-----------------------------------------------------------------------------------------------------------------------------------------------

// type matrix: (col-major)
template <typename T>
class sstd::mat{
private:
	T* MatX;
	uint rowNum;	// 行数
	uint colNum;	// 列数
	uint length;

public:
	inline mat(){ rowNum=0; colNum=0; length=0; MatX=0; }
	inline mat(const std::initializer_list<std::initializer_list<T>>& rhs){ // ={{1, 2, 3}, {4, 5, 6}, {7, 8, 9}} の初期化形式
		rowNum=rhs.size();
		if(rowNum==0){ colNum=0; length=0; return; }
		colNum=(rhs.begin()[0]).size();
		length=rowNum*colNum;
		MatX = new T[length];
		
		const std::initializer_list<T>* pRhs=rhs.begin();
		for(uint p=0; p<rowNum; p++){
			const T* ppRhs=pRhs[p].begin();
			for(uint q=0; q<colNum; q++){
				if(q>=pRhs[p].size()){break;}
				MatX[p+q*rowNum]=ppRhs[q];
			}
		}
	}
	inline mat(const class mat&  rhs){ rowNum=0; colNum=0; length=0; MatX=0; sstd::copy<T>(*this, rhs); } // called by "sstd::mat_r buf1(N, N); sstd::mat_r buf2(buf1);"
	inline mat(      class mat&& rhs){ rowNum=0; colNum=0; length=0; MatX=0; sstd::move<T>(*this, rhs); } // called by "return std::move(rhs);" or "std::swap(buf1, buf2)".
	// std::move(lhs, rhs): "move to uninitalized object" will be called.
	// std::swap(lhs, rhs): "move to uninitalized object" -> "copy to lhs or rhs" -> "copy to lhs or rhs" will be called.
	inline mat(const uint& row, const uint& col){
		rowNum = row;
		colNum = col;
		length = row * col;
		MatX = new T[length];
		if(MatX==0){ sstd::pdbg("ERROR: This pointer is not allocated.\n"); }
	}
	inline ~mat(){ delete[] MatX; }
	
	// R: read only
	inline const uint& rows() const { return rowNum; }
	inline const uint& cols() const { return colNum; }
	inline const uint& len () const { return length; }

	// RW: read and write
	inline T*& pMat_RW(){ return MatX; }
	inline uint& rows_RW(){ return rowNum; }
	inline uint& cols_RW(){ return colNum; }
	inline uint& len_RW (){ return length; }

	class mat& operator=(const class mat& rhs){ sstd::copy<T>(*this, rhs); return *this; }	// called by "lhs = mat::mat(3, 3);".
	
	T& operator[](const uint& p)       { return MatX[      p]; }
	T& operator[](const  int& p)       { return MatX[(uint)p]; }
	T  operator[](const uint& p) const { return MatX[      p]; }
	T  operator[](const  int& p) const { return MatX[(uint)p]; }
	
	T& operator()(const uint& p, const uint& q)       { return MatX[      p + rowNum*      q]; }
	T& operator()(const  int& p, const uint& q)       { return MatX[(uint)p + rowNum*      q]; }
	T& operator()(const uint& p, const  int& q)       { return MatX[      p + rowNum*(uint)q]; }
	T& operator()(const  int& p, const  int& q)       { return MatX[(uint)p + rowNum*(uint)q]; }
	T  operator()(const uint& p, const uint& q) const { return MatX[      p + rowNum*      q]; }
	T  operator()(const  int& p, const uint& q) const { return MatX[(uint)p + rowNum*      q]; }
	T  operator()(const uint& p, const  int& q) const { return MatX[      p + rowNum*(uint)q]; }
	T  operator()(const  int& p, const  int& q) const { return MatX[(uint)p + rowNum*(uint)q]; }
	
	class CopyRow<T> operator()(const uint& p, const char& c_dummy){ return OpCopyRow<T>(this, p, c_dummy); }
	class CopyRow<T> operator()(const  int& p, const char& c_dummy){ return OpCopyRow<T>(this, p, c_dummy); }
	
	class CopyCol<T> operator()(const char& c_dummy, const uint& q){ return OpCopyCol<T>(this, c_dummy, q); }
	class CopyCol<T> operator()(const char& c_dummy, const  int& q){ return OpCopyCol<T>(this, c_dummy, q); }
	
	// for element operations (elements multiplication)
	inline sstd::mat_elements<T> operator()(){ return sstd::mat_elements<T>((const T*&)MatX, (const uint&)rowNum, (const uint&)colNum, (const uint&)length); }
	inline sstd::mat_elements<T>        vec(){ return sstd::mat_elements<T>((const T*&)MatX, (const uint&)rowNum, (const uint&)colNum, (const uint&)length); }
};

//-----------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline void sstd::eye(sstd::mat<T>& rhs){
	for(uint q=0; q<rhs.cols(); q++){
		for(uint p=0; p<rhs.rows(); p++){
			if(p!=q){ rhs(p, q)=(T)0;
			}  else { rhs(p, q)=(T)1; }
		}
	}
}

template <typename T>
inline void sstd::ones(sstd::mat<T>& rhs){
	for(uint p=0; p<rhs.len(); p++){ rhs[p]=(T)1; }
}

template <typename T>
inline void sstd::zeros(sstd::mat<T>& mat){
	for(uint p=0; p<mat.len(); p++){ mat[p]=(T)0; }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline void copy_withoutAllocate(sstd::mat<T>& lhs, const sstd::mat<T>& rhs){
	for(uint q=0; q<rhs.cols(); q++){
		for(uint p=0; p<rhs.rows(); p++){
			lhs(p, q) = rhs(p, q);
		}
	}
}
template <typename T>
inline void sstd::copy(sstd::mat<T>& lhs, const sstd::mat<T>& rhs){

	if(lhs.len() != rhs.len()){
		free(lhs.pMat_RW()); lhs.pMat_RW() = 0;
		if(rhs.len()!=0){ lhs.pMat_RW() = (T*)malloc(sizeof(T) * rhs.len()); }
	}

	lhs.rows_RW() = rhs.rows();
	lhs.cols_RW() = rhs.cols();
	lhs.len_RW()  = rhs.len();
	
	copy_withoutAllocate<T>(lhs, rhs);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline void sstd::move(sstd::mat<T>& lhs, sstd::mat<T>& rhs){

	lhs.rows_RW() = rhs.rows(); rhs.rows_RW() = 0;
	lhs.cols_RW() = rhs.cols(); rhs.cols_RW() = 0;
	lhs.len_RW()  = rhs.len();  rhs.len_RW()  = 0;

	free(lhs.pMat_RW());
	lhs.pMat_RW() = rhs.pMat_RW();
	rhs.pMat_RW() = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
void swap(sstd::mat<T>& lhs, sstd::mat<T>& rhs){

	uint rowsBuf=lhs.rows(); lhs.rows_RW()=rhs.rows(); rhs.rows_RW()=rowsBuf;
	uint colsBuf=lhs.cols(); lhs.cols_RW()=rhs.cols(); rhs.cols_RW()=colsBuf;
	uint lenBuf=lhs.len(); lhs.len_RW()=rhs.len(); rhs.len_RW()=lenBuf;
	
	T* pMatBuf=lhs.pMat(); lhs.pMat_RW()=rhs.pMat(); rhs.pMat_RW()=pMatBuf;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
sstd::mat<T> sstd::Tr(sstd::mat<T>& rhs){
	sstd::mat<T> lhs(rhs.cols(), rhs.rows());
	for(uint q=0; q<rhs.cols(); q++){
		for(uint p=0; p<rhs.rows(); p++){
			lhs(q, p) = rhs(p, q);
		}
	}
	return lhs;
}
template <typename T>
void sstd::Tr_myself(sstd::mat<T>& rhs){
	sstd::mat<T> lhs = sstd::Tr(rhs);
	sstd::move(rhs, lhs);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
inline sstd::mat<T>* sstd::copyRect(sstd::mat<T>*& pMat, const uint& rowStart, const uint& rowEnd, const uint& colStart, const uint& colEnd){

	sstd::mat<T>* pMatBuf = new sstd::mat<T>(rowEnd-rowStart, colEnd-colStart);

	for(uint q=0; q<(colEnd-colStart); q++){
		for(uint p=0; p<(rowEnd-rowStart); p++){
			(*pMatBuf)(p, q) = (*pMat)(p+rowStart, q+colStart);
		}
	}

	return pMatBuf;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
