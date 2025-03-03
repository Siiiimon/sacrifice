#include "harm_component.h"
#include "defs.h"
#include "raylib.h"
#include <stdlib.h>

struct HarmComponentArray* NewHarmComponentArray(void) {
    struct HarmComponentArray* harms = malloc(sizeof(struct HarmComponentArray));
    if (!harms) {
        TraceLog(LOG_ERROR, "failed to allocate memory for HarmComponentArray");
        return NULL;
    }

    for (unsigned int i = 0; i < MAX_ENTITIES; i++) {
        harms->components[i] = NULL;
    }

    return harms;
}

void FreeHarmComponentArray(struct HarmComponentArray* harms) {
    if (!harms) return;
    for (int i = 0; i < MAX_ENTITIES; i++) {
        FreeHarm(harms->components[i]);
    }
    free(harms);
}

void AddHarmToEntity(unsigned int entity, struct HarmComponentArray* harms, int damage) {
    if (!harms) return;
    if (entity >= MAX_ENTITIES) {
        TraceLog(LOG_ERROR, "entity index out of bounds");
        return;
    }

    struct HarmComponent* component = malloc(sizeof(struct HarmComponent));
    if (!component) {
        TraceLog(LOG_ERROR, "failed to allocate memory for HarmComponent");
        return;
    }
    component->damage = damage;

    if (harms->components[entity] != NULL) {
        TraceLog(LOG_ERROR, "entity %u already has a HarmComponent", entity);
        FreeHarm(harms->components[entity]);
    }
    harms->components[entity] = component;
}

struct HarmComponent* GetHarm(struct HarmComponentArray* harms, unsigned int entity) {
    if (!harms) return NULL;
    if (entity >= MAX_ENTITIES) {
        TraceLog(LOG_ERROR, "entity index out of bounds");
        return NULL;
    }
    return harms->components[entity];
}

void FreeHarm(struct HarmComponent* harm) {
    free(harm);
}
