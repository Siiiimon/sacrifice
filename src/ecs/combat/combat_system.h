#ifndef COMBAT_SYSTEM_H
#define COMBAT_SYSTEM_H

#include "../physics/collider_component.h"
#include "harm_component.h"
#include "health_component.h"

void UpdateCombat(
    struct ColliderComponent* colliders[MAX_ENTITIES],
    struct HarmComponentArray* harms,
    struct HealthComponentArray* healths
);
#endif //COMBAT_SYSTEM_H
