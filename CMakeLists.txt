cmake_minimum_required(VERSION 3.17)
project(AVML)

set(CMAKE_CXX_STANDARD 11)

#######################################
# AVML Library
#######################################

add_library(AVML INTERFACE)
target_include_directories(AVML INTERFACE ./include/)

#######################################
# AVML Tests
#######################################

option(AVML_BUILD_TESTS OFF)

if (AVML_BUILD_TESTS)
    add_subdirectory(vendor/googletest)

    add_executable(AVML_tests tests/AVML_tests.cpp)

    target_include_directories(AVML_tests PRIVATE
        ./include/
    )

    target_compile_options(AVML_tests
        PRIVATE
        "-march=icelake-client"
        "-O3" "-fno-stack-check"
        "-fno-stack-protector"
    )

    target_link_libraries(AVML_tests PRIVATE gtest)
endif()


