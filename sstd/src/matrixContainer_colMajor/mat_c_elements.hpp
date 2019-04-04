#pragma once

namespace sstd{
	template <typename T> class mat_c;
	template <typename T> class mat_c_elements;
}

template <typename T>
class sstd::mat_c_elements{ // "sstd::mat_c_elements" is defined for elements operations of matrix.
private:
	const T* pMatT;
	uint rowSize;
	uint colSize;
	uint elems; // number of elements
	
public:
	inline mat_c_elements(const T*& pMat, const uint& row, const uint& col, const uint& size){
		pMatT   = pMat;
		rowSize = row;
		colSize = col;
		elems   = size;
	}
	inline ~mat_c_elements(){}
	
	// R: read only
	inline const uint& rows() const { return rowSize; }
	inline const uint& cols() const { return colSize; }
	inline const uint& size() const { return elems;   }
	
	inline       T& operator[](const uint p)       { return pMatT[      p]; }
	inline       T& operator[](const  int p)       { return pMatT[(uint)p]; }
	inline const T& operator[](const uint p) const { return pMatT[      p]; }
	inline const T& operator[](const  int p) const { return pMatT[(uint)p]; }
	
	inline       T& operator()(const uint p, const uint q)       { return pMatT[      p + rowSize*      q]; }
	inline       T& operator()(const  int p, const uint q)       { return pMatT[(uint)p + rowSize*      q]; }
	inline       T& operator()(const uint p, const  int q)       { return pMatT[      p + rowSize*(uint)q]; }
	inline       T& operator()(const  int p, const  int q)       { return pMatT[(uint)p + rowSize*(uint)q]; }
	inline const T& operator()(const uint p, const uint q) const { return pMatT[      p + rowSize*      q]; }
	inline const T& operator()(const  int p, const uint q) const { return pMatT[(uint)p + rowSize*      q]; }
	inline const T& operator()(const uint p, const  int q) const { return pMatT[      p + rowSize*(uint)q]; }
	inline const T& operator()(const  int p, const  int q) const { return pMatT[(uint)p + rowSize*(uint)q]; }
};

