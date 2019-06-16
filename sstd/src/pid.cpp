#include "./pid.hpp"

#include <stdio.h>

#ifdef _WIN32
	#include <Windows.h>
#else
	#include <sys/types.h> 
	#include <unistd.h>
#endif

int32 sstd::getpid(){
	#ifdef _WIN32
		return (int32)GetCurrentProcessId();
	#else
		return (int32)::getpid();
	#endif
}




