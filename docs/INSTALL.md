
# Debian 10 - buster

Installation de package :

 apt-get install build-essential gcc libmongoclient-dev git doxygen graphviz pkg-config libjsoncpp-dev libjsoncpp1 libboost-all-dev libmongoclient-dev libmongoclient0 libcppunit-dev

Compilation de Catch2

 git clone https://github.com/catchorg/Catch2.git
 cd Catch2/
 mkdir build
 cd build/
 cmake .. && make && make install

Compilation de json-rpc-cpp

 apt-get install libargtable2-dev libhiredis-dev
 cd /opt
 git clone https://github.com/cinemast/libjson-rpc-cpp.git
 libjson-rpc-cpp/
 mkdir build
 cd build/
 cmake .. && make && make install


