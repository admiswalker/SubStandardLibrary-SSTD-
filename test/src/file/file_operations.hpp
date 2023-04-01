#pragma once


//--------------------------------------------------------------------------------------------------------

TEST(file_operations, file_size){
    const char* path = "main.cpp";

    uint64 ret_size=0ull;
    bool ret = sstd::file_size(ret_size, path);
    ASSERT_TRUE(ret);

    //uint64 size_ans = std::stoull(sstd::system_stdout(sstd::ssprintf("ls -al %s | cut -d ' ' -f 5", path))); // failed on alpine linux (cut command -d ' ' is not work well)
    uint64 size_ans = std::stoull(sstd::split(sstd::system_stdout(sstd::ssprintf("ls -al %s", path)), ' ')[4]);
    ASSERT_EQ(ret_size, size_ans);
}
/*
TEST(file_operations, file_size_False){
    const char* path = "Not_existing_file_path_aslkgjklasjgla";

    uint64 ret_size=0ull;
    bool ret = sstd::file_size(ret_size, path);
    ASSERT_FALSE(ret);
}
*/

//--------------------------------------------------------------------------------------------------------
