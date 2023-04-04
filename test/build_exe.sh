#!/bin/bash

OWN_DIR=`dirname $0`
CALL_DIR=`pwd -P`

BUILD_DST=$1 # ../tmp/make/dummy/../test/src/cast/typeConversion.exe
BUILD_SRC=$2 # ../test/src/cast/typeConversion.cpp
CXX=$3
CFLAGS=$4
TEST_LIST=$5

# for debug
#BUILD_DST=../tmp/make/dummy/../test/src/cast/typeConversion.exe
#BUILD_SRC=../test/src/cast/typeConversion.cpp
#CXX=g++
#CFLAGS="-L../sstd/lib -I../sstd/include -lsstd -L../googletest-master/build/lib -I../googletest-master/googletest/include -lgtest -pthread -std=c++11 -Wall -O3"
#TEST_LIST=../tests_list_for_build_and_run.txt

# fix path
BUILD_DST=$(realpath --relative-to=${CALL_DIR} ${BUILD_DST})
BUILD_SRC=$(realpath --relative-to=${CALL_DIR} ${BUILD_SRC})

# for debug
#echo BUILD_DST: ${BUILD_DST}
#echo BUILD_SRC: ${BUILD_SRC}
#echo CXX: ${CXX}
#echo CFLAGS: ${CFLAGS}

#echo ${TEST_LIST}
#SEARCH_WORD="typeConversion.cpp"
#SEARCH_WORD="test"
TEST_LIST_STR=$(cat ${TEST_LIST} | cut -d "#" -f 1) # rm comments
SEARCH_WORD=${BUILD_SRC}

if [[ "${TEST_LIST_STR}" == *"${SEARCH_WORD}"* ]]; then
    #echo "contain search word"
    /usr/bin/time -f "Build time: %e sec (${BUILD_SRC})" ${CXX} -o ${BUILD_DST} ${BUILD_SRC} ${CFLAGS}
else
    #echo "Not contain search word"
    : # do nothing
fi
   
   


