#pragma once

/*
 * compile option for sstd to remove uncompilable code for cygwin
 */

/* sstd::pdbg defines "pdbg", "pdbg_if", "pdbg_if_exit", "pdbg_if_stop_exit", "dbg", "ndbg", "pdbg_always" and "pdbg_always_stop_exit" as a global scope. */
#define use_sstd_pdbg

/* sstd::printn defines "printn" as a global scope. */
#define use_sstd_printn

#define use_sstd_gcc4_4_7



