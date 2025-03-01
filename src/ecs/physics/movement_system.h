#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "position_component.h"
#include "velocity_component.h"

void UpdateMovement(struct PositionComponentArray* positions, struct VelocityComponentArray* velocity_components);

#endif
