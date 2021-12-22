add_subdirectory(ray)
add_subdirectory(utility)
add_subdirectory(data)
add_subdirectory(game)
add_subdirectory(tools)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    project_settings
    ray
    game
)