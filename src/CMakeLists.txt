
add_subdirectory(audio/)
add_subdirectory(ecs/)
add_subdirectory(entity/)
add_subdirectory(input/)
add_subdirectory(rendering/)
add_subdirectory(utils/)
add_subdirectory(core/)
add_subdirectory(gl/)

target_sources(${PROJECT_NAME} PRIVATE engine.cpp metaparse.cpp screen.cpp)