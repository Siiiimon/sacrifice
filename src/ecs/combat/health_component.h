#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "defs.h"
#include <stdbool.h>
#include <harm_component.h>

struct HealthComponent {
    int max_health;
    int current_health;
    bool is_invincible;
    float invincibility_duration;
    float invincibility_timer;
};

struct HealthComponent* NewHealth(int max_health);
void ReceiveDamage(struct HealthComponent* health, struct HarmComponent* harm);
void UpdateInvincibilityFrames(struct HealthComponent* health);
void FreeHealth(struct HealthComponent* health);

#endif //HEALTH_COMPONENT_H
