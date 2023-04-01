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
#       + tmpMake/
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

# Name of generate file: 生成ファイル名
TARGET = libsstd.a

# Options: コンパイルオプション
CFLAGS  = -std=gnu++0x
CFLAGS += -Wall
CFLAGS += -O3

#============================================================

SRC_DIR := ./src

CPP_SRCS      := $(shell find $(SRC_DIR) -type f -name '*.cpp')
HPP_SRCS      := $(shell find $(SRC_DIR) -type f -name '*.hpp')
H_SRCS        := $(shell find $(SRC_DIR) -type f -name '*.h')
BASE_HPP_SRCS := 'sstd.hpp' 'compileOption.hpp'
PY_SRCS       := $(shell find $(SRC_DIR) -type f -name '*.py')

SRCS = $(CPP_SRCS) $(HPP_SRCS) $(H_SRCS) $(BASE_HPP_SRCS) $(PY_SRCS)

TEMP_DIR = tmpMake
OBJS     = $(addprefix $(TEMP_DIR)/, $(patsubst %.cpp, %.o, $(CPP_SRCS)))
#OBJS     = $(addprefix $(TEMP_DIR)/, $(CPP_SRCS:%.cpp=%.o))#別表記

DEPS  = $(addprefix $(TEMP_DIR)/, $(patsubst %.cpp, %.d, $(CPP_SRCS)))
#DEPS  = $(addprefix $(TEMP_DIR)/, $(CPP_SRCS:%.cpp=%.d))#別表記


# $(TARGET) を生成する
# .a ファイルとしてオブジェクトファイルを梱包する
$(TARGET): $(OBJS)
	@echo "\n------------------------------------------------------------"
	@echo   "Build begin: libsstd.a\n"
	@echo   "CFLAGS: \n$(CFLAGS)\n"
	@mkdir -p ./lib
	@`/usr/bin/time -f "Build time: %e sec ($@)\n" ar rc ./lib/$(TARGET) $(OBJS);`
#	ar rc ./lib/$(TARGET) $(OBJS)
	@(make COPY_heads)
	@echo   "                                        Build end: libsstd.a"
	@echo   "------------------------------------------------------------\n"


.PHONY: COPY_heads
COPY_heads: $(HPP_SRCS) $(H_SRCS) $(PY_SRCS)
	@echo "COPY_heads"
	@mkdir -p ./include/sstd
	@cp LICENSE ./include/sstd/
	@cp $(BASE_HPP_SRCS) ./include/sstd/
	@echo $^ | xargs -n 1 | xargs -I {} cp {} ./include/sstd --parents -P


# 各ファイルの分割コンパイル
$(TEMP_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@`/usr/bin/time -f "Build time: %e sec ($<)" $(CXX) $< -c -o $@ $(CFLAGS);`
#	$(CXX) $< -c -o $@ $(CFLAGS);


# 「-include $(DEPS)」により，必要な部分のみ分割で再コンパイルを行うため，依存関係を記した *.d ファイルに生成する
$(TEMP_DIR)/%.d: %.cpp
	@mkdir -p $(dir $@)
	@`/usr/bin/time -f "Build time: %e sec ($@)" $(CXX) $< -MM $(CFLAGS) | sed 's/$(notdir $*)\.o/$(subst /,\/,$(patsubst %.d,%.o,$@) $@)/' > $@;[ -s $@ ] || rm -f $@;`
#	mkdir -p $(dir $@);\
#	$(CXX) $< -MM $(CFLAGS)\
#	| sed 's/$(notdir $*)\.o/$(subst /,\/,$(patsubst %.d,%.o,$@) $@)/' > $@;\
#	[ -s $@ ] || rm -f $@
#	@echo $*	# for debug
#	@echo $@	# for debug


.PHONY: all
all:
	@(make clean)
	@(make -j)
#	make clean ; \	#別表記
#	make			#別表記


.PHONY: steps
steps:
	@echo $(SRCS) | xargs wc -l


.PHONY: clean
clean:
	-rm -rf $(TEMP_DIR) $(TARGET)
	-rm -rf include
	-rm -rf lib
#	-rm -f $(OBJS) $(DEPS) $(TARGET)


-include $(DEPS)


# $@ : ターゲット名
# $^ : 依存ファイルのリスト
# $< : 最初の依存ファイル

# $@ : ターゲットファイル名
# $% : ターゲットがアーカイブメンバだったときのターゲットメンバ名
# $< : 最初の依存するファイルの名前
# $? : ターゲットより新しいすべての依存するファイル名
# $^ : すべての依存するファイルの名前
# $+ : Makefileと同じ順番の依存するファイルの名前
# $* : サフィックスを除いたターゲットの名前

#	@for header in $^; do\
#		echo $$header;\
#	done

# http://d.hatena.ne.jp/srkzhr/20081216/1229449984
#  パイプで受け取った入力をシェルコマンドとして実行。*1
#  echo 'hoge foo var' | sed 's/^/mkdir /' | sh -x
#  これは以下と等価です。
#  mkdir hoge foo var

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
