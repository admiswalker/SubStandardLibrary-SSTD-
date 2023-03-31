#define DEBUG
//#define use_sstd_pause        // Enable to switch "Pause" or "Not Pause" by "#define UseSysPause".
#define use_sstd_pauseIfWin32    // Enable to switch "Pause" or "Not Pause" by "#define UsePauseIfWin32".
#ifdef _WIN32
    #include "./sstd/sstd.hpp"
#else
    #include <sstd/sstd.hpp>
#endif

#include <gtest/gtest.h>

//-----------------------------------------------------------------------------------------------------------------------------------------------

#include "test/check_multiple_definition.hpp" // Trigger a compilation error if there are multiple definitions. In order not to occor "multiple definition error" when including <sstd/sstd.hpp> from multi file.

//*
// Remove comment out when you test it.
#include "test/cast/typeConversion.hpp"

#include "test/container/matrixContainer_binary/bmat.hpp"    // <- Needed to modify test.
#include "test/container/matrixContainer_colMajor/mat_c.hpp" // <- Needed to modify test.
#include "test/container/matrixContainer_colMajor/ope.hpp"   // <- Needed to modify test.
#include "test/container/matrixContainer_rowMajor/mat_r.hpp" // <- Needed to modify test.
#include "test/container/vector/slice.hpp"
#include "test/container/vector/stdVector_expansion.hpp" // stdVector_expansion of operators
#include "test/container/vector/vec_manipulation.hpp"
#include "test/container/vector/vvec.hpp"

#include "test/definitions/typeDef.hpp" // <- Needed to modify test.
#include "test/definitions/typeNum.hpp"

#include "test/file/cp.hpp"
#include "test/file/csv.hpp"
#include "test/file/file.hpp"
#include "test/file/file_c.hpp" // <- Needed to modify test.
#include "test/file/file_operations.hpp"
#include "test/file/glob.hpp"
#include "test/file/mkdir.hpp" // <- Needed to modify test.
#include "test/file/path.hpp"
#include "test/file/read_write.hpp"
#include "test/file/tinyInterpreter.hpp"

#include "test/math/hashFnc_of_MD5_SHA1_SHA2/hashSum.hpp"
#include "test/math/hashFnc_of_MD5_SHA1_SHA2/sstd_md5_sha1_sha2_wrapper.hpp"
#include "test/math/math.hpp"

#include "test/memory/unique_void_ptr.hpp"
#include "test/memory/void_ptr_obj.hpp"

#include "test/print/pdbg.hpp"
#include "test/print/print_printn_printn_all.hpp" // void pdbg(){ printf("======p\n"); } // #define DEBUG を定義しない場合でも，マクロでこの名前は使えなくなるので，名前空間を汚しており，本当はよくない．

#include "test/python/c2py.hpp"

#include "test/string/encode_decode.hpp"
#include "test/string/strEdit.hpp"
#include "test/string/strmatch.hpp"
#include "test/string/utf8.hpp"

#include "test/sys/status.hpp"
#include "test/sys/system.hpp"

#include "test/time/time.hpp"
#include "test/time/measureTime.hpp"
//*/

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
    ::testing::InitGoogleTest(&argc, argv);
    
    auto ret = RUN_ALL_TESTS();

    printf("\n");
    printf("■ measureTime_stop----------------\n");
    sstd::measureTime_stop_print(timem);
    sstd::pauseIfWin32();
    return ret;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

