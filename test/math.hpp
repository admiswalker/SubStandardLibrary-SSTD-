#pragma once

void TEST_math(){
    printf("■ math\n");
        // 偶数への丸め (round to even)
    float  re_f1 = sstd::round2even(1.5); printf("round to even: %lf ≒ %lf\n", 1.5, re_f1);
    float  re_f2 = sstd::round2even(2.5); printf("round to even: %lf ≒ %lf\n", 2.5, re_f2);
    double re_d1 = sstd::round2even(1.5); printf("round to even: %lf ≒ %lf\n", 1.5, re_d1);
    double re_d2 = sstd::round2even(2.5); printf("round to even: %lf ≒ %lf\n", 2.5, re_d2);
        // 奇数への丸め (round to odd)
    float  ro_f1 = sstd::round2odd(1.5); printf("round to odd: %lf ≒ %lf\n", 1.5, ro_f1);
    float  ro_f2 = sstd::round2odd(2.5); printf("round to odd: %lf ≒ %lf\n", 2.5, ro_f2);
    double ro_d1 = sstd::round2odd(1.5); printf("round to odd: %lf ≒ %lf\n", 1.5, ro_d1);
    double ro_d2 = sstd::round2odd(2.5); printf("round to odd: %lf ≒ %lf\n", 2.5, ro_d2);
    printf("\n");
    
    std::vector<float> buf_f = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4};
    sstd::printn(buf_f);
//    printf("sum: %f\n", sstd::sum(buf_f));
//    printf("sum_abs: %f\n", sstd::sum_abs(buf_f));
    printf("ave: %f\n", sstd::ave(buf_f));
    printf("ave in the first 2 elements: %f\n", sstd::ave(buf_f, 2));
    printf("med: %f\n", sstd::med(buf_f));
    printf("var: %f\n", sstd::var(buf_f));
    printf("var_p: %f\n", sstd::var_p(buf_f));
    printf("stdev: %f\n", sstd::stdev(buf_f));
    printf("stdev_p: %f\n", sstd::stdev_p(buf_f));
    printf("\n");
    
    std::vector<double> buf_d = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4};
    sstd::printn(buf_d);
//    printf("sum: %f\n", sstd::sum(buf_d));
//    printf("sum_abs: %f\n", sstd::sum_abs(buf_d));
    printf("ave: %f\n", sstd::ave(buf_d));
    printf("ave in the first 2 elements: %f\n", sstd::ave(buf_d, 2));
    printf("med: %f\n", sstd::med(buf_d));
    printf("var: %f\n", sstd::var(buf_d));
    printf("var_p: %f\n", sstd::var_p(buf_d));
    printf("stdev: %f\n", sstd::stdev(buf_d));
    printf("stdev_p: %f\n", sstd::stdev_p(buf_d));
    printf("\n");
    
    /* test: Kahan summation algorithm 01 */
//    std::vector<float> buf_f2 = {100000.0f, 0.0125f, 0.0125f, 0.0125f, 0.0125f, 0.0125f, 0.0125f, 0.0125f, 0.0125f}; // float の有効桁数 = 24/1og2(10) ≒ 7.224 ≒ 7
//    printf("sum: %lf\n", sstd::sum(buf_f2));
//    std::vector<double> buf_d2 = {100000000000000.0, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125}; // double の有効桁数 = 24/1og2(10) ≒ 15.955 ≒ 15
//    printf("sum: %lf\n", sstd::sum(buf_d2));
//    printf("\n");
    
    /* test: Kahan summation algorithm 02 */
    /*
    double d1=100000000.0;
    double d2=0.000000001;
    for(uint i=0; i<1000000000; i++){ d1+=d2; }
    printf("normal sum: %lf\n", d1);

    double lhs=d1;
    double del=0;
    for(uint i=0; i<1000000000; i++){
        double r1=d2-del;
        double r2=lhs+r1;
        del=(r2-lhs)-r1;
        lhs=r2;
    }
    printf(" Kahan sum: %lf\n", lhs);
    printf("\n");
    */

    // get a list of prime number under rhs.
    std::vector<uint64> primeList = sstd::prime((uint)100);
    printf("primeList = "); sstd::print(primeList);
    printf("\n");

    uint64 fact_num = 2*2*3*3*5*5;
    std::vector<struct sstd::fact> factList = sstd::factor(fact_num);
    printf("%lu = %lu^%lu", fact_num, factList[0].prime, factList[0].num);
    for(uint i=1; i<factList.size(); i++){ printf(" + %lu^%lu", factList[i].prime, factList[i].num); }
    sstd::print(factList);
    sstd::printn(factList);
    sstd::printn_all(factList);
    printf("\n");

    uint div_num = 2*2*3*3*5*5;
    std::vector<uint64> divList = sstd::divisor(div_num);
    printf("divList = "); sstd::print(divList);
    printf("divList = "); sstd::print(sstd::divisor(factList));
    printf("\n");

    uint   ui  = sstd::pow((  uint)2, (  uint) 4); printf("%u\n",  ui );
    uint8  u8  = sstd::pow(( uint8)2, ( uint8) 4); printf("%u\n",  u8 );
    uint16 u16 = sstd::pow((uint16)2, (uint16) 8); printf("%u\n",  u16);
    uint32 u32 = sstd::pow((uint32)2, (uint32) 9); printf("%u\n",  u32);
    uint64 u64 = sstd::pow((uint64)2, (uint64)10); printf("%lu\n", u64);
    printf("\n");
}

TEST(math, theOthers){
    TEST_math();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(math, sum){
    { std::vector< char > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_EQ(sstd::sum(buf), -5); }
    { std::vector< int8 > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_EQ(sstd::sum(buf), -5); }
    { std::vector< int16> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_EQ(sstd::sum(buf), -5); }
    { std::vector< int32> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_EQ(sstd::sum(buf), -5); }
    { std::vector< int64> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_EQ(sstd::sum(buf), -5); }
//    { std::vector<uchar > buf={               0,1,2,3,4}; ASSERT_EQ(sstd::sum(buf), 10ul); }
    { std::vector<uint8 > buf={               0,1,2,3,4}; ASSERT_EQ(sstd::sum(buf), 10ul ); }
    { std::vector<uint16> buf={               0,1,2,3,4}; ASSERT_EQ(sstd::sum(buf), 10ul ); }
    { std::vector<uint32> buf={               0,1,2,3,4}; ASSERT_EQ(sstd::sum(buf), 10ul ); }
    { std::vector<uint64> buf={               0,1,2,3,4}; ASSERT_EQ(sstd::sum(buf), 10ull); }
    
    { std::vector<float > buf;                            ASSERT_EQ(sstd::sum(buf),  0.0); } // Pairwise summation algorithm
    { std::vector<float > buf={1};                        ASSERT_EQ(sstd::sum(buf),  1.0); } // Pairwise summation algorithm
    { std::vector<float > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_EQ(sstd::sum(buf), -5.0); } // Pairwise summation algorithm
    { std::vector<double> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_EQ(sstd::sum(buf), -5.0); } // Pairwise summation algorithm
    { std::vector<float > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_EQ(sstd::sum_abs(buf), 25.0); } // Pairwise summation algorithm
    { std::vector<double> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_EQ(sstd::sum_abs(buf), 25.0); } // Pairwise summation algorithm
    
    { std::vector<float > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_EQ(sstd::sumK(buf), -5.0); } // Kahan summation algorithm
    { std::vector<double> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_EQ(sstd::sumK(buf), -5.0); } // Kahan summation algorithm
    { std::vector<float > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_EQ(sstd::sumK_abs(buf), 25.0); } // Kahan summation algorithm
    { std::vector<double> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_EQ(sstd::sumK_abs(buf), 25.0); } // Kahan summation algorithm
    
    {
        // float の有効桁数 = 24/1og2(10) ≒ 7.224 ≒ 7
        std::vector<float> buf_f; buf_f.push_back( 1000000.0f ); for(uint i=0; i<10000; ++i){ buf_f.push_back( 0.0001f ); }
        ASSERT_EQ((int64)sstd::sum (buf_f)                                    , 1000001ll); // Pairwise summation algorithm
        ASSERT_EQ((int64)sstd::sumK(buf_f)                                    , 1000001ll); // Kahan summation algorithm
        ASSERT_EQ((int64)std::accumulate(buf_f.begin(), buf_f.end(), (float)0), 1000000ll);
    }
    {
        // double の有効桁数 = 24/1og2(10) ≒ 15.955 ≒ 15
        std::vector<double> buf_f; buf_f.push_back( 1000000000000000.0 ); for(uint i=0; i<10000; ++i){ buf_f.push_back( 0.0001 ); }
        ASSERT_EQ((int64)sstd::sum (buf_f)                                     , 1000000000000001ll); // Pairwise summation algorithm
        ASSERT_EQ((int64)sstd::sumK(buf_f)                                     , 1000000000000001ll); // Kahan summation algorithm
        ASSERT_EQ((int64)std::accumulate(buf_f.begin(), buf_f.end(), (double)0), 1000000000000000ll);
    }
    
    // TODO: wite test of "sum(vec, a, b)" function;
//    { std::vector< int> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_EQ((std::vector<int>::iterator)sstd::sum(buf.begin(), (std::vector<int>::iterator)buf.end()), -5); }
}

TEST(math, sum_ab){
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(math, min_vec){
    { std::vector< char > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::min(buf)==-5); }
    { std::vector< int8 > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::min(buf)==-5); }
    { std::vector< int16> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::min(buf)==-5); }
    { std::vector< int32> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::min(buf)==-5); }
    { std::vector< int64> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::min(buf)==-5); }
//    { std::vector<uchar > buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::min(buf)==0); }
    { std::vector<uint8 > buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::min(buf)==0); }
    { std::vector<uint16> buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::min(buf)==0); }
    { std::vector<uint32> buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::min(buf)==0); }
    { std::vector<uint64> buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::min(buf)==0); }
}
TEST(math, min_vec_abs){
    { std::vector< char > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::min_abs(buf)==0); }
    { std::vector< int8 > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::min_abs(buf)==0); }
    { std::vector< int16> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::min_abs(buf)==0); }
    { std::vector< int32> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::min_abs(buf)==0); }
    { std::vector< int64> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::min_abs(buf)==0); }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(math, max_vec){
    { std::vector< char > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::max(buf)==4); }
    { std::vector< int8 > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::max(buf)==4); }
    { std::vector< int16> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::max(buf)==4); }
    { std::vector< int32> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::max(buf)==4); }
    { std::vector< int64> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::max(buf)==4); }
//    { std::vector<uchar > buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::max(buf)==4); }
    { std::vector<uint8 > buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::max(buf)==4); }
    { std::vector<uint16> buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::max(buf)==4); }
    { std::vector<uint32> buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::max(buf)==4); }
    { std::vector<uint64> buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::max(buf)==4); }
}
TEST(math, max_vec_abs){
    { std::vector< char > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::max_abs(buf)==-5); }
    { std::vector< int8 > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::max_abs(buf)==-5); }
    { std::vector< int16> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::max_abs(buf)==-5); }
    { std::vector< int32> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::max_abs(buf)==-5); }
    { std::vector< int64> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::max_abs(buf)==-5); }
}
TEST(math, max_mat_c){
    { sstd::mat_c< char > buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::max(buf)==1); }
    { sstd::mat_c< int8 > buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::max(buf)==1); }
    { sstd::mat_c< int16> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::max(buf)==1); }
    { sstd::mat_c< int32> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::max(buf)==1); }
    { sstd::mat_c< int64> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::max(buf)==1); }
    { sstd::mat_c<uint8 > buf={{ 0,  1}, {2, 3}}; ASSERT_TRUE(sstd::max(buf)==3); }
    { sstd::mat_c<uint16> buf={{ 0,  1}, {2, 3}}; ASSERT_TRUE(sstd::max(buf)==3); }
    { sstd::mat_c<uint32> buf={{ 0,  1}, {2, 3}}; ASSERT_TRUE(sstd::max(buf)==3); }
    { sstd::mat_c<uint64> buf={{ 0,  1}, {2, 3}}; ASSERT_TRUE(sstd::max(buf)==3); }
    { sstd::mat_c< float> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::max(buf)==1); }
    { sstd::mat_c<double> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::max(buf)==1); }
}
TEST(math, max_mat_r){
    { sstd::mat_r< char > buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::max(buf)==1); }
    { sstd::mat_r< int8 > buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::max(buf)==1); }
    { sstd::mat_r< int16> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::max(buf)==1); }
    { sstd::mat_r< int32> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::max(buf)==1); }
    { sstd::mat_r< int64> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::max(buf)==1); }
    { sstd::mat_r<uint8 > buf={{ 0,  1}, {2, 3}}; ASSERT_TRUE(sstd::max(buf)==3); }
    { sstd::mat_r<uint16> buf={{ 0,  1}, {2, 3}}; ASSERT_TRUE(sstd::max(buf)==3); }
    { sstd::mat_r<uint32> buf={{ 0,  1}, {2, 3}}; ASSERT_TRUE(sstd::max(buf)==3); }
    { sstd::mat_r<uint64> buf={{ 0,  1}, {2, 3}}; ASSERT_TRUE(sstd::max(buf)==3); }
    { sstd::mat_r< float> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::max(buf)==1); }
    { sstd::mat_r<double> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::max(buf)==1); }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(math, argmin_vec){
    { std::vector< char > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmin(buf)==0); }
    { std::vector< int8 > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmin(buf)==0); }
    { std::vector< int16> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmin(buf)==0); }
    { std::vector< int32> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmin(buf)==0); }
    { std::vector< int64> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmin(buf)==0); }
//    { std::vector<uchar > buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::min(buf)==0); }
    { std::vector<uint8 > buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::argmin(buf)==0); }
    { std::vector<uint16> buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::argmin(buf)==0); }
    { std::vector<uint32> buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::argmin(buf)==0); }
    { std::vector<uint64> buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::argmin(buf)==0); }
}
TEST(math, argmin_vec_abs){
    { std::vector< char > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmin_abs(buf)==5); }
    { std::vector< int8 > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmin_abs(buf)==5); }
    { std::vector< int16> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmin_abs(buf)==5); }
    { std::vector< int32> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmin_abs(buf)==5); }
    { std::vector< int64> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmin_abs(buf)==5); }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(math, argmax_vec){
    { std::vector< char > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmax(buf)==buf.size()-1); }
    { std::vector< int8 > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmax(buf)==buf.size()-1); }
    { std::vector< int16> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmax(buf)==buf.size()-1); }
    { std::vector< int32> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmax(buf)==buf.size()-1); }
    { std::vector< int64> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmax(buf)==buf.size()-1); }
//    { std::vector<uchar > buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::argmax(buf)==buf.size()-1); }
    { std::vector<uint8 > buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::argmax(buf)==buf.size()-1); }
    { std::vector<uint16> buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::argmax(buf)==buf.size()-1); }
    { std::vector<uint32> buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::argmax(buf)==buf.size()-1); }
    { std::vector<uint64> buf={               0,1,2,3,4}; ASSERT_TRUE(sstd::argmax(buf)==buf.size()-1); }
}
TEST(math, argmax_vec_abs){
    { std::vector< char > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmax_abs(buf)==0); }
    { std::vector< int8 > buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmax_abs(buf)==0); }
    { std::vector< int16> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmax_abs(buf)==0); }
    { std::vector< int32> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmax_abs(buf)==0); }
    { std::vector< int64> buf={-5,-4,-3,-2,-1,0,1,2,3,4}; ASSERT_TRUE(sstd::argmax_abs(buf)==0); }
}
TEST(math, argmax_mat_c){
    { sstd::mat_c< char > buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_c< int8 > buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_c< int16> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_c< int32> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_c< int64> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_c<uint8 > buf={{ 0,  1}, {2, 3}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_c<uint16> buf={{ 0,  1}, {2, 3}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_c<uint32> buf={{ 0,  1}, {2, 3}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_c<uint64> buf={{ 0,  1}, {2, 3}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_c< float> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_c<double> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
}
TEST(math, argmax_mat_r){
    { sstd::mat_r< char > buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_r< int8 > buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_r< int16> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_r< int32> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_r< int64> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_r<uint8 > buf={{ 0,  1}, {2, 3}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_r<uint16> buf={{ 0,  1}, {2, 3}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_r<uint32> buf={{ 0,  1}, {2, 3}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_r<uint64> buf={{ 0,  1}, {2, 3}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_r< float> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
    { sstd::mat_r<double> buf={{-2, -1}, {0, 1}}; ASSERT_TRUE(sstd::argmax(buf)==3); }
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(math, nearest_down){
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_down(buf, -100)==buf[0]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_down(buf, -1  )==buf[0]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_down(buf,    0)==buf[0]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_down(buf,    1)==buf[1]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_down(buf,    2)==buf[2]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_down(buf,    3)==buf[3]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_down(buf,    4)==buf[3]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_down(buf,    5)==buf[4]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_down(buf,    6)==buf[4]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_down(buf,  100)==buf[4]); }
    
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_up  (buf, -100)==buf[0]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_up  (buf, -1  )==buf[0]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_up  (buf,    0)==buf[0]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_up  (buf,    1)==buf[1]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_up  (buf,    2)==buf[2]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_up  (buf,    3)==buf[3]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_up  (buf,    4)==buf[4]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_up  (buf,    5)==buf[4]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_up  (buf,    6)==buf[4]); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::nearest_up  (buf,  100)==buf[4]); }
}
TEST(math, argnearest_down){
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_down(buf, -100)==0); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_down(buf, -1  )==0); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_down(buf,    0)==0); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_down(buf,    1)==1); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_down(buf,    2)==2); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_down(buf,    3)==3); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_down(buf,    4)==3); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_down(buf,    5)==4); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_down(buf,    6)==4); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_down(buf,  100)==4); }
    
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_up  (buf, -100)==0); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_up  (buf, -1  )==0); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_up  (buf,    0)==0); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_up  (buf,    1)==1); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_up  (buf,    2)==2); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_up  (buf,    3)==3); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_up  (buf,    4)==4); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_up  (buf,    5)==4); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_up  (buf,    6)==4); }
    { std::vector<int> buf={{0, 1, 2, 3, 5}}; ASSERT_TRUE(sstd::argnearest_up  (buf,  100)==4); }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(math, sort){
    std::vector<float> buf = {5, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4};
    std::vector<float> ans = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
    
    sstd::sort(buf); ASSERT_TRUE(buf==ans);
}
TEST(math, sorted){
    std::vector<float> buf = {5, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4};
    std::vector<float> ans = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
    
    std::vector<float> ret=sstd::sorted(buf); ASSERT_TRUE(ret==ans);
}
TEST(math, sort_mv){
    std::vector<float> buf = {5, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4};
    std::vector<float> ans = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
    
    std::vector<float> ret=sstd::sorted(std::move(buf)); ASSERT_TRUE(ret==ans);
}

//---

TEST(math, sort_gr){
    std::vector<float> buf = {5, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4};
    std::vector<float> ans_gr = {5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5};
    
    sstd::sort_gr(buf); ASSERT_TRUE(buf==ans_gr);
}
TEST(math, sorted_gr){
    std::vector<float> buf = {5, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4};
    std::vector<float> ans_gr = {5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5};
    
    std::vector<float> ret=sstd::sorted_gr(buf); ASSERT_TRUE(ret==ans_gr);
}
TEST(math, sort_gr_mv){
    std::vector<float> buf = {5, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4};
    std::vector<float> ans_gr = {5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5};
    
    std::vector<float> ret=sstd::sorted_gr(std::move(buf)); ASSERT_TRUE(ret==ans_gr);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(math, nonzero){
    std::vector<double>  in={1,2,3,0,4};
    std::vector<double> ans={1,2,3};
    std::vector<double> out=sstd::nonzero(in);
    
    ASSERT_TRUE(out==ans);
}
TEST(math, supress){
    std::vector<double> in1={1,2,3,0,4};
    std::vector<double> in2={1,2,3};
    std::vector<uint>   in3={1,2,3};
    std::vector<double> in4={1,2,3,4};
    sstd::suppress(in1, in2, in3, in4);
    
    ASSERT_TRUE(in1.size()==3);
    ASSERT_TRUE(in2.size()==3);
    ASSERT_TRUE(in3.size()==3);
    ASSERT_TRUE(in4.size()==3);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------






