#
# @Author: *
# @License: *
# @Date: *
# @Version: 1
# @Description: Makefile
#

cmake_minimum_required(VERSION 3.12)

###############################################################################
# Set of compilator parameters
###############################################################################
set(CMAKE_BUILD_TYPE Release) # (Release|Debug)

set(CMAKE_CXX_FLAGS "-std=c++2a -fopenmp\
                                -pedantic -Wall -Wextra -Wcast-align -Wctor-dtor-privacy    \
                                -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op \
                                -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept    \
                                -Woverloaded-virtual -Wredundant-decls  -Wsign-promo        \
                                -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Werror  \
                                -Wno-unused") # -Wswitch-default -Wsign-conversion -Wshadow  -Wcast-qual -Wold-style-cast
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

###############################################################################
# Load modules cmake
###############################################################################
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(auto-install)   # auto install package
include(cppcheck)       #
include(clang-format)   #
include(version)        # Version name generator form git branch, hash
include(doxygen)        # Create le documentation

###############################################################################
# Load modules of the projet
###############################################################################
project(stocos)
set(MODULE_PROBLEM_ONEMAX true)
set(MODULE_PROBLEM_LATINSQUARE true)
set(MODULE_PROBLEM_KNAPSACK true)
set(MODULE_PROBLEM_TSP true)
set(MODULE_PROBLEM_SUBSETSUM true)
set(MODULE_PROBLEM_CONTINOUSPROBLEM true)

###############################################################################
# Load modules of external libs
###############################################################################
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

###############################################################################
# Get external libs
###############################################################################
include(ExternalProject)

ExternalProject_Add(LIBJSON_RPC_CPP
    SOURCE_DIR "${PROJECT_BINARY_DIR}/deps/libjson-rpc-cpp"
    BINARY_DIR "${PROJECT_BINARY_DIR}/deps/libjson-rpc-cpp-build"
    INSTALL_DIR "${PROJECT_BINARY_DIR}/deps/install"
    GIT_REPOSITORY https://github.com/cinemast/libjson-rpc-cpp.git
    GIT_TAG c696f69
    CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

## PkgConfigmr
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
find_package(Boost 1.40 COMPONENTS program_options log iostreams REQUIRED)
include_directories(${BOOST_INCLUDE_DIR})
if (NOT Boost_FOUND)
    packageManager("libboost-all-dev")
    find_package(Boost 1.40 COMPONENTS program_options log iostreams REQUIRED)
    include_directories(${BOOST_INCLUDE_DIR})
endif(NOT Boost_FOUND)

## Mongo
find_library(MongoDB_LIBRARIES NAMES mongoclient)
if (NOT MongoDB_LIBRARIES)
    packageManager("libmongoclient-dev")
    find_library(MongoDB_LIBRARIES NAMES mongoclient)
endif(NOT MongoDB_LIBRARIES)

find_path(MongoDB_INCLUDE_DIR NAMES mongo/client/dbclient.h)
if (NOT MongoDB_INCLUDE_DIR)
    packageManager("libmongoclient0")
    find_path(MongoDB_INCLUDE_DIR NAMES mongo/client/dbclient.h)
endif(NOT MongoDB_INCLUDE_DIR)

###############################################################################
# Stocos
###############################################################################
add_executable(${PROJECT_NAME} sources/main.cpp)
file(GLOB_RECURSE ALL_SOURCE_FILES  sources/*.hpp)
foreach(PATH_FILE  ${LIST_OF_FILES})
    target_precompile_headers(${PROJECT_NAME} PRIVATE ${PATH_FILE})
endforeach()

target_include_directories(${PROJECT_NAME} PRIVATE "modules")

target_link_libraries(${PROJECT_NAME}  
    ${BOOST_LIBRARIES} 
    ${JSONCPP_LIBRARIES}
    "${CMAKE_CURRENT_BINARY_DIR}/deps/install/lib/libjsonrpccpp-client.so"
    "${CMAKE_CURRENT_BINARY_DIR}/deps/install/lib/libjsonrpccpp-common.so"
    ${MongoDB_LIBRARIES})

target_compile_definitions(${PROJECT_NAME} PRIVATE 
    MODULE_PROBLEM_ONEMAX=${MODULE_PROBLEM_ONEMAX} 
    MODULE_PROBLEM_LATINSQUARE=${MODULE_PROBLEM_LATINSQUARE} 
    MODULE_PROBLEM_KNAPSACK=${MODULE_PROBLEM_KNAPSACK} 
    MODULE_PROBLEM_TSP=${MODULE_PROBLEM_TSP} 
    MODULE_PROBLEM_SUBSETSUM=${MODULE_PROBLEM_SUBSETSUM} 
    MODULE_PROBLEM_CONTINOUSPROBLEM=${MODULE_PROBLEM_CONTINOUSPROBLEM})

## Cppunit
pkg_check_modules(CPPUNIT cppunit)
if (NOT CPPUNIT_FOUND)
    packageManager("libcppunit-dev")
endif(NOT CPPUNIT_FOUND)

link_libraries(${CPPUNIT_LIBRARIES})

###############################################################################
# Stocos unit test
###############################################################################
add_custom_target(unit-test COMMAND ${PROJECT_NAME}-unittest DEPENDS ${PROJECT_NAME}-unittest)
add_executable(${PROJECT_NAME}-unittest tests-unitaires/unitTest.cpp)
target_include_directories(${PROJECT_NAME}-unittest PRIVATE 
    modules/
    sources/)
target_link_libraries(${PROJECT_NAME}-unittest LINK_PRIVATE
    ${BOOST_LIBRARIES}
    ${JSONCPP_LIBRARIES}
    ${CPPUNIT_LIBRARIES}
    ${MongoDB_LIBRARIES})

enable_testing()
add_test(NAME "tests-unitaires" COMMAND ./build/${PROJECT_NAME}-unittest WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

## Detection du programme python3.7
FIND_PROGRAM(PYTHON3.7_EXECUTABLE python3.7)
if (NOT PYTHON3.7_EXECUTABLE)
    packageManager("python3.7")
    FIND_PROGRAM(PYTHON3.7_EXECUTABLE python3.7)
endif(NOT PYTHON3.7_EXECUTABLE)

file(GLOB LIST_OF_FILES  tests-solver/*.py)
foreach(PATH_FILE  ${LIST_OF_FILES})
    get_filename_component(FILE ${PATH_FILE} NAME)
    add_test(NAME ${FILE} COMMAND ${PYTHON3.7_EXECUTABLE} ${PATH_FILE} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endforeach()