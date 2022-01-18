#pragma once

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

