#define DEBUG
//#define use_sstd_pause        // Enable to switch "Pause" or "Not Pause" by "#define UseSysPause".
#define use_sstd_pauseIfWin32    // Enable to switch "Pause" or "Not Pause" by "#define UsePauseIfWin32".
#ifdef _WIN32
    #include "./sstd/sstd.hpp"
#else
    #include <sstd/sstd.hpp>
#endif

#include "gtest_parallel/gtest_parallel.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

#include "test/multiple_definition/check_multiple_definition.hpp" // Trigger a compilation error if there are multiple definitions. In order not to occor "multiple definition error" when including <sstd/sstd.hpp> from multi file.

//-----------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char** argv){
    printf("\n");
    printf("+----------------------------------------------------+\n");
    printf("|                                                    |\n");
    printf("|    Welcome to The Sub Standard Library (SSTD) !    |\n");
    printf("|                                                    |\n");
    printf("+----------------------------------------------------+\n");
    printf("\n");
    printf("■ measureTime_start---------------\n\n"); time_m timem; sstd::measureTime_start(timem);
    sstd::rm("tmp/test"); // rm the tmp directory for test
    
    // Testing binaries
    std::vector<std::string> vExePath = gtest_parallel::get_exeList("tmp/make/test/src_test", "*.exe");
    int ret = gtest_parallel::run_tests(vExePath);
    
    printf("\n");
    printf("■ measureTime_stop----------------\n");
    sstd::measureTime_stop_print(timem);
    sstd::pauseIfWin32();
    return ret;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
