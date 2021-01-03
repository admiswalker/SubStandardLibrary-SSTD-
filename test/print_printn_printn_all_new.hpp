#pragma once


//-----------------------------------------------------------------------------------------------------------------------------------------------
// print_woLF

TEST(print_new, print_woLF_bool){
    {
        bool tf = true;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(tf);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "T");
    }
    {
        bool tf = false;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(tf);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "F");
    }
}
TEST(print_new, print_woLF_char){
    {
        char c = ' ';
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "' '");
    }
    {
        char c = 'A';
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "'A'");
    }
    {
        char c = 'z';
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "'z'");
    }
    {
        char c = '~';
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "'~'");
    }
}
TEST(print_new, print_woLF_i8){
    {
        int8 i = -128;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "-128");
    }
    {
        int8 i = 0;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0");
    }
    {
        int8 i = 127;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "127");
    }
}
TEST(print_new, print_woLF_i16){
    {
        int16 i = -32768;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "-32768");
    }
    {
        int16 i = 0;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0");
    }
    {
        int16 i = 32767;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "32767");
    }
}
TEST(print_new, print_woLF_i32){
    {
        int32 i = -2147483648;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "-2147483648");
    }
    {
        int32 i = 0;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0");
    }
    {
        int32 i = 2147483647;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "2147483647");
    }
}
TEST(print_new, print_woLF_i64){
    {
        int64 i = -9223372036854775808ll;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "-9223372036854775808");
    }
    {
        int64 i = 0;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0");
    }
    {
        int64 i = 9223372036854775807ll;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "9223372036854775807");
    }
}

//----------------------------------------------------------------------

TEST(print_new, print_woLF_u8){
    {
        uint8 i = 0;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0");
    }
    {
        uint8 i = 255;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "255");
    }
}
TEST(print_new, print_woLF_u16){
    {
        uint16 i = 0;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0");
    }
    {
        uint16 i = 65535;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "65535");
    }
}
TEST(print_new, print_woLF_u32){
    {
        uint32 i = 0;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0");
    }
    {
        uint32 i = 4294967295;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "4294967295");
    }
}
TEST(print_new, print_woLF_u64){
    {
        uint64 i = 0;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0");
    }
    {
        uint64 i = 18446744073709551615ull;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "18446744073709551615");
    }
}

//----------------------------------------------------------------------

TEST(print_new, print_woLF_float){
    {
        float i = 0.0;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0.");
    }
    {
        float i = 1234.4321;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "1234.43");
    }
}
TEST(print_new, print_woLF_double){
    {
        double i = 0.0;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0.");
    }
    {
        double i = 1234.4321;
        testing::internal::CaptureStdout();
        sstd::print_woLF_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "1234.43");
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// print

TEST(print_new, print_bool){
    {
        bool tf = true;
        testing::internal::CaptureStdout();
        sstd::print_new(tf);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "T\n");
    }
    {
        bool tf = false;
        testing::internal::CaptureStdout();
        sstd::print_new(tf);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "F\n");
    }
}
TEST(print_new, print_char){
    {
        char c = ' ';
        testing::internal::CaptureStdout();
        sstd::print_new(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "' '\n");
    }
    {
        char c = 'A';
        testing::internal::CaptureStdout();
        sstd::print_new(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "'A'\n");
    }
    {
        char c = 'z';
        testing::internal::CaptureStdout();
        sstd::print_new(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "'z'\n");
    }
    {
        char c = '~';
        testing::internal::CaptureStdout();
        sstd::print_new(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "'~'\n");
    }
}
TEST(print_new, print_i8){
    {
        int8 i = -128;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "-128\n");
    }
    {
        int8 i = 0;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0\n");
    }
    {
        int8 i = 127;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "127\n");
    }
}
TEST(print_new, print_i16){
    {
        int16 i = -32768;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "-32768\n");
    }
    {
        int16 i = 0;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0\n");
    }
    {
        int16 i = 32767;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "32767\n");
    }
}
TEST(print_new, print_i32){
    {
        int32 i = -2147483648;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "-2147483648\n");
    }
    {
        int32 i = 0;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0\n");
    }
    {
        int32 i = 2147483647;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "2147483647\n");
    }
}
TEST(print_new, print_i64){
    {
        int64 i = -9223372036854775808ll;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "-9223372036854775808\n");
    }
    {
        int64 i = 0;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0\n");
    }
    {
        int64 i = 9223372036854775807ll;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "9223372036854775807\n");
    }
}

//----------------------------------------------------------------------

TEST(print_new, print_u8){
    {
        uint8 i = 0;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0\n");
    }
    {
        uint8 i = 255;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "255\n");
    }
}
TEST(print_new, print_u16){
    {
        uint16 i = 0;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0\n");
    }
    {
        uint16 i = 65535;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "65535\n");
    }
}
TEST(print_new, print_u32){
    {
        uint32 i = 0;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0\n");
    }
    {
        uint32 i = 4294967295;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "4294967295\n");
    }
}
TEST(print_new, print_u64){
    {
        uint64 i = 0;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0\n");
    }
    {
        uint64 i = 18446744073709551615ull;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "18446744073709551615\n");
    }
}

//----------------------------------------------------------------------

TEST(print_new, print_float){
    {
        float i = 0.0;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0.\n");
    }
    {
        float i = 1234.4321;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "1234.43\n");
    }
}
TEST(print_new, print_double){
    {
        double i = 0.0;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0.\n");
    }
    {
        double i = 1234.4321;
        testing::internal::CaptureStdout();
        sstd::print_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "1234.43\n");
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for_printn

TEST(print_new, for_printn_bool){
    {
        bool tf = true;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(tf);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = T\n");
    }
    {
        bool tf = false;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(tf);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = F\n");
    }
}
TEST(print_new, for_printn_char){
    {
        char c = ' ';
        testing::internal::CaptureStdout();
        sstd::for_printn_new(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = ' '\n");
    }
    {
        char c = 'A';
        testing::internal::CaptureStdout();
        sstd::for_printn_new(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 'A'\n");
    }
    {
        char c = 'z';
        testing::internal::CaptureStdout();
        sstd::for_printn_new(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 'z'\n");
    }
    {
        char c = '~';
        testing::internal::CaptureStdout();
        sstd::for_printn_new(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = '~'\n");
    }
}
TEST(print_new, for_printn_i8){
    {
        int8 i = -128;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = -128\n");
    }
    {
        int8 i = 0;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0\n");
    }
    {
        int8 i = 127;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 127\n");
    }
}
TEST(print_new, for_printn_i16){
    {
        int16 i = -32768;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = -32768\n");
    }
    {
        int16 i = 0;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0\n");
    }
    {
        int16 i = 32767;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 32767\n");
    }
}
TEST(print_new, for_printn_i32){
    {
        int32 i = -2147483648;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = -2147483648\n");
    }
    {
        int32 i = 0;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0\n");
    }
    {
        int32 i = 2147483647;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 2147483647\n");
    }
}
TEST(print_new, for_printn_i64){
    {
        int64 i = -9223372036854775808ll;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = -9223372036854775808\n");
    }
    {
        int64 i = 0;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0\n");
    }
    {
        int64 i = 9223372036854775807ll;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 9223372036854775807\n");
    }
}

//----------------------------------------------------------------------

TEST(print_new, for_printn_u8){
    {
        uint8 i = 0;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0\n");
    }
    {
        uint8 i = 255;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 255\n");
    }
}
TEST(print_new, for_printn_u16){
    {
        uint16 i = 0;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0\n");
    }
    {
        uint16 i = 65535;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 65535\n");
    }
}
TEST(print_new, for_printn_u32){
    {
        uint32 i = 0;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0\n");
    }
    {
        uint32 i = 4294967295;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 4294967295\n");
    }
}
TEST(print_new, for_printn_u64){
    {
        uint64 i = 0;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0\n");
    }
    {
        uint64 i = 18446744073709551615ull;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 18446744073709551615\n");
    }
}

//----------------------------------------------------------------------

TEST(print_new, for_printn_float){
    {
        float i = 0.0;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0.\n");
    }
    {
        float i = 1234.4321;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 1234.43\n");
    }
}
TEST(print_new, for_printn_double){
    {
        double i = 0.0;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 0.\n");
    }
    {
        double i = 1234.4321;
        testing::internal::CaptureStdout();
        sstd::for_printn_new(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), " = 1234.43\n");
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------------------------------


TEST(print_new, print){
    int i=0;
    sstd::printn_new(i);
}
TEST(print_new, print_v){
    std::vector<int> v={1,2,3};
    sstd::printn_new(v);
}
TEST(print_new, print_vv){
    std::vector<std::vector<int>> vv = {{1,2,3}, {4,5,6}};
    sstd::printn_new(vv);
}
TEST(print_new, print_vvv){
    std::vector<std::vector<std::vector<int>>> vvv = {{{1,2,3},{4,5,6}}, {{7,8,9},{10,11,12}}};
    sstd::printn_new(vvv);
}
TEST(print_new, print_vvvv){
    std::vector<std::vector<std::vector<std::vector<int>>>> vvvv = { {{{1,2,3},{4,5,6}}, {{7,8,9},{10,11,12}}}, {{{13,14,15},{16,17,18}}, {{19,20,21},{22,23,24}}} };
    sstd::printn_new(vvvv);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
