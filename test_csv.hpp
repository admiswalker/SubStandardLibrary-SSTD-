#pragma once

// vvec2csv(header, vvec_str);
/*

vvec_str = {{""}};
vvec_str >>= header;
vvec_str <<= footer;
vvec2csv(savePath, vvec_str);
//vvec2csv(header, vvec_str);

//---

vvec_str = csvPath2vvec(const char* pReadFile);
header   = vvec_str[0];
vvec_str = vvec_str[1:];

vvec_str = vvec_str[sstd::slice(1,sstd::end())];

vvec_str = vvec_str[sstd::sl(1,sstd::end())];
vvec_str = vvec_str[1,:];

vvec_str = vvec_str[sstd::s(1,sstd::e())];

vvec_str = vvec_str[sstd::s(sstd::b(),sstd::e())];

vvec_str = vvec_str[sstd::slice(sstd::begin(),sstd::end())];
vvec_str = vvec_str[sstd::slice("1:")];

vvec_str = sstd::slice(vvec_str, 0);

*/

// vvec_str = sstd::Tr(vvec_str);
// vvec2csv(savePath, header, vvecTable);

// vvec = csvPath2vvec(header, path);
/*
void dummy(){
	
	
	vvec_str = vvec_str[0];
	vvec_str = vvec_str[1:];
	
	vvec_str = vvec_str[0];
	vvec_str = vvec_str[sstd::slice(1, sstd::end())];
	vvec_str = vvec_str[sstd::slice(sstd::begin(), sstd::end())];
	
	// このあたりは，std::copy() っぽい問題．
	// -> std::copy() の記法は微妙なので，上記を実装してみる．

}
//*/


// sstd::slice() を実装したら，csv 周りを実装する．

void TEST__csv__csvPath2vvec(){
	std::vector<std::vector<std::string>> csv = sstd::csvPath2vvec(R"(./parseCSV.csv)");
	sstd::printn(csv.size());
	
	printf("----\n");
	for(uint p=0; p<csv.size(); p++){
		for(uint q=0; q<csv[p].size(); q++){
			printf("%s,", csv[p][q].c_str());
		}
		printf("\n");
	}
	printf("----\n");
}

//------------------------------------------

TEST(csv, parseCSV){ TEST__csv__csvPath2vvec(); }


