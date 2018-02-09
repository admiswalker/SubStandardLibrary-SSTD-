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

void sstd::print(const struct tm& rhs){ printf("%s\n", sstd::tm2str((struct tm&)rhs).c_str()); }
void sstd::for_printn(const struct tm& rhs){ printf(" = %s\n", sstd::tm2str((struct tm&)rhs).c_str()); }
