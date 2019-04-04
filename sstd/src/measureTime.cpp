#include "measureTime.hpp"
#include "ssprintf.hpp"
#include "typeDef.h"


void sstd::measureTime_start(time_m& startTime){
	startTime = std::chrono::system_clock::now();
}
double sstd::measureTime_stop_s(const time_m& startTime){
	time_m endTime = std::chrono::system_clock::now();
	auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(endTime-startTime).count();
	return ((double)msec) / 1000.0;
}
double sstd::measureTime_stop_ms(const time_m& startTime){
	time_m endTime = std::chrono::system_clock::now();
	auto usec = std::chrono::duration_cast<std::chrono::microseconds>(endTime-startTime).count();
	return ((double)usec) / 1000.0;
}
double sstd::measureTime_stop_us(const time_m& startTime){
	time_m endTime = std::chrono::system_clock::now();
	auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime-startTime).count();
	return ((double)nsec) / 1000.0;
}
double sstd::measureTime_stop_ns(const time_m& startTime){
	time_m endTime = std::chrono::system_clock::now();
	auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime-startTime).count();
	return (double)nsec;
}
std::string sstd::measureTime_stop_str(const time_m& startTime){
	uint64 msec = (uint64)sstd::measureTime_stop_ms(startTime);
	uint64 sec = msec/1000;
	msec = msec - sec*1000;
	
	return sstd::ssprintf("Execution time: %5ld. %03ld sec", sec, msec);
}
void sstd::measureTime_stop_print(const time_m& startTime){
	printf("--------------------------------\n");
	printf(" %s\n", sstd::measureTime_stop_str(startTime).c_str());
	printf("--------------------------------\n");
}
