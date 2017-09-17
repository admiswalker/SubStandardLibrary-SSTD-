#pragma once

#include <stdio.h>
#include "pause.hpp"

#define DEBUG

#ifdef DEBUG
	#define printf_dbger(...) {printf("%s(%d): ", __func__, __LINE__); printf(__VA_ARGS__);}
	#define printf_dbger_if(Boolean, ...) if((Boolean)==true){printf_dbger(__VA_ARGS__);}
	#define printf_dbger_if_Exit(Boolean, ...) if((Boolean)==true){printf_dbger(__VA_ARGS__);exit(-1);}
	#define printf_dbger_if_Stop_Exit(Boolean, ...) if((Boolean)==true){printf_dbger(__VA_ARGS__);sstd::pauseIfWin32();exit(-1);}
	#define if_dbg(Code) {Code}
#else
	#define printf_dbger(...)
	#define printf_dbger_if(Boolean, ...)
	#define printf_dbger_if_Exit(Boolean, ...)
	#define printf_dbger_if_Exit_Stop(Boolean, ...)
	#define if_dbg(Code)
#endif

// 常時エラーを出力する必要がある場合
#define printf_ErrMsg(...) {printf("%s(%d): ", __func__, __LINE__); printf(__VA_ARGS__);}
#define printf_ErrMsg_Stop_Exit(...) {printf_ErrMsg(__VA_ARGS__);sstd::pauseIfWin32();exit(-1);}

// How to use this
//
//  printf_dbger("DbgMsg: error message. value = %lf. \n", 3.14);			// always
// >> FunctionName(LineNum): DbgMsg: error message. value = 3.140000.
// >> 続行するには何かキーを押してください . . .
//
//  printf_dbger_if(true, "ERROR: error message. value = %lf. \n", 3.14);	// when a conditional expression is false
// >> FunctionName(LineNum): ERROR: error message. value = 3.140000.
// >> 続行するには何かキーを押してください . . .
//
// if_dbg(XXXXX);	// XXXXX: Code that is only run while "DEBUG" is defined.

/*
#pragma once

#include <stdio.h>
#include "SysPauseForWin32.h"

#define DEBUG
#ifdef DEBUG
	#define printf_dbger(...) {printf("%s(%d): ", __func__, __LINE__); printf(__VA_ARGS__);}
	#define printf_dbger_if(Boolean, ...) if((Boolean)==true){printf_dbger(__VA_ARGS__);SysPauseForWin32();exit(-1);}
	#define if_dbg(Code) {Code}
#else
	#define printf_dbger(...)
	#define printf_dbger_if(Boolean,...)
	#define if_dbg(Code)
#endif

// How to use this
//
//  printf_dbger("DbgMsg: error message. value = %lf. \n", 3.14);			// always
// >> FunctionName(LineNum): DbgMsg: error message. value = 3.140000.
// >> 続行するには何かキーを押してください . . .
//
//  printf_dbger_if(false, "ERROR: error message. value = %lf. \n", 3.14);	// when a conditional expression is false
// >> FunctionName(LineNum): ERROR: error message. value = 3.140000.
// >> 続行するには何かキーを押してください . . .
//
// if_dbg(XXXXX);	// XXXXX: Code that is only run while "DEBUG" is defined.
*/
