#include "raylib.h"
#include "cimgui_include.h"

#include "game_context.h"
#include "ecs/entity_manager.h"
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
    game_context->world->entities = NewEntityManager();
    game_context->world->positions = NewPositionComponentArray();
    game_context->world->velocities = NewVelocityComponentArray();

    unsigned int player = NewEntity(game_context->world->entities);
    AddPositionToEntity(player, game_context->world->positions, game_context->game_width / 2, game_context->game_height / 2);
    AddVelocityToEntity(player, game_context->world->velocities, 1.0f, -1.0f);

    InitWindow(1280, 720, "Sacrifice");
    rlImGuiSetup(true);

    ImGuiIO* io = igGetIO();
    io->FontGlobalScale = 1.0f / GetWindowScaleDPI().x;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateMovement(game_context->world->positions, game_context->world->velocities);

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

        igBegin("Entities", NULL, 0);
        if (igCollapsingHeader_TreeNodeFlags("Entity Manager", ImGuiTreeNodeFlags_DefaultOpen)) {
            igText("Next Entity Id: %u", game_context->world->entities->next_entity);
        }

        igSeparator();

        unsigned int* active_entities = GetActiveEntities(game_context->world->entities);
        if (active_entities != NULL) {
            for (unsigned int i = 0; i < game_context->world->entities->next_entity; ++i) {
                unsigned int entity = active_entities[i];
                igText("Entity ID: %u", entity);
                struct PositionComponent* entity_position = GetPosition(game_context->world->positions, entity);
                igText("Position: (%d, %d)", entity_position->x, entity_position->y);
            }
        }
        free(active_entities);
        igEnd();

        rlImGuiEnd();
#endif

        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}
