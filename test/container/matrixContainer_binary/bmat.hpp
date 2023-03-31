#pragma once

/*
void TEST_bmat(){
    // init test
    sstd::bmat bMat4x4(4, 4);
    sstd::eye(bMat4x4);   sstd::printn(bMat4x4);
    sstd::ones(bMat4x4);  sstd::printn(bMat4x4);
    sstd::zeros(bMat4x4); sstd::printn(bMat4x4);
    sstd::print(bMat4x4);     // for print debug
    sstd::print_all(bMat4x4); // for bmat debug // Internaly, the bit matrix is processed as a set of 8x8 matrices.
    //

    sstd::bmat bonded8x8 = sstd::zeros(4, 4) << sstd::eye(4, 4) &&
                           sstd::ones (4, 4) << sstd::eye(4, 4);
    sstd::printn(bonded8x8);

    sstd::bmat bonded8x8_2 = sstd::zeros(5, 5) << sstd::eye(3, 3) &&
                             sstd::ones (3, 5) << sstd::eye(3, 3);
    sstd::printn(bonded8x8_2);
    
    sstd::bmat bonded16x16_horzcat2_2 = sstd::ones(16, 16) << sstd::eye(16, 16);
    sstd::printn(bonded16x16_horzcat2_2);
    
    sstd::bmat bonded16x16_vertcat2_2 = sstd::ones(16, 16) &&
                                        sstd::eye (16, 16);
    sstd::printn(bonded16x16_vertcat2_2);
    
    sstd::bmat bonded16x16 = sstd::zeros(16, 16) << sstd::eye(16, 16) &&
                             sstd::ones (16, 16) << sstd::eye(16, 16);
    sstd::printn(bonded16x16);
    
    //
    sstd::bmat bMat8x9 = sstd::eye(8, 9);
    sstd::printn(bMat8x9);
    sstd::print_all(bMat8x9); // for debug // Internaly, the bit matrix is processed as a set of 8x8 matrices.

    sstd::printn(bMat8x9.rows());
    sstd::printn(bMat8x9.cols());
    printf("\n");

    // access to elements
    sstd::bmat M = sstd::zeros(4, 4);
    M(0, 1) = 1;
    M(1, 2) = 1;
    M(2, 3) = 1;
    M(3, 4) = 1;
    sstd::printn(M);
    sstd::printn(M*M); // multi

    // tranpose
    sstd:: bmat M_tr = M; // copy
    sstd::Tr_myself(M_tr);
    sstd::printn(M_tr);
    sstd::printn(sstd::Tr(M));

    // pow test
    sstd::bmat L1 = sstd::LxShiftMat(16, 1);
    sstd::printn(L1);
    sstd::bmat L7 = L1^((uint64)7); // この計算は後で確認して！！！
    sstd::printn(L7);

    uint N = 32;
    sstd::bmat I(N, N); sstd::eye(I);
    sstd::bmat L15 = sstd::LxShiftMat(N, 15);
    sstd::bmat R17 = sstd::RxShiftMat(N, 17);
    sstd::bmat L13 = sstd::LxShiftMat(N, 13);
    sstd::bmat T = (I + L15)*(I + R17)*(I + L13);
    sstd::printn(T);
    sstd::bmat Tp = T^(4294967296-1); // XORSHIFT
    sstd::printn(Tp);
    
    printf("Tp==I: "); if(Tp==I){ printf("true\n");  }else{ printf("false\n"); }
    printf("Tp!=I: "); if(Tp!=I){ printf("true\n");  }else{ printf("false\n"); }

    printf("I(0, 0): "); if(I(0, 0)){printf("true\n");}else{printf("false\n");}
    printf("I(1, 0): "); if(I(1, 0)){printf("true\n");}else{printf("false\n");}
    printf("I(0, 1): "); if(I(0, 1)){printf("true\n");}else{printf("false\n");}
    printf("I(1, 1): "); if(I(1, 1)){printf("true\n");}else{printf("false\n");}

    I = sstd::eye(4, 4);
    sstd::printn(I);
    I(0, 0) = false;
    I(1, 1) = false;
    I(0, 1) = 1;
    I(0, 2) = 1000;    // "I(0, 2) = 1000;" に同じ．

//    I(1, 0) = I(2, 0) = I(2, 2);
    I(1, 0) = I(2, 0) = I(2, 2) = true;

    sstd::printn(I);

    sstd::printn(I);
    I[0] = false;
    I[1] = true;

    I[2] = I[3] = I[15];
    I[4] = I[5] = true;

    I[6] = I[7] = I(2, 2);
    I(2, 2) = I[0];

    sstd::printn(I);
}//*/

