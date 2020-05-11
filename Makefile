#
# @Author: Jxtopher
# @License: *
# @Date: 2018-10
# @Version: 1
# @Description: Makefile
#
.PHONY: all test tools-required
MAKEFLAGS += --no-print-directory

all : tools-required
	@cd build && cmake ..
	@cd build && make

test: tools-required
	@cd build && cmake ..
	@cd build && make
	@cd build && make test

run:
	./build/stocos -c ./configuration/stocos-TSP.json

checks:
	@cd build && make cppcheck

tools-required:
	@#build-essential
	@hash cmake 2> /dev/null || sudo apt-get install -y cmake 2> /dev/null || ( echo >&2 "Please install cmake" ; exit -1)