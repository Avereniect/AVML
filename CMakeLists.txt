cmake_minimum_required(VERSION 3.17)
project(AVML)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(vendor/googletest)

add_library(AVML INTERFACE)
target_include_directories(AVML INTERFACE ./include)

add_executable(AVML_tests tests/AVML_tests.cpp)

target_include_directories(AVML_tests PRIVATE
    ./include/
    vendor/googletest/googletest/include
)
target_link_libraries(AVML_tests PRIVATE gtest)
