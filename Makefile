# The MIT License (MIT)
# Copyright (c) 2017 ADMIS_Walker (Blog: https://admiswalker.blogspot.jp/)

# Example directory structure: ディレクトリ構成例
#
# root/
#   |
#   + main.cpp (your code)
#   |
#   + Makefile (your makefile): This file
#   |
#   + sstd/
#       |
#       + sstd.hpp (head file that you need to include)
#       |
#       + Makefile (Makefile that you need to '$ make')
#       |
#       + make_temp/
#       |   |
#       |   + src/
#       |      |
#       |      + *.d
#       |      |
#       |      + *.o (object files that you need to link "./sstd/make_temp/*.o")
#       |
#       + src/
#           |
#           + *.cpp
#           |
#           + *.hpp
#           |
#           + *.h

# .o: Objects file
# .d: Depends file

#============================================================

# Please set each item: 各項目を設定してください

# Source files
SRCS = ./main.cpp

# Name of generate file: 生成ファイル名
TARGET = exe

# Options: コンパイルオプション
CFLAGS  = -L./sstd/lib -I./sstd/include -lsstd
CFLAGS += -std=gnu++0x
CFLAGS += -Wall
CFLAGS += -O3

#============================================================

$(TARGET): FORCE $(SRCS)
	@echo -e "\n============================================================\n"
	@echo -e "SRCS: \n$(SRCS)\n"
	@echo -e "OBJS: \n$(OBJS)\n"
	@echo -e "CFLAGS: \n$(CFLAGS)"
	@echo -e "\n============================================================\n"
	$(CXX) -o $(TARGET) $(SRCS) $(CFLAGS)
	@echo ""


.PHONY: FORCE
FORCE:
	@(cd ./sstd; make -j)


.PHONY: all
all:
	@(make clean)
	@(make -j)


patch            := *.stackdump
patch_txt_exists := $(shell find -name $(patch))
.PHONY: clean
clean:
	-rm -rf $(TARGET)
	@(cd ./sstd; make clean)
	-rm -rf ./test_fopen.txt
	-rm -rf ./test_mkdir
	$(if $(patch_txt_exists) ,$(rm *.stackdump))


.PHONY: steps
steps: $(SRCS)
	@(cd ./sstd; make steps)
	@echo ""
	@echo "$^" | xargs wc -l
