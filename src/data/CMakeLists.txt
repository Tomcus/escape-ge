add_library(data STATIC
    level/level.cpp
    game_state/game_state.cpp
)

target_include_directories(data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(data PUBLIC
    project_settings
    utility
    ray
)

target_add_unit_tests(TARGET data FILES binary_tree/binary_tree.unit.cpp)