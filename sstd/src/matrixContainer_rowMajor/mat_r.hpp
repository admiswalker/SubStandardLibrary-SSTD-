#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <initializer_list>
#include "../pdbg.hpp"
#include "../typeDef.h"

//--------------------------------------------------------------------------------------------------------

namespace sstd{
	template <typename T> class mat_r;
	template <typename T> void copy(class sstd::mat_r<T>& lhs, const class sstd::mat_r<T>& rhs);
	template <typename T> void move(class sstd::mat_r<T>& lhs,       class sstd::mat_r<T>& rhs);
	template <typename T> void swap(class sstd::mat_r<T>& lhs,       class sstd::mat_r<T>& rhs);

	template <typename T> void zeros(class sstd::mat_r<T>& Mat);
	template <typename T> class sstd::mat_r<T> Tr(class sstd::mat_r<T>& rhs);		// lhs = Transpose(rhs)
	template <typename T> void          Tr_myself(class sstd::mat_r<T>& rhs);		// Transpose(rhs)

	template <typename T> class sstd::mat_r<T>* copyRect(class sstd::mat_r<T>*& pMat, const uint& rowStart, const uint& rowEnd, const uint& colStart, const uint& colEnd);
	
	void print(const class sstd::mat_r<       bool>& Mat);
	void print(const class sstd::mat_r<       char>& Mat);
//	void print(const class sstd::mat_r<      uchar>& Mat); // same as uint8
	void print(const class sstd::mat_r<       int8>& Mat);
	void print(const class sstd::mat_r<      int16>& Mat);
	void print(const class sstd::mat_r<      int32>& Mat);
	void print(const class sstd::mat_r<      int64>& Mat);
	void print(const class sstd::mat_r<      uint8>& Mat);
	void print(const class sstd::mat_r<     uint16>& Mat);
	void print(const class sstd::mat_r<     uint32>& Mat);
	void print(const class sstd::mat_r<     uint64>& Mat);
	void print(const class sstd::mat_r<      float>& Mat);
	void print(const class sstd::mat_r<     double>& Mat);
	void print(const class sstd::mat_r<std::string>& Mat);
	
	// for sstd::printn(); and sstd::printn_all();.
	void for_printn(const class sstd::mat_r<       bool>& tMat);
	void for_printn(const class sstd::mat_r<       char>& tMat);
//	void for_printn(const class sstd::mat_r<      uchar>& tMat); // same as uint8
	void for_printn(const class sstd::mat_r<       int8>& tMat);
	void for_printn(const class sstd::mat_r<      int16>& tMat);
	void for_printn(const class sstd::mat_r<      int32>& tMat);
	void for_printn(const class sstd::mat_r<      int64>& tMat);
	void for_printn(const class sstd::mat_r<      uint8>& tMat);
	void for_printn(const class sstd::mat_r<     uint16>& tMat);
	void for_printn(const class sstd::mat_r<     uint32>& tMat);
	void for_printn(const class sstd::mat_r<     uint64>& tMat);
	void for_printn(const class sstd::mat_r<      float>& tMat);
	void for_printn(const class sstd::mat_r<     double>& tMat);
	void for_printn(const class sstd::mat_r<std::string>& tMat);
}

//--------------------------------------------------------------------------------------------------------

#include "CopyRow_r.hpp"	// "namespace tmat_r{};" の後で include すること!!!
#include "CopyCol_r.hpp"	// "namespace tmat_r{};" の後で include すること!!!

//--------------------------------------------------------------------------------------------------------

// type martix (row major)
template <typename T>
class sstd::mat_r{
private:
	T* MatX;
	uint rowNum;	// 行数
	uint colNum;	// 列数
	uint length;

public:
	inline mat_r(){ rowNum=0; colNum=0; length=0; MatX=0; }
	inline mat_r(const std::initializer_list<std::initializer_list<T>>& rhs){ // ={{1, 2, 3}, {4, 5, 6}, {7, 8, 9}} の初期化形式
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
				MatX[p*colNum+q]=ppRhs[q];
			}
		}
	}
	inline mat_r(const class mat_r&  rhs){ rowNum=0; colNum=0; length=0; MatX=0; sstd::copy<T>(*this, rhs); }	// called by "sstd::tmat_r buf1(N, N); sstd::tmat_r buf2(buf1);"
	inline mat_r(      class mat_r&& rhs){ rowNum=0; colNum=0; length=0; MatX=0; sstd::move<T>(*this, rhs); }	// called by "return std::move(rhs);" or "std::swap(buf1, buf2)".
	// std::move(lhs, rhs): "move to uninitalized object" will be called.
	// std::swap(lhs, rhs): "move to uninitalized object" -> "copy to lhs or rhs" -> "copy to lhs or rhs" will be called.
	inline mat_r(const uint& row, const uint& col){
		rowNum = row;
		colNum = col;
		length = row * col;
		MatX = new T[length];
		sstd::pdbg_if_stop_exit(MatX==0, "ERROR: This pointer is not allocated.\n");
	}
	inline ~mat_r(){ delete[] MatX; }

	// R: read only
	inline const uint& rows() const { return rowNum; }
	inline const uint& cols() const { return colNum; }
	inline const uint& len () const { return length; }

	// RW: read and write
	inline T*& pMat_RW(){ return MatX; }
	inline uint&  rows_RW(){ return rowNum; }
	inline uint&  cols_RW(){ return colNum; }
	inline uint&  len_RW (){ return length; }

	class mat_r& operator=(const class mat_r& rhs){ sstd::copy<T>(*this, rhs); return *this; }	// called by "lhs = tmat_r::tmat_r(3, 3);".

	T& operator[](const uint& q)       { return MatX[      q]; }
	T& operator[](const  int& q)       { return MatX[(uint)q]; }
	T  operator[](const uint& q) const { return MatX[      q]; }
	T  operator[](const  int& q) const { return MatX[(uint)q]; }

	T& operator()(const uint& p, const uint& q)       { return MatX[colNum*      p +       q]; }
	T& operator()(const  int& p, const uint& q)       { return MatX[colNum*(uint)p +       q]; }
	T& operator()(const uint& p, const  int& q)       { return MatX[colNum*      p + (uint)q]; }
	T& operator()(const  int& p, const  int& q)       { return MatX[colNum*(uint)p + (uint)q]; }
	T  operator()(const uint& p, const uint& q) const { return MatX[colNum*      p +       q]; }
	T  operator()(const  int& p, const uint& q) const { return MatX[colNum*(uint)p +       q]; }
	T  operator()(const uint& p, const  int& q) const { return MatX[colNum*      p + (uint)q]; }
	T  operator()(const  int& p, const  int& q) const { return MatX[colNum*(uint)p + (uint)q]; }

	class CopyRow_r<T> operator()(const uint& p, const char& c_dummy){ return OpCopyRow_r<T>(this, p, c_dummy); }
	class CopyRow_r<T> operator()(const  int& p, const char& c_dummy){ return OpCopyRow_r<T>(this, p, c_dummy); }

	class CopyCol_r<T> operator()(const char& c_dummy, const uint& q){ return OpCopyCol_r<T>(this, c_dummy, q); }
	class CopyCol_r<T> operator()(const char& c_dummy, const  int& q){ return OpCopyCol_r<T>(this, c_dummy, q); }
};

//--------------------------------------------------------------------------------------------------------

template <typename T>
inline void sstd::zeros(class sstd::mat_r<T>& mat){
	for(uint p=0; p<mat.len(); p++){ mat[p]=(T)0; }
}

//--------------------------------------------------------------------------------------------------------

template <typename T>
inline void copy_withoutAllocate(class sstd::mat_r<T>& lhs, const class sstd::mat_r<T>& rhs){
	for(uint p=0; p<rhs.rows(); p++){
		for(uint q=0; q<rhs.cols(); q++){
			lhs(p, q) = rhs(p, q);
		}
	}
}
template <typename T>
inline void sstd::copy(class sstd::mat_r<T>& lhs, const class sstd::mat_r<T>& rhs){

	if(lhs.len() != rhs.len()){
		free(lhs.pMat_RW()); lhs.pMat_RW() = 0;
		if(rhs.len()!=0){ lhs.pMat_RW() = (T*)malloc(sizeof(T) * rhs.len()); }
	}

	lhs.rows_RW() = rhs.rows();
	lhs.cols_RW() = rhs.cols();
	lhs.len_RW()  = rhs.len();

	copy_withoutAllocate<T>(lhs, rhs);
}

//--------------------------------------------------------------------------------------------------------

template <typename T>
inline void sstd::move(class sstd::mat_r<T>& lhs, class sstd::mat_r<T>& rhs){
	lhs.rows_RW() = rhs.rows(); rhs.rows_RW() = 0;
	lhs.cols_RW() = rhs.cols(); rhs.cols_RW() = 0;
	lhs.len_RW()  = rhs.len();  rhs.len_RW()  = 0;

	free(lhs.pMat_RW());
	lhs.pMat_RW() = rhs.pMat_RW();
	rhs.pMat_RW() = 0;
}

//--------------------------------------------------------------------------------------------------------

template <typename T>
void swap(class sstd::mat_r<T>& lhs, class sstd::mat_r<T>& rhs){
	uint rowsBuf=lhs.rows(); lhs.rows_RW()=rhs.rows(); rhs.rows_RW()=rowsBuf;
	uint colsBuf=lhs.cols(); lhs.cols_RW()=rhs.cols(); rhs.cols_RW()=colsBuf;
	uint lenBuf=lhs.len(); lhs.len_RW()=rhs.len(); rhs.len_RW()=lenBuf;
	
	T* pMatBuf=lhs.pMat(); lhs.pMat_RW()=rhs.pMat(); rhs.pMat_RW()=pMatBuf;
}

//--------------------------------------------------------------------------------------------------------

template <typename T>
class sstd::mat_r<T> sstd::Tr(class sstd::mat_r<T>& rhs){
	class sstd::mat_r<T> lhs(rhs.cols(), rhs.rows());
	for(uint p=0; p<rhs.rows(); p++){
		for(uint q=0; q<rhs.cols(); q++){
			lhs(q, p) = rhs(p, q);
		}
	}
	return lhs;
}
template <typename T>
void sstd::Tr_myself(class sstd::mat_r<T>& rhs){
	class sstd::mat_r<T> lhs = sstd::Tr(rhs);
	sstd::move(rhs, lhs);
}

//--------------------------------------------------------------------------------------------------------

template <typename T>
inline class sstd::mat_r<T>* sstd::copyRect(class sstd::mat_r<T>*& pMat, const uint& rowStart, const uint& rowEnd, const uint& colStart, const uint& colEnd){

	class sstd::mat_r<T>* pMatBuf = new sstd::mat_r<T>(rowEnd-rowStart, colEnd-colStart);

	for(uint p=0; p<(rowEnd-rowStart); p++){
		for(uint q=0; q<(colEnd-colStart); q++){
			(*pMatBuf)(p, q) = (*pMat)(p+rowStart, q+colStart);
		}
	}

	return pMatBuf;
}

//--------------------------------------------------------------------------------------------------------

