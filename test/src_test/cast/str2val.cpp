#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(str2val, type_bool){
    bool tf;
    bool res;

    // True
    res=false; tf=sstd::str2val(res, "true" ); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    res=false; tf=sstd::str2val(res, "t"    ); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    
    res=false; tf=sstd::str2val(res, "yes"  ); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    res=false; tf=sstd::str2val(res, "y"    ); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    
    res=false; tf=sstd::str2val(res, "on"   ); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    
    res=false; tf=sstd::str2val(res, "1"    ); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);

    // False
    res=true;  tf=sstd::str2val(res, "false"); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    res=true;  tf=sstd::str2val(res, "f"    ); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    
    res=true;  tf=sstd::str2val(res, "no"   ); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    res=true;  tf=sstd::str2val(res, "n"    ); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    
    res=true;  tf=sstd::str2val(res, "off"  ); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    
    res=true;  tf=sstd::str2val(res, "0"    ); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    
    // True others
    res=false; tf=sstd::str2val(res, "True" ); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    res=false; tf=sstd::str2val(res, "TRUE" ); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    res=false; tf=sstd::str2val(res, "tRuE" ); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    res=false; tf=sstd::str2val(res, "T"    ); ASSERT_EQ(tf, true); ASSERT_EQ(res, true);
    
    // False others
    res=true;  tf=sstd::str2val(res, "False"); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    res=true;  tf=sstd::str2val(res, "FALSE"); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    res=true;  tf=sstd::str2val(res, "falsE"); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    res=true;  tf=sstd::str2val(res, "F"    ); ASSERT_EQ(tf, true); ASSERT_EQ(res, false);
    
    // Error
    res=true;  tf=sstd::str2val(res, "invalid"); ASSERT_EQ(tf, false); ASSERT_EQ(res, true);
    res=true;  tf=sstd::str2val(res, "x"      ); ASSERT_EQ(tf, false); ASSERT_EQ(res, true);
}
TEST(str2val, type_char){
    bool tf;
    char res;
    res='\0'; tf=sstd::str2val(res,       "a"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, 'a');
    res='a';  tf=sstd::str2val(res, "invalid"); ASSERT_EQ(tf, false); ASSERT_EQ(res, 'a');
}
TEST(str2val, type_int8){
    bool tf;
    int8 res;
    res=1; tf=sstd::str2val(res,    "-128"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int8)-128);
    res=1; tf=sstd::str2val(res,       "0"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int8)   0);
    res=1; tf=sstd::str2val(res,     "127"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int8) 127);
    res=1; tf=sstd::str2val(res, "invalid"); ASSERT_EQ(tf, false); ASSERT_EQ(res, (int8)   0);
}
TEST(str2val, type_int16){
    bool tf;
    int16 res;
    res=1; tf=sstd::str2val(res,  "-32768"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int16)-32768);
    res=1; tf=sstd::str2val(res,       "0"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int16)     0);
    res=1; tf=sstd::str2val(res,   "32767"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int16) 32767);
    res=1; tf=sstd::str2val(res, "invalid"); ASSERT_EQ(tf, false); ASSERT_EQ(res, (int16)     0);
}
TEST(str2val, type_int32){
    bool tf;
    int32 res;
    res=1; tf=sstd::str2val(res, "-2147483648"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int32)-2147483648);
    res=1; tf=sstd::str2val(res,           "0"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int32)          0);
    res=1; tf=sstd::str2val(res,  "2147483647"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int32) 2147483647);
    res=1; tf=sstd::str2val(res,     "invalid"); ASSERT_EQ(tf, false); ASSERT_EQ(res, (int32)          0);
}
TEST(str2val, type_int64){
    bool tf;
    int64 res;
//  res=1; tf=sstd::str2val(res, "-9223372036854775808"); ASSERT_EQ(tf, true); ASSERT_EQ(res, (int64)-9223372036854775808ll); // Commenting out this line in order to suppress the bagged warning of GCC.
    res=1; tf=sstd::str2val(res,                    "0"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int64)                   0  );
    res=1; tf=sstd::str2val(res,  "9223372036854775807"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (int64) 9223372036854775807ll);
    res=1; tf=sstd::str2val(res,              "invalid"); ASSERT_EQ(tf, false); ASSERT_EQ(res, (int64)                   0  );
}
TEST(str2val, type_uint8){
    bool tf;
    uint8 res;
    res=1; tf=sstd::str2val(res,       "0"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (uint8)  0);
    res=1; tf=sstd::str2val(res,     "255"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (uint8)255);
    res=1; tf=sstd::str2val(res, "invalid"); ASSERT_EQ(tf, false); ASSERT_EQ(res, (uint8)  0);
}
TEST(str2val, type_uint16){
    bool tf;
    uint16 res;
    res=1; tf=sstd::str2val(res,       "0"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (uint16)    0);
    res=1; tf=sstd::str2val(res,   "65535"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (uint16)65535);
    res=1; tf=sstd::str2val(res, "invalid"); ASSERT_EQ(tf, false); ASSERT_EQ(res, (uint16)    0);
}
TEST(str2val, type_uint32){
    bool tf;
    uint32 res;
    res=1; tf=sstd::str2val(res,          "0"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (uint32)         0);
    res=1; tf=sstd::str2val(res, "4294967295"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (uint32)4294967295);
    res=1; tf=sstd::str2val(res,    "invalid"); ASSERT_EQ(tf, false); ASSERT_EQ(res, (uint32)         0);
}
TEST(str2val, type_uint64){
    bool tf;
    uint64 res;
    res=1; tf=sstd::str2val(res,                    "0"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (uint64)                   0   );
    res=1; tf=sstd::str2val(res, "18446744073709551615"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (uint64)18446744073709551615ull);
    res=1; tf=sstd::str2val(res,              "invalid"); ASSERT_EQ(tf, false); ASSERT_EQ(res, (uint64)                   0   );
}
TEST(str2val, type_float){
    bool tf;
    float res;
    res=1.0; tf=sstd::str2val(res,  "-1.234"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (float)-1.234);
    res=1.0; tf=sstd::str2val(res,     "0.0"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (float) 0.0  );
    res=1.0; tf=sstd::str2val(res,   "1.234"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (float) 1.234);
    res=1.0; tf=sstd::str2val(res, "invalid"); ASSERT_EQ(tf, false); ASSERT_EQ(res, (float) 0.0  );
}
TEST(str2val, type_double){
    bool tf;
    double res;
    res=1.0; tf=sstd::str2val(res,  "-1.234"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (double)-1.234);
    res=1.0; tf=sstd::str2val(res,     "0.0"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (double) 0.0  );
    res=1.0; tf=sstd::str2val(res,   "1.234"); ASSERT_EQ(tf, true ); ASSERT_EQ(res, (double) 1.234);
    
    res=1.0; tf=sstd::str2val(res, "invalid"); ASSERT_EQ(tf, false); ASSERT_EQ(res, (double) 0.0  );
}
TEST(str2val, type_string){
    bool tf;
    std::string res;
    res=1.0; tf=sstd::str2val(res, "abcd"); ASSERT_EQ(tf, true); ASSERT_EQ(res, std::string("abcd"));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Interface test only

TEST(str2val, type_bool_vec  ){ std::vector< bool > res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"true","true"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector< bool >({true,true})); }
TEST(str2val, type_char_vec  ){ std::vector< char > res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"a","b"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector< char >({'a','b'})); }
TEST(str2val, type_int8_vec  ){ std::vector< int8 > res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector< int8 >({1,2})); }
TEST(str2val, type_int16_vec ){ std::vector< int16> res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector< int16>({1,2})); }
TEST(str2val, type_int32_vec ){ std::vector< int32> res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector< int32>({1,2})); }
TEST(str2val, type_int64_vec ){ std::vector< int64> res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector< int64>({1,2})); }
TEST(str2val, type_uint8_vec ){ std::vector<uint8 > res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector<uint8 >({1,2})); }
TEST(str2val, type_uint16_vec){ std::vector<uint16> res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector<uint16>({1,2})); }
TEST(str2val, type_uint32_vec){ std::vector<uint32> res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector<uint32>({1,2})); }
TEST(str2val, type_uint64_vec){ std::vector<uint64> res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector<uint64>({1,2})); }
TEST(str2val, type_float_vec ){ std::vector<float > res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector<float >({1,2})); }
TEST(str2val, type_double_vec){ std::vector<double> res_v; bool tf=sstd::str2val(res_v, std::vector<std::string>({"1","2"})); ASSERT_EQ(tf, true); ASSERT_EQ(res_v, std::vector<double>({1,2})); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
