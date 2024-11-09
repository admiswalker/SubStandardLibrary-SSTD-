#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// print

TEST(print, print_table){
    std::unordered_map<std::string, std::vector<uint>> table;
    table["abc"] = {123, 456};
    table["def"] = {456, 789};

    {
        testing::internal::CaptureStdout();
        sstd::print( table );

        std::string buf = testing::internal::GetCapturedStdout().c_str();
        bool tf1 = sstd::strcmp(buf, "[ [key: \"def\", value: [456 789]], [key: \"abc\", value: [123 456]] ]\n");
        if(tf1){
            ASSERT_STREQ(buf.c_str(), "[ [key: \"def\", value: [456 789]], [key: \"abc\", value: [123 456]] ]\n");
        }else{
            ASSERT_STREQ(buf.c_str(), "[ [key: \"abc\", value: [123 456]], [key: \"def\", value: [456 789]] ]\n");
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// print

TEST(print, print_voidp){
    {
        int8 i = 123;
        
        testing::internal::CaptureStdout();
        sstd::print(&i);
        std::string res = testing::internal::GetCapturedStdout();
        
        testing::internal::CaptureStdout();
        printf("%p\n", &i);
        std::string ans = testing::internal::GetCapturedStdout();
        
        ASSERT_STREQ(res.c_str(), ans.c_str());
    }
    {
        const char* pc = "abcdef";
        
        testing::internal::CaptureStdout();
        sstd::print(pc);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "\"abcdef\"\n");
    }
    {
        const char* pc = "abcdef";
        testing::internal::CaptureStdout();
        sstd::print((void*)pc);
        std::string res = testing::internal::GetCapturedStdout();
        
        testing::internal::CaptureStdout();
        printf("%p\n", pc);
        std::string ans = testing::internal::GetCapturedStdout();
        
        ASSERT_STREQ(res.c_str(), ans.c_str());
    }
}
TEST(print, print_bool){
    {
        bool tf = true;
        testing::internal::CaptureStdout();
        sstd::print(tf);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "true\n");
    }
    {
        bool tf = false;
        testing::internal::CaptureStdout();
        sstd::print(tf);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "false\n");
    }
}
TEST(print, print_char){
    {
        char c = ' ';
        testing::internal::CaptureStdout();
        sstd::print(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "' '\n");
    }
    {
        char c = 'A';
        testing::internal::CaptureStdout();
        sstd::print(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "'A'\n");
    }
    {
        char c = 'z';
        testing::internal::CaptureStdout();
        sstd::print(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "'z'\n");
    }
    {
        char c = '~';
        testing::internal::CaptureStdout();
        sstd::print(c);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "'~'\n");
    }
}
TEST(print, print_i8){
    {
        int8 i = -128;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "-128\n");
    }
    {
        int8 i = 0;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0\n");
    }
    {
        int8 i = 127;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "127\n");
    }
}
TEST(print, print_i16){
    {
        int16 i = -32768;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "-32768\n");
    }
    {
        int16 i = 0;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0\n");
    }
    {
        int16 i = 32767;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "32767\n");
    }
}
TEST(print, print_i32){
    {
        int32 i = -2147483648;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "-2147483648\n");
    }
    {
        int32 i = 0;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0\n");
    }
    {
        int32 i = 2147483647;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "2147483647\n");
    }
}
TEST(print, print_i64){
    {
        int64 i = -9223372036854775808ll;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "-9223372036854775808\n");
    }
    {
        int64 i = 0;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0\n");
    }
    {
        int64 i = 9223372036854775807ll;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "9223372036854775807\n");
    }
}

//----------------------------------------------------------------------

TEST(print, print_u8){
    {
        uint8 i = 0;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0\n");
    }
    {
        uint8 i = 255;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "255\n");
    }
}
TEST(print, print_u16){
    {
        uint16 i = 0;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0\n");
    }
    {
        uint16 i = 65535;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "65535\n");
    }
}
TEST(print, print_u32){
    {
        uint32 i = 0;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0\n");
    }
    {
        uint32 i = 4294967295;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "4294967295\n");
    }
}
TEST(print, print_u64){
    {
        uint64 i = 0;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0\n");
    }
    {
        uint64 i = 18446744073709551615ull;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "18446744073709551615\n");
    }
}

//----------------------------------------------------------------------

TEST(print, print_float){
    {
        float i = 0.0;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0.\n");
    }
    {
        float i = 1234.4321;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "1234.43\n");
    }
}
TEST(print, print_double){
    {
        double i = 0.0;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "0.\n");
    }
    {
        double i = 1234.4321;
        testing::internal::CaptureStdout();
        sstd::print(i);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "1234.43\n");
    }
}

//----------------------------------------------------------------------

TEST(print, print_charP){
    const char* i = "abc ABCd";
    testing::internal::CaptureStdout();
    sstd::print(i);
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "\"abc ABCd\"\n");
}
TEST(print, print_str){
    const std::string i = "abc ABCd";
    testing::internal::CaptureStdout();
    sstd::print(i);
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "\"abc ABCd\"\n");
}

//----------------------------------------------------------------------

TEST(print, print_pathAndType_case01){
    struct sstd::pathAndType pt;
    pt.path = "/dir1/dir2";
    pt.type = 'd';
    testing::internal::CaptureStdout();
    sstd::print(pt);
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "\"path: /dir1/dir2, type: directory\"\n");
}
TEST(print, print_pathAndType_case02){
    struct sstd::pathAndType pt;
    pt.path = "/dir1/example.txt";
    pt.type = 'f';
    testing::internal::CaptureStdout();
    sstd::print(pt);
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "\"path: /dir1/example.txt, type: file\"\n");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for std::vector<T>

TEST(print, print_vector){
    std::vector<int> v={1,2,3};
    testing::internal::CaptureStdout();
    sstd::print(v);
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "[1 2 3]\n");
}

// Recursive call for deep std::vector<std::vector<... std::vector<T>... >>.
TEST(print, print_vector_re_depth2){
    std::vector<std::vector<int>> vv = {{1,2,3}, {4,5,6}};
    testing::internal::CaptureStdout();
    sstd::print(vv);
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "[[1 2 3] [4 5 6]]\n");
}
TEST(print, print_vector_re_depth3){
    std::vector<std::vector<std::vector<int>>> vvv = {{{1,2,3},{4,5,6}}, {{7,8,9},{10,11,12}}};
    testing::internal::CaptureStdout();
    sstd::print(vvv);
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "[[[1 2 3] [4 5 6]] [[7 8 9] [10 11 12]]]\n");
}
TEST(print, print_vector_re_depth4){
    std::vector<std::vector<std::vector<std::vector<int>>>> vvvv = { {{{1,2,3},{4,5,6}}, {{7,8,9},{10,11,12}}}, {{{13,14,15},{16,17,18}}, {{19,20,21},{22,23,24}}} };
    testing::internal::CaptureStdout();
    sstd::print(vvvv);
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "[[[[1 2 3] [4 5 6]] [[7 8 9] [10 11 12]]] [[[13 14 15] [16 17 18]] [[19 20 21] [22 23 24]]]]\n");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for std::unordered_set<T>

TEST(print, print_hash_set){
    std::unordered_set<std::string> table;
    table.insert( "abc" );
    table.insert( "def" );

    {
        testing::internal::CaptureStdout();
        sstd::print( table );

        std::string buf = testing::internal::GetCapturedStdout().c_str();
        bool tf1 = sstd::strcmp(buf, "[\"def\", \"abc\"]\n");
        if(tf1){
            ASSERT_STREQ(buf.c_str(), "[\"def\", \"abc\"]\n");
        }else{
            ASSERT_STREQ(buf.c_str(), "[\"abc\", \"def\"]\n");
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for std::unordered_map<T_lhs, T_rhs>

TEST(print, print_table_02){
    std::unordered_map<std::string, std::vector<uint>> table;
    table["abc"] = {123, 456};
    table["def"] = {456, 789};

    {
        testing::internal::CaptureStdout();
        sstd::print( table );

        std::string buf = testing::internal::GetCapturedStdout().c_str();
        bool tf1 = sstd::strcmp(buf, "[ [key: \"def\", value: [456 789]], [key: \"abc\", value: [123 456]] ]\n");
        if(tf1){
            ASSERT_STREQ(buf.c_str(), "[ [key: \"def\", value: [456 789]], [key: \"abc\", value: [123 456]] ]\n");
        }else{
            ASSERT_STREQ(buf.c_str(), "[ [key: \"abc\", value: [123 456]], [key: \"def\", value: [456 789]] ]\n");
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// for std::tuple<T...>

// print
TEST(print, print_tuple_int){
    {
        std::tuple<int> ix1 = {0};
        testing::internal::CaptureStdout();
        sstd::print(ix1);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "(0)\n");
    }
    {
        std::tuple<int,int> ix2 = {0, 0};
        testing::internal::CaptureStdout();
        sstd::print(ix2);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "(0, 0)\n");
    }
    {
        std::tuple<int,int,int> ix3 = {0, 0, 0};
        testing::internal::CaptureStdout();
        sstd::print(ix3);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "(0, 0, 0)\n");
    }
}
TEST(print, print_tuple_iss){
    {
        std::tuple<int,std::string,std::string> iss = {0, "abc", "def"};
        testing::internal::CaptureStdout();
        sstd::print(iss);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "(0, \"abc\", \"def\")\n");
    }
}

// print
TEST(print, print_tuple){
    {
        std::tuple<int> ix1 = {0};
        testing::internal::CaptureStdout();
        sstd::print(ix1);
        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "(0)\n");
    }
}
/*
// std::vector<std::tuple<T...>>
TEST(print, v_tuple){
    {
        std::vector<std::tuple<int,int>> vII = {{0,1}, {2,3}};
//        testing::internal::CaptureStdout();
        sstd::print(vII);
//        ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "(0)\n");
    }
}
*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// for #define printn

TEST(print, printn){
    int valName=0;
    testing::internal::CaptureStdout();
    sstd::printn(valName);
    ASSERT_STREQ(testing::internal::GetCapturedStdout().c_str(), "valName = 0\n");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
