#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include "defs.h"
#include "raylib.h"

struct ColliderComponentArray {
    struct ColliderComponent* components[MAX_ENTITIES];
};

enum ColliderShape {
    COLLIDER_SHAPE_RECTANGLE,
    COLLIDER_SHAPE_CIRCLE,
};

struct ColliderComponent {
    enum ColliderShape shape_type;
    Vector2 offset;
    short colliding_count;
    unsigned int colliding_with[MAX_COLLISIONS];
    // int layer;
    // unsigned int mask;
    bool is_bound_to_map;

    union {
        struct {
            float width;
            float height;
        } rectangle;

        struct {
            float radius;
        } circle;
    } shape;
};

struct ColliderComponentArray* NewColliderComponentArray(void);
void FreeColliderComponentArray(struct ColliderComponentArray* colliders);

void AddRectangleColliderToEntity(unsigned int entity, struct ColliderComponentArray* colliders, float width, float height, Vector2 offset, bool is_bound_to_map);
void AddCircleColliderToEntity(unsigned int entity, struct ColliderComponentArray* colliders, float radius, Vector2 offset, bool is_bound_to_map);
struct ColliderComponent* GetCollider(struct ColliderComponentArray* colliders, unsigned int entity);
void FreeCollider(struct ColliderComponent* collider);

#endif
