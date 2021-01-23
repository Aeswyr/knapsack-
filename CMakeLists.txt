cmake_minimum_required(VERSION 3.16)


include (FetchContent)


# set the project name and version
project(knapsackPP VERSION 0.2.1)


## specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
cmake_policy(SET CMP0076 NEW)


if(WIN32)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()


# add the exported library
add_library(${PROJECT_NAME} SHARED)


# fetch external dependencies
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Populate(
        FETCH_BOOST_CMAKE        
        GIT_REPOSITORY  https://github.com/Orphis/boost-cmake
        SOURCE_DIR      ../libs/boostcmake
        )
FetchContent_Populate(
        FETCH_STB        
        GIT_REPOSITORY  https://github.com/nothings/stb
        SOURCE_DIR      ../libs/stb
        )
FetchContent_Populate(
        FETCH_OPENAL        
        GIT_REPOSITORY  https://github.com/kcat/openal-soft
        SOURCE_DIR      ../libs/openal
        )
FetchContent_Populate(
        FETCH_GLM        
        GIT_REPOSITORY  https://github.com/g-truc/glm
        SOURCE_DIR      ../libs/glm
        )
FetchContent_Populate(
        FETCH_GLFW        
        GIT_REPOSITORY  https://github.com/glfw/glfw
        SOURCE_DIR      ../libs/glfw
        )
#FetchContent_Populate(
#        FETCH_FREETYPE        
#        GIT_REPOSITORY  https://github.com/aseprite/freetype2
#        SOURCE_DIR      ../libs/freetype
#        )


# add dependency src
add_subdirectory(libs/openal/)
add_subdirectory(libs/glm/)
# add_subdirectory(libs/freetype/)
target_sources(${PROJECT_NAME} PRIVATE libs/glad/src/glad.c)

#setup GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(libs/glfw/)

#setup boost
set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/libs/boost)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME ON)
# execute_process(${CMAKE_SOURCE_DIR}/libs)
find_package(Boost COMPONENTS REQUIRED)


#include remaining dependencies
target_include_directories(${PROJECT_NAME} PUBLIC libs/glfw/include/)
target_include_directories(${PROJECT_NAME} PUBLIC libs/glad/include/)
target_include_directories(${PROJECT_NAME} PUBLIC libs/stb/)
target_include_directories(${PROJECT_NAME} PUBLIC libs/glm/)
target_include_directories(${PROJECT_NAME} PUBLIC libs/openal/)
# target_include_directories(${PROJECT_NAME} PUBLIC libs/boost/libs/thread/include/)
# target_include_directories(${PROJECT_NAME} PUBLIC libs/boost/libs/dynamic_bitset/include/)
# target_include_directories(${PROJECT_NAME} PUBLIC libs/boost/libs/asio/include/)


# add source files
add_subdirectory(src/)
target_include_directories(${PROJECT_NAME} PUBLIC headers/)
target_link_libraries(${PROJECT_NAME} Boost::boost Boost::thread glfw)