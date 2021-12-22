add_library(ray INTERFACE)

target_include_directories(ray INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ray INTERFACE raylib raygui)

target_add_unit_tests(TARGET ray FILES ray.unit.cpp)