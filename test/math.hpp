#pragma once

#define TEST_vec_sort_sort_de(Type)                                    \
    std::vector<Type> buf = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4};    \
    std::vector<Type> sortDe = sstd::sort_de(buf);                    \
    sstd::printn(sortDe);                                            \
    sstd::printn(sstd::sort(sortDe));                                \
    printf("\n");
#define TEST_vec_sort_sort_de_u(Type)                                \
    std::vector<Type> buf = {0, 1, 2, 3, 4};                        \
    std::vector<Type> sortDe = sstd::sort_de(buf);                    \
    sstd::printn(sortDe);                                            \
    sstd::printn(sstd::sort(sortDe));                                \
    printf("\n");
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
    printf("sum: %f\n", sstd::sum(buf_f));
    printf("sum_abs: %f\n", sstd::sum_abs(buf_f));
    printf("ave: %f\n", sstd::ave(buf_f));
    printf("ave in the first 2 elements: %f\n", sstd::ave(buf_f, 2));
    printf("med: %f\n", sstd::med(buf_f));
    printf("var: %f\n", sstd::var(buf_f));
    printf("var_p: %f\n", sstd::var_p(buf_f));
    printf("stdev: %f\n", sstd::stdev(buf_f));
    printf("stdev_p: %f\n", sstd::stdev_p(buf_f));
    printf("\n");
    std::vector<float> sortDe_f = sstd::sort_de(buf_f);
    sstd::printn(sortDe_f);
    sstd::printn(sstd::sort(sortDe_f));
    printf("\n");
    
    std::vector<double> buf_d = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4};
    sstd::printn(buf_d);
    printf("sum: %f\n", sstd::sum(buf_d));
    printf("sum_abs: %f\n", sstd::sum_abs(buf_d));
    printf("ave: %f\n", sstd::ave(buf_d));
    printf("ave in the first 2 elements: %f\n", sstd::ave(buf_d, 2));
    printf("med: %f\n", sstd::med(buf_d));
    printf("var: %f\n", sstd::var(buf_d));
    printf("var_p: %f\n", sstd::var_p(buf_d));
    printf("stdev: %f\n", sstd::stdev(buf_d));
    printf("stdev_p: %f\n", sstd::stdev_p(buf_d));
    printf("\n");
    std::vector<double> sortDe_d = sstd::sort_de(buf_d);
    sstd::printn(sortDe_d);
    sstd::printn(sstd::sort(sortDe_d));
    printf("\n");

    /* test: Kahan summation algorithm 01 */
    std::vector<float> buf_f2 = {100000.0f, 0.0125f, 0.0125f, 0.0125f, 0.0125f, 0.0125f, 0.0125f, 0.0125f, 0.0125f}; // float の有効桁数 = 24/1og2(10) ≒ 7.224 ≒ 7
    printf("sum: %lf\n", sstd::sum(buf_f2));
    std::vector<double> buf_d2 = {100000000000000.0, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125}; // double の有効桁数 = 24/1og2(10) ≒ 15.955 ≒ 15
    printf("sum: %lf\n", sstd::sum(buf_d2));
    printf("\n");
    
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

    //-------------------------------------------------------------------------------------------------------------------------------------------
    
    { TEST_vec_sort_sort_de  ( int8 ); }
    { TEST_vec_sort_sort_de  ( int16); }
    { TEST_vec_sort_sort_de  ( int32); }
    { TEST_vec_sort_sort_de  ( int64); }
    { TEST_vec_sort_sort_de_u(uint8 ); }
    { TEST_vec_sort_sort_de_u(uint16); }
    { TEST_vec_sort_sort_de_u(uint32); }
    { TEST_vec_sort_sort_de_u(uint64); }
    
    //-------------------------------------------------------------------------------------------------------------------------------------------
}

TEST(math, theOthers){
    TEST_math();
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
}/*
// Under implementation

TEST(math, argmax_mat_c){
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
TEST(math, argmax_mat_r){
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
//*/
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






