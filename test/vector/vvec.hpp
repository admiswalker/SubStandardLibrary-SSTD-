#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------

void TEST__vvec__Tr_1x0(){
    std::vector<std::vector<int>> vvec = {{}}; // 1x0
    std::vector<std::vector<int>> vvecTr = sstd::Tr(vvec);
    std::vector<std::vector<int>> vvecAns; // define that the return value is 0x0.
    ASSERT_TRUE(vvecTr == vvecAns);
}
void TEST__vvec__Tr_2x0(){
    std::vector<std::vector<int>> vvec = {{}, {}}; // 2x0
    std::vector<std::vector<int>> vvecTr = sstd::Tr(vvec);
    std::vector<std::vector<int>> vvecAns; // define that the return value is 0x0.
    ASSERT_TRUE(vvecTr == vvecAns);
}
void TEST__vvec__Tr_3x0(){
    std::vector<std::vector<int>> vvec = {{}, {}, {}}; // 1x0
    std::vector<std::vector<int>> vvecTr = sstd::Tr(vvec);
    std::vector<std::vector<int>> vvecAns; // define that the return value is 0x0.
    ASSERT_TRUE(vvecTr == vvecAns);
}

//---

void TEST__vvec__Tr_1x3(){
    std::vector<std::vector<int>> vvec = {
        { 1, 2, 3 }
    };
    std::vector<std::vector<int>> vvecTr = sstd::Tr(vvec);
    std::vector<std::vector<int>> vvecAns = {
        { 1 },
        { 2 },
        { 3 }
    };
    ASSERT_TRUE(vvecTr == vvecAns);
}
void TEST__vvec__Tr_3x1(){
    std::vector<std::vector<int>> vvec = {
        { 1 },
        { 2 },
        { 3 }
    };
    std::vector<std::vector<int>> vvecTr = sstd::Tr(vvec);
    std::vector<std::vector<int>> vvecAns = {
        { 1, 2, 3 }
    };
    ASSERT_TRUE(vvecTr == vvecAns);
}

//---

void TEST__vvec__Tr_0x0(){
    std::vector<std::vector<int>> vvec;
    std::vector<std::vector<int>> vvecTr = sstd::Tr(vvec);
    std::vector<std::vector<int>> vvecAns;
    ASSERT_TRUE(vvecTr == vvecAns);
}
void TEST__vvec__Tr_1x1(){
    std::vector<std::vector<int>> vvec = {
        { 1}
    };
    std::vector<std::vector<int>> vvecTr = sstd::Tr(vvec);
    
    std::vector<std::vector<int>> vvecAns = {
        { 1}
    };
    ASSERT_TRUE(vvecTr == vvecAns);
}
void TEST__vvec__Tr_3x3(){
    std::vector<std::vector<int>> vvec = {
        { 1,  2,  3}, 
        { 4,  5,  6}, 
        { 7,  8,  9}
    };
    std::vector<std::vector<int>> vvecTr = sstd::Tr(vvec);
    
    std::vector<std::vector<int>> vvecAns = {
        { 1,  4,  7}, 
        { 2,  5,  8}, 
        { 3,  6,  9}
    };
    ASSERT_TRUE(vvecTr == vvecAns);
}

//---

void TEST__vvec__Tr_theOthers01(){
    std::vector<std::vector<int>> vvec = {
        { 1,  2,  3,  4}, 
        { 5,  6}, 
        { 7,  8,  9, 10, 11, 12, 13, 14}, 
        {15, 16, 17}, 
        {18, 19}, 
        {20, 21, 22, 23}, 
        {24, 25}, 
        {26, 27, 28}, 
        {29}
    };
    std::vector<std::vector<int>> vvecTr = sstd::Tr(vvec);
    
    std::vector<std::vector<int>> vvecAns = {
        { 1,  5,  7, 15, 18, 20, 24, 26, 29},
        { 2,  6,  8, 16, 19, 21, 25, 27}, 
        { 3,  0,  9, 17,  0, 22,  0, 28},
        { 4,  0, 10,  0,  0, 23},
        { 0,  0, 11},
        { 0,  0, 12},
        { 0,  0, 13},
        { 0,  0, 14}
    };
    
    ASSERT_TRUE(vvecTr == vvecAns);
}
void TEST__vvec__Tr_theOthers02(){
    std::vector<std::vector<int>> vvec = {
        { 1}, 
        { 2,  3}, 
        { 4,  5,  6}
    };
    std::vector<std::vector<int>> vvecTr = sstd::Tr(vvec);
    
    std::vector<std::vector<int>> vvecAns = {
        { 1,  2,  4},
        { 0,  3,  5}, 
        { 0,  0,  6}
    };
    
    ASSERT_TRUE(vvecTr == vvecAns);
}
void TEST__vvec__Tr_theOthers03(){
    std::vector<std::vector<int>> vvec = {
        { 1,  2,  3}, 
        { 4,  5}, 
        { 6}
    };
    std::vector<std::vector<int>> vvecTr = sstd::Tr(vvec);
    
    std::vector<std::vector<int>> vvecAns = {
        { 1,  4,  6},
        { 2,  5}, 
        { 3}
    };
    
    ASSERT_TRUE(vvecTr == vvecAns);
}
void TEST__vvec__Tr_theOthers04(){
    std::vector<std::vector<int>> vvec = {
        { 1}, 
        {}, 
        { 4,  5,  6}
    };
    std::vector<std::vector<int>> vvecTr = sstd::Tr(vvec);
    
    std::vector<std::vector<int>> vvecAns = {
        { 1,  0,  4},
        { 0,  0,  5}, 
        { 0,  0,  6}
    };
    
    ASSERT_TRUE(vvecTr == vvecAns);
}
void TEST__vvec__Tr_theOthers05(){
    std::vector<std::vector<int>> vvec = {
        {}, 
        { 4,  5}, 
        { 6}
    };
    std::vector<std::vector<int>> vvecTr = sstd::Tr(vvec);
    
    std::vector<std::vector<int>> vvecAns = {
        { 0,  4,  6},
        { 0,  5}, 
    };
    
    ASSERT_TRUE(vvecTr == vvecAns);
}

//---

void TEST__vvec__Tr_with_std_move(){
    std::vector<std::vector<std::string>> vvec = {
        {std::string(" 1"), std::string(" 2"), std::string(" 3")}, 
        {std::string(" 4"), std::string(" 5")}, 
        {std::string(" 6")}
    };
    std::vector<std::vector<std::string>> vvecTr = sstd::Tr(std::move(vvec));
    
    std::vector<std::vector<std::string>> vvecAns = {
        {std::string(" 1"), std::string(" 4"), std::string(" 6")},
        {std::string(" 2"), std::string(" 5")}, 
        {std::string(" 3")}
    };
    
    ASSERT_TRUE(vvecTr == vvecAns);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(vector_vvec, Tr_1x0){ TEST__vvec__Tr_1x0(); }
TEST(vector_vvec, Tr_2x0){ TEST__vvec__Tr_2x0(); }
TEST(vector_vvec, Tr_3x0){ TEST__vvec__Tr_3x0(); }

TEST(vector_vvec, Tr_1x3){ TEST__vvec__Tr_1x3(); }
TEST(vector_vvec, Tr_3x1){ TEST__vvec__Tr_3x1(); }

TEST(vector_vvec, Tr_0x0){ TEST__vvec__Tr_0x0(); }
TEST(vector_vvec, Tr_1x1){ TEST__vvec__Tr_1x1(); }
TEST(vector_vvec, Tr_2x2){ TEST__vvec__Tr_3x3(); }

TEST(vector_vvec, Tr_theOthers01){ TEST__vvec__Tr_theOthers01(); }
TEST(vector_vvec, Tr_theOthers02){ TEST__vvec__Tr_theOthers02(); }
TEST(vector_vvec, Tr_theOthers03){ TEST__vvec__Tr_theOthers03(); }
TEST(vector_vvec, Tr_theOthers04){ TEST__vvec__Tr_theOthers04(); }
TEST(vector_vvec, Tr_theOthers05){ TEST__vvec__Tr_theOthers05(); }

TEST(vector_vvec, Tr_with_std_move){ TEST__vvec__Tr_with_std_move(); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

