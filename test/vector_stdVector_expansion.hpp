#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(vector_stdVector_expansion, plus){
    std::vector<double> lhs={1, 2, 3}, rhs={1, 2, 3};
    std::vector<uint32> lhsInt={1, 2, 3}, rhsInt={1, 2, 3};
    
    {
        std::vector<double> ans={2, 4, 6};
        ASSERT_TRUE( (lhs+rhs) == ans );
    }
    {
        std::vector<double> ans={11, 12, 13};
        ASSERT_TRUE( (lhs+(  int8)10) == ans );
        ASSERT_TRUE( (lhs+(uint32)10) == ans );
        ASSERT_TRUE( (lhs+(double)10) == ans );
        ASSERT_TRUE( ((  int8)10+lhs) == ans );
    }
    {
        std::vector<uint32> ans={11, 12, 13};
        ASSERT_TRUE( (lhsInt+(double)10) == ans );
    }
    
    {
        std::vector<double> lhs_buf=lhs;
        std::vector<double> ans={2, 4, 6};
        lhs_buf+=rhs;
        ASSERT_TRUE( lhs_buf == ans );
    }
    {
        std::vector<double> lhs_buf=lhs;
        std::vector<double> ans={11, 12, 13};
        lhs_buf += (double)10;
        ASSERT_TRUE( lhs_buf == ans );
    }
    {
        // self overwriting vector.
        std::vector<double> lhs_buf=lhs;
        std::vector<double> ans={2, 3, 4};
        lhs_buf += lhs_buf[0];
        ASSERT_TRUE( lhs_buf == ans );
    }
}
TEST(vector_stdVector_expansion, minus){
    std::vector<double> lhs={1, 2, 3}, rhs={1, 2, 3};
    std::vector<uint32> lhsInt={1, 2, 3}, rhsInt={1, 2, 3};
    
    {
        std::vector<double> lhs_buf=lhs;
        std::vector<double> ans={-9, -8, -7};
        lhs_buf-=(double)10;
        ASSERT_TRUE( lhs_buf == ans );
    }
    {
        std::vector<double> lhs_buf=lhs;
        std::vector<double> ans={0, 0, 0};
        lhs_buf-=rhs;
        ASSERT_TRUE( lhs_buf == ans );
    }
    {
        std::vector<double> ans={0, 0, 0};
        ASSERT_TRUE( lhs-rhs == ans );
    }
    {
        std::vector<double> ans={-9, -8, -7};
        ASSERT_TRUE( (lhs-(int8)10) == ans );
    }
    {
        std::vector<double> ans={9, 8, 7};
        ASSERT_TRUE( ((int8)10-lhs) == ans );
    }
}
TEST(vector_stdVector_expansion, multiplication){
    std::vector<double> lhs={1, 2, 3}, rhs={1, 2, 3};
    {
        std::vector<double> ans={1, 4, 9};
        ASSERT_TRUE( (lhs*rhs) == ans );
    }
    {
        std::vector<double> ans={10, 20, 30};
        ASSERT_TRUE( (lhs*(int8)10) == ans );
        ASSERT_TRUE( ((int8)10*lhs) == ans );
    }
    {
        std::vector<double> ans={1, 4, 9};
        std::vector<double> lhs_buf=lhs;
        lhs_buf*=rhs;
        ASSERT_TRUE( lhs_buf == ans );
    }
    {
        std::vector<double> ans={10, 20, 30};
        std::vector<double> lhs_buf=lhs;
        lhs_buf*=(double)10;
        ASSERT_TRUE( lhs_buf == ans );
    }
}
TEST(vector_stdVector_expansion, division){
    std::vector<double> lhs={1, 2, 3}, rhs={1, 2, 3};
    {
        std::vector<double> lhs_buf=lhs;
        std::vector<double> ans={0.1, 0.2, 0.3};
        ASSERT_TRUE( (lhs_buf/=(double)10) == ans );
    }
    {
        std::vector<double> lhs_buf=lhs;
        std::vector<double> ans={1, 1, 1};
        ASSERT_TRUE( (lhs_buf/=rhs) == ans );
    }
    {
        std::vector<double> ans={1, 1, 1};
        ASSERT_TRUE( (lhs/rhs) == ans );
    }
    {
        std::vector<double> ans={0.1, 0.2, 0.3};
        ASSERT_TRUE( (lhs/(int8)10) == ans );
    }
    {
        std::vector<double> ans={10./1., 10./2., 10./3.};
        ASSERT_TRUE( ((int8)10/lhs) == ans );
    }
}
TEST(vector_stdVector_expansion, modulo){
    std::vector<uint32> lhsInt={1, 2, 3}, rhsInt={1, 2, 3};
    
    {
        std::vector<uint32> ans={0, 0, 0};
        ASSERT_TRUE( (lhsInt%rhsInt) == ans );
    }
    {
        std::vector<uint32> ans={1, 2, 3};
        ASSERT_TRUE( (lhsInt%(int8)10) == ans );
    }
    {
        std::vector<uint32> ans={0, 0, 1};
        ASSERT_TRUE( ((int8)10%lhsInt) == ans );
    }
    {
        std::vector<uint32> ans={1, 2, 3};
        std::vector<uint32> lhsInt_buf=lhsInt;
        ASSERT_TRUE( (lhsInt_buf%=(int8)10) == ans );
    }
    {
        std::vector<uint32> ans={0, 0, 0};
        std::vector<uint32> lhsInt_buf=lhsInt;
        ASSERT_TRUE( (lhsInt%=rhsInt) == ans );
    }
}
TEST(vector_stdVector_expansion, power){
    std::vector<double> lhs={1, 2, 3}, rhs={1, 2, 3};
    std::vector<uint32> lhsInt={1, 2, 3}, rhsInt={1, 2, 3};
    
    {
        std::vector<double> ans={1, 4, 27};
        ASSERT_TRUE( (lhs^rhs) == ans );
    }
    {
        std::vector<uint32> ans={1, 4, 27};
        ASSERT_TRUE( (lhsInt^rhsInt) == ans );
    }
    {
        std::vector<uint32> ans={1, 4, 9};
        ASSERT_TRUE( (lhsInt^(uint32)2) == ans );
    }
    {
        std::vector<uint32> ans={2, 4, 8};
        ASSERT_TRUE( ((uint32)2^lhsInt) == ans );
    }
    {
        std::vector<double> lhs_buf=lhs;
        std::vector<double> ans={1, 4, 9};
        ASSERT_TRUE( (lhs_buf^=2) == ans );
    }
    {
        std::vector<double> lhs_buf=lhs;
        std::vector<double> ans={1, 4, 27};
        ASSERT_TRUE( (lhs_buf^=rhs) == ans );
    }
}
TEST(vector_stdVector_expansion, inclement){
    std::vector<uint32> lhsInt={1, 2, 3}, rhsInt={1, 2, 3};
    {
        std::vector<uint32> lhsInt_buf=lhsInt;
        std::vector<uint32> ans_ret=lhsInt;
        std::vector<uint32> ans={2, 3, 4};
        
        std::vector<uint32> ret=lhsInt_buf++;
        ASSERT_TRUE( ret        == ans_ret );
        ASSERT_TRUE( lhsInt_buf == ans     );
    }
    {
        std::vector<uint32> lhsInt_buf=lhsInt;
        std::vector<uint32> ans={2, 3, 4};
        
        std::vector<uint32> ret=++lhsInt_buf;
        ASSERT_TRUE( ret        == ans );
        ASSERT_TRUE( lhsInt_buf == ans );
    }
}
TEST(vector_stdVector_expansion, decrement){
    std::vector<uint32> lhsInt={1, 2, 3}, rhsInt={1, 2, 3};
    {
        std::vector<uint32> lhsInt_buf=lhsInt;
        std::vector<uint32> ans_ret=lhsInt;
        std::vector<uint32> ans={0, 1, 2};
        
        std::vector<uint32> ret=lhsInt_buf--;
        ASSERT_TRUE( ret        == ans_ret );
        ASSERT_TRUE( lhsInt_buf == ans     );
    }
    {
        std::vector<uint32> lhsInt_buf=lhsInt;
        std::vector<uint32> ans={0, 1, 2};
        
        std::vector<uint32> ret=--lhsInt_buf;
        ASSERT_TRUE( ret        == ans );
        ASSERT_TRUE( lhsInt_buf == ans );
    }
}
TEST(vector_stdVector_expansion, leftShift_as_merge){
    std::vector<double> lhs={1, 2, 3}, rhs={1, 2, 3};
    std::vector<uint32> lhsInt={1, 2, 3}, rhsInt={1, 2, 3};
    
    {
        std::vector<double> ans={1, 2, 3, 1, 2, 3};
        ASSERT_TRUE( (lhs<<rhs) == ans );
    }
    {
        std::vector<double> ans={1, 2, 3, 3.14};
        ASSERT_TRUE( (lhs<<(double)3.14) == ans );
    }
    {
        std::vector<double> ans={3.14, 1, 2, 3};
        ASSERT_TRUE( ((double)3.14<<lhs) == ans );
    }
    {
        std::vector<double> ans={123, 1, 2, 3, 1.23};
        
        std::vector<double> buf={123};
        buf <<= lhs;
        buf <<= (double)1.23;
        
        ASSERT_TRUE( buf == ans );
    }
}
TEST(vector_stdVector_expansion, RightShift_as_merge){
    std::vector<double> lhs={1, 2, 3}, rhs={4, 5, 6};
    std::vector<uint32> lhsInt={1, 2, 3}, rhsInt={1, 2, 3};
    
    {
        std::vector<double> ans={4, 5, 6, 1, 2, 3};
        ASSERT_TRUE( (lhs>>rhs) == ans );
    }
    {
        std::vector<double> ans={3.14, 1, 2, 3};
        ASSERT_TRUE( (lhs>>(double)3.14) == ans );
    }
    {
        std::vector<double> ans={1, 2, 3, 3.14};
        ASSERT_TRUE( ((double)3.14>>lhs) == ans );
    }
    {
        std::vector<double> ans={1.23, 1, 2, 3, 123};
        
        std::vector<double> buf={123};
        buf >>= lhs;
        buf >>= (double)1.23;
        
        ASSERT_TRUE( buf == ans );
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

