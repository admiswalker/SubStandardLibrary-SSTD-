#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------

void TEST__slice__call(){
	namespace std=sstd_stdVector_extensions;
	
	printf("imh\n");
	std::vector<int> vec={1,2,3};
//	sstd::printn(vec);
	
//	std::vector<int> vec_sliced = vec[sstd::slice(1,2)];
	std::vector<int> vec_sliced = vec[sstd::slice_range()];
//	std::vector<int> vec_sliced = vec + sstd::slice_range();
//	vec[sstd::slice((uint)1,(uint)2)];
//	sstd::printn(vec_sliced);
	
	
	
//	ASSERT_TRUE(vvecTr == vvecAns);
}


//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(vector_slice, Tr_1x0){ TEST__slice__call(); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

