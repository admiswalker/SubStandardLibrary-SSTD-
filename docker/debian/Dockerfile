FROM debian:12

RUN apt-get update && apt-get install -y \
    coreutils \
    make \
    gcc \
    g++ \
    cmake \
    python3-numpy \
    python3-matplotlib \
    time

RUN apt-get clean && rm -rf /var/lib/apt/lists/*
