cmake_minimum_required(VERSION 3.16)

include (FetchContent)

# set the project name and version
project(KnapsackPP VERSION 0.2)

## specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# add the exported library
add_library(knapsackpp SHARED)

# fetch external dependencies
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Populate(
        LIB_BOOST        
        GIT_REPOSITORY  https://github.com/boostorg/boost
        SOURCE_DIR      ../libs/boost
        )
FetchContent_Populate(
        LIB_STB        
        GIT_REPOSITORY  https://github.com/nothings/stb
        SOURCE_DIR      ../libs/stb
        )
FetchContent_Populate(
        LIB_OPENAL        
        GIT_REPOSITORY  https://github.com/kcat/openal-soft
        SOURCE_DIR      ../libs/openal
        )
FetchContent_Populate(
        LIB_GLM        
        GIT_REPOSITORY  https://github.com/g-truc/glm
        SOURCE_DIR      ../libs/glm
        )
FetchContent_Populate(
        LIB_GLFW        
        GIT_REPOSITORY  https://github.com/glfw/glfw
        SOURCE_DIR      ../libs/glfw
        )
#FetchContent_Populate(
#        LIB_FREETYPE        
#        GIT_REPOSITORY  https://github.com/aseprite/freetype2
#        SOURCE_DIR      ../libs/freetype
#        )

# add dependencies
add_subdirectory(libs/boost/)
add_subdirectory(libs/openal/)
add_subdirectory(libs/glm/)
add_subdirectory(libs/glfw/)
# add_subdirectory(libs/freetype/)

target_include_directories(knapsackpp PUBLIC libs/stb/)

# add source files
add_subdirectory(src/)
target_include_directories(knapsackpp PUBLIC headers/)
#target_link_libraries(knapsackpp)