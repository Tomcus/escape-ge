add_library(data STATIC
    level/level.cpp
    game_data/game_data.cpp
)

target_include_directories(data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(data PUBLIC
    project_settings
    utility
    ray
)