#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(strEdit, theOthers){
    printf("■ strEdit\n");
    printf("  □ readA_bin\n");
    std::vector<uint8> raw = sstd::read_bin("./test/test.png");
    sstd::printn_all(raw.size());
    printf("  □ write_bin\n");
    if(!sstd::write_bin("./test__write_bin_char.png",             raw)){ sstd::pdbg("ERROR: sstd::write_bin()\n"); }
    if(!sstd::write_bin(std::string("./test__write_bin_str.png"), raw)){ sstd::pdbg("ERROR: sstd::write_bin()\n"); }
    
    printf("  □ read_withoutBOM & splitByLine\n");
//    std::string str_tI = sstd::read_withoutBOM(R"(./test/tinyInterpreter.txt)");
    std::string str_tI = sstd::read_withoutBOM(std::string(R"(./test/file/tinyInterpreter.txt)"));
    std::vector<std::string> splitLList = sstd::splitByLine(str_tI);
    printf("\n");
    printf("  ./test/tinyInterpreter.txt\n");
    printf("+----+---------------------------------------------------------------------+\n");
    for(uint i=0; i<splitLList.size(); ++i){
        printf("| %2d | %-67s |\n", i, splitLList[i].c_str());
    }
    printf("+----+---------------------------------------------------------------------+\n");
    printf("\n");
    
    printf("  □ splitByX\n");
    std::vector<std::string> vecRow;
    vecRow = sstd::split("ABC DEF",       ' ');        sstd::printn(vecRow); // "ABC DEF" -> ["ABC", "DEF"]
    vecRow = sstd::split(" ABC   D EF  ", ' ');        sstd::printn(vecRow); // " ABC   D EF  " -> ["ABC", "D", "EF"]
    
    vecRow = sstd::split("ABC,DEF",              ','); sstd::printn(vecRow); // "ABC,DEF" -> ["ABC", "DEF"]
    vecRow = sstd::split(" ABC  , D,  EF ,GH  ", ','); sstd::printn(vecRow); // " ABC  , D,  EF ,GH  " -> ["ABC", "D", "EF",  "GH"]
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(strEdit, lstrip){
    std::string str_in  = " \t abcd \t ";
    std::string str_ans =     "abcd \t ";
    ASSERT_TRUE(sstd::lstrip(str_in.c_str()) == str_ans);
    ASSERT_TRUE(sstd::lstrip(str_in        ) == str_ans);
}
TEST(strEdit, lstrip_ow){
    std::string str_in  = " \t abcd \t ";
    std::string str_ans =     "abcd \t ";
    sstd::lstrip_ow(str_in);
    ASSERT_TRUE(str_in == str_ans);
}
TEST(strEdit, rstrip){
    std::string str_in  = " \t abcd \t ";
    std::string str_ans = " \t abcd";
    ASSERT_TRUE(sstd::rstrip(str_in.c_str()) == str_ans);
    ASSERT_TRUE(sstd::rstrip(str_in        ) == str_ans);
}
TEST(strEdit, rstrip_ow){
    std::string str_in  = " \t abcd \t ";
    std::string str_ans = " \t abcd";
    sstd::rstrip_ow(str_in);
    ASSERT_TRUE(str_in == str_ans);
}
TEST(strEdit, strip){
    std::string str_in  = " \t abcd \t ";
    std::string str_ans = "abcd";
    ASSERT_TRUE(sstd::strip(str_in.c_str()) == str_ans);
    ASSERT_TRUE(sstd::strip(str_in        ) == str_ans);
}
TEST(strEdit, strip_ow){
    std::string str_in  = " \t abcd \t ";
    std::string str_ans = "abcd";
    sstd::strip_ow(str_in);
    ASSERT_TRUE(str_in == str_ans);
}
TEST(strEdit, strip_vec){
    std::vector<std::string> vecStr_in  = {" \t abcd01 \t ", " \t abcd02 \t ", " \t abcd03 \t "};
    std::vector<std::string> vecStr_ans = {"abcd01", "abcd02", "abcd03"};
    ASSERT_TRUE(sstd::strip(vecStr_in) == vecStr_ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(strEdit, stripAll_case01_01){
    std::string str_in  = "0a0b0cx0d0xe0f0g0";
    std::string str_ans = "abcdefg";
    std::string ret = sstd::stripAll(str_in.c_str(), "x0");
    ASSERT_TRUE(ret == str_ans);
}
TEST(strEdit, stripAll_case01_02){
    std::string str_in  = "\r\nabc\r\n\r\ndefg\r\n";
    std::string str_ans = "abcdefg";
    std::string ret = sstd::stripAll(str_in.c_str(), "\r\n");
    ASSERT_TRUE(ret == str_ans);
}
TEST(strEdit, stripAll_case02){
    std::string str_in  = "0a0b0cx0d0xe0f0g00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x";
    std::string str_ans = "abcdefg";
    std::string ret = sstd::stripAll(str_in.c_str(), "x0");
    ASSERT_TRUE(ret == str_ans);
}

#define strEdit_stripAll_check_io(LHS, RHS)                     \
    std::string str_in  = "0a0b0cx0d0xe0f0g0";                  \
    std::string str_ans = "abcdefg";                            \
    std::string ret = sstd::stripAll(LHS, RHS);                 \
    ASSERT_TRUE(ret == str_ans);
TEST(strEdit, stripAll_cc){ strEdit_stripAll_check_io(str_in.c_str(),             "x0" ); }
TEST(strEdit, stripAll_sc){ strEdit_stripAll_check_io(str_in,                     "x0" ); }
TEST(strEdit, stripAll_cs){ strEdit_stripAll_check_io(str_in.c_str(), std::string("x0")); }
TEST(strEdit, stripAll_ss){ strEdit_stripAll_check_io(str_in,         std::string("x0")); }
#undef strEdit_stripAll_check_io

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(strEdit, stripAll_ow_case01_01){
    std::string str_in  = "0a0b0cx0d0xe0f0g0";
    std::string str_ans = "abcdefg";
    sstd::stripAll_ow(str_in, "x0");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, stripAll_ow_case01_02){
    std::string str_in  = "";
    std::string str_ans = "";
    sstd::stripAll_ow(str_in, "x0");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, stripAll_ow_case01_03){
    std::string str_in  = "";
    std::string str_ans = "";
    sstd::stripAll_ow(str_in, "");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}
TEST(strEdit, stripAll_ow_case02){
    std::string str_in  = "0a0b0cx0d0xe0f0g00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x00000000000000000000000000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000x0x0x0x0x0x000x0x0xxx0000x0x0xx00000x00x0x0x";
    std::string str_ans = "abcdefg";
    sstd::stripAll_ow(str_in, "x0");
    ASSERT_STREQ(str_in.c_str(), str_ans.c_str());
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
