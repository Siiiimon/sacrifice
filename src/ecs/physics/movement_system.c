#include "movement_system.h"

void UpdateMovement(struct PositionComponentArray* position_components) {
    for (unsigned int i = 0; i < position_components->count; i++) {
        struct PositionComponent* position = position_components->components[i];
        position->x += 1.0f;
    }
}
