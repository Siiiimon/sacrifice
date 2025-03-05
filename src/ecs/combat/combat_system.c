#include "combat_system.h"

#include <ecs.h>

void UpdateCombat(
    struct ColliderComponentArray* colliders,
    struct HarmComponentArray* harms,
    struct HealthComponentArray* healths
) {
    for (Entity i = 0; i < MAX_ENTITIES; i++) {
        struct ColliderComponent* collider = colliders->components[i];
        struct HealthComponent* health = healths->components[i];

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
