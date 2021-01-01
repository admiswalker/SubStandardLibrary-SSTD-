#pragma once

namespace sstd{
    int system(const        char* cmd);
    int system(const std::string& cmd);

    std::string system_stdout(const        char* cmd);
    std::string system_stdout(const std::string& cmd);
    
    std::string system_stderr(const        char* cmd);
    std::string system_stderr(const std::string& cmd);
    
    std::string system_stdout_stderr(const        char* cmd);
    std::string system_stdout_stderr(const std::string& cmd);
}
