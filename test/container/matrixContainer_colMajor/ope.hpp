#pragma once

/*
#Include "./MatrixStore/Core/MatrixStore.hpp"


int main(){

    mxs::MatrixStore<double> MatA(3, 3); mxs::zeros(MatA);
    mxs::MatrixStore<double> MatB(3, 3); mxs::zeros(MatB);

    for(uint q=0; q<MatA.cols; q++){
        for(uint p=0; p<MatA.rows; p++){
            MatA(p, q) = (MatA.cols)*p + q;
        }
    }

    printm(MatA); printf("\n");

    MatB(':', 0) = MatA(':', 1);
//    MatB(':', 1) = MatA(':', 2);
//    MatB(':', 2) = MatA(':', 0);

    printm(MatB); printf("\n");

//    MatB(0, ':') = MatA(0, ':');
    MatB(1, ':') = MatB(0, ':') = MatA(0, ':');
//    MatB(1, ':') = MatA(1, ':');
//    MatB(2, ':') = MatA(2, ':');

    //MatA = MatA.array() * MatB.array();
    // MatA = MatA.a() * MatB.a();
    // MatA = MatA.arr() * MatB;
    // MatA = MatA * MatB.arr();

    // MatA = MatA .* MatB;
    // MatA = MatA ,* MatB;
    // MatA = MatA <dot> MatB;
    // MatA = MatA ("dot")* MatB;
    // MatA = MatA *(dot) MatB;
    // MatA.cols;
    // MatB.rows;

    printm(MatB);
}
*/
