
# Debian 10 - buster
 
apt-get install build-essential gcc libmongoclient-dev git doxygen graphviz


git clone https://github.com/catchorg/Catch2.git
cd Catch2/
mkdir build
cd build/
cmake .. && make && make install


apt-get install libargtable2-dev libhiredis-dev
cd /opt
git clone https://github.com/cinemast/libjson-rpc-cpp.git
libjson-rpc-cpp/
mkdir build
cd build/
cmake .. && make && make install


