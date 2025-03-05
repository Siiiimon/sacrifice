#include "movement_system.h"
#include <stdlib.h>

void UpdateMovement(struct PositionComponent* positions[MAX_ENTITIES], struct VelocityComponentArray* velocities) {
    for (Entity i = 0; i < MAX_ENTITIES; i++) {
        struct PositionComponent* position = positions[i];
        struct VelocityComponent* velocity = velocities->components[i];
        if (position == NULL || velocity == NULL) continue;
        // TODO: when reworking physics movement, build vector and normalize it
        // otherwise moving diagonally will be faster than moving straight
        position->x += velocity->x;
        position->y += velocity->y;
    }
}
