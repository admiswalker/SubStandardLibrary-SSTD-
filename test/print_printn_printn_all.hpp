#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------
void TEST_print(){
    sstd::print("in TEST_print-------------");

    //---

    bool tf1 = true;  sstd::print(tf1);
    bool tf2 = false; sstd::print(tf2);
    
    //---
    
    char c = 'c';  sstd::print(c);
    
    //---
    
    // signed
    int8  s8  = -1; sstd::print(s8);
    int16 s16 = -2; sstd::print(s16);
    int32 s32 = -3; sstd::print(s32);
    int64 s64 = -4; sstd::print(s64);

    // unsigned
    uint8  u8  = 1; sstd::print(u8);
    uint16 u16 = 2; sstd::print(u16);
    uint32 u32 = 3; sstd::print(u32);
    uint64 u64 = 4; sstd::print(u64);

    float  f  = -1.23; sstd::print(f);
    double d  = -1.23; sstd::print(d);

    sstd::print("char*");
    sstd::print(std::string("std::string"));
    sstd::print(sstd::ssprintf("std::string"));
    
    //---

    std::vector<bool> v_bool = {true, false, true, false}; sstd::print(v_bool);
    std::vector<char> v_char = {'a', 'b', 'c', 'd'}; sstd::print(v_char);

    std::vector<int8>  v_s8  = {-1, 2, 3, 4}; sstd::print(v_s8);
    std::vector<int16> v_s16 = {1, -2, 3, 4}; sstd::print(v_s16);
    std::vector<int32> v_s32 = {1, 2, -3, 4}; sstd::print(v_s32);
    std::vector<int64> v_s64 = {1, 2, 3, -4}; sstd::print(v_s64);

    std::vector<uint8>  v_u8  = {1, 2, 3, 4}; sstd::print(v_u8);
    std::vector<uint16> v_u16 = {1, 2, 3, 4}; sstd::print(v_u16);
    std::vector<uint32> v_u32 = {1, 2, 3, 4}; sstd::print(v_u32);
    std::vector<uint64> v_u64 = {1, 2, 3, 4}; sstd::print(v_u64);
    
    std::vector<float>  v_f0 = {1.0f, 2.0f, 3.0f, 4.0f}; sstd::print(v_f0);
    std::vector<double> v_d0 = {1.0, 2.0, 3.0, 4.0}; sstd::print(v_d0);
    
    std::vector<float>  v_f1 = {1.1f, 2.2f, 3.3f, 4.4f}; sstd::print(v_f1);
    std::vector<double> v_d1 = {1.1, 2.2, 3.3, 4.4}; sstd::print(v_d1);

    std::vector<std::string> v_str = {"abc", "def"}; sstd::print(v_str);
    
    //---

    std::vector<std::vector<bool>> vv_bool = {{true, false, true, false}, {false, true, false, true}}; sstd::print(vv_bool);
    std::vector<std::vector<char>> vv_char = {{'a', 'b'}, {'c', 'd'}}; sstd::print(vv_char);
    
    std::vector<std::vector<int8>>  vv_s8  = {{-1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::print(vv_s8);
    std::vector<std::vector<int16>> vv_s16 = {{1, -2, 3, 4}, {5, 6, 7, 8}}; sstd::print(vv_s16);
    std::vector<std::vector<int32>> vv_s32 = {{1, 2, -3, 4}, {5, 6, 7, 8}}; sstd::print(vv_s32);
    std::vector<std::vector<int64>> vv_s64 = {{1, 2, 3, -4}, {5, 6, 7, 8}}; sstd::print(vv_s64);
    
    std::vector<std::vector<uint8>>  vv_u8  = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::print(vv_u8);
    std::vector<std::vector<uint16>> vv_u16 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::print(vv_u16);
    std::vector<std::vector<uint32>> vv_u32 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::print(vv_u32);
    std::vector<std::vector<uint64>> vv_u64 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::print(vv_u64);

    std::vector<std::vector<float>>  vv_f0 = {{1.0f, 2.0f, 3.0f, 4.0f}, {5.0f, 6.0f, 7.0f, 8.0f}}; sstd::print(vv_f0);
    std::vector<std::vector<double>> vv_d0 = {{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}}; sstd::print(vv_d0);
    
    std::vector<std::vector<float>>  vv_f1 = {{1.1f, 2.2f, 3.3f, 4.4f}, {5.5f, 6.6f, 7.7f, 8.8f}}; sstd::print(vv_f1);
    std::vector<std::vector<double>> vv_d1 = {{1.1, 2.2, 3.3, 4.4}, {5.5, 6.6, 7.7, 8.8}}; sstd::print(vv_d1);
    
//    std::vector<std::vector<std::string>> vv_str = {{"abc", "def"}, {"ghi", "jkl"}}; sstd::print(vv_str); // gcc 5.4.0
    std::vector<std::vector<std::string>> vv_str = {{std::string("abc"), std::string("def")}, {std::string("ghi"), std::string("jkl")}}; sstd::print(vv_str); // gcc 4.4.7
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void TEST_printn(){
    sstd::print("■ sstd::printn");
    
    //---

    bool tf1 = true;  sstd::printn(tf1);
    bool tf2 = false; sstd::printn(tf2);
    
    //---

    char c = 'c';  sstd::printn(c);
    
    //---

    // signed
    int8  s8  = -1; sstd::printn(s8);
    int16 s16 = -2; sstd::printn(s16);
    int32 s32 = -3; sstd::printn(s32);
    int64 s64 = -4; sstd::printn(s64);

    // unsigned
    uint8  u8  = 1; sstd::printn(u8);
    uint16 u16 = 2; sstd::printn(u16);
    uint32 u32 = 3; sstd::printn(u32);
    uint64 u64 = 4; sstd::printn(u64);

    float  f  = -1.23; sstd::printn(f);
    double d  = -1.23; sstd::printn(d);

    sstd::printn("char*");
    sstd::printn(std::string("std::string"));
    
    //---

    std::vector<bool> v_bool = {true, false, true, false}; sstd::printn(v_bool);
    std::vector<char> v_char = {'a', 'b', 'c', 'd'}; sstd::printn(v_char);

    std::vector<int8>  v_s8  = {-1, 2, 3, 4}; sstd::printn(v_s8);
    std::vector<int16> v_s16 = {1, -2, 3, 4}; sstd::printn(v_s16);
    std::vector<int32> v_s32 = {1, 2, -3, 4}; sstd::printn(v_s32);
    std::vector<int64> v_s64 = {1, 2, 3, -4}; sstd::printn(v_s64);

    std::vector<uint8>  v_u8  = {1, 2, 3, 4}; sstd::printn(v_u8);
    std::vector<uint16> v_u16 = {1, 2, 3, 4}; sstd::printn(v_u16);
    std::vector<uint32> v_u32 = {1, 2, 3, 4}; sstd::printn(v_u32);
    std::vector<uint64> v_u64 = {1, 2, 3, 4}; sstd::printn(v_u64);
    
    std::vector<float>  v_f0 = {1.0f, 2.0f, 3.0f, 4.0f}; sstd::printn(v_f0);
    std::vector<double> v_d0 = {1.0, 2.0, 3.0, 4.0}; sstd::printn(v_d0);
    
    std::vector<float>  v_f1 = {1.1f, 2.2f, 3.3f, 4.4f}; sstd::printn(v_f1);
    std::vector<double> v_d1 = {1.1, 2.2, 3.3, 4.4}; sstd::printn(v_d1);

    std::vector<std::string> v_str = {"abc", "def"}; sstd::printn(v_str);
    
    //---

    std::vector<std::vector<bool>> vv_bool = {{true, false, true, false}, {false, true, false, true}}; sstd::printn(vv_bool);
    std::vector<std::vector<char>> vv_char = {{'a', 'b'}, {'c', 'd'}}; sstd::printn(vv_char);
    
    std::vector<std::vector<int8>>  vv_s8  = {{-1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn(vv_s8);
    std::vector<std::vector<int16>> vv_s16 = {{1, -2, 3, 4}, {5, 6, 7, 8}}; sstd::printn(vv_s16);
    std::vector<std::vector<int32>> vv_s32 = {{1, 2, -3, 4}, {5, 6, 7, 8}}; sstd::printn(vv_s32);
    std::vector<std::vector<int64>> vv_s64 = {{1, 2, 3, -4}, {5, 6, 7, 8}}; sstd::printn(vv_s64);
    
    std::vector<std::vector<uint8>>  vv_u8  = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn(vv_u8);
    std::vector<std::vector<uint16>> vv_u16 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn(vv_u16);
    std::vector<std::vector<uint32>> vv_u32 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn(vv_u32);
    std::vector<std::vector<uint64>> vv_u64 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn(vv_u64);
    
    std::vector<std::vector<float>>  vv_f0 = {{1.0f, 2.0f, 3.0f, 4.0f}, {5.0f, 6.0f, 7.0f, 8.0f}}; sstd::printn(vv_f0);
    std::vector<std::vector<double>> vv_d0 = {{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}}; sstd::printn(vv_d0);
    
    std::vector<std::vector<float>>  vv_f1 = {{1.1f, 2.2f, 3.3f, 4.4f}, {5.5f, 6.6f, 7.7f, 8.8f}}; sstd::printn(vv_f1);
    std::vector<std::vector<double>> vv_d1 = {{1.1, 2.2, 3.3, 4.4}, {5.5, 6.6, 7.7, 8.8}}; sstd::printn(vv_d1);
    
//    std::vector<std::vector<std::string>> vv_str = {{"abc", "def"}, {"ghi", "jkl"}}; sstd::printn(vv_str); // gcc 5.4.0
    std::vector<std::vector<std::string>> vv_str = {{std::string("abc"), std::string("def")}, {std::string("ghi"), std::string("jkl")}}; sstd::printn(vv_str); // gcc 4.4.7
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void TEST_printn_all(){
    sstd::print("■ sstd::printn_all");

    //---

    bool tf1 = true;  sstd::printn_all(tf1);
    bool tf2 = false; sstd::printn_all(tf2);
    
    //---

    char c = 'c'; sstd::printn_all(c);
    
    //---

    // signed
    int8  s8  = -1; sstd::printn_all(s8);
    int16 s16 = -2; sstd::printn_all(s16);
    int32 s32 = -3; sstd::printn_all(s32);
    int64 s64 = -4; sstd::printn_all(s64);

    // unsigned
    uint8  u8  = 1; sstd::printn_all(u8);
    uint16 u16 = 2; sstd::printn_all(u16);
    uint32 u32 = 3; sstd::printn_all(u32);
    uint64 u64 = 4; sstd::printn_all(u64);

    float  f  = -1.23; sstd::printn_all(f);
    double d  = -1.23; sstd::printn_all(d);

    sstd::printn_all("char*");
    sstd::printn_all(std::string("std::string"));
    
    //---

    std::vector<bool> v_bool = {true, false, true, false}; sstd::printn_all(v_bool);
    std::vector<char> v_char = {'a', 'b', 'c', 'd'}; sstd::printn_all(v_char);

    std::vector<int8>  v_s8  = {-1, 2, 3, 4}; sstd::printn_all(v_s8);
    std::vector<int16> v_s16 = {1, -2, 3, 4}; sstd::printn_all(v_s16);
    std::vector<int32> v_s32 = {1, 2, -3, 4}; sstd::printn_all(v_s32);
    std::vector<int64> v_s64 = {1, 2, 3, -4}; sstd::printn_all(v_s64);

    std::vector<uint8>  v_u8  = {1, 2, 3, 4}; sstd::printn_all(v_u8);
    std::vector<uint16> v_u16 = {1, 2, 3, 4}; sstd::printn_all(v_u16);
    std::vector<uint32> v_u32 = {1, 2, 3, 4}; sstd::printn_all(v_u32);
    std::vector<uint64> v_u64 = {1, 2, 3, 4}; sstd::printn_all(v_u64);

    std::vector<float>  v_f0 = {1.0f, 2.0f, 3.0f, 4.0f}; sstd::printn_all(v_f0);
    std::vector<double> v_d0 = {1.0, 2.0, 3.0, 4.0}; sstd::printn_all(v_d0);

    std::vector<float>  v_f1 = {1.1f, 2.2f, 3.3f, 4.4f}; sstd::printn_all(v_f1);
    std::vector<double> v_d1 = {1.1, 2.2, 3.3, 4.4}; sstd::printn_all(v_d1);

    std::vector<std::string> v_str = {"abc", "def"}; sstd::printn_all(v_str);
    
    //---

    std::vector<std::vector<bool>> vv_bool = {{true, false, true, false}, {false, true, false, true}}; sstd::printn_all(vv_bool);
    std::vector<std::vector<char>> vv_char = {{'a', 'b'}, {'c', 'd'}}; sstd::printn_all(vv_char);

    std::vector<std::vector<int8>>  vv_s8  = {{-1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn_all(vv_s8);
    std::vector<std::vector<int16>> vv_s16 = {{1, -2, 3, 4}, {5, 6, 7, 8}}; sstd::printn_all(vv_s16);
    std::vector<std::vector<int32>> vv_s32 = {{1, 2, -3, 4}, {5, 6, 7, 8}}; sstd::printn_all(vv_s32);
    std::vector<std::vector<int64>> vv_s64 = {{1, 2, 3, -4}, {5, 6, 7, 8}}; sstd::printn_all(vv_s64);
    
    std::vector<std::vector<uint8>>  vv_u8  = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn_all(vv_u8);
    std::vector<std::vector<uint16>> vv_u16 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn_all(vv_u16);
    std::vector<std::vector<uint32>> vv_u32 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn_all(vv_u32);
    std::vector<std::vector<uint64>> vv_u64 = {{1, 2, 3, 4}, {5, 6, 7, 8}}; sstd::printn_all(vv_u64);

    std::vector<std::vector<float>>  vv_f0 = {{1.0f, 2.0f, 3.0f, 4.0f}, {5.0f, 6.0f, 7.0f, 8.0f}}; sstd::printn_all(vv_f0);
    std::vector<std::vector<double>> vv_d0 = {{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}}; sstd::printn_all(vv_d0);
    
    std::vector<std::vector<float>>  vv_f1 = {{1.1f, 2.2f, 3.3f, 4.4f}, {5.5f, 6.6f, 7.7f, 8.8f}}; sstd::printn_all(vv_f1);
    std::vector<std::vector<double>> vv_d1 = {{1.1, 2.2, 3.3, 4.4}, {5.5, 6.6, 7.7, 8.8}}; sstd::printn_all(vv_d1);
    
//    std::vector<std::vector<std::string>> vv_str = {{"abc", "def"}, {"ghi", "jkl"}}; sstd::printn_all(vv_str); // gcc 5.4.0
    std::vector<std::vector<std::string>> vv_str = {{std::string("abc"), std::string("def")}, {std::string("ghi"), std::string("jkl")}}; sstd::printn_all(vv_str); // gcc 4.4.7
}
//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(print, print     ){ TEST_print     (); }
TEST(print, printn    ){ TEST_printn    (); }
TEST(print, printn_all){ TEST_printn_all(); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

