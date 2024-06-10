cmake_minimum_required(VERSION 3.10)

project(Prism)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find Raylib package
find_package(raylib REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/utils)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/common)
include_directories(${RAYLIB_INCLUDE_DIR})

# Add the main engine source files
file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp")

# Variables for pluging compilation
file(GLOB_RECURSE COMMON "src/common/*.cpp")
file(GLOB_RECURSE UTILS "utils/*.cpp")

add_executable(prism_engine ${ENGINE_SOURCES})

# Set the output directory for the executable
set_target_properties(prism_engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

# Link Raylib library
target_link_libraries(prism_engine PRIVATE raylib)

# Include the dlls directory
add_subdirectory(plugins)
