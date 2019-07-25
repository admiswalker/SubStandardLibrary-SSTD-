#pragma once
#include <vector>
#include <limits.h> // UINT_MAX

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
	template <typename T> std::vector<std::vector<T>> Tr(const std::vector<std::vector<T>>&  rhs);
//	template <typename T> std::vector<std::vector<T>> Tr(      std::vector<std::vector<T>>&& rhs);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
/*
#define Tr_base()								\
	abc;										\
	def;

template <typename T> Tr(const std::vector<std::vector<T>>&  rhs){ std::vector<std::vector<T>> lhs; Tr_base(); return lhs; }
template <typename T> Tr(      std::vector<std::vector<T>>&& rhs){                                  Tr_base(); return lhs; }
//*/

template <typename T>
std::vector<std::vector<T>> sstd::Tr(const std::vector<std::vector<T>>& rhs){
	// return while zero.
	if(rhs.size()==0){ return std::vector<std::vector<T>>(); }
	
	// Calculating a lhs size.
	uint colsMax = 0; // column size max
	std::vector<uint> vecRows, vecCols;
	uint i=rhs.size()-1;
	if(rhs[i].size()>colsMax){ colsMax=rhs[i].size(); }
	vecRows.push_back( rhs[i].size() );
	vecCols.push_back(      i+1      );
	i--;
	for(; i!=UINT_MAX; i--){
		if(rhs[i].size()<vecRows[vecRows.size()-1]){ continue; }
		
		if(rhs[i].size()>colsMax){ colsMax=rhs[i].size(); }
		vecRows.push_back( rhs[i].size() );
		vecCols.push_back(      i+1      );
	}
	
	// Allocating the lhs.
	std::vector<std::vector<T>> lhs(colsMax);
	for(uint i=0, r=0; r<vecRows.size(); r++){
		for(; i<vecRows[r]; i++){
			uint cols = vecCols[r];
			lhs[i].resize( cols );
		}
	}
	
	// copy or move value.
	for(uint r=0; r<rhs.size(); r++){
		for(uint c=0; c<rhs[r].size(); c++){
			lhs[c][r] = rhs[r][c];
		}
	}
	
	return lhs;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

// Example of transposing, an irreversible conversion.
//
// vvec_r<T>          vvec_r<T>        vvec_r<T>
//
// ----       =Tr()=> |||||||| =Tr()=> --------
// --                 ||||||||         --------
// --------           ||||||||         --------
// ---                |||              ---


