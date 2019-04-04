﻿#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <initializer_list>
#include "./mat_r_operators.hpp"
#include "./mat_r_elements.hpp" // for element operations (elements multiplication)
#include "../math.hpp"
#include "../pdbg.hpp"
#include "../typeDef.h"

//--------------------------------------------------------------------------------------------------------

namespace sstd{
	template <typename T> class mat_r;
	template <typename T> void copy(sstd::mat_r<T>& lhs, const sstd::mat_r<T>& rhs);
	template <typename T> void move(sstd::mat_r<T>& lhs,       sstd::mat_r<T>& rhs);
	template <typename T> void swap(sstd::mat_r<T>& lhs,       sstd::mat_r<T>& rhs);
	
	template <typename T> void   eye(sstd::mat_r<T>& rhs);
	template <typename T> void  ones(sstd::mat_r<T>& rhs);
	template <typename T> void zeros(sstd::mat_r<T>& Mat);
	template <typename T> sstd::mat_r<T> Tr        (sstd::mat_r<T>& rhs); // lhs = Transpose(rhs)
	template <typename T> void           Tr_myself(sstd::mat_r<T>& rhs); // Transpose(rhs)
	template <typename T> sstd::mat_r<T>* copyRect(sstd::mat_r<T>*& pMat, const uint& rowStart, const uint& rowEnd, const uint& colStart, const uint& colEnd);
	
	void print(const sstd::mat_r<       bool>& Mat);
	void print(const sstd::mat_r<       char>& Mat);
//	void print(const sstd::mat_r<      uchar>& Mat); // same as uint8
	void print(const sstd::mat_r<       int8>& Mat);
	void print(const sstd::mat_r<      int16>& Mat);
	void print(const sstd::mat_r<      int32>& Mat);
	void print(const sstd::mat_r<      int64>& Mat);
	void print(const sstd::mat_r<      uint8>& Mat);
	void print(const sstd::mat_r<     uint16>& Mat);
	void print(const sstd::mat_r<     uint32>& Mat);
	void print(const sstd::mat_r<     uint64>& Mat);
	void print(const sstd::mat_r<      float>& Mat);
	void print(const sstd::mat_r<     double>& Mat);
	void print(const sstd::mat_r<std::string>& Mat);
	
	// for sstd::printn(); and sstd::printn_all();.
	void for_printn(const sstd::mat_r<       bool>& tMat);
	void for_printn(const sstd::mat_r<       char>& tMat);
//	void for_printn(const sstd::mat_r<      uchar>& tMat); // same as uint8
	void for_printn(const sstd::mat_r<       int8>& tMat);
	void for_printn(const sstd::mat_r<      int16>& tMat);
	void for_printn(const sstd::mat_r<      int32>& tMat);
	void for_printn(const sstd::mat_r<      int64>& tMat);
	void for_printn(const sstd::mat_r<      uint8>& tMat);
	void for_printn(const sstd::mat_r<     uint16>& tMat);
	void for_printn(const sstd::mat_r<     uint32>& tMat);
	void for_printn(const sstd::mat_r<     uint64>& tMat);
	void for_printn(const sstd::mat_r<      float>& tMat);
	void for_printn(const sstd::mat_r<     double>& tMat);
	void for_printn(const sstd::mat_r<std::string>& tMat);
}

//--------------------------------------------------------------------------------------------------------

#include "CopyRow_r.hpp"	// "namespace tmat_r{};" の後で include すること!!!
#include "CopyCol_r.hpp"	// "namespace tmat_r{};" の後で include すること!!!

//--------------------------------------------------------------------------------------------------------

// type martix (row major)
template <typename T>
class sstd::mat_r{
private:
	T* pMatT;
	uint rowSize;
	uint colSize;
	uint elems; // number of elements

public:
	inline mat_r(){ rowSize=0; colSize=0; elems=0; pMatT=0; }
	inline mat_r(const std::initializer_list<std::initializer_list<T>>& rhs){ // ={{1, 2, 3}, {4, 5, 6}, {7, 8, 9}} の初期化形式
		rowSize=rhs.size();
		if(rowSize==0){ colSize=0; elems=0; return; }
		colSize=(rhs.begin()[0]).size();
		elems=rowSize*colSize;
		pMatT = new T[elems];
		
		const std::initializer_list<T>* pRhs=rhs.begin();
		for(uint p=0; p<rowSize; p++){
			const T* ppRhs=pRhs[p].begin();
			for(uint q=0; q<colSize; q++){
				if(q>=pRhs[p].size()){break;}
				pMatT[p*colSize+q]=ppRhs[q];
			}
		}
	}
	inline mat_r(const class mat_r&  rhs){ rowSize=0; colSize=0; elems=0; pMatT=0; sstd::copy<T>(*this, rhs); }	// called by "sstd::tmat_r buf1(N, N); sstd::tmat_r buf2(buf1);"
	inline mat_r(      class mat_r&& rhs){ rowSize=0; colSize=0; elems=0; pMatT=0; sstd::move<T>(*this, rhs); }	// called by "return std::move(rhs);" or "std::swap(buf1, buf2)".
	// std::move(lhs, rhs): "move to uninitalized object" will be called.
	// std::swap(lhs, rhs): "move to uninitalized object" -> "copy to lhs or rhs" -> "copy to lhs or rhs" will be called.
	inline mat_r(const uint& row, const uint& col){
		rowSize = row;
		colSize = col;
		elems = row * col;
		pMatT = new T[elems];
		sstd::pdbg_if_stop_exit(pMatT==0, "ERROR: This pointer is not allocated.\n");
	}
	inline ~mat_r(){ delete[] pMatT; }

	// R: read only
	inline const uint& rows() const { return rowSize; }
	inline const uint& cols() const { return colSize; }
	inline const uint& size() const { return elems; }

	// RW: read and write
	inline T*& pMatT_RW(){ return pMatT; }
	inline uint& rows_RW(){ return rowSize; }
	inline uint& cols_RW(){ return colSize; }
	inline uint& size_RW(){ return elems; }

	class mat_r& operator=(const class mat_r& rhs){ sstd::copy<T>(*this, rhs); return *this; }	// called by "lhs = tmat_r::tmat_r(3, 3);".

	inline       T& operator[](const uint q)       { return pMatT[      q]; }
	inline       T& operator[](const  int q)       { return pMatT[(uint)q]; }
	inline const T& operator[](const uint q) const { return pMatT[      q]; }
	inline const T& operator[](const  int q) const { return pMatT[(uint)q]; }

	inline       T& operator()(const uint p, const uint q)       { return pMatT[colSize*      p +       q]; }
	inline       T& operator()(const  int p, const uint q)       { return pMatT[colSize*(uint)p +       q]; }
	inline       T& operator()(const uint p, const  int q)       { return pMatT[colSize*      p + (uint)q]; }
	inline       T& operator()(const  int p, const  int q)       { return pMatT[colSize*(uint)p + (uint)q]; }
	inline const T& operator()(const uint p, const uint q) const { return pMatT[colSize*      p +       q]; }
	inline const T& operator()(const  int p, const uint q) const { return pMatT[colSize*(uint)p +       q]; }
	inline const T& operator()(const uint p, const  int q) const { return pMatT[colSize*      p + (uint)q]; }
	inline const T& operator()(const  int p, const  int q) const { return pMatT[colSize*(uint)p + (uint)q]; }
	
	class CopyRow_r<T> operator()(const uint& p, const char& c_dummy){ return OpCopyRow_r<T>(this, p, c_dummy); }
	class CopyRow_r<T> operator()(const  int& p, const char& c_dummy){ return OpCopyRow_r<T>(this, p, c_dummy); }

	class CopyCol_r<T> operator()(const char& c_dummy, const uint& q){ return OpCopyCol_r<T>(this, c_dummy, q); }
	class CopyCol_r<T> operator()(const char& c_dummy, const  int& q){ return OpCopyCol_r<T>(this, c_dummy, q); }
	
	// for element operations (elements multiplication)
	inline sstd::mat_r_elements<T> operator()(){ return sstd::mat_r_elements<T>((const T*&)pMatT, (const uint&)rowSize, (const uint&)colSize, (const uint&)elems); }
	inline sstd::mat_r_elements<T>        vec(){ return sstd::mat_r_elements<T>((const T*&)pMatT, (const uint&)rowSize, (const uint&)colSize, (const uint&)elems); }
};

//--------------------------------------------------------------------------------------------------------

template <typename T>
inline void sstd::eye(sstd::mat_r<T>& rhs){
	for(uint p=0; p<rhs.rows(); p++){
		for(uint q=0; q<rhs.cols(); q++){
			if(p!=q){ rhs(p, q)=(T)0;
			}  else { rhs(p, q)=(T)1; }
		}
	}
}

template <typename T>
inline void sstd::ones(sstd::mat_r<T>& rhs){
	for(uint p=0; p<rhs.size(); p++){ rhs[p]=(T)1; }
}

template <typename T>
inline void sstd::zeros(sstd::mat_r<T>& mat){
	for(uint p=0; p<mat.size(); p++){ mat[p]=(T)0; }
}

//--------------------------------------------------------------------------------------------------------

template <typename T>
inline void copy_withoutAllocate(sstd::mat_r<T>& lhs, const sstd::mat_r<T>& rhs){
	for(uint p=0; p<rhs.rows(); p++){
		for(uint q=0; q<rhs.cols(); q++){
			lhs(p, q) = rhs(p, q);
		}
	}
}
template <typename T>
inline void sstd::copy(sstd::mat_r<T>& lhs, const sstd::mat_r<T>& rhs){

	if(lhs.size() != rhs.size()){
		delete[] lhs.pMatT_RW(); lhs.pMatT_RW() = 0;
		if(rhs.size()!=0){ lhs.pMatT_RW() = new T[rhs.size()]; }
	}

	lhs.rows_RW() = rhs.rows();
	lhs.cols_RW() = rhs.cols();
	lhs.size_RW() = rhs.size();

	copy_withoutAllocate<T>(lhs, rhs);
}

//--------------------------------------------------------------------------------------------------------

template <typename T>
inline void sstd::move(sstd::mat_r<T>& lhs, sstd::mat_r<T>& rhs){	
	lhs.rows_RW() = rhs.rows(); rhs.rows_RW() = 0;
	lhs.cols_RW() = rhs.cols(); rhs.cols_RW() = 0;
	lhs.size_RW()  = rhs.size(); rhs.size_RW()  = 0;

	delete[] lhs.pMatT_RW();
	lhs.pMatT_RW() = rhs.pMatT_RW();
	rhs.pMatT_RW() = 0;
}

//--------------------------------------------------------------------------------------------------------

template <typename T>
void swap(sstd::mat_r<T>& lhs, sstd::mat_r<T>& rhs){
	uint rowsBuf=lhs.rows(); lhs.rows_RW()=rhs.rows(); rhs.rows_RW()=rowsBuf;
	uint colsBuf=lhs.cols(); lhs.cols_RW()=rhs.cols(); rhs.cols_RW()=colsBuf;
	uint sizeBuf=lhs.size(); lhs.size_RW()=rhs.size(); rhs.size_RW()=sizeBuf;
	
	T* pMatBuf=lhs.pMat(); lhs.pMatT_RW()=rhs.pMat(); rhs.pMatT_RW()=pMatBuf;
}

//--------------------------------------------------------------------------------------------------------

template <typename T>
sstd::mat_r<T> sstd::Tr(sstd::mat_r<T>& rhs){
	sstd::mat_r<T> lhs(rhs.cols(), rhs.rows());
	for(uint p=0; p<rhs.rows(); p++){
		for(uint q=0; q<rhs.cols(); q++){
			lhs(q, p) = rhs(p, q);
		}
	}
	return lhs;
}
template <typename T>
void sstd::Tr_myself(sstd::mat_r<T>& rhs){
	sstd::mat_r<T> lhs = sstd::Tr(rhs);
	sstd::move(rhs, lhs);
}

//--------------------------------------------------------------------------------------------------------

template <typename T>
inline sstd::mat_r<T>* sstd::copyRect(sstd::mat_r<T>*& pMat, const uint& rowStart, const uint& rowEnd, const uint& colStart, const uint& colEnd){

	sstd::mat_r<T>* pMatBuf = new sstd::mat_r<T>(rowEnd-rowStart, colEnd-colStart);

	for(uint p=0; p<(rowEnd-rowStart); p++){
		for(uint q=0; q<(colEnd-colStart); q++){
			(*pMatBuf)(p, q) = (*pMat)(p+rowStart, q+colStart);
		}
	}

	return pMatBuf;
}

//--------------------------------------------------------------------------------------------------------
