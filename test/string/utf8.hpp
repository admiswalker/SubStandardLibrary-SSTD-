


TEST(string_utf8, constructor01){
    sstd::utf8 u8;
}
TEST(string_utf8, constructor02){
    const char* pU8 = "あいうえお"; // As a strict definition, it needs to be "const char8_t*". This means the UTF-8 encoded string.
    sstd::utf8 u8(pU8);

    ASSERT_EQ(u8.size(), (size_t)15);
    ASSERT_EQ(u8.alloc_size(), (size_t)16);
    
    sstd::print(&u8[0]);
//    sstd::print(u8._alloc_size());
//    sstd::print(u8._size());
//    sstd::print(u8._alloc_size());
}




/*
TEST(string_utf8, XXX){
    sstd:utf8 u8;
    
    u8 = "XXX";

    u8 = sstd::utf8_rm_Cc(u8);
    u8 = sstd::utf8_rm_Cf(u8);
    u8 = sstd::utf8_rm_Cn(u8);
    u8 = sstd::utf8_rm_Co(u8);
    u8 = sstd::utf8_rm_Cs(u8);

    u8 = sstd::utf8_rm_CX(u8); // rm CX is removing "Cc", "Cf", "Cn", "Co" and "Cs".
    u8 = sstd::utf8_rm_CX_owZWJ(u8); // owZWJ: without Zero Width Joiner
    ;
}
*/






