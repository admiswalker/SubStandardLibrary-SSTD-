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

TEST(csv, csv2vvec){
    std::vector<std::vector<std::string>> csv = sstd::csv2vvec(R"(./test/file/parseCSV.csv)");
    sstd::printn(csv.size());
    
    printf("----\n");
    for(uint p=0; p<csv.size(); ++p){
        for(uint q=0; q<csv[p].size(); ++q){
            printf("%s,", csv[p][q].c_str());
        }
        printf("\n");
    }
    printf("----\n");
}
TEST(csv, vvec2csv){
    sstd::mkdir("./tmp");
    std::vector<std::vector<std::string>> csv = sstd::csv2vvec(R"(./test/file/parseCSV.csv)");
    
    const char* path = R"(./tmp/test_vvec2csvPath.csv)";
    bool result = sstd::vvec2csv(path, csv); ASSERT_TRUE( result );
    std::vector<std::vector<std::string>> csv_re = sstd::csv2vvec(path);
    
    ASSERT_TRUE(csv == csv_re);
    sstd::rm("./tmp");
}
TEST(csv, csv2vvec_vvec2csv_std_string){
    std::string tmpDir = R"(./tmp)";
    sstd::mkdir(tmpDir);
    
    std::string exCSV = R"(./test/file/parseCSV.csv)";
    std::vector<std::vector<std::string>> csv = sstd::csv2vvec(exCSV);
    
    std::string path = tmpDir + R"(/test_vvec2csvPath.csv)";
    bool result = sstd::vvec2csv(path, csv); ASSERT_TRUE( result );
    std::vector<std::vector<std::string>> csv_re = sstd::csv2vvec(path);
    
    ASSERT_TRUE(csv == csv_re);
    sstd::rm(tmpDir);
}

