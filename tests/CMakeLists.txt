enable_testing()

string(REGEX REPLACE "^ " "" UNIT_TEST_DEPENDENCIES ${UNIT_TEST_DEPENDENCIES})
string(REGEX REPLACE "  " " " UNIT_TEST_DEPENDENCIES ${UNIT_TEST_DEPENDENCIES})
string(REGEX REPLACE "^ " "" UNIT_TEST_SOURCES ${UNIT_TEST_SOURCES})
string(REGEX REPLACE "  " " " UNIT_TEST_SOURCES ${UNIT_TEST_SOURCES})
message(NOTICE ">${UNIT_TEST_SOURCES}<")

add_executable(unit_tests ${UNIT_TEST_SOURCES})

target_link_libraries(unit_tests PUBLIC test_base_with_main ${UNIT_TEST_DEPENDENCIES})

add_test(UnitTests unit_tests)