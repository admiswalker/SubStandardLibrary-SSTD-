#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------
// strmatch() and strmatch_getWC()

TEST(strmatch, strmatch){
    const char* str = "abcdefghijk";
    const char* WildCard1 = "abc*";
    const char* WildCard2 = "a?cdefghijk";
    const char* WildCard3 = "a?";

    // strmatch
      // test (1)
    ASSERT_TRUE ( sstd::strmatch(str, WildCard1) );
    ASSERT_TRUE ( sstd::strmatch(str, WildCard2) );
    ASSERT_FALSE( sstd::strmatch(str, WildCard3) );
      // test (2)
    ASSERT_TRUE( sstd::strmatch("TOKYOTO...", "??KYOTO*") );
      // test (3) type test
    ASSERT_TRUE ( sstd::strmatch(std::string(str),             WildCard1 ) );
    ASSERT_TRUE ( sstd::strmatch(            str , std::string(WildCard1)) );
    ASSERT_TRUE ( sstd::strmatch(std::string(str), std::string(WildCard1)) );
    
    // strmatch_getWC
      // test (1)
    std::string retWC;
    ASSERT_TRUE ( sstd::strmatch_getWC(str, WildCard1, retWC) ); ASSERT_STREQ(retWC.c_str(), "defghijk"); ASSERT_TRUE( retWC.size()==8 ); retWC.clear();
    ASSERT_TRUE ( sstd::strmatch_getWC(str, WildCard2, retWC) ); ASSERT_STREQ(retWC.c_str(), "b"       ); ASSERT_TRUE( retWC.size()==1 ); retWC.clear();
    ASSERT_FALSE( sstd::strmatch_getWC(str, WildCard3, retWC) ); ASSERT_STREQ(retWC.c_str(), ""        ); ASSERT_TRUE( retWC.size()==0 );
      // test (2)
    std::string ret;
    ASSERT_TRUE( sstd::strmatch_getWC("TOKYOTO...", "TO*...", ret) );
    ASSERT_STREQ(ret.c_str(), "KYOTO"); ASSERT_EQ(ret.size(), (uint)5);
    
    ASSERT_TRUE( sstd::strmatch_getWC("TOKYOTO...", "??KYOTO*", ret) );
    ASSERT_STREQ(ret.c_str(), "TO..."); ASSERT_EQ(ret.size(), (uint)5);
    
    ASSERT_TRUE( sstd::strmatch_getWC("TOKYOTO...", "*KYOTO.*.", ret) );
    ASSERT_STREQ(ret.c_str(), "TO."); ASSERT_EQ(ret.size(), (uint)3);
    
    ASSERT_TRUE( sstd::strmatch_getWC("TOKYOTO...", "TO?????.*.", ret) );
    ASSERT_STREQ(ret.c_str(), "KYOTO."); ASSERT_EQ(ret.size(), (uint)6);
    
    ASSERT_TRUE( sstd::strmatch_getWC("TOKYOTO...", "T*?T?*...*", ret) );
    ASSERT_STREQ(ret.c_str(), "OKYOO"); ASSERT_EQ(ret.size(), (uint)5);
      // test (3) type test
    ASSERT_TRUE( sstd::strmatch_getWC(std::string("TOKYOTO..."),             "??KYOTO*" , ret) ); ASSERT_STREQ(ret.c_str(), "TO..."); ASSERT_EQ(ret.size(), (uint)5);
    ASSERT_TRUE( sstd::strmatch_getWC(            "TOKYOTO..." , std::string("??KYOTO*"), ret) ); ASSERT_STREQ(ret.c_str(), "TO..."); ASSERT_EQ(ret.size(), (uint)5);
    ASSERT_TRUE( sstd::strmatch_getWC(std::string("TOKYOTO..."), std::string("??KYOTO*"), ret) ); ASSERT_STREQ(ret.c_str(), "TO..."); ASSERT_EQ(ret.size(), (uint)5);
    
    // isNum
    ASSERT_TRUE ( sstd::isNum('0') );
    ASSERT_TRUE ( sstd::isNum('5') );
    ASSERT_TRUE ( sstd::isNum('9') );
    ASSERT_FALSE( sstd::isNum('a') );
    ASSERT_FALSE( sstd::isNum('A') );
    
    // isAlphabet
    ASSERT_TRUE ( sstd::isAlphabet('a') );
    ASSERT_TRUE ( sstd::isAlphabet('A') );
    ASSERT_FALSE( sstd::isAlphabet('0') );
    ASSERT_FALSE( sstd::isAlphabet('9') );
    
    ASSERT_TRUE ( sstd::isAlphabet_onlyUpper('A') );
    ASSERT_FALSE( sstd::isAlphabet_onlyUpper('a') );
    
    ASSERT_TRUE ( sstd::isAlphabet_onlyLower('a') );
    ASSERT_FALSE( sstd::isAlphabet_onlyLower('A') );
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// charIn()

TEST(strmatch, charIn){
    {
        char lhs = ' ';
        std::string rhs = "";
        bool ret=sstd::charIn(lhs, rhs); ASSERT_FALSE(ret);
    }
    {
        char lhs = 'A';
        std::string rhs = "ABCDEFG";
        bool ret=sstd::charIn(lhs, rhs); ASSERT_TRUE(ret);
    }
    {
        char lhs = 'B';
        std::string rhs = "ABCDEFG";
        bool ret=sstd::charIn(lhs, rhs); ASSERT_TRUE(ret);
    }
    {
        char lhs = 'G';
        std::string rhs = "ABCDEFG";
        bool ret=sstd::charIn(lhs, rhs); ASSERT_TRUE(ret);
    }
    {
        char lhs = 'X';
        std::string rhs = "ABCDEFG";
        bool ret=sstd::charIn(lhs, rhs); ASSERT_FALSE(ret);
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// strIn()

TEST(strmatch, strIn){
    {
        std::string lhs = "";
        std::string rhs = "";
        bool ret=sstd::strIn(lhs, rhs); ASSERT_TRUE(ret);
    }
    {
        std::string lhs = "ABCD";
        std::string rhs = "ABCDEFG";
        bool ret=sstd::strIn(lhs, rhs); ASSERT_TRUE(ret);
    }
    {
        std::string lhs = "BCD";
        std::string rhs = "ABCDEFG";
        bool ret=sstd::strIn(lhs, rhs); ASSERT_TRUE(ret);
    }
    {
        std::string lhs = "DEFG";
        std::string rhs = "ABCDEFG";
        bool ret=sstd::strIn(lhs, rhs); ASSERT_TRUE(ret);
    }
    {
        std::string lhs = "ABCDEFG";
        std::string rhs = "ABCDEFG";
        bool ret=sstd::strIn(lhs, rhs); ASSERT_TRUE(ret);
    }
    {
        std::string lhs = "AXCDEFG";
        std::string rhs = "ABCDEFG";
        bool ret=sstd::strIn(lhs, rhs); ASSERT_FALSE(ret);
    }
    {
        std::string lhs = "XABCDEFG";
        std::string rhs = "AABCDEFG";
        bool ret=sstd::strIn(lhs, rhs); ASSERT_FALSE(ret);
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
