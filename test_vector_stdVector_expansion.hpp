#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(vector_stdVector_expansion, all){
	printf("== sstd_stdVector_expansion ==\n\n");
	
	// 算術演算子以外にも，<< 演算や，| 演算子によって，結合を定義するとよい．
	
	std::vector<double> lhs={1, 2, 3}, rhs={1, 2, 3};
//	std::vector<int> lhsInt={1, 2, 3}, rhsInt={1, 2, 3};
	std::vector<uint32> lhsInt={1, 2, 3}, rhsInt={1, 2, 3};

	printf("■ plus\n");
	sstd::printn_all(lhs+rhs);
	
	sstd::printn_all(lhs+(int8)10);
	sstd::printn_all(lhs+(uint32)10);
	sstd::printn_all(lhs+(double)10);
	sstd::printn_all(lhsInt+(double)10);
	
	sstd::printn_all((int8)10+lhs);
	// XXX 次はこれを実装する XXX
	sstd::printn_all(lhs+=rhs);
	sstd::printn_all(lhs+=(double)10);
	// ++
	printf("\n");
	
	printf("■ minus\n");
	sstd::printn_all(lhs-=(double)10);
	sstd::printn_all(lhs-=rhs);
	sstd::printn_all(lhs-rhs);
	sstd::printn_all(lhs-(int8)10);
	sstd::printn_all((int8)10-lhs);
	// XXX 次はこれを実装する XXX
	// --
	printf("\n");
	
	printf("■ multiplication\n");
	sstd::printn_all(lhs*rhs);
	sstd::printn_all(lhs*(int8)10);
	sstd::printn_all((int8)10*lhs);
	sstd::printn_all(lhs*=rhs);
	sstd::printn_all(lhs*=(double)10);
	printf("\n");
	
	printf("■ division\n");
	sstd::printn_all(lhs/=(double)10);
	sstd::printn_all(lhs/=rhs);
	sstd::printn_all(lhs/rhs);
	sstd::printn_all(lhs/(int8)10);
	sstd::printn_all((int8)10/lhs);
	printf("\n");
	
	printf("■ modulo\n");
	sstd::printn_all(lhsInt%rhsInt);
	sstd::printn_all(lhsInt%(int8)10);
	sstd::printn_all((int8)10%lhsInt);
	sstd::printn_all(lhsInt%=(int8)10);
	sstd::printn_all(lhsInt%=rhsInt);
	printf("\n");

	printf("■ power\n");
	sstd::printn_all(lhs^rhs);
	sstd::printn_all(lhsInt^rhsInt);
	sstd::printn_all(lhsInt^(uint32)2);
	sstd::printn_all((uint32)2^lhsInt);
	sstd::printn_all(lhs^=2);
	sstd::printn_all(lhs^=rhs);
	printf("\n");
	
	printf("■ inclement and decrement\n");
	sstd::printn_all(lhsInt++);
	sstd::printn_all(++lhsInt);
	sstd::printn_all(lhsInt--);
	sstd::printn_all(--lhsInt);
	printf("\n");
	
	printf("■ operator >>\n");
	sstd::printn_all(lhs<<rhs);
	sstd::printn_all(lhs<<(double)3.14);
	sstd::printn_all((double)3.14<<lhs);
	std::vector<double> buf={123};
	buf <<= lhs;
	buf <<= (double)1.23;
	sstd::printn_all(buf);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

