#pragma once

// vvec2csv(header, vvec_str);
/*

vvec_str = {{""}};
vvec_str >>= header;
vvec_str <<= footer;
vvec2csv(savePath, vvec_str);
//vvec2csv(header, vvec_str);

*/

// vvec_str = sstd::Tr(vvec_str);
// vvec2csv(savePath, header, vvecTable);

// vvec = csvPath2vvec(header, path);


// sstd::slice() を実装したら，csv 周りを実装する．

TEST(csv, csvPath2vvec){
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
TEST(csv, vvec2csvPath){
	sstd::mkdir("./tmp");
	std::vector<std::vector<std::string>> csv = sstd::csvPath2vvec(R"(./parseCSV.csv)");
	
	const char* path = R"(./tmp/test_vvec2csvPath.csv)";
	bool result = sstd::vvec2csvPath(path, csv); ASSERT_TRUE( result );
	std::vector<std::vector<std::string>> csv_re = sstd::csvPath2vvec(path);
	
	ASSERT_TRUE(csv == csv_re);
	sstd::rm("./tmp");
}

