#
# @Author: Jxtopher
# @License: *
# @Date: 2018-10
# @Version: 1
# @Description: Makefile
#
.PHONY: all test
MAKEFLAGS += --no-print-directory

all : 
	@hash cmake 2> /dev/null || sudo apt-get install -y cmake 2> /dev/null || ( echo >&2 "Please install cmake" ; exit -1)
	#build-essential
	@cd build && cmake ..
	@cd build && make
	./build/stocos-Release

test:
	@cd build && cmake ..
	@cd build && make
	@cd build && make test