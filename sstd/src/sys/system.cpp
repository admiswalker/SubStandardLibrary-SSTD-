#include <stdlib.h>
#include <string>

#include "system.hpp"
#include "../print/pdbg.hpp"
#include "../file/file.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

int sstd::system(const        char* cmd){ return ::system(cmd        ); }
int sstd::system(const std::string& cmd){ return ::system(cmd.c_str()); }

//---

int sstd::system_stdout(std::string& ret, const char* cmd){
    std::string cmd_out = cmd + std::string(" >&1 2>/dev/null"); // >&1: get stdout, throw away stderr.
    
    sstd::file fp;
    if(!fp.popen(cmd_out.c_str(), "r")){ sstd::pdbg_err("sstd::file::popen() was failed.\n"); return -1; }
    
    char buf[1024];
    while(fp.fgets(buf, 1024) != NULL){ ret+=buf; }
    
    return fp.close();
}
int sstd::system_stdout(std::string& ret, const std::string& cmd){
    return sstd::system_stdout(ret, cmd.c_str());
}

//---

int sstd::system_stderr(std::string& ret, const char* cmd){
    std::string cmd_out = cmd + std::string(" 2>&1 1>/dev/null"); // >&1: get stdout, throw away stderr.
    
    sstd::file fp;
    if(!fp.popen(cmd_out.c_str(), "r")){ sstd::pdbg_err("sstd::file::popen() was failed.\n"); return -1; }
    
    char buf[1024];
    while(fp.fgets(buf, 1024) != NULL){ ret+=buf; }
    
    return fp.close();
}
int sstd::system_stderr(std::string& ret, const std::string& cmd){
    return sstd::system_stderr(ret, cmd.c_str());
}

//---

int sstd::system_stdout_stderr(std::string& ret, const char* cmd){
    std::string cmd_out_err = cmd + std::string(R"( 2>&1)"); // 2>&1: redirecting stderr to stdout.
    sstd::file fp;
    if(!fp.popen(cmd_out_err.c_str(), "r")){ sstd::pdbg_err("sstd::file::popen() was failed.\n"); return -1; }
    
    char buf[1024];
    while(fp.fgets(buf, 1024) != NULL){ ret+=buf; }
    
    return fp.close();
}
int sstd::system_stdout_stderr(std::string& ret, const std::string& cmd){
    return sstd::system_stdout_stderr(ret, cmd.c_str());
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Below functions are the not recommended to use. (Below functions will be delete on sstd ver 3.x.x).

std::string sstd::system_stdout(const char* cmd){
    std::string cmd_out = cmd + std::string(" >&1 2>/dev/null"); // >&1: get stdout, throw away stderr.
    
    sstd::file fp;
    if(!fp.popen(cmd_out.c_str(), "r")){ sstd::pdbg_err("sstd::file::popen() was failed.\n"); return ""; }
    
    std::string ret;
    char buf[1024];
    while(fp.fgets(buf, 1024) != NULL){ ret+=buf; }
    
    return ret;
}
std::string sstd::system_stdout(const std::string& cmd){
    return sstd::system_stdout(cmd.c_str());
}

std::string sstd::system_stderr(const char* cmd){
    std::string cmd_out = cmd + std::string(" 2>&1 1>/dev/null"); // >&1: get stdout, throw away stderr.
    
    sstd::file fp;
    if(!fp.popen(cmd_out.c_str(), "r")){ sstd::pdbg_err("sstd::file::popen() was failed.\n"); return ""; }
    
    std::string ret;
    char buf[1024];
    while(fp.fgets(buf, 1024) != NULL){ ret+=buf; }
    
    return ret;
}
std::string sstd::system_stderr(const std::string& cmd){
    return sstd::system_stderr(cmd.c_str());
}

std::string sstd::system_stdout_stderr(const char* cmd){
    std::string cmd_out_err = cmd + std::string(R"( 2>&1)"); // 2>&1: redirecting stderr to stdout.
    sstd::file fp;
    if(!fp.popen(cmd_out_err.c_str(), "r")){ sstd::pdbg_err("sstd::file::popen() was failed.\n"); return ""; }
    
    std::string ret;
    char buf[1024];
    while(fp.fgets(buf, 1024) != NULL){ ret+=buf; }
    
    return ret;
}
std::string sstd::system_stdout_stderr(const std::string& cmd){
    return sstd::system_stdout_stderr(cmd.c_str());
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
