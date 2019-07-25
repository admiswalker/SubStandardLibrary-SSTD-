#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------

void TEST__vvec__Tr_1x3(){
	std::vector<std::vector<int>> vvec = {
		{ 1, 2, 3 }
	};
	std::vector<std::vector<int>> vvecTr = sstd::Tr<int>(vvec);
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
	std::vector<std::vector<int>> vvecTr = sstd::Tr<int>(vvec);
	std::vector<std::vector<int>> vvecAns = {
		{ 1, 2, 3 }
	};
	ASSERT_TRUE(vvecTr == vvecAns);
}

//---

void TEST__vvec__Tr_0x0(){
	std::vector<std::vector<int>> vvec;
	std::vector<std::vector<int>> vvecTr = sstd::Tr<int>(vvec);
	std::vector<std::vector<int>> vvecAns;
	ASSERT_TRUE(vvecTr == vvecAns);
}
void TEST__vvec__Tr_1x1(){
	std::vector<std::vector<int>> vvec = {
		{ 1}
	};
	std::vector<std::vector<int>> vvecTr = sstd::Tr<int>(vvec);
	
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
	std::vector<std::vector<int>> vvecTr = sstd::Tr<int>(vvec);
	
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
	std::vector<std::vector<int>> vvecTr = sstd::Tr<int>(vvec);
	
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
	std::vector<std::vector<int>> vvecTr = sstd::Tr<int>(vvec);
	
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
	std::vector<std::vector<int>> vvecTr = sstd::Tr<int>(vvec);
	
	std::vector<std::vector<int>> vvecAns = {
		{ 1,  4,  6},
		{ 2,  5}, 
		{ 3}
	};
	
	ASSERT_TRUE(vvecTr == vvecAns);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(vvec, Tr_1x3){ TEST__vvec__Tr_1x3(); }
TEST(vvec, Tr_3x1){ TEST__vvec__Tr_3x1(); }

TEST(vvec, Tr_0x0){ TEST__vvec__Tr_0x0(); }
TEST(vvec, Tr_1x1){ TEST__vvec__Tr_1x1(); }
TEST(vvec, Tr_2x2){ TEST__vvec__Tr_3x3(); }

TEST(vvec, Tr_theOthers01){ TEST__vvec__Tr_theOthers01(); }
TEST(vvec, Tr_theOthers02){ TEST__vvec__Tr_theOthers02(); }
TEST(vvec, Tr_theOthers03){ TEST__vvec__Tr_theOthers03(); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

