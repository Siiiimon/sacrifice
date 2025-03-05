#include "health_component.h"
#include "defs.h"
#include "raylib.h"
#include <stdlib.h>

struct HealthComponentArray* NewHealthComponentArray(void) {
    struct HealthComponentArray* healths = malloc(sizeof(struct HealthComponentArray));
    if (!healths) {
        TraceLog(LOG_ERROR, "failed to allocate memory for HealthComponentArray");
        return NULL;
    }

    for (Entity i = 0; i < MAX_ENTITIES; i++) {
        healths->components[i] = NULL;
    }

    return healths;
}

void FreeHealthComponentArray(struct HealthComponentArray* healths) {
    if (!healths) return;
    for (int i = 0; i < MAX_ENTITIES; i++) {
        FreeHealth(healths->components[i]);
    }
    free(healths);
}

void AddHealthToEntity(Entity entity, struct HealthComponentArray* healths, int max_health) {
    if (!healths) return;
    if (entity >= MAX_ENTITIES) {
        TraceLog(LOG_ERROR, "entity index out of bounds");
        return;
    }

    struct HealthComponent* component = malloc(sizeof(struct HealthComponent));
    if (!component) {
        TraceLog(LOG_ERROR, "failed to allocate memory for HealthComponent");
        return;
    }

    component->max_health = max_health;
    component->current_health = max_health;
    component->is_invincible = false;
    component->invincibility_duration = 1.0f;
    component->invincibility_timer = 0.0f;

    if (healths->components[entity] != NULL) {
        TraceLog(LOG_ERROR, "entity %u already has a HealthComponent", entity);
        FreeHealth(healths->components[entity]);
    }
    healths->components[entity] = component;
}

struct HealthComponent* GetHealth(struct HealthComponentArray* healths, Entity entity) {
    if (!healths) return NULL;
    if (entity >= MAX_ENTITIES) {
        TraceLog(LOG_ERROR, "entity index out of bounds");
        return NULL;
    }
    return healths->components[entity];
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
