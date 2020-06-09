#include "typeDef.h"
#include "math.hpp"
#include <cmath>      // ceil(), floor()
#include <iterator>
#include <stdio.h>    // printf
#include <stdlib.h>   // abs()

// 偶数丸め (round to even, round to the nearest even; RN)
float  sstd::round2even(float n){ return std::ceil((n - 0.5) / 2) + std::floor((n + 0.5) / 2); }
double sstd::round2even(double n){ return std::ceil((n - 0.5) / 2) + std::floor((n + 0.5) / 2); }

// 奇数へ丸め (round to odd, round to the nearest odd; RO)
float  sstd::round2odd(float n){ return std::ceil((n + 0.5) / 2) + std::floor((n - 0.5) / 2); }
double sstd::round2odd(double n){ return std::ceil((n + 0.5) / 2) + std::floor((n - 0.5) / 2); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

// Pairwise summation algorithm

#define SSTD_DEF_math_PairwiseSum(Func_PairwiseSum, pFirst)             \
    template <class Iterator>                                           \
    inline typename std::iterator_traits<Iterator>::value_type Func_PairwiseSum(Iterator first, Iterator last){ \
        using T = typename std::iterator_traits<Iterator>::value_type;  \
        const uint N = 128;                                             \
        const uint size = last - first;                                 \
        if(size <= N){                                                  \
            T sum = (T)0;                                               \
            /* for(; first!=last; ++first){ sum += *first; } */         \
            for(; first!=last; ++first){ sum += pFirst; }               \
            return sum;                                                 \
        }else{                                                          \
            Iterator half = first + (size>>1);                          \
            return PairwiseSum(first, half) + PairwiseSum(half, last);  \
        }                                                               \
    }

SSTD_DEF_math_PairwiseSum(PairwiseSum,              (*first) ); // template<typename T> inline T PairwiseSum    (T* first, T* last);
SSTD_DEF_math_PairwiseSum(PairwiseSum_abs, std::abs((*first))); // template<typename T> inline T PairwiseSum_abs(T* first, T* last);

#undef SSTD_DEF_math_PairwiseSum

//-----------------------------------------------------------------------------------------------------------------------------------------------

//float sstd::sum    (const std::vector<float>& rhs, uint a, uint b){ return PairwiseSum((float*)&rhs[0]+a, (float*)&rhs[0]+b); }
float sstd::sum    (const std::vector<float>& rhs){ return PairwiseSum    (rhs.begin(), rhs.end()); }
float sstd::sum_abs(const std::vector<float>& rhs){ return PairwiseSum_abs(rhs.begin(), rhs.end()); }

double sstd::sum    (const std::vector<double>& rhs){ return PairwiseSum    (rhs.begin(), rhs.end()); }
double sstd::sum_abs(const std::vector<double>& rhs){ return PairwiseSum_abs(rhs.begin(), rhs.end()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

// Kahan summation algorithm
#define KAHAN_SUM_i(Type, lhs, rhs_i, begin_i, end_i)   \
    Type del=0;                                         \
    for(uint i=begin_i; i<end_i; i++){                  \
        Type r1=rhs_i-del;                              \
        Type r2=lhs+r1;                                 \
        del=(r2-lhs)-r1;                                \
        lhs=r2;                                         \
    }

//   Kahan summation algorithm
// 以外の選択肢として
//   Pairwise summation: https://en.wikipedia.org/wiki/Pairwise_summation
// が知られている．(Kahan より精度は劣るがほぼ等価で，ずっと高速)
//
// また，分散の計算には
//   Algorithms for calculating variance - Wikipedia
// が知られている．
//
// Ref: http://iwiwi.hatenadiary.jp/entry/2016/11/23/144034

// -> Todo: ここのアルゴリズムは，Pairwise summation に置き換える．

//-----------------------------------------------------------------------------------------------------------------------------------------------

float sstd::sumK(const std::vector<float>& rhs){
    float lhs=0;
    KAHAN_SUM_i(float, lhs, rhs[i], 0, rhs.size());
    return lhs;
}
// 配列の a 番目から b 番目までの合計. sum of the a th to b th of array.
float sstd::sum(const std::vector<float>& rhs, uint a, uint b){
    float lhs=0;
    KAHAN_SUM_i(float, lhs, rhs[i], a, b);
    return lhs;
}
float sstd::sumK_abs(const std::vector<float>& rhs){
    float lhs=0;
    KAHAN_SUM_i(float, lhs, std::abs(rhs[i]), 0, rhs.size());
    return lhs;
}
float sstd::ave(const std::vector<float>& rhs){
    return sstd::sum(rhs)/rhs.size();
}
// 平均値: average in the first num elements.
float sstd::ave(const std::vector<float>& rhs, uint num){
    return sstd::sum(rhs, 0, num)/num;
}
float sstd::med(std::vector<float> rhs){ // copy rhs
    // TODO: rewrite this fn by 2 of std::nth_element.
    
    if(rhs.size()==0){ return (float)0.0; }
    std::sort(rhs.begin(), rhs.end());
    uint size_div2 = rhs.size() / 2;
    uint size_mod  = rhs.size() - 2*size_div2; // same as "rhs.size()%2"
    if(size_mod==0){ return (rhs[size_div2-1] + rhs[size_div2])/(float)2.0; // rhs.size() is even number
    }     else     { return rhs[size_div2]; }                               // rhs.size() is odd number
}
// 不偏分散/標本分散 (variance): u^2 = (1/(n-1))*Σ(x_i-μ)^2
float sstd::var(const std::vector<float>& rhs){
    float a=sstd::ave(rhs);
    float lhs=0;
    KAHAN_SUM_i(float, lhs, (rhs[i]-a)*(rhs[i]-a), 0, rhs.size());
    lhs/=(float)(rhs.size()-1);
    return lhs;
}
// 母分散 (variance population): σ^2 = (1/n)*Σ(x_i-μ)^2
float sstd::var_p(const std::vector<float>& rhs){
    float a=sstd::ave(rhs);
    float lhs=0;
    KAHAN_SUM_i(float, lhs, (rhs[i]-a)*(rhs[i]-a), 0, rhs.size());
    lhs/=(float)rhs.size();
    return lhs;
}
// 標本標準偏差 (sample standard deviation): u = SQRT( (1/(n-1))*Σ(x_i-μ)^2 )
float sstd::stdev(const std::vector<float>& rhs){ return sqrt(sstd::var(rhs)); }
// 標準偏差 (standard deviation): σ = SQRT( (1/n)*Σ(x_i-μ)^2 )
float sstd::stdev_p(const std::vector<float>& rhs){ return sqrt(sstd::var_p(rhs)); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

double sstd::sumK(const std::vector<double>& rhs){
    double lhs=0;
    KAHAN_SUM_i(double, lhs, rhs[i], 0, rhs.size());
    return lhs;
}
// 配列の a 番目から b 番目までの合計. sum of the a th to b th of array.
double sstd::sum(const std::vector<double>& rhs, uint a, uint b){
    double lhs=0;
    KAHAN_SUM_i(double, lhs, rhs[i], a, b);
    return lhs;
}
double sstd::sumK_abs(const std::vector<double>& rhs){
    double lhs=0;
    KAHAN_SUM_i(double, lhs, std::abs(rhs[i]), 0, rhs.size());
    return lhs;
}
double sstd::ave(const std::vector<double>& rhs){
    return sstd::sum(rhs)/rhs.size();
}
// 平均値: average in the first num elements.
double sstd::ave(const std::vector<double>& rhs, uint num){
    return sstd::sum(rhs, 0, num)/num;
}
double sstd::med(std::vector<double> rhs){ // copy rhs
    if(rhs.size()==0){ return (double)0.0; }
    std::sort(rhs.begin(), rhs.end());
    uint size_div2 = rhs.size() / 2;
    uint size_mod  = rhs.size() - 2*size_div2; // same as "rhs.size()%2"
    if(size_mod==0){ return (rhs[size_div2-1] + rhs[size_div2])/(double)2.0; // rhs.size() is even number
    }     else     { return rhs[size_div2]; }                                // rhs.size() is odd number
}
// 不偏分散/標本分散 (variance): u^2 = (1/(n-1))*Σ(x_i-μ)^2
double sstd::var(const std::vector<double>& rhs){
    double a=sstd::ave(rhs);
    double lhs=0;
    KAHAN_SUM_i(double, lhs, (rhs[i]-a)*(rhs[i]-a), 0, rhs.size());
    lhs/=(double)(rhs.size()-1);
    return lhs;
}
// 母分散 (variance population): σ^2 = (1/n)*Σ(x_i-μ)^2
double sstd::var_p(const std::vector<double>& rhs){
    double a=sstd::ave(rhs);
    double lhs=0;
    KAHAN_SUM_i(double, lhs, (rhs[i]-a)*(rhs[i]-a), 0, rhs.size());
    lhs/=(double)rhs.size();
    return lhs;
}
// 標本標準偏差 (sample standard deviation): u = SQRT( (1/(n-1))*Σ(x_i-μ)^2 )
double sstd::stdev(const std::vector<double>& rhs){ return sqrt(sstd::var(rhs)); }
// 標準偏差 (standard deviation): σ = SQRT( (1/n)*Σ(x_i-μ)^2 )
double sstd::stdev_p(const std::vector<double>& rhs){ return sqrt(sstd::var_p(rhs)); }

// get a list of prime number under rhs.
std::vector<uint64> sstd::prime(uint64 rhs){
    
    uint64 ApproximationNumOfPrimes = (uint64)log((double)rhs); // depend on "Prime number theorem"
    std::vector<uint64> lhs(ApproximationNumOfPrimes); lhs.clear();

    std::vector<char> sieve(rhs, 0); // Sieve of Eratosthenes

    for(uint64 p=3; p<rhs; p+=2){
        for(uint64 q=p*p; q<rhs; q+=2*p){ // p*p mean smallest number that not sift through is multiple of own // adding 2*p to avoid multiple of 2
            sieve[q]=1;
        }
    }

    if(rhs>=2){ lhs.push_back(2); }
    for(uint64 i=3; i<rhs; i+=2){
        if(sieve[i]!=1){
            lhs.push_back(i);
        }
    }
    
    return lhs;
}

// get a list of prime factorization
std::vector<struct sstd::fact> sstd::factor(uint64 rhs){
    std::vector<struct sstd::fact> lhs;
    
//    std::vector<uint> primeList = sstd::prime((uint)(sqrt((double)rhs)+1)); // これは間違い factor(10) でコケる
    std::vector<uint64> primeList = sstd::prime(rhs/2+1);
    struct sstd::fact buf; buf.num = 0;
    for(uint64 i=0; i<primeList.size(); i++){
        buf.prime = primeList[i];
        while(1){
            uint64 prime_div = rhs / primeList[i];
            uint64 prime_mod = rhs - primeList[i]*prime_div; // same as "rhs % primeList[i];"
            if(prime_mod!=0){ break; }
            buf.num++;
            rhs = prime_div;
        }
        if(buf.num!=0){ lhs.push_back(buf); }
        if(rhs==1){ break; }
        buf.num = 0;
    }
    return lhs;
}
void print_NotConst(std::vector<struct sstd::fact>& factList){
    uint64 fact_num=1;
    for(uint i=0; i<factList.size(); i++){ fact_num *= sstd::pow(factList[i].prime, factList[i].num); }
    printf("%lu = %lu^%lu", fact_num, factList[0].prime, factList[0].num);
    for(uint i=1; i<factList.size(); i++){ printf(" + %lu^%lu", factList[i].prime, factList[i].num); }
    printf("\n");
}
void sstd::print(const std::vector<struct fact>& factList){
    print_NotConst((std::vector<struct fact>&)factList);
}
void sstd::for_printn(const std::vector<struct fact>& factList){
    printf(": ");
    print_NotConst((std::vector<struct fact>&)factList);
}

// get a list of all divisors
std::vector<uint64> sstd::divisor(const std::vector<struct sstd::fact>& factorList){
    if(factorList.size()==0){ return std::vector<uint64>(0); } // ERROR check

    std::vector<std::vector<uint64>> expList(factorList.size());
    for(uint64 p=0; p<expList.size(); p++){
        expList[p].push_back(1);
        for(uint64 q=1; q<factorList[p].num+1; q++){
            expList[p].push_back(expList[p][q-1] * factorList[p].prime);
        }
    }

    uint64 size = expList[0].size(); for(uint64 i=1; i<expList.size(); i++){ size *= expList[i].size(); }
    std::vector<uint64> divList(size); divList.clear();
    std::vector<uint64> divList_buf(size); divList_buf.clear();

    for(uint64 i=0; i<expList[0].size(); i++){ divList.push_back( expList[0][i] ); }
    for(uint64 i=1; i<expList.size(); i++){
        for(uint64 p=0; p<divList.size(); p++){
            for(uint64 q=0; q<expList[i].size(); q++){
                divList_buf.push_back(divList[p] * expList[i][q]);
            }
        }
        std::swap(divList, divList_buf);
        divList_buf.clear();
    }

    std::sort(divList.begin(), divList.end());
    return divList;
}
std::vector<uint64> sstd::divisor(uint64 rhs){
    return divisor(sstd::factor(rhs));
}

/*
// base ^ exponent
#define sstd_pow_unsigned(type, base, exp)      \
if(exp==0){ return 1; }                         \
type ret=base;                                  \
for(type i=1; i<exp; i++){ ret *= base; }       \
return ret
//下記のように最適化
// 高速化と言っても O(sqrt(n)/2) 程度なので，特に必要がなければ，double ::pow(double, double) で計算するのがよい (たぶん)．
*/
// base ^ exponent
#define SSTD_DEF_pow_unsigned(T, base, exp)     \
    T b=base, e=exp;                            \
                                                \
    if(e==(T)0){ return (T)1; }                 \
                                                \
    for(; e>(T)0; e>>=1){                       \
        if(e & 1){                              \
            if(e==(T)1){ return b; }            \
            break;                              \
        }                                       \
        b *= b;                                 \
    }                                           \
    T buf = b;                                  \
    buf *= buf;                                 \
    e>>=1;                                      \
                                                \
    for(;;e>>=1){                               \
        if(e & 1){                              \
            b = b * buf;                        \
            if(e==(T)1){ return b; }            \
        }                                       \
        buf *= buf;                             \
    }                                           \
    return b;
uint8  sstd::pow(const uint8 & base, const uint8 & exp){ SSTD_DEF_pow_unsigned(uint8,  base, exp); }
uint16 sstd::pow(const uint16& base, const uint16& exp){ SSTD_DEF_pow_unsigned(uint16, base, exp); }
uint32 sstd::pow(const uint32& base, const uint32& exp){ SSTD_DEF_pow_unsigned(uint32, base, exp); }
uint64 sstd::pow(const uint64& base, const uint64& exp){ SSTD_DEF_pow_unsigned(uint64, base, exp); }
float  sstd::pow(const  float& base, const  float& exp){ return std::pow( (float)base,  (float)exp); }
double sstd::pow(const double& base, const double& exp){ return std::pow((double)base, (double)exp); }

#undef SSTD_DEF_pow_unsigned

//-----------------------------------------------------------------------------------------------------------------------------------------------

