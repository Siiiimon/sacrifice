#include "movement_system.h"
#include <stdlib.h>

void UpdateMovement(struct PositionComponentArray* position_components) {
    for (unsigned int i = 0; i < MAX_ENTITIES; i++) {
        struct PositionComponent* position = position_components->components[i];
        if (position == NULL) continue;
        position->x += 1.0f;
    }
}
