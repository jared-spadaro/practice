# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jaspadar/cpe419/lab3/2017ImageReadBase/2017ImageReadBase

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jaspadar/cpe419/lab3/2017ImageReadBase/2017ImageReadBase/build

# Include any dependencies generated for this target.
include CMakeFiles/readImg.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/readImg.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/readImg.dir/flags.make

CMakeFiles/readImg.dir/src/main.cpp.o: CMakeFiles/readImg.dir/flags.make
CMakeFiles/readImg.dir/src/main.cpp.o: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jaspadar/cpe419/lab3/2017ImageReadBase/2017ImageReadBase/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/readImg.dir/src/main.cpp.o"
	/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/readImg.dir/src/main.cpp.o -c /home/jaspadar/cpe419/lab3/2017ImageReadBase/2017ImageReadBase/src/main.cpp

CMakeFiles/readImg.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/readImg.dir/src/main.cpp.i"
	/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jaspadar/cpe419/lab3/2017ImageReadBase/2017ImageReadBase/src/main.cpp > CMakeFiles/readImg.dir/src/main.cpp.i

CMakeFiles/readImg.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/readImg.dir/src/main.cpp.s"
	/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jaspadar/cpe419/lab3/2017ImageReadBase/2017ImageReadBase/src/main.cpp -o CMakeFiles/readImg.dir/src/main.cpp.s

CMakeFiles/readImg.dir/src/main.cpp.o.requires:
.PHONY : CMakeFiles/readImg.dir/src/main.cpp.o.requires

CMakeFiles/readImg.dir/src/main.cpp.o.provides: CMakeFiles/readImg.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/readImg.dir/build.make CMakeFiles/readImg.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/readImg.dir/src/main.cpp.o.provides

CMakeFiles/readImg.dir/src/main.cpp.o.provides.build: CMakeFiles/readImg.dir/src/main.cpp.o

# Object files for target readImg
readImg_OBJECTS = \
"CMakeFiles/readImg.dir/src/main.cpp.o"

# External object files for target readImg
readImg_EXTERNAL_OBJECTS =

readImg: CMakeFiles/readImg.dir/src/main.cpp.o
readImg: CMakeFiles/readImg.dir/build.make
readImg: CMakeFiles/readImg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable readImg"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/readImg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/readImg.dir/build: readImg
.PHONY : CMakeFiles/readImg.dir/build

CMakeFiles/readImg.dir/requires: CMakeFiles/readImg.dir/src/main.cpp.o.requires
.PHONY : CMakeFiles/readImg.dir/requires

CMakeFiles/readImg.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/readImg.dir/cmake_clean.cmake
.PHONY : CMakeFiles/readImg.dir/clean

CMakeFiles/readImg.dir/depend:
	cd /home/jaspadar/cpe419/lab3/2017ImageReadBase/2017ImageReadBase/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jaspadar/cpe419/lab3/2017ImageReadBase/2017ImageReadBase /home/jaspadar/cpe419/lab3/2017ImageReadBase/2017ImageReadBase /home/jaspadar/cpe419/lab3/2017ImageReadBase/2017ImageReadBase/build /home/jaspadar/cpe419/lab3/2017ImageReadBase/2017ImageReadBase/build /home/jaspadar/cpe419/lab3/2017ImageReadBase/2017ImageReadBase/build/CMakeFiles/readImg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/readImg.dir/depend

