add_executable(mon_test 
    mon_test.cpp
)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(mon_test 
    GTest::gtest_main 
    monlib
)
gtest_discover_tests(mon_test 
    PROPERTIES LABELS "mon"
)