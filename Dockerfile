FROM debian:buster

## Install dependances
RUN apt-get update -y
RUN apt-get install -y build-essential
RUN apt-get install -y apt-utils
RUN apt-get install -y dialog
RUN apt-get install -y sudo
RUN apt-get install -y cmake
RUN apt-get install -y git
RUN apt-get install -y libcppunit-dev
RUN apt-get install -y libjsoncpp-dev
RUN apt-get install -y libjsoncpp1
RUN apt-get install -y libboost-log-dev
RUN apt-get install -y libboost-program-options-dev
RUN apt-get install -y libboost-iostreams-dev
RUN apt-get install -y libmongoclient-dev
RUN apt-get install -y libmongoclient0
RUN apt-get install -y g++-8
RUN apt-get install -y doxygen
RUN apt-get install -y libargtable2-dev
RUN apt-get install -y libmicrohttpd-dev
RUN apt-get install -y libhiredis-dev
RUN apt-get install -y python3.7
RUN apt-get install -y clang-format
RUN apt-get install -y pkg-config
RUN apt-get install -y libcurl4
RUN apt-get install -y libcurl4-gnutls-dev

RUN rm -rf /var/cache/apk/*

## Compilation
COPY . /app
RUN cd /app && make all