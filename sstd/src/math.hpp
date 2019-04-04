#pragma once

#include <vector>
#include "./matrixContainer_colMajor/mat_c.hpp"
#include "./matrixContainer_rowMajor/mat_r.hpp"

#include <algorithm>  // std::sort()
#include <functional> // std::greater<T>()

namespace sstd{
	// 偶数丸め (round to even, round to the nearest even; RN)
	float  round2even(float n);
	double round2even(double n);

	// 奇数へ丸め (round to odd, round to the nearest odd; RO)
	float  round2odd(float n);
	double round2odd(double n);

	float  sum    (const std::vector<float>& rhs);
	float  sum    (const std::vector<float>& rhs, uint a, uint b); // 配列の a 番目から b 番目までの合計. sum of the a th to b th of array.
	float  sum_abs(const std::vector<float>& rhs);
	float  ave    (const std::vector<float>& rhs);           // 平均値: average
	float  ave    (const std::vector<float>& rhs, uint num); // 平均値: average in the first num elements.
	float  med    (      std::vector<float>  rhs);           // 中央値: median // copy rhs // If rhs.size () is even, average of the two median values is returned.
//	float  mod    (const std::vector<float>& rhs);           // 最頻値: mode
	float  max    (const std::vector<float>& rhs);
	float  max_abs(const std::vector<float>& rhs);
	float  min    (const std::vector<float>& rhs);
	float  min_abs(const std::vector<float>& rhs);
	float  var    (const std::vector<float>& rhs); // 不偏分散/標本分散 (variance): u^2 = (1/(n-1))*Σ(x_i-μ)^2
	float  var_p  (const std::vector<float>& rhs); // 母分散 (variance population): σ^2 = (1/n)*Σ(x_i-μ)^2
	float  stdev  (const std::vector<float>& rhs); // 標本標準偏差 (sample standard deviation): u = SQRT( (1/(n-1))*Σ(x_i-μ)^2 )
	float  stdev_p(const std::vector<float>& rhs); // 標準偏差 (standard deviation): σ = SQRT( (1/n)*Σ(x_i-μ)^2 )
	
	double sum    (const std::vector<double>& rhs);
	double sum    (const std::vector<double>& rhs, uint a, uint b); // 配列の a 番目から b 番目までの合計. sum of the a th to b th of array.
	double sum_abs(const std::vector<double>& rhs);
	double ave    (const std::vector<double>& rhs);           // 平均値: average
	double ave    (const std::vector<double>& rhs, uint num); // 平均値: average in the first num elements.
	double med    (      std::vector<double>  rhs);           // 中央値: median // copy rhs // If rhs.size () is even, average of the two median values is returned.
//	double mod    (const std::vector<double>& rhs);           // 最頻値: mode
	double max    (const std::vector<double>& rhs);
	double max_abs(const std::vector<double>& rhs);
	double min    (const std::vector<double>& rhs);
	double min_abs(const std::vector<double>& rhs);
	double var    (const std::vector<double>& rhs); // 不偏分散/標本分散 (variance): u^2 = (1/(n-1))*Σ(x_i-μ)^2
	double var_p  (const std::vector<double>& rhs); // 母分散 (variance population): σ^2 = (1/n)*Σ(x_i-μ)^2
	double stdev  (const std::vector<double>& rhs); // 標本標準偏差 (sample standard deviation): u = SQRT( (1/(n-1))*Σ(x_i-μ)^2 )
	double stdev_p(const std::vector<double>& rhs); // 標準偏差 (standard deviation): σ = SQRT( (1/n)*Σ(x_i-μ)^2 )

	std::vector<uint64> prime(uint64 rhs);                                  // get a list of prime number under rhs.
	struct fact{
		uint64 prime;
		uint64 num;
	};
	std::vector<struct fact> factor(uint64 rhs);                            // get a list of prime factorization
	void print     (const std::vector<struct fact>& factList);
	void for_printn(const std::vector<struct fact>& factList);
	std::vector<uint64> divisor(const std::vector<struct sstd::fact>& rhs); // get a list of all divisors
	std::vector<uint64> divisor(uint64 rhs);                                // get a list of all of the divisors.

	uint8  pow(const uint8 & base, const uint8 & exp);
	uint16 pow(const uint16& base, const uint16& exp);
	uint32 pow(const uint32& base, const uint32& exp);
	uint64 pow(const uint64& base, const uint64& exp);
	 float pow(const  float& base, const  float& exp);
	double pow(const double& base, const double& exp);

	//-----------------------------------------------------------------------------------------------------------------------------------------------
	
	// ここ，テンプレートで書きなおせば，ベタ書きする必要がなくなり，さらに，一般の type T について，ソート可能になるので，書き直す．
	// ここ，テンプレートで書きなおせば，ベタ書きする必要がなくなり，さらに，一般の type T について，ソート可能になるので，書き直す．
	// ここ，テンプレートで書きなおせば，ベタ書きする必要がなくなり，さらに，一般の type T について，ソート可能になるので，書き直す．
	// ここ，テンプレートで書きなおせば，ベタ書きする必要がなくなり，さらに，一般の type T について，ソート可能になるので，書き直す．
	// XXXXXXXXXXXXXXXXXXXXX
	// XXXXXXXXXXXXXXXXXXXXX
	// XXXXXXXXXXXXXXXXXXXXX
	// XXXXXXXXXXXXXXXXXXXXX
	// XXXXXXXXXXXXXXXXXXXXX
	// -> 開発当初は，float と double にしか対応する予定がなかったため．
	
	  char max    (const std::vector< char >& rhs);
	  int8 max    (const std::vector< int8 >& rhs);
	 int16 max    (const std::vector< int16>& rhs);
	 int32 max    (const std::vector< int32>& rhs);
	 int64 max    (const std::vector< int64>& rhs);
//	 uchar max    (const std::vector<uchar >& rhs); // same as a uint8
	 uint8 max    (const std::vector<uint8 >& rhs);
	uint16 max    (const std::vector<uint16>& rhs);
	uint32 max    (const std::vector<uint32>& rhs);
	uint64 max    (const std::vector<uint64>& rhs);
	  char max_abs(const std::vector< char >& rhs);
	  int8 max_abs(const std::vector< int8 >& rhs);
	 int16 max_abs(const std::vector< int16>& rhs);
	 int32 max_abs(const std::vector< int32>& rhs);
	 int64 max_abs(const std::vector< int64>& rhs);
	
	  char min    (const std::vector< char >& rhs);
	  int8 min    (const std::vector< int8 >& rhs);
	 int16 min    (const std::vector< int16>& rhs);
	 int32 min    (const std::vector< int32>& rhs);
	 int64 min    (const std::vector< int64>& rhs);
//	 uchar min    (const std::vector<uchar >& rhs); // same as a uint8
	 uint8 min    (const std::vector<uint8 >& rhs);
	uint16 min    (const std::vector<uint16>& rhs);
	uint32 min    (const std::vector<uint32>& rhs);
	uint64 min    (const std::vector<uint64>& rhs);
	  char min_abs(const std::vector< char >& rhs);
	  int8 min_abs(const std::vector< int8 >& rhs);
	 int16 min_abs(const std::vector< int16>& rhs);
	 int32 min_abs(const std::vector< int32>& rhs);
	 int64 min_abs(const std::vector< int64>& rhs);
	
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	
	  char max    (const sstd::mat_c< char >& rhs);
	  int8 max    (const sstd::mat_c< int8 >& rhs);
	 int16 max    (const sstd::mat_c< int16>& rhs);
	 int32 max    (const sstd::mat_c< int32>& rhs);
	 int64 max    (const sstd::mat_c< int64>& rhs);
//	 uchar max    (const sstd::mat_c<uchar >& rhs); // same as a uint8
	 uint8 max    (const sstd::mat_c<uint8 >& rhs);
	uint16 max    (const sstd::mat_c<uint16>& rhs);
	uint32 max    (const sstd::mat_c<uint32>& rhs);
	uint64 max    (const sstd::mat_c<uint64>& rhs);
	 float max    (const sstd::mat_c< float>& rhs);
	double max    (const sstd::mat_c<double>& rhs);
	  char max_abs(const sstd::mat_c< char >& rhs);
	  int8 max_abs(const sstd::mat_c< int8 >& rhs);
	 int16 max_abs(const sstd::mat_c< int16>& rhs);
	 int32 max_abs(const sstd::mat_c< int32>& rhs);
	 int64 max_abs(const sstd::mat_c< int64>& rhs);
	 float max_abs(const sstd::mat_c< float>& rhs);
	double max_abs(const sstd::mat_c<double>& rhs);
	
	  char min    (const sstd::mat_c< char >& rhs);
	  int8 min    (const sstd::mat_c< int8 >& rhs);
	 int16 min    (const sstd::mat_c< int16>& rhs);
	 int32 min    (const sstd::mat_c< int32>& rhs);
	 int64 min    (const sstd::mat_c< int64>& rhs);
//	 uchar min    (const sstd::mat_c<uchar >& rhs); // same as a uint8
	 uint8 min    (const sstd::mat_c<uint8 >& rhs);
	uint16 min    (const sstd::mat_c<uint16>& rhs);
	uint32 min    (const sstd::mat_c<uint32>& rhs);
	uint64 min    (const sstd::mat_c<uint64>& rhs);
	 float min    (const sstd::mat_c< float>& rhs);
	double min    (const sstd::mat_c<double>& rhs);
	  char min_abs(const sstd::mat_c< char >& rhs);
	  int8 min_abs(const sstd::mat_c< int8 >& rhs);
	 int16 min_abs(const sstd::mat_c< int16>& rhs);
	 int32 min_abs(const sstd::mat_c< int32>& rhs);
	 int64 min_abs(const sstd::mat_c< int64>& rhs);
	 float min_abs(const sstd::mat_c< float>& rhs);
	double min_abs(const sstd::mat_c<double>& rhs);
	
	//-----------------------------------------------------------------------------------------------------------------------------------------------

	  char max    (const sstd::mat_r< char >& rhs);
	  int8 max    (const sstd::mat_r< int8 >& rhs);
	 int16 max    (const sstd::mat_r< int16>& rhs);
	 int32 max    (const sstd::mat_r< int32>& rhs);
	 int64 max    (const sstd::mat_r< int64>& rhs);
//	 uchar max    (const sstd::mat_r<uchar >& rhs); // same as a uint8
	 uint8 max    (const sstd::mat_r<uint8 >& rhs);
	uint16 max    (const sstd::mat_r<uint16>& rhs);
	uint32 max    (const sstd::mat_r<uint32>& rhs);
	uint64 max    (const sstd::mat_r<uint64>& rhs);
	 float max    (const sstd::mat_r< float>& rhs);
	double max    (const sstd::mat_r<double>& rhs);
	  char max_abs(const sstd::mat_r< char >& rhs);
	  int8 max_abs(const sstd::mat_r< int8 >& rhs);
	 int16 max_abs(const sstd::mat_r< int16>& rhs);
	 int32 max_abs(const sstd::mat_r< int32>& rhs);
	 int64 max_abs(const sstd::mat_r< int64>& rhs);
	 float max_abs(const sstd::mat_r< float>& rhs);
	double max_abs(const sstd::mat_r<double>& rhs);
	
	  char min    (const sstd::mat_r< char >& rhs);
	  int8 min    (const sstd::mat_r< int8 >& rhs);
	 int16 min    (const sstd::mat_r< int16>& rhs);
	 int32 min    (const sstd::mat_r< int32>& rhs);
	 int64 min    (const sstd::mat_r< int64>& rhs);
//	 uchar min    (const sstd::mat_r<uchar >& rhs); // same as a uint8
	 uint8 min    (const sstd::mat_r<uint8 >& rhs);
	uint16 min    (const sstd::mat_r<uint16>& rhs);
	uint32 min    (const sstd::mat_r<uint32>& rhs);
	uint64 min    (const sstd::mat_r<uint64>& rhs);
	 float min    (const sstd::mat_r< float>& rhs);
	double min    (const sstd::mat_r<double>& rhs);
	  char min_abs(const sstd::mat_r< char >& rhs);
	  int8 min_abs(const sstd::mat_r< int8 >& rhs);
	 int16 min_abs(const sstd::mat_r< int16>& rhs);
	 int32 min_abs(const sstd::mat_r< int32>& rhs);
	 int64 min_abs(const sstd::mat_r< int64>& rhs);
	 float min_abs(const sstd::mat_r< float>& rhs);
	double min_abs(const sstd::mat_r<double>& rhs);
	
	//-----------------------------------------------------------------------------------------------------------------------------------------------

	// これだど，コピーが不要な場合も必ずコピーされるので，ダメでは？
	template <typename T> inline std::vector<T> sort   (std::vector<T> rhs){ std::sort(rhs.begin(), rhs.end()); return rhs; }                    // Ascending: 昇順: 0, 1, 2, ...
	template <typename T> inline std::vector<T> sort_de(std::vector<T> rhs){ std::sort(rhs.begin(), rhs.end(), std::greater<T>()); return rhs; } // Descending: 降順: 9, 8, 7, ...
	
	//-----------------------------------------------------------------------------------------------------------------------------------------------
}
