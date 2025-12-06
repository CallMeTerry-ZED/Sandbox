cmake_minimum_required(VERSION 3.10)
project(imgui)

# Core ImGui sources
set(IMGUI_SOURCES
    imgui.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
)

# Backends (GLFW + OpenGL3)
set(IMGUI_BACKEND_SOURCES
    backends/imgui_impl_glfw.cpp
    backends/imgui_impl_opengl3.cpp
)

# Create static library
add_library(imgui STATIC
    ${IMGUI_SOURCES}
    ${IMGUI_BACKEND_SOURCES}
)

# Include directories
target_include_directories(imgui
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/backends
)

# Link GLFW (needed for imgui_impl_glfw)
find_package(glfw3 QUIET)
if(NOT glfw3_FOUND)
endif()