#include "map_bounds_system.h"
#include <stdlib.h>

void UpdateMapBounds(struct PositionComponent* positions[MAX_ENTITIES], struct ColliderComponent* colliders[MAX_ENTITIES], Vector2 map_size) {
    for (Entity i = 0; i < MAX_ENTITIES; i++) {
        struct PositionComponent* position = positions[i];
        struct ColliderComponent* collider = colliders[i];
        if (position == NULL || collider == NULL) continue;
        if (!collider->is_bound_to_map) continue;

        if (collider->shape_type == COLLIDER_SHAPE_RECTANGLE) {
            if (position->x < 0) {
                position->x = 0;
            } else if (position->x + collider->shape.rectangle.width > map_size.x) {
                position->x = map_size.x - collider->shape.rectangle.width;
            }
            if (position->y < 0) {
                position->y = 0;
            } else if (position->y + collider->shape.rectangle.height > map_size.y) {
                position->y = map_size.y - collider->shape.rectangle.height;
            }
        } else if (collider->shape_type == COLLIDER_SHAPE_CIRCLE) {
            if (position->x <= 0) {
                position->x = 0;
            } else if (position->x + collider->offset.x + collider->shape.circle.radius >= map_size.x) {
                position->x = map_size.x - collider->shape.circle.radius - collider->offset.x;
            }
            if (position->y <= 0) {
                position->y = 0;
            } else if (position->y + collider->offset.y + collider->shape.circle.radius >= map_size.y) {
                position->y = map_size.y - collider->shape.circle.radius - collider->offset.y;
            }
        }
    }
}
