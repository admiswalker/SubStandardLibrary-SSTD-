//#include <unistd.h>
#include<thread>
#include "typeDef.h"

namespace sstd{
	inline void sleep_hour(uint rhs){ std::this_thread::sleep_for(std::chrono::hours       (rhs)); }
	inline void sleep_min (uint rhs){ std::this_thread::sleep_for(std::chrono::minutes     (rhs)); }
	inline void sleep_s   (uint rhs){ std::this_thread::sleep_for(std::chrono::seconds     (rhs)); }
	inline void sleep_ms  (uint rhs){ std::this_thread::sleep_for(std::chrono::milliseconds(rhs)); }
	inline void sleep_us  (uint rhs){ std::this_thread::sleep_for(std::chrono::microseconds(rhs)); }
	inline void sleep_ns  (uint rhs){ std::this_thread::sleep_for(std::chrono::nanoseconds (rhs)); }
}

/*
namespace sstd{
	inline void sleep_s(uint rhs);  // second
	inline void sleep_ms(uint rhs); // milli second
	inline void sleep_us(uint rhs); // micro second
}


#ifdef _WIN32
	inline void sstd::sleep_s(uint rhs){ Sleep(rhs*1000); }
	inline void sstd::sleep_ms(uint rhs){
		timeBeginPeriod(1);
		Sleep(rhs);
		timeEndPeriod(1);
	}
	inline void sstd::sleep_us(uint rhs){ std::this_thread::sleep_for(std::chrono::microseconds(rhs)); }
#else
	inline void sstd::sleep_s(uint rhs){ sleep(rhs); }
	inline void sstd::sleep_ms(uint rhs){ usleep(rhs*1000); }
	inline void sstd::sleep_us(uint rhs){ usleep(rhs); }
#endif
*/
