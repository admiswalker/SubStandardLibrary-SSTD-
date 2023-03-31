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

