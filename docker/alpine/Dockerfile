FROM crystallang/crystal:latest-alpine

RUN apk update && apk add --no-cache \
    make \
    gcc \
    g++ \
    cmake \
    python3 \
    py3-pip \
    py3-numpy \
    py3-matplotlib

RUN ln -s /usr/bin/python3.10 /usr/bin/python

