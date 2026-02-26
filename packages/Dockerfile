FROM ubuntu:latest

RUN apt update && apt upgrade -y

RUN apt install -y \
  build-essential cmake git ninja-build \
  libssl-dev \
  libcrypto++-dev libcrypto++-doc libcrypto++-utils \
  libgtest-dev \
  python3-pytest python3-pytest-xdist \
  unzip xsltproc doxygen graphviz python3-yaml valgrind astyle

# Build & install gtest
RUN cd /usr/src/gtest && cmake -S . -B build && cmake --build build -j && cmake --install build

# Build & install liboqs
RUN git clone -b main https://github.com/open-quantum-safe/liboqs.git
WORKDIR /liboqs
RUN cmake -S . -B build -GNinja && ninja -C build && ninja -C build install

WORKDIR /app
COPY . .