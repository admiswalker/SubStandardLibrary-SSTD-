#include "bmat.hpp"
#include "SwapByTwoIndex.hpp"

/*
bool SwapByTwoIndex::getVal(class sstd::bmat& bMat, uint& p, uint& q){

	// Mat 座標 <- bMat 座標
	uint p_Div8 = p / 8;
	uint q_Div8 = q / 8;

	// bMat8x8 座標 <- bMat 座標
	uint p_Mod8 = p - p_Div8 * 8;	// p % 8;
	uint q_Mod8 = q - q_Div8 * 8;	// q % 8;

	UINT64 mask = 0x8000000000000000;
	mask = mask>>(8*p_Mod8+q_Mod8);

	return ((bMat.bMat8x8(p_Div8, q_Div8)&mask) != (UINT64)0);
}


void SwapByTwoIndex::setVal(class sstd::bmat& bMat, uint& p, uint& q, bool val){

	// Mat 座標 <- bMat 座標
	uint p_Div8 = p / 8;
	uint q_Div8 = q / 8;

	// bMat8x8 座標 <- bMat 座標
	uint p_Mod8 = p - p_Div8 * 8;	// p % 8;
	uint q_Mod8 = q - q_Div8 * 8;	// q % 8;

	UINT64 mask = 0x8000000000000000;
	mask = mask>>(8*p_Mod8+q_Mod8);

	if(val){
		// val != 0, true
		bMat.bMat8x8(p_Div8, q_Div8) |= mask;
	}else{
		// val == 0, false
		mask=~mask;
		bMat.bMat8x8(p_Div8, q_Div8) &= mask;
	}
}


class SwapByTwoIndex OpSwapByTwoIndex(sstd::bmat* pthis, uint p, uint q){

	class SwapByTwoIndex SBTI;
	SBTI.pBMxs = pthis;
	SBTI.SwapRowNum = p;
	SBTI.SwapColNum = q;

	return SBTI;
};
*/
