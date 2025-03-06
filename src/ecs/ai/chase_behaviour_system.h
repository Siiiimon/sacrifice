#ifndef CHASE_BEHAVIOUR_SYSTEM_H
#define CHASE_BEHAVIOUR_SYSTEM_H

#include "ecs/ai/chase_behaviour_component.h"
#include "ecs/physics/position_component.h"
#include "ecs/physics/velocity_component.h"

void UpdateChaseBehaviours(
    struct PositionComponent* positions[MAX_ENTITIES],
    struct VelocityComponent* velocities[MAX_ENTITIES],
    struct ChaseBehaviourComponent* chase_behaviours[MAX_ENTITIES]
);

#endif
