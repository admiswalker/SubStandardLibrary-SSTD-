#pragma once

#include <stdio.h>
#include "../sys/pause.hpp"

namespace sstd{
    // need to inline in order to avoid mulple definition
    inline void pdbg_dummy(){}
    
    inline void pdbg(...){}
    inline void pdbg_err(...){}
    inline void pdbg_if(...){}
    inline void pdbg_if_exit(...){}
    inline void pdbg_if_stop_exit(...){}
    inline void dbg(...){}
    inline void ndbg(...){}
}

#define pdbg(...) pdbg_dummy();{printf("\u001b[1m\u001b[31m%s:%d %s(): \u001b[0m", __FILE__, __LINE__, __func__);printf(__VA_ARGS__);}
#define pdbg_err(...) pdbg_dummy();{printf("\u001b[1m%s:%d %s(): \u001b[31merror: \u001b[0m", __FILE__, __LINE__, __func__);printf(__VA_ARGS__);}
#define pdbg_err(...) pdbg_dummy();{printf("\u001b[1m%s:%d %s(): \u001b[31merror: \u001b[0m", __FILE__, __LINE__, __func__);printf(__VA_ARGS__);}
#define pdbg_err_str(...) ssprintf("%s:%d %s(): error: %s", __FILE__, __LINE__, __func__, sstd::ssprintf(__VA_ARGS__).c_str())
//  \u001b[1m  : set bold
//  \u001b[31m  :  set output red
//  \u001b[0m   :  reset bold and color
#define pdbg_if(Boolean, ...) pdbg_dummy();if((Boolean)==true){sstd::pdbg(__VA_ARGS__);}
#define pdbg_if_exit(Boolean, ...) pdbg_dummy();if((Boolean)==true){sstd::pdbg(__VA_ARGS__);exit(-1);}
#define pdbg_if_stop_exit(Boolean, ...) pdbg_dummy();if((Boolean)==true){sstd::pdbg(__VA_ARGS__);sstd::pauseIfWin32();exit(-1);}
#define dbg(Code) pdbg_dummy();{Code}
#define ndbg(Code) pdbg_dummy();
