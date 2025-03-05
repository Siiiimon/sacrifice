#include "velocity_component.h"
#include "defs.h"
#include "raylib.h"
#include <stdlib.h>

struct VelocityComponentArray* NewVelocityComponentArray(void) {
    struct VelocityComponentArray* velocities = malloc(sizeof(struct VelocityComponentArray));
    if (!velocities) {
        TraceLog(LOG_ERROR, "failed to allocate memory for VelocityComponentArray");
        return NULL;
    }

    for (Entity i = 0; i < MAX_ENTITIES; i++) {
        velocities->components[i] = NULL;
    }

    return velocities;
}

void FreeVelocityComponentArray(struct VelocityComponentArray* velocities) {
    if (!velocities) return;
    for (int i = 0; i < MAX_ENTITIES; i++) {
        FreeVelocity(velocities->components[i]);
    }
    free(velocities);
}

void AddVelocityToEntity(Entity entity, struct VelocityComponentArray* velocities, float x, float y) {
    if (!velocities) return;
    if (entity >= MAX_ENTITIES) {
        TraceLog(LOG_ERROR, "entity index out of bounds");
        return;
    }

    struct VelocityComponent* component = malloc(sizeof(struct VelocityComponent));
    if (!component) {
        TraceLog(LOG_ERROR, "failed to allocate memory for VelocityComponent");
        return;
    }
    component->x = x;
    component->y = y;

    if (velocities->components[entity] != NULL) {
        TraceLog(LOG_ERROR, "entity %u already has a VelocityComponent", entity);
        FreeVelocity(velocities->components[entity]);
    }
    velocities->components[entity] = component;
}

struct VelocityComponent* GetVelocity(struct VelocityComponentArray* velocities, Entity entity) {
    if (!velocities) return NULL;
    if (entity >= MAX_ENTITIES) {
        TraceLog(LOG_ERROR, "entity index out of bounds");
        return NULL;
    }
    return velocities->components[entity];
}

void FreeVelocity(struct VelocityComponent* velocity) {
    free(velocity);
}
