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
include plugins/test/CMakeFiles/test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include plugins/test/CMakeFiles/test.dir/compiler_depend.make

# Include the progress variables for this target.
include plugins/test/CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include plugins/test/CMakeFiles/test.dir/flags.make

plugins/test/CMakeFiles/test.dir/test.cpp.o: plugins/test/CMakeFiles/test.dir/flags.make
plugins/test/CMakeFiles/test.dir/test.cpp.o: /Users/sejersen/dev/prism/plugins/test/test.cpp
plugins/test/CMakeFiles/test.dir/test.cpp.o: plugins/test/CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sejersen/dev/prism/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object plugins/test/CMakeFiles/test.dir/test.cpp.o"
	cd /Users/sejersen/dev/prism/build/plugins/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT plugins/test/CMakeFiles/test.dir/test.cpp.o -MF CMakeFiles/test.dir/test.cpp.o.d -o CMakeFiles/test.dir/test.cpp.o -c /Users/sejersen/dev/prism/plugins/test/test.cpp

plugins/test/CMakeFiles/test.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test.dir/test.cpp.i"
	cd /Users/sejersen/dev/prism/build/plugins/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sejersen/dev/prism/plugins/test/test.cpp > CMakeFiles/test.dir/test.cpp.i

plugins/test/CMakeFiles/test.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test.dir/test.cpp.s"
	cd /Users/sejersen/dev/prism/build/plugins/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sejersen/dev/prism/plugins/test/test.cpp -o CMakeFiles/test.dir/test.cpp.s

plugins/test/CMakeFiles/test.dir/__/__/utils/step_functions.cpp.o: plugins/test/CMakeFiles/test.dir/flags.make
plugins/test/CMakeFiles/test.dir/__/__/utils/step_functions.cpp.o: /Users/sejersen/dev/prism/utils/step_functions.cpp
plugins/test/CMakeFiles/test.dir/__/__/utils/step_functions.cpp.o: plugins/test/CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sejersen/dev/prism/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object plugins/test/CMakeFiles/test.dir/__/__/utils/step_functions.cpp.o"
	cd /Users/sejersen/dev/prism/build/plugins/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT plugins/test/CMakeFiles/test.dir/__/__/utils/step_functions.cpp.o -MF CMakeFiles/test.dir/__/__/utils/step_functions.cpp.o.d -o CMakeFiles/test.dir/__/__/utils/step_functions.cpp.o -c /Users/sejersen/dev/prism/utils/step_functions.cpp

plugins/test/CMakeFiles/test.dir/__/__/utils/step_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test.dir/__/__/utils/step_functions.cpp.i"
	cd /Users/sejersen/dev/prism/build/plugins/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sejersen/dev/prism/utils/step_functions.cpp > CMakeFiles/test.dir/__/__/utils/step_functions.cpp.i

plugins/test/CMakeFiles/test.dir/__/__/utils/step_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test.dir/__/__/utils/step_functions.cpp.s"
	cd /Users/sejersen/dev/prism/build/plugins/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sejersen/dev/prism/utils/step_functions.cpp -o CMakeFiles/test.dir/__/__/utils/step_functions.cpp.s

plugins/test/CMakeFiles/test.dir/__/__/src/common/ffmpeg.cpp.o: plugins/test/CMakeFiles/test.dir/flags.make
plugins/test/CMakeFiles/test.dir/__/__/src/common/ffmpeg.cpp.o: /Users/sejersen/dev/prism/src/common/ffmpeg.cpp
plugins/test/CMakeFiles/test.dir/__/__/src/common/ffmpeg.cpp.o: plugins/test/CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sejersen/dev/prism/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object plugins/test/CMakeFiles/test.dir/__/__/src/common/ffmpeg.cpp.o"
	cd /Users/sejersen/dev/prism/build/plugins/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT plugins/test/CMakeFiles/test.dir/__/__/src/common/ffmpeg.cpp.o -MF CMakeFiles/test.dir/__/__/src/common/ffmpeg.cpp.o.d -o CMakeFiles/test.dir/__/__/src/common/ffmpeg.cpp.o -c /Users/sejersen/dev/prism/src/common/ffmpeg.cpp

plugins/test/CMakeFiles/test.dir/__/__/src/common/ffmpeg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test.dir/__/__/src/common/ffmpeg.cpp.i"
	cd /Users/sejersen/dev/prism/build/plugins/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sejersen/dev/prism/src/common/ffmpeg.cpp > CMakeFiles/test.dir/__/__/src/common/ffmpeg.cpp.i

plugins/test/CMakeFiles/test.dir/__/__/src/common/ffmpeg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test.dir/__/__/src/common/ffmpeg.cpp.s"
	cd /Users/sejersen/dev/prism/build/plugins/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sejersen/dev/prism/src/common/ffmpeg.cpp -o CMakeFiles/test.dir/__/__/src/common/ffmpeg.cpp.s

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/test.cpp.o" \
"CMakeFiles/test.dir/__/__/utils/step_functions.cpp.o" \
"CMakeFiles/test.dir/__/__/src/common/ffmpeg.cpp.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

/Users/sejersen/dev/prism/bin/plug/libtest.dylib: plugins/test/CMakeFiles/test.dir/test.cpp.o
/Users/sejersen/dev/prism/bin/plug/libtest.dylib: plugins/test/CMakeFiles/test.dir/__/__/utils/step_functions.cpp.o
/Users/sejersen/dev/prism/bin/plug/libtest.dylib: plugins/test/CMakeFiles/test.dir/__/__/src/common/ffmpeg.cpp.o
/Users/sejersen/dev/prism/bin/plug/libtest.dylib: plugins/test/CMakeFiles/test.dir/build.make
/Users/sejersen/dev/prism/bin/plug/libtest.dylib: /opt/homebrew/Cellar/raylib/5.0/lib/libraylib.dylib
/Users/sejersen/dev/prism/bin/plug/libtest.dylib: plugins/test/CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/sejersen/dev/prism/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library /Users/sejersen/dev/prism/bin/plug/libtest.dylib"
	cd /Users/sejersen/dev/prism/build/plugins/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
plugins/test/CMakeFiles/test.dir/build: /Users/sejersen/dev/prism/bin/plug/libtest.dylib
.PHONY : plugins/test/CMakeFiles/test.dir/build

plugins/test/CMakeFiles/test.dir/clean:
	cd /Users/sejersen/dev/prism/build/plugins/test && $(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : plugins/test/CMakeFiles/test.dir/clean

plugins/test/CMakeFiles/test.dir/depend:
	cd /Users/sejersen/dev/prism/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sejersen/dev/prism /Users/sejersen/dev/prism/plugins/test /Users/sejersen/dev/prism/build /Users/sejersen/dev/prism/build/plugins/test /Users/sejersen/dev/prism/build/plugins/test/CMakeFiles/test.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : plugins/test/CMakeFiles/test.dir/depend

