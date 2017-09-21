#pragma once


template <typename type>
class CopyRow{
private:
public:
	CopyRow(){}
	~CopyRow(){}

	class sstd::typeMatrix<type>* pMxs;
	uint CopyRowNum;

	class CopyRow<type> operator=(class CopyRow<type> CR);
};


template <typename type>
inline class CopyRow<type> CopyRow<type>::operator=(class CopyRow<type> CR)
{
	for(uint q=0; q<this->pMxs->cols(); q++){
		(*(this->pMxs))(this->CopyRowNum, q)
		 = (*(CR.pMxs))(   CR.CopyRowNum, q);
	}
	return *this;
}

// 行のコピー, 例: MatB(1, ':') = MatB(0, ':') = MatA(0, ':');
template <typename type>
inline class CopyRow<type> OpCopyRow(sstd::typeMatrix<type>* pthis, uint p, const char& c_dummy)
{
	class CopyRow<type> CR;
	CR.pMxs = pthis;
	CR.CopyRowNum = p;

	return CR;
}
