cmake_minimum_required(VERSION 3.10)

project(Prism)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Raylib package
find_package(raylib REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/utils)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/common)
include_directories(${RAYLIB_INCLUDE_DIR})

# Add the main engine source files
file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp")
list(REMOVE_ITEM ENGINE_SOURCES "${CMAKE_SOURCE_DIR}/src/common/ffmpeg.cpp")

add_executable(prism_engine ${ENGINE_SOURCES})

# Link Raylib library
target_link_libraries(prism_engine PRIVATE raylib)
# Include the dlls directory
add_subdirectory(dlls)
