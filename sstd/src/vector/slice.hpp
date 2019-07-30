#pragma once
//#include "../itr.hpp" // definition of sstd::begin() and sstd::end()

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
	class slice_range;
	/*
	sstd::slice_range slice(const         int rhs);
	sstd::slice_range slice(const        uint rhs);
	
	sstd::slice_range slice(const         int lhs, const       int rhs);
	sstd::slice_range slice(const         int lhs, const      uint rhs);
	sstd::slice_range slice(const        uint lhs, const       int rhs);
	//*/
	sstd::slice_range slice(const        uint lhs, const      uint rhs);
	/*
	sstd::slice_range slice(const sstd::being lhs, const       int rhs);
	sstd::slice_range slice(const sstd::being lhs, const      uint rhs);
	sstd::slice_range slice(const         int lhs, const sstd::end rhs);
	sstd::slice_range slice(const        uint lhs, const sstd::end rhs);
	sstd::slice_range slice(const sstd::being lhs, const sstd::end rhs);
	//*/
	/*
	sstd::slice_range_mv slice_mv(const         int rhs);
	sstd::slice_range_mv slice_mv(const        uint rhs);
	
	sstd::slice_range_mv slice_mv(const         int lhs, const       int rhs);
	sstd::slice_range_mv slice_mv(const         int lhs, const      uint rhs);
	sstd::slice_range_mv slice_mv(const        uint lhs, const       int rhs);
	sstd::slice_range_mv slice_mv(const        uint lhs, const      uint rhs);
	
	sstd::slice_range_mv slice_mv(const sstd::being lhs, const       int rhs);
	sstd::slice_range_mv slice_mv(const sstd::being lhs, const      uint rhs);
	sstd::slice_range_mv slice_mv(const         int lhs, const sstd::end rhs);
	sstd::slice_range_mv slice_mv(const        uint lhs, const sstd::end rhs);
	sstd::slice_range_mv slice_mv(const sstd::being lhs, const sstd::end rhs);
	//*/
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

struct sstd::slice_range{
private:
public:
	slice_range(){}
	~slice_range(){}
	
//	std::vector<T> operator[](sstd::slice_range lhs){
//		return std::vector<T>();
//		return std::vector<int>();
//	}
};

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd_stdVector_extensions{
	using namespace std;
//	namespace sstd_stdVector_extensions = std;
	
	template<class _Tp, class _Alloc=std::allocator<_Tp> >
	class vector : std::vector<_Tp, _Alloc>{
	private:
	public:
		using std::vector<_Tp, _Alloc>::vector;
		vector<_Tp, _Alloc> operator[](sstd::slice_range lhs){
			printf("in ope[]\n");
			return vector<_Tp, _Alloc>();
		}
	};
}
//namespace std=sstd_stdVector_extensions;

//-----------------------------------------------------------------------------------------------------------------------------------------------

struct sstd::slice_range sstd::slice(const        uint lhs, const      uint rhs){
	return sstd::slice_range();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
/*
template <typename T>
inline std::vector<T> operator [](std::vector<T>& rhs, sstd::slice_range lhs){
//inline std::vector<T> operator +(std::vector<T>& rhs, sstd::slice_range lhs){
//std::vector<T> operator[](std::vector<T> rhs, sstd::slice_range lhs){
//inline std::vector<T> sstd::operator[](const sstd::slice_range& rhs){
//inline std::vector<T> operator[](const sstd::slice_range& rhs){
//	for(uint p=0; p<rhs.size(); p++){ rhs[p]--; }
	return std::vector<T>();
}//*/

/*
template <typename T>
inline std::vector<T> operator[](const sstd::slice_range& rhs){
//	for(uint p=0; p<rhs.size(); p++){ rhs[p]--; }
//	return rhs;
}//*/

// まずは，演算子が呼び出せるところまで実装して，様子を伺う．

//-----------------------------------------------------------------------------------------------------------------------------------------------




