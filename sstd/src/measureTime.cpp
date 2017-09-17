#include "measureTime.hpp"


void sstd::measureTime_start(time_m& StartTime){}
void sstd::measureTime_stop(time_m& StartTime){}


void sstd::measureTime_start_entity(time_m& StartTime){
	StartTime = std::chrono::system_clock::now();
}
void sstd::measureTime_stop_entity(time_m& StartTime){
	std::chrono::system_clock::time_point EndTime = std::chrono::system_clock::now();
    auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime-StartTime).count();
	auto sec = msec/1000;
	msec = msec - sec*1000;
	printf("--------------------------------\n");
	printf(" Execution time: %5ld. %03ld sec\n", sec, msec);
	printf("--------------------------------\n");
}