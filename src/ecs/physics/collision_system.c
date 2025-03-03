#include "collision_system.h"
#include "collider_component.h"
#include "defs.h"
#include "raylib.h"
#include <stdlib.h>

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

        our_collider->is_colliding = false;

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

            if (our_collider->shape_type == COLLIDER_SHAPE_RECTANGLE) {
                if (their_collider->shape_type == COLLIDER_SHAPE_RECTANGLE) {
                    our_collider->is_colliding = CheckCollisionRecs(
                        CLITERAL(Rectangle) {
                            our_position->x,
                            our_position->y,
                            our_collider->shape.rectangle.width,
                            our_collider->shape.rectangle.height
                        },
                        CLITERAL(Rectangle) {
                            their_position->x,
                            their_position->y,
                            their_collider->shape.rectangle.width,
                            their_collider->shape.rectangle.height
                        }
                    );
                }
            }
        }
    }
}
