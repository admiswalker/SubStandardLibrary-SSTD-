#pragma once

#ifdef _WIN32
	#include <stdio.h>
	#include <windows.h>   //system("pause");用
#else
	#include <stdio.h>
#endif

//===

// このヘッダに，直接実装を書けば見通しがよいが，
// 実体を各所で include すると，容易に多重定義エラとなるので，
// 実装と定義を分離すべく，このままにしておく．

//===

namespace sstd{
	void pauseIfWin32();
	void do_pauseIfWin32();
	void do_not_pauseIfWin32();
}
#ifdef sstd_usePauseIfWin32
	#define pauseIfWin32 do_pauseIfWin32
#else
	#define pauseIfWin32 do_not_pauseIfWin32
#endif

//===

namespace sstd{
	void pause();
	void do_pause();
	void do_not_pause();
}
#ifdef sstd_usePause
	#define pause do_pause
#else
	#define pause do_not_pause
#endif

//===
