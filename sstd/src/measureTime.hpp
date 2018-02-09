#pragma once

#include <stdio.h>
#ifdef _WIN32
#else
	#include <unistd.h>
#endif

#include <chrono>
#include <ctime>

typedef std::chrono::system_clock::time_point time_m;

namespace sstd{
	void measureTime_start(time_m& startTime);
	void measureTime_stop(time_m& startTime);
	void measureTime_start_entity(time_m& startTime);
	void measureTime_stop_entity(time_m& startTime);
}

#ifdef use_sstd_measureTime
	#define measureTime_start measureTime_start_entity
	#define measureTime_stop measureTime_stop_entity
#endif
