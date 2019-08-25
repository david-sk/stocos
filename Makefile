#
# @Author: Jxtopher
# @License: *
# @Date: 2018-10
# @Version: 1
# @Description: Makefile
#
MAKEFLAGS += --no-print-directory

all : 
	@cd build && cmake ..
	@cd build && make
	./build/stocos-Release

test:
	@cd build && cmake ..
	@cd build && make
	@cd build && make test