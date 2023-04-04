# Options: コンパイルオプション
CFLAGS  = -L../sstd/lib -I../sstd/include -lsstd # sstd
CFLAGS += -L../googletest-master/build/lib -I../googletest-master/googletest/include -lgtest -pthread # google test
CFLAGS += -std=c++11 # CFLAGS += -std=gnu++0x
CFLAGS += -Wall
CFLAGS += -O3

BASE_PATH    := ..
TEST_SRC_DIR := test/src
TEMP_DIR     := tmp/make

TEST_SRC_PATH := $(BASE_PATH)/$(TEST_SRC_DIR)
TEST_TMP_PATH := $(BASE_PATH)/$(TEMP_DIR)/dummy

TEST_SRCS  := $(shell find $(TEST_SRC_PATH) -type f -name '*.cpp')
TEST_HEADS := $(shell find $(TEST_SRC_PATH) -type f -name '*.hpp')
TEST_PY    := $(shell find $(TEST_SRC_PATH) -type f -name '*.py' )
TEST_EXES  := $(addprefix $(TEST_TMP_PATH)/, $(patsubst %.cpp, %.exe, $(TEST_SRCS)))
TEST_DEPS  := $(addprefix $(TEST_TMP_PATH)/, $(patsubst %.cpp, %.d, $(TEST_SRCS)))

LIB_SSTD       := ../sstd/lib/libsstd.a
LIB_GOOGLETEST := ../googletest-master/build/lib/libgtest.a

TEST_LIST := ../tests_list_for_build_and_run.txt


all: $(DEPS) $(TEST_EXES)


$(TEST_TMP_PATH)/%.exe: %.cpp $(LIB_SSTD) $(LIB_GOOGLETEST)
	@mkdir -p $(dir $@)
	@/bin/bash ./build_exe.sh $@ $< $(CXX) "$(CFLAGS)" $(TEST_LIST)
#	@`/usr/bin/time -f "Build time: %e sec ($<)" $(CXX) -o $@ $< $(CFLAGS);`


# 「-include $(DEPS)」により，必要な部分のみ分割で再コンパイルを行うため，依存関係を記した *.d ファイルに生成する
$(TEST_TMP_PATH)/%.d: %.cpp
	@mkdir -p $(dir $@)
	@`/usr/bin/time -f "Build time: %e sec ($(dir $<)$(notdir $@))" $(CXX) $< -MM $(CFLAGS) > $@;`


.PHONY: steps
steps:
	@echo $(TEST_SRCS) $(TEST_HEADS) $(TEST_PY) ../test_c2py.py | xargs wc -l


include $(TEST_DEPS)
