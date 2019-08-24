#
# @Author: Jxtopher
# @License: *
# @Date: 2018-10
# @Version: 1
# @Description: Makefile
#

CC = g++
CFLAGS = -std=c++1z -Wall -fopenmp -ljsoncpp -lcurl -ljsonrpccpp-common -ljsonrpccpp-client -lboost_program_options -lmongoclient -lboost_system  -lboost_log 	# c++17
#CFLAGS = -std=c++14 -Wall -fopenmp
OFLAGS = #-Os # Optimization flags
GFLAGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Werror -Wno-unused  #-Werror=switch-default   -Wswitch-default
#DFLAGS = -DDEBUG
FLAGS = $(CFLAGS) $(OFLAGS) $(GFLAGS) $(DFLAGS)
EXEC_NAME = stocos

#INCLUDES =
#LIBS =
#OBJ_FILES = fichier_1.o fichier_2.o
#INSTALL_DIR = /usr/bin
#SOURCES_DIR = ./sources/
BUILD_DIR = ./build/

#all : $(EXEC_NAME)

#$(EXEC_NAME): $(SOURCES_DIR)main.cpp
all : ./sources/main.cpp
	$(CC) $(FLAGS) $< -o $(BUILD_DIR)$(EXEC_NAME)

run:
	$(BUILD_DIR)$(EXEC_NAME)
vide:
	# ./build/stocos --problem=0 --instance=instances/OneMax/onemax-50.json --algo=0			# OneMax
	# ./build/stocos --problem=1 --instance=instances/SubSetSum/SubSetSum-5.json --algo=0			# SubSetSum
	# ./build/stocos --problem=2 --instance=instances/knapsackProblem/knapsackProblem-5-1.json --algo=0	# Knapsack

packagesDebain:
	apt-get install g++ build-essential rapidjson-dev libboost-all-dev libcppunit-dev libjsoncpp-dev

unittest : ./sources/unitTest.cpp
	$(CC) $(FLAGS) $< -o $(BUILD_DIR)unittest_$(EXEC_NAME) -lcppunit

doxygen:
	doxygen doxygen.cfg

.PHONY: clean

clean:
	rm $(EXEC_NAME)

mrproper:
	rm $(EXEC_NAME) *.o

format:
	clang-format -i -style=file *.cpp *.h

check:
	cppcheck --enable=all sources/