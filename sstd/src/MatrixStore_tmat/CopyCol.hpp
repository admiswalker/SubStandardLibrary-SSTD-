#pragma once


template <typename type>
class CopyCol{
private:
public:
	CopyCol(){}
	~CopyCol(){}

	class sstd::typeMatrix<type>* pMxs;
	uint CopyColNum;

	class CopyCol<type> operator=(class CopyCol<type> CC);
};


template <typename type>
inline class CopyCol<type> CopyCol<type>::operator=(class CopyCol<type> CC)
{
	for(uint p=0; p<this->pMxs->rows(); p++){
		(*(this->pMxs))(p, this->CopyColNum)
		 = (*(CC.pMxs))(p,    CC.CopyColNum);
	}
	return *this;
}

// 列のコピー, 例: MatB(':', 1) = MatB(':', 0) = MatA(':', 0);
template <typename type>
inline class CopyCol<type> OpCopyCol(sstd::typeMatrix<type>* pthis, const char& c_dummy, uint q)
{
	class CopyCol<type> CC;
	CC.pMxs = pthis;
	CC.CopyColNum = q;

	return CC;
}
