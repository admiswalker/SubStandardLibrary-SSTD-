# The MIT License (MIT)
# Copyright (c) 2017 ADMIS_Walker (Blog: https://admiswalker.blogspot.jp/)

# Example directory structure: ディレクトリ構成例
#
# root/
#   |
#   + main.cpp (your code)
#   |
#   + Makefile (your makefile)
#   |
#   + sstd/
#       |
#       + sstd.hpp (head file that you need to include)
#       |
#       + Makefile (Makefile that you need to '$ make'): This file
#       |
#       + make_temp/
#       |   |
#       |   + *.d
#       |   |
#       |   + *.o (object files that you need to link "./sstd/make_temp/*.o")
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

# Set files to do "$ make". If you cont line num of header files, you also need to add header files.
# ソースファイルの場所 ($make steps コマンドで，ヘッダファイルの行数もカウントする場合は，
# ヘッダファイルのディレクトリも追加する必要があります．また，拡張子を記述してはいけません)
DIR  = ./*.
DIR += ./src/*.
DIR += ./src/MatrixStore_tmat/*.
DIR += ./src/MatrixStore_bmat/*.

# Name of generate file: 生成ファイル名
TARGET = sstd_lib.a

# Options: コンパイルオプション
CFLAGS  = -std=gnu++0x
CFLAGS += -Wall
CFLAGS += -O3

#============================================================

SRCDIR   = $(patsubst %., %.cpp, $(DIR))
SRCS     = $(wildcard $(SRCDIR))

HDIR     = $(patsubst %., %.h, $(DIR))
HEADS    = $(wildcard $(HDIR))

HPPDIR   = $(patsubst %., %.hpp, $(DIR))
HEADppS  = $(wildcard $(HPPDIR))

TEMP_DIR = make_temp
OBJS     = $(addprefix $(TEMP_DIR)/, $(patsubst %.cpp, %.o, $(SRCS)))
#OBJS     = $(addprefix $(TEMP_DIR)/, $(SRCS:%.cpp=%.o))#別表記

DEPS  = $(addprefix $(TEMP_DIR)/, $(patsubst %.cpp, %.d, $(SRCS)))
#DEPS  = $(addprefix $(TEMP_DIR)/, $(SRCS:%.cpp=%.d))#別表記


# $(TARGET) を生成する
# .a ファイルとしてオブジェクトファイルを梱包する
$(TARGET): $(OBJS)
	@echo -e "\n============================================================\n"
	@echo -e "SRCS: \n$(SRCS)\n"
	@echo -e "OBJS: \n$(OBJS)\n"
	@echo -e "CFLAGS: \n$(CFLAGS)"
	@echo -e "\n============================================================\n"
	ar rc $(TARGET) $(OBJS)
	@echo ""


# 各ファイルの分割コンパイル
$(TEMP_DIR)/%.o: %.cpp
	@echo ""
	mkdir -p $(dir $@);\
	$(CXX) $< -c -o $@ $(CFLAGS)


# 「-include $(DEPS)」により，必要な部分のみ分割で再コンパイルを行うため，依存関係を記した *.d ファイルに生成する
$(TEMP_DIR)/%.d: %.cpp
	@echo ""
	mkdir -p $(dir $@);\
	$(CXX) $< -MM $(CFLAGS)\
	| sed 's/$(notdir $*)\.o/$(subst /,\/,$(patsubst %.d,%.o,$@) $@)/' > $@;\
	[ -s $@ ] || rm -f $@
#	@echo $*	# for debug
#	@echo $@	# for debug


.PHONY: all
all:
	@(make clean)
	@(make)
#	make clean ; \	#別表記
#	make			#別表記


.PHONY: steps
steps: $(SRCS) $(HEADppS) $(HEADS)
	@echo "$^" | xargs wc -l


.PHONY: clean
clean:
	-rm -rf $(TEMP_DIR) $(TARGET)
	-rm -f $(OBJS) $(DEPS) $(TARGET)


-include $(DEPS)


#============================================================
#
#	参考資料: 
#		[1] Makefile 別ディレクトリに中間ファイル & 自動依存関係設定 - 電脳律速: http://d-rissoku.net/2013/06/makefile-%E5%88%A5%E3%83%87%E3%82%A3%E3%83%AC%E3%82%AF%E3%83%88%E3%83%AA%E3%81%AB%E4%B8%AD%E9%96%93%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB-%E8%87%AA%E5%8B%95%E4%BE%9D%E5%AD%98%E9%96%A2%E4%BF%82/
#		[2] Makefileでワイルドカードを使う方法 - nao-bambooの日記: http://tech.chocolatoon.com/entry/2015/09/11/175832
#		[3] Makefileの関数 - Qiita: http://qiita.com/chibi929/items/b8c5f36434d5d3fbfa4a
#		[4] Makeでヘッダファイルの依存関係に対応する - wagavulin's blog: http://blog.wagavulin.jp/entry/20120405/1333629926
#		[5] シンプルで応用の効くmakefileとその解説 - URIN HACK: http://urin.github.io/posts/2013/simple-makefile-for-clang/
#		[6] シェルの初歩の初歩 - One Two.jp: http://www.onetwo.jp/proginfo/pub/unix/sh.htm
#		[7] sedコマンドの備忘録 - Qiita: http://qiita.com/takech9203/items/b96eff5773ce9d9cc9b3
#		[8] ディレクトリ構成図を書くときに便利な記号 - Qiita: http://qiita.com/paty-fakename/items/c82ed27b4070feeceff6
#		[9] https://github.com/T-matsuno07/mtnMakefile/blob/master/makefile
#		[10] プログラムのステップ数をカウントする方法 - nishio-dens's diary: http://nishio.hateblo.jp/entry/20101110/1289398449
#		[11] シェル（bash）のfor文の違いを吸収するMakefileの書き方 - 檜山正幸のキマイラ飼育記: http://d.hatena.ne.jp/m-hiyama/20080724/1216874932
#		[12] Javaのステップ数を数える - kumai@github: http://qiita.com/kumai@github/items/3b9e6f73d71323a1bc1d
