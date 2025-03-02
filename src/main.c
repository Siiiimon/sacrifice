#include "raylib.h"

#include "game_context.h"
#include "ecs/entity_manager.h"
#include "ecs/physics/position_component.h"
#include "ecs/physics/movement_system.h"
#include "raymath.h"
#include "render/render_system.h"
#include "render/sprite_component.h"
#include "texture_io.h"
#include "input.h"
#include "velocity_component.h"
#include <stdlib.h>
#include "debug/debug.h"

struct GameContext* game_context = NULL;

int main(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    InitWindow(1280, 720, "Sacrifice");

    game_context = malloc(sizeof(struct GameContext));
    game_context->game_width = 1280;
    game_context->game_height = 720;

    Texture cat = LoadTextureFromFile("assets/sprites/cat.png");
    Texture wall_text = LoadTextureFromFile("assets/sprites/wall.png");

    game_context->world = malloc(sizeof(struct World));
    game_context->world->entities = NewEntityManager();
    game_context->world->positions = NewPositionComponentArray();
    game_context->world->velocities = NewVelocityComponentArray();
    game_context->world->sprites = NewSpriteComponentArray();
    game_context->world->player_move_speed = 3.0f;

    unsigned int player = NewEntity(game_context->world->entities);
    unsigned int wall = NewEntity(game_context->world->entities);
    TraceLog(LOG_INFO, "player id: %u", player);
    TraceLog(LOG_INFO, "wall id: %u", wall);

    AddPositionToEntity(player, game_context->world->positions, game_context->game_width / 2, game_context->game_height / 2);
    AddVelocityToEntity(player, game_context->world->velocities, 0.0f, 0.0f);
    AddSpriteToEntity(player, game_context->world->sprites, cat);

    AddPositionToEntity(wall, game_context->world->positions, 200, (game_context->game_height / 2) - 75);
    AddSpriteToEntity(wall, game_context->world->sprites, wall_text);

    rlImGuiSetup(true);

    ImGuiIO* io = igGetIO();
    io->FontGlobalScale = 1.0f / GetWindowScaleDPI().x;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Vector2 player_movement = Vector2Scale(GetMovementInput(), game_context->world->player_move_speed);
        struct VelocityComponent* player_velocity = GetVelocity(game_context->world->velocities, player);

        player_velocity->x = player_movement.x;
        player_velocity->y = player_movement.y;

        UpdateMovement(game_context->world->positions, game_context->world->velocities);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        RenderSprites(game_context->world->sprites, game_context->world->positions);

#ifdef DEBUG
        rlImGuiBegin();

        DrawDebugUI(game_context);

        rlImGuiEnd();
#endif

        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}
