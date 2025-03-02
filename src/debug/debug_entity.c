#include "debug_entity.h"
#include "cimgui_include.h"
#include "raylib.h"
#include "rlImGui.h"

static void DrawPositionDebug(struct PositionComponent* position) {
    DrawLineEx(
        CLITERAL(Vector2){position->x - 8, position->y},
        CLITERAL(Vector2){position->x + 8, position->y},
        2.0f,
        MAGENTA);
    DrawLineEx(
        CLITERAL(Vector2){position->x, position->y - 8},
        CLITERAL(Vector2){position->x, position->y + 8},
        2.0f,
        MAGENTA);
    igText("Position: (%.1f, %.1f)", position->x, position->y);
}

static void DrawVelocityDebug(struct VelocityComponent* velocity) {
    igText("Velocity: (%.1f, %.1f)", velocity->x, velocity->y);
}

static void DrawSpriteDebug(struct SpriteComponent* sprite) {
    if (igCollapsingHeader_TreeNodeFlags("Sprite", ImGuiTreeNodeFlags_DefaultOpen)) {
        igText("Sprite ID: %u", sprite->texture.id);
        igText("Sprite Dimensions: %d x %d", sprite->texture.width, sprite->texture.height);
        rlImGuiImage(&sprite->texture);
    }
}

void DrawEntityInspector(struct GameContext* game_context) {
    unsigned int entity = game_context->currently_inspected_entity_id;
    if (entity == 0) {
        return;
    }

    igBegin(TextFormat("Entity %u", entity), NULL, 0);

    struct PositionComponent* position = GetPosition(game_context->world->positions, entity);
    if (position) {
        DrawPositionDebug(position);
    }
    struct VelocityComponent* velocity = GetVelocity(game_context->world->velocities, entity);
    if (velocity) {
        DrawVelocityDebug(velocity);
    }

    if (position && velocity) {
        DrawLineEx(
            CLITERAL(Vector2){position->x, position->y},
            CLITERAL(Vector2){position->x + velocity->x * 10.0f, position->y + velocity->y * 10.0f},
            2.0f,
            SKYBLUE);
    }
    struct SpriteComponent* sprite = GetSprite(game_context->world->sprites, entity);
    if (sprite) {
        DrawSpriteDebug(sprite);
    }

    igEnd();
}
