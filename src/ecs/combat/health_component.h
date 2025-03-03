#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "defs.h"
#include <stdbool.h>
#include <harm_component.h>

struct HealthComponentArray {
    struct HealthComponent* components[MAX_ENTITIES];
};

struct HealthComponent {
    int max_health;
    int current_health;
    bool is_invincible;
    float invincibility_duration;
    float invincibility_timer;
};

struct HealthComponentArray* NewHealthComponentArray(void);
void FreeHealthComponentArray(struct HealthComponentArray* healths);

void AddHealthToEntity(unsigned int entity, struct HealthComponentArray* healths, int max_health);
struct HealthComponent* GetHealth(struct HealthComponentArray* healths, unsigned int entity);
void ReceiveDamage(struct HealthComponent* health, struct HarmComponent* harm);
void UpdateInvincibilityFrames(struct HealthComponent* health);
void FreeHealth(struct HealthComponent* health);

#endif //HEALTH_COMPONENT_H
