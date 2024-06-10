# Set the project name
project(bezier_creator)

# List source files
set(BEZIER_CREATOR_SOURCES
    bezier_creator.cpp
    ../../src/common/ffmpeg.cpp  # Adjust this path as necessary
    ../../utils/step_functions.cpp 
)

# Create the shared library
add_library(bezier_creator SHARED ${BEZIER_CREATOR_SOURCES})

# Link Raylib library
target_link_libraries(bezier_creator PRIVATE raylib)

# Specify the output directory for the .so file
set_target_properties(bezier_creator PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dlls/bezier_creator
)
