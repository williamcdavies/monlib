# Ref: https://google.github.io/googletest/quickstart-cmake.html
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(monlib_test
    mon_test.cpp
    party_test.cpp
)
target_link_libraries(monlib_test
    GTest::gtest_main
    monlib
)

include(GoogleTest)
gtest_discover_tests(monlib_test)