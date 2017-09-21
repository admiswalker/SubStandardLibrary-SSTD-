#pragma once

#include <stdio.h>
#include "pause.hpp"

#ifdef DEBUG
	#define pdbg(...) do_pdbg();{printf("%s(%d): ", __func__, __LINE__);printf(__VA_ARGS__);}
	#define pdbg_if(Boolean, ...) do_pdbg_if();if((Boolean)==true){sstd::pdbg(__VA_ARGS__);}
	#define pdbg_if_exit(Boolean, ...) do_pdbg_if_exit();if((Boolean)==true){sstd::pdbg(__VA_ARGS__);exit(-1);}
	#define pdbg_if_stop_exit(Boolean, ...) do_pdbg_if_stop_exit();if((Boolean)==true){sstd::pdbg(__VA_ARGS__);sstd::pauseIfWin32();exit(-1);}
	#define dbg(Code) do_dbg();{Code}
	#define ndbg(Code) do_not_ndbg();
#else
	#define pdbg(...) do_not_pdbg();
	#define pdbg_if(Boolean, ...) do_not_pdbg_if();
	#define pdbg_if_exit(Boolean, ...) do_not_pdbg_if_exit();
	#define pdbg_if_stop_exit(Boolean, ...) do_not_pdbg_if_stop_exit();
	#define dbg(Code) do_not_dbg();
	#define ndbg(Code) do_ndbg();{Code}
#endif

// 常時エラーを出力する必要がある場合
#define pdbg_always(...) do_pdbg_always();{printf("%s(%d): ", __func__, __LINE__); printf(__VA_ARGS__);}
#define pdbg_always_stop_exit(...) do_pdbg_always_stop_exit();{sstd::pdbg_always(__VA_ARGS__);sstd::pauseIfWin32();exit(-1);}

namespace sstd{
	inline void do_pdbg(){}
	inline void do_pdbg_if(){}
	inline void do_pdbg_if_exit(){}
	inline void do_pdbg_if_stop_exit(){}
	inline void do_dbg(){}
	inline void do_ndbg(){}

	inline void do_not_pdbg(){}
	inline void do_not_pdbg_if(){}
	inline void do_not_pdbg_if_exit(){}
	inline void do_not_pdbg_if_stop_exit(){}

	inline void do_pdbg_always(){}
	inline void do_pdbg_always_stop_exit(){}
	inline void do_not_dbg(){}
	inline void do_not_ndbg(){}
}
