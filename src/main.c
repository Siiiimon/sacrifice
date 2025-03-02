#include "raylib.h"
#include "cimgui_include.h"

#include "game_context.h"
#include "ecs/entity_manager.h"
#include "ecs/physics/position_component.h"
#include "ecs/physics/movement_system.h"
#include "render/render_system.h"
#include "render/sprite_component.h"
#include "texture_io.h"
#include <stdlib.h>

struct GameContext* game_context = NULL;

int main(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    InitWindow(1280, 720, "Sacrifice");

    game_context = malloc(sizeof(struct GameContext));
    game_context->game_width = 1280;
    game_context->game_height = 720;

    Texture cat = LoadTextureFromFile("assets/sprites/cat.png");

    game_context->world = malloc(sizeof(struct World));
    game_context->world->entities = NewEntityManager();
    game_context->world->positions = NewPositionComponentArray();
    game_context->world->velocities = NewVelocityComponentArray();
    game_context->world->sprites = NewSpriteComponentArray();

    unsigned int player = NewEntity(game_context->world->entities);
    TraceLog(LOG_INFO, "player id: %u", player);
    AddPositionToEntity(player, game_context->world->positions, game_context->game_width / 2, game_context->game_height / 2);
    AddVelocityToEntity(player, game_context->world->velocities, 1.0f, -1.0f);
    AddSpriteToEntity(player, game_context->world->sprites, cat);

    rlImGuiSetup(true);

    ImGuiIO* io = igGetIO();
    io->FontGlobalScale = 1.0f / GetWindowScaleDPI().x;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateMovement(game_context->world->positions, game_context->world->velocities);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        RenderSprites(game_context->world->sprites, game_context->world->positions);

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

        unsigned int active_entity_count;
        unsigned int* active_entities = GetActiveEntities(game_context->world->entities, &active_entity_count);
        if (active_entities != NULL) {
            for (unsigned int i = 0; i <= active_entity_count; ++i) {
                unsigned int entity = active_entities[i];
                igText("Entity ID: %u", entity);
                struct PositionComponent* position = GetPosition(game_context->world->positions, entity);
                if (position) {
                    igText("Position: (%f, %f)", position->x, position->y);
                }
                struct VelocityComponent* velocity = GetVelocity(game_context->world->velocities, entity);
                if (velocity) {
                    igText("Velocity: (%f, %f)", velocity->x, velocity->y);
                }
                // struct SpriteComponent* sprite = GetSprite(game_context->world->sprites, entity);
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
