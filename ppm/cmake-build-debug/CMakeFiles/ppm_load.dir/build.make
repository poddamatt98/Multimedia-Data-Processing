# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\podda\CLionProjects\ppm_load

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\podda\CLionProjects\ppm_load\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ppm_load.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ppm_load.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ppm_load.dir/flags.make

CMakeFiles/ppm_load.dir/main.cpp.obj: CMakeFiles/ppm_load.dir/flags.make
CMakeFiles/ppm_load.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\podda\CLionProjects\ppm_load\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ppm_load.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ppm_load.dir\main.cpp.obj -c C:\Users\podda\CLionProjects\ppm_load\main.cpp

CMakeFiles/ppm_load.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ppm_load.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\podda\CLionProjects\ppm_load\main.cpp > CMakeFiles\ppm_load.dir\main.cpp.i

CMakeFiles/ppm_load.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ppm_load.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\podda\CLionProjects\ppm_load\main.cpp -o CMakeFiles\ppm_load.dir\main.cpp.s

CMakeFiles/ppm_load.dir/json.cpp.obj: CMakeFiles/ppm_load.dir/flags.make
CMakeFiles/ppm_load.dir/json.cpp.obj: ../json.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\podda\CLionProjects\ppm_load\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ppm_load.dir/json.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ppm_load.dir\json.cpp.obj -c C:\Users\podda\CLionProjects\ppm_load\json.cpp

CMakeFiles/ppm_load.dir/json.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ppm_load.dir/json.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\podda\CLionProjects\ppm_load\json.cpp > CMakeFiles\ppm_load.dir\json.cpp.i

CMakeFiles/ppm_load.dir/json.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ppm_load.dir/json.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\podda\CLionProjects\ppm_load\json.cpp -o CMakeFiles\ppm_load.dir\json.cpp.s

# Object files for target ppm_load
ppm_load_OBJECTS = \
"CMakeFiles/ppm_load.dir/main.cpp.obj" \
"CMakeFiles/ppm_load.dir/json.cpp.obj"

# External object files for target ppm_load
ppm_load_EXTERNAL_OBJECTS =

ppm_load.exe: CMakeFiles/ppm_load.dir/main.cpp.obj
ppm_load.exe: CMakeFiles/ppm_load.dir/json.cpp.obj
ppm_load.exe: CMakeFiles/ppm_load.dir/build.make
ppm_load.exe: CMakeFiles/ppm_load.dir/linklibs.rsp
ppm_load.exe: CMakeFiles/ppm_load.dir/objects1.rsp
ppm_load.exe: CMakeFiles/ppm_load.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\podda\CLionProjects\ppm_load\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ppm_load.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ppm_load.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ppm_load.dir/build: ppm_load.exe

.PHONY : CMakeFiles/ppm_load.dir/build

CMakeFiles/ppm_load.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ppm_load.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ppm_load.dir/clean

CMakeFiles/ppm_load.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\podda\CLionProjects\ppm_load C:\Users\podda\CLionProjects\ppm_load C:\Users\podda\CLionProjects\ppm_load\cmake-build-debug C:\Users\podda\CLionProjects\ppm_load\cmake-build-debug C:\Users\podda\CLionProjects\ppm_load\cmake-build-debug\CMakeFiles\ppm_load.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ppm_load.dir/depend

