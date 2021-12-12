#pragma once

void TEST__measureTime__mTime_start_stop(){
    {
        // sec
        time_m timem;
        sstd::measureTime_start(timem);
        sstd::sleep_ms(10);
        double sec = sstd::measureTime_stop_s(timem);
        uint64 buf = (uint64)(sec*100.0);
        ASSERT_TRUE( buf==1 );
    }
    {
        // milli sec
        time_m timem;
        sstd::measureTime_start(timem);
        sstd::sleep_ms(10);
        double ms = sstd::measureTime_stop_ms(timem);
        uint64 buf = (uint64)(ms/10.0);
        ASSERT_TRUE( buf==1 );
    }
    {
        // micro sec
        time_m timem;
        sstd::measureTime_start(timem);
        sstd::sleep_us(10*1000);
        double us = sstd::measureTime_stop_us(timem);
        uint64 buf = (uint64)(us/(10.0*1000.0));
        ASSERT_TRUE( buf==1 );
    }
    {
        // nano sec
        time_m timem;
        sstd::measureTime_start(timem);
        sstd::sleep_us(10*1000); // use sleeo_us, because sleep ns is not defind.
        double ns = sstd::measureTime_stop_ns(timem);
        uint64 buf = (uint64)(ns/(10.0*1000.0*1000.0));
        ASSERT_TRUE( buf==1 );
    }
    {
        // str
        uint64 tmp;
        std::string s;
        std::string ans;
        
        tmp  = 1000;
        tmp +=  200;
        s = sstd::measureTime_ms2str(tmp);
        ans  = "--------------------------------\n";
        ans += " Execution time:     1. 200 sec\n";
        ans += "--------------------------------";
        ASSERT_STREQ(ans.c_str(), s.c_str());
        
        tmp  = 60 * 1000;
        tmp +=  2 * 1000;
        tmp +=       300;
        s = sstd::measureTime_ms2str(tmp);
        ans  = "-------------------------------------\n";
        ans += " Execution time:     1 m  2. 300 sec\n";
        ans += "                 (     62. 300 sec )\n";
        ans += "-------------------------------------";
        ASSERT_STREQ(ans.c_str(), s.c_str());
        
        tmp  =  1 * 60 * 60 * 1000;
        tmp +=       2 * 60 * 1000;
        tmp +=            3 * 1000;
        tmp +=                 400;
        s = sstd::measureTime_ms2str(tmp);
        ans  = "------------------------------------------\n";
        ans += " Execution time:     1 h  2 m  3. 400 sec\n";
        ans += "                 (        3723. 400 sec )\n";
        ans += "------------------------------------------";
        ASSERT_STREQ(ans.c_str(), s.c_str());
        
        tmp  = 24 * 60 * 60 * 1000;
        tmp +=  2 * 60 * 60 * 1000;
        tmp +=       3 * 60 * 1000;
        tmp +=            4 * 1000;
        tmp +=                 500;
        s = sstd::measureTime_ms2str(tmp);
        ans  = "-------------------------------------------------\n";
        ans += " Execution time:     1 day  2 h  3 m  4. 500 sec\n";
        ans += "                 (              93784. 500 sec )\n";
        ans += "-------------------------------------------------";
        ASSERT_STREQ(ans.c_str(), s.c_str());
    }
    {
        // print
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(measureTime, mTime_start_stop){ TEST__measureTime__mTime_start_stop(); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

