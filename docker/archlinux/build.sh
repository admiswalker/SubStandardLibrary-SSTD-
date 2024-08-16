#!/bin/bash
SCRIPT_DIR=`cd $(dirname ${BASH_SOURCE:-$0}); pwd`
docker build -t sstd_archlinux $SCRIPT_DIR

