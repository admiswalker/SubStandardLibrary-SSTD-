#pragma once

// --- Notification ---
// 
//   This sstd::slice() is implemented to have a same behavior with python slice.

//-----------------------------------------------------------------------------------------------------------------------------------------------

/*
 *	what i really want.
 *	
 *	std::vector<T> vec_sliced = vec[0];
 *	std::vector<T> vec_sliced = vec[sstd::slice(1, sstd::end())];
 *	std::vector<T> vec_sliced = vec[sstd::slice(sstd::begin(), sstd::end())];
 *	std::vector<T> vec_sliced = vec[sstd::slice_mv(sstd::begin(), sstd::end())];
 */

/*
 *	what i really implimented.
 *
 *	std::vector<T> vec_sliced = vec[0];
 *	std::vector<T> vec_sliced = vec && sstd::slice(1, sstd::end());
 *	std::vector<T> vec_sliced = vec && sstd::slice(sstd::begin(), sstd::end());
 *	std::vector<T> vec_sliced = vec && sstd::slice_mv(sstd::begin(), sstd::end());
 */

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(vector_slice, ii00){
	std::vector<int> vec    ={1,2,3,4,5};
	std::vector<int> vec_ans={1,2,3,4  };
	std::vector<int> vec_sliced = vec && sstd::slice((int)0, (int)-1);
	ASSERT_TRUE(vec_ans == vec_sliced);
}
TEST(vector_slice, ii01){
	std::vector<int> vec    ={1,2,3,4,5};
	std::vector<int> vec_ans={  2,3    };
	std::vector<int> vec_sliced = vec && sstd::slice((int)-4, (int)-2);
	ASSERT_TRUE(vec_ans == vec_sliced);
}
//---
TEST(vector_slice, iu00){
	std::vector<int> vec    ={1,2,3,4,5};
	std::vector<int> vec_ans={1,2,3,4  };
	std::vector<int> vec_sliced = vec && sstd::slice((int)0, (uint)4);
	ASSERT_TRUE(vec_ans == vec_sliced);
}
TEST(vector_slice, iu01){
	std::vector<int> vec    ={1,2,3,4,5};
	std::vector<int> vec_ans={  2      };
	std::vector<int> vec_sliced = vec && sstd::slice((int)-4, (uint)2);
	ASSERT_TRUE(vec_ans == vec_sliced);
}
//---
TEST(vector_slice, ui00){
	std::vector<int> vec    ={1,2,3,4,5};
	std::vector<int> vec_ans={1,2,3,4  };
	std::vector<int> vec_sliced = vec && sstd::slice((uint)0, (int)-1);
	ASSERT_TRUE(vec_ans == vec_sliced);
}
TEST(vector_slice, ui01){
	std::vector<int> vec    ={1,2,3,4,5};
	std::vector<int> vec_ans={1,2,3    };
	std::vector<int> vec_sliced = vec && sstd::slice((uint)0, (int)-2);
	ASSERT_TRUE(vec_ans == vec_sliced);
}
TEST(vector_slice, ui02){
	std::vector<int> vec    ={1,2,3,4,5};
	std::vector<int> vec_ans={    3    };
	std::vector<int> vec_sliced = vec && sstd::slice((uint)2, (int)-2);
	ASSERT_TRUE(vec_ans == vec_sliced);
}
//---
TEST(vector_slice, uu00){
	std::vector<int> vec={1,2,3};
	std::vector<int> vec_sliced = vec && sstd::slice((uint)0, (uint)vec.size());
	ASSERT_TRUE(vec == vec_sliced);
}
TEST(vector_slice, uu01){
	std::vector<int> vec    ={1,2,3,4,5};
	std::vector<int> vec_ans={  2,3    };
	std::vector<int> vec_sliced = vec && sstd::slice((uint)1, (uint)3);
	ASSERT_TRUE(vec_ans == vec_sliced);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

