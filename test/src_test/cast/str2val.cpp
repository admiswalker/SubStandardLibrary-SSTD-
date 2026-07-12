#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// char*

TEST(str2val, type_char_C){
    bool tf;
    char res;
    res='\0'; tf=sstd::str2val(res,       "a"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, 'a');
    res='a';  tf=sstd::str2val(res, "invalid"); ASSERT_EQ(tf, false); ASSERT_EQ(res, 'a');
}
TEST(str2val, type_string_C){
    bool tf;
    std::string res;
    res=1.0; tf=sstd::str2val(res, "abcd"); ASSERT_EQ(tf, true); ASSERT_EQ(res, std::string("abcd"));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// std::string

TEST(str2val, type_bool_S){
    bool tf;
    bool res;

    // True
    res=false; tf=sstd::str2val(res, std::string("true" )); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    res=false; tf=sstd::str2val(res, std::string("t"    )); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    
    res=false; tf=sstd::str2val(res, std::string("yes"  )); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    res=false; tf=sstd::str2val(res, std::string("y"    )); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    
    res=false; tf=sstd::str2val(res, std::string("on"   )); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    
    res=false; tf=sstd::str2val(res, std::string("1"    )); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);

    // False
    res=true;  tf=sstd::str2val(res, std::string("false")); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    res=true;  tf=sstd::str2val(res, std::string("f"    )); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    
    res=true;  tf=sstd::str2val(res, std::string("no"   )); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    res=true;  tf=sstd::str2val(res, std::string("n"    )); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    
    res=true;  tf=sstd::str2val(res, std::string("off"  )); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    
    res=true;  tf=sstd::str2val(res, std::string("0"    )); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    
    // True others
    res=false; tf=sstd::str2val(res, std::string("True" )); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    res=false; tf=sstd::str2val(res, std::string("TRUE" )); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    res=false; tf=sstd::str2val(res, std::string("tRuE" )); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    res=false; tf=sstd::str2val(res, std::string("T"    )); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    
    // False others
    res=true;  tf=sstd::str2val(res, std::string("False")); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    res=true;  tf=sstd::str2val(res, std::string("FALSE")); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    res=true;  tf=sstd::str2val(res, std::string("falsE")); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    res=true;  tf=sstd::str2val(res, std::string("F"    )); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    
    // Error
    res=true;  tf=sstd::str2val(res, std::string("invalid")); ASSERT_EQ(tf, false); ASSERT_EQ(res, true);
    res=true;  tf=sstd::str2val(res, std::string("x"      )); ASSERT_EQ(tf, false); ASSERT_EQ(res, true);
}
TEST(str2val, type_char_S){
    bool tf;
    char res;
    res='\0'; tf=sstd::str2val(res, std::string(      "a")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, 'a');
    res='a';  tf=sstd::str2val(res, std::string("invalid")); ASSERT_EQ(tf, false); ASSERT_EQ(res, 'a');
}
TEST(str2val, type_int8_S){
    bool tf;
    int8 res;
    res=1; tf=sstd::str2val(res, std::string(   "-128")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int8)-128);
    res=1; tf=sstd::str2val(res, std::string(      "0")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int8)   0);
    res=1; tf=sstd::str2val(res, std::string(    "127")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int8) 127);
    res=1; tf=sstd::str2val(res, std::string("invalid")); ASSERT_EQ(tf, false); ASSERT_EQ(res, (int8)   0);
}
TEST(str2val, type_int16_S){
    bool tf;
    int16 res;
    res=1; tf=sstd::str2val(res, std::string( "-32768")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int16)-32768);
    res=1; tf=sstd::str2val(res, std::string(      "0")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int16)     0);
    res=1; tf=sstd::str2val(res, std::string(  "32767")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int16) 32767);
    res=1; tf=sstd::str2val(res, std::string("invalid")); ASSERT_EQ(tf, false); ASSERT_EQ(res, (int16)     0);
}
TEST(str2val, type_int32_S){
    bool tf;
    int32 res;
    res=1; tf=sstd::str2val(res, std::string("-2147483648")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int32)-2147483648);
    res=1; tf=sstd::str2val(res, std::string(          "0")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int32)          0);
    res=1; tf=sstd::str2val(res, std::string( "2147483647")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int32) 2147483647);
    res=1; tf=sstd::str2val(res, std::string(    "invalid")); ASSERT_EQ(tf, false); ASSERT_EQ(res, (int32)          0);
}
TEST(str2val, type_int64_S){
    bool tf;
    int64 res;
//  res=1; tf=sstd::str2val(res, std::string("-9223372036854775808")); ASSERT_EQ(tf, true); ASSERT_EQ(res, (int64)-9223372036854775808ll); // Commenting out this line in order to suppress the bagged warning of GCC.
    res=1; tf=sstd::str2val(res, std::string(                   "0")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int64)                   0  );
    res=1; tf=sstd::str2val(res, std::string( "9223372036854775807")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int64) 9223372036854775807ll);
    res=1; tf=sstd::str2val(res, std::string(             "invalid")); ASSERT_EQ(tf, false); ASSERT_EQ(res, (int64)                   0  );
}
TEST(str2val, type_uint8_S){
    bool tf;
    uint8 res;
    res=1; tf=sstd::str2val(res, std::string(      "0")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (uint8)  0);
    res=1; tf=sstd::str2val(res, std::string(    "255")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (uint8)255);
    res=1; tf=sstd::str2val(res, std::string("invalid")); ASSERT_EQ(tf, false); ASSERT_EQ(res, (uint8)  0);
}
TEST(str2val, type_uint16_S){
    bool tf;
    uint16 res;
    res=1; tf=sstd::str2val(res, std::string(      "0")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (uint16)    0);
    res=1; tf=sstd::str2val(res, std::string(  "65535")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (uint16)65535);
    res=1; tf=sstd::str2val(res, std::string("invalid")); ASSERT_EQ(tf, false); ASSERT_EQ(res, (uint16)    0);
}
TEST(str2val, type_uint32_S){
    bool tf;
    uint32 res;
    res=1; tf=sstd::str2val(res, std::string(         "0")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (uint32)         0);
    res=1; tf=sstd::str2val(res, std::string("4294967295")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (uint32)4294967295);
    res=1; tf=sstd::str2val(res, std::string(   "invalid")); ASSERT_EQ(tf, false); ASSERT_EQ(res, (uint32)         0);
}
TEST(str2val, type_uint64_S){
    bool tf;
    uint64 res;
    res=1; tf=sstd::str2val(res, std::string(                   "0")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (uint64)                   0   );
    res=1; tf=sstd::str2val(res, std::string("18446744073709551615")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (uint64)18446744073709551615ull);
    res=1; tf=sstd::str2val(res, std::string(             "invalid")); ASSERT_EQ(tf, false); ASSERT_EQ(res, (uint64)                   0   );
}
TEST(str2val, type_float_S){
    bool tf;
    float res;
    res=1.0; tf=sstd::str2val(res, std::string( "-1.234")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (float)-1.234);
    res=1.0; tf=sstd::str2val(res, std::string(    "0.0")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (float) 0.0  );
    res=1.0; tf=sstd::str2val(res, std::string(  "1.234")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (float) 1.234);
    res=1.0; tf=sstd::str2val(res, std::string("invalid")); ASSERT_EQ(tf, false); ASSERT_EQ(res, (float) 0.0  );
}
TEST(str2val, type_double_S){
    bool tf;
    double res;
    res=1.0; tf=sstd::str2val(res, std::string( "-1.234")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (double)-1.234);
    res=1.0; tf=sstd::str2val(res, std::string(    "0.0")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (double) 0.0  );
    res=1.0; tf=sstd::str2val(res, std::string(  "1.234")); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (double) 1.234);
    
    res=1.0; tf=sstd::str2val(res, std::string("invalid")); ASSERT_EQ(tf, false); ASSERT_EQ(res, (double) 0.0  );
}
TEST(str2val, type_string_S){
    bool tf;
    std::string res;
    res=1.0; tf=sstd::str2val(res, std::string("abcd")); ASSERT_EQ(tf, true); ASSERT_EQ(res, std::string("abcd"));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Interface test only

TEST(str2val, type_bool_vec  ){  bool  res; bool tf=sstd::str2val(res, std::vector<std::string>({"true"})); ASSERT_EQ(tf, true); ASSERT_EQ(res, ( bool )true); }
TEST(str2val, type_char_vec  ){  char  res; bool tf=sstd::str2val(res, std::vector<std::string>({"a"})); ASSERT_EQ(tf, true); ASSERT_EQ(res, ( char )'a'); }
TEST(str2val, type_int8_vec  ){  int8  res; bool tf=sstd::str2val(res, std::vector<std::string>({"1"})); ASSERT_EQ(tf, true); ASSERT_EQ(res, ( int8 )1); }
TEST(str2val, type_int16_vec ){  int16 res; bool tf=sstd::str2val(res, std::vector<std::string>({"1"})); ASSERT_EQ(tf, true); ASSERT_EQ(res, ( int16)1); }
TEST(str2val, type_int32_vec ){  int32 res; bool tf=sstd::str2val(res, std::vector<std::string>({"1"})); ASSERT_EQ(tf, true); ASSERT_EQ(res, ( int32)1); }
TEST(str2val, type_int64_vec ){  int64 res; bool tf=sstd::str2val(res, std::vector<std::string>({"1"})); ASSERT_EQ(tf, true); ASSERT_EQ(res, ( int64)1); }
TEST(str2val, type_uint8_vec ){ uint8  res; bool tf=sstd::str2val(res, std::vector<std::string>({"1"})); ASSERT_EQ(tf, true); ASSERT_EQ(res, (uint8 )1); }
TEST(str2val, type_uint16_vec){ uint16 res; bool tf=sstd::str2val(res, std::vector<std::string>({"1"})); ASSERT_EQ(tf, true); ASSERT_EQ(res, (uint16)1); }
TEST(str2val, type_uint32_vec){ uint32 res; bool tf=sstd::str2val(res, std::vector<std::string>({"1"})); ASSERT_EQ(tf, true); ASSERT_EQ(res, (uint32)1); }
TEST(str2val, type_uint64_vec){ uint64 res; bool tf=sstd::str2val(res, std::vector<std::string>({"1"})); ASSERT_EQ(tf, true); ASSERT_EQ(res, (uint64)1); }
TEST(str2val, type_float_vec ){ float  res; bool tf=sstd::str2val(res, std::vector<std::string>({"1"})); ASSERT_EQ(tf, true); ASSERT_EQ(res, (float )1); }
TEST(str2val, type_double_vec){ double res; bool tf=sstd::str2val(res, std::vector<std::string>({"1"})); ASSERT_EQ(tf, true); ASSERT_EQ(res, (double)1); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Interface test only

TEST(str2val, type_vbool_vec  ){ std::vector< bool > res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"true","true"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector< bool >({true,true})); }
TEST(str2val, type_vchar_vec  ){ std::vector< char > res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"a","b"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector< char >({'a','b'})); }
TEST(str2val, type_vint8_vec  ){ std::vector< int8 > res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector< int8 >({1,2})); }
TEST(str2val, type_vint16_vec ){ std::vector< int16> res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector< int16>({1,2})); }
TEST(str2val, type_vint32_vec ){ std::vector< int32> res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector< int32>({1,2})); }
TEST(str2val, type_vint64_vec ){ std::vector< int64> res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector< int64>({1,2})); }
TEST(str2val, type_vuint8_vec ){ std::vector<uint8 > res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector<uint8 >({1,2})); }
TEST(str2val, type_vuint16_vec){ std::vector<uint16> res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector<uint16>({1,2})); }
TEST(str2val, type_vuint32_vec){ std::vector<uint32> res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector<uint32>({1,2})); }
TEST(str2val, type_vuint64_vec){ std::vector<uint64> res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector<uint64>({1,2})); }
TEST(str2val, type_vfloat_vec ){ std::vector<float > res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector<float >({1,2})); }
TEST(str2val, type_vdouble_vec){ std::vector<double> res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector<double>({1,2})); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
