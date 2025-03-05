#include "cimgui_include.h"
#include "raylib.h"
#include "rlImGui.h"

#include "debug_entity.h"
#include "entity/debug_position.h"

#include <debug_data.h>
#include <harm_component.h>
#include <health_component.h>

static void DrawVelocityDebug(struct VelocityComponent* velocity) {
    igText("Velocity: (%.1f, %.1f)", velocity->x, velocity->y);
}

static void DrawSpriteDebug(struct SpriteComponent* sprite) {
    if (igCollapsingHeader_TreeNodeFlags("Sprite", 0)) {
        igText("Sprite ID: %u", sprite->texture.id);
        igText("Sprite Dimensions: %d x %d", sprite->texture.width, sprite->texture.height);
        rlImGuiImage(&sprite->texture);
    }
}

static void DrawColliderDebug(struct ColliderComponent* collider) {
    if (igCollapsingHeader_TreeNodeFlags("Collider", 0)) {
        igText("Collider shape_type: %s", collider->shape_type == COLLIDER_SHAPE_CIRCLE ? "Circle" : "Rectangle");
        if (collider->shape_type == COLLIDER_SHAPE_CIRCLE) {
            igText("Radius: %.1f", collider->shape.circle.radius);
        } else if (collider->shape_type == COLLIDER_SHAPE_RECTANGLE) {
            igText("Width: %.1f", collider->shape.rectangle.width);
            igText("Height: %.1f", collider->shape.rectangle.height);
        }
        igText("Offset: (%.1f, %.1f)", collider->offset.x, collider->offset.y);
        for (int i = 0; i < collider->colliding_count; i++) {
            igText("Colliding with Entity %d", collider->colliding_with[i]);
        }
    }
}

void DrawEntityInspector(struct GameContext* game_context) {
    if (
        game_context->debug_data->show_entity_inspector_window &&
        igBegin("Entity Inspector", &game_context->debug_data->show_entity_inspector_window, ImGuiWindowFlags_AlwaysAutoResize)
    ) {
        Entity entity = game_context->debug_data->currently_inspected_entity_id;
        if (entity == 0) {
            igText("No Entity Selected!");
            igEnd();
            return;
        }
        struct PositionComponent* position = GetComponentOfEntity(
            game_context->world->ecs,
            entity,
            COMPONENT_TYPE_POSITION
        );
        if (position) {
            DrawPositionDebug(game_context->world->debug_layer, position);
        }
        struct VelocityComponent* velocity = GetComponentOfEntity(
            game_context->world->ecs,
            entity,
            COMPONENT_TYPE_VELOCITY
        );
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
        struct SpriteComponent* sprite = GetComponentOfEntity(
            game_context->world->ecs,
            entity,
            COMPONENT_TYPE_SPRITE
        );
        if (sprite) {
            DrawSpriteDebug(sprite);
        }

        struct ColliderComponent* collider = GetCollider(game_context->world->colliders, entity);
        if (position && collider) {
            DrawColliderDebug(collider);
        }

        if (igCollapsingHeader_TreeNodeFlags("Health / Harm", 0)) {
            struct HealthComponent* health = GetHealth(game_context->world->healths, entity);
            if (health) {
                if (health->current_health <= 0) {
                    igText("entity is dead");
                } else {
                    igText("%d out of %d health", health->current_health, health->max_health);
                }
                if (health->is_invincible) {
                    igText("invincible for %.1f", health->invincibility_duration - health->invincibility_timer);
                } else {
                    igText("currently vulnerable");
                }
            }

            struct HarmComponent* harm = GetHarm(game_context->world->harms, entity);
            if (harm) {
                igText("deals %d damage", harm->damage);
            }
        }

        igEnd();
    }
}
