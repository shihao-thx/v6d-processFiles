# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/hao/Desktop/v6d-processFiles

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hao/Desktop/v6d-processFiles/build

# Include any dependencies generated for this target.
include thirdparty/hiredis/CMakeFiles/hiredis.dir/depend.make

# Include the progress variables for this target.
include thirdparty/hiredis/CMakeFiles/hiredis.dir/progress.make

# Include the compile flags for this target's objects.
include thirdparty/hiredis/CMakeFiles/hiredis.dir/flags.make

thirdparty/hiredis/CMakeFiles/hiredis.dir/alloc.c.o: thirdparty/hiredis/CMakeFiles/hiredis.dir/flags.make
thirdparty/hiredis/CMakeFiles/hiredis.dir/alloc.c.o: ../thirdparty/hiredis/alloc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hao/Desktop/v6d-processFiles/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object thirdparty/hiredis/CMakeFiles/hiredis.dir/alloc.c.o"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hiredis.dir/alloc.c.o   -c /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/alloc.c

thirdparty/hiredis/CMakeFiles/hiredis.dir/alloc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hiredis.dir/alloc.c.i"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/alloc.c > CMakeFiles/hiredis.dir/alloc.c.i

thirdparty/hiredis/CMakeFiles/hiredis.dir/alloc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hiredis.dir/alloc.c.s"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/alloc.c -o CMakeFiles/hiredis.dir/alloc.c.s

thirdparty/hiredis/CMakeFiles/hiredis.dir/async.c.o: thirdparty/hiredis/CMakeFiles/hiredis.dir/flags.make
thirdparty/hiredis/CMakeFiles/hiredis.dir/async.c.o: ../thirdparty/hiredis/async.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hao/Desktop/v6d-processFiles/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object thirdparty/hiredis/CMakeFiles/hiredis.dir/async.c.o"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hiredis.dir/async.c.o   -c /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/async.c

thirdparty/hiredis/CMakeFiles/hiredis.dir/async.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hiredis.dir/async.c.i"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/async.c > CMakeFiles/hiredis.dir/async.c.i

thirdparty/hiredis/CMakeFiles/hiredis.dir/async.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hiredis.dir/async.c.s"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/async.c -o CMakeFiles/hiredis.dir/async.c.s

thirdparty/hiredis/CMakeFiles/hiredis.dir/dict.c.o: thirdparty/hiredis/CMakeFiles/hiredis.dir/flags.make
thirdparty/hiredis/CMakeFiles/hiredis.dir/dict.c.o: ../thirdparty/hiredis/dict.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hao/Desktop/v6d-processFiles/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object thirdparty/hiredis/CMakeFiles/hiredis.dir/dict.c.o"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hiredis.dir/dict.c.o   -c /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/dict.c

thirdparty/hiredis/CMakeFiles/hiredis.dir/dict.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hiredis.dir/dict.c.i"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/dict.c > CMakeFiles/hiredis.dir/dict.c.i

thirdparty/hiredis/CMakeFiles/hiredis.dir/dict.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hiredis.dir/dict.c.s"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/dict.c -o CMakeFiles/hiredis.dir/dict.c.s

thirdparty/hiredis/CMakeFiles/hiredis.dir/hiredis.c.o: thirdparty/hiredis/CMakeFiles/hiredis.dir/flags.make
thirdparty/hiredis/CMakeFiles/hiredis.dir/hiredis.c.o: ../thirdparty/hiredis/hiredis.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hao/Desktop/v6d-processFiles/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object thirdparty/hiredis/CMakeFiles/hiredis.dir/hiredis.c.o"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hiredis.dir/hiredis.c.o   -c /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/hiredis.c

thirdparty/hiredis/CMakeFiles/hiredis.dir/hiredis.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hiredis.dir/hiredis.c.i"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/hiredis.c > CMakeFiles/hiredis.dir/hiredis.c.i

thirdparty/hiredis/CMakeFiles/hiredis.dir/hiredis.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hiredis.dir/hiredis.c.s"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/hiredis.c -o CMakeFiles/hiredis.dir/hiredis.c.s

thirdparty/hiredis/CMakeFiles/hiredis.dir/net.c.o: thirdparty/hiredis/CMakeFiles/hiredis.dir/flags.make
thirdparty/hiredis/CMakeFiles/hiredis.dir/net.c.o: ../thirdparty/hiredis/net.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hao/Desktop/v6d-processFiles/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object thirdparty/hiredis/CMakeFiles/hiredis.dir/net.c.o"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hiredis.dir/net.c.o   -c /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/net.c

thirdparty/hiredis/CMakeFiles/hiredis.dir/net.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hiredis.dir/net.c.i"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/net.c > CMakeFiles/hiredis.dir/net.c.i

thirdparty/hiredis/CMakeFiles/hiredis.dir/net.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hiredis.dir/net.c.s"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/net.c -o CMakeFiles/hiredis.dir/net.c.s

thirdparty/hiredis/CMakeFiles/hiredis.dir/read.c.o: thirdparty/hiredis/CMakeFiles/hiredis.dir/flags.make
thirdparty/hiredis/CMakeFiles/hiredis.dir/read.c.o: ../thirdparty/hiredis/read.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hao/Desktop/v6d-processFiles/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object thirdparty/hiredis/CMakeFiles/hiredis.dir/read.c.o"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hiredis.dir/read.c.o   -c /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/read.c

thirdparty/hiredis/CMakeFiles/hiredis.dir/read.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hiredis.dir/read.c.i"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/read.c > CMakeFiles/hiredis.dir/read.c.i

thirdparty/hiredis/CMakeFiles/hiredis.dir/read.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hiredis.dir/read.c.s"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/read.c -o CMakeFiles/hiredis.dir/read.c.s

thirdparty/hiredis/CMakeFiles/hiredis.dir/sds.c.o: thirdparty/hiredis/CMakeFiles/hiredis.dir/flags.make
thirdparty/hiredis/CMakeFiles/hiredis.dir/sds.c.o: ../thirdparty/hiredis/sds.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hao/Desktop/v6d-processFiles/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object thirdparty/hiredis/CMakeFiles/hiredis.dir/sds.c.o"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hiredis.dir/sds.c.o   -c /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/sds.c

thirdparty/hiredis/CMakeFiles/hiredis.dir/sds.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hiredis.dir/sds.c.i"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/sds.c > CMakeFiles/hiredis.dir/sds.c.i

thirdparty/hiredis/CMakeFiles/hiredis.dir/sds.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hiredis.dir/sds.c.s"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/sds.c -o CMakeFiles/hiredis.dir/sds.c.s

thirdparty/hiredis/CMakeFiles/hiredis.dir/sockcompat.c.o: thirdparty/hiredis/CMakeFiles/hiredis.dir/flags.make
thirdparty/hiredis/CMakeFiles/hiredis.dir/sockcompat.c.o: ../thirdparty/hiredis/sockcompat.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hao/Desktop/v6d-processFiles/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object thirdparty/hiredis/CMakeFiles/hiredis.dir/sockcompat.c.o"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hiredis.dir/sockcompat.c.o   -c /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/sockcompat.c

thirdparty/hiredis/CMakeFiles/hiredis.dir/sockcompat.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hiredis.dir/sockcompat.c.i"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/sockcompat.c > CMakeFiles/hiredis.dir/sockcompat.c.i

thirdparty/hiredis/CMakeFiles/hiredis.dir/sockcompat.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hiredis.dir/sockcompat.c.s"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis/sockcompat.c -o CMakeFiles/hiredis.dir/sockcompat.c.s

# Object files for target hiredis
hiredis_OBJECTS = \
"CMakeFiles/hiredis.dir/alloc.c.o" \
"CMakeFiles/hiredis.dir/async.c.o" \
"CMakeFiles/hiredis.dir/dict.c.o" \
"CMakeFiles/hiredis.dir/hiredis.c.o" \
"CMakeFiles/hiredis.dir/net.c.o" \
"CMakeFiles/hiredis.dir/read.c.o" \
"CMakeFiles/hiredis.dir/sds.c.o" \
"CMakeFiles/hiredis.dir/sockcompat.c.o"

# External object files for target hiredis
hiredis_EXTERNAL_OBJECTS =

thirdparty/hiredis/libhiredis.so.1.0.3-dev: thirdparty/hiredis/CMakeFiles/hiredis.dir/alloc.c.o
thirdparty/hiredis/libhiredis.so.1.0.3-dev: thirdparty/hiredis/CMakeFiles/hiredis.dir/async.c.o
thirdparty/hiredis/libhiredis.so.1.0.3-dev: thirdparty/hiredis/CMakeFiles/hiredis.dir/dict.c.o
thirdparty/hiredis/libhiredis.so.1.0.3-dev: thirdparty/hiredis/CMakeFiles/hiredis.dir/hiredis.c.o
thirdparty/hiredis/libhiredis.so.1.0.3-dev: thirdparty/hiredis/CMakeFiles/hiredis.dir/net.c.o
thirdparty/hiredis/libhiredis.so.1.0.3-dev: thirdparty/hiredis/CMakeFiles/hiredis.dir/read.c.o
thirdparty/hiredis/libhiredis.so.1.0.3-dev: thirdparty/hiredis/CMakeFiles/hiredis.dir/sds.c.o
thirdparty/hiredis/libhiredis.so.1.0.3-dev: thirdparty/hiredis/CMakeFiles/hiredis.dir/sockcompat.c.o
thirdparty/hiredis/libhiredis.so.1.0.3-dev: thirdparty/hiredis/CMakeFiles/hiredis.dir/build.make
thirdparty/hiredis/libhiredis.so.1.0.3-dev: thirdparty/hiredis/CMakeFiles/hiredis.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hao/Desktop/v6d-processFiles/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C shared library libhiredis.so"
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hiredis.dir/link.txt --verbose=$(VERBOSE)
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && $(CMAKE_COMMAND) -E cmake_symlink_library libhiredis.so.1.0.3-dev libhiredis.so.1.0.3-dev libhiredis.so

thirdparty/hiredis/libhiredis.so: thirdparty/hiredis/libhiredis.so.1.0.3-dev
	@$(CMAKE_COMMAND) -E touch_nocreate thirdparty/hiredis/libhiredis.so

# Rule to build all files generated by this target.
thirdparty/hiredis/CMakeFiles/hiredis.dir/build: thirdparty/hiredis/libhiredis.so

.PHONY : thirdparty/hiredis/CMakeFiles/hiredis.dir/build

thirdparty/hiredis/CMakeFiles/hiredis.dir/clean:
	cd /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis && $(CMAKE_COMMAND) -P CMakeFiles/hiredis.dir/cmake_clean.cmake
.PHONY : thirdparty/hiredis/CMakeFiles/hiredis.dir/clean

thirdparty/hiredis/CMakeFiles/hiredis.dir/depend:
	cd /home/hao/Desktop/v6d-processFiles/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hao/Desktop/v6d-processFiles /home/hao/Desktop/v6d-processFiles/thirdparty/hiredis /home/hao/Desktop/v6d-processFiles/build /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis /home/hao/Desktop/v6d-processFiles/build/thirdparty/hiredis/CMakeFiles/hiredis.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : thirdparty/hiredis/CMakeFiles/hiredis.dir/depend
