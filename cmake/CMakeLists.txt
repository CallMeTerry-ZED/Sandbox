# /*
#  * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
#  */

cmake_minimum_required(VERSION 3.10)

project(FPS VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type defaults to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Project root directory (parent of cmake directory)
get_filename_component(PROJECT_ROOT ${CMAKE_SOURCE_DIR} DIRECTORY)

# Add spdlog as subdirectory (with explicit binary directory)
add_subdirectory(${PROJECT_ROOT}/thridparty/spdlog ${CMAKE_BINARY_DIR}/thridparty/spdlog)

# Include directories
include_directories(
    ${PROJECT_ROOT}/include
)

# Source files - glob recursively for all .cpp files
file(GLOB_RECURSE SOURCES
    "${PROJECT_ROOT}/src/*.cpp"
    "${PROJECT_ROOT}/src/*.c"
)

# Header files - glob recursively for all header files
file(GLOB_RECURSE HEADERS
    "${PROJECT_ROOT}/include/*.h"
    "${PROJECT_ROOT}/include/*.hpp"
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# MSVC-specific options
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
        /permissive-
    )
endif()

