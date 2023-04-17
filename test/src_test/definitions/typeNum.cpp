#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(typeNum, type2num_bool  ){ ASSERT_EQ(sstd::type2num(       bool()), sstd::num_bool  ); }
TEST(typeNum, type2num_char  ){ ASSERT_EQ(sstd::type2num(       char()), sstd::num_char  ); }
//TEST(typeNum, type2num_uchar ){ ASSERT_EQ(sstd::type2num(      uchar()), sstd::num_uchar ); } // same as uint8
TEST(typeNum, type2num_int8  ){ ASSERT_EQ(sstd::type2num(      int8 ()), sstd::num_int8  ); }
TEST(typeNum, type2num_int16 ){ ASSERT_EQ(sstd::type2num(      int16()), sstd::num_int16 ); }
TEST(typeNum, type2num_int32 ){ ASSERT_EQ(sstd::type2num(      int32()), sstd::num_int32 ); }
TEST(typeNum, type2num_int64 ){ ASSERT_EQ(sstd::type2num(      int64()), sstd::num_int64 ); }
TEST(typeNum, type2num_uint8 ){ ASSERT_EQ(sstd::type2num(     uint8 ()), sstd::num_uint8 ); }
TEST(typeNum, type2num_uint16){ ASSERT_EQ(sstd::type2num(     uint16()), sstd::num_uint16); }
TEST(typeNum, type2num_uint32){ ASSERT_EQ(sstd::type2num(     uint32()), sstd::num_uint32); }
TEST(typeNum, type2num_uint64){ ASSERT_EQ(sstd::type2num(     uint64()), sstd::num_uint64); }
TEST(typeNum, type2num_float ){ ASSERT_EQ(sstd::type2num(      float()), sstd::num_float ); }
TEST(typeNum, type2num_double){ ASSERT_EQ(sstd::type2num(     double()), sstd::num_double); }
TEST(typeNum, type2num_str   ){ ASSERT_EQ(sstd::type2num(std::string()), sstd::num_str   ); }

TEST(typeNum, type2num_vec_bool  ){ ASSERT_EQ(sstd::type2num(std::vector<       bool>()), sstd::num_vec_bool  ); }
TEST(typeNum, type2num_vec_char  ){ ASSERT_EQ(sstd::type2num(std::vector<       char>()), sstd::num_vec_char  ); }
//TEST(typeNum, type2num_vec_uchar ){ ASSERT_EQ(sstd::type2num(std::vector<      uchar>()), sstd::num_vec_uchar ); } // same as uint8
TEST(typeNum, type2num_vec_int8  ){ ASSERT_EQ(sstd::type2num(std::vector<      int8 >()), sstd::num_vec_int8  ); }
TEST(typeNum, type2num_vec_int16 ){ ASSERT_EQ(sstd::type2num(std::vector<      int16>()), sstd::num_vec_int16 ); }
TEST(typeNum, type2num_vec_int32 ){ ASSERT_EQ(sstd::type2num(std::vector<      int32>()), sstd::num_vec_int32 ); }
TEST(typeNum, type2num_vec_int64 ){ ASSERT_EQ(sstd::type2num(std::vector<      int64>()), sstd::num_vec_int64 ); }
TEST(typeNum, type2num_vec_uint8 ){ ASSERT_EQ(sstd::type2num(std::vector<     uint8 >()), sstd::num_vec_uint8 ); }
TEST(typeNum, type2num_vec_uint16){ ASSERT_EQ(sstd::type2num(std::vector<     uint16>()), sstd::num_vec_uint16); }
TEST(typeNum, type2num_vec_uint32){ ASSERT_EQ(sstd::type2num(std::vector<     uint32>()), sstd::num_vec_uint32); }
TEST(typeNum, type2num_vec_uint64){ ASSERT_EQ(sstd::type2num(std::vector<     uint64>()), sstd::num_vec_uint64); }
TEST(typeNum, type2num_vec_float ){ ASSERT_EQ(sstd::type2num(std::vector<      float>()), sstd::num_vec_float ); }
TEST(typeNum, type2num_vec_double){ ASSERT_EQ(sstd::type2num(std::vector<     double>()), sstd::num_vec_double); }
TEST(typeNum, type2num_vec_str   ){ ASSERT_EQ(sstd::type2num(std::vector<std::string>()), sstd::num_vec_str   ); }

TEST(typeNum, type2num_vvec_bool  ){ ASSERT_EQ(sstd::type2num(std::vector<std::vector<       bool>>()), sstd::num_vvec_bool  ); }
TEST(typeNum, type2num_vvec_char  ){ ASSERT_EQ(sstd::type2num(std::vector<std::vector<       char>>()), sstd::num_vvec_char  ); }
//TEST(typeNum, type2num_vvec_uchar ){ ASSERT_EQ(sstd::type2num(std::vector<std::vector<      uchar>>()), sstd::num_vvec_uchar ); } // same as uint8
TEST(typeNum, type2num_vvec_int8  ){ ASSERT_EQ(sstd::type2num(std::vector<std::vector<      int8 >>()), sstd::num_vvec_int8  ); }
TEST(typeNum, type2num_vvec_int16 ){ ASSERT_EQ(sstd::type2num(std::vector<std::vector<      int16>>()), sstd::num_vvec_int16 ); }
TEST(typeNum, type2num_vvec_int32 ){ ASSERT_EQ(sstd::type2num(std::vector<std::vector<      int32>>()), sstd::num_vvec_int32 ); }
TEST(typeNum, type2num_vvec_int64 ){ ASSERT_EQ(sstd::type2num(std::vector<std::vector<      int64>>()), sstd::num_vvec_int64 ); }
TEST(typeNum, type2num_vvec_uint8 ){ ASSERT_EQ(sstd::type2num(std::vector<std::vector<     uint8 >>()), sstd::num_vvec_uint8 ); }
TEST(typeNum, type2num_vvec_uint16){ ASSERT_EQ(sstd::type2num(std::vector<std::vector<     uint16>>()), sstd::num_vvec_uint16); }
TEST(typeNum, type2num_vvec_uint32){ ASSERT_EQ(sstd::type2num(std::vector<std::vector<     uint32>>()), sstd::num_vvec_uint32); }
TEST(typeNum, type2num_vvec_uint64){ ASSERT_EQ(sstd::type2num(std::vector<std::vector<     uint64>>()), sstd::num_vvec_uint64); }
TEST(typeNum, type2num_vvec_float ){ ASSERT_EQ(sstd::type2num(std::vector<std::vector<      float>>()), sstd::num_vvec_float ); }
TEST(typeNum, type2num_vvec_double){ ASSERT_EQ(sstd::type2num(std::vector<std::vector<     double>>()), sstd::num_vvec_double); }
TEST(typeNum, type2num_vvec_str   ){ ASSERT_EQ(sstd::type2num(std::vector<std::vector<std::string>>()), sstd::num_vvec_str   ); }

TEST(typeNum, type2num_mat_c_bool  ){ ASSERT_EQ(sstd::type2num(sstd::mat_c<       bool>()), sstd::num_mat_c_bool  ); }
TEST(typeNum, type2num_mat_c_char  ){ ASSERT_EQ(sstd::type2num(sstd::mat_c<       char>()), sstd::num_mat_c_char  ); }
//TEST(typeNum, type2num_mat_c_uchar ){ ASSERT_EQ(sstd::type2num(sstd::mat_c<      uchar>()), sstd::num_mat_c_uchar ); } // same as uint8
TEST(typeNum, type2num_mat_c_int8  ){ ASSERT_EQ(sstd::type2num(sstd::mat_c<      int8 >()), sstd::num_mat_c_int8  ); }
TEST(typeNum, type2num_mat_c_int16 ){ ASSERT_EQ(sstd::type2num(sstd::mat_c<      int16>()), sstd::num_mat_c_int16 ); }
TEST(typeNum, type2num_mat_c_int32 ){ ASSERT_EQ(sstd::type2num(sstd::mat_c<      int32>()), sstd::num_mat_c_int32 ); }
TEST(typeNum, type2num_mat_c_int64 ){ ASSERT_EQ(sstd::type2num(sstd::mat_c<      int64>()), sstd::num_mat_c_int64 ); }
TEST(typeNum, type2num_mat_c_uint8 ){ ASSERT_EQ(sstd::type2num(sstd::mat_c<     uint8 >()), sstd::num_mat_c_uint8 ); }
TEST(typeNum, type2num_mat_c_uint16){ ASSERT_EQ(sstd::type2num(sstd::mat_c<     uint16>()), sstd::num_mat_c_uint16); }
TEST(typeNum, type2num_mat_c_uint32){ ASSERT_EQ(sstd::type2num(sstd::mat_c<     uint32>()), sstd::num_mat_c_uint32); }
TEST(typeNum, type2num_mat_c_uint64){ ASSERT_EQ(sstd::type2num(sstd::mat_c<     uint64>()), sstd::num_mat_c_uint64); }
TEST(typeNum, type2num_mat_c_float ){ ASSERT_EQ(sstd::type2num(sstd::mat_c<      float>()), sstd::num_mat_c_float ); }
TEST(typeNum, type2num_mat_c_double){ ASSERT_EQ(sstd::type2num(sstd::mat_c<     double>()), sstd::num_mat_c_double); }
TEST(typeNum, type2num_mat_c_str   ){ ASSERT_EQ(sstd::type2num(sstd::mat_c<std::string>()), sstd::num_mat_c_str   ); }

TEST(typeNum, type2num_mat_r_bool  ){ ASSERT_EQ(sstd::type2num(sstd::mat_r<       bool>()), sstd::num_mat_r_bool  ); }
TEST(typeNum, type2num_mat_r_char  ){ ASSERT_EQ(sstd::type2num(sstd::mat_r<       char>()), sstd::num_mat_r_char  ); }
//TEST(typeNum, type2num_mat_r_uchar ){ ASSERT_EQ(sstd::type2num(sstd::mat_r<      uchar>()), sstd::num_mat_r_uchar ); } // same as uint8
TEST(typeNum, type2num_mat_r_int8  ){ ASSERT_EQ(sstd::type2num(sstd::mat_r<      int8 >()), sstd::num_mat_r_int8  ); }
TEST(typeNum, type2num_mat_r_int16 ){ ASSERT_EQ(sstd::type2num(sstd::mat_r<      int16>()), sstd::num_mat_r_int16 ); }
TEST(typeNum, type2num_mat_r_int32 ){ ASSERT_EQ(sstd::type2num(sstd::mat_r<      int32>()), sstd::num_mat_r_int32 ); }
TEST(typeNum, type2num_mat_r_int64 ){ ASSERT_EQ(sstd::type2num(sstd::mat_r<      int64>()), sstd::num_mat_r_int64 ); }
TEST(typeNum, type2num_mat_r_uint8 ){ ASSERT_EQ(sstd::type2num(sstd::mat_r<     uint8 >()), sstd::num_mat_r_uint8 ); }
TEST(typeNum, type2num_mat_r_uint16){ ASSERT_EQ(sstd::type2num(sstd::mat_r<     uint16>()), sstd::num_mat_r_uint16); }
TEST(typeNum, type2num_mat_r_uint32){ ASSERT_EQ(sstd::type2num(sstd::mat_r<     uint32>()), sstd::num_mat_r_uint32); }
TEST(typeNum, type2num_mat_r_uint64){ ASSERT_EQ(sstd::type2num(sstd::mat_r<     uint64>()), sstd::num_mat_r_uint64); }
TEST(typeNum, type2num_mat_r_float ){ ASSERT_EQ(sstd::type2num(sstd::mat_r<      float>()), sstd::num_mat_r_float ); }
TEST(typeNum, type2num_mat_r_double){ ASSERT_EQ(sstd::type2num(sstd::mat_r<     double>()), sstd::num_mat_r_double); }
TEST(typeNum, type2num_mat_r_str   ){ ASSERT_EQ(sstd::type2num(sstd::mat_r<std::string>()), sstd::num_mat_r_str   ); }

TEST(typeNum, type2num_hash_str_bool  ){ ASSERT_EQ(sstd::type2num(std::unordered_map<std::string,       bool>()), sstd::num_hash_str_bool  ); }
TEST(typeNum, type2num_hash_str_char  ){ ASSERT_EQ(sstd::type2num(std::unordered_map<std::string,       char>()), sstd::num_hash_str_char  ); }
//TEST(typeNum, type2num_hash_str_uchar ){ ASSERT_EQ(sstd::type2num(std::unordered_map<std::string,      uchar>()), sstd::num_hash_str_uchar ); } // same as uint8
TEST(typeNum, type2num_hash_str_int8  ){ ASSERT_EQ(sstd::type2num(std::unordered_map<std::string,      int8 >()), sstd::num_hash_str_int8  ); }
TEST(typeNum, type2num_hash_str_int16 ){ ASSERT_EQ(sstd::type2num(std::unordered_map<std::string,      int16>()), sstd::num_hash_str_int16 ); }
TEST(typeNum, type2num_hash_str_int32 ){ ASSERT_EQ(sstd::type2num(std::unordered_map<std::string,      int32>()), sstd::num_hash_str_int32 ); }
TEST(typeNum, type2num_hash_str_int64 ){ ASSERT_EQ(sstd::type2num(std::unordered_map<std::string,      int64>()), sstd::num_hash_str_int64 ); }
TEST(typeNum, type2num_hash_str_uint8 ){ ASSERT_EQ(sstd::type2num(std::unordered_map<std::string,     uint8 >()), sstd::num_hash_str_uint8 ); }
TEST(typeNum, type2num_hash_str_uint16){ ASSERT_EQ(sstd::type2num(std::unordered_map<std::string,     uint16>()), sstd::num_hash_str_uint16); }
TEST(typeNum, type2num_hash_str_uint32){ ASSERT_EQ(sstd::type2num(std::unordered_map<std::string,     uint32>()), sstd::num_hash_str_uint32); }
TEST(typeNum, type2num_hash_str_uint64){ ASSERT_EQ(sstd::type2num(std::unordered_map<std::string,     uint64>()), sstd::num_hash_str_uint64); }
TEST(typeNum, type2num_hash_str_float ){ ASSERT_EQ(sstd::type2num(std::unordered_map<std::string,      float>()), sstd::num_hash_str_float ); }
TEST(typeNum, type2num_hash_str_double){ ASSERT_EQ(sstd::type2num(std::unordered_map<std::string,     double>()), sstd::num_hash_str_double); }
TEST(typeNum, type2num_hash_str_str   ){ ASSERT_EQ(sstd::type2num(std::unordered_map<std::string,std::string>()), sstd::num_hash_str_str   ); }

TEST(typeNum, type2num_void_ptr      ){ ASSERT_EQ(sstd::type2num(sstd::void_ptr()),                           sstd::num_void_ptr      ); }
TEST(typeNum, type2num_vec_void_ptr  ){ ASSERT_EQ(sstd::type2num(            std::vector<sstd::void_ptr> ()), sstd::num_vec_void_ptr  ); }
TEST(typeNum, type2num_vvec_void_ptr ){ ASSERT_EQ(sstd::type2num(std::vector<std::vector<sstd::void_ptr>>()), sstd::num_vvec_void_ptr ); }
TEST(typeNum, type2num_mat_c_void_ptr){ ASSERT_EQ(sstd::type2num(sstd::mat_c<sstd::void_ptr>()),              sstd::num_mat_c_void_ptr); }
TEST(typeNum, type2num_mat_r_void_ptr){ ASSERT_EQ(sstd::type2num(sstd::mat_r<sstd::void_ptr>()),              sstd::num_mat_r_void_ptr); }

TEST(typeNum, type2num_hash_str_void_ptr     ){ ASSERT_EQ(sstd::type2num(std::unordered_map<std::string,    sstd::void_ptr>()), sstd::num_hash_str_void_ptr     ); }
//TEST(typeNum, type2num_hash_void_ptr_void_ptr){ ASSERT_EQ(sstd::type2num(std::unordered_map<sstd::void_ptr, sstd::void_ptr>()), sstd::num_hash_void_ptr_void_ptr); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(typeNum, typeNum2str_num_void){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_void).c_str(), "void"); }
TEST(typeNum, typeNum2str_num_len ){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_len ).c_str(), "len" ); }
TEST(typeNum, typeNum2str_num_err ){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_err ).c_str(), "err" ); }
TEST(typeNum, typeNum2str_num_null){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_null).c_str(), "null"); }

TEST(typeNum, typeNum2str_num_bool  ){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_bool  ).c_str(),  "bool" ); }
TEST(typeNum, typeNum2str_num_char  ){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_char  ).c_str(),  "char" ); }
TEST(typeNum, typeNum2str_num_uchar ){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_uchar ).c_str(),  "uchar"); }
TEST(typeNum, typeNum2str_num_int8  ){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_int8  ).c_str(),  "int8" ); }
TEST(typeNum, typeNum2str_num_int16 ){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_int16 ).c_str(),  "int16"); }
TEST(typeNum, typeNum2str_num_int32 ){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_int32 ).c_str(),  "int32"); }
TEST(typeNum, typeNum2str_num_int64 ){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_int64 ).c_str(),  "int64"); }
TEST(typeNum, typeNum2str_num_uint8 ){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_uint8 ).c_str(), "uint8" ); }
TEST(typeNum, typeNum2str_num_uint16){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_uint16).c_str(), "uint16"); }
TEST(typeNum, typeNum2str_num_uint32){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_uint32).c_str(), "uint32"); }
TEST(typeNum, typeNum2str_num_uint64){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_uint64).c_str(), "uint64"); }
TEST(typeNum, typeNum2str_num_float ){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_float).c_str(),  "float" ); }
TEST(typeNum, typeNum2str_num_double){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_double).c_str(), "double"); }
TEST(typeNum, typeNum2str_num_str   ){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_str).c_str(),    "str"   ); }

TEST(typeNum, typeNum2str_num_void_ptr         ){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_void_ptr         ).c_str(), "void_ptr"         ); }
TEST(typeNum, typeNum2str_num_vec_void_ptr     ){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_vec_void_ptr     ).c_str(), "vec_void_ptr"     ); }
TEST(typeNum, typeNum2str_num_hash_str_void_ptr){ ASSERT_STREQ(sstd::typeNum2str(sstd::num_hash_str_void_ptr).c_str(), "hash_str_void_ptr"); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
