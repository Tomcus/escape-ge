set(CMAKE_CXX_STANDARD 20)

add_library(project_settings INTERFACE)

set_target_properties(project_settings PROPERTIES CXX_STANDARD 20)

target_compile_options(project_settings INTERFACE
    -Wall
    -Wextra
    # -Wpedantic - can't use TRY and MUST
    -Wunused
    -Wmaybe-uninitialized
    -Wshadow
    -Wno-comment
)

if (${CMAKE_BUILD_TYPE} EQUAL "Debug")
    target_compile_definitions(project_settings INTERFACE
        DEBUG
    )
endif()

if (${CMAKE_BUILD_TYPE} EQUAL "Release")
    target_compile_options(project_settings INTERFACE
        -Werror
    )
endif()