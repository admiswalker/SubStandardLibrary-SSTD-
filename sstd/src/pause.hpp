#pragma once

#ifdef _WIN32
	#include <winsock2.h> // for "struct timeval" // マクロが再定義されました。主な原因は、<WinSock2.h>より先に<windows.h>がインクルードされたことです。Windowsの制約として、windows.hよりも先にwinsock2.hをインクルードすることが必要です。http://www.02.246.ne.jp/~torutk/cxx/socket/win32_socket.html
	#include <windows.h>  //system("pause");用
	#undef min
	#undef max

	#include <stdio.h>
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
#ifdef use_sstd_pauseIfWin32
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
#ifdef use_sstd_pause
	#define pause do_pause
#else
	#define pause do_not_pause
#endif

//===
