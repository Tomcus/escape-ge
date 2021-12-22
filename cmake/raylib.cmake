# Set this to the minimal version you want to support
find_package(raylib 4.0 QUIET) # Let CMake search for a raylib-config.cmake
find_package(raygui 3.0 QUIET)

include(FetchContent)

# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
	FetchContent_Declare(
		raylib
		URL https://github.com/raysan5/raylib/archive/master.tar.gz
	)

	FetchContent_GetProperties(raylib)
	if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(raylib)

		set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

		# build raylib
		add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

	endif()

endif()

if (NOT raygui_FOUND)
	FetchContent_Declare(
		raygui
		URL https://github.com/raysan5/raygui/archive/master.tar.gz
	)

	FetchContent_GetProperties(raygui)
	if (NOT raygui_POPULATED)
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(raygui)
		
		add_subdirectory(${raygui_SOURCE_DIR}/projects/CMake/)
	endif()

endif()