#pragma once


class SwapByTwoIndex OpSwapByTwoIndex(sstd::bmat* pthis, uint p, uint q);


class SwapByTwoIndex{
private:
	bool getVal(class sstd::bmat& bMat, uint& p, uint& q);
	void setVal(class sstd::bmat& bMat, uint& p, uint& q, bool& val);
public:
	SwapByTwoIndex(){}
	~SwapByTwoIndex(){}

	class sstd::bmat* pBMxs;

	uint SwapRowNum;
	uint SwapColNum;

	// called by "sstd::bmat bMat; bMat(0, 0) = bMat(1, 1) = bMat(2, 2);".
	bool operator=(class SwapByTwoIndex SBTI){
		bool result = getVal(*SBTI.pBMxs, SBTI.SwapRowNum, SBTI.SwapColNum);
		setVal(*(*this).pBMxs, (*this).SwapRowNum, (*this).SwapColNum, result);
		return result;
	}

	// called by "sstd::bmat bMat; bMat(1, 1) = bMat(0, 0) = true or false;".
	bool operator=(bool rhs){ setVal(*(*this).pBMxs, (*this).SwapRowNum, (*this).SwapColNum, rhs); return rhs; }

	// called by "sstd::bmat bMat; bool buf = bMat(0, 0);".
	operator bool(){ return getVal(*(*this).pBMxs, (*this).SwapRowNum, (*this).SwapColNum); }	// キャスト演算子のオーバーロード
};
