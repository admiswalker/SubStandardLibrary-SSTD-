#pragma once

#include <vector>

namespace sstd{
	// 最近接偶数への丸め (round to the nearest even; RN)
	float round2even(float n);
	double round2even(double n);

	// 最近接奇数への丸め (round to the nearest odd; RO)
	float round2odd(float n);
	double round2odd(double n);

	float sum(std::vector<float>& rhs);
	float sum_abs(std::vector<float>& rhs);
	float ave(std::vector<float>& rhs); // 平均値: average
//	float med(std::vector<float>& rhs); // 中央値: median
//	float mod(std::vector<float>& rhs); // 最頻値: mode
	float max(std::vector<float>& rhs);
	float max_abs(std::vector<float>& rhs);
	float min(std::vector<float>& rhs);
	float min_abs(std::vector<float>& rhs);
	float var(std::vector<float>& rhs); // 不偏分散/標本分散 (variance): u^2 = (1/(n-1))*Σ(x_i-μ)^2
	float var_p(std::vector<float>& rhs); // 母分散 (variance population): σ^2 = (1/n)*Σ(x_i-μ)^2
	float stdev(std::vector<float>& rhs); // 標本標準偏差 (sample standard deviation): u = SQRT( (1/(n-1))*Σ(x_i-μ)^2 )
	float stdev_p(std::vector<float>& rhs); // 標準偏差 (standard deviation): σ = SQRT( (1/n)*Σ(x_i-μ)^2 )

	double sum(std::vector<double>& rhs);
	double sum_abs(std::vector<double>& rhs);
	double ave(std::vector<double>& rhs); // 平均値: average
//	double med(std::vector<double>& rhs); // 中央値: median
//	double mod(std::vector<double>& rhs); // 最頻値: mode
	double max(std::vector<double>& rhs);
	double max_abs(std::vector<double>& rhs);
	double min(std::vector<double>& rhs);
	double min_abs(std::vector<double>& rhs);
	double var(std::vector<double>& rhs); // 不偏分散/標本分散 (variance): u^2 = (1/(n-1))*Σ(x_i-μ)^2
	double var_p(std::vector<double>& rhs); // 母分散 (variance population): σ^2 = (1/n)*Σ(x_i-μ)^2
	double stdev(std::vector<double>& rhs); // 標本標準偏差 (sample standard deviation): u = SQRT( (1/(n-1))*Σ(x_i-μ)^2 )
	double stdev_p(std::vector<double>& rhs); // 標準偏差 (standard deviation): σ = SQRT( (1/n)*Σ(x_i-μ)^2 )
}
