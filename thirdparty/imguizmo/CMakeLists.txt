cmake_minimum_required(VERSION 3.10)
project(imguizmo)

# ImGuizmo sources
set(IMGUIZMO_SOURCES
    ImGuizmo.cpp
    ImCurveEdit.cpp
    ImGradient.cpp
    ImSequencer.cpp
    GraphEditor.cpp
)

# Create static library
add_library(imguizmo STATIC
    ${IMGUIZMO_SOURCES}
)

# Include directories - ADD IMGUI PATH HERE
target_include_directories(imguizmo
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/../imgui-docking
)

# Link against imgui (if imgui target exists)
if(TARGET imgui)
    target_link_libraries(imguizmo PRIVATE imgui)
endif()