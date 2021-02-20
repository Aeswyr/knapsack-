cmake_minimum_required(VERSION 3.19)

# set the project name and version
        project(knapsackpp VERSION 0.2.1)


# specify the C++ standard
        set(CMAKE_CXX_STANDARD 17)
        set(CMAKE_CXX_STANDARD_REQUIRED True)
        cmake_policy(SET CMP0076 NEW)


if(WIN32)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()


# add the exported library
        add_library(${PROJECT_NAME} SHARED)
        set(CMAKE_EXE_LINKER_FLAGS " -static")
        target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++)

# add dependency src
        add_subdirectory(libs/glm/)
        # add_subdirectory(libs/openal-soft/)
        target_sources(${PROJECT_NAME} PRIVATE libs/glad/src/glad.c)

#setup Freetype2
        # set(SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE)
        # add_subdirectory(libs/freetype2/)

#setup GLFW
        set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(libs/glfw/)

#setup boost
        add_subdirectory(libs/boost-cmake)

#include remaining dependencies
        target_include_directories(${PROJECT_NAME} PRIVATE libs/glfw/include/)
        target_include_directories(${PROJECT_NAME} PRIVATE libs/glad/include/)
        target_include_directories(${PROJECT_NAME} PRIVATE libs/stb/)
        target_include_directories(${PROJECT_NAME} PRIVATE libs/glm/)
        # target_include_directories(${PROJECT_NAME} PRIVATE libs/freetype2/include/)
        # target_include_directories(${PROJECT_NAME} PRIVATE libs/openal-soft/)

# add source files and link
        add_subdirectory(src/)
        target_include_directories(${PROJECT_NAME} PUBLIC include/)
        target_link_libraries(${PROJECT_NAME} Boost::boost Boost::thread glfw)