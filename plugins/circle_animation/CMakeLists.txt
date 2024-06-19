# Set the project namecircle
project(circle_animation)

file(GLOB_RECURSE PLUG_SOURCES "./*.cpp")

# Create the shared library
add_library(circle_animation SHARED ${PLUG_SOURCES} ${UTILS} ${COMMON})

# Link Raylib library
target_link_libraries(circle_animation PRIVATE raylib)

# Specify the output directory for the lib file
set_target_properties(circle_animation PROPERTIES
LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/plug
)
