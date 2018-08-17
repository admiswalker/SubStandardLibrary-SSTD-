#pragma once


template <typename T>
class CopyCol_r{
private:
public:
	CopyCol_r(){}
	~CopyCol_r(){}

	class sstd::mat_r<T>* pMxs;
	uint CopyCol_rNum;

	class CopyCol_r<T> operator=(class CopyCol_r<T> CC);
};


template <typename T>
inline class CopyCol_r<T> CopyCol_r<T>::operator=(class CopyCol_r<T> CC)
{
	for(uint p=0; p<this->pMxs->rows(); p++){
		(*(this->pMxs))(p, this->CopyCol_rNum)
		 = (*(CC.pMxs))(p,    CC.CopyCol_rNum);
	}
	return *this;
}

// 列のコピー, 例: MatB(':', 1) = MatB(':', 0) = MatA(':', 0);
template <typename T>
inline class CopyCol_r<T> OpCopyCol_r(sstd::mat_r<T>* pthis, const char& c_dummy, uint q)
{
	class CopyCol_r<T> CC;
	CC.pMxs = pthis;
	CC.CopyCol_rNum = q;

	return CC;
}
