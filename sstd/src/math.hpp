﻿#pragma once

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
//    float  mod    (const std::vector<float>& rhs);           // 最頻値: mode
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
//    double mod    (const std::vector<double>& rhs);           // 最頻値: mode
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
    
    template<typename T> inline T min    (const std::vector<T>& rhs);
    template<typename T> inline T min_abs(const std::vector<T>& rhs);
    template<typename T> inline T max    (const std::vector<T>& rhs);
    template<typename T> inline T max_abs(const std::vector<T>& rhs);
    
    template<typename T> inline T min    (const sstd::mat_c<T>& rhs);
    template<typename T> inline T min_abs(const sstd::mat_c<T>& rhs);
    template<typename T> inline T max    (const sstd::mat_c<T>& rhs);
    template<typename T> inline T max_abs(const sstd::mat_c<T>& rhs);
    
    template<typename T> inline T min    (const sstd::mat_r<T>& rhs);
    template<typename T> inline T min_abs(const sstd::mat_r<T>& rhs);
    template<typename T> inline T max    (const sstd::mat_r<T>& rhs);
    template<typename T> inline T max_abs(const sstd::mat_r<T>& rhs);

    //-----------------------------------------------------------------------------------------------------------------------------------------------
    
    // TODO: argmin
    // TODO: argmax
    
    template<typename T> uint argmin    (const std::vector<T>& rhs);
//    template<typename T> uint argmin_abs(const std::vector<T>& rhs);
//    template<typename T> uint argmax    (const std::vector<T>& rhs);
//    template<typename T> uint argmax_abs(const std::vector<T>& rhs);
    /*
    template<typename T> uint argmin    (const sstd::mat_c<T>& rhs);
    template<typename T> uint argmin_abs(const sstd::mat_c<T>& rhs);
    template<typename T> uint argmax    (const sstd::mat_c<T>& rhs);
    template<typename T> uint argmax_abs(const sstd::mat_c<T>& rhs);
    
    template<typename T> uint argmin    (const sstd::mat_r<T>& rhs);
    template<typename T> uint argmin_abs(const sstd::mat_r<T>& rhs);
    template<typename T> uint  argmax    (const sstd::mat_r<T>& rhs);
    template<typename T> uint argmax_abs(const sstd::mat_r<T>& rhs);
    //*/
    //-----------------------------------------------------------------------------------------------------------------------------------------------

    template <typename T> inline std::vector<T> sort   (std::vector<T>   rhs){ std::sort(rhs.begin(), rhs.end()); return rhs; }                    // Ascending: 昇順: 0, 1, 2, ...
    template <typename T> inline std::vector<T> sort   (std::vector<T>&& rhs){ std::sort(rhs.begin(), rhs.end()); return rhs; }                    // Ascending: 昇順: 0, 1, 2, ...
    template <typename T> inline std::vector<T> sort_de(std::vector<T>   rhs){ std::sort(rhs.begin(), rhs.end(), std::greater<T>()); return rhs; } // Descending: 降順: 9, 8, 7, ...
    template <typename T> inline std::vector<T> sort_de(std::vector<T>&& rhs){ std::sort(rhs.begin(), rhs.end(), std::greater<T>()); return rhs; } // Descending: 降順: 9, 8, 7, ...
    
    //-----------------------------------------------------------------------------------------------------------------------------------------------
    
    template <typename T> std::vector<T> nonzero(const std::vector<T>& rhs);
//    template <typename T> void padding (std::vector<T>& vecLhs, std::vector<T>& vecRhs); // <--> sstd::suppress();
//    template <typename T> void suppress(std::vector<T>& vecLhs, std::vector<T>& vecRhs); // <--> sstd::padding(); or zfill
    template <typename... Args> void suppress(Args&... args);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define MIN_vec_mat(T, lhs, rhs)                                        \
    if(rhs.size()==0){ return T(); }                                    \
    T lhs=rhs[0];                                                       \
    for(uint i=1; i<rhs.size(); i++){ if(rhs[i]<lhs){ lhs=rhs[i]; } }   \
    return lhs;

#define MIN_ABS_vec_mat(T, lhs, rhs)                                    \
    if(rhs.size()==0){ return T(); }                                    \
    T lhs=rhs[0], buf=std::abs(rhs[0]);                                 \
    for(uint i=1; i<rhs.size(); i++){ if(std::abs(rhs[i])<buf){ lhs=rhs[i]; buf=std::abs(rhs[i]); } } \
    return lhs;

#define MAX_vec_mat(T, lhs, rhs)                                        \
    if(rhs.size()==0){ return T(); }                                    \
    T lhs=rhs[0];                                                       \
    for(uint i=1; i<rhs.size(); i++){ if(rhs[i]>lhs){ lhs=rhs[i]; } }   \
    return lhs;

#define MAX_ABS_vec_mat(T, lhs, rhs)                                    \
    if(rhs.size()==0){ return T(); }                                    \
    T lhs=rhs[0], buf=std::abs(rhs[0]);                                 \
    for(uint i=1; i<rhs.size(); i++){ if(std::abs(rhs[i])>buf){ lhs=rhs[i]; buf=std::abs(rhs[i]); } } \
    return lhs;

template<typename T> inline T sstd::min    (const std::vector<T>& rhs){ MIN_vec_mat    (T, lhs, rhs); }
template<typename T> inline T sstd::min_abs(const std::vector<T>& rhs){ MIN_ABS_vec_mat(T, lhs, rhs); }
template<typename T> inline T sstd::max    (const std::vector<T>& rhs){ MAX_vec_mat    (T, lhs, rhs); }
template<typename T> inline T sstd::max_abs(const std::vector<T>& rhs){ MAX_ABS_vec_mat(T, lhs, rhs); }

template<typename T> inline T sstd::min    (const sstd::mat_c<T>& rhs){ MIN_vec_mat    (T, lhs, rhs); }
template<typename T> inline T sstd::min_abs(const sstd::mat_c<T>& rhs){ MIN_ABS_vec_mat(T, lhs, rhs); }
template<typename T> inline T sstd::max    (const sstd::mat_c<T>& rhs){ MAX_vec_mat    (T, lhs, rhs); }
template<typename T> inline T sstd::max_abs(const sstd::mat_c<T>& rhs){ MAX_ABS_vec_mat(T, lhs, rhs); }

template<typename T> inline T sstd::min    (const sstd::mat_r<T>& rhs){ MIN_vec_mat    (T, lhs, rhs); }
template<typename T> inline T sstd::min_abs(const sstd::mat_r<T>& rhs){ MIN_ABS_vec_mat(T, lhs, rhs); }
template<typename T> inline T sstd::max    (const sstd::mat_r<T>& rhs){ MAX_vec_mat    (T, lhs, rhs); }
template<typename T> inline T sstd::max_abs(const sstd::mat_r<T>& rhs){ MAX_ABS_vec_mat(T, lhs, rhs); }

#undef MAX_ABS_vec_mat
#undef MAX_vec_mat
#undef MIN_ABS_vec_mat
#undef MIN_vec_mat

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define ARGMIN_vec_mat(T, lhs, rhs)                                     \
    if(rhs.size()==0){ return T(); }                                    \
    uint lhs=0;                                                         \
    for(uint i=1; i<rhs.size(); i++){ if(rhs[i]<rhs[lhs]){ lhs=i; } }   \
    return lhs;

template<typename T> uint argmin    (const std::vector<T>& rhs){ ARGMIN_vec_mat    (T, lhs, rhs); }
//template<typename T> uint argmin_abs(const std::vector<T>& rhs);
//template<typename T> uint argmax    (const std::vector<T>& rhs);
//template<typename T> uint argmax_abs(const std::vector<T>& rhs);

//#undef ARGMAX_ABS_vec_mat
//#undef ARGMAX_vec_mat
//#undef ARGMIN_ABS_vec_mat
#undef ARGMIN_vec_mat

//-----------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
std::vector<T> sstd::nonzero(const std::vector<T>& rhs){
    std::vector<T> lhs(rhs.size()); lhs.clear();
    const T zero = (T)0;
    
    for(uint i=0; i<rhs.size(); i++){
        if(rhs[i]==zero){ break; }
        lhs.push_back( rhs[i] );
    }
    return lhs;
}

//---

template <typename T>
void sstd_suppress__args2vecSize(std::vector<uint>& retSize, std::vector<T>& arg_head){
    retSize.push_back(arg_head.size());
}
template <typename T, class... Args>
void sstd_suppress__args2vecSize(std::vector<uint>& retSize, std::vector<T>& arg_head, Args&... arg_body){
    retSize.push_back(arg_head.size());
    sstd_suppress__args2vecSize(retSize, arg_body...);
}

template <typename T>
void sstd_suppress__resize(const uint size, std::vector<T>& arg_head){
    arg_head.resize(size);
}
template <typename T, class... Args>
void sstd_suppress__resize(const uint size, std::vector<T>& arg_head, Args&... arg_body){
    arg_head.resize(size);
    sstd_suppress__resize(size, arg_body...);
}

template <class... Args>
void sstd::suppress(Args&... args){ // Ex. "sstd::suppress(std::vector<T1>& rhs1, std::vector<T2>& rhs2, ...)"
    std::vector<uint> vecSize;
    sstd_suppress__args2vecSize(vecSize, args...);
    sstd_suppress__resize(sstd::min(vecSize), args...);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

