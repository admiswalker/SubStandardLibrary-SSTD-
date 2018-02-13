#include "./mat_r.hpp"

// このあたりの関数は，const cast 不要で渡せるようにつくり直した後に順次修正する．

// print 関数の定義．
#define sstd_mat_r_print(mat, rows, cols, OPTION1, OPTION2)\
	for(uint p=0; p<rows; p++){\
		uint q=0;\
		printf(OPTION1, mat(p, q));\
		for(q++; q<cols; q++){\
			printf(OPTION2, mat(p, q));\
		}\
		printf("\n");\
	}


// "% d", "% lf" のように，マイナスのためにスペース1つ分空ける．(符号なし整数についても，位置を合わせるためスペースを空けておく)
void sstd::print(const class sstd::mat_r<  bool>& mat){
	for(uint p=0; p<mat.rows(); p++){
		for(uint q=0; q<mat.cols(); q++){ printf("%c ", (mat(p, q) ? 'T' : 'F')); } printf("\n");
	}
}
void sstd::print(const class sstd::mat_r<       char>& mat){ sstd_mat_r_print(mat, mat.rows(), mat.cols(), "%c", "\t %c"  ); }
//void sstd::print(const class sstd::mat_r<      uchar>& mat){ sstd_mat_r_print(mat, mat.rows(), mat.cols(), "%u", "\t %u"); } // same as uint8
void sstd::print(const class sstd::mat_r<       int8>& mat){ sstd_mat_r_print(mat, mat.rows(), mat.cols(), "% d",  "\t % d" ); }
void sstd::print(const class sstd::mat_r<      int16>& mat){ sstd_mat_r_print(mat, mat.rows(), mat.cols(), "% d",  "\t % d" ); }
void sstd::print(const class sstd::mat_r<      int32>& mat){ sstd_mat_r_print(mat, mat.rows(), mat.cols(), "% d",  "\t % d" ); }
void sstd::print(const class sstd::mat_r<      int64>& mat){ sstd_mat_r_print(mat, mat.rows(), mat.cols(), "% ld", "\t % ld"); }
void sstd::print(const class sstd::mat_r<      uint8>& mat){ sstd_mat_r_print(mat, mat.rows(), mat.cols(), "%u",   "\t %u"  ); } // "%u" はエラーが出るので空けない．
void sstd::print(const class sstd::mat_r<     uint16>& mat){ sstd_mat_r_print(mat, mat.rows(), mat.cols(), "%u",   "\t %u"  ); } // "%u" はエラーが出るので空けない．
void sstd::print(const class sstd::mat_r<     uint32>& mat){ sstd_mat_r_print(mat, mat.rows(), mat.cols(), "%u",   "\t %u"  ); } // "%u" はエラーが出るので空けない．
void sstd::print(const class sstd::mat_r<     uint64>& mat){ sstd_mat_r_print(mat, mat.rows(), mat.cols(), "%lu",  "\t %lu" ); } // "%u" はエラーが出るので空けない．
void sstd::print(const class sstd::mat_r<      float>& mat){ sstd_mat_r_print(mat, mat.rows(), mat.cols(), "% f",  "\t % f" ); }
void sstd::print(const class sstd::mat_r<     double>& mat){ sstd_mat_r_print(mat, mat.rows(), mat.cols(), "% lf", "\t % lf"); }
void sstd::print(const class sstd::mat_r<std::string>& mat){
	for(uint p=0; p<mat.rows(); p++){
		uint q=0;
		printf("%s", mat(p, q).c_str());
		for(q++; q<mat.cols(); q++){ printf("\t %s", mat(p, q).c_str()); }
		printf("\n");
	}
}

// for sstd::printn(); and sstd::printn_all();.
void sstd::for_printn(const class sstd::mat_r<       bool>& mat){ printf(" = \n");sstd::print(mat); }
void sstd::for_printn(const class sstd::mat_r<       char>& mat){ printf(" = \n");sstd::print(mat); }
//void sstd::for_printn(const class sstd::mat_r<      uchar>& mat){ printf(" = \n");sstd::print(mat); } // same as uint8
void sstd::for_printn(const class sstd::mat_r<       int8>& mat){ printf(" = \n");sstd::print(mat); }
void sstd::for_printn(const class sstd::mat_r<      int16>& mat){ printf(" = \n");sstd::print(mat); }
void sstd::for_printn(const class sstd::mat_r<      int32>& mat){ printf(" = \n");sstd::print(mat); }
void sstd::for_printn(const class sstd::mat_r<      int64>& mat){ printf(" = \n");sstd::print(mat); }
void sstd::for_printn(const class sstd::mat_r<      uint8>& mat){ printf(" = \n");sstd::print(mat); }
void sstd::for_printn(const class sstd::mat_r<     uint16>& mat){ printf(" = \n");sstd::print(mat); }
void sstd::for_printn(const class sstd::mat_r<     uint32>& mat){ printf(" = \n");sstd::print(mat); }
void sstd::for_printn(const class sstd::mat_r<     uint64>& mat){ printf(" = \n");sstd::print(mat); }
void sstd::for_printn(const class sstd::mat_r<      float>& mat){ printf(" = \n");sstd::print(mat); }
void sstd::for_printn(const class sstd::mat_r<     double>& mat){ printf(" = \n");sstd::print(mat); }
void sstd::for_printn(const class sstd::mat_r<std::string>& mat){ printf(" = \n");sstd::print(mat); }

