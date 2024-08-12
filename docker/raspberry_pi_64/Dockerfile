FROM ghcr.io/admiswalker/raspios_full_arm64_2022-04-04_bullseye:2024-08-12-update

#RUN apt update && \
#    apt upgrade -y
RUN apt install -y build-essential \
    coreutils \
    make \
    gcc \
    g++ \
    cmake \
    python3-pip \
    python3-numpy \
    python3-matplotlib \
    time
RUN apt clean

