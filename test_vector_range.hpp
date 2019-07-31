#pragma once

/*
	what i really want.
	
	std::vector<T> vec_sliced = vec[0];
	std::vector<T> vec_sliced = vec[sstd::slice(1, sstd::end())];
	std::vector<T> vec_sliced = vec[sstd::slice(sstd::begin(), sstd::end())];
	std::vector<T> vec_sliced = vec[sstd::slice_mv(sstd::begin(), sstd::end())];
*/



//----------------
/*
	what i really implimented.

	std::vector<T> vec_sliced = vec[0];
	std::vector<T> vec_sliced = vec && sstd::range(1, sstd::end());
	std::vector<T> vec_sliced = vec && sstd::range(sstd::begin(), sstd::end());
	std::vector<T> vec_sliced = vec && sstd::range_mv(sstd::begin(), sstd::end());
*/

//-----------------------------------------------------------------------------------------------------------------------------------------------

void TEST__range__call(){
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

TEST(vector_range, slice__call){ TEST__range__call(); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

