# Set the project name
project(bezier_creator)

file(GLOB_RECURSE PLUG_SOURCES "./*.cpp")

# Create the shared library
add_library(bezier_creator SHARED ${PLUG_SOURCES} ${UTILS} ${COMMON})

# Link Raylib library
target_link_libraries(bezier_creator PRIVATE raylib)

# Specify the output directory for the lib file
set_target_properties(bezier_creator PROPERTIES
LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/plug
)
