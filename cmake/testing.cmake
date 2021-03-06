find_package(Catch2 3 QUIET)

include(FetchContent)

if(NOT Catch2_FOUND)
	
	FetchContent_Declare(
		Catch2
		GIT_REPOSITORY https://github.com/catchorg/Catch2.git
		GIT_TAG        v3.0.0-preview3
	)
    FetchContent_MakeAvailable(Catch2)
endif()

add_library(test_base_with_main INTERFACE)

target_link_libraries(test_base_with_main INTERFACE project_settings Catch2::Catch2WithMain)

set(UNIT_TEST_SOURCES "" CACHE INTERNAL "UNIT_TEST_SOURCES")
set(UNIT_TEST_DEPENDENCIES "" CACHE INTERNAL "UNIT_TEST_DEPENDENCIES")

function(target_add_unit_tests)
    cmake_parse_arguments(ADD_UNIT_TEST "" "TARGET" "FILES" ${ARGN})

	string(REPLACE "${CMAKE_SOURCE_DIR}" "" PATH_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
	set(PATH_PREFIX "..${PATH_PREFIX}")
	foreach(FILE ${ADD_UNIT_TEST_FILES})
		if ("${UNIT_TEST_SOURCES}" STREQUAL "")
			set(UNIT_TEST_SOURCES ${PATH_PREFIX}/${FILE} CACHE INTERNAL "UNIT_TEST_SOURCES")
		else()
			set(UNIT_TEST_SOURCES ${UNIT_TEST_SOURCES} ${PATH_PREFIX}/${FILE} CACHE INTERNAL "UNIT_TEST_SOURCES")
		endif()
	endforeach()
    set(UNIT_TEST_DEPENDENCIES ${UNIT_TEST_DEPENDENCIES} ${ADD_UNIT_TEST_TARGET} CACHE INTERNAL "UNIT_TEST_DEPENDENCIES")
endfunction()
