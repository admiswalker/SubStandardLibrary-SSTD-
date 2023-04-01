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
TEST_TMP_PATH := $(BASE_PATH)/$(TEMP_DIR)/$(TEST_SRC_DIR)

TEST_SRCS    := $(shell find $(TEST_SRC_PATH) -type f -name '*.cpp')
TEST_HEADS   := $(shell find $(TEST_SRC_PATH) -type f -name '*.hpp')
TEST_PY      := $(shell find $(TEST_SRC_PATH) -type f -name '*.py' )
TEST_EXES    := $(patsubst $(TEST_SRC_PATH)%, $(TEST_TMP_PATH)%, $(patsubst %.cpp, %.exe, $(TEST_SRCS)))
TEST_DEPS    := $(patsubst $(TEST_SRC_PATH)%, $(TEST_TMP_PATH)%, $(patsubst %.cpp, %.d,   $(TEST_SRCS)))

#DEPS_OLD  = $(addprefix $(TEST_TMP_PATH)/, $(patsubst %.cpp, %.d, $(TEST_SRCS)))
DEPS       = $(patsubst $(TEST_SRC_PATH)%, $(TEST_TMP_PATH)%, $(patsubst %.cpp, %.d, $(TEST_SRCS)))

#aa:
#	@echo $(DEPS)
#	@echo $(TEST_TMP_PATH)
#	@echo $(TEST_SRC_PATH)
#	@echo $(TEST_TMP_PATH)
#	@echo "hello"
#	@echo $(TEST_EXES)
#	@echo ""
#	@echo ""
#	@echo $(TEST_TMP_PATH)

#all: $(DEPS)
all:
	@echo $(DEPS)

#MAKE_TEST_EXE: $(TEST_EXES) $(TEST_SRCS)
#	@echo $(TEST_EXES)


#../tmp/make/test/src/cast/typeConversion.exe: ../test/src/cast/typeConversion.cpp
#	@echo ""
#	mkdir -p $(dir $@);\
#	$(CXX) -o $@ $< $(CFLAGS)


#$(TEST_EXES): $(LIB_GOOGLETEST) $(LIB_GTEST_PARALLEL_MAIN) $(LIB_SSTD)
#$(TEST_TMP_PATH)/%.exe: %.cpp $(TEST_SRCS) $(TEST_HEADS) $(LIB_GOOGLETEST) $(LIB_GTEST_PARALLEL_MAIN) $(LIB_SSTD)
#	@echo ""
#	mkdir -p $(dir $@);\
#	$(CXX) -o $@ $< $(CFLAGS)


# 「-include $(DEPS)」により，必要な部分のみ分割で再コンパイルを行うため，依存関係を記した *.d ファイルに生成する
#$(TEST_DEPS): %.cpp
#$(TEST_TMP_PATH)/%.d: %.cpp
%.d:
#../tmp/make/test/src/%.d: %.cpp
	@echo ""
	@echo "---------------"
	@echo ""
	@echo $(DEPS_OLD)
	@echo ""
#	mkdir -p $(dir $@);\
#	$(CXX) $< -MM $(CFLAGS)> $(patsubst $(TEST_SRC_PATH)%, $(TEST_TMP_PATH)%, $*).d
#	mkdir -p $(dir $@);\
#	$(CXX) $< -MM $(CFLAGS)\
#	| sed 's/$(notdir $*)\.o/$(subst /,\/,$(patsubst %.d,%.o,$@) $@)/' > $@;\
#	[ -s $@ ] || rm -f $@
	@echo $*	# for debug
	@echo $@	# for debug
	@echo $<
	@echo $(notdir $*).d
	@echo $(dir $*)
	@echo $(patsubst $(TEST_SRC_PATH)%, $(TEST_TMP_PATH)%, $*).d



-include $(DEPS)
#-include $(DEPS_OLD)


#../test/src/container/matrixContainer_colMajor/ope
#../tmp/make/test/src/../test/src/container/matrixContainer_colMajor/ope.d

