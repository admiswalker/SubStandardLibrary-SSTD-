#pragma once
#include <time.h>
#include <string>
#include "typeDef.h"
#ifdef _WIN32
	#include <winsock2.h> // for "struct timeval" // マクロが再定義されました。主な原因は、<WinSock2.h>より先に<windows.h>がインクルードされたことです。Windowsの制約として、windows.hよりも先にwinsock2.hをインクルードすることが必要です。http://www.02.246.ne.jp/~torutk/cxx/socket/win32_socket.html
	#include <windows.h>
#endif

namespace sstd{
//	struct tm getTm_gm(0);       // get current time
//	struct tm getTm_local(0);    // get current time
//	time_t    getTime_gm(0);     // get current time
//	time_t    getTime_local(0);  // get current time
	
	struct tm time2tm       (time_t unixtime);
	time_t    tm2time       (struct tm& rhs);
	struct tm timeGm2tmLocal(time_t unixtime);
	time_t    tmLocal2timeGm(struct tm& rhs);
	std::string time2str    (time_t unixtime);
	std::string   tm2str    (struct tm& rhs);
	double      time2unixday(time_t unixtime);
	double        tm2unixday(struct tm& rhs);
	
//	struct tm timeLocal2tmGm(struct tm& rhs);
//	time_t    tmGm2timeLocal(struct tm& rhs);
//	time_t timeGm2timeLocal(time_t unixtime);
//	time_t timeGm2timeLocal(time_t unixtime);
//	time_t timeLocal2timeGm(time_t unixtime);
//	time_t timeLocal2timeGm(time_t unixtime);

	time_t    yday2time(uint year, uint yday);
	struct tm yday2tm  (uint year, uint yday);

	struct timeval getTimeval();

	//---

	double unixtime2JulianDate(time_t unixtime);
	
	// 経過ユリウス年の計算
	double Julius_T(time_t unixtime);
	double JulianDate2Julius_T(double JulianDate);
	
	// Truncated Julian Day (TJD)
	// TJD=JD-2440000.5
	// で定義されたもので、起算時点は1968年5月24日世界時0時である。
	// これはNASAが導入したもので、天文計算に用いる。MJDに似ているが、これより１桁少ない数字で日付を表すことが出来る。
	double TJuliusD(time_t unixtime);
	double JulianDate2TJuliusD(double JulianDate);
	
	//---

//	print(time_t unixtime);
	void print(const struct tm& rhs);
	void for_printn(const struct tm& rhs);
}
