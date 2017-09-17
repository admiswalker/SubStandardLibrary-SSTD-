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
CFLAGS  = -std=gnu++0x
CFLAGS += -Wall
CFLAGS += -O3

LIBS = ./sstd/sstd_lib.a

#============================================================

$(TARGET): $(SRCS) FORCE
	$(CXX) -o $(TARGET) $(SRCS) $(LIBS) $(CFLAGS)


.PHONY: FORCE
FORCE:
	@(cd ./sstd; make)


.PHONY: all
all:
	@(make clean)
	@(make)


.PHONY: clean
clean:
	-rm -rf $(TARGET)
	@(cd ./sstd; make clean)


.PHONY: steps
steps: $(SRCS)
	@echo "$^" | xargs wc -l
	@echo ""
	@(cd ./sstd; make steps)
