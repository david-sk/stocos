#
# @Author: *
# @License: *
# @Date: *
# @Version: 1
# @Description: Makefile
#

cmake_minimum_required(VERSION 3.0)

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
find_package(PkgConfig REQUIRED)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "apt install pkg-config")
endif(NOT Boost_FOUND)

## jsoncpp
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

## Boost - program_options + log
find_package(Boost 1.40 COMPONENTS program_options log REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
if (NOT Boost_FOUND)
    message(FATAL_ERROR "apt-get install libboost-all-dev")
endif(NOT Boost_FOUND)

if(BUILD_WITH_BAR)
  hunter_add_package(bar)
endif()

## Stocos
add_executable(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} sources/main.cpp)
target_link_libraries(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} LINK_PUBLIC ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} LINK_PUBLIC ${JSONCPP_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} LINK_PUBLIC ${JSONRPCCPPCLIENT_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} LINK_PUBLIC /usr/lib/x86_64-linux-gnu/libjsonrpccpp-client.so)
target_link_libraries(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} LINK_PUBLIC /usr/lib/x86_64-linux-gnu/libjsonrpccpp-common.so.0)
target_link_libraries(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} LINK_PUBLIC /usr/lib/x86_64-linux-gnu/libmongoclient.so.0)

## Cppunit
pkg_check_modules(CPPUNIT cppunit)
link_libraries(${CPPUNIT_LIBRARIES})

## Stocos unit test
add_executable(${PROJECT_NAME}-unittest-${CMAKE_BUILD_TYPE} tests-unitaires/unitTest.cpp)
target_include_directories(${PROJECT_NAME}-unittest-${CMAKE_BUILD_TYPE} PUBLIC sources/)
target_link_libraries(${PROJECT_NAME}-unittest-${CMAKE_BUILD_TYPE} LINK_PUBLIC ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-unittest-${CMAKE_BUILD_TYPE} LINK_PUBLIC ${JSONCPP_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-unittest-${CMAKE_BUILD_TYPE} LINK_PUBLIC ${CPPUNIT_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-unittest-${CMAKE_BUILD_TYPE} LINK_PUBLIC /usr/lib/x86_64-linux-gnu/libmongoclient.so.0)

## Test unitaire -> make test ARGS="-V"
enable_testing()
add_test(NAME "tests-unitaires" COMMAND ./build/stocos-unittest-Release WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME "oneMax-FirstImprovement-FlipBit" COMMAND /usr/local/bin/python3.7 ./tests-solver/oneMax-FirstImprovement-FlipBit.py WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME "oneMax-OnePlusLambda-FlipBit" COMMAND /usr/local/bin/python3.7 ./tests-solver/oneMax-OnePlusLambda-FlipBit.py WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME "oneMax-TabuSearch-FlipBit.py" COMMAND /usr/local/bin/python3.7 ./tests-solver/oneMax-TabuSearch-FlipBit.py WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME "oneMax-IteratedLocalSearch-FI-FlipBit" COMMAND /usr/local/bin/python3.7 ./tests-solver/oneMax-IteratedLocalSearch-FI-FlipBit.py WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME "oneMax-EvolutionaryAlgo-FlipBit" COMMAND /usr/local/bin/python3.7 ./tests-solver/oneMax-EvolutionaryAlgo-FlipBit.py WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
# add_test(NAME "oneMax-BestImprovement-Neighborhood" COMMAND /usr/local/bin/python3.7 ./tests-solver/oneMax-BestImprovement-Neighborhood.py WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})


# ## > Doxygen ##################################################################
# find_package(Doxygen)
# if (DOXYGEN_FOUND)
#     configure_file(Doxyfile.in Doxyfile)

#     set(DOXYGEN_INPUT ${CMAKE_BINARY_DIR}/Doxyfile)
#     set(DOXYGEN_OUTPUT ${APIDOC_DIR}/html/index.html)

#     add_custom_target(doc ALL
#     COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
#     COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT} > /dev/null
#     COMMAND ${CMAKE_COMMAND} -E echo "Done."
#     )

#     install(DIRECTORY ${CMAKE_BINARY_DIR}/doc/html 
#         DESTINATION share/doc/${CMAKE_PROJECT_NAME})
# else (DOXYGEN_FOUND)
#     message("Doxygen need to be installed to generate the doxygen documentation")
# endif (DOXYGEN_FOUND)
# ## < Doxygen

## > cppcheck ##################################################################
SET(PROJECT_TRDPARTY_DIR third-party)

file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)
foreach (SOURCE_FILE ${ALL_SOURCE_FILES})
    string(FIND ${SOURCE_FILE} ${PROJECT_TRDPARTY_DIR} PROJECT_TRDPARTY_DIR_FOUND)
    if (NOT ${PROJECT_TRDPARTY_DIR_FOUND} EQUAL -1)
        list(REMOVE_ITEM ALL_SOURCE_FILES ${SOURCE_FILE})
    endif ()
endforeach ()

add_custom_target(
        cppcheck
        COMMAND /usr/bin/cppcheck
        --enable=warning,performance,portability,information,missingInclude
        --std=c++11
        --library=qt.cfg
        --template="[{severity}][{id}] {message} {callstack} \(On {file}:{line}\)"
        --verbose
        --quiet
        ${ALL_SOURCE_FILES}
)
## < cppcheck


## > clang-format ##################################################################
file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)
foreach (SOURCE_FILE ${ALL_SOURCE_FILES})
    string(FIND ${SOURCE_FILE} ${PROJECT_TRDPARTY_DIR} PROJECT_TRDPARTY_DIR_FOUND)
    if (NOT ${PROJECT_TRDPARTY_DIR_FOUND} EQUAL -1)
        list(REMOVE_ITEM ALL_SOURCE_FILES ${SOURCE_FILE})
    endif ()
endforeach ()

add_custom_target(
        clangformat
        COMMAND /usr/bin/clang-format
        -style=file
        -i
        ${ALL_SOURCE_FILES}
)
## < clang-format