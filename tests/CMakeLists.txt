enable_testing()

add_executable(unit_tests ${UNIT_TEST_SOURCES})

target_link_libraries(unit_tests PUBLIC test_base_with_main ${UNIT_TEST_DEPENDENCIES})

add_test(UnitTests unit_tests)