#pragma once
#ifdef _WIN32
#else

#include "./typeDef.h"

namespace sstd{
	int status_print();
	
	// std::string status_Name (); // Name:	exe
	// std::string status_State(); // State:	S (sleeping)
	uint64 status_Tgid        (); // Tgid:	18108
	uint64 status_Ngid        (); // Ngid:	0
	uint64 status_Pid         (); // Pid:	18108
	uint64 status_PPid        (); // PPid:	15553
	uint64 status_TracerPid   (); // TracerPid:	0
	// std::vector<uint64> status_Uid(); // Uid:	1000	1000	1000	1000
	// std::vector<uint64> status_Gid(); // Gid:	1000	1000	1000	1000
	uint64 status_FDSize      (); // FDSize:	256
	// std::vector<uint64> status_Groups(); // Groups:	4 24 27 30 46 113 128 1000
	
	uint64 status_NStgid      (); // NStgid:	18108
	uint64 status_NSpid       (); // NSpid:	18108
	uint64 status_NSpgid      (); // NSpgid:	18108
	uint64 status_NSsid       (); // NSsid:	15553
	
	uint64 status_VmPeak      (); // VmPeak:	   16192 kB
	uint64 status_VmSize      (); // VmSize:	   16192 kB
	uint64 status_VmLck       (); // VmLck:	       0 kB
	uint64 status_VmPin       (); // VmPin:	       0 kB
	uint64 status_VmHWM       (); // VmHWM:	    4004 kB
	uint64 status_VmRSS       (); // VmRSS:	    4004 kB
	uint64 status_VmData      (); // VmData:	     296 kB
	uint64 status_VmStk       (); // VmStk:	     132 kB
	uint64 status_VmExe       (); // VmExe:	     764 kB
	uint64 status_VmLib       (); // VmLib:	    4664 kB
	uint64 status_VmPTE       (); // VmPTE:	      48 kB
	uint64 status_VmPMD       (); // VmPMD:	      12 kB
	uint64 status_VmSwap      (); // VmSwap:	       0 kB
	uint64 status_HugetlbPages(); // HugetlbPages:	       0 kB
	
	uint64 status_Threads     (); // Threads:	1
	// uint64 status_SigQ     (); // SigQ:	5/128305
	// uint64 status_SigPnd   (); // SigPnd:	0000000000000000
	// uint64 status_ShdPnd   (); // ShdPnd:	0000000000000000
	// uint64 status_SigBlk   (); // SigBlk:	0000000000010000
	// uint64 status_SigIgn   (); // SigIgn:	0000000000000006
	// uint64 status_SigCgt   (); // SigCgt:	0000000180000000
	// uint64 status_CapInh   (); // CapInh:	0000000000000000
	// uint64 status_CapPrm   (); // CapPrm:	0000000000000000
	// uint64 status_CapEff   (); // CapEff:	0000000000000000
	// uint64 status_CapBnd   (); // CapBnd:	0000003fffffffff
	// uint64 status_CapAmb   (); // CapAmb:	0000000000000000
	uint64 status_Seccomp  (); // Seccomp:	0
	// std::string status_Speculation_Store_Bypass(); // Speculation_Store_Bypass:	thread vulnerable
	// uint64 status_Cpus_allowed                 (); // Cpus_allowed:	ffff
	// uint64 status_Cpus_allowed_list            (); // Cpus_allowed_list:	0-15
	// std::vector<uint64> status_Mems_allowed    (); // Mems_allowed:	00000000,00000001
	uint64 status_Mems_allowed_list               (); // Mems_allowed_list:	0
	uint64 status_voluntary_ctxt_switches         (); // voluntary_ctxt_switches:	35
	uint64 status_nonvoluntary_ctxt_switches      (); // nonvoluntary_ctxt_switches:	2
}

#endif

