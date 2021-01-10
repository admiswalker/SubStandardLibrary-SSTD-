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
    std::string str_tI = sstd::read_withoutBOM(std::string(R"(./test/tinyInterpreter.txt)"));
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
