set(TEST_EXEC "basic_string_cmp")

set(TEST_SOURCES
    compare.h
    test/test.cpp
)

add_executable(${TEST_EXEC} ${TEST_SOURCES})
target_link_libraries(${TEST_EXEC} GTest::gtest_main)

target_include_directories(${TEST_EXEC}
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}
)

add_custom_target(run_basic_string_cmp_tests
    DEPENDS ${TEST_EXEC}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${TEST_EXEC}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running basic_string compare tests"
    VERBATIM
)
