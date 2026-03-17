# CMP0135 requires at least CMake v3.24
cmake_minimum_required(VERSION 3.24)
project(monlib)

option(MONLIB_BUILD_TESTING "..." OFF)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(monlib
    src/party.cpp
)
target_include_directories(monlib PUBLIC
    include
)

if (MONLIB_BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()