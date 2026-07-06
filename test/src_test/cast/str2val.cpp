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
    res=true;  tf=sstd::str2val(res, "undefined-value"); ASSERT_EQ(tf, false); ASSERT_EQ(res, true);
    res=true;  tf=sstd::str2val(res, "x"              ); ASSERT_EQ(tf, false); ASSERT_EQ(res, true);
}
TEST(str2val, type_char){
    bool tf;
    char res;
    res='\0'; tf=sstd::str2val(res, "a"); ASSERT_EQ(tf, true); ASSERT_EQ(res, 'a');
}
TEST(str2val, type_int8){
    bool tf;
    int8 res;
    res=0; tf=sstd::str2val(res,  "123"); ASSERT_EQ(tf, true); ASSERT_EQ(res,  123);
    res=0; tf=sstd::str2val(res, "-123"); ASSERT_EQ(tf, true); ASSERT_EQ(res, -123);
    // TODO: 境界テストの導入
}
TEST(str2val, type_int16){
    bool tf;
    int16 res;
    res=0; tf=sstd::str2val(res,  "123"); ASSERT_EQ(tf, true); ASSERT_EQ(res,  123);
    res=0; tf=sstd::str2val(res, "-123"); ASSERT_EQ(tf, true); ASSERT_EQ(res, -123);
    // TODO: 境界テストの導入
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
