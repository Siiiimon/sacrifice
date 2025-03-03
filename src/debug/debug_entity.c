#include "debug_entity.h"
#include "cimgui_include.h"
#include "raylib.h"
#include "rlImGui.h"

static void DrawPositionDebug(RenderTexture2D debug_layer, struct PositionComponent* position) {
    BeginTextureMode(debug_layer);
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
    EndTextureMode();
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

static void DrawColliderDebug(struct ColliderComponent* collider) {
    igText("Collider shape_type: %s", collider->shape_type == COLLIDER_SHAPE_CIRCLE ? "Circle" : "Rectangle");
    if (collider->shape_type == COLLIDER_SHAPE_CIRCLE) {
        igText("Radius: %.1f", collider->shape.circle.radius);
    } else if (collider->shape_type == COLLIDER_SHAPE_RECTANGLE) {
        igText("Width: %.1f", collider->shape.rectangle.width);
        igText("Height: %.1f", collider->shape.rectangle.height);
    }
    igText("Offset: (%.1f, %.1f)", collider->offset.x, collider->offset.y);
    igText("is %s", collider->is_colliding ? "Colliding" : "Not Colliding");
}

void DrawEntityInspector(struct GameContext* game_context) {
    unsigned int entity = game_context->currently_inspected_entity_id;
    if (entity == 0) {
        return;
    }

    igBegin(TextFormat("Entity %u", entity), NULL, 0);

    struct PositionComponent* position = GetPosition(game_context->world->positions, entity);
    if (position) {
        DrawPositionDebug(game_context->world->debug_layer, position);
    }
    struct VelocityComponent* velocity = GetVelocity(game_context->world->velocities, entity);
    if (velocity) {
        DrawVelocityDebug(velocity);
    }

    if (position && velocity) {
        BeginTextureMode(game_context->world->debug_layer);
        DrawLineEx(
            CLITERAL(Vector2){position->x, position->y},
            CLITERAL(Vector2){position->x + velocity->x * 10.0f, position->y + velocity->y * 10.0f},
            2.0f,
            SKYBLUE
        );
        EndTextureMode();
    }
    struct SpriteComponent* sprite = GetSprite(game_context->world->sprites, entity);
    if (sprite) {
        DrawSpriteDebug(sprite);
    }

    struct ColliderComponent* collider = GetCollider(game_context->world->colliders, entity);
    if (position && collider) {
        DrawColliderDebug(collider);
    }

    igEnd();
}
