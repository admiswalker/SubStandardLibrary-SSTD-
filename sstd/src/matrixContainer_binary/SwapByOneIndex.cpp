#include "bmat.hpp"
#include "SwapByOneIndex.hpp"


bool SwapByOneIndex::getVal(class sstd::bmat& bMat, uint& p){

	// bMat 座標 <- 配列座標
	uint q_DivBMR = p/bMat.rows();
	uint p_ModBMR = p - q_DivBMR * bMat.rows();	// p % bMat.rows;

	// Mat 座標 <- bMat 座標
	uint p_Div8 = p_ModBMR / 8;
	uint q_Div8 = q_DivBMR / 8;

	// bMat8x8 座標 <- bMat 座標
	uint p_Mod8 = p_ModBMR - p_Div8 * 8;	// bMat.rows % 8;
	uint q_Mod8 = q_DivBMR - q_Div8 * 8;	// bMat.cols % 8;

	uint64 mask = 0x8000000000000000;
	mask = mask>>(8*p_Mod8+q_Mod8);

	return ((bMat.bMat8x8_RW()(p_Div8, q_Div8)&mask) != (uint64)0);
}


void SwapByOneIndex::setVal(class sstd::bmat& bMat, uint& p, bool& val){

	// bMat 座標 <- 配列座標
	uint q_DivBMR = p/bMat.rows();
	uint p_ModBMR = p - q_DivBMR * bMat.rows();	// p % bMat.rows;

	// Mat 座標 <- bMat 座標
	uint p_Div8 = p_ModBMR / 8;
	uint q_Div8 = q_DivBMR / 8;

	// bMat8x8 座標 <- bMat 座標
	uint p_Mod8 = p_ModBMR - p_Div8 * 8;	// bMat.rows % 8;
	uint q_Mod8 = q_DivBMR - q_Div8 * 8;	// bMat.cols % 8;

	uint64 mask = 0x8000000000000000;
	mask = mask>>(8*p_Mod8+q_Mod8);

	if(val){
		// val != 0, true
		bMat.bMat8x8_RW()(p_Div8, q_Div8) |= mask;
	}else{
		// val == 0, false
		mask=~mask;
		bMat.bMat8x8_RW()(p_Div8, q_Div8) &= mask;
	}
}


class SwapByOneIndex OpSwapByOneIndex(sstd::bmat* pthis, uint p){

	class SwapByOneIndex SBOI;
	SBOI.pBMxs = pthis;
	SBOI.SwapNum = p;

	return SBOI;
};
