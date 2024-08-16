#!/bin/sh
docker run \
       -u `id -u`:`id -g` \
       -v /etc/group:/etc/group:ro \
       -v /etc/passwd:/etc/passwd:ro \
       -v /etc/shadow:/etc/shadow:ro \
       -v /etc/sudoers.d:/etc/sudoers.d:ro \
       --rm -it --name sstd_fedora \
       -v $PWD:/home -w /home \
       sstd_archlinux:latest /bin/bash

#       --user root \
