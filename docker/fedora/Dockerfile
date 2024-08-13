FROM fedora:40

RUN dnf -y update && dnf clean all
RUN dnf -y install \
    coreutils \
    make \
    gcc \
    g++ \
    cmake \
    python3-numpy \
    python3-matplotlib \
    time \
    && dnf clean all

