# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sejersen/dev/prism

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sejersen/dev/prism/build

# Include any dependencies generated for this target.
include CMakeFiles/prism_engine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/prism_engine.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/prism_engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/prism_engine.dir/flags.make

CMakeFiles/prism_engine.dir/src/common/ffmpeg.cpp.o: CMakeFiles/prism_engine.dir/flags.make
CMakeFiles/prism_engine.dir/src/common/ffmpeg.cpp.o: /Users/sejersen/dev/prism/src/common/ffmpeg.cpp
CMakeFiles/prism_engine.dir/src/common/ffmpeg.cpp.o: CMakeFiles/prism_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sejersen/dev/prism/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/prism_engine.dir/src/common/ffmpeg.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/prism_engine.dir/src/common/ffmpeg.cpp.o -MF CMakeFiles/prism_engine.dir/src/common/ffmpeg.cpp.o.d -o CMakeFiles/prism_engine.dir/src/common/ffmpeg.cpp.o -c /Users/sejersen/dev/prism/src/common/ffmpeg.cpp

CMakeFiles/prism_engine.dir/src/common/ffmpeg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/prism_engine.dir/src/common/ffmpeg.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sejersen/dev/prism/src/common/ffmpeg.cpp > CMakeFiles/prism_engine.dir/src/common/ffmpeg.cpp.i

CMakeFiles/prism_engine.dir/src/common/ffmpeg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/prism_engine.dir/src/common/ffmpeg.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sejersen/dev/prism/src/common/ffmpeg.cpp -o CMakeFiles/prism_engine.dir/src/common/ffmpeg.cpp.s

CMakeFiles/prism_engine.dir/src/main.cpp.o: CMakeFiles/prism_engine.dir/flags.make
CMakeFiles/prism_engine.dir/src/main.cpp.o: /Users/sejersen/dev/prism/src/main.cpp
CMakeFiles/prism_engine.dir/src/main.cpp.o: CMakeFiles/prism_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sejersen/dev/prism/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/prism_engine.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/prism_engine.dir/src/main.cpp.o -MF CMakeFiles/prism_engine.dir/src/main.cpp.o.d -o CMakeFiles/prism_engine.dir/src/main.cpp.o -c /Users/sejersen/dev/prism/src/main.cpp

CMakeFiles/prism_engine.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/prism_engine.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sejersen/dev/prism/src/main.cpp > CMakeFiles/prism_engine.dir/src/main.cpp.i

CMakeFiles/prism_engine.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/prism_engine.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sejersen/dev/prism/src/main.cpp -o CMakeFiles/prism_engine.dir/src/main.cpp.s

CMakeFiles/prism_engine.dir/src/plug.cpp.o: CMakeFiles/prism_engine.dir/flags.make
CMakeFiles/prism_engine.dir/src/plug.cpp.o: /Users/sejersen/dev/prism/src/plug.cpp
CMakeFiles/prism_engine.dir/src/plug.cpp.o: CMakeFiles/prism_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sejersen/dev/prism/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/prism_engine.dir/src/plug.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/prism_engine.dir/src/plug.cpp.o -MF CMakeFiles/prism_engine.dir/src/plug.cpp.o.d -o CMakeFiles/prism_engine.dir/src/plug.cpp.o -c /Users/sejersen/dev/prism/src/plug.cpp

CMakeFiles/prism_engine.dir/src/plug.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/prism_engine.dir/src/plug.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sejersen/dev/prism/src/plug.cpp > CMakeFiles/prism_engine.dir/src/plug.cpp.i

CMakeFiles/prism_engine.dir/src/plug.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/prism_engine.dir/src/plug.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sejersen/dev/prism/src/plug.cpp -o CMakeFiles/prism_engine.dir/src/plug.cpp.s

# Object files for target prism_engine
prism_engine_OBJECTS = \
"CMakeFiles/prism_engine.dir/src/common/ffmpeg.cpp.o" \
"CMakeFiles/prism_engine.dir/src/main.cpp.o" \
"CMakeFiles/prism_engine.dir/src/plug.cpp.o"

# External object files for target prism_engine
prism_engine_EXTERNAL_OBJECTS =

/Users/sejersen/dev/prism/bin/prism_engine: CMakeFiles/prism_engine.dir/src/common/ffmpeg.cpp.o
/Users/sejersen/dev/prism/bin/prism_engine: CMakeFiles/prism_engine.dir/src/main.cpp.o
/Users/sejersen/dev/prism/bin/prism_engine: CMakeFiles/prism_engine.dir/src/plug.cpp.o
/Users/sejersen/dev/prism/bin/prism_engine: CMakeFiles/prism_engine.dir/build.make
/Users/sejersen/dev/prism/bin/prism_engine: /opt/homebrew/Cellar/raylib/5.0/lib/libraylib.dylib
/Users/sejersen/dev/prism/bin/prism_engine: CMakeFiles/prism_engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/sejersen/dev/prism/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable /Users/sejersen/dev/prism/bin/prism_engine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/prism_engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/prism_engine.dir/build: /Users/sejersen/dev/prism/bin/prism_engine
.PHONY : CMakeFiles/prism_engine.dir/build

CMakeFiles/prism_engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/prism_engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/prism_engine.dir/clean

CMakeFiles/prism_engine.dir/depend:
	cd /Users/sejersen/dev/prism/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sejersen/dev/prism /Users/sejersen/dev/prism /Users/sejersen/dev/prism/build /Users/sejersen/dev/prism/build /Users/sejersen/dev/prism/build/CMakeFiles/prism_engine.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/prism_engine.dir/depend

