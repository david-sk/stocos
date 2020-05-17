FROM debian:buster
RUN apt-get update -y 
RUN apt-get install -y make git libcppunit-dev libjsoncpp-dev libjsoncpp1 libboost-log-dev libboost-program-options-dev libboost-iostreams-dev libmongoclient-dev libmongoclient0 g++-8  doxygen sudo 
RUN rm -rf /var/cache/apk/*
COPY . /app
RUN cd /app && make all