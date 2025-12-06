cmake_minimum_required(VERSION 3.10)
project(glad)

# Create a static library from glad.c
add_library(glad STATIC glad.c)

# Make the headers visible to any target that links glad
target_include_directories(glad
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
