## ============================================================================
##! @file src/CMakeLists.txt
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
## ============================================================================>
set(VERSIONS 3.0...3.26)
set(DEPTH 0)

set(ROOT "./src/Types")
set(LIBRARY libTypes)

# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
message("CMake [${DEPTH}] Entering ${ROOT}")
cmake_minimum_required(VERSION ${VERSIONS})

# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables
project(${LIBRARY} VERSION 0.0.1 LANGUAGES CXX)

# Pinting to the include directory helps resolve the includes.
include_directories(${LIBRARY} "src/")

# Include the SRCS and HDRS from these CMakeLists.txt file.
file(GLOB_RECURSE SRCS ${ROOT}/*.cpp)
file(GLOB_RECURSE HDRS ${ROOT}/*.h)

message(STATUS ${SRCS})
message(STATUS ${HDRS})

# Other common choices are STATIC, SHARED, and MODULE
# Including header files here helps IDEs but is not required.
# Output libname matches target name, with the usual extensions on your system
add_library(${LIBRARY} STATIC ${SRCS} ${HDRS})

message("CMake [${DEPTH}] Leaving ${ROOT}")