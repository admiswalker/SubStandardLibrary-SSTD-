#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------
// constructors

TEST(unique_void_ptr, constructor_default_constructor){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr();
}
TEST(unique_void_ptr, constructor_copy_constructor){
//    sstd::unique_void_ptr void_ptr_01;
//    sstd::unique_void_ptr void_ptr_02 = sstd::unique_void_ptr(void_ptr_01); // Because of the copy constructor is deleted, this line can not compileable.
}
TEST(unique_void_ptr, constructor_move_constructor_01){
    sstd::unique_void_ptr void_ptr_01;
    sstd::unique_void_ptr void_ptr_02 = sstd::unique_void_ptr(std::move(void_ptr_01));
}
TEST(unique_void_ptr, constructor_move_constructor_02){
    sstd::unique_void_ptr void_ptr_01;
    sstd::unique_void_ptr void_ptr_02 = sstd::unique_void_ptr((sstd::unique_void_ptr&&)void_ptr_01);
}

//---

TEST(unique_void_ptr, constructor_bool){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new bool(10));
}
TEST(unique_void_ptr, constructor_char){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new char(10));
}
//TEST(unique_void_ptr, constructor_uchar){} // same as uint8
TEST(unique_void_ptr, constructor_int8){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new int8(10));
}
TEST(unique_void_ptr, constructor_int16){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new int16(10));
}
TEST(unique_void_ptr, constructor_int32){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new int32(10));
}
TEST(unique_void_ptr, constructor_int64){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new int64(10));
}
TEST(unique_void_ptr, constructor_uint8){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new uint8(10));
}
TEST(unique_void_ptr, constructor_uint16){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new uint16(10));
}
TEST(unique_void_ptr, constructor_uint32){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new uint32(10));
}
TEST(unique_void_ptr, constructor_uint64){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new uint64(10));
}
TEST(unique_void_ptr, constructor_float){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new float(10));
}
TEST(unique_void_ptr, constructor_double){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new double(10));
}
TEST(unique_void_ptr, constructor_str){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new std::string(""));
}

//---

TEST(unique_void_ptr, constructor_vec_bool){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new std::vector<bool>(10));
}
TEST(unique_void_ptr, constructor_vec_char){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new std::vector<char>(10));
}
//TEST(unique_void_ptr, constructor_vec_uchar){} // same as uint8
TEST(unique_void_ptr, constructor_vec_int8){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new std::vector<int8>(10));
}
TEST(unique_void_ptr, constructor_vec_int16){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new std::vector<int16>(10));
}
TEST(unique_void_ptr, constructor_vec_int32){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new std::vector<int32>(10));
}
TEST(unique_void_ptr, constructor_vec_int64){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new std::vector<int64>(10));
}
TEST(unique_void_ptr, constructor_vec_uint8){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new std::vector<uint8>(10));
}
TEST(unique_void_ptr, constructor_vec_uint16){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new std::vector<uint16>(10));
}
TEST(unique_void_ptr, constructor_vec_uint32){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new std::vector<uint32>(10));
}
TEST(unique_void_ptr, constructor_vec_uint64){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new std::vector<uint64>(10));
}
TEST(unique_void_ptr, constructor_vec_float){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new std::vector<float>(10));
}
TEST(unique_void_ptr, constructor_vec_double){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new std::vector<double>(10));
}
TEST(unique_void_ptr, constructor_vec_str){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new std::vector<std::string>({""}));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// member functions

TEST(unique_void_ptr, typeNum){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new std::vector<std::string>({""}));
    ASSERT_EQ(void_ptr.typeNum(), sstd::num_vec_str);
}
TEST(unique_void_ptr, ptr){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new std::vector<std::string>({"abc"}));

    std::vector<std::string>* ptr = (std::vector<std::string>*)void_ptr.ptr();
    (*ptr).push_back(std::string("def"));

    std::vector<std::string> vec_ans = {"abc", "def"};
    
    ASSERT_TRUE((*ptr)==vec_ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

