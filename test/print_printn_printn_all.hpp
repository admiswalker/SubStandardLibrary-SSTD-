#pragma once


//-----------------------------------------------------------------------------------------------------------------------------------------------
// for_printn

TEST(print, for_printn_bool){
    {
        bool tf = true;
        testing::internal::CaptureStdout();
        sstd::for_printn(tf);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = true\n");
    }
    {
        bool tf = false;
        testing::internal::CaptureStdout();
        sstd::for_printn(tf);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = false\n");
    }
}
TEST(print, for_printn_char){
    {
        char c = ' ';
        testing::internal::CaptureStdout();
        sstd::for_printn(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = ' '\n");
    }
    {
        char c = 'A';
        testing::internal::CaptureStdout();
        sstd::for_printn(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 'A'\n");
    }
    {
        char c = 'z';
        testing::internal::CaptureStdout();
        sstd::for_printn(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 'z'\n");
    }
    {
        char c = '~';
        testing::internal::CaptureStdout();
        sstd::for_printn(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = '~'\n");
    }
}
TEST(print, for_printn_i8){
    {
        int8 i = -128;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = -128\n");
    }
    {
        int8 i = 0;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0\n");
    }
    {
        int8 i = 127;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 127\n");
    }
}
TEST(print, for_printn_i16){
    {
        int16 i = -32768;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = -32768\n");
    }
    {
        int16 i = 0;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0\n");
    }
    {
        int16 i = 32767;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 32767\n");
    }
}
TEST(print, for_printn_i32){
    {
        int32 i = -2147483648;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = -2147483648\n");
    }
    {
        int32 i = 0;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0\n");
    }
    {
        int32 i = 2147483647;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 2147483647\n");
    }
}
TEST(print, for_printn_i64){
    {
        int64 i = -9223372036854775808ll;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = -9223372036854775808\n");
    }
    {
        int64 i = 0;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0\n");
    }
    {
        int64 i = 9223372036854775807ll;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 9223372036854775807\n");
    }
}

//----------------------------------------------------------------------

TEST(print, for_printn_u8){
    {
        uint8 i = 0;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0\n");
    }
    {
        uint8 i = 255;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 255\n");
    }
}
TEST(print, for_printn_u16){
    {
        uint16 i = 0;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0\n");
    }
    {
        uint16 i = 65535;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 65535\n");
    }
}
TEST(print, for_printn_u32){
    {
        uint32 i = 0;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0\n");
    }
    {
        uint32 i = 4294967295;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 4294967295\n");
    }
}
TEST(print, for_printn_u64){
    {
        uint64 i = 0;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0\n");
    }
    {
        uint64 i = 18446744073709551615ull;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 18446744073709551615\n");
    }
}

//----------------------------------------------------------------------

TEST(print, for_printn_float){
    {
        float i = 0.0;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0.\n");
    }
    {
        float i = 1234.4321;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 1234.43\n");
    }
}
TEST(print, for_printn_double){
    {
        double i = 0.0;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0.\n");
    }
    {
        double i = 1234.4321;
        testing::internal::CaptureStdout();
        sstd::for_printn(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 1234.43\n");
    }
}

//----------------------------------------------------------------------

TEST(print, for_printn_charP){
    const char* i = "abc ABCd";
    testing::internal::CaptureStdout();
    sstd::for_printn(i);
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = \"abc ABCd\"\n");
}
TEST(print, for_printn_str){
    const std::string i = "abc ABCd";
    testing::internal::CaptureStdout();
    sstd::for_printn(i);
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = \"abc ABCd\"\n");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for std::vector<T>

TEST(print, for_printn_vector){
    std::vector<int> v={1,2,3};
    testing::internal::CaptureStdout();
    sstd::for_printn(v);
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = [1 2 3]\n");
}

// Recursive call for deep std::vector<std::vector<... std::vector<T>... >>.
TEST(print, for_printn_vector_re_depth2){
    std::vector<std::vector<int>> vv = {{1,2,3}, {4,5,6}};
    testing::internal::CaptureStdout();
    sstd::for_printn(vv);
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = [[1 2 3] [4 5 6]]\n");
}
TEST(print, for_printn_vector_re_depth3){
    std::vector<std::vector<std::vector<int>>> vvv = {{{1,2,3},{4,5,6}}, {{7,8,9},{10,11,12}}};
    testing::internal::CaptureStdout();
    sstd::for_printn(vvv);
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = [[[1 2 3] [4 5 6]] [[7 8 9] [10 11 12]]]\n");
}
TEST(print, for_printn_vector_re_depth4){
    std::vector<std::vector<std::vector<std::vector<int>>>> vvvv = { {{{1,2,3},{4,5,6}}, {{7,8,9},{10,11,12}}}, {{{13,14,15},{16,17,18}}, {{19,20,21},{22,23,24}}} };
    testing::internal::CaptureStdout();
    sstd::for_printn(vvvv);
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = [[[[1 2 3] [4 5 6]] [[7 8 9] [10 11 12]]] [[[13 14 15] [16 17 18]] [[19 20 21] [22 23 24]]]]\n");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for #define printn

TEST(print, printn){
    int valName=0;
    testing::internal::CaptureStdout();
    sstd::printn(valName);
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "valName = 0\n");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
