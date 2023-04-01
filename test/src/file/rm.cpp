#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

// Do not run this test, in order not to break your system when a sstd::rm() has a bag and removing unexpected file or direcories.
// And run this test on a external disk or virtual machine, preparing for the system corruption.


//-----------------------------------------------------------------------------------------------------------------------------------------------
// rm

TEST(rm, rm_case01){
//    sstd::rm(".");
//    sstd::rm("/media/admis/KIOXIA/test_rm");
//    sstd::rm("/media/admis/KIOXIA/test_rm");
//    sstd::rm("/media/admis/KIOXIA/test_rm/a/al");
}

TEST(rm, rm_case02){
    // when a file name and directory name is same
    // -> Not allowed by a file system.

//    sstd::system("touch a");
//    sstd::system("mkdir a"); // ERROR
}

/*
void TEST_rm(){
    printf("■ rm\n");
    printf("  □ unlink\n");
    { sstd::file fp; fp.fopen("./unlink.txt", "w"); }
    sstd::printn(sstd::unlink("./unlink.txt"));
    printf("\n");

    printf("  □ rmdir\n");
    sstd::mkdir("./test_rmdir");
    sstd::printn(sstd::rmdir("./test_rmdir"));
    printf("\n");
    
    sstd::mkdir("./test_rm/abc/def");
    sstd::mkdir("./test_rm/abc2/def");
    { sstd::file fp; fp.fopen("./test_rm/abc/def/abc.txt", "w"); }
    { sstd::file fp; fp.fopen("./test_rm/abc/abc.txt",     "w"); }
    { sstd::file fp; fp.fopen("./test_rm/abc/xxx",         "w"); }
    { sstd::file fp; fp.fopen("./test_rm/abc2/xxx",        "w"); }
    { sstd::file fp; fp.fopen("./test_rm/123.txt",         "w"); }
    
    printf("  □ getAllInDir\n");
    std::vector<struct sstd::pathAndType> ret;
    sstd::printn(sstd::getAllPath(ret, "./test_rm"));
    for(uint i=0; i<ret.size(); i++){
        if      (ret[i].type=='f'){ sstd::printn(sstd::ssprintf("type: file,      path: %s", ret[i].path.c_str()));
        }else if(ret[i].type=='d'){ sstd::printn(sstd::ssprintf("type: directory, path: %s", ret[i].path.c_str()));
        }          else           { sstd::pdbg("ERROR: sstd::getAllInDir() is failed.\n"); }
    }
    printf("\n");
    
    std::vector<std::string> retStr;
    sstd::printn(sstd::getAllPath(retStr, "./test_rm")); sstd::printn(retStr); printf("\n");
    sstd::printn(sstd::getAllFile(retStr, "./test_rm")); sstd::printn(retStr); printf("\n");
    sstd::printn(sstd::getAllDir (retStr, "./test_rm")); sstd::printn(retStr); printf("\n");
    printf("\n");
    
    printf("  □ rm\n");
    sstd::printn(sstd::rm("./test_rm")); // enable to delete not empty directory by one step.
}
*/

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
