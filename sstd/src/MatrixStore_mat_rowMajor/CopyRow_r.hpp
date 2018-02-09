#pragma once


template <typename T>
class CopyRow_r{
private:
public:
	CopyRow_r(){}
	~CopyRow_r(){}

	class sstd::mat_r<T>* pMxs;
	uint CopyRow_rNum;

	class CopyRow_r<T> operator=(class CopyRow_r<T> CR);
};


template <typename T>
inline class CopyRow_r<T> CopyRow_r<T>::operator=(class CopyRow_r<T> CR)
{
	for(uint q=0; q<this->pMxs->cols(); q++){
		(*(this->pMxs))(this->CopyRow_rNum, q)
		 = (*(CR.pMxs))(   CR.CopyRow_rNum, q);
	}
	return *this;
}

// 行のコピー, 例: MatB(1, ':') = MatB(0, ':') = MatA(0, ':');
template <typename T>
inline class CopyRow_r<T> OpCopyRow_r(sstd::mat_r<T>* pthis, uint p, const char& c_dummy)
{
	class CopyRow_r<T> CR;
	CR.pMxs = pthis;
	CR.CopyRow_rNum = p;

	return CR;
}
