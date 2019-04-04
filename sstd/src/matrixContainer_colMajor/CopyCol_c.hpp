#pragma once


template <typename T>
class CopyCol{
private:
public:
	CopyCol(){}
	~CopyCol(){}

	class sstd::mat_c<T>* pMxs;
	uint CopyColNum;

	class CopyCol<T> operator=(class CopyCol<T> CC);
};


template <typename T>
inline class CopyCol<T> CopyCol<T>::operator=(class CopyCol<T> CC)
{
	for(uint p=0; p<this->pMxs->rows(); p++){
		(*(this->pMxs))(p, this->CopyColNum)
		 = (*(CC.pMxs))(p,    CC.CopyColNum);
	}
	return *this;
}

// 列のコピー, 例: MatB(':', 1) = MatB(':', 0) = MatA(':', 0);
template <typename T>
inline class CopyCol<T> OpCopyCol(sstd::mat_c<T>* pthis, const char& c_dummy, uint q)
{
	class CopyCol<T> CC;
	CC.pMxs = pthis;
	CC.CopyColNum = q;

	return CC;
}
