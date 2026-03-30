add_executable(party_test 
    party_test.cpp
)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(party_test 
    GTest::gtest_main 
    monlib
)
gtest_discover_tests(party_test 
    PROPERTIES LABELS "party"
)