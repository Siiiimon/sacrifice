#include "raylib.h"
#include "cimgui_include.h"

#include "game_context.h"
#include "ecs/physics/position_component.h"
#include "ecs/physics/movement_system.h"
#include <stdlib.h>

struct GameContext* game_context = NULL;

int main(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    game_context = malloc(sizeof(struct GameContext));
    game_context->game_width = 1280;
    game_context->game_height = 720;

    game_context->world = malloc(sizeof(struct World));
    game_context->world->positions = NewPositionComponentArray();

    unsigned int player = 0;
    AddPositionToEntity(player, game_context->world->positions, game_context->game_width / 2, game_context->game_height / 2);

    InitWindow(1280, 720, "Sacrifice");
    rlImGuiSetup(true);

    ImGuiIO* io = igGetIO();
    io->FontGlobalScale = 1.0f / GetWindowScaleDPI().x;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateMovement(game_context->world->positions);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        // manually draw a box around the player entity for now
        struct PositionComponent* player_position = GetPosition(game_context->world->positions, player);
        DrawRectangle(player_position->x - 10, player_position->y - 10, 20, 20, RED);

#ifdef DEBUG
        rlImGuiBegin();

        igBegin("Debug", NULL, 0);
        if (igCollapsingHeader_TreeNodeFlags("Performance", ImGuiTreeNodeFlags_DefaultOpen)) {
            igText("FPS: %d", GetFPS());
        }
        if (igCollapsingHeader_TreeNodeFlags("System", ImGuiTreeNodeFlags_DefaultOpen)) {
            igText("DPI scale: %f", GetWindowScaleDPI().x);
            igText("Platform: %s",
            #if defined(_WIN32)
                "Windows"
            #elif defined(__APPLE__)
                "macOS"
            #elif defined(__linux__)
                "Linux"
            #else
                "Unknown"
            #endif
            );
        }
        igEnd();

        rlImGuiEnd();
#endif

        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}
