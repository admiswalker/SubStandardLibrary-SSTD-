#include "measureTime.hpp"


void sstd::measureTime_start(time_m& startTime){}
void sstd::measureTime_stop(time_m& startTime){}


void sstd::measureTime_start_entity(time_m& startTime){
	startTime = std::chrono::system_clock::now();
}
void sstd::measureTime_stop_entity(time_m& startTime){
	std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
    auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(endTime-startTime).count();
	auto sec = msec/1000;
	msec = msec - sec*1000;
	printf("--------------------------------\n");
	printf(" Execution time: %5ld. %03ld sec\n", sec, msec);
	printf("--------------------------------\n");
}
