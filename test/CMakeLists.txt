## ============================================================================
##! @file test/CMakeLists.txt
##! @author Michael P. MIscho
##! @date May 4, 2023
##! @brief This file is the header for the Integer number type header.
##! @see 
## ____________________________________________________________________________
##! @copyright Copyright (C) 2024 Michael P, Mischo - All Rights Reserved
##! You may use, distribute and modify this code under the terms of the GPL
##! license. You should have received a copy of the GPL license with this 
##! file. If not, please write to: , or visit :
##! https:##www.gnu.org/licenses/gpl-3.0.en.html
## ============================================================================
MATH(EXPR DEPTH "${DEPTH}+1")

# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
message("CMake [${DEPTH}] Entering ./test")
cmake_minimum_required(VERSION ${VERSIONS})

# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables
project(Test VERSION 0.0.1 LANGUAGES CXX)

# Link each target with other targets or add options, etc.

# Pinting to the include directory helps resolve the includes.
include_directories(Test "test")
include_directories(Test  "src")

# Include the SRCS and HDRS from these CMakeLists.txt file.
file(GLOB_RECURSE TEST_SRCS test/*.cpp)
file(GLOB_RECURSE TEST_HDRS test/*.h)

message(STATUS ${TEST_SRCS})
message(STATUS ${TEST_HDRS})

# Adding something we can run - Output name matches target name
add_executable(Test "test/main.cpp" ${TEST_SRCS} ${TEST_HDRS})

# Make sure you link your targets with this command. It can also link libraries and
# even flags, so linking a target that does not exist will not give a configure-time error.
target_link_libraries(Test PRIVATE libMathematics)

message("CMake [${DEPTH}] Leaving ./tests")
MATH(EXPR DEPTH "${DEPTH}-1")