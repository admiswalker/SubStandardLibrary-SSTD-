#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// constructors

TEST(void_ptr, constructor_default_constructor){
    sstd::void_ptr void_ptr = sstd::void_ptr();
}
TEST(void_ptr, constructor_copy_constructor_01){
    sstd::void_ptr void_ptr_01;
    sstd::void_ptr void_ptr_02 = sstd::void_ptr(void_ptr_01);
}
TEST(void_ptr, constructor_copy_constructor_02){
    sstd::void_ptr void_ptr_01 = sstd::void_ptr(new std::string("abc")); // allocates the memory
    sstd::void_ptr void_ptr_02 = void_ptr_01; // copy the object
    
    ASSERT_EQ(void_ptr_01.typeNum(), sstd::num_str);
    ASSERT_EQ(void_ptr_02.typeNum(), sstd::num_str);

    std::string* pStr01 = (std::string*)void_ptr_01.ptr();
    std::string* pStr02 = (std::string*)void_ptr_02.ptr();
    
    ASSERT_STREQ(pStr01->c_str(), "abc");
    ASSERT_STREQ(pStr02->c_str(), "abc");
    ASSERT_NE(pStr01, pStr02); // has a different memory address
}
TEST(void_ptr, constructor_move_constructor_01){
    sstd::void_ptr void_ptr_01;
    sstd::void_ptr void_ptr_02 = sstd::void_ptr(std::move(void_ptr_01));
}
TEST(void_ptr, constructor_move_constructor_02){
    sstd::void_ptr void_ptr_01;
    sstd::void_ptr void_ptr_02 = sstd::void_ptr((sstd::void_ptr&&)void_ptr_01);
}

//---

TEST(void_ptr, constructor_bool){
    sstd::void_ptr void_ptr = sstd::void_ptr(new bool);
}
TEST(void_ptr, constructor_char){
    sstd::void_ptr void_ptr = sstd::void_ptr(new char);
}
//TEST(void_ptr, constructor_uchar){} // same as uint8
TEST(void_ptr, constructor_int8){
    sstd::void_ptr void_ptr = sstd::void_ptr(new int8);
}
TEST(void_ptr, constructor_int16){
    sstd::void_ptr void_ptr = sstd::void_ptr(new int16);
}
TEST(void_ptr, constructor_int32){
    sstd::void_ptr void_ptr = sstd::void_ptr(new int32);
}
TEST(void_ptr, constructor_int64){
    sstd::void_ptr void_ptr = sstd::void_ptr(new int64);
}
TEST(void_ptr, constructor_uint8){
    sstd::void_ptr void_ptr = sstd::void_ptr(new uint8);
}
TEST(void_ptr, constructor_uint16){
    sstd::void_ptr void_ptr = sstd::void_ptr(new uint16);
}
TEST(void_ptr, constructor_uint32){
    sstd::void_ptr void_ptr = sstd::void_ptr(new uint32);
}
TEST(void_ptr, constructor_uint64){
    sstd::void_ptr void_ptr = sstd::void_ptr(new uint64);
}
TEST(void_ptr, constructor_float){
    sstd::void_ptr void_ptr = sstd::void_ptr(new float);
}
TEST(void_ptr, constructor_double){
    sstd::void_ptr void_ptr = sstd::void_ptr(new double);
}
TEST(void_ptr, constructor_str){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::string(""));
}
TEST(void_ptr, constructor_void_ptr){
    sstd::void_ptr void_ptr = sstd::void_ptr(new sstd::void_ptr());
}

//---

TEST(void_ptr, constructor_vec_bool){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::vector<bool>);
}
TEST(void_ptr, constructor_vec_char){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::vector<char>);
}
//TEST(void_ptr, constructor_vec_uchar){} // same as uint8
TEST(void_ptr, constructor_vec_int8){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::vector<int8>);
}
TEST(void_ptr, constructor_vec_int16){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::vector<int16>);
}
TEST(void_ptr, constructor_vec_int32){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::vector<int32>);
}
TEST(void_ptr, constructor_vec_int64){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::vector<int64>);
}
TEST(void_ptr, constructor_vec_uint8){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::vector<uint8>);
}
TEST(void_ptr, constructor_vec_uint16){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::vector<uint16>);
}
TEST(void_ptr, constructor_vec_uint32){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::vector<uint32>);
}
TEST(void_ptr, constructor_vec_uint64){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::vector<uint64>);
}
TEST(void_ptr, constructor_vec_float){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::vector<float>);
}
TEST(void_ptr, constructor_vec_double){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::vector<double>);
}
TEST(void_ptr, constructor_vec_str){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::vector<std::string>({""}));
}
TEST(void_ptr, constructor_vec_void_ptr){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::vector<sstd::void_ptr>());
}

//---

TEST(void_ptr, constructor_hash_str_str){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::unordered_map<std::string, std::string>({{"key1", "value1"}}));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// member functions

#define SSTD_TEST_void_ptr_overwrite(Type, TypeNum)         \
    sstd::void_ptr void_ptr = sstd::void_ptr(new bool); \
    void* prev_p = void_ptr.ptr();                              \
                                                                \
    void_ptr.overwrite(new Type);                               \
                                                                \
    ASSERT_NE(void_ptr.ptr(), prev_p);                          \
    ASSERT_EQ(void_ptr.typeNum(), TypeNum);
    
TEST(void_ptr, overwrite_bool    ){ SSTD_TEST_void_ptr_overwrite(          bool, sstd::num_bool    ) }
TEST(void_ptr, overwrite_char    ){ SSTD_TEST_void_ptr_overwrite(          char, sstd::num_char    ) }
//TEST(void_ptr, overwrite_uchar){} // same as uint8
TEST(void_ptr, overwrite_int8    ){ SSTD_TEST_void_ptr_overwrite(         int8 , sstd::num_int8    ) }
TEST(void_ptr, overwrite_int16   ){ SSTD_TEST_void_ptr_overwrite(         int16, sstd::num_int16   ) }
TEST(void_ptr, overwrite_int32   ){ SSTD_TEST_void_ptr_overwrite(         int32, sstd::num_int32   ) }
TEST(void_ptr, overwrite_int64   ){ SSTD_TEST_void_ptr_overwrite(         int64, sstd::num_int64   ) }
TEST(void_ptr, overwrite_uint8   ){ SSTD_TEST_void_ptr_overwrite(        uint8 , sstd::num_uint8   ) }
TEST(void_ptr, overwrite_uint16  ){ SSTD_TEST_void_ptr_overwrite(        uint16, sstd::num_uint16  ) }
TEST(void_ptr, overwrite_uint32  ){ SSTD_TEST_void_ptr_overwrite(        uint32, sstd::num_uint32  ) }
TEST(void_ptr, overwrite_uint64  ){ SSTD_TEST_void_ptr_overwrite(        uint64, sstd::num_uint64  ) }
TEST(void_ptr, overwrite_float   ){ SSTD_TEST_void_ptr_overwrite(         float, sstd::num_float   ) }
TEST(void_ptr, overwrite_double  ){ SSTD_TEST_void_ptr_overwrite(        double, sstd::num_double  ) }
TEST(void_ptr, overwrite_str     ){ SSTD_TEST_void_ptr_overwrite(   std::string, sstd::num_str     ) }
TEST(void_ptr, overwrite_void_ptr){ SSTD_TEST_void_ptr_overwrite(sstd::void_ptr, sstd::num_void_ptr) }

TEST(void_ptr, overwrite_vec_bool    ){ SSTD_TEST_void_ptr_overwrite(std::vector<          bool>, sstd::num_vec_bool    ) }
TEST(void_ptr, overwrite_vec_char    ){ SSTD_TEST_void_ptr_overwrite(std::vector<          char>, sstd::num_vec_char    ) }
//TEST(void_ptr, overwrite_vec_ucha  r){} // same as uint8
TEST(void_ptr, overwrite_vec_int8    ){ SSTD_TEST_void_ptr_overwrite(std::vector<         int8 >, sstd::num_vec_int8    ) }
TEST(void_ptr, overwrite_vec_int16   ){ SSTD_TEST_void_ptr_overwrite(std::vector<         int16>, sstd::num_vec_int16   ) }
TEST(void_ptr, overwrite_vec_int32   ){ SSTD_TEST_void_ptr_overwrite(std::vector<         int32>, sstd::num_vec_int32   ) }
TEST(void_ptr, overwrite_vec_int64   ){ SSTD_TEST_void_ptr_overwrite(std::vector<         int64>, sstd::num_vec_int64   ) }
TEST(void_ptr, overwrite_vec_uint8   ){ SSTD_TEST_void_ptr_overwrite(std::vector<        uint8 >, sstd::num_vec_uint8   ) }
TEST(void_ptr, overwrite_vec_uint16  ){ SSTD_TEST_void_ptr_overwrite(std::vector<        uint16>, sstd::num_vec_uint16  ) }
TEST(void_ptr, overwrite_vec_uint32  ){ SSTD_TEST_void_ptr_overwrite(std::vector<        uint32>, sstd::num_vec_uint32  ) }
TEST(void_ptr, overwrite_vec_uint64  ){ SSTD_TEST_void_ptr_overwrite(std::vector<        uint64>, sstd::num_vec_uint64  ) }
TEST(void_ptr, overwrite_vec_float   ){ SSTD_TEST_void_ptr_overwrite(std::vector<         float>, sstd::num_vec_float   ) }
TEST(void_ptr, overwrite_vec_double  ){ SSTD_TEST_void_ptr_overwrite(std::vector<        double>, sstd::num_vec_double  ) }
TEST(void_ptr, overwrite_vec_str     ){ SSTD_TEST_void_ptr_overwrite(std::vector<   std::string>, sstd::num_vec_str     ) }
TEST(void_ptr, overwrite_vec_void_ptr){ SSTD_TEST_void_ptr_overwrite(std::vector<sstd::void_ptr>, sstd::num_vec_void_ptr) }

TEST(void_ptr, overwrite_hash_str_str   ){ SSTD_TEST_void_ptr_overwrite((std::unordered_map<std::string, std::string>), sstd::num_hash_str_str   ) }

//---

TEST(void_ptr, ptr){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::vector<std::string>({"abc"}));

    std::vector<std::string>* ptr = (std::vector<std::string>*)void_ptr.ptr();
    (*ptr).push_back(std::string("def"));

    std::vector<std::string> vec_ans = {"abc", "def"};
    
    ASSERT_TRUE((*ptr)==vec_ans);
}
TEST(void_ptr, typeNum){
    sstd::void_ptr void_ptr = sstd::void_ptr(new std::vector<std::string>({""}));
    ASSERT_EQ(void_ptr.typeNum(), sstd::num_vec_str);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// operators

TEST(void_ptr, constructor_copy_operator){
    sstd::void_ptr void_ptr_01 = sstd::void_ptr(new std::string("abc")); // allocates the memory
    sstd::void_ptr void_ptr_02;
    void_ptr_02 = void_ptr_01; // copy the object
    
    ASSERT_EQ(void_ptr_01.typeNum(), sstd::num_str);
    ASSERT_EQ(void_ptr_02.typeNum(), sstd::num_str);

    std::string* pStr01 = (std::string*)void_ptr_01.ptr();
    std::string* pStr02 = (std::string*)void_ptr_02.ptr();
    
    ASSERT_STREQ(pStr01->c_str(), "abc");
    ASSERT_STREQ(pStr02->c_str(), "abc");
    ASSERT_NE(pStr01, pStr02); // has a different memory address
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
