#pragma once

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
