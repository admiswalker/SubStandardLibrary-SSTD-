#pragma once


template <typename T>
class CopyRow{
private:
public:
	CopyRow(){}
	~CopyRow(){}

	class sstd::mat_c<T>* pMxs;
	uint CopyRowNum;

	class CopyRow<T> operator=(class CopyRow<T> CR);
};


template <typename T>
inline class CopyRow<T> CopyRow<T>::operator=(class CopyRow<T> CR)
{
	for(uint q=0; q<this->pMxs->cols(); q++){
		(*(this->pMxs))(this->CopyRowNum, q)
		 = (*(CR.pMxs))(   CR.CopyRowNum, q);
	}
	return *this;
}

// 行のコピー, 例: MatB(1, ':') = MatB(0, ':') = MatA(0, ':');
template <typename T>
inline class CopyRow<T> OpCopyRow(sstd::mat_c<T>* pthis, uint p, const char& c_dummy)
{
	class CopyRow<T> CR;
	CR.pMxs = pthis;
	CR.CopyRowNum = p;

	return CR;
}
