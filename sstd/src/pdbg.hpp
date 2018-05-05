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
}

#define pdbg(...) pdbg_dummy();{printf("%s(%d): ", __func__, __LINE__);printf(__VA_ARGS__);}
#define pdbg_if(Boolean, ...) pdbg_dummy();if((Boolean)==true){sstd::pdbg(__VA_ARGS__);}
#define pdbg_if_exit(Boolean, ...) pdbg_dummy();if((Boolean)==true){sstd::pdbg(__VA_ARGS__);exit(-1);}
#define pdbg_if_stop_exit(Boolean, ...) pdbg_dummy();if((Boolean)==true){sstd::pdbg(__VA_ARGS__);sstd::pauseIfWin32();exit(-1);}
#define dbg(Code) pdbg_dummy();{Code}
#define ndbg(Code) pdbg_dummy();
