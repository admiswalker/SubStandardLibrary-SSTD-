#include "unique_void_ptr.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define        num_NULL    254

#define        num_void    200
#define        num_len     201

#define        num_bool    0
#define        num_char    1
#define        num_uchar   2
#define        num_int8    3
#define        num_int16   4
#define        num_int32   5
#define        num_int64   6
#define        num_uint8   7
#define        num_uint16  8
#define        num_uint32  9
#define        num_uint64 10
#define        num_float  11
#define        num_double 12
#define        num_str    13

#define    VEC_NUM_BASE   14 // std::vector<T> // vec_num_bool = num_bool + VEC_NUM_BASE
#define    vec_num_bool   14
#define    vec_num_char   15
#define    vec_num_uchar  16
#define    vec_num_int8   17
#define    vec_num_int16  18
#define    vec_num_int32  19
#define    vec_num_int64  20
#define    vec_num_uint8  21
#define    vec_num_uint16 22
#define    vec_num_uint32 23
#define    vec_num_uint64 24
#define    vec_num_float  25
#define    vec_num_double 26
#define    vec_num_str    27

#define   VVEC_NUM_BASE   28 // std::vector<std::vector<T>> // vvec_num_bool = num_bool + VVEC_NUM_BASE
#define   vvec_num_bool   28
#define   vvec_num_char   29
#define   vvec_num_uchar  30
#define   vvec_num_int8   31
#define   vvec_num_int16  32
#define   vvec_num_int32  33
#define   vvec_num_int64  34
#define   vvec_num_uint8  35
#define   vvec_num_uint16 36
#define   vvec_num_uint32 37
#define   vvec_num_uint64 38
#define   vvec_num_float  39
#define   vvec_num_double 40
#define   vvec_num_str    41

#define  MAT_C_NUM_BASE   42 // sstd::mat_c<T> // mat_c_num_bool = num_bool + MAT_C_NUM_BASE
#define  mat_c_num_bool   42
#define  mat_c_num_char   43
#define  mat_c_num_uchar  44
#define  mat_c_num_int8   45
#define  mat_c_num_int16  46
#define  mat_c_num_int32  47
#define  mat_c_num_int64  48
#define  mat_c_num_uint8  49
#define  mat_c_num_uint16 50
#define  mat_c_num_uint32 51
#define  mat_c_num_uint64 52
#define  mat_c_num_float  53
#define  mat_c_num_double 54
#define  mat_c_num_str    55

#define  MAT_R_NUM_BASE   56 // sstd::mat_r<T> // mat_r_num_bool = num_bool + MAT_R_NUM_BASE
#define  mat_r_num_bool   56
#define  mat_r_num_char   57
#define  mat_r_num_uchar  58
#define  mat_r_num_int8   59
#define  mat_r_num_int16  60
#define  mat_r_num_int32  61
#define  mat_r_num_int64  62
#define  mat_r_num_uint8  63
#define  mat_r_num_uint16 64
#define  mat_r_num_uint32 65
#define  mat_r_num_uint64 66
#define  mat_r_num_float  67
#define  mat_r_num_double 68
#define  mat_r_num_str    69

#define VMAT_C_NUM_BASE   70 // std::vector<sstd::mat_c<T>> // vmat_c_num_bool = num_bool + VMAT_C_NUM_BASE
#define vmat_c_num_bool   70
#define vmat_c_num_char   71
#define vmat_c_num_uchar  72
#define vmat_c_num_int8   73
#define vmat_c_num_int16  74
#define vmat_c_num_int32  75
#define vmat_c_num_int64  76
#define vmat_c_num_uint8  77
#define vmat_c_num_uint16 78
#define vmat_c_num_uint32 79
#define vmat_c_num_uint64 80
#define vmat_c_num_float  81
#define vmat_c_num_double 82
#define vmat_c_num_str    83

#define VMAT_R_NUM_BASE   84 // std::vector<sstd::mat_r<T>> // vmat_r_num_bool = num_bool + VMAT_R_NUM_BASE
#define vmat_r_num_bool   84
#define vmat_r_num_char   85
#define vmat_r_num_uchar  86
#define vmat_r_num_int8   87
#define vmat_r_num_int16  88
#define vmat_r_num_int32  89
#define vmat_r_num_int64  90
#define vmat_r_num_uint8  91
#define vmat_r_num_uint16 92
#define vmat_r_num_uint32 93
#define vmat_r_num_uint64 94
#define vmat_r_num_float  95
#define vmat_r_num_double 96
#define vmat_r_num_str    97

//-----------------------------------------------------------------------------------------------------------------------------------------------
// constructors

sstd::unique_void_ptr::unique_void_ptr(): typeNum(254), pData(NULL) {}

sstd::unique_void_ptr::unique_void_ptr(bool* ptr){
    this->typeNum = num_bool;
    this->pData   = ptr;
}

sstd::unique_void_ptr::unique_void_ptr(int* ptr){
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// destructor

sstd::unique_void_ptr::~unique_void_ptr(){
    switch (this->typeNum){
    case num_bool: { delete (bool*)pData; } break;
    default: {} break;
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

