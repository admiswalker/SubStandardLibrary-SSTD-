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

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
