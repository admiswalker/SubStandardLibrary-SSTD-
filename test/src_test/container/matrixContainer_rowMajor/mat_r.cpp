#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"


/*
void TEST_mat_rowMajor(){
    printf("== sstd_src_MatrixStore_mat_rowMajor ==\n\n");
    
    printf("■ Init sstd::mat_r<type> by \"std::initializer_list<T>\"\n");
    printf("\n");
    
    sstd::mat_r<double> matD_initializer{{1, 2, 3},{4, 5, 6},{7, 8, 9},{10, 11, 12}}; // これは，sstd::mat<T> 側にもテストを書くように．
    sstd::printn(matD_initializer);
    printf("\n");
    
    //===
    
    printf("■ Init sstd::mat_r<type>\n");
    printf("\n");
    
    sstd::mat_r<double> Matd(5, 3);
    printf("RowSize: %d\n", Matd.rows());
    printf("ColSize: %d\n", Matd.cols());
    printf("Length:  %d\n", Matd.size());

    printf("Indication of row major\n");
    uint i=0;
    for(uint p=0; p<Matd.rows(); p++){
        for(uint q=0; q<Matd.cols(); q++){
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
    
    sstd::mat_r<double>* pMatd = new sstd::mat_r<double>(5, 3);
    printf("RowSize: %d\n", pMatd->rows());
    printf("ColSize: %d\n", pMatd->cols());
    printf("Length:  %d\n", pMatd->size());

    printf("Indication of row major\n");
    i=0;
    for(uint p=0; p<pMatd->rows(); p++){
        for(uint q=0; q<pMatd->cols(); q++){
            (*pMatd)(p, q) = i; i++;
        }
    }

    sstd::print(*pMatd);
    printf("\n");
    delete pMatd;
    
    //===

    printf("■ copy\n");printf("\n");
    sstd::mat_r<double> Matd_copy = Matd;
    Matd_copy = Matd; // "sstd::copy(Matd_copy, Matd);" is called.
    sstd::print(Matd_copy); printf("\n");

    //===

    printf("■ copy row\n");printf("\n");
    sstd::mat_r<double> Matd_rowCopy(5, 3); sstd::zeros(Matd_rowCopy);
    Matd_rowCopy(1, ':') = Matd(1, ':');
    sstd::print(Matd_rowCopy); printf("\n");
    
    printf("■ copy col\n");printf("\n");
    sstd::mat_r<double> Matd_colCopy(5, 3); sstd::zeros(Matd_colCopy);
    Matd_colCopy(':', 2) = Matd(':', 2);
    sstd::print(Matd_colCopy); printf("\n");

    //===

    sstd::printn(Matd_colCopy); printf("\n");
    sstd::printn_all(Matd_colCopy); printf("\n");
    
    //===
    
    printf("■ print(type& rhs)\n");printf("\n");
    sstd::mat_r<bool> mat_rB{{true, false, false},{false, true, false},{false, false, true},{true, false, false}};
    sstd::printn(mat_rB);
    
    printf("■ print(type& rhs)\n");printf("\n");
    sstd::mat_r<std::string> mat_rStr{{"a", "ab", "abc"},{"abcd", "abcde", "abcdef"},{"7", "8", "9"},{"10", "11", "12"}};
    sstd::printn(mat_rStr);
    
    //===

    printf("■ Operators for linearAlgebra\n");printf("\n");
    {
        // このあたりは順次テストを書くこと
        
        sstd::mat_r<double> lhs={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
        sstd::mat_r<double> rhs={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
        
        sstd::mat_r<double> lhs23={{1,2,3}, {4, 5, 6}};
        sstd::mat_r<double> rhs32={{1,2}, {3, 4}, {5, 6}};
        
        sstd::mat_r<int> lhsInt={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
        sstd::mat_r<int> rhsInt={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
        
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
//*/
/*
// 実装完了 (処理時間短縮のため，コメントアウト)

TEST(c2py, mat_r_ope_eq_ne){
    // sstd::mat (col-major)
    
    sstd::mat_r<double> matIn(5, 3);
    sstd::mat_r<double> ansT0(5, 3);
    sstd::mat_r<double> ansF0(5, 3);
    sstd::mat_r<double> ansF1(3, 5);
    
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
//*/

EXECUTE_TESTS();
