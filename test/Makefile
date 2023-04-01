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


all: $(DEPS) $(TEST_EXES)


$(TEST_TMP_PATH)/%.exe: %.cpp
	@echo ""
	mkdir -p $(dir $@);\
	$(CXX) -o $@ $< $(CFLAGS)


# 「-include $(DEPS)」により，必要な部分のみ分割で再コンパイルを行うため，依存関係を記した *.d ファイルに生成する
$(TEST_TMP_PATH)/%.d: %.cpp
	@echo ""
	@echo "---------------"
	@echo ""
	@echo $(DEPS_OLD)
	@echo ""
	mkdir -p $(dir $@)
	$(CXX) $< -MM $(CFLAGS) > $@
#	@echo $*	# for debug
#	@echo $@	# for debug


include $(TEST_DEPS)
