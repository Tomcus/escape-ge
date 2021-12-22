add_library(game STATIC
    render/ray_renderer.cpp
    render/texture_renderer.cpp
    input/event.cpp
    input/ray_input_handler.cpp
)

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(game PUBLIC
    project_settings
    data
)