# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.3.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\All Alex Files\Code\UF_DataStructures_HW\Art-Chart"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\All Alex Files\Code\UF_DataStructures_HW\Art-Chart\cmake-build-release"

# Include any dependencies generated for this target.
include CMakeFiles/ArtChart.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ArtChart.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ArtChart.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ArtChart.dir/flags.make

CMakeFiles/ArtChart.dir/main.cpp.obj: CMakeFiles/ArtChart.dir/flags.make
CMakeFiles/ArtChart.dir/main.cpp.obj: ../main.cpp
CMakeFiles/ArtChart.dir/main.cpp.obj: CMakeFiles/ArtChart.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\All Alex Files\Code\UF_DataStructures_HW\Art-Chart\cmake-build-release\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ArtChart.dir/main.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ArtChart.dir/main.cpp.obj -MF CMakeFiles\ArtChart.dir\main.cpp.obj.d -o CMakeFiles\ArtChart.dir\main.cpp.obj -c "C:\All Alex Files\Code\UF_DataStructures_HW\Art-Chart\main.cpp"

CMakeFiles/ArtChart.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArtChart.dir/main.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\All Alex Files\Code\UF_DataStructures_HW\Art-Chart\main.cpp" > CMakeFiles\ArtChart.dir\main.cpp.i

CMakeFiles/ArtChart.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArtChart.dir/main.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\All Alex Files\Code\UF_DataStructures_HW\Art-Chart\main.cpp" -o CMakeFiles\ArtChart.dir\main.cpp.s

# Object files for target ArtChart
ArtChart_OBJECTS = \
"CMakeFiles/ArtChart.dir/main.cpp.obj"

# External object files for target ArtChart
ArtChart_EXTERNAL_OBJECTS =

ArtChart.exe: CMakeFiles/ArtChart.dir/main.cpp.obj
ArtChart.exe: CMakeFiles/ArtChart.dir/build.make
ArtChart.exe: CMakeFiles/ArtChart.dir/linklibs.rsp
ArtChart.exe: CMakeFiles/ArtChart.dir/objects1.rsp
ArtChart.exe: CMakeFiles/ArtChart.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\All Alex Files\Code\UF_DataStructures_HW\Art-Chart\cmake-build-release\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ArtChart.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ArtChart.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ArtChart.dir/build: ArtChart.exe
.PHONY : CMakeFiles/ArtChart.dir/build

CMakeFiles/ArtChart.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ArtChart.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ArtChart.dir/clean

CMakeFiles/ArtChart.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\All Alex Files\Code\UF_DataStructures_HW\Art-Chart" "C:\All Alex Files\Code\UF_DataStructures_HW\Art-Chart" "C:\All Alex Files\Code\UF_DataStructures_HW\Art-Chart\cmake-build-release" "C:\All Alex Files\Code\UF_DataStructures_HW\Art-Chart\cmake-build-release" "C:\All Alex Files\Code\UF_DataStructures_HW\Art-Chart\cmake-build-release\CMakeFiles\ArtChart.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/ArtChart.dir/depend

