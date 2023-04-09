#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(status, memory){
    sstd::status_print();
    printf("\n");
    
//    sstd::printn( sstd::status_Name()         ); // Name:    exe
//    sstd::printn( sstd::status_State()        ); // State:    S (sleeping)
    sstd::printn( sstd::status_Tgid()         ); // Tgid:    18108
    sstd::printn( sstd::status_Ngid()         ); // Ngid:    0
    sstd::printn( sstd::status_Pid()          ); // Pid:    18108
    sstd::printn( sstd::status_PPid()         ); // PPid:    15553
    sstd::printn( sstd::status_TracerPid()    ); // TracerPid:    0
//    sstd::printn( sstd::status_Uid()          ); // Uid:    1000    1000    1000    1000
//    sstd::printn( sstd::status_Gid()          ); // Gid:    1000    1000    1000    1000
    sstd::printn( sstd::status_FDSize()       ); // FDSize:    256
//    sstd::printn( sstd::status_Groups()       ); // Groups:    4 24 27 30 46 113 128 1000
    
    sstd::printn( sstd::status_NStgid()       );
    sstd::printn( sstd::status_NSpid()        );
    sstd::printn( sstd::status_NSpgid()       );
    sstd::printn( sstd::status_NSsid()        );
    
    sstd::printn( sstd::status_VmPeak()       );
    sstd::printn( sstd::status_VmSize()       );
    sstd::printn( sstd::status_VmLck()        );
    sstd::printn( sstd::status_VmPin()        );
    sstd::printn( sstd::status_VmHWM()        );
    sstd::printn( sstd::status_VmRSS()        );
    sstd::printn( sstd::status_VmData()       );
    sstd::printn( sstd::status_VmStk()        );
    sstd::printn( sstd::status_VmExe()        );
    sstd::printn( sstd::status_VmLib()        );
    sstd::printn( sstd::status_VmPTE()        );
    sstd::printn( sstd::status_VmPMD()        );
    sstd::printn( sstd::status_VmSwap()       );
    sstd::printn( sstd::status_HugetlbPages() );
    
    sstd::printn( sstd::status_Threads()      ); // Threads:    1
//    sstd::printn( sstd::status_SigQ()         ); // SigQ:    5/128305
//    sstd::printn( sstd::status_SigPnd()       ); // SigPnd:    0000000000000000
//    sstd::printn( sstd::status_ShdPnd()       ); // ShdPnd:    0000000000000000
//    sstd::printn( sstd::status_SigBlk()       ); // SigBlk:    0000000000010000
//    sstd::printn( sstd::status_SigIgn()       ); // SigIgn:    0000000000000006
//    sstd::printn( sstd::status_SigCgt()       ); // SigCgt:    0000000180000000
//    sstd::printn( sstd::status_CapInh()       ); // CapInh:    0000000000000000
//    sstd::printn( sstd::status_CapPrm()       ); // CapPrm:    0000000000000000
//    sstd::printn( sstd::status_CapEff()       ); // CapEff:    0000000000000000
//    sstd::printn( sstd::status_CapBnd()       ); // CapBnd:    0000003fffffffff
//    sstd::printn( sstd::status_CapAmb()       ); // CapAmb:    0000000000000000
    sstd::printn( sstd::status_Seccomp()                   );// Seccomp:    0
//    sstd::printn( sstd::status_Speculation_Store_Bypass()  ); // Speculation_Store_Bypass:    thread vulnerable
//    sstd::printn( sstd::status_Cpus_allowed()              ); // Cpus_allowed:    ffff
//    sstd::printn( sstd::status_Cpus_allowed_list()         ); // Cpus_allowed_list:    0-15
//    sstd::printn( sstd::status_Mems_allowed()              ); // Mems_allowed:    00000000,00000001
    sstd::printn( sstd::status_Mems_allowed_list()         ); // Mems_allowed_list:    0
    sstd::printn( sstd::status_voluntary_ctxt_switches()   ); // voluntary_ctxt_switches:    35
    sstd::printn( sstd::status_nonvoluntary_ctxt_switches()); // nonvoluntary_ctxt_switches:    2
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
