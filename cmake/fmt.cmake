find_package(fmt 8.0 QUIET)

include(FetchContent)

if(NOT fmt_FOUND)
	FetchContent_Declare(
		fmt
		URL https://github.com/fmtlib/fmt/archive/master.tar.gz
	)

	FetchContent_GetProperties(fmt)
	if (NOT fmt_POPULATED)
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(fmt)

		add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR})
	endif()
endif()