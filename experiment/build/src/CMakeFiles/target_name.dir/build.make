# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shunxu/QtProj/DayLight/experiment

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shunxu/QtProj/DayLight/experiment/build

# Include any dependencies generated for this target.
include src/CMakeFiles/target_name.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/target_name.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/target_name.dir/flags.make

src/CMakeFiles/target_name.dir/main.cpp.o: src/CMakeFiles/target_name.dir/flags.make
src/CMakeFiles/target_name.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shunxu/QtProj/DayLight/experiment/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/target_name.dir/main.cpp.o"
	cd /home/shunxu/QtProj/DayLight/experiment/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/target_name.dir/main.cpp.o -c /home/shunxu/QtProj/DayLight/experiment/src/main.cpp

src/CMakeFiles/target_name.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/target_name.dir/main.cpp.i"
	cd /home/shunxu/QtProj/DayLight/experiment/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shunxu/QtProj/DayLight/experiment/src/main.cpp > CMakeFiles/target_name.dir/main.cpp.i

src/CMakeFiles/target_name.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/target_name.dir/main.cpp.s"
	cd /home/shunxu/QtProj/DayLight/experiment/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shunxu/QtProj/DayLight/experiment/src/main.cpp -o CMakeFiles/target_name.dir/main.cpp.s

src/CMakeFiles/target_name.dir/main.cpp.o.requires:

.PHONY : src/CMakeFiles/target_name.dir/main.cpp.o.requires

src/CMakeFiles/target_name.dir/main.cpp.o.provides: src/CMakeFiles/target_name.dir/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/target_name.dir/build.make src/CMakeFiles/target_name.dir/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/target_name.dir/main.cpp.o.provides

src/CMakeFiles/target_name.dir/main.cpp.o.provides.build: src/CMakeFiles/target_name.dir/main.cpp.o


# Object files for target target_name
target_name_OBJECTS = \
"CMakeFiles/target_name.dir/main.cpp.o"

# External object files for target target_name
target_name_EXTERNAL_OBJECTS =

src/target_name: src/CMakeFiles/target_name.dir/main.cpp.o
src/target_name: src/CMakeFiles/target_name.dir/build.make
src/target_name: src/CMakeFiles/target_name.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shunxu/QtProj/DayLight/experiment/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable target_name"
	cd /home/shunxu/QtProj/DayLight/experiment/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/target_name.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/target_name.dir/build: src/target_name

.PHONY : src/CMakeFiles/target_name.dir/build

src/CMakeFiles/target_name.dir/requires: src/CMakeFiles/target_name.dir/main.cpp.o.requires

.PHONY : src/CMakeFiles/target_name.dir/requires

src/CMakeFiles/target_name.dir/clean:
	cd /home/shunxu/QtProj/DayLight/experiment/build/src && $(CMAKE_COMMAND) -P CMakeFiles/target_name.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/target_name.dir/clean

src/CMakeFiles/target_name.dir/depend:
	cd /home/shunxu/QtProj/DayLight/experiment/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shunxu/QtProj/DayLight/experiment /home/shunxu/QtProj/DayLight/experiment/src /home/shunxu/QtProj/DayLight/experiment/build /home/shunxu/QtProj/DayLight/experiment/build/src /home/shunxu/QtProj/DayLight/experiment/build/src/CMakeFiles/target_name.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/target_name.dir/depend

