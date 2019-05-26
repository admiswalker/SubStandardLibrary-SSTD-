#include "time.hpp"
#ifndef _WIN32
	#include <sys/time.h> // for gettimeofday
#endif

struct tm sstd::time2tm(time_t unixtime){
	struct tm ret;
	#ifdef _WIN32
		gmtime_s(&ret, &unixtime);
	#else
		gmtime_r(&unixtime, &ret);
	#endif
	return ret;
}
time_t sstd::tm2time(struct tm& rhs){
	#ifdef _WIN32
		return _mkgmtime(&rhs);
	#else
		return timegm(&rhs);
	#endif
}

struct tm sstd::timeGm2tmLocal(time_t unixtime){
	struct tm ret;
	#ifdef _WIN32
		localtime_s(&ret, &unixtime);
	#else
		localtime_r(&unixtime, &ret);
	#endif
	return ret;
}
#ifdef _WIN32
int get_utc_offset(){
	time_t Jan2_1990 = 24*60*60;
	struct tm tmLocal = sstd::timeGm2tmLocal(Jan2_1990);
	int local_hh = tmLocal.tm_hour;
	if(tmLocal.tm_yday<(2-1)){ // GMT is now Jan 2, 1990 00:00, and Is local time under or over this?
		local_hh -= 24;
	}
	return local_hh;
}
#endif
time_t sstd::tmLocal2timeGm(struct tm& rhs){
	#ifdef _WIN32
		return sstd::tm2time(rhs) - get_utc_offset()*60*60;
	#else
		return timelocal(&rhs);
	#endif
}

std::string sstd::time2str(time_t unixtime){
	struct tm lhs = sstd::time2tm(unixtime);
	return tm2str(lhs);
}
std::string sstd::tm2str(struct tm& rhs){
	std::string str(19, 0); // strlen("2017-10-03 14:07:27") // '\0' will be malloced inside std::string.
	strftime(&str[0], 20, "%F %H:%M:%S", &rhs);
	return str;
}

double sstd::time2unixday(time_t unixtime){
	return ((double)unixtime)/(24.0*60.0*60.0); // 1970年1月1日午前0時0分0秒 からの経過日数．
}
double sstd::tm2unixday(struct tm& rhs){
	time_t unixtime = sstd::tm2time(rhs);
	return ((double)unixtime)/(24.0*60.0*60.0); // 1970年1月1日午前0時0分0秒 からの経過日数．
}

time_t sstd::yday2time(uint year, uint yday){
	
	struct tm date;
	date.tm_year = year - 1900;
	date.tm_mon  = 1 - 1; // [0, 11]
	date.tm_mday = 1;     // [1, 31]
	date.tm_hour = 0;     // [0, 23]
	date.tm_min  = 0;     // [0, 59]
	date.tm_sec  = 0;     // [0, 60/61]
//	date.tm_yday = 0;     // [0, 365]
	
	uint dayOfYear_minus1 = yday - 1; // 通日
	return sstd::tm2time(date) + dayOfYear_minus1 * 24 * 60 * 60;
}
struct tm sstd::yday2tm(uint year, uint yday){
	return sstd::time2tm(sstd::yday2time(year, yday));
}


struct timeval sstd::getTimeval(){
	struct timeval ret;
#ifdef _WIN32
	SYSTEMTIME sys_tm;
	GetSystemTime(&sys_tm);
	ret.tv_sec  = sys_tm.wSecond;
	ret.tv_usec = sys_tm.wMilliseconds*1000;
#else
	gettimeofday(&ret, NULL);
#endif
	return ret;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

double sstd::unixtime2JulianDate(time_t unixtime){
	// ユリウス日: ユリウス暦を -4712 年 (紀元前 4713 年) 01 月 01 日まで遡って適用し、そこから数えた経過日数です。ユリウス通日ということもあります。-4712年 (紀元前4713年) 1月1日はユリウス日では0日 - https://eco.mtk.nao.ac.jp/koyomi/wiki/A5E6A5EAA5A6A5B9C6FC.html - 2019 年 05 月 26 日閲覧．
	// unixtime: 1970/01/01からの経過秒数．
	// [1970/01/01] - [-4712/01/01] = 2440587.5[日](0.5は、ユリウス日が正午に日付が入れ替わるから。)
	// 1970年1月1日AM0:0:0（世界時） がユリウス日の 2440587.5日に相当
	
	// ユリウス通日 = (unixtime/(24*60*60))+2440587.5
	// ただし、ここでは閏秒を考慮せず。
	double JulianDate = (((double)unixtime)/((double)(24*60*60)))+(double)2440587.5;
	return JulianDate;
}

// 経過ユリウス年の計算
double sstd::Julius_T(time_t unixtime){
	double JulianDate = unixtime2JulianDate(unixtime);
	
	// 2000年1月1日12時(世界時)からのユリウス世紀
	// J2000.0からの経過日数をユリウス世紀単位(36525日単位)で測った時間をユリウス世紀数といいます。
	// ユリウス世紀数 T = (ユリウス日 - 2451545) / 36525
	// 経過ユリウス年 T = (ユリウス日 - 2451545) / 365.25
	double JuliusT = (JulianDate-(double)2451545.0)/(double)365.25;
	return JuliusT;
}
double sstd::JulianDate2Julius_T(double JulianDate){
	
	// 2000 年 01 月 01 日 12 時 (世界時) からのユリウス世紀
	// J2000.0からの経過日数をユリウス世紀単位(36525日単位)で測った時間をユリウス世紀数といいます。
	// ユリウス世紀数 T = (ユリウス日 - 2451545) / 36525
	// 経過ユリウス年 T = (ユリウス日 - 2451545) / 365.25
	double JuliusT = (JulianDate-(double)2451545.0)/(double)365.25;
	return JuliusT;
}

// Truncated Julian Day (TJD)
// TJD = JD - 2440000.5
// で定義されたもので、起算時点は1968年5月24日世界時0時である。
// これはNASAが導入したもので、天文計算に用いる。MJDに似ているが、これより１桁少ない数字で日付を表すことが出来る。
double sstd::TJuliusD(time_t unixtime){
	double TJD = unixtime2JulianDate(unixtime) - (double)2440000.5;
	return TJD;
}
double sstd::JulianDate2TJuliusD(double JulianDate){
	double TJD = JulianDate - (double)2440000.5;
	return TJD;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

void sstd::print(const struct tm& rhs){ printf("%s\n", sstd::tm2str((struct tm&)rhs).c_str()); }
void sstd::for_printn(const struct tm& rhs){ printf(" = %s\n", sstd::tm2str((struct tm&)rhs).c_str()); }


