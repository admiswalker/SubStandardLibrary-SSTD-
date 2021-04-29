#pragma once


//--------------------------------------------------------------------------------------------------------

//TEST(file, fopen_char){
//}
//TEST(file, fopen_str){
//}

//---

TEST(file, popen_char){
    const char* pCmd = "echo \"Hello sstd::popen()!\"";
    
    sstd::file fp;
    ASSERT_TRUE( fp.popen(pCmd,"r") );
    
    char buf[128];
    fp.fgets(buf, sizeof(buf)); buf[20] = '\0';
    ASSERT_STREQ(buf, "Hello sstd::popen()!");
}
TEST(file, popen_str){
    std::string cmd = "echo \"Hello sstd::popen()!\"";
    
    sstd::file fp;
    ASSERT_TRUE( fp.popen(cmd.c_str(),"r") );
    
    char buf[128];
    fp.fgets(buf, sizeof(buf)); buf[20] = '\0';
    ASSERT_STREQ(buf, "Hello sstd::popen()!");
}

//---

//TEST(file, close){
//}

//--------------------------------------------------------------------------------------------------------

//TEST(file, fgets){
//}
//TEST(file, fread){
//}
//TEST(file, fscan){
//}
//TEST(file, fseek){
//}
//TEST(file, fsize){
//}
//TEST(file, ftell){
//}
//TEST(file, fwrite){
//}

//--------------------------------------------------------------------------------------------------------
