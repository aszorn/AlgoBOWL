# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /cygdrive/c/Users/Abbey/.CLion2017.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Abbey/.CLion2017.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/Abbey/Documents/School/Algorithms/c++/Algobowl_attempt1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/Abbey/Documents/School/Algorithms/c++/Algobowl_attempt1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Algobowl_attempt1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Algobowl_attempt1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Algobowl_attempt1.dir/flags.make

CMakeFiles/Algobowl_attempt1.dir/main.cpp.o: CMakeFiles/Algobowl_attempt1.dir/flags.make
CMakeFiles/Algobowl_attempt1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Abbey/Documents/School/Algorithms/c++/Algobowl_attempt1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Algobowl_attempt1.dir/main.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Algobowl_attempt1.dir/main.cpp.o -c /cygdrive/c/Users/Abbey/Documents/School/Algorithms/c++/Algobowl_attempt1/main.cpp

CMakeFiles/Algobowl_attempt1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Algobowl_attempt1.dir/main.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/Abbey/Documents/School/Algorithms/c++/Algobowl_attempt1/main.cpp > CMakeFiles/Algobowl_attempt1.dir/main.cpp.i

CMakeFiles/Algobowl_attempt1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Algobowl_attempt1.dir/main.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/Abbey/Documents/School/Algorithms/c++/Algobowl_attempt1/main.cpp -o CMakeFiles/Algobowl_attempt1.dir/main.cpp.s

CMakeFiles/Algobowl_attempt1.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Algobowl_attempt1.dir/main.cpp.o.requires

CMakeFiles/Algobowl_attempt1.dir/main.cpp.o.provides: CMakeFiles/Algobowl_attempt1.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Algobowl_attempt1.dir/build.make CMakeFiles/Algobowl_attempt1.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Algobowl_attempt1.dir/main.cpp.o.provides

CMakeFiles/Algobowl_attempt1.dir/main.cpp.o.provides.build: CMakeFiles/Algobowl_attempt1.dir/main.cpp.o


# Object files for target Algobowl_attempt1
Algobowl_attempt1_OBJECTS = \
"CMakeFiles/Algobowl_attempt1.dir/main.cpp.o"

# External object files for target Algobowl_attempt1
Algobowl_attempt1_EXTERNAL_OBJECTS =

Algobowl_attempt1.exe: CMakeFiles/Algobowl_attempt1.dir/main.cpp.o
Algobowl_attempt1.exe: CMakeFiles/Algobowl_attempt1.dir/build.make
Algobowl_attempt1.exe: CMakeFiles/Algobowl_attempt1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Abbey/Documents/School/Algorithms/c++/Algobowl_attempt1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Algobowl_attempt1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Algobowl_attempt1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Algobowl_attempt1.dir/build: Algobowl_attempt1.exe

.PHONY : CMakeFiles/Algobowl_attempt1.dir/build

CMakeFiles/Algobowl_attempt1.dir/requires: CMakeFiles/Algobowl_attempt1.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Algobowl_attempt1.dir/requires

CMakeFiles/Algobowl_attempt1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Algobowl_attempt1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Algobowl_attempt1.dir/clean

CMakeFiles/Algobowl_attempt1.dir/depend:
	cd /cygdrive/c/Users/Abbey/Documents/School/Algorithms/c++/Algobowl_attempt1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Abbey/Documents/School/Algorithms/c++/Algobowl_attempt1 /cygdrive/c/Users/Abbey/Documents/School/Algorithms/c++/Algobowl_attempt1 /cygdrive/c/Users/Abbey/Documents/School/Algorithms/c++/Algobowl_attempt1/cmake-build-debug /cygdrive/c/Users/Abbey/Documents/School/Algorithms/c++/Algobowl_attempt1/cmake-build-debug /cygdrive/c/Users/Abbey/Documents/School/Algorithms/c++/Algobowl_attempt1/cmake-build-debug/CMakeFiles/Algobowl_attempt1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Algobowl_attempt1.dir/depend

