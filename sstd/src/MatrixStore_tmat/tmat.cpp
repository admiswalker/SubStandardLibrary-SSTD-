#include "./tmat.hpp"


void tmat::print(class sstd::typeMatrix<char>& Mat){
	for(uint p=0; p<Mat.rows(); p++){
		uint q=0;
		printf("% d", Mat(p, q));
		for(q++; q<Mat.cols(); q++){
			printf("\t % d", Mat(p, q));
		}
		printf("\n");
	}
}
void tmat::print(class sstd::typeMatrix<uchar>& Mat){
	for(uint p=0; p<Mat.rows(); p++){
		uint q=0;
		printf("% d", Mat(p, q));
		for(q++; q<Mat.cols(); q++){
			printf("\t % d", Mat(p, q));
		}
		printf("\n");
	}
}
void tmat::print(class sstd::typeMatrix<int>& Mat){
	for(uint p=0; p<Mat.rows(); p++){
		uint q=0;
		printf("% d", Mat(p, q));
		for(q++; q<Mat.cols(); q++){
			printf("\t % d", Mat(p, q));
		}
		printf("\n");
	}
}
void tmat::print(class sstd::typeMatrix<uint>& Mat){
	for(uint p=0; p<Mat.rows(); p++){
		uint q=0;
		printf(" %u", Mat(p, q));
		for(q++; q<Mat.cols(); q++){
			printf("\t  %u", Mat(p, q));
		}
		printf("\n");
	}
}
void tmat::print(class sstd::typeMatrix<float>& Mat){
	for(uint p=0; p<Mat.rows(); p++){
		uint q=0;
		printf("% f", Mat(p, q));
		for(q++; q<Mat.cols(); q++){
			printf("\t % f", Mat(p, q));
		}
		printf("\n");
	}
}
void tmat::print(class sstd::typeMatrix<double>& Mat){
	for(uint p=0; p<Mat.rows(); p++){
		uint q=0;
		printf("% lf", Mat(p, q));	// マイナスのためにスペース1つ分空ける．(符号なし整数についても，位置を合わせるためスペースを空けておく)
		for(q++; q<Mat.cols(); q++){
			printf("\t % lf", Mat(p, q));	// マイナスのためにスペース1つ分空ける．(符号なし整数についても，位置を合わせるためスペースを空けておく)
		}
		printf("\n");
	}
}
