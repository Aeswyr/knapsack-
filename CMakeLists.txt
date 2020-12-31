cmake_minimum_required(VERSION 3.16)

# set the project name and version
project(Tutorial VERSION 0.2)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/build/)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)

# add the executable
add_library(KnapsackPP SHARED knapsack.cxx)