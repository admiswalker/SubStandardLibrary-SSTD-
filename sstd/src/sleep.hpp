#pragma once
#include "typeDef.h"

#include "../compileOption.hpp"
#ifndef use_sstd_gcc4_4_7
	#include<thread>
	namespace sstd{
		inline void sleep_hour(uint rhs){ std::this_thread::sleep_for(std::chrono::hours       (rhs)); }
		inline void sleep_min (uint rhs){ std::this_thread::sleep_for(std::chrono::minutes     (rhs)); }
		inline void sleep_s   (uint rhs){ std::this_thread::sleep_for(std::chrono::seconds     (rhs)); }
		inline void sleep_ms  (uint rhs){ std::this_thread::sleep_for(std::chrono::milliseconds(rhs)); }
		inline void sleep_us  (uint rhs){ std::this_thread::sleep_for(std::chrono::microseconds(rhs)); }
		inline void sleep_ns  (uint rhs){ std::this_thread::sleep_for(std::chrono::nanoseconds (rhs)); }
	}
#else
	#ifdef _WIN32
		#include <winsock2.h> // for "struct timeval" // マクロが再定義されました。主な原因は、<WinSock2.h>より先に<windows.h>がインクルードされたことです。Windowsの制約として、windows.hよりも先にwinsock2.hをインクルードすることが必要です。http://www.02.246.ne.jp/~torutk/cxx/socket/win32_socket.html
		#include <windows.h>
		#undef min
		#undef max
		namespace sstd{
			inline void sleep_hour(uint rhs){ Sleep(rhs*1000*60*60); }
			inline void sleep_min (uint rhs){ Sleep(rhs*1000*60   ); }
			inline void sleep_s   (uint rhs){ Sleep(rhs*1000      ); }
			inline void sleep_ms  (uint rhs){ Sleep(rhs           ); }
			inline void sleep_us  (uint rhs){ printf("ERROR: Not supported\n"); }
			inline void sleep_ns  (uint rhs){ printf("ERROR: Not supported\n"); }
		}
	#else
		#include <stdio.h>
		#include <unistd.h>
		namespace sstd{
			inline void sleep_hour(uint rhs){  sleep(rhs*60*60); }
			inline void sleep_min (uint rhs){  sleep(rhs*60   ); }
			inline void sleep_s   (uint rhs){  sleep(rhs      ); }
			inline void sleep_ms  (uint rhs){ usleep(rhs*1000 ); }
			inline void sleep_us  (uint rhs){ usleep(rhs      ); }
			inline void sleep_ns  (uint rhs){ printf("ERROR: use_sstd_gcc4_4_7 option not support sleep_ns()\n"); } // not support
		}
	#endif
#endif
