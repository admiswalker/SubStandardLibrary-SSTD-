#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"


/*
void TEST_mat_colMajor(){
    printf("== sstd_src_MatrixStore_mat ==\n\n"); // col-major
    
    printf("■ Init sstd::eye()\n");
    { sstd::mat_c<double> buf(3, 3); sstd::eye(buf); sstd::printn(buf); printf("\n"); }
    { sstd::mat_c<double> buf(3, 2); sstd::eye(buf); sstd::printn(buf); printf("\n"); }
    { sstd::mat_c<double> buf(2, 3); sstd::eye(buf); sstd::printn(buf); printf("\n"); }
        
    printf("■ Init sstd::ones()\n");
    { sstd::mat_c<double> buf(3, 3); sstd::ones(buf); sstd::printn(buf); printf("\n"); }
    { sstd::mat_c<double> buf(3, 2); sstd::ones(buf); sstd::printn(buf); printf("\n"); }
    { sstd::mat_c<double> buf(2, 3); sstd::ones(buf); sstd::printn(buf); printf("\n"); }
        
    printf("■ Init sstd::zeros()\n");
    { sstd::mat_c<double> buf(3, 3); sstd::zeros(buf); sstd::printn(buf); printf("\n"); }
    { sstd::mat_c<double> buf(3, 2); sstd::zeros(buf); sstd::printn(buf); printf("\n"); }
    { sstd::mat_c<double> buf(2, 3); sstd::zeros(buf); sstd::printn(buf); printf("\n"); }

    printf("■ Init sstd::mat_c<type> by \"std::initializer_list<T>\"\n");
    printf("\n");
    
    sstd::mat_c<double> matD_initializer{{1, 2, 3},{4, 5, 6},{7, 8, 9},{10, 11, 12}}; // これは，sstd::mat_c<T> 側にもテストを書くように．
    sstd::printn(matD_initializer);
    printf("\n");
    
    //===
    
    printf("■ Init sstd::mat_c<type>\n");
    printf("\n");
    
    sstd::mat_c<double> Matd(5, 3);
    printf("RowSize: %d\n", Matd.rows());
    printf("ColSize: %d\n", Matd.cols());
    printf("Length:  %d\n", Matd.size());

    printf("Indication of column major\n");
    uint i=0;
    for(uint q=0; q<Matd.cols(); q++){
        for(uint p=0; p<Matd.rows(); p++){
            Matd(p, q) = i; i++;
        }
    }
    sstd::print(Matd);
    printf("\n");
    
    //===
    
    i=0;
    for(uint q=0; q<Matd.size(); q++){ Matd[i] = i; i++; }
    sstd::print(Matd);
    printf("\n");

    //===
    
    sstd::mat_c<double>* pMatd = new sstd::mat_c<double>(5, 3);
    printf("RowSize: %d\n", pMatd->rows());
    printf("ColSize: %d\n", pMatd->cols());
    printf("Length:  %d\n", pMatd->size());

    printf("Indication of column major\n");
    i=0;
    for(uint q=0; q<pMatd->cols(); q++){
        for(uint p=0; p<pMatd->rows(); p++){
            (*pMatd)(p, q) = i; i++;
        }
    }

    sstd::print(*pMatd);
    printf("\n");
    delete pMatd;
    
    //===

    printf("■ copy\n");printf("\n");
    sstd::mat_c<double> Matd_copy = Matd;
    Matd_copy = Matd; // "sstd::copy(Matd_copy, Matd);" is called.
    sstd::print(Matd_copy); printf("\n");

    //===

    printf("■ copy row\n");printf("\n");
    sstd::mat_c<double> Matd_rowCopy(5, 3); sstd::zeros(Matd_rowCopy);
    Matd_rowCopy(1, ':') = Matd(1, ':');
    sstd::print(Matd_rowCopy); printf("\n");
    
    printf("■ copy col\n");printf("\n");
    sstd::mat_c<double> Matd_colCopy(5, 3); sstd::zeros(Matd_colCopy);
    Matd_colCopy(':', 2) = Matd(':', 2);
    sstd::print(Matd_colCopy); printf("\n");

    //===
    sstd::printn(Matd_colCopy); printf("\n");
    sstd::printn_all(Matd_colCopy); printf("\n");

    //===
    
    printf("■ print(type& rhs)\n");printf("\n");
    sstd::mat_c<bool> matB{{true, false, false},{false, true, false},{false, false, true},{true, false, false}};
    sstd::printn(matB);

    printf("■ print(type& rhs)\n");printf("\n");
    sstd::mat_c<std::string> matStr{{"a", "ab", "abc"},{"abcd", "abcde", "abcdef"},{"7", "8", "9"},{"10", "11", "12"}};
    sstd::printn(matStr);
    
    //===

    printf("■ Operators for linearAlgebra\n");printf("\n");
    {
        // このあたりは順次テストを書くこと
        
        sstd::mat_c<double> lhs={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
        sstd::mat_c<double> rhs={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
        
        sstd::mat_c<double> lhs23={{1,2,3}, {4, 5, 6}};
        sstd::mat_c<double> rhs32={{1,2}, {3, 4}, {5, 6}};
        
        sstd::mat_c<int> lhsInt={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
        sstd::mat_c<int> rhsInt={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
        
        printf("  □ plus\n");printf("\n");
        sstd::printn(lhs+rhs); printf("\n");
        sstd::printn(lhs+(uint)1); printf("\n");
        sstd::printn((uint)1+lhs); printf("\n");
        
        sstd::printn(lhs+(int)-1); printf("\n");
        sstd::printn((int)-1+lhs); printf("\n");
        
        printf("  □ minus\n");printf("\n");
        sstd::printn(lhs-rhs); printf("\n");
        
        sstd::printn(lhs-(int)1); printf("\n");
        sstd::printn((int)1-lhs); printf("\n");
        
        printf("  □ multiplication\n");printf("\n");
        sstd::printn(lhs*rhs); printf("\n");
        sstd::printn(lhs23*rhs32); printf("\n");
        sstd::printn(lhs23*(uint)2); printf("\n");
        sstd::printn((uint)2*lhs23); printf("\n");
        
        sstd::printn(lhs()*rhs()); printf("\n");
        sstd::printn(lhs  *rhs()); printf("\n");
        sstd::printn(lhs()*rhs  ); printf("\n");
        sstd::printn(lhs.vec()*rhs.vec()); printf("\n");
        
        printf("  □ division\n");printf("\n");
        sstd::printn(lhs()/rhs()); printf("\n");
        sstd::printn(lhs  /rhs()); printf("\n");
        sstd::printn(lhs()/rhs  ); printf("\n");

        printf("  □ power\n");printf("\n");
        sstd::printn(lhs^(uint32)0); printf("\n");
        sstd::printn(lhs^(uint32)1); printf("\n");
        sstd::printn(lhs^(uint32)2); printf("\n");
        sstd::printn(lhs*lhs); printf("\n");
        sstd::printn(lhs^(uint32)3); printf("\n");
        sstd::printn(lhs*lhs*lhs); printf("\n");

        
        sstd::printn(lhs^(int32)3); printf("\n");
        
        sstd::printn(lhs()^rhs()); printf("\n");
        sstd::printn(lhs  ^rhs()); printf("\n");
        sstd::printn(lhs()^rhs  ); printf("\n");
        
        // 未実装
        //sstd::printn(lhs^(int32)-1); printf("\n");
        //sstd::printn(lhs^(float)-1); printf("\n");
        //sstd::printn(lhs^(double)-1); printf("\n");
        
        printf("  □ modulo\n");printf("\n");
        sstd::printn(lhsInt % 2); printf("\n");
        
        sstd::printn(lhsInt()%rhsInt()); printf("\n");
        sstd::printn(lhsInt  %rhsInt()); printf("\n");
        sstd::printn(lhsInt()%rhsInt  ); printf("\n");
    }
}
*/
/*
TEST(c2py, mat_ope_eq_ne){
    // sstd::mat_c (col-major)
    
    sstd::mat_c<double> matIn(5, 3);
    sstd::mat_c<double> ansT0(5, 3);
    sstd::mat_c<double> ansF0(5, 3);
    sstd::mat_c<double> ansF1(3, 5);
    
    for(uint i=0; i<matIn.size(); i++){
        matIn[i]=i;
        ansT0[i]=i;
        ansF0[i]=i;
        ansF1[i]=i;
    }
    ansF0[0]=(double)999;
    
    ASSERT_TRUE (matIn==ansT0);
    ASSERT_FALSE(matIn==ansF0);
    ASSERT_FALSE(matIn==ansF1);
    
    ASSERT_FALSE(matIn!=ansT0);
    ASSERT_TRUE (matIn!=ansF0);
    ASSERT_TRUE (matIn!=ansF1);
}
*/


EXECUTE_TESTS();
