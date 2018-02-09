#pragma once

#include <stdio.h>
#include "pause.hpp"

namespace sstd{
	// need to inline in order to avoid mulple definition
	inline void pdbg_dummy(){}
	
	inline void pdbg(...){}
	inline void pdbg_if(...){}
	inline void pdbg_if_exit(...){}
	inline void pdbg_if_stop_exit(...){}
	inline void dbg(...){}
	inline void ndbg(...){}

	inline void pdbg_always(...){}
	inline void pdbg_always_stop_exit(...){}
}

#ifdef DEBUG
	#define pdbg(...) pdbg_dummy();{printf("%s(%d): ", __func__, __LINE__);printf(__VA_ARGS__);}
	#define pdbg_if(Boolean, ...) pdbg_dummy();if((Boolean)==true){sstd::pdbg(__VA_ARGS__);}
	#define pdbg_if_exit(Boolean, ...) pdbg_dummy();if((Boolean)==true){sstd::pdbg(__VA_ARGS__);exit(-1);}
	#define pdbg_if_stop_exit(Boolean, ...) pdbg_dummy();if((Boolean)==true){sstd::pdbg(__VA_ARGS__);sstd::pauseIfWin32();exit(-1);}
	#define dbg(Code) pdbg_dummy();{Code}
	#define ndbg(Code) pdbg_dummy();
#else
	#define pdbg(...) pdbg_dummy();
	#define pdbg_if(Boolean, ...) pdbg_dummy();
	#define pdbg_if_exit(Boolean, ...) pdbg_dummy();
	#define pdbg_if_stop_exit(Boolean, ...) pdbg_dummy();
	#define dbg(Code) pdbg_dummy();
	#define ndbg(Code) pdbg_dummy();{Code}
#endif

// 常時エラーを出力する必要がある場合
#define pdbg_always(...) pdbg_dummy();{printf("%s(%d): ", __func__, __LINE__); printf(__VA_ARGS__);}
#define pdbg_always_stop_exit(...) pdbg_dummy();{sstd::pdbg_always(__VA_ARGS__);sstd::pauseIfWin32();exit(-1);}

