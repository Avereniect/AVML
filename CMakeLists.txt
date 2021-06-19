cmake_minimum_required(VERSION 3.17)
project(AVML)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(vendor/googletest)

#######################################
# AVML Library
#######################################

add_library(AVML INTERFACE)
target_include_directories(AVML INTERFACE ./include/)



#######################################
# AVML Tests
#######################################

add_executable(AVML_tests tests/AVML_tests.cpp)

target_include_directories(AVML_tests PRIVATE
    ./include/
    vendor/googletest/googletest/include
)
target_link_libraries(AVML_tests PRIVATE gtest)
