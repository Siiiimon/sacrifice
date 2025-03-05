#include "raylib.h"

#include "game_context.h"
#include "ecs/ecs.h"
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
#include <debug_data.h>
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

    game_context->debug_data = NewDebugData();

    Texture cat = LoadTextureFromFile("assets/sprites/cat.png");
    Texture wall_text = LoadTextureFromFile("assets/sprites/wall.png");
    Texture rotund_text = LoadTextureFromFile("assets/sprites/rotund_specimen.png");

    game_context->world = malloc(sizeof(struct World));
    game_context->world->ecs = NewECS();
    game_context->world->harms = NewHarmComponentArray();
    game_context->world->chase_behaviours = NewChaseBehaviourComponentArray();

    game_context->world->player_move_speed = 6.0f;

    game_context->world->debug_layer = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    game_context->world->should_draw_collision_bounds = false;

    Entity player = NewEntity(game_context->world->ecs);
    Entity wall_a = NewEntity(game_context->world->ecs);
    // unsigned int wall_b = NewEntity(game_context->world->entities);
    Entity rotund = NewEntity(game_context->world->ecs);

    AttachComponentToEntity(
        game_context->world->ecs,
        player,
        NewTag(ENTITY_TAG_PLAYER),
        COMPONENT_TYPE_TAG
    );
    AttachComponentToEntity(
        game_context->world->ecs,
        player,
        NewPosition(game_context->game_width / 2, game_context->game_height / 2),
        COMPONENT_TYPE_POSITION
    );
    AttachComponentToEntity(
        game_context->world->ecs,
        player,
        NewVelocity(0.0f, 0.0f),
        COMPONENT_TYPE_VELOCITY
    );
    AttachComponentToEntity(
        game_context->world->ecs,
        player,
        NewSprite(cat),
        COMPONENT_TYPE_SPRITE
    );
    AttachComponentToEntity(
        game_context->world->ecs,
        player,
        NewRectangleCollider(cat.width, cat.height, CLITERAL(Vector2){cat.width / 2, cat.height / 2}, true),
        COMPONENT_TYPE_COLLIDER
    );
    AttachComponentToEntity(
        game_context->world->ecs,
        player,
        NewHealth(100),
        COMPONENT_TYPE_HEALTH
    );

    AttachComponentToEntity(
        game_context->world->ecs,
        wall_a,
        NewTag(ENTITY_TAG_WALL),
        COMPONENT_TYPE_TAG
    );
    AttachComponentToEntity(
        game_context->world->ecs,
        wall_a,
        NewPosition(200, (game_context->game_height / 2) - 75),
        COMPONENT_TYPE_POSITION
    );
    AttachComponentToEntity(
        game_context->world->ecs,
        wall_a,
        NewSprite(wall_text),
        COMPONENT_TYPE_SPRITE
    );
    AttachComponentToEntity(
        game_context->world->ecs,
        wall_a,
        NewRectangleCollider(wall_text.width, wall_text.height, CLITERAL(Vector2){wall_text.width / 2, wall_text.height / 2}, true),
        COMPONENT_TYPE_COLLIDER
    );

    // AddPositionToEntity(wall_b, game_context->world->positions, 200, (game_context->game_height / 2) + 25);
    // AddSpriteToEntity(wall_b, game_context->world->sprites, wall_text);
    // AddRectangleColliderToEntity(wall_b, game_context->world->colliders, wall_text.width, wall_text.height, CLITERAL(Vector2){wall_text.width / 2, wall_text.height / 2}, true);

    AttachComponentToEntity(
            game_context->world->ecs,
            rotund,
            NewTag(ENTITY_TAG_ENEMY),
            COMPONENT_TYPE_TAG
        );
    AttachComponentToEntity(
        game_context->world->ecs,
        rotund,
        NewPosition(game_context->game_width - 300, game_context->game_height / 2),
        COMPONENT_TYPE_POSITION
    );
    AttachComponentToEntity(
        game_context->world->ecs,
        rotund,
        NewVelocity(0.0f, 0.0f),
        COMPONENT_TYPE_VELOCITY
    );
    AttachComponentToEntity(
        game_context->world->ecs,
        rotund,
        NewSprite(rotund_text),
        COMPONENT_TYPE_SPRITE
    );
    AttachComponentToEntity(
        game_context->world->ecs,
        rotund,
        NewCircleCollider(rotund_text.width / 2, CLITERAL(Vector2){rotund_text.width / 2, rotund_text.height / 2}, true),
        COMPONENT_TYPE_COLLIDER
    );
    AddChaseBehaviourToEntity(rotund, game_context->world->chase_behaviours, player);
    AddHarmToEntity(rotund, game_context->world->harms, 10);

    struct VelocityComponent* player_velocity = GetComponentOfEntity(
        game_context->world->ecs,
        player,
        COMPONENT_TYPE_VELOCITY
    );
    struct HealthComponent* player_health = GetComponentOfEntity(
        game_context->world->ecs,
        player,
        COMPONENT_TYPE_HEALTH
    );

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

        UpdateMovement(game_context->world->ecs->position_component_array, game_context->world->ecs->velocity_component_array);
        UpdateChaseBehaviours(game_context->world->ecs->position_component_array, game_context->world->ecs->velocity_component_array, game_context->world->chase_behaviours);
        UpdateColliders(game_context->world->ecs->position_component_array, game_context->world->ecs->collider_component_array, game_context->world->ecs->tag_component_array);
        UpdateMapBounds(game_context->world->ecs->position_component_array, game_context->world->ecs->collider_component_array, CLITERAL(Vector2){game_context->game_width, game_context->game_height});
        if (game_context->world->should_draw_collision_bounds) {
            DrawCollisionBounds(game_context->world->debug_layer, game_context->world->ecs->position_component_array, game_context->world->ecs->collider_component_array);
        }
        UpdateCombat(game_context->world->ecs->collider_component_array, game_context->world->harms, game_context->world->ecs->health_component_array);

        BeginDrawing();

        ClearBackground(DARKGRAY);

        RenderSprites(game_context->world->ecs->sprite_component_array, game_context->world->ecs->position_component_array);

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
