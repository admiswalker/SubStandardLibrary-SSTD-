#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd{
    int system(const        char* cmd);
    int system(const std::string& cmd);

    int system_stdout(std::string& ret, const        char* cmd);
    int system_stdout(std::string& ret, const std::string& cmd);
    
    int system_stderr(std::string& ret, const        char* cmd);
    int system_stderr(std::string& ret, const std::string& cmd);
    
    int system_stdout_stderr(std::string& ret, const        char* cmd);
    int system_stdout_stderr(std::string& ret, const std::string& cmd);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Below functions are the not recommended to use. (Below functions will be delete on sstd ver 3.x.x).

namespace sstd{
    std::string system_stdout(const        char* cmd);
    std::string system_stdout(const std::string& cmd);
    
    std::string system_stderr(const        char* cmd);
    std::string system_stderr(const std::string& cmd);
    
    std::string system_stdout_stderr(const        char* cmd);
    std::string system_stdout_stderr(const std::string& cmd);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
