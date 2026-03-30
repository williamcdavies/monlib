# CMP0135 requires at least CMake v3.24
cmake_minimum_required(VERSION 3.24)
project(monlib)

option(MONLIB_BUILD_TESTING "..." OFF)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD            17)
set(CMAKE_CXX_STANDARD_REQUIRED   ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  nlohmann_json
  URL https://github.com/nlohmann/json/archive/refs/tags/v3.12.0.zip
)
FetchContent_MakeAvailable(nlohmann_json)

add_library(monlib
    src/mon.cpp
    src/party.cpp
)
target_include_directories(monlib PUBLIC
    include
)
target_link_libraries(monlib PUBLIC
    nlohmann_json::nlohmann_json
)

if (MONLIB_BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()