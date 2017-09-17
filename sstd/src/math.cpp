#include "typeDef.h"
#include "math.hpp"
#include <stdlib.h> // abs()
#include <cmath> // ceil(), floor()

// 最近接偶数への丸め (round to the nearest even; RN)
float sstd::round2even(float n){ return std::ceil((n - 0.5) / 2) + std::floor((n + 0.5) / 2); }
double sstd::round2even(double n){ return std::ceil((n - 0.5) / 2) + std::floor((n + 0.5) / 2); }

// 最近接奇数への丸め (round to the nearest odd; RO)
float sstd::round2odd(float n){ return std::ceil((n + 0.5) / 2) + std::floor((n - 0.5) / 2); }
double sstd::round2odd(double n){ return std::ceil((n + 0.5) / 2) + std::floor((n - 0.5) / 2); }

// Kahan summation algorithm
// lhs = KahanSum(std::vector<Type>& rhs)
#define KAHAN_SUM_i(Type, lhs, rhs_i, rhs_len)\
	Type del=0;\
	for(uint i=0; i<rhs_len; i++){\
		Type r1=rhs_i-del;\
		Type r2=lhs+r1;\
		del=(r2-lhs)-r1;\
		lhs=r2;\
	}

float sstd::sum(std::vector<float>& rhs){
	float lhs=0;
	KAHAN_SUM_i(float, lhs, rhs[i], rhs.size());
	return lhs;
}
float sstd::sum_abs(std::vector<float>& rhs){
	float lhs=0;
	KAHAN_SUM_i(float, lhs, abs(rhs[i]), rhs.size());
	return lhs;
}
float sstd::ave(std::vector<float>& rhs){
	return sstd::sum(rhs)/rhs.size();
}
float sstd::max(std::vector<float>& rhs){
	float lhs=0;
	for(uint i=0; i<rhs.size(); i++){ if(lhs<rhs[i]){ lhs=rhs[i]; } }
	return lhs;
}
float sstd::max_abs(std::vector<float>& rhs){
	float lhs=0;
	for(uint i=0; i<rhs.size(); i++){ if(lhs<abs(rhs[i])){ lhs=rhs[i]; } }
	return lhs;
}
float sstd::min(std::vector<float>& rhs){
	float lhs=0;
	for(uint i=0; i<rhs.size(); i++){ if(lhs>rhs[i]){ lhs=rhs[i]; } }
	return lhs;
}
float sstd::min_abs(std::vector<float>& rhs){
	float lhs=0;
	for(uint i=0; i<rhs.size(); i++){ if(lhs>abs(rhs[i])){ lhs=abs(rhs[i]); } }
	return lhs;
}
// 不偏分散/標本分散 (variance): u^2 = (1/(n-1))*Σ(x_i-μ)^2
float sstd::var(std::vector<float>& rhs){
	float a=sstd::ave(rhs);
	float lhs=0;
	KAHAN_SUM_i(float, lhs, (rhs[i]-a)*(rhs[i]-a), rhs.size());
	lhs/=(float)(rhs.size()-1);
	return lhs;
}
// 母分散 (variance population): σ^2 = (1/n)*Σ(x_i-μ)^2
float sstd::var_p(std::vector<float>& rhs){
	float a=sstd::ave(rhs);
	float lhs=0;
	KAHAN_SUM_i(float, lhs, (rhs[i]-a)*(rhs[i]-a), rhs.size());
	lhs/=(float)rhs.size();
	return lhs;
}
// 標本標準偏差 (sample standard deviation): u = SQRT( (1/(n-1))*Σ(x_i-μ)^2 )
float sstd::stdev(std::vector<float>& rhs){ return sqrt(sstd::var(rhs)); }
// 標準偏差 (standard deviation): σ = SQRT( (1/n)*Σ(x_i-μ)^2 )
float sstd::stdev_p(std::vector<float>& rhs){ return sqrt(sstd::var_p(rhs)); }


double sstd::sum(std::vector<double>& rhs){
	double lhs=0;
	KAHAN_SUM_i(double, lhs, rhs[i], rhs.size());
	return lhs;
}
double sstd::sum_abs(std::vector<double>& rhs){
	double lhs=0;
	KAHAN_SUM_i(double, lhs, abs(rhs[i]), rhs.size());
	return lhs;
}
double sstd::ave(std::vector<double>& rhs){
	return sstd::sum(rhs)/rhs.size();
}
double sstd::max(std::vector<double>& rhs){
	double lhs=0;
	for(uint i=0; i<rhs.size(); i++){ if(lhs<rhs[i]){ lhs=rhs[i]; } }
	return lhs;
}
double sstd::max_abs(std::vector<double>& rhs){
	double lhs=0;
	for(uint i=0; i<rhs.size(); i++){ if(lhs<abs(rhs[i])){ lhs=rhs[i]; } }
	return lhs;
}
double sstd::min(std::vector<double>& rhs){
	double lhs=0;
	for(uint i=0; i<rhs.size(); i++){ if(lhs>rhs[i]){ lhs=rhs[i]; } }
	return lhs;
}
double sstd::min_abs(std::vector<double>& rhs){
	double lhs=0;
	for(uint i=0; i<rhs.size(); i++){ if(lhs>abs(rhs[i])){ lhs=abs(rhs[i]); } }
	return lhs;
}
// 不偏分散/標本分散 (variance): u^2 = (1/(n-1))*Σ(x_i-μ)^2
double sstd::var(std::vector<double>& rhs){
	double a=sstd::ave(rhs);
	double lhs=0;
	KAHAN_SUM_i(double, lhs, (rhs[i]-a)*(rhs[i]-a), rhs.size());
	lhs/=(double)(rhs.size()-1);
	return lhs;
}
// 母分散 (variance population): σ^2 = (1/n)*Σ(x_i-μ)^2
double sstd::var_p(std::vector<double>& rhs){
	double a=sstd::ave(rhs);
	double lhs=0;
	KAHAN_SUM_i(double, lhs, (rhs[i]-a)*(rhs[i]-a), rhs.size());
	lhs/=(double)rhs.size();
	return lhs;
}
// 標本標準偏差 (sample standard deviation): u = SQRT( (1/(n-1))*Σ(x_i-μ)^2 )
double sstd::stdev(std::vector<double>& rhs){ return sqrt(sstd::var(rhs)); }
// 標準偏差 (standard deviation): σ = SQRT( (1/n)*Σ(x_i-μ)^2 )
double sstd::stdev_p(std::vector<double>& rhs){ return sqrt(sstd::var_p(rhs)); }

