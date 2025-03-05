include_directories(../vendor/greatest)

add_executable(sacrifice_tests
    test_main.c
    test_entity_manager.c
        ../src/ecs/ecs.c
    test_movement_system.c
    ../src/ecs/physics/movement_system.c
    ../src/ecs/physics/velocity_component.c
    ../src/ecs/physics/position_component.c
)

target_include_directories(sacrifice_tests PRIVATE
    ../vendor/raylib/src
    ../vendor/rlImGui
    ../vendor/cimgui
    ../vendor/cimgui/imgui
    ../vendor/greatest
    ../src
    ../src/ecs
    ../src/ecs/physics
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(sacrifice_tests PRIVATE DEBUG)

    target_compile_options(sacrifice_tests PRIVATE -g -O0 -Wall -Wextra -Wpedantic -Werror)
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
else()
    target_compile_options(sacrifice_tests PRIVATE -O3 -Wall -Wextra -Wpedantic -Werror)
endif()

target_link_libraries(sacrifice_tests PRIVATE raylib rlImGui cimgui)

if (APPLE)
    target_link_libraries(sacrifice_tests PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()

add_custom_target(test
    COMMAND sacrifice_tests
    DEPENDS sacrifice_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
