#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "position_component.h"
#include "velocity_component.h"

void UpdateMovement(struct PositionComponent* positions[MAX_ENTITIES], struct VelocityComponentArray* velocity_components);

#endif
