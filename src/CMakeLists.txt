
add_subdirectory(audio/)
add_subdirectory(ecs/)
add_subdirectory(entity/)
add_subdirectory(input/)
add_subdirectory(rendering/)
add_subdirectory(utils/)

target_sources(knapsackpp PRIVATE engine.cpp handler.cpp metaparse.cpp screen.cpp)