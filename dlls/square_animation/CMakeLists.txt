# Set the project name
project(square_animation)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)

# List source files
set(SQUARE_SOURCES
    animation.cpp
    ../../src/common/ffmpeg.cpp  # Adjust this path as necessary
    ../../utils/step_functions.cpp 
)

# Create the shared library
add_library(square_animation SHARED ${SQUARE_SOURCES})

target_link_libraries(square_animation PRIVATE raylib)

# Specify the output directory for the .so file
set_target_properties(square_animation PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dlls/square_animation
)
