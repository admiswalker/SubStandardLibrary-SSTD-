#include "bmat.hpp"

//--------------------------------------------------------------------------------------------------------

void bmat::copy(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs){

	lhs.rows = rhs.rows;
	lhs.cols = rhs.cols;

	if(lhs.bMat8x8.rows()*lhs.bMat8x8.cols() != rhs.bMat8x8.rows()*rhs.bMat8x8.cols()){
		free(lhs.bMat8x8.pMat()); lhs.bMat8x8.pMat_RW()=0;
		if(lhs.rows!=0 && lhs.cols!=0){ lhs.bMat8x8.pMat_RW() = (uint64*)malloc(sizeof(uint64) * rhs.bMat8x8.rows() * rhs.bMat8x8.cols()); }
	}

	tmat::copy(lhs.bMat8x8, rhs.bMat8x8);	// lhs.bMat8x8 = rhs.bMat8x8; // 本来は，これでオーバーロードされるはずだが，GCC 5.4.0 だとバグるので，明示的に書く．(他の場合でもバグりかねないのが，問題)
}
void bmat::move(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs){

	lhs.rows = rhs.rows; rhs.rows = 0;
	lhs.cols = rhs.cols; rhs.cols = 0;

	tmat::move(lhs.bMat8x8, rhs.bMat8x8);	// lhs.bMat8x8 = std::move(rhs.bMat8x8); // これだとバグる．
}

//--------------------------------------------------------------------------------------------------------

void printBit(uint BitRowNum, uint end, uint64& buf){

	uint64 mask = (uint64)1<<(sizeof(uint64)*(8-BitRowNum)-1);

	for(uint i=0; i<end; i++, mask=mask>>1 ){
		if(mask&buf){ putchar('1');putchar(' ');
		}   else    { putchar('0');putchar(' '); }
	}
}
void bmat::printBitMatrix(class sstd::bitMatrix bMat){

	uint row_m1 = bMat.bMat8x8.rows() - 1;
	uint col_m1 = bMat.bMat8x8.cols() - 1;
	uint RowEdge = bMat.rows - row_m1*8;
	uint ColEdge = bMat.cols - col_m1*8;

	for(uint p=0; p<bMat.bMat8x8.rows(); p++){

		uint row_end;
		if(p!=row_m1){ row_end = 8;
		}    else    { row_end = RowEdge; }

		for(uint BitRowNum=0; BitRowNum<row_end; BitRowNum++){
			for(uint q=0; q<bMat.bMat8x8.cols(); q++){

				uint col_end;
				if(q!=col_m1){ col_end = 8;
				}    else    { col_end = ColEdge; }

				printBit(BitRowNum, col_end, bMat.bMat8x8(p, q)); putchar(' ');putchar(' ');
			}
			printf("\n");
		}
		printf("\n");
	}
}
void bmat::printBitMatrix_all(class sstd::bitMatrix bMat){

	for(uint p=0; p<bMat.bMat8x8.rows(); p++){
		for(uint BitRowNum=0; BitRowNum<8; BitRowNum++){
			for(uint q=0; q<bMat.bMat8x8.cols(); q++){
				printBit(BitRowNum, 8, bMat.bMat8x8(p, q));	putchar(' ');putchar(' ');
			}
			printf("\n");
		}
		printf("\n");
	}
}

//--------------------------------------------------------------------------------------------------------

uint64 inline eyeBit8x8(){
	// I = Eye8x8
	//   = 10000000
	//     01000000
	//     00100000
	//     00010000
	//     00001000
	//     00000100
	//     00000010
	//     00000001
	//   = 0b1000000001000000001000000001000000001000000001000000001000000001
	//   = 0x8040201008040201
	return 0x8040201008040201;
}
uint64 inline eyeBitNxN(uint N){
	uint64 EyeTableNxN[] = { 0x0000000000000000		// Eye0x0
							,0x8000000000000000		// Eye1x1
							,0x8040000000000000		// Eye2x2
							,0x8040200000000000		// Eye3x3
							,0x8040201000000000		// Eye4x4
							,0x8040201008000000		// Eye5x5
							,0x8040201008040000		// Eye6x6
							,0x8040201008040200		// Eye7x7
							,0x8040201008040201 };	// Eye8x8
	return EyeTableNxN[N];
}
void bmat::eye(class sstd::bitMatrix& bMat){

	uint row_m1 = bMat.bMat8x8.rows() - 1;
	uint col_m1 = bMat.bMat8x8.cols() - 1;
	uint RowEdge = bMat.rows - row_m1*8;	// bMat.rows % 8
	uint ColEdge = bMat.cols - col_m1*8;	// bMat.cols % 8
	uint buf; if(bMat.rows<=bMat.cols){ buf = RowEdge; }else{ buf = ColEdge; }

	for(uint q=0; q<bMat.bMat8x8.cols(); q++){
		for(uint p=0; p<bMat.bMat8x8.rows(); p++){
			if(            p!=q            ){ bMat.bMat8x8(p, q) = (uint64)0;
			}else if(p==row_m1 || q==col_m1){ bMat.bMat8x8(p, q) = eyeBitNxN(buf);
			}else                           { bMat.bMat8x8(p, q) = eyeBit8x8();
			}
		}
	}
}
class sstd::bitMatrix bmat::eye(uint row, uint col){

	class sstd::bitMatrix result(row, col);
	bmat::eye(result);
	return result;
}
class sstd::bitMatrix bmat::eye(uint size){
	return bmat::eye(size, size);
}

//--------------------------------------------------------------------------------------------------------

uint64 inline onesBitRow8xM(uint M){
	uint64 OnesTableRow8xM[] = { 0x0000000000000000		// Ones8x0
								,0x8080808080808080		// Ones8x1
								,0xC0C0C0C0C0C0C0C0		// Ones8x2
								,0xE0E0E0E0E0E0E0E0		// Ones8x3
								,0xF0F0F0F0F0F0F0F0		// Ones8x4
								,0xF8F8F8F8F8F8F8F8		// Ones8x5
								,0xFCFCFCFCFCFCFCFC		// Ones8x6
								,0xFEFEFEFEFEFEFEFE		// Ones8x7
								,0xFFFFFFFFFFFFFFFF };	// Ones8x8
	return OnesTableRow8xM[M];
}
uint64 inline onesBitNxCol8(uint N){
	uint64 OnesTableNxCol8[] = { 0x0000000000000000		// Ones0x8
								,0xFF00000000000000		// Ones1x8
								,0xFFFF000000000000		// Ones2x8
								,0xFFFFFF0000000000		// Ones3x8
								,0xFFFFFFFF00000000		// Ones4x8
								,0xFFFFFFFFFF000000		// Ones5x8
								,0xFFFFFFFFFFFF0000		// Ones6x8
								,0xFFFFFFFFFFFFFF00		// Ones7x8
								,0xFFFFFFFFFFFFFFFF };	// Ones8x8
	return OnesTableNxCol8[N];
}
uint64 inline onesBitNxM(uint N, uint M){
	return (onesBitNxCol8(N) & onesBitRow8xM(M));
}
void bmat::ones(class sstd::bitMatrix& bMat){

	uint row_m1  = bMat.bMat8x8.rows() - 1;
	uint col_m1  = bMat.bMat8x8.cols() - 1;
	uint RowEdge = bMat.rows - row_m1*8;	// bMat.rows % 8
	uint ColEdge = bMat.cols - col_m1*8;	// bMat.cols % 8

	for(uint q=0; q<bMat.bMat8x8.cols(); q++){
		for(uint p=0; p<bMat.bMat8x8.rows(); p++){
			if(p==row_m1 && q==col_m1){ bMat.bMat8x8(p, q) = onesBitNxM   (RowEdge, ColEdge);
			}else if(   p==row_m1    ){ bMat.bMat8x8(p, q) = onesBitNxCol8(RowEdge);
			}else if(   q==col_m1    ){ bMat.bMat8x8(p, q) = onesBitRow8xM(ColEdge);
			}else                     { bMat.bMat8x8(p, q) = (uint64)0xFFFFFFFFFFFFFFFF;
			}
		}
	}
}
class sstd::bitMatrix bmat::ones(uint row, uint col){

	class sstd::bitMatrix result(row, col);
	bmat::ones(result);
	return result;
}
class sstd::bitMatrix bmat::ones(uint size){
	return bmat::ones(size, size);
}

//--------------------------------------------------------------------------------------------------------

void bmat::zeros(class sstd::bitMatrix& bMat){

	for(uint q=0; q<bMat.bMat8x8.cols(); q++){
		for(uint p=0; p<bMat.bMat8x8.rows(); p++){
			bMat.bMat8x8(p, q) = (uint64)0;
		}
	}
}
class sstd::bitMatrix bmat::zeros(uint row, uint col){

	class sstd::bitMatrix result(row, col);
	bmat::zeros(result);
	return result;
}
class sstd::bitMatrix bmat::zeros(uint size){
	return bmat::zeros(size, size);
}

//--------------------------------------------------------------------------------------------------------

uint64 inline LxBit8x8(uint x){
	uint64 LxTable8x8[] = { 0x8040201008040201		// L0
						   ,0x4020100804020100		// L1
						   ,0x2010080402010000		// L2
						   ,0x1008040201000000		// L3
						   ,0x0804020100000000		// L4
						   ,0x0402010000000000		// L5
						   ,0x0201000000000000		// L6
						   ,0x0100000000000000		// L7
						   ,0x0000000000000000 };	// L8
	return LxTable8x8[x];
}
uint64 inline RxBit8x8(uint x){
	uint64 RxTable8x8[] = { 0x8040201008040201		// R0
						   ,0x0080402010080402		// R1
						   ,0x0000804020100804		// R2
						   ,0x0000008040201008		// R3
						   ,0x0000000080402010		// R4
						   ,0x0000000000804020		// R5
						   ,0x0000000000008040		// R6
						   ,0x0000000000000080		// R7
						   ,0x0000000000000000 };	// R8
	return RxTable8x8[x];
}
class sstd::bitMatrix bmat::LxShiftMat(uint size, uint xShift){

	class sstd::bitMatrix buf(size, size);
	uint xShiftDiv8      = xShift / 8;
	uint xShiftMod8      = xShift - xShiftDiv8 * 8;	// xShift%8;
	uint xShiftDiv8Plus1 =          xShiftDiv8 + 1;
	uint xShiftMod8_Inv  =      8 - xShiftMod8;

	uint col_m1 = buf.bMat8x8.cols() - 1;
	uint ColEdge = buf.cols - col_m1*8;				// buf.cols % 8

	for(uint q=0; q<buf.bMat8x8.cols(); q++){
		for(uint p=0; p<buf.bMat8x8.rows(); p++){
			if((p+xShiftDiv8) == q){
				if(col_m1 != q){ buf.bMat8x8(p, q) = LxBit8x8(xShiftMod8);
				}     else     { buf.bMat8x8(p, q) = LxBit8x8(xShiftMod8) & onesBitRow8xM(ColEdge); }
			}else if((p+xShiftDiv8Plus1) == q){
				if(col_m1 != q){ buf.bMat8x8(p, q) = RxBit8x8(xShiftMod8_Inv);
				}     else     { buf.bMat8x8(p, q) = RxBit8x8(xShiftMod8_Inv) & onesBitRow8xM(ColEdge); }
			}else{
				buf.bMat8x8(p, q) = (uint64)0;
			}
		}
	}

	return buf;
}
class sstd::bitMatrix bmat::RxShiftMat(uint size, uint xShift){

	class sstd::bitMatrix buf(size, size);
	uint xShiftDiv8      = xShift / 8;
	uint xShiftMod8      = xShift - xShiftDiv8 * 8;	// xShift % 8;
	uint xShiftDiv8Plus1 =          xShiftDiv8 + 1;
	uint xShiftMod8_Inv  =      8 - xShiftMod8;

	uint row_m1  = buf.bMat8x8.rows() - 1;
	uint RowEdge = buf.rows - row_m1*8;				// buf.cols % 8

	for(uint q=0; q<buf.bMat8x8.cols(); q++){
		for(uint p=0; p<buf.bMat8x8.rows(); p++){
			if(p == (q+xShiftDiv8)){
				if(row_m1 != p){ buf.bMat8x8(p, q) = RxBit8x8(xShiftMod8);
				}     else     { buf.bMat8x8(p, q) = RxBit8x8(xShiftMod8) & onesBitNxCol8(RowEdge); }
			}else if(p == (q+xShiftDiv8Plus1)){
				if(row_m1 != p){ buf.bMat8x8(p, q) = LxBit8x8(xShiftMod8_Inv);
				}     else     { buf.bMat8x8(p, q) = LxBit8x8(xShiftMod8_Inv) & onesBitNxCol8(RowEdge); }
			}else{
				buf.bMat8x8(p, q) = (uint64)0;
			}
		}
	}

	return buf;
}

//--------------------------------------------------------------------------------------------------------

void TrBit8x8(uint64& rhs){
	uint64 buf;

	// 8x8Bit行列中の，右上4x4と左下4x4を交換
	// 
	// 4*8-4 = 4*(8-1) = 28
	// 0x00000000F0F0F0F0 = 0b00000000
	//                        00000000
	//                        00000000
	//                        00000000
	//                        11110000
	//                        11110000
	//                        11110000
	//                        11110000
	buf  = ((rhs>>28)^rhs) & 0x00000000F0F0F0F0;
	buf |= buf<<28;
	rhs ^= buf;
	
	// 8x8Bit行列中の4個の4x4中の，右上2x2と左下2x2を交換
	// 
	// 2*8-2 = 2*(8-1) = 14
	// 0x0000CCCC0000CCCC = 0b00000000
	//                        00000000
	//                        11001100
	//                        11001100
	//                        00000000
	//                        00000000
	//                        11001100
	//                        11001100
	buf  = ((rhs>>14)^rhs) & 0x0000CCCC0000CCCC;
	buf |= buf<<14;
	rhs ^= buf;
	
	// 8x8Bit行列中の16個の2x2中の，右上1x1と左下1x1を交換
	// 
	// 1*8-1 = 1*(8-1) = 7
	// 0x00AA00AA00AA00AA = 0b00000000
	//                        10101010
	//                        00000000
	//                        10101010
	//                        00000000
	//                        10101010
	//                        00000000
	//                        10101010
	buf  = ((rhs>>7)^rhs) & 0x00AA00AA00AA00AA;
	buf |= buf<<7;
	rhs ^= buf;
}
class sstd::bitMatrix bmat::Tr(class sstd::bitMatrix& rhs){

	class sstd::bitMatrix result(rhs.cols, rhs.rows);

	for(uint q=0; q<rhs.bMat8x8.cols(); q++){
		for(uint p=q; p<rhs.bMat8x8.rows(); p++){
			if(p==q){ result.bMat8x8(p, q) = rhs.bMat8x8(p, q); TrBit8x8(result.bMat8x8(p, q)); }
			result.bMat8x8(p, q) = rhs.bMat8x8(q, p); TrBit8x8(result.bMat8x8(p, q));
			result.bMat8x8(q, p) = rhs.bMat8x8(p, q); TrBit8x8(result.bMat8x8(q, p));
		}
	}

	return result;
}
void bmat::Tr_myself(class sstd::bitMatrix& rhs){

	if(rhs.bMat8x8.rows()==rhs.bMat8x8.cols()){
		for(uint q=0; q<rhs.bMat8x8.cols(); q++){
			for(uint p=q; p<rhs.bMat8x8.rows(); p++){
				if(p==q){ TrBit8x8(rhs.bMat8x8(p, q)); }
			
				std::swap(rhs.bMat8x8(p, q), rhs.bMat8x8(q, p));
				TrBit8x8(rhs.bMat8x8(p, q));
				TrBit8x8(rhs.bMat8x8(q, p));
			}
		}
		std::swap(rhs.rows, rhs.cols);
	}else if(rhs.bMat8x8.rows()==1 || rhs.bMat8x8.cols()==1){
		for(uint q=0; q<rhs.bMat8x8.cols(); q++){
			for(uint p=0; p<rhs.bMat8x8.rows(); p++){
				TrBit8x8(rhs.bMat8x8(p, q));
			}
		}
		std::swap(rhs.rows, rhs.cols);
		std::swap(rhs.bMat8x8.rows_RW(), rhs.bMat8x8.cols_RW());
	}else{
		sstd::bitMatrix result = bmat::Tr(rhs);
		bmat::move(rhs, result);
	}
}

//--------------------------------------------------------------------------------------------------------

class sstd::bitMatrix bmat::add(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs){

	class sstd::bitMatrix result(lhs.rows, lhs.cols);

	for(uint q=0; q<rhs.bMat8x8.cols(); q++){
		for(uint p=0; p<rhs.bMat8x8.rows(); p++){
			result.bMat8x8(p, q) = lhs.bMat8x8(p, q) | rhs.bMat8x8(p, q);
		}
	}
	return result;
}
void bmat::add_myself(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs){

	for(uint q=0; q<rhs.bMat8x8.cols(); q++){
		for(uint p=0; p<rhs.bMat8x8.rows(); p++){
			lhs.bMat8x8(p, q) |= rhs.bMat8x8(p, q);
		}
	}
}


uint64 mulBit8x8(uint64 lhs, uint64 rhs){

	const uint64 col_FF = (uint64)0x0000000000000FF;
	const uint64 row_FF = (uint64)0x101010101010101;
	uint64 result = (uint64)0;

	for(; lhs&&rhs; lhs=lhs>>1, rhs=rhs>>8){
		result ^= (((lhs & row_FF) * col_FF) & ((rhs & col_FF) * row_FF));
	}
	return result;
}
class sstd::bitMatrix bmat::mul(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs){

	class sstd::bitMatrix result(lhs.rows, rhs.cols);
	bmat::zeros(result);

	for(uint q=0; q<rhs.bMat8x8.cols(); q++){
		for(uint i=0; i<rhs.bMat8x8.rows(); i++){
			for(uint p=0; p<lhs.bMat8x8.rows(); p++){
				result.bMat8x8(p, q) ^= mulBit8x8(lhs.bMat8x8(p, i), rhs.bMat8x8(i, q));
			}
		}
	}
	return result;
}
void bmat::mul_myself(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs){

	sstd::bitMatrix result = bmat::mul(lhs, rhs); // 最適化の余地なし．
	lhs = result;
}

/*
class sstd::bitMatrix bmat::pow(class sstd::bitMatrix base, uint64 exponent){

	sstd::bitMatrix result(base.rows, base.cols);
	bmat::eye(result);

	for(; exponent>(uint64)0; exponent>>=1){
		if(exponent & 1){
			result = bmat::mul(result, base);
		}
		base = bmat::mul(base, base);
	}

	return result;
}
// 下記のように最適化．
*/
void bmat_power_calculation(class sstd::bitMatrix& base, uint64& exponent){

	for(; exponent>(uint64)0; exponent>>=1){
		if(exponent & 1){
			if(exponent==(uint64)1){ return; }
			break;
		}
		base = bmat::mul(base, base);
	}
	sstd::bitMatrix buf = base;
	buf = bmat::mul(buf, buf);
	exponent>>=1;

	for(;;exponent>>=1){
		if(exponent & 1){
			base = bmat::mul(base, buf);
			if(exponent==(uint64)1){ return; }
		}
		buf = bmat::mul(buf, buf);
	}
}
class sstd::bitMatrix bmat::pow(class sstd::bitMatrix base, uint64 exponent){

	if(exponent==(uint64)0){ return eye(base.rows, base.cols); }
	bmat_power_calculation(base, exponent);
	return base;
}
void bmat::pow_myself(class sstd::bitMatrix& base, uint64 exponent){

	if(exponent==(uint64)0){ base=eye(base.rows, base.cols); return; }
	bmat_power_calculation(base, exponent);
}


class sstd::bitMatrix bmat::and_(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs){

	class sstd::bitMatrix result(rhs.rows, rhs.cols);

	for(uint q=0; q<rhs.bMat8x8.cols(); q++){
		for(uint p=0; p<rhs.bMat8x8.rows(); p++){
			result.bMat8x8(p, q) = lhs.bMat8x8(p, q) & rhs.bMat8x8(p, q);
		}
	}
	return result;
}
void bmat::and_myself(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs){

	for(uint q=0; q<rhs.bMat8x8.cols(); q++){
		for(uint p=0; p<rhs.bMat8x8.rows(); p++){
			lhs.bMat8x8(p, q) &= rhs.bMat8x8(p, q);
		}
	}
}


class sstd::bitMatrix bmat::or_(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs){

	class sstd::bitMatrix result(rhs.rows, rhs.cols);

	for(uint q=0; q<rhs.bMat8x8.cols(); q++){
		for(uint p=0; p<rhs.bMat8x8.rows(); p++){
			result.bMat8x8(p, q) = lhs.bMat8x8(p, q) | rhs.bMat8x8(p, q);
		}
	}
	return result;
}
void bmat::or_myself(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs){

	for(uint q=0; q<rhs.bMat8x8.cols(); q++){
		for(uint p=0; p<rhs.bMat8x8.rows(); p++){
			lhs.bMat8x8(p, q) |= rhs.bMat8x8(p, q);
		}
	}
}


class sstd::bitMatrix bmat::not_(class sstd::bitMatrix& rhs){

	class sstd::bitMatrix result(rhs.rows, rhs.cols);

	for(uint q=0; q<rhs.bMat8x8.cols(); q++){
		for(uint p=0; p<rhs.bMat8x8.rows(); p++){
			result.bMat8x8(p, q) = ~rhs.bMat8x8(p, q);
		}
	}
	return result;
}


class sstd::bitMatrix bmat::xor_(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs){ return bmat::add(lhs, rhs); }

//--------------------------------------------------------------------------------------------------------

bool bmat::eq(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs){

	bool result=true;

	for(uint q=0; q<rhs.bMat8x8.cols(); q++){
		for(uint p=0; p<rhs.bMat8x8.rows(); p++){
			if(lhs.bMat8x8(p, q) != rhs.bMat8x8(p, q)){ result=false; return result; }
		}
	}

	return result;
}
bool bmat::ne(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs){
	return !bmat::eq(lhs, rhs);
}

//--------------------------------------------------------------------------------------------------------

uint64 inline onesBitRow8xM_Inv(uint M){
	uint64 OnesTableRow8xM_Inv[] = { 0x0000000000000000		// Ones8x0
									,0x0101010101010101		// Ones8x1
									,0x0303030303030303		// Ones8x2
									,0x0707070707070707		// Ones8x3
									,0x0F0F0F0F0F0F0F0F		// Ones8x4
									,0x1F1F1F1F1F1F1F1F		// Ones8x5
									,0x3F3F3F3F3F3F3F3F		// Ones8x6
									,0x7F7F7F7F7F7F7F7F		// Ones8x7
									,0xFFFFFFFFFFFFFFFF };	// Ones8x8
	return OnesTableRow8xM_Inv[M];
}
uint64 RShift8x8(uint64& rhs, uint& shiftMod8, uint& shiftMod8_Inv){
	return (rhs>>shiftMod8) & onesBitRow8xM_Inv(shiftMod8_Inv);
}
uint64 LShift8x8(uint64& rhs, uint& shiftMod8, uint& shiftMod8_Inv){
	return (rhs<<shiftMod8) & onesBitRow8xM(shiftMod8_Inv);
}
class sstd::bitMatrix REShift_arg(class sstd::bitMatrix& rhs,
	uint& shift, uint shiftDiv8, uint& shiftMod8, uint shiftDiv8Plus1, uint& shiftMod8_Inv){

	class sstd::bitMatrix result(rhs.rows, rhs.cols+shift); bmat::zeros(result);

	if(shiftMod8==0){
		for(uint q=0; q<rhs.bMat8x8.cols(); q++){
			for(uint p=0; p<rhs.bMat8x8.rows(); p++){
				result.bMat8x8(p, q+shiftDiv8) = rhs.bMat8x8(p, q);
			}
		}
	}else{
		uint q = 0;
		for(uint p=0; p<rhs.bMat8x8.rows(); p++){
			result.bMat8x8(p, q+shiftDiv8) = RShift8x8(rhs.bMat8x8(p, q), shiftMod8, shiftMod8_Inv);
		}
		for(q=1; q<rhs.bMat8x8.cols(); q++){
			for(uint p=0; p<rhs.bMat8x8.rows(); p++){
				result.bMat8x8(p, q+shiftDiv8) = LShift8x8(rhs.bMat8x8(p, q-1), shiftMod8_Inv, shiftMod8)
			                                   | RShift8x8(rhs.bMat8x8(p, q  ), shiftMod8, shiftMod8_Inv);
			}
		}
		if(rhs.cols<8 && (rhs.cols+shift)>8){
			q = rhs.bMat8x8.cols()-1;
			for(uint p=0; p<rhs.bMat8x8.rows(); p++){
				result.bMat8x8(p, q+shiftDiv8Plus1) = LShift8x8(rhs.bMat8x8(p, q), shiftMod8_Inv, shiftMod8);
			}
		}
	}
	return result;
}
class sstd::bitMatrix bmat::REShift(class sstd::bitMatrix& rhs, uint shift){

	uint shiftDiv8      = shift / 8;
	uint shiftMod8      = shift - shiftDiv8 * 8;	// shift % 8;
	uint shiftDiv8Plus1 =         shiftDiv8 + 1;
	uint shiftMod8_Inv  =     8 - shiftMod8;

	return REShift_arg(rhs, shift, shiftDiv8, shiftMod8, shiftDiv8Plus1, shiftMod8_Inv);
}

//--------------------------------------------------------------------------------------------------------

uint64 inline onesBitNxCol8_Inv(uint N){
	uint64 OnesTableNxCol8_Inv[] = { 0x0000000000000000		// Ones8x0
									,0x00000000000000FF		// Ones8x1
									,0x000000000000FFFF		// Ones8x2
									,0x0000000000FFFFFF		// Ones8x3
									,0x00000000FFFFFFFF		// Ones8x4
									,0x000000FFFFFFFFFF		// Ones8x5
									,0x0000FFFFFFFFFFFF		// Ones8x6
									,0x00FFFFFFFFFFFFFF		// Ones8x7
									,0xFFFFFFFFFFFFFFFF };	// Ones8x8
	return OnesTableNxCol8_Inv[N];
}
uint64 DShift8x8(uint64& rhs, uint& shiftMod8, uint& shiftMod8_Inv){
	return (rhs>>(8*shiftMod8)) & onesBitNxCol8_Inv(shiftMod8_Inv);
}
uint64 UShift8x8(uint64& rhs, uint& shiftMod8, uint& shiftMod8_Inv){
	return (rhs<<(8*shiftMod8)) & onesBitNxCol8(shiftMod8);
}
class sstd::bitMatrix DEShift_arg(class sstd::bitMatrix& rhs,
	uint& shift, uint shiftDiv8, uint& shiftMod8, uint shiftDiv8Plus1, uint& shiftMod8_Inv){

	class sstd::bitMatrix result(rhs.rows+shift, rhs.cols); bmat::zeros(result);

	if(shiftMod8==0){
		for(uint q=0; q<rhs.bMat8x8.cols(); q++){
			for(uint p=0; p<rhs.bMat8x8.rows(); p++){
				result.bMat8x8(p+shiftDiv8, q) = rhs.bMat8x8(p, q);
			}
		}
	}else{
		for(uint q=0; q<rhs.bMat8x8.cols(); q++){
			
			uint p = 0;
			result.bMat8x8(p+shiftDiv8, q) = DShift8x8(rhs.bMat8x8(p, q), shiftMod8, shiftMod8_Inv);

			for(p=1; p<rhs.bMat8x8.rows(); p++){
				result.bMat8x8(p+shiftDiv8, q) = UShift8x8(rhs.bMat8x8(p-1, q), shiftMod8_Inv, shiftMod8)
			                                   | DShift8x8(rhs.bMat8x8(p  , q), shiftMod8, shiftMod8_Inv);
			}
			if(rhs.rows<8 && (rhs.rows+shift)>8){
				p = rhs.bMat8x8.rows()-1;
				result.bMat8x8(p+shiftDiv8Plus1, q) = UShift8x8(rhs.bMat8x8(p, q), shiftMod8_Inv, shiftMod8);
			}
		}
	}
	return result;
}
class sstd::bitMatrix bmat::DEShift(class sstd::bitMatrix& rhs, uint shift){

	uint shiftDiv8      = shift / 8;
	uint shiftMod8      = shift - shiftDiv8 * 8;	// shift % 8;
	uint shiftDiv8Plus1 =         shiftDiv8 + 1;
	uint shiftMod8_Inv  =     8 - shiftMod8;

	return DEShift_arg(rhs, shift, shiftDiv8, shiftMod8, shiftDiv8Plus1, shiftMod8_Inv);
}

//--------------------------------------------------------------------------------------------------------

class sstd::bitMatrix bmat::horzcat2(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs){

	uint row_size; if(lhs.rows>rhs.rows){ row_size=lhs.rows; }else{ row_size = rhs.rows; }
	class sstd::bitMatrix result(row_size, lhs.cols + rhs.cols); bmat::zeros(result);

	for(uint q=0; q<lhs.bMat8x8.cols(); q++){
		for(uint p=0; p<lhs.bMat8x8.rows(); p++){
			result.bMat8x8(p, q) = lhs.bMat8x8(p, q);
		}
	}

	uint shift          = lhs.cols;
	uint shiftDiv8      = shift / 8;
	uint shiftMod8      = shift - shiftDiv8 * 8;	// shift % 8;
	uint shiftMod8_Inv  =     8 - shiftMod8;
	class sstd::bitMatrix rhs_buf = REShift_arg(rhs, shiftMod8, 0, shiftMod8, 1, shiftMod8_Inv);
	for(uint q=0; q<rhs_buf.bMat8x8.cols(); q++){
		for(uint p=0; p<rhs_buf.bMat8x8.rows(); p++){
			result.bMat8x8(p, q+lhs.bMat8x8.cols()-1) |= rhs_buf.bMat8x8(p, q);
		}
	}
	return result;
}
class sstd::bitMatrix bmat::vertcat2(class sstd::bitMatrix& us, class sstd::bitMatrix& ds){

	uint col_size; if(us.cols>ds.cols){ col_size=us.cols; }else{ col_size=ds.cols; }
	class sstd::bitMatrix result(us.rows + ds.rows, col_size); bmat::zeros(result);

	for(uint q=0; q<us.bMat8x8.cols(); q++){
		for(uint p=0; p<us.bMat8x8.rows(); p++){
			result.bMat8x8(p, q) = us.bMat8x8(p, q);
		}
	}

	uint shift          = us.rows;
	uint shiftDiv8      = shift / 8;
	uint shiftMod8      = shift - shiftDiv8 * 8;	// shift % 8;
	uint shiftMod8_Inv  =     8 - shiftMod8;
	class sstd::bitMatrix ds_buf = DEShift_arg(ds, shiftMod8, 0, shiftMod8, 1, shiftMod8_Inv);
	for(uint q=0; q<ds_buf.bMat8x8.cols(); q++){
		for(uint p=0; p<ds_buf.bMat8x8.rows(); p++){
			result.bMat8x8(p+us.bMat8x8.rows()-1, q) |= ds_buf.bMat8x8(p, q);
		}
	}
	return result;
}
/*
// 上記のように，一般化
// 下記は8x8に特化した実装
class sstd::bitMatrix bmat::horzcat2(class sstd::bitMatrix& lhs, class sstd::bitMatrix& rhs){

	uint row_size, bMat8x8_row_size; if(lhs.rows>rhs.rows){ row_size=lhs.rows; bMat8x8_row_size=lhs.bMat8x8.rows; }else{ row_size = rhs.rows; bMat8x8_row_size=rhs.bMat8x8.rows; }
	class sstd::bitMatrix result(row_size, lhs.cols + rhs.cols); bmat::zeros(result);

	for(uint q=0; q<lhs.bMat8x8.cols(); q++){
		for(uint p=0; p<lhs.bMat8x8.rows(); p++){
			result.bMat8x8(p, q) = lhs.bMat8x8(p, q);
		}
	}
	for(uint q=0; q<rhs.bMat8x8.cols(); q++){
		for(uint p=0; p<rhs.bMat8x8.rows(); p++){
			result.bMat8x8(p, lhs.bMat8x8.cols+q) = rhs.bMat8x8(p, q);
		}
	}
	return result;
}
class sstd::bitMatrix bmat::vertcat2(class sstd::bitMatrix& us, class sstd::bitMatrix& ds){	// us , ds    // upside, downside.

	uint col_size, bMat8x8_col_size; if(us.cols>ds.cols){ col_size=us.cols; bMat8x8_col_size=us.bMat8x8.cols; }else{ col_size=ds.cols; bMat8x8_col_size=ds.bMat8x8.cols; }
	class sstd::bitMatrix result(us.rows + ds.rows, col_size);

	for(uint q=0; q<us.bMat8x8.cols(); q++){
		for(uint p=0; p<us.bMat8x8.rows(); p++){
			result.bMat8x8(p, q) = us.bMat8x8(p, q);
		}
	}
	for(uint q=0; q<ds.bMat8x8.cols(); q++){
		for(uint p=0; p<ds.bMat8x8.rows(); p++){
			result.bMat8x8(us.bMat8x8.rows+p, q) = ds.bMat8x8(p, q);
		}
	}
	return result;
}
*/
//--------------------------------------------------------------------------------------------------------
