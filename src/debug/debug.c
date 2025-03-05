#include "debug.h"
#include "cimgui.h"
#include "entity/debug_entities.h"
#include "raylib.h"

#include <debug_data.h>

void DrawCollisionBounds(RenderTexture2D debug_layer, struct PositionComponent* positions[MAX_ENTITIES], struct ColliderComponent* colliders[MAX_ENTITIES]) {
    BeginTextureMode(debug_layer);
    for (Entity i = 0; i < MAX_ENTITIES; i++) {
        if (colliders[i] == NULL) continue;
        struct ColliderComponent* collider = colliders[i];

        if (positions[i] == NULL) continue;
        struct PositionComponent* position = positions[i];

        if (collider->shape_type == COLLIDER_SHAPE_CIRCLE) {
            if (collider->colliding_count > 0) {
                DrawCircleV(
                    CLITERAL(Vector2){
                        position->x + collider->offset.x,
                        position->y + collider->offset.y
                    },
                    collider->shape.circle.radius,
                    CLITERAL(Color){ 255, 161, 0, 150 }
                );
            } else {
                DrawCircleLinesV(
                    CLITERAL(Vector2){
                        position->x + collider->offset.x,
                        position->y + collider->offset.y
                    },
                    collider->shape.circle.radius,
                    ORANGE
                );
            }
        } else if (collider->shape_type == COLLIDER_SHAPE_RECTANGLE) {
            if (collider->colliding_count > 0) {
                DrawRectangle(
                    position->x + collider->offset.x - collider->shape.rectangle.width / 2,
                    position->y + collider->offset.y - collider->shape.rectangle.height / 2,
                    collider->shape.rectangle.width,
                    collider->shape.rectangle.height,
                    CLITERAL(Color){ 255, 161, 0, 150 }
                );
            } else {
                DrawRectangleLines(
                    position->x + collider->offset.x - collider->shape.rectangle.width / 2,
                    position->y + collider->offset.y - collider->shape.rectangle.height / 2,
                    collider->shape.rectangle.width,
                    collider->shape.rectangle.height,
                    ORANGE
                );
            }
        }
    }
    EndTextureMode();
}

void DrawDebugUI(struct GameContext *game_context) {
    igBeginMainMenuBar();
    if (igBeginMenu("Windows", true)) {
        igMenuItem_BoolPtr("Main Window", NULL, &game_context->debug_data->show_main_window, true);
        igMenuItem_BoolPtr("Entities", NULL, &game_context->debug_data->show_entities_window, true);
        igMenuItem_BoolPtr("Entity Inspector", NULL, &game_context->debug_data->show_entity_inspector_window, true);
        igEndMenu();
    }
    igEndMainMenuBar();

    if (game_context->debug_data->show_main_window && igBegin("Debug", &game_context->debug_data->show_main_window, 0)) {
        if (igCollapsingHeader_TreeNodeFlags("Performance", ImGuiTreeNodeFlags_DefaultOpen)) {
            igText("FPS: %d", GetFPS());
        }
        if (igCollapsingHeader_TreeNodeFlags("System", ImGuiTreeNodeFlags_DefaultOpen)) {
            igText("DPI scale: %.1f", GetWindowScaleDPI().x);
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
        igCheckbox("Draw Collision Bounds", &game_context->world->should_draw_collision_bounds);
        igEnd();
    }
    DrawEntitiesDebugUI(game_context);

    igShowDemoWindow(NULL);
}
