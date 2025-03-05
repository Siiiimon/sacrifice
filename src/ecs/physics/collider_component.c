#include "collider_component.h"
#include "defs.h"
#include "raylib.h"

#include <ecs.h>
#include <stdlib.h>

struct ColliderComponent* NewRectangleCollider(float width, float height, Vector2 offset, bool is_bound_to_map) {
    struct ColliderComponent* collider = malloc(sizeof(struct ColliderComponent));
    if (!collider) {
        TraceLog(LOG_ERROR, "Failed to allocate memory for ColliderComponent");
        return NULL;
    }

    collider->offset = offset;
    collider->colliding_count = 0;
    for (Entity i = 0; i < MAX_COLLISIONS; i++) {
        collider->colliding_with[i] = 0;
    }
    collider->is_bound_to_map = is_bound_to_map;
    collider->shape_type = COLLIDER_SHAPE_RECTANGLE;
    collider->shape.rectangle.width = width;
    collider->shape.rectangle.height = height;

    return collider;
}

struct ColliderComponent* NewCircleCollider(float radius, Vector2 offset, bool is_bound_to_map) {
    struct ColliderComponent* collider = malloc(sizeof(struct ColliderComponent));
    if (!collider) {
        TraceLog(LOG_ERROR, "Failed to allocate memory for ColliderComponent");
        return NULL;
    }

    collider->offset = offset;
    collider->colliding_count = 0;
    for (Entity i = 0; i < MAX_COLLISIONS; i++) {
        collider->colliding_with[i] = 0;
    }
    collider->is_bound_to_map = is_bound_to_map;
    collider->shape_type = COLLIDER_SHAPE_CIRCLE;
    collider->shape.circle.radius = radius;

    return collider;
}

void FreeCollider(struct ColliderComponent* collider) {
    if (!collider) return;
    free(collider);
}
