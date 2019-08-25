#
# @Author: *
# @License: *
# @Date: *
# @Version: 1
# @Description: Makefile
#

cmake_minimum_required(VERSION 3.0)

# Load modul
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmaketools")
include(auto-install)   # auto install package
include(cppcheck)       # 
include(clang-format)   #
#include(doxygen)        # Create le doc
include(cotire)         # CMake module to speed up builds

project(stocos)



set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "-std=c++17 -pedantic -Wall -Wextra -Wcast-align -Wctor-dtor-privacy    \
                                -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op \
                                -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept    \
                                -Woverloaded-virtual -Wredundant-decls  -Wsign-promo        \
                                -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Werror  \
                                -Wno-unused") # -Wswitch-default -Wsign-conversion -Wshadow  -Wcast-qual -Wold-style-cast
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")



## PkgConfig
find_package(PkgConfig)
if (NOT PKG_CONFIG_FOUND)
    packageManager("pkg-config")
    find_package(PkgConfig REQUIRED)
endif(NOT PKG_CONFIG_FOUND)

## jsoncpp
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
if (NOT JSONCPP_FOUND)
    packageManager("libjsoncpp-dev")
    packageManager("libjsoncpp1")
endif(NOT JSONCPP_FOUND)

## Boost - program_options + log
find_package(Boost 1.40 COMPONENTS program_options log REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
if (NOT Boost_FOUND)
    packageManager("libboost-all-dev")
endif(NOT Boost_FOUND)

## Mongo
find_library(MongoDB_LIBRARIES NAMES mongoclient)
if (NOT MongoDB_LIBRARIES)
    packageManager("libmongoclient-dev")
endif(NOT MongoDB_LIBRARIES)

find_path(MongoDB_INCLUDE_DIR NAMES mongo/client/dbclient.h)
if (NOT MongoDB_INCLUDE_DIR)
    packageManager("libmongoclient0")
endif(NOT MongoDB_INCLUDE_DIR)

## Jsonrpccpp
find_library(JSONRPCCPPCOMMON_LIBRARIES NAMES jsonrpccpp-common)
if (NOT JSONRPCCPPCOMMON_LIBRARIES)
    packageManager("libjsonrpccpp-common0")
endif(NOT JSONRPCCPPCOMMON_LIBRARIES)

find_library(JSONRPCCPPCLIENT_LIBRARIES NAMES jsonrpccpp-client)
if (NOT JSONRPCCPPCLIENT_LIBRARIES)
    packageManager("libjsonrpccpp-client0")
endif(NOT JSONRPCCPPCLIENT_LIBRARIES)


# ## Stocos
add_executable(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} sources/main.cpp)
target_link_libraries(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} LINK_PUBLIC ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} LINK_PUBLIC ${JSONCPP_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} LINK_PUBLIC ${JSONRPCCPPCLIENT_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} LINK_PUBLIC ${JSONRPCCPPCOMMON_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} LINK_PUBLIC ${MongoDB_LIBRARIES})

#set_target_properties(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "sources/problem/exprtk/exprtk.h")
#get_target_property(_precompiledHeader "sources/problem/exprtk/exprtk.h" COTIRE_CXX_PRECOMPILED_HEADER)
#cotire(${PROJECT_NAME}-${CMAKE_BUILD_TYPE})

## Cppunit
pkg_check_modules(CPPUNIT cppunit)
if (NOT CPPUNIT_FOUND)
    packageManager("libcppunit-dev")
endif(NOT CPPUNIT_FOUND)

link_libraries(${CPPUNIT_LIBRARIES})

## Stocos unit test
add_executable(${PROJECT_NAME}-unittest-${CMAKE_BUILD_TYPE} tests-unitaires/unitTest.cpp)
target_include_directories(${PROJECT_NAME}-unittest-${CMAKE_BUILD_TYPE} PUBLIC sources/)
target_link_libraries(${PROJECT_NAME}-unittest-${CMAKE_BUILD_TYPE} LINK_PUBLIC ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-unittest-${CMAKE_BUILD_TYPE} LINK_PUBLIC ${JSONCPP_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-unittest-${CMAKE_BUILD_TYPE} LINK_PUBLIC ${CPPUNIT_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-unittest-${CMAKE_BUILD_TYPE} LINK_PUBLIC ${MongoDB_LIBRARIES})

## Test unitaire -> make test ARGS="-V"
enable_testing()
add_test(NAME "tests-unitaires" COMMAND ./build/stocos-unittest-Release WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME "oneMax-FirstImprovement-FlipBit" COMMAND /usr/local/bin/python3.7 ./tests-solver/oneMax-FirstImprovement-FlipBit.py WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME "oneMax-OnePlusLambda-FlipBit" COMMAND /usr/local/bin/python3.7 ./tests-solver/oneMax-OnePlusLambda-FlipBit.py WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME "oneMax-TabuSearch-FlipBit.py" COMMAND /usr/local/bin/python3.7 ./tests-solver/oneMax-TabuSearch-FlipBit.py WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME "oneMax-IteratedLocalSearch-FI-FlipBit" COMMAND /usr/local/bin/python3.7 ./tests-solver/oneMax-IteratedLocalSearch-FI-FlipBit.py WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME "oneMax-EvolutionaryAlgo-FlipBit" COMMAND /usr/local/bin/python3.7 ./tests-solver/oneMax-EvolutionaryAlgo-FlipBit.py WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME "genericProblem-eq1-FirstImprovement-FlipBit" COMMAND /usr/local/bin/python3.7 ./tests-solver/genericProblem-eq1-FirstImprovement-FlipBit.py WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME "genericProblem-eq2-FirstImprovement-FlipBit" COMMAND /usr/local/bin/python3.7 ./tests-solver/genericProblem-eq1-FirstImprovement-FlipBit.py WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
# add_test(NAME "oneMax-BestImprovement-Neighborhood" COMMAND /usr/local/bin/python3.7 ./tests-solver/oneMax-BestImprovement-Neighborhood.py WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})




