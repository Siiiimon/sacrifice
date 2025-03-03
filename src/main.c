#include "raylib.h"

#include "game_context.h"
#include "ecs/entity_manager.h"
#include "ecs/physics/position_component.h"
#include "ecs/physics/movement_system.h"
#include "ecs/physics/collider_component.h"
#include "ecs/physics/collision_system.h"
#include "ecs/physics/map_bounds_system.h"
#include "raymath.h"
#include "render/render_system.h"
#include "render/sprite_component.h"
#include "tag_component.h"
#include "texture_io.h"
#include "input.h"
#include "velocity_component.h"
#include <stdlib.h>
#include "debug/debug.h"

#include <chase_behaviour_system.h>
#include <combat_system.h>
#include <harm_component.h>
#include <health_component.h>

struct GameContext* game_context = NULL;

int main(void)
{
#ifdef DEBUG
    SetTraceLogLevel(LOG_DEBUG);
#endif

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    InitWindow(1280, 720, "Sacrifice");

    game_context = malloc(sizeof(struct GameContext));
    game_context->game_width = 1280;
    game_context->game_height = 720;

    Texture cat = LoadTextureFromFile("assets/sprites/cat.png");
    Texture wall_text = LoadTextureFromFile("assets/sprites/wall.png");
    Texture rotund_text = LoadTextureFromFile("assets/sprites/rotund_specimen.png");

    game_context->world = malloc(sizeof(struct World));
    game_context->world->entities = NewEntityManager();
    game_context->world->tags = NewTagComponentArray();
    game_context->world->positions = NewPositionComponentArray();
    game_context->world->velocities = NewVelocityComponentArray();
    game_context->world->sprites = NewSpriteComponentArray();
    game_context->world->colliders = NewColliderComponentArray();
    game_context->world->healths = NewHealthComponentArray();
    game_context->world->harms = NewHarmComponentArray();
    game_context->world->chase_behaviours = NewChaseBehaviourComponentArray();

    game_context->world->player_move_speed = 6.0f;

    game_context->world->debug_layer = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    game_context->world->should_draw_collision_bounds = false;

    unsigned int player = NewEntity(game_context->world->entities);
    unsigned int wall_a = NewEntity(game_context->world->entities);
    // unsigned int wall_b = NewEntity(game_context->world->entities);
    unsigned int rotund = NewEntity(game_context->world->entities);

    AddTagToEntity(player, game_context->world->tags, ENTITY_TAG_PLAYER);
    AddPositionToEntity(player, game_context->world->positions, game_context->game_width / 2, game_context->game_height / 2);
    AddVelocityToEntity(player, game_context->world->velocities, 0.0f, 0.0f);
    AddSpriteToEntity(player, game_context->world->sprites, cat);
    AddRectangleColliderToEntity(player, game_context->world->colliders, cat.width, cat.height, CLITERAL(Vector2){cat.width / 2, cat.height / 2}, true);
    AddHealthToEntity(player, game_context->world->healths, 100);
    // AddCircleColliderToEntity(player, game_context->world->colliders, cat.height / 2, CLITERAL(Vector2){cat.width / 2, cat.height / 2});

    AddTagToEntity(wall_a, game_context->world->tags, ENTITY_TAG_WALL);
    AddPositionToEntity(wall_a, game_context->world->positions, 200, (game_context->game_height / 2) - 75);
    AddSpriteToEntity(wall_a, game_context->world->sprites, wall_text);
    AddRectangleColliderToEntity(wall_a, game_context->world->colliders, wall_text.width, wall_text.height, CLITERAL(Vector2){wall_text.width / 2, wall_text.height / 2}, true);

    // AddPositionToEntity(wall_b, game_context->world->positions, 200, (game_context->game_height / 2) + 25);
    // AddSpriteToEntity(wall_b, game_context->world->sprites, wall_text);
    // AddRectangleColliderToEntity(wall_b, game_context->world->colliders, wall_text.width, wall_text.height, CLITERAL(Vector2){wall_text.width / 2, wall_text.height / 2}, true);

    AddTagToEntity(rotund, game_context->world->tags, ENTITY_TAG_ENEMY);
    AddPositionToEntity(rotund, game_context->world->positions, game_context->game_width - 300, game_context->game_height / 2);
    AddVelocityToEntity(rotund, game_context->world->velocities, 0.0f, 0.0f);
    AddSpriteToEntity(rotund, game_context->world->sprites, rotund_text);
    AddCircleColliderToEntity(rotund, game_context->world->colliders, rotund_text.width / 2, CLITERAL(Vector2){rotund_text.width / 2, rotund_text.height / 2}, true);
    AddChaseBehaviourToEntity(rotund, game_context->world->chase_behaviours, player);
    AddHarmToEntity(rotund, game_context->world->harms, 10);

    struct VelocityComponent* player_velocity = GetVelocity(game_context->world->velocities, player);
    struct HealthComponent* player_health = GetHealth(game_context->world->healths, player);

    rlImGuiSetup(true);

    ImGuiIO* io = igGetIO();
    io->FontGlobalScale = 1.0f / GetWindowScaleDPI().x;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
#ifdef DEBUG
        BeginTextureMode(game_context->world->debug_layer);
        ClearBackground(BLANK);
        EndTextureMode();
#endif

        Vector2 player_movement = Vector2Scale(GetMovementInput(), game_context->world->player_move_speed);

        if (player_velocity) {
            player_velocity->x = player_movement.x;
            player_velocity->y = player_movement.y;
        }

        UpdateMovement(game_context->world->positions, game_context->world->velocities);
        UpdateChaseBehaviours(game_context->world->positions, game_context->world->velocities, game_context->world->chase_behaviours);
        UpdateColliders(game_context->world->positions, game_context->world->colliders, game_context->world->tags);
        UpdateMapBounds(game_context->world->positions, game_context->world->colliders, CLITERAL(Vector2){game_context->game_width, game_context->game_height});
        if (game_context->world->should_draw_collision_bounds) {
            DrawCollisionBounds(game_context->world->debug_layer, game_context->world->positions, game_context->world->colliders);
        }
        UpdateCombat(game_context->world->colliders, game_context->world->harms, game_context->world->healths);

        BeginDrawing();

        ClearBackground(DARKGRAY);

        RenderSprites(game_context->world->sprites, game_context->world->positions);

        // manually drawing player health bar for now
        DrawRectangleLinesEx(
            CLITERAL(Rectangle){10.0f, 10.0f, 500.0f, 15.0f},
            2.0f,
            RAYWHITE
        );
        if (player_health) {
            DrawRectangleRec(
                CLITERAL(Rectangle){10.0f, 10.0f, player_health->current_health * 5, 15.0f},
                GREEN
            );
        }


#ifdef DEBUG
        rlImGuiBegin();

        DrawDebugUI(game_context);

        DrawTextureRec(
            game_context->world->debug_layer.texture,
            CLITERAL(Rectangle){0, 0, GetScreenWidth(), -GetScreenHeight()},
            CLITERAL(Vector2){0, 0},
            WHITE
        );

        rlImGuiEnd();

#endif

        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}
