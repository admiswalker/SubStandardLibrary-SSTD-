#pragma once

namespace sstd{
	template <typename T> class mat;
	template <typename T> class mat_elements;
}

template <typename T>
class sstd::mat_elements{
private:
	const T* MatX;
	uint rowNum;	// 行数
	uint colNum;	// 列数
	uint length;
	
public:
	inline mat_elements(const T*& pMat, const uint& row, const uint& col, const uint& len){
		MatX = pMat;
		rowNum = row;
		colNum = col;
		length = len;
	}
	inline ~mat_elements(){}

	// R: read only
	inline const uint& rows() const { return rowNum; }
	inline const uint& cols() const { return colNum; }
	inline const uint& len () const { return length; }
	
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
};

