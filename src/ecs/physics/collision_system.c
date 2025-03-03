#include "collision_system.h"
#include "collider_component.h"
#include "defs.h"
#include "raylib.h"
#include <stdlib.h>

static bool RectOnRect(
    struct PositionComponent* a_position,
    struct ColliderComponent* a_collider,
    struct PositionComponent* b_position,
    struct ColliderComponent* b_collider
) {
    return CheckCollisionRecs(
        CLITERAL(Rectangle) {
            a_position->x,
            a_position->y,
            a_collider->shape.rectangle.width,
            a_collider->shape.rectangle.height
        },
        CLITERAL(Rectangle) {
            b_position->x,
            b_position->y,
            b_collider->shape.rectangle.width,
            b_collider->shape.rectangle.height
        }
    );
}

static bool CircleOnRect(
    struct PositionComponent* a_position,
    struct ColliderComponent* a_collider,
    struct PositionComponent* b_position,
    struct ColliderComponent* b_collider
) {
    return CheckCollisionCircleRec(
        CLITERAL(Vector2) {
            a_position->x + a_collider->offset.x,
            a_position->y + a_collider->offset.y
        },
        a_collider->shape.circle.radius,
        CLITERAL(Rectangle) {
            b_position->x,
            b_position->y,
            b_collider->shape.rectangle.width,
            b_collider->shape.rectangle.height
        }
    );
}

static bool CircleOnCircle(
    struct PositionComponent* a_position,
    struct ColliderComponent* a_collider,
    struct PositionComponent* b_position,
    struct ColliderComponent* b_collider
) {
    return CheckCollisionCircles(
        CLITERAL(Vector2) {
            a_position->x + a_collider->offset.x,
            a_position->y + a_collider->offset.y
        },
        a_collider->shape.circle.radius,
        CLITERAL(Vector2) {
            b_position->x + b_collider->offset.x,
            b_position->y + b_collider->offset.y
        },
        b_collider->shape.circle.radius
    );
}


void UpdateColliders(struct PositionComponentArray* positions, struct ColliderComponentArray* colliders) {
    for (unsigned int i = 0; i < MAX_ENTITIES; i++) {
        if (colliders->components[i] == NULL) {
            continue;
        }
        struct ColliderComponent* our_collider = colliders->components[i];

        if (positions->components[i] == NULL) {
            TraceLog(LOG_ERROR, "Collider %u has no position component", i);
            continue;
        }
        struct PositionComponent* our_position = positions->components[i];


        our_collider->colliding_count = 0;
        for (unsigned int i = 0; i < MAX_COLLISIONS; i++) {
            our_collider->colliding_with[i] = 0;
        }

        for (unsigned int j = 0; j < MAX_ENTITIES; j++) {
            if (i == j || colliders->components[j] == NULL || positions->components[j] == NULL) {
                continue;
            }
            struct ColliderComponent* their_collider = colliders->components[j];

            if (positions->components[j] == NULL) {
                TraceLog(LOG_ERROR, "Collider %u has no position component", j);
                continue;
            }
            struct PositionComponent* their_position = positions->components[j];

            bool collision_detected = false;

            if (our_collider->shape_type == COLLIDER_SHAPE_RECTANGLE && their_collider->shape_type == COLLIDER_SHAPE_RECTANGLE) {
                // our Rect on their Rect
                collision_detected = RectOnRect(our_position, our_collider, their_position, their_collider);
            }
            if (our_collider->shape_type == COLLIDER_SHAPE_CIRCLE && their_collider->shape_type == COLLIDER_SHAPE_RECTANGLE) {
                // our Circle on their Rect
                collision_detected = CircleOnRect(our_position, our_collider, their_position, their_collider);
            }
            if (our_collider->shape_type == COLLIDER_SHAPE_RECTANGLE && their_collider->shape_type == COLLIDER_SHAPE_CIRCLE) {
                // our Rect on their Circle
                collision_detected = CircleOnRect(their_position, their_collider, our_position, our_collider);
            }
            if (our_collider->shape_type == COLLIDER_SHAPE_CIRCLE && their_collider->shape_type == COLLIDER_SHAPE_CIRCLE) {
                // our Circle on their Circle
                collision_detected = CircleOnCircle(our_position, our_collider, their_position, their_collider);
            }

            if (collision_detected) {
                our_collider->colliding_with[our_collider->colliding_count] = j;
                our_collider->colliding_count++;
            }
        }
    }
}
