add_executable(${PROJECT_NAME}LevelEditor
    main.cpp
    base.cpp
    wallsEdit.cpp
)

target_link_libraries(${PROJECT_NAME}LevelEditor
    project_settings
    data
    ray
)