#include "combat_system.h"

#include <ecs.h>

void UpdateCombat(
    struct ColliderComponent* colliders[MAX_ENTITIES],
    struct HarmComponentArray* harms,
    struct HealthComponent* healths[MAX_ENTITIES]
) {
    for (Entity i = 0; i < MAX_ENTITIES; i++) {
        struct ColliderComponent* collider = colliders[i];
        struct HealthComponent* health = healths[i];

        if (!collider || !health) continue;

        UpdateInvincibilityFrames(health);

        for (short j = 0; j < collider->colliding_count; j++) {
            Entity other = collider->colliding_with[j];
            struct HarmComponent* harm = harms->components[other];
            if (harm)
                ReceiveDamage(health, harm);
        }
    }
}
