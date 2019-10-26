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
    }
    {
        // print
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(measureTime, mTime_start_stop){ TEST__measureTime__mTime_start_stop(); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

