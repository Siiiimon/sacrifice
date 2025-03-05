#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include "defs.h"
#include "raylib.h"

#include <ecs.h>

enum ColliderShape {
    COLLIDER_SHAPE_RECTANGLE,
    COLLIDER_SHAPE_CIRCLE,
};

struct ColliderComponent {
    enum ColliderShape shape_type;
    Vector2 offset;
    short colliding_count;
    Entity colliding_with[MAX_COLLISIONS];
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

struct ColliderComponent* NewRectangleCollider(float width, float height, Vector2 offset, bool is_bound_to_map);
struct ColliderComponent* NewCircleCollider(float radius, Vector2 offset, bool is_bound_to_map);
void FreeCollider(struct ColliderComponent* collider);

#endif
