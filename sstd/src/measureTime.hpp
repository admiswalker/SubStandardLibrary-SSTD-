#pragma once

#include <stdio.h>
#ifdef _WIN32
#else
	#include <unistd.h>
#endif

#include <chrono>
#include <ctime>
#include <string>

typedef std::chrono::system_clock::time_point time_m;

namespace sstd{
	void        measureTime_start     (      time_m& startTime);
	double      measureTime_stop_s    (const time_m& startTime); // sec
	double      measureTime_stop_ms   (const time_m& startTime); // milli sec
	double      measureTime_stop_us   (const time_m& startTime); // micro sec
	double      measureTime_stop_ns   (const time_m& startTime); // nano sec
	std::string measureTime_stop_str  (const time_m& startTime);
	void        measureTime_stop_print(const time_m& startTime);
}

