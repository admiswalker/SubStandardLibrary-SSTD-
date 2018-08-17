#pragma once


class SwapByOneIndex OpSwapByOneIndex(sstd::bmat* pthis, uint p);


class SwapByOneIndex{
private:
	bool getVal(class sstd::bmat& bMat, uint& p);
	void setVal(class sstd::bmat& bMat, uint& p, bool& val);
public:
	SwapByOneIndex(){}
	~SwapByOneIndex(){}

	class sstd::bmat* pBMxs;

	uint SwapNum;

	// called by "sstd::bmat bMat; bMat[0] = bMat[1] = bMat[2];".
	bool operator=(class SwapByOneIndex SBOI){
		bool result = getVal(*SBOI.pBMxs, SBOI.SwapNum);
		setVal(*(*this).pBMxs, (*this).SwapNum, result);
		return result;
	}

	// called by "sstd::bmat bMat; bMat[1] = bMat[0] = true or false;".
	bool operator=(bool rhs){ setVal(*(*this).pBMxs, (*this).SwapNum, rhs); return rhs; }

	// called by "sstd::bmat bMat; bool buf = bMat[0];".
	operator bool(){ return getVal(*(*this).pBMxs, (*this).SwapNum); }	// キャスト演算子のオーバーロード
};
