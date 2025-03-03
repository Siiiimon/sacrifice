cmake_minimum_required(VERSION 3.15)
project(sacrifice C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)  # Add C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Require C++11

option(BUILD_TESTS "Build tests" ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# build Raylib
add_subdirectory(vendor/raylib)

# build cimgui
add_subdirectory(vendor/cimgui)

# build rlImGui
add_library(rlImGui STATIC
    vendor/rlImGui/rlImGui.cpp
)
target_include_directories(rlImGui PRIVATE
    vendor/raylib/src
    vendor/cimgui
    vendor/cimgui/imgui
)
target_include_directories(rlImGui PUBLIC
    vendor/rlImGui
)
target_link_libraries(rlImGui PUBLIC cimgui raylib)
set_target_properties(rlImGui PROPERTIES
    LINKER_LANGUAGE CXX
    POSITION_INDEPENDENT_CODE ON
)

add_executable(${PROJECT_NAME}
    src/main.c

    src/io/texture_io.c

    src/input/input.c

    src/ecs/entity_manager.c
    src/ecs/tag_component.c
    src/ecs/render/render_system.c
    src/ecs/render/sprite_component.c
    src/ecs/physics/movement_system.c
    src/ecs/physics/collision_system.c
    src/ecs/physics/map_bounds_system.c
    src/ecs/physics/velocity_component.c
    src/ecs/physics/position_component.c
    src/ecs/physics/collider_component.c
    src/ecs/ai/chase_behaviour_system.c
    src/ecs/ai/chase_behaviour_component.c

    src/debug/debug.c
    src/debug/debug_entities.c
    src/debug/debug_entity.c
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib rlImGui cimgui)

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
    vendor/cimgui
    vendor/cimgui/imgui

    src
    src/io
    src/input
    src/ecs
    src/ecs/physics
    src/ecs/ai
    src/debug
)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
