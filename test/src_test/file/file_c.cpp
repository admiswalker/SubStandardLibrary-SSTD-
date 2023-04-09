#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

/*
void TEST_file_c(){
    // $ sha512sum ./test/test.png
    // 021c3d7da0cedd5aa780ca765f9071f210ed3e19db3c08ee74aa6531aaf6552c3daaa8d0f30abeb10a30793bffbb86d39e3b019b865d54c2793dbd3b62c243e6  ./test/test.png

    const char* pFilePath_c = "./test_file_c.png";
    {
        const char* pFilePath = "./test/test.png";
        std::vector<uint8> data = sstd::readAll_bin(pFilePath);
        
        sstd::file_c fp_c;
        if(!fp_c.fopen_wbp(pFilePath_c)){ sstd::pdbg("ERROR: sstd::file_c::fopen_wbp(%s) was failed.\n", pFilePath); return; }
        if(!fp_c.fwriteAll(data)       ){ sstd::pdbg("ERROR: sstd::file_c::fwriteAll(%s) was failed.\n", pFilePath); return; }
    }
    
    const char* pFilePath_c2f = "./test_file_c2f.png";
    {
        std::vector<uint8> data;
        
        sstd::file_c fp_c;
        if(!fp_c.fopen_rbp(pFilePath_c)){ sstd::pdbg("ERROR: sstd::file_c::fopen_rbp(%s) was failed.\n", pFilePath_c); return; }
        if(!fp_c.freadAll (data)       ){ sstd::pdbg("ERROR: sstd::file_c::freadAll() was failed.\n"); return; }

        if(!sstd::writeAll_bin(pFilePath_c2f, data)){ sstd::pdbg("ERROR: sstd::fwriteAll(%s) was failed.\n", pFilePath_c2f); return; }
    }
}
*/

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
