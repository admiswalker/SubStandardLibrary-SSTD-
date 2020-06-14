#pragma once

//ASSERT_TRUE();
//ASSERT_STREQ(test.c_str(), ans.c_str());

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(strEdit, theOthers){
    printf("■ strEdit\n");
    printf("  □ readAll_bin\n");
    std::vector<uint8> raw = sstd::readAll_bin("./test/test.png");
    sstd::printn_all(raw.size());
    printf("  □ writeAll_bin\n");
    if(!sstd::writeAll_bin("./test__writeAll_bin_char.png",             raw)){ sstd::pdbg("ERROR: sstd::writeAll_bin()\n"); }
    if(!sstd::writeAll_bin(std::string("./test__writeAll_bin_str.png"), raw)){ sstd::pdbg("ERROR: sstd::writeAll_bin()\n"); }
    
    printf("  □ readAll_withoutBOM & splitByLine\n");
//    std::string str_tI = sstd::readAll_withoutBOM(R"(./test/tinyInterpreter.txt)");
    std::string str_tI = sstd::readAll_withoutBOM(std::string(R"(./test/tinyInterpreter.txt)"));
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
/*
// 実装完了 (処理時間短縮のため，コメントアウト)
TEST(strEdit, strIn){
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
        bool ret=sstd::strIn(lhs, rhs); ASSERT_TRUE(!ret);
    }
}
//*/

//-----------------------------------------------------------------------------------------------------------------------------------------------
