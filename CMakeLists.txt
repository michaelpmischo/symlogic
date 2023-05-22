set(VERSIONS 3.0...3.26)
set(DEPTH 0)

# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
message("CMake [${DEPTH}] Entering ./")
cmake_minimum_required(VERSION ${VERSIONS})

# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables
project(Mathematics VERSION 0.0.1 LANGUAGES CXX)

if (MSVC)
set(CCFLAGS /Wall /std:c++17)
else()
set(CCFLAGS -g -Wall -pedantic -std=c++17)
endif()
add_compile_options(${CCFLAGS})

# If you set any CMAKE_ variables, that can go here.
# (But usually don't do this, except maybe for C++ standard)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

#add_compile_definitions(__WCHAR_EXPRESSIONS__)
#add_compile_definitions(__UTF32_EXPRESSIONS__)
#add_compile_definitions(__UTF16_EXPRESSIONS__)
#add_compile_definitions(__UTF8_EXPRESSIONS__)
add_compile_definitions(__ASCII_EXPRESSIONS__)

## Test to see if int128 is availabe.
add_compile_definitions(__CHECK_FOR_INT128__)

set(CMAKE_EXE_LINKER_FLAGS)

# Include the Library: libMathematics 
include("src/CMakeLists.txt")

# Include the test Executable and Build it.
include("test/CMakeLists.txt")

message("CMake [${DEPTH}] Leaving ./")