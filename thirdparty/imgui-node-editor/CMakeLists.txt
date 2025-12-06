cmake_minimum_required(VERSION 3.10)
project(imgui_node_editor)

# Node editor sources
set(NODE_EDITOR_SOURCES
    imgui_node_editor.cpp
    imgui_node_editor_api.cpp
    imgui_canvas.cpp
    crude_json.cpp
)

# Create static library
add_library(imgui_node_editor STATIC
    ${NODE_EDITOR_SOURCES}
)

# Include directories - ADD IMGUI PATH HERE
target_include_directories(imgui_node_editor
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/../imgui-docking
)

# Link against imgui (if imgui target exists)
if(TARGET imgui)
    target_link_libraries(imgui_node_editor PRIVATE imgui)
endif()