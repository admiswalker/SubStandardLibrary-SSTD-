#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------
// constructors

TEST(void_ptr_obj, constructor_default_constructor){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj();
}
TEST(void_ptr_obj, constructor_copy_constructor_01){
    sstd::void_ptr_obj void_ptr_01;
    sstd::void_ptr_obj void_ptr_02 = sstd::void_ptr_obj(void_ptr_01);
}
TEST(void_ptr_obj, constructor_copy_constructor_02){
    sstd::void_ptr_obj void_ptr_01 = sstd::void_ptr_obj(new std::string("abc")); // allocates the memory
    sstd::void_ptr_obj void_ptr_02 = void_ptr_01; // copy the object
    
    ASSERT_EQ(void_ptr_01.typeNum(), sstd::num_str);
    ASSERT_EQ(void_ptr_02.typeNum(), sstd::num_str);

    std::string* pStr01 = (std::string*)void_ptr_01.ptr();
    std::string* pStr02 = (std::string*)void_ptr_02.ptr();
    
    ASSERT_STREQ(pStr01->c_str(), "abc");
    ASSERT_STREQ(pStr02->c_str(), "abc");
    ASSERT_NE(pStr01, pStr02); // has a different memory address
}
TEST(void_ptr_obj, constructor_move_constructor_01){
    sstd::void_ptr_obj void_ptr_01;
    sstd::void_ptr_obj void_ptr_02 = sstd::void_ptr_obj(std::move(void_ptr_01));
}
TEST(void_ptr_obj, constructor_move_constructor_02){
    sstd::void_ptr_obj void_ptr_01;
    sstd::void_ptr_obj void_ptr_02 = sstd::void_ptr_obj((sstd::void_ptr_obj&&)void_ptr_01);
}

//---

TEST(void_ptr_obj, constructor_bool){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new bool(10));
}
TEST(void_ptr_obj, constructor_char){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new char(10));
}
//TEST(void_ptr_obj, constructor_uchar){} // same as uint8
TEST(void_ptr_obj, constructor_int8){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new int8(10));
}
TEST(void_ptr_obj, constructor_int16){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new int16(10));
}
TEST(void_ptr_obj, constructor_int32){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new int32(10));
}
TEST(void_ptr_obj, constructor_int64){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new int64(10));
}
TEST(void_ptr_obj, constructor_uint8){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new uint8(10));
}
TEST(void_ptr_obj, constructor_uint16){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new uint16(10));
}
TEST(void_ptr_obj, constructor_uint32){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new uint32(10));
}
TEST(void_ptr_obj, constructor_uint64){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new uint64(10));
}
TEST(void_ptr_obj, constructor_float){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new float(10));
}
TEST(void_ptr_obj, constructor_double){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new double(10));
}
TEST(void_ptr_obj, constructor_str){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new std::string(""));
}

//---

TEST(void_ptr_obj, constructor_vec_bool){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new std::vector<bool>(10));
}
TEST(void_ptr_obj, constructor_vec_char){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new std::vector<char>(10));
}
//TEST(void_ptr_obj, constructor_vec_uchar){} // same as uint8
TEST(void_ptr_obj, constructor_vec_int8){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new std::vector<int8>(10));
}
TEST(void_ptr_obj, constructor_vec_int16){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new std::vector<int16>(10));
}
TEST(void_ptr_obj, constructor_vec_int32){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new std::vector<int32>(10));
}
TEST(void_ptr_obj, constructor_vec_int64){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new std::vector<int64>(10));
}
TEST(void_ptr_obj, constructor_vec_uint8){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new std::vector<uint8>(10));
}
TEST(void_ptr_obj, constructor_vec_uint16){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new std::vector<uint16>(10));
}
TEST(void_ptr_obj, constructor_vec_uint32){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new std::vector<uint32>(10));
}
TEST(void_ptr_obj, constructor_vec_uint64){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new std::vector<uint64>(10));
}
TEST(void_ptr_obj, constructor_vec_float){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new std::vector<float>(10));
}
TEST(void_ptr_obj, constructor_vec_double){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new std::vector<double>(10));
}
TEST(void_ptr_obj, constructor_vec_str){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new std::vector<std::string>({""}));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// member functions

TEST(void_ptr_obj, typeNum){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new std::vector<std::string>({""}));
    ASSERT_EQ(void_ptr.typeNum(), sstd::num_vec_str);
}
TEST(void_ptr_obj, ptr){
    sstd::void_ptr_obj void_ptr = sstd::void_ptr_obj(new std::vector<std::string>({"abc"}));

    std::vector<std::string>* ptr = (std::vector<std::string>*)void_ptr.ptr();
    (*ptr).push_back(std::string("def"));

    std::vector<std::string> vec_ans = {"abc", "def"};
    
    ASSERT_TRUE((*ptr)==vec_ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

