#pragma once

/*
	what i really want.
	
	std::vector<T> vec_sliced = vec[0];
	std::vector<T> vec_sliced = vec[sstd::slice(1, sstd::end())];
	std::vector<T> vec_sliced = vec[sstd::slice(sstd::begin(), sstd::end())];
	std::vector<T> vec_sliced = vec[sstd::slice_mv(sstd::begin(), sstd::end())];
*/

/*
	what i really implimented.

	std::vector<T> vec_sliced = vec[0];
	std::vector<T> vec_sliced = vec && sstd::slice(1, sstd::end());
	std::vector<T> vec_sliced = vec && sstd::slice(sstd::begin(), sstd::end());
	std::vector<T> vec_sliced = vec && sstd::slice_mv(sstd::begin(), sstd::end());
*/

//-----------------------------------------------------------------------------------------------------------------------------------------------

void TEST__slice__call(){
	printf("imh\n");
	
	std::vector<int> vec={1,2,3};
	std::vector<int> vec_sliced = vec && sstd::slice(0, vec.size());
	ASSERT_TRUE(vec == vec_sliced);
}	
//	sstd::printn(vec);

//	std::vector<int> vec_sliced = vec[sstd::slice(1,2)];
//	std::vector<int> vec_sliced = vec[sstd::slice_range()];
//	std::vector<int> vec_sliced = vec + sstd::slice_range();
//	vec[sstd::slice((uint)1,(uint)2)];
//	sstd::printn(vec_sliced);

//	ASSERT_TRUE(vvecTr == vvecAns);

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(vector_slice, slice__call){ TEST__slice__call(); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

