#ifndef COMBAT_SYSTEM_H
#define COMBAT_SYSTEM_H

#include "../physics/collider_component.h"
#include "harm_component.h"
#include "health_component.h"

void UpdateCombat(
    struct ColliderComponent* colliders[MAX_ENTITIES],
    struct HarmComponent* harms[MAX_ENTITIES],
    struct HealthComponent* healths[MAX_ENTITIES]
);
#endif //COMBAT_SYSTEM_H
