#include "./status.hpp"
#ifdef _WIN32
#else
//-----------------------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // for system

int sstd::status_print(){
	char cmd[128];
	sprintf(cmd, "cat /proc/%d/status", getpid());
	return system(cmd);
}

template<typename retVal>
uint64 sstd_statusBase(const char* fmtBase, const char* type){
	retVal ret=retVal();
	
	FILE *fp;
	char cmd[128];
	sprintf(cmd, "grep %s /proc/%d/status", type, getpid());
	if( (fp=popen(cmd,"r"))==NULL ){ return ret; } // failure
	
	char fmt[128];
	sprintf(fmt, fmtBase, type);
	int reads = fscanf(fp, fmt, &ret);
	if(reads==0){ return ret; } // failure
	
	if(pclose(fp)==-1){ return ret; } // failure
	return ret;
}
// std::string sstd::status_Name      (){ return sstd_statusBase(""      ); } // Name:	exe
// std::string sstd::status_State      (){ return sstd_statusBase(""      ); } // State:	S (sleeping)
uint64 sstd::status_Tgid        (){ return sstd_statusBase<uint64>("%s: %%ull", "Tgid"           ); } // Tgid:	18108
uint64 sstd::status_Ngid        (){ return sstd_statusBase<uint64>("%s: %%ull", "Ngid"           ); } // Ngid:	0
uint64 sstd::status_Pid         (){ return sstd_statusBase<uint64>("%s: %%ull", "Pid"            ); } // Pid:	18108
uint64 sstd::status_PPid        (){ return sstd_statusBase<uint64>("%s: %%ull", "PPid"           ); } // PPid:	15553
uint64 sstd::status_TracerPid   (){ return sstd_statusBase<uint64>("%s: %%ull", "TracerPid"      ); } // TracerPid:	0
// std::vector<uint64> sstd::status_Uid      (){ return sstd_statusBase(""      ); } // Uid:	1000	1000	1000	1000
// std::vector<uint64> sstd::status_Gid      (){ return sstd_statusBase(""      ); } // Gid:	1000	1000	1000	1000
uint64 sstd::status_FDSize      (){ return sstd_statusBase<uint64>("%s: %%ull", "FDSize"         ); } // FDSize:	256
// std::vector<uint64> sstd::status_Groups      (){ return sstd_statusBase(""      ); } // Groups:	4 24 27 30 46 113 128 1000

uint64 sstd::status_NStgid      (){ return sstd_statusBase<uint64>("%s: %%ull", "NStgid"         ); } // NStgid:	18108
uint64 sstd::status_NSpid       (){ return sstd_statusBase<uint64>("%s: %%ull", "NSpid"          ); } // NSpid:	18108
uint64 sstd::status_NSpgid      (){ return sstd_statusBase<uint64>("%s: %%ull", "NSpgid"         ); } // NSpgid:	18108
uint64 sstd::status_NSsid       (){ return sstd_statusBase<uint64>("%s: %%ull", "NSsid"          ); } // NSsid:	15553

uint64 sstd::status_VmPeak      (){ return sstd_statusBase<uint64>("%s: %%ull kB", "VmPeak"      ); } // VmPeak:	   16192 kB
uint64 sstd::status_VmSize      (){ return sstd_statusBase<uint64>("%s: %%ull kB", "VmSize"      ); } // VmSize:	   16192 kB
uint64 sstd::status_VmLck       (){ return sstd_statusBase<uint64>("%s: %%ull kB", "VmLck"       ); } // VmLck:	       0 kB
uint64 sstd::status_VmPin       (){ return sstd_statusBase<uint64>("%s: %%ull kB", "VmPin"       ); } // VmPin:	       0 kB
uint64 sstd::status_VmHWM       (){ return sstd_statusBase<uint64>("%s: %%ull kB", "VmHWM"       ); } // VmHWM:	    4004 kB
uint64 sstd::status_VmRSS       (){ return sstd_statusBase<uint64>("%s: %%ull kB", "VmRSS"       ); } // VmRSS:	    4004 kB
uint64 sstd::status_VmData      (){ return sstd_statusBase<uint64>("%s: %%ull kB", "VmData"      ); } // VmData:	     296 kB
uint64 sstd::status_VmStk       (){ return sstd_statusBase<uint64>("%s: %%ull kB", "VmStk"       ); } // VmStk:	     132 kB
uint64 sstd::status_VmExe       (){ return sstd_statusBase<uint64>("%s: %%ull kB", "VmExe"       ); } // VmExe:	     764 kB
uint64 sstd::status_VmLib       (){ return sstd_statusBase<uint64>("%s: %%ull kB", "VmLib"       ); } // VmLib:	    4664 kB
uint64 sstd::status_VmPTE       (){ return sstd_statusBase<uint64>("%s: %%ull kB", "VmPTE"       ); } // VmPTE:	      48 kB
uint64 sstd::status_VmPMD       (){ return sstd_statusBase<uint64>("%s: %%ull kB", "VmPMD"       ); } // VmPMD:	      12 kB
uint64 sstd::status_VmSwap      (){ return sstd_statusBase<uint64>("%s: %%ull kB", "VmSwap"      ); } // VmSwap:	       0 kB
uint64 sstd::status_HugetlbPages(){ return sstd_statusBase<uint64>("%s: %%ull kB", "HugetlbPages"); } // HugetlbPages:	       0 kB

uint64 sstd::status_Threads     (){ return sstd_statusBase<uint64>("%s: %%ull", "Threads"        ); } // Threads:	1
// uint64 sstd::status_SigQ      (){ return sstd_statusBase(""      ); } // SigQ:	5/128305
// uint64 sstd::status_SigPnd      (){ return sstd_statusBase("SigPnd"      ); } // SigPnd:	0000000000000000
// uint64 sstd::status_ShdPnd      (){ return sstd_statusBase("ShdPnd"      ); } // ShdPnd:	0000000000000000
// uint64 sstd::status_SigBlk      (){ return sstd_statusBase("SigBlk"      ); } // SigBlk:	0000000000010000
// uint64 sstd::status_SigIgn      (){ return sstd_statusBase("SigIgn"      ); } // SigIgn:	0000000000000006
// uint64 sstd::status_SigCgt      (){ return sstd_statusBase("SigCgt"      ); } // SigCgt:	0000000180000000
// uint64 sstd::status_CapInh      (){ return sstd_statusBase("CapInh"      ); } // CapInh:	0000000000000000
// uint64 sstd::status_CapPrm      (){ return sstd_statusBase("CapPrm"      ); } // CapPrm:	0000000000000000
// uint64 sstd::status_CapEff      (){ return sstd_statusBase("CapEff"      ); } // CapEff:	0000000000000000
// uint64 sstd::status_CapBnd      (){ return sstd_statusBase("CapBnd"      ); } // CapBnd:	0000003fffffffff
// uint64 sstd::status_CapAmb      (){ return sstd_statusBase("CapAmb"      ); } // CapAmb:	0000000000000000
uint64 sstd::status_Seccomp      (){ return sstd_statusBase<uint64>("%s: %%ull", "Seccomp"      ); } // Seccomp:	0
// std::string sstd::status_Speculation_Store_Bypass      (){ return sstd_statusBase(""      ); } // Speculation_Store_Bypass:	thread vulnerable
// uint64 sstd::status_Cpus_allowed      (){ return sstd_statusBase(""      ); } // Cpus_allowed:	ffff
// uint64 sstd::status_Cpus_allowed_list      (){ return sstd_statusBase(""      ); } // Cpus_allowed_list:	0-15
// std::vector<uint64> sstd::status_Mems_allowed      (){ return sstd_statusBase(""      ); } // Mems_allowed:	00000000,00000001
uint64 sstd::status_Mems_allowed_list         (){ return sstd_statusBase<uint64>("%s: %%ull", "Mems_allowed_list"         ); } // Mems_allowed_list:	0
uint64 sstd::status_voluntary_ctxt_switches   (){ return sstd_statusBase<uint64>("%s: %%ull", "voluntary_ctxt_switches"   ); } // voluntary_ctxt_switches:	35
uint64 sstd::status_nonvoluntary_ctxt_switches(){ return sstd_statusBase<uint64>("%s: %%ull", "nonvoluntary_ctxt_switches"); } // nonvoluntary_ctxt_switches:	2

/*
$ cat /proc/[PID]/status
Name:	exe
State:	S (sleeping)
Tgid:	18108
Ngid:	0
Pid:	18108
PPid:	15553
TracerPid:	0
Uid:	1000	1000	1000	1000
Gid:	1000	1000	1000	1000
FDSize:	256
Groups:	4 24 27 30 46 113 128 1000 
NStgid:	18108
NSpid:	18108
NSpgid:	18108
NSsid:	15553
VmPeak:	   16192 kB
VmSize:	   16192 kB
VmLck:	       0 kB
VmPin:	       0 kB
VmHWM:	    4004 kB
VmRSS:	    4004 kB
VmData:	     296 kB
VmStk:	     132 kB
VmExe:	     764 kB
VmLib:	    4664 kB
VmPTE:	      48 kB
VmPMD:	      12 kB
VmSwap:	       0 kB
HugetlbPages:	       0 kB
Threads:	1
SigQ:	5/128305
SigPnd:	0000000000000000
ShdPnd:	0000000000000000
SigBlk:	0000000000010000
SigIgn:	0000000000000006
SigCgt:	0000000180000000
CapInh:	0000000000000000
CapPrm:	0000000000000000
CapEff:	0000000000000000
CapBnd:	0000003fffffffff
CapAmb:	0000000000000000
Seccomp:	0
Speculation_Store_Bypass:	thread vulnerable
Cpus_allowed:	ffff
Cpus_allowed_list:	0-15
Mems_allowed:	00000000,00000001
Mems_allowed_list:	0
voluntary_ctxt_switches:	35
nonvoluntary_ctxt_switches:	2
//*/

//-----------------------------------------------------------------------------------------------------------------------------------------------
#endif
