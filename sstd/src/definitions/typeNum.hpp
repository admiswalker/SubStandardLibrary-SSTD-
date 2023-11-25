#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "../definitions/typeDef.h"
#include "../memory/void_ptr.hpp"
#include "../container/matrixContainer_colMajor/mat_c.hpp"
#include "../container/matrixContainer_rowMajor/mat_r.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
    const static uchar        num_void   = 200;
    const static uchar        num_len    = 201;
    const static uchar        num_err    = 254;
    const static uchar        num_null   = 255;

    const static uchar        num_bool   =   0;
    const static uchar        num_char   =   1;
    const static uchar        num_uchar  =   2;
    const static uchar        num_int8   =   3;
    const static uchar        num_int16  =   4;
    const static uchar        num_int32  =   5;
    const static uchar        num_int64  =   6;
    const static uchar        num_uint8  =   7;
    const static uchar        num_uint16 =   8;
    const static uchar        num_uint32 =   9;
    const static uchar        num_uint64 =  10;
    const static uchar        num_float  =  11;
    const static uchar        num_double =  12;
    const static uchar        num_str    =  13;

    const static uchar    NUM_VEC_BASE   =  14; // std::vector<T> // num_vec_bool = NUM_VEC_BASE + num_bool
    const static uchar    num_vec_bool   =  14;
    const static uchar    num_vec_char   =  15;
    const static uchar    num_vec_uchar  =  16;
    const static uchar    num_vec_int8   =  17;
    const static uchar    num_vec_int16  =  18;
    const static uchar    num_vec_int32  =  19;
    const static uchar    num_vec_int64  =  20;
    const static uchar    num_vec_uint8  =  21;
    const static uchar    num_vec_uint16 =  22;
    const static uchar    num_vec_uint32 =  23;
    const static uchar    num_vec_uint64 =  24;
    const static uchar    num_vec_float  =  25;
    const static uchar    num_vec_double =  26;
    const static uchar    num_vec_str    =  27;

    const static uchar   NUM_VVEC_BASE   =  28; // std::vector<std::vector<T>> // num_vvec_bool = NUM_VVEC_BASE + num_bool
    const static uchar   num_vvec_bool   =  28;
    const static uchar   num_vvec_char   =  29;
    const static uchar   num_vvec_uchar  =  30;
    const static uchar   num_vvec_int8   =  31;
    const static uchar   num_vvec_int16  =  32;
    const static uchar   num_vvec_int32  =  33;
    const static uchar   num_vvec_int64  =  34;
    const static uchar   num_vvec_uint8  =  35;
    const static uchar   num_vvec_uint16 =  36;
    const static uchar   num_vvec_uint32 =  37;
    const static uchar   num_vvec_uint64 =  38;
    const static uchar   num_vvec_float  =  39;
    const static uchar   num_vvec_double =  40;
    const static uchar   num_vvec_str    =  41;

    const static uchar  NUM_MAT_C_BASE   =  42; // sstd::mat_c<T> // num_mat_c_bool = NUM_MAT_C_BASE + num_bool
    const static uchar  num_mat_c_bool   =  42;
    const static uchar  num_mat_c_char   =  43;
    const static uchar  num_mat_c_uchar  =  44;
    const static uchar  num_mat_c_int8   =  45;
    const static uchar  num_mat_c_int16  =  46;
    const static uchar  num_mat_c_int32  =  47;
    const static uchar  num_mat_c_int64  =  48;
    const static uchar  num_mat_c_uint8  =  49;
    const static uchar  num_mat_c_uint16 =  50;
    const static uchar  num_mat_c_uint32 =  51;
    const static uchar  num_mat_c_uint64 =  52;
    const static uchar  num_mat_c_float  =  53;
    const static uchar  num_mat_c_double =  54;
    const static uchar  num_mat_c_str    =  55;

    const static uchar  NUM_MAT_R_BASE   =  56; // sstd::mat_r<T> // num_mat_r_bool = NUM_MAT_R_BASE + num_bool
    const static uchar  num_mat_r_bool   =  56;
    const static uchar  num_mat_r_char   =  57;
    const static uchar  num_mat_r_uchar  =  58;
    const static uchar  num_mat_r_int8   =  59;
    const static uchar  num_mat_r_int16  =  60;
    const static uchar  num_mat_r_int32  =  61;
    const static uchar  num_mat_r_int64  =  62;
    const static uchar  num_mat_r_uint8  =  63;
    const static uchar  num_mat_r_uint16 =  64;
    const static uchar  num_mat_r_uint32 =  65;
    const static uchar  num_mat_r_uint64 =  66;
    const static uchar  num_mat_r_float  =  67;
    const static uchar  num_mat_r_double =  68;
    const static uchar  num_mat_r_str    =  69;

    const static uchar NUM_VMAT_C_BASE   =  70; // std::vector<sstd::mat_c<T>> // num_vmat_c_bool = NUM_VMAT_C_BASE + num_bool
    const static uchar num_vmat_c_bool   =  70;
    const static uchar num_vmat_c_char   =  71;
    const static uchar num_vmat_c_uchar  =  72;
    const static uchar num_vmat_c_int8   =  73;
    const static uchar num_vmat_c_int16  =  74;
    const static uchar num_vmat_c_int32  =  75;
    const static uchar num_vmat_c_int64  =  76;
    const static uchar num_vmat_c_uint8  =  77;
    const static uchar num_vmat_c_uint16 =  78;
    const static uchar num_vmat_c_uint32 =  79;
    const static uchar num_vmat_c_uint64 =  80;
    const static uchar num_vmat_c_float  =  81;
    const static uchar num_vmat_c_double =  82;
    const static uchar num_vmat_c_str    =  83;

    const static uchar NUM_VMAT_R_BASE   =  84; // std::vector<sstd::mat_r<T>> // num_vmat_r_bool = NUM_VMAT_R_BASE + num_bool
    const static uchar num_vmat_r_bool   =  84;
    const static uchar num_vmat_r_char   =  85;
    const static uchar num_vmat_r_uchar  =  86;
    const static uchar num_vmat_r_int8   =  87;
    const static uchar num_vmat_r_int16  =  88;
    const static uchar num_vmat_r_int32  =  89;
    const static uchar num_vmat_r_int64  =  90;
    const static uchar num_vmat_r_uint8  =  91;
    const static uchar num_vmat_r_uint16 =  92;
    const static uchar num_vmat_r_uint32 =  93;
    const static uchar num_vmat_r_uint64 =  94;
    const static uchar num_vmat_r_float  =  95;
    const static uchar num_vmat_r_double =  96;
    const static uchar num_vmat_r_str    =  97;

    const static uchar NUM_HASH_BASE       =  98; // std::unordered_map<std::string,std::string> // num_hash_str_bool = NUM_HASH_BASE + num_bool
    const static uchar num_hash_str_bool   =  98;
    const static uchar num_hash_str_char   =  99;
    const static uchar num_hash_str_uchar  = 100;
    const static uchar num_hash_str_int8   = 101;
    const static uchar num_hash_str_int16  = 102;
    const static uchar num_hash_str_int32  = 103;
    const static uchar num_hash_str_int64  = 104;
    const static uchar num_hash_str_uint8  = 105;
    const static uchar num_hash_str_uint16 = 106;
    const static uchar num_hash_str_uint32 = 107;
    const static uchar num_hash_str_uint64 = 108;
    const static uchar num_hash_str_float  = 109;
    const static uchar num_hash_str_double = 110;
    const static uchar num_hash_str_str    = 111;

    const static uchar num_void_ptr        = 112;
    const static uchar num_vec_void_ptr    = 113;
    const static uchar num_vvec_void_ptr   = 114;
    const static uchar num_mat_c_void_ptr  = 115;
    const static uchar num_mat_r_void_ptr  = 116;
    
    const static uchar num_hash_str_void_ptr      = 117;
    const static uchar num_hash_void_ptr_void_ptr = 118;
    
    const static uchar num_vec_terp_var_v2        = 119;
    const static uchar num_hash_terp_var_v2       = 120;
    
    //---

    uchar type2num(              bool rhs);
    uchar type2num(              char rhs);
  //uchar type2num(             uchar rhs); // same as uint8
    uchar type2num(              int8 rhs);
    uchar type2num(             int16 rhs);
    uchar type2num(             int32 rhs);
    uchar type2num(             int64 rhs);
    uchar type2num(             uint8 rhs);
    uchar type2num(            uint16 rhs);
    uchar type2num(            uint32 rhs);
    uchar type2num(            uint64 rhs);
    uchar type2num(             float rhs);
    uchar type2num(            double rhs);
    uchar type2num(const std::string& rhs);

    uchar type2num(const std::vector<       bool>& rhs);
    uchar type2num(const std::vector<       char>& rhs);
  //uchar type2num(const std::vector<      uchar>& rhs); // same as uint8
    uchar type2num(const std::vector<       int8>& rhs);
    uchar type2num(const std::vector<      int16>& rhs);
    uchar type2num(const std::vector<      int32>& rhs);
    uchar type2num(const std::vector<      int64>& rhs);
    uchar type2num(const std::vector<      uint8>& rhs);
    uchar type2num(const std::vector<     uint16>& rhs);
    uchar type2num(const std::vector<     uint32>& rhs);
    uchar type2num(const std::vector<     uint64>& rhs);
    uchar type2num(const std::vector<      float>& rhs);
    uchar type2num(const std::vector<     double>& rhs);
    uchar type2num(const std::vector<std::string>& rhs);

    uchar type2num(const std::vector<std::vector<       bool>>& rhs);
    uchar type2num(const std::vector<std::vector<       char>>& rhs);
  //uchar type2num(const std::vector<std::vector<      uchar>>& rhs); // same as uint8
    uchar type2num(const std::vector<std::vector<       int8>>& rhs);
    uchar type2num(const std::vector<std::vector<      int16>>& rhs);
    uchar type2num(const std::vector<std::vector<      int32>>& rhs);
    uchar type2num(const std::vector<std::vector<      int64>>& rhs);
    uchar type2num(const std::vector<std::vector<      uint8>>& rhs);
    uchar type2num(const std::vector<std::vector<     uint16>>& rhs);
    uchar type2num(const std::vector<std::vector<     uint32>>& rhs);
    uchar type2num(const std::vector<std::vector<     uint64>>& rhs);
    uchar type2num(const std::vector<std::vector<      float>>& rhs);
    uchar type2num(const std::vector<std::vector<     double>>& rhs);
    uchar type2num(const std::vector<std::vector<std::string>>& rhs);

    uchar type2num(const sstd::mat_c<       bool>& rhs);
    uchar type2num(const sstd::mat_c<       char>& rhs);
  //uchar type2num(const sstd::mat_c<      uchar>& rhs); // same as uint8
    uchar type2num(const sstd::mat_c<       int8>& rhs);
    uchar type2num(const sstd::mat_c<      int16>& rhs);
    uchar type2num(const sstd::mat_c<      int32>& rhs);
    uchar type2num(const sstd::mat_c<      int64>& rhs);
    uchar type2num(const sstd::mat_c<      uint8>& rhs);
    uchar type2num(const sstd::mat_c<     uint16>& rhs);
    uchar type2num(const sstd::mat_c<     uint32>& rhs);
    uchar type2num(const sstd::mat_c<     uint64>& rhs);
    uchar type2num(const sstd::mat_c<      float>& rhs);
    uchar type2num(const sstd::mat_c<     double>& rhs);
    uchar type2num(const sstd::mat_c<std::string>& rhs);

    uchar type2num(const sstd::mat_r<       bool>& rhs);
    uchar type2num(const sstd::mat_r<       char>& rhs);
  //uchar type2num(const sstd::mat_r<      uchar>& rhs); // same as uint8
    uchar type2num(const sstd::mat_r<       int8>& rhs);
    uchar type2num(const sstd::mat_r<      int16>& rhs);
    uchar type2num(const sstd::mat_r<      int32>& rhs);
    uchar type2num(const sstd::mat_r<      int64>& rhs);
    uchar type2num(const sstd::mat_r<      uint8>& rhs);
    uchar type2num(const sstd::mat_r<     uint16>& rhs);
    uchar type2num(const sstd::mat_r<     uint32>& rhs);
    uchar type2num(const sstd::mat_r<     uint64>& rhs);
    uchar type2num(const sstd::mat_r<      float>& rhs);
    uchar type2num(const sstd::mat_r<     double>& rhs);
    uchar type2num(const sstd::mat_r<std::string>& rhs);

    uchar type2num(const std::unordered_map<std::string,       bool>& rhs);
    uchar type2num(const std::unordered_map<std::string,       char>& rhs);
  //uchar type2num(const std::unordered_map<std::string,      uchar>& rhs); // same as uint8
    uchar type2num(const std::unordered_map<std::string,       int8>& rhs);
    uchar type2num(const std::unordered_map<std::string,      int16>& rhs);
    uchar type2num(const std::unordered_map<std::string,      int32>& rhs);
    uchar type2num(const std::unordered_map<std::string,      int64>& rhs);
    uchar type2num(const std::unordered_map<std::string,      uint8>& rhs);
    uchar type2num(const std::unordered_map<std::string,     uint16>& rhs);
    uchar type2num(const std::unordered_map<std::string,     uint32>& rhs);
    uchar type2num(const std::unordered_map<std::string,     uint64>& rhs);
    uchar type2num(const std::unordered_map<std::string,      float>& rhs);
    uchar type2num(const std::unordered_map<std::string,     double>& rhs);
    uchar type2num(const std::unordered_map<std::string,std::string>& rhs);

    uchar type2num(const sstd::void_ptr& rhs);
    uchar type2num(const             std::vector<sstd::void_ptr> & rhs);
    uchar type2num(const std::vector<std::vector<sstd::void_ptr>>& rhs);
    uchar type2num(const sstd::mat_c<sstd::void_ptr>& rhs);
    uchar type2num(const sstd::mat_r<sstd::void_ptr>& rhs);

    uchar type2num(const std::unordered_map<std::string,    sstd::void_ptr>& rhs);
    //uchar type2num(const std::unordered_map<sstd::void_ptr, sstd::void_ptr>& rhs);

    //---

    std::string typeNum2str(uchar rhs);
};

//-----------------------------------------------------------------------------------------------------------------------------------------------

