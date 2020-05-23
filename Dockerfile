FROM debian:buster

## Install dependances
RUN apt-get update -y
RUN apt-get install -y --no-install-recommends build-essential
RUN apt-get install -y --no-install-recommends apt-utils
RUN apt-get install -y --no-install-recommends dialog
RUN apt-get install -y --no-install-recommends sudo
RUN apt-get install -y --no-install-recommends cmake
RUN apt-get install -y --no-install-recommends git
RUN apt-get install -y --no-install-recommends libcppunit-dev
RUN apt-get install -y --no-install-recommends libjsoncpp-dev
RUN apt-get install -y --no-install-recommends libjsoncpp1
RUN apt-get install -y --no-install-recommends libboost-log-dev
RUN apt-get install -y --no-install-recommends libboost-program-options-dev
RUN apt-get install -y --no-install-recommends libboost-iostreams-dev
RUN apt-get install -y --no-install-recommends libmongoclient-dev
RUN apt-get install -y --no-install-recommends libmongoclient0
RUN apt-get install -y --no-install-recommends g++-8
RUN apt-get install -y --no-install-recommends doxygen
RUN apt-get install -y --no-install-recommends libargtable2-dev
RUN apt-get install -y --no-install-recommends libmicrohttpd-dev
RUN apt-get install -y --no-install-recommends libhiredis-dev
RUN apt-get install -y --no-install-recommends python3.7
RUN apt-get install -y --no-install-recommends clang-format
RUN apt-get install -y --no-install-recommends pkg-config
RUN apt-get install -y --no-install-recommends libcurl4
RUN apt-get install -y --no-install-recommends libcurl4-gnutls-dev
RUN apt-get install -y --no-install-recommends cppcheck

RUN rm -rf /var/cache/apk/*

## Compilation
COPY . /app
RUN cd /app && make all