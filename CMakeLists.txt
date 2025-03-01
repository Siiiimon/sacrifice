cmake_minimum_required(VERSION 3.15)
project(sacrifice C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11) # Requires C11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# build Raylib
add_subdirectory(vendor/raylib)

get_target_property(RAYLIB_INCLUDE_DIRS raylib INCLUDE_DIRECTORIES)

# build DearImGui
add_library(imgui STATIC
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_demo.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
    vendor/imgui
    ${RAYLIB_INCLUDE_DIRS}
)
set_target_properties(imgui PROPERTIES
    LINKER_LANGUAGE CXX
    POSITION_INDEPENDENT_CODE ON
)

# build rlImGui
add_library(rlImGui STATIC
    vendor/rlImGui/rlImGui.cpp
)
target_include_directories(rlImGui PUBLIC vendor/rlImGui vendor/imgui)
target_link_libraries(rlImGui PUBLIC imgui PRIVATE raylib)
set_target_properties(rlImGui PROPERTIES
    LINKER_LANGUAGE CXX
    POSITION_INDEPENDENT_CODE ON
)

add_library(imgui_wrapper STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/debug/imgui_wrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/debug/main_ui.cpp
)
target_include_directories(imgui_wrapper PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/debug
    vendor/imgui
    vendor/rlImGui
)
target_link_libraries(imgui_wrapper PRIVATE rlImGui imgui)
set_target_properties(imgui_wrapper PROPERTIES
    LINKER_LANGUAGE CXX
    POSITION_INDEPENDENT_CODE ON
)

add_executable(${PROJECT_NAME}
    src/main.c
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib rlImGui imgui_wrapper)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)

    target_compile_options(${PROJECT_NAME} PRIVATE -g -O0 -Wall -Wextra -Wpedantic -Werror)
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -O3 -Wall -Wextra -Wpedantic -Werror)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    vendor/raylib/src
    vendor/rlImGui
    vendor/imgui
    src/debug
)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()
