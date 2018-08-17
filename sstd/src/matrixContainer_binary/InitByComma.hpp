#pragma once


//class SwapByTwoIndex OpSwapByTwoIndex(sstd::bitMatrix* pthis, uint p, uint q);


class InitByComma{
private:
//	bool getVal(class sstd::bitMatrix& bMat, uint& p, uint& q);
//	void setVal(class sstd::bitMatrix& bMat, uint& p, uint& q, bool val);
public:
	InitByComma(){}
	~InitByComma(){}

//	class sstd::bitMatrix* pBMxs;

//	uint SwapRowNum;
//	uint SwapColNum;

	// called by "sstd::bitMatrix bMat; bMat(0, 0) = bMat(1, 1) = bMat(2, 2);".
//	bool operator=(class SwapByTwoIndex SBTI){
//		bool result = getVal(*SBTI.pBMxs, SBTI.SwapRowNum, SBTI.SwapColNum);
//		setVal(*(*this).pBMxs, (*this).SwapRowNum, (*this).SwapColNum, result);
//		return result;
//	}

	// called by "sstd::bitMatrix bMat; bMat(1, 1) = bMat(0, 0) = true or false;".
//	bool operator=(bool rhs){ setVal(*(*this).pBMxs, (*this).SwapRowNum, (*this).SwapColNum, rhs); return rhs; }

	// called by "sstd::bitMatrix bMat; bool buf = bMat(0, 0);".
//	operator bool(){ return getVal(*(*this).pBMxs, (*this).SwapRowNum, (*this).SwapColNum); }	// キャスト演算子のオーバーロード
};
