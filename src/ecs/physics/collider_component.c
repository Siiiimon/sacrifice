#include "collider_component.h"
#include "defs.h"
#include "raylib.h"
#include <stdlib.h>

struct ColliderComponentArray* NewColliderComponentArray(void) {
    struct ColliderComponentArray* colliders = malloc(sizeof(struct ColliderComponentArray));
    if (!colliders) {
        TraceLog(LOG_ERROR, "Failed to allocate memory for ColliderComponentArray");
        return NULL;
    }

    for (unsigned int i = 0; i < MAX_ENTITIES; i++) {
        colliders->components[i] = NULL;
    }

    return colliders;
}

void FreeColliderComponentArray(struct ColliderComponentArray* colliders) {
    if (!colliders) return;

    for (unsigned int i = 0; i < MAX_ENTITIES; i++) {
        FreeCollider(colliders->components[i]);
    }

    free(colliders);
}


void AddRectangleColliderToEntity(unsigned int entity, struct ColliderComponentArray* colliders, float width, float height, Vector2 offset, bool is_bound_to_map) {
    if (!colliders) return;
    if (entity >= MAX_ENTITIES) {
        TraceLog(LOG_ERROR, "Entity index out of bounds");
        return;
    }

    struct ColliderComponent* collider = malloc(sizeof(struct ColliderComponent));
    if (!collider) {
        TraceLog(LOG_ERROR, "Failed to allocate memory for ColliderComponent");
        return;
    }

    collider->offset = offset;
    collider->colliding_count = 0;
    for (unsigned int i = 0; i < MAX_COLLISIONS; i++) {
        collider->colliding_with[i] = 0;
    }
    collider->is_bound_to_map = is_bound_to_map;
    collider->shape_type = COLLIDER_SHAPE_RECTANGLE;
    collider->shape.rectangle.width = width;
    collider->shape.rectangle.height = height;

    if (colliders->components[entity] != NULL) {
        TraceLog(LOG_ERROR, "Entity %u already has a collider", entity);
        FreeCollider(collider);
    }
    colliders->components[entity] = collider;
}

void AddCircleColliderToEntity(unsigned int entity, struct ColliderComponentArray* colliders, float radius, Vector2 offset, bool is_bound_to_map) {
    if (!colliders) return;
    if (entity >= MAX_ENTITIES) {
        TraceLog(LOG_ERROR, "Entity index out of bounds");
        return;
    }

    struct ColliderComponent* collider = malloc(sizeof(struct ColliderComponent));
    if (!collider) {
        TraceLog(LOG_ERROR, "Failed to allocate memory for ColliderComponent");
        return;
    }

    collider->offset = offset;
    collider->colliding_count = 0;
    for (unsigned int i = 0; i < MAX_COLLISIONS; i++) {
        collider->colliding_with[i] = 0;
    }
    collider->is_bound_to_map = is_bound_to_map;
    collider->shape_type = COLLIDER_SHAPE_CIRCLE;
    collider->shape.circle.radius = radius;

    if (colliders->components[entity] != NULL) {
        TraceLog(LOG_ERROR, "Entity %u already has a collider", entity);
        FreeCollider(collider);
    }
    colliders->components[entity] = collider;
}

struct ColliderComponent* GetCollider(struct ColliderComponentArray* colliders, unsigned int entity) {
    if (!colliders) return NULL;
    if (entity >= MAX_ENTITIES) {
        TraceLog(LOG_ERROR, "Entity index out of bounds");
        return NULL;
    }
    return colliders->components[entity];
}

void FreeCollider(struct ColliderComponent* collider) {
    if (!collider) return;
    free(collider);
}
