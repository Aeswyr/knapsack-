cmake_minimum_required(VERSION 3.16)

# set the project name and version
project(KnapsackPP VERSION 0.2)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# set output directory
set(dir ${CMAKE_CURRENT_SOURCE_DIR}/build/)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)

# add the library
add_library(knapsackpp SHARED)

# add external libraries
find_library(SDL SDL2 libs/lib/)
find_library(SDLMIXER SDL2_MIXER libs/lib/)
find_library(SDLIMAGE SDL2_IMAGE libs/lib/)
find_library(SDLTTF SDL2_TTF libs/lib/)

# add source files
add_subdirectory(src/)
target_include_directories(knapsackpp PUBLIC headers/ libs/include/SDL2/)
target_link_libraries(knapsackpp ${SDL} ${SDLMIXER} ${SDLIMAGE} ${SDLTTF})