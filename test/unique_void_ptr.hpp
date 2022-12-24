#pragma once


TEST(unique_void_ptr, constructor_empty){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr();
}

TEST(unique_void_ptr, constructor_bool){
    sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new bool(10));
}

TEST(unique_void_ptr, constructor_int){
    //sstd::unique_void_ptr void_ptr = sstd::unique_void_ptr(new int(10));
}

