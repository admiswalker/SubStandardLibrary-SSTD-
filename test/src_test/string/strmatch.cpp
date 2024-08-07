#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// startswith()

TEST(strmatch, startswith_c_c){ sstd::startswith(            "" ,             "" ); }
TEST(strmatch, startswith_c_s){ sstd::startswith(            "" , std::string("")); }
TEST(strmatch, startswith_s_c){ sstd::startswith(std::string(""),             "" ); }
TEST(strmatch, startswith_s_s){ sstd::startswith(std::string(""), std::string("")); }

TEST(strmatch, startswith_null){ ASSERT_TRUE(sstd::startswith("", "")); }
TEST(strmatch, startswith_01){ ASSERT_TRUE(sstd::startswith("abc", "")); }
TEST(strmatch, startswith_02){ ASSERT_TRUE(!sstd::startswith("abc", "b")); }
TEST(strmatch, startswith_03){ ASSERT_TRUE(sstd::startswith("abc", "abc")); }
TEST(strmatch, startswith_04){ ASSERT_TRUE(sstd::startswith("abcdef", "abc")); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// strcmp()

TEST(strmatch, strcmp_c_c){ sstd::strcmp(            "" ,             "" ); }
TEST(strmatch, strcmp_c_s){ sstd::strcmp(            "" , std::string("")); }
TEST(strmatch, strcmp_s_c){ sstd::strcmp(std::string(""),             "" ); }
TEST(strmatch, strcmp_s_s){ sstd::strcmp(std::string(""), std::string("")); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// strmatch() and strmatch_getWC()

TEST(strmatch, strmatch){
    const char* str = "abcdefghijk";
    const char* wildcard1 = "abc*";
    const char* wildcard2 = "a?cdefghijk";
    const char* wildcard3 = "a?";

    // strmatch
      // test (1)
    ASSERT_TRUE ( sstd::strmatch(str, wildcard1) );
    ASSERT_TRUE ( sstd::strmatch(str, wildcard2) );
    ASSERT_FALSE( sstd::strmatch(str, wildcard3) );
      // test (2)
    ASSERT_TRUE( sstd::strmatch("TOKYOTO...", "??KYOTO*") );
      // test (3) type test
    ASSERT_TRUE ( sstd::strmatch(std::string(str),             wildcard1 ) );
    ASSERT_TRUE ( sstd::strmatch(            str , std::string(wildcard1)) );
    ASSERT_TRUE ( sstd::strmatch(std::string(str), std::string(wildcard1)) );
    
    // strmatch_getWC
      // test (1)
    std::string retWC;
    ASSERT_TRUE ( sstd::strmatch_getWC(str, wildcard1, retWC) ); ASSERT_STREQ(retWC.c_str(), "defghijk"); ASSERT_TRUE( retWC.size()==8 ); retWC.clear();
    ASSERT_TRUE ( sstd::strmatch_getWC(str, wildcard2, retWC) ); ASSERT_STREQ(retWC.c_str(), "b"       ); ASSERT_TRUE( retWC.size()==1 ); retWC.clear();
    ASSERT_FALSE( sstd::strmatch_getWC(str, wildcard3, retWC) ); ASSERT_STREQ(retWC.c_str(), ""        ); ASSERT_TRUE( retWC.size()==0 );
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
}
TEST(strmatch, pathmatch){
    const char* str = "/abc/def/ghi/example.txt";
    const char* wildcard1 = "/abc/def/ghi/*.txt";
    const char* wildcard2 = "/abc/def/*/*.txt";
    const char* wildcard3 = "/abc/*.txt";
    const char* wildcard4 = R"(/abc/*/*/*.txt)";   // escape `*` or use `raw string literal`
    const char* wildcard5 = R"(/abc/*/???/*.txt)"; // escape `*` or use `raw string literal`

    ASSERT_TRUE ( sstd::pathmatch(str, wildcard1) );
    ASSERT_TRUE ( sstd::pathmatch(str, wildcard2) );
    ASSERT_FALSE( sstd::pathmatch(str, wildcard3) );
    ASSERT_TRUE ( sstd::pathmatch(str, wildcard4) );
    ASSERT_TRUE ( sstd::pathmatch(str, wildcard5) );
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// rcount(), lcount(), count()

TEST(strmatch, rcount_cc){
    ASSERT_EQ(sstd::rcount("abcdef", 'x'), (uint)0);
    ASSERT_EQ(sstd::rcount("abcdef", 'f'), (uint)1);
    ASSERT_EQ(sstd::rcount("abcfff", 'f'), (uint)3);
    ASSERT_EQ(sstd::rcount("", 'a'), (uint)0);
}
TEST(strmatch, rcount_sc){
    ASSERT_EQ(sstd::rcount(std::string("abcdef"), 'x'), (uint)0);
}

//---

TEST(strmatch, lcount_cc){
    ASSERT_EQ(sstd::lcount("abcdef", 'x'), (uint)0);
    ASSERT_EQ(sstd::lcount("abcdef", 'a'), (uint)1);
    ASSERT_EQ(sstd::lcount("aaabcd", 'a'), (uint)3);
    ASSERT_EQ(sstd::lcount("", 'a'), (uint)0);
}
TEST(strmatch, lcount_sc){
    ASSERT_EQ(sstd::lcount(std::string("abcdef"), 'x'), (uint)0);
}

//---

TEST(strmatch, count_cc){
    ASSERT_EQ(sstd::count("abcdef", 'x'), (uint)0);
    ASSERT_EQ(sstd::count("abcdef", 'a'), (uint)1);
    ASSERT_EQ(sstd::count("xbxdex", 'x'), (uint)3);
    ASSERT_EQ(sstd::count("", 'a'), (uint)0);
}
TEST(strmatch, count_sc){
    ASSERT_EQ(sstd::count(std::string("abcdef"), 'x'), (uint)0);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(strmatch, isNum_char){
    ASSERT_TRUE ( sstd::isNum('0') );
    ASSERT_TRUE ( sstd::isNum('5') );
    ASSERT_TRUE ( sstd::isNum('9') );
    ASSERT_FALSE( sstd::isNum('a') );
    ASSERT_FALSE( sstd::isNum('A') );
}
TEST(strmatch, isNum_pChar){
    ASSERT_TRUE ( sstd::isNum("0") );
    ASSERT_TRUE ( sstd::isNum("5") );
    ASSERT_TRUE ( sstd::isNum("9") );
    ASSERT_FALSE( sstd::isNum("a") );
    ASSERT_FALSE( sstd::isNum("A") );
    
    ASSERT_TRUE ( sstd::isNum("0123456789") );
    ASSERT_TRUE ( sstd::isNum("9876543210") );
    ASSERT_TRUE ( sstd::isNum("097563758974329") );
    ASSERT_FALSE( sstd::isNum("w458934") );
    ASSERT_FALSE( sstd::isNum("458934a") );
    ASSERT_FALSE( sstd::isNum("w458934a") );
    ASSERT_FALSE( sstd::isNum("A8908023") );
    ASSERT_FALSE( sstd::isNum("A8908023Z") );
}
TEST(strmatch, isNum_str){
    ASSERT_TRUE ( sstd::isNum(std::string("0")) );
    ASSERT_TRUE ( sstd::isNum(std::string("5")) );
    ASSERT_TRUE ( sstd::isNum(std::string("9")) );
    ASSERT_FALSE( sstd::isNum(std::string("a")) );
    ASSERT_FALSE( sstd::isNum(std::string("A")) );
    
    ASSERT_TRUE ( sstd::isNum(std::string("0123456789")) );
    ASSERT_TRUE ( sstd::isNum(std::string("9876543210")) );
    ASSERT_TRUE ( sstd::isNum(std::string("097563758974329")) );
    ASSERT_FALSE( sstd::isNum(std::string("w458934")) );
    ASSERT_FALSE( sstd::isNum(std::string("458934a")) );
    ASSERT_FALSE( sstd::isNum(std::string("w458934a")) );
    ASSERT_FALSE( sstd::isNum(std::string("A8908023")) );
    ASSERT_FALSE( sstd::isNum(std::string("A8908023Z")) );
}
TEST(strmatch, isAlphabet_char){
    ASSERT_TRUE ( sstd::isAlphabet('a') );
    ASSERT_TRUE ( sstd::isAlphabet('A') );
    ASSERT_FALSE( sstd::isAlphabet('0') );
    ASSERT_FALSE( sstd::isAlphabet('9') );
}
TEST(strmatch, isAlphabet_pChar){
    ASSERT_TRUE ( sstd::isAlphabet("a") );
    ASSERT_TRUE ( sstd::isAlphabet("A") );
    ASSERT_FALSE( sstd::isAlphabet("0") );
    ASSERT_FALSE( sstd::isAlphabet("9") );
    
    ASSERT_TRUE ( sstd::isAlphabet("abczAZ") );
    ASSERT_TRUE ( sstd::isAlphabet("AlhjkboeisduhjnwoghdsfoijoieabaHGREGeiosjoidsfZ") );
    ASSERT_FALSE( sstd::isAlphabet("w458934") );
    ASSERT_FALSE( sstd::isAlphabet("458934a") );
    ASSERT_FALSE( sstd::isAlphabet("w458934a") );
    ASSERT_FALSE( sstd::isAlphabet("A8908023") );
    ASSERT_FALSE( sstd::isAlphabet("A8908023Z") );
}
TEST(strmatch, isAlphabet_str){
    ASSERT_TRUE ( sstd::isAlphabet(std::string("a")) );
    ASSERT_TRUE ( sstd::isAlphabet(std::string("A")) );
    ASSERT_FALSE( sstd::isAlphabet(std::string("0")) );
    ASSERT_FALSE( sstd::isAlphabet(std::string("9")) );
    
    ASSERT_TRUE ( sstd::isAlphabet(std::string("abczAZ")) );
    ASSERT_TRUE ( sstd::isAlphabet(std::string("AlhjkboeisduhjnwoghdsfoijoieabaHGREGeiosjoidsfZ")) );
    ASSERT_FALSE( sstd::isAlphabet(std::string("w458934")) );
    ASSERT_FALSE( sstd::isAlphabet(std::string("458934a")) );
    ASSERT_FALSE( sstd::isAlphabet(std::string("w458934a")) );
    ASSERT_FALSE( sstd::isAlphabet(std::string("A8908023")) );
    ASSERT_FALSE( sstd::isAlphabet(std::string("A8908023Z")) );
}
TEST(strmatch, isAlphabet_upper_char){
    ASSERT_TRUE ( sstd::isAlphabet_upper('A') );
    ASSERT_FALSE( sstd::isAlphabet_upper('a') );
}
TEST(strmatch, isAlphabet_upper_pChar){
    ASSERT_TRUE ( sstd::isAlphabet_upper("A") );
    ASSERT_FALSE( sstd::isAlphabet_upper("a") );
    
    ASSERT_TRUE ( sstd::isAlphabet_upper("AZ") );
    ASSERT_FALSE( sstd::isAlphabet_upper("az") );
}
TEST(strmatch, isAlphabet_upper_str){
    ASSERT_TRUE ( sstd::isAlphabet_upper(std::string("A")) );
    ASSERT_FALSE( sstd::isAlphabet_upper(std::string("a")) );
    
    ASSERT_TRUE ( sstd::isAlphabet_upper(std::string("AZ")) );
    ASSERT_FALSE( sstd::isAlphabet_upper(std::string("az")) );
}
TEST(strmatch, isAlphabet_lower_char){
    ASSERT_TRUE ( sstd::isAlphabet_lower('a') );
    ASSERT_FALSE( sstd::isAlphabet_lower('A') );
}
TEST(strmatch, isAlphabet_lower_pChar){
    ASSERT_TRUE ( sstd::isAlphabet_lower("a") );
    ASSERT_FALSE( sstd::isAlphabet_lower("A") );
    
    ASSERT_TRUE ( sstd::isAlphabet_lower("az") );
    ASSERT_FALSE( sstd::isAlphabet_lower("AZ") );
}
TEST(strmatch, isAlphabet_lower_str){
    ASSERT_TRUE ( sstd::isAlphabet_lower(std::string("a")) );
    ASSERT_FALSE( sstd::isAlphabet_lower(std::string("A")) );
    
    ASSERT_TRUE ( sstd::isAlphabet_lower(std::string("az")) );
    ASSERT_FALSE( sstd::isAlphabet_lower(std::string("AZ")) );
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// charIn()

TEST(strmatch, charIn_c){
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

TEST(strmatch, charIn_s_cc){
    std::string lhs = "AB";
    std::string rhs = "ABCDEFG";
    bool ret=sstd::charIn(lhs.c_str(), rhs.c_str()); ASSERT_TRUE(ret);
}
TEST(strmatch, charIn_s_cs){
    std::string lhs = "AB";
    std::string rhs = "ABCDEFG";
    bool ret=sstd::charIn(lhs.c_str(), rhs); ASSERT_TRUE(ret);
}
TEST(strmatch, charIn_s_sc){
    std::string lhs = "AB";
    std::string rhs = "ABCDEFG";
    bool ret=sstd::charIn(lhs, rhs.c_str()); ASSERT_TRUE(ret);
}
TEST(strmatch, charIn_s_ss){
    std::string lhs = "AB";
    std::string rhs = "ABCDEFG";
    bool ret=sstd::charIn(lhs, rhs); ASSERT_TRUE(ret);
}
TEST(strmatch, charIn_s_true_01){
    std::string lhs = "ABX";
    std::string rhs = "ABCDEFG";
    bool ret=sstd::charIn(lhs.c_str(), rhs.c_str()); ASSERT_TRUE(ret);
}
TEST(strmatch, charIn_s_false_01){
    std::string lhs = "HIJ";
    std::string rhs = "ABCDEFG";
    bool ret=sstd::charIn(lhs.c_str(), rhs.c_str()); ASSERT_FALSE(ret);
}

TEST(strmatch, charIn_all_cc){
    std::string lhs = "AB";
    std::string rhs = "ABCDEFG";
    bool ret=sstd::charIn_all(lhs.c_str(), rhs.c_str()); ASSERT_TRUE(ret);
}
TEST(strmatch, charIn_all_cs){
    std::string lhs = "AB";
    std::string rhs = "ABCDEFG";
    bool ret=sstd::charIn_all(lhs.c_str(), rhs); ASSERT_TRUE(ret);
}
TEST(strmatch, charIn_all_sc){
    std::string lhs = "AB";
    std::string rhs = "ABCDEFG";
    bool ret=sstd::charIn_all(lhs, rhs.c_str()); ASSERT_TRUE(ret);
}
TEST(strmatch, charIn_all_ss){
    std::string lhs = "AB";
    std::string rhs = "ABCDEFG";
    bool ret=sstd::charIn_all(lhs, rhs); ASSERT_TRUE(ret);
}
TEST(strmatch, charIn_all_true_01){
    std::string lhs = "AB";
    std::string rhs = "ABCDEFG";
    bool ret=sstd::charIn_all(lhs.c_str(), rhs.c_str()); ASSERT_TRUE(ret);
}
TEST(strmatch, charIn_all_false_01){
    std::string lhs = "ABX";
    std::string rhs = "ABCDEFG";
    bool ret=sstd::charIn_all(lhs.c_str(), rhs.c_str()); ASSERT_FALSE(ret);
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
TEST(strmatch, strIn_02){
    ASSERT_TRUE(sstd::strIn(": ", "k:1:: v:1"));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
