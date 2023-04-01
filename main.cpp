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
    sstd::rm("tmp/test");
    
    std::string base_path = "./tmp/make/test/src";
    std::vector<std::string> vExePath;
    
    // Testing binaries
    //*
    vExePath.push_back(base_path+"/cast/typeConversion.exe"                     );
    vExePath.push_back(base_path+"/container/matrixContainer_binary/bmat.exe"   );
    vExePath.push_back(base_path+"/container/matrixContainer_colMajor/mat_c.exe");
    vExePath.push_back(base_path+"/container/matrixContainer_colMajor/ope.exe"  );
    vExePath.push_back(base_path+"/container/matrixContainer_rowMajor/mat_r.exe");
    vExePath.push_back(base_path+"/container/vector/slice.exe"                  );
    vExePath.push_back(base_path+"/container/vector/stdVector_expansion.exe"    );
    vExePath.push_back(base_path+"/container/vector/vec_manipulation.exe"       );
    vExePath.push_back(base_path+"/container/vector/vvec.exe"                   );
    vExePath.push_back(base_path+"/definitions/typeDef.exe"                     );
    vExePath.push_back(base_path+"/definitions/typeNum.exe"                     );
    vExePath.push_back(base_path+"/file/cp.exe"                                 );
    vExePath.push_back(base_path+"/file/csv.exe"                                );
    vExePath.push_back(base_path+"/file/file.exe"                               );
    vExePath.push_back(base_path+"/file/file_c.exe"                             );
    vExePath.push_back(base_path+"/file/glob.exe"                               );
    vExePath.push_back(base_path+"/file/mkdir.exe"                              );
    vExePath.push_back(base_path+"/file/mv.exe"                                 );
    vExePath.push_back(base_path+"/file/path.exe"                               );
    vExePath.push_back(base_path+"/file/read_write.exe"                         );
    vExePath.push_back(base_path+"/file/rm.exe"                                 );
    vExePath.push_back(base_path+"/file/tinyInterpreter.exe"                    );
    vExePath.push_back(base_path+"/math/math.exe"                               );
    vExePath.push_back(base_path+"/math/signal.exe"                             );
    vExePath.push_back(base_path+"/math/hashFnc_of_MD5_SHA1_SHA2/hashSum.exe"   );
    vExePath.push_back(base_path+"/math/hashFnc_of_MD5_SHA1_SHA2/sstd_md5_sha1_sha2_wrapper.exe");
    vExePath.push_back(base_path+"/memory/unique_void_ptr.exe"                  );
    vExePath.push_back(base_path+"/memory/void_ptr_obj.exe"                     );
    vExePath.push_back(base_path+"/print/pdbg.exe"                              );
    vExePath.push_back(base_path+"/print/print_printn_printn_all.exe"           );
    vExePath.push_back(base_path+"/python/c2py.exe"                             );
    vExePath.push_back(base_path+"/string/encode_decode.exe"                    );
    vExePath.push_back(base_path+"/string/strEdit.exe"                          );
    vExePath.push_back(base_path+"/string/strmatch.exe"                         );
    vExePath.push_back(base_path+"/string/utf8.exe"                             );
    vExePath.push_back(base_path+"/sys/status.exe"                              );
    vExePath.push_back(base_path+"/sys/system.exe"                              );
    vExePath.push_back(base_path+"/time/measureTime.exe"                        );
    vExePath.push_back(base_path+"/time/time.exe"                               );
    //*/
    
    int ret = gtest_parallel::run_tests(vExePath);

    printf("\n");
    printf("■ measureTime_stop----------------\n");
    sstd::measureTime_stop_print(timem);
    sstd::pauseIfWin32();
    return ret;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
