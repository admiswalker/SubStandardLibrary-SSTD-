#pragma once


void TEST_time(){
    printf("■ time\n");
    time_t      c_time    = time(0); // get current time
    struct tm   c_tm      = sstd::time2tm(c_time);
    time_t      c_time_2  = sstd::tm2time(c_tm);
    double      unixday   = sstd::time2unixday(c_time);
    double      unixday_2 = sstd::tm2unixday(c_tm);
    printf("GMT: %s\n", sstd::tm2str(c_tm).c_str());
    printf("GMT: %s\n", sstd::time2str(c_time_2).c_str());
    printf("unixday: %lf\n", unixday);
    printf("unixday: %lf\n", unixday_2);
    printf("\n");

    struct tm   c_tm_l   = sstd::timeGm2tmLocal(c_time);
//    time_t      c_time_3 = sstd::tmLocal2timeGm(c_tm_l);
    printf("local: %s\n",  sstd::tm2str(c_tm_l).c_str());
//    printf("GMT: %s\n",    sstd::time2str(c_time_3).c_str());
    printf("\n");
    
    time_t c_time_yday  = sstd::yday2time(c_tm.tm_year+1900, c_tm.tm_yday+1);
    printf("GMT: %s\n",   sstd::time2str(c_time_yday).c_str());
    struct tm c_tm_yday = sstd::yday2tm(c_tm.tm_year+1900, c_tm.tm_yday+1);
    printf("GMT: %s\n",   sstd::tm2str(c_tm_yday).c_str());
    printf("\n");

    struct timeval time_sec_micro = sstd::getTimeval();
    printf("timeval: %lf\n",(time_sec_micro.tv_sec)+(time_sec_micro.tv_usec*1.0E-6));

    sstd::print(c_tm_yday);
    sstd::printn(c_tm_yday);
    sstd::printn_all(c_tm_yday);
}

TEST(time, theOthers){
    TEST_time();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(time, time2tm){
}
TEST(time, tm2time){
}
TEST(time, time2unixday){
}
TEST(time, tm2unixday){
}
TEST(time, tm2str){
}
TEST(time, time2str){
}
TEST(time, timeGm2tmLocal){
}
TEST(time, tmLocal2timeGm){
//  time_t c_time = time(0); // get current time
    time_t c_time = 1619108282;
    // local: 2021-04-23 01:18:02
    // GMT: 2021-04-22 16:18:02
    
    struct tm c_tm_l   = sstd::timeGm2tmLocal(c_time);
    time_t    c_time_g = sstd::tmLocal2timeGm(c_tm_l);
//  std::string t_l = sstd::ssprintf("local: %s", sstd::tm2str(c_tm_l).c_str());
    std::string t_g = sstd::ssprintf("GMT: %s", sstd::time2str(c_time_g).c_str());
    
//  ASSERT_STREQ("local: 2021-04-23 01:18:02", t_l.c_str()); // Because of the local time depends on the area defined in the system, this line is difficult to test.
    ASSERT_STREQ("GMT: 2021-04-22 16:18:02",   t_g.c_str());
}
TEST(time, yday2time){
}
TEST(time, yday2tm){
}
TEST(time, getTimeval){
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------

