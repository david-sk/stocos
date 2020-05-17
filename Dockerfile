FROM debian:buster
RUN apt-get update -y 
RUN apt-get install make git sudo -y
RUN rm -rf /var/cache/apk/*
COPY . /app
RUN cd /app && make all