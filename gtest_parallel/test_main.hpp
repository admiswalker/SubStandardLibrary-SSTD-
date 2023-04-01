#pragma once
#include <gtest/gtest.h>


#define EXECUTE_TESTS()                         \
    int main(int argc, char** argv){            \
        ::testing::InitGoogleTest(&argc, argv); \
                                                \
        auto ret = RUN_ALL_TESTS();             \
                                                \
        return ret;                             \
    }


#define SET_TMP_DIR_NAME()                                              \
    std::string tmpDir = std::string("./tmp/test/")+test_info_->test_case_name()+"_"+test_info_->name()

