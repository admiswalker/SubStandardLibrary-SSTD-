#pragma once


//	vvec_c2csv(header, vvec_str); // vvec col-major to csv.

//	vvec_str = vvec_Tr(vvec_str);
//	vvec_r2csv(header, vvecTable, ); // vvec row-major to csv.

// csvPath2vvec_c(vvec_c, header, path);
// csvPath2vvec_r(vvec_r, header, path);


void TEST__csv__csvPath2vvec_r(){
	std::vector<std::vector<std::string>> csv = sstd::csvPath2vvec_r(R"(./parseCSV.csv)");
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

TEST(csv, parseCSV){ TEST__csv__csvPath2vvec_r(); }


