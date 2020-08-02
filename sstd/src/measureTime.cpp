#include "measureTime.hpp"
#include "ssprintf.hpp"


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
std::string sstd::measureTime_ms2str(uint64 tmp){
    uint64 msec = tmp;
    uint64  sec = msec / 1000; msec -= sec*1000; uint64 sec_all = sec;
    uint64    m =  sec /   60;  sec -=   m*60;
    uint64    h =    m /   60;    m -=   h*60;
    uint64  day =    h /   24;    h -= day*24;

    uint len=0;
    std::string s;
    if      (day==0ull && h==0ull && m==0ull){ s = sstd::ssprintf(" Execution time: %5ld. %03ld sec\n",                                    sec, msec); len = s.size();
    }else if(day==0ull && h==0ull           ){ s = sstd::ssprintf(" Execution time: %5ld m %2ld. %03ld sec\n",                          m, sec, msec); len = s.size(); s += sstd::ssprintf("                 ( %6ld. %03ld sec )\n", sec_all, msec);
    }else if(day==0ull                      ){ s = sstd::ssprintf(" Execution time: %5ld h %2ld m %2ld. %03ld sec\n",                h, m, sec, msec); len = s.size(); s += sstd::ssprintf("                 ( %11ld. %03ld sec )\n", sec_all, msec);
    }else                                    { s = sstd::ssprintf(" Execution time: %5ld day %2ld h %2ld m %2ld. %03ld sec\n", day, h, m, sec, msec); len = s.size(); s += sstd::ssprintf("                 ( %18ld. %03ld sec )\n", sec_all, msec);
    }
    
    return std::string(len, '-') + "\n" + s + std::string(len, '-');
}
std::string sstd::measureTime_stop_str(const time_m& startTime){
    uint64 tmp = (uint64)sstd::measureTime_stop_ms(startTime);
    return sstd::measureTime_ms2str( tmp );
}
void sstd::measureTime_stop_print(const time_m& startTime){
    printf("%s\n", sstd::measureTime_stop_str(startTime).c_str());
    /*
     -------------------------------------------------
      Execution time:     1 day  2 h  3 m  4. 500 sec
                      (              93784. 000 sec )
     -------------------------------------------------
    */
}
