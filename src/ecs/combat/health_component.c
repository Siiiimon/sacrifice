#include "health_component.h"
#include "raylib.h"
#include <stdlib.h>

struct HealthComponent* NewHealth(int max_health) {
    struct HealthComponent* health = malloc(sizeof(struct HealthComponent));
    if (!health) {
        TraceLog(LOG_ERROR, "failed to allocate memory for HealthComponent");
        return NULL;
    }

    health->max_health = max_health;
    health->current_health = max_health;
    health->is_invincible = false;
    health->invincibility_duration = 1.0f;
    health->invincibility_timer = 0.0f;

    return health;
}

void ReceiveDamage(struct HealthComponent* health, struct HarmComponent* harm) {
    if (health->is_invincible)
        return;

    health->current_health -= harm->damage;

    health->is_invincible = true;
    health->invincibility_timer = 0.0f;
}

void UpdateInvincibilityFrames(struct HealthComponent* health) {
    if (health->is_invincible) {
        health->invincibility_timer += GetFrameTime();

        if (health->invincibility_timer >= health->invincibility_duration) {
            health->is_invincible = false;
            health->invincibility_timer = 0.0f;
        }
    }
}

void FreeHealth(struct HealthComponent* health) {
    free(health);
}
