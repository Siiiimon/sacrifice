#include "position_component.h"
#include "defs.h"
#include "raylib.h"
#include <stdlib.h>

struct PositionComponentArray* NewPositionComponentArray(void) {
    struct PositionComponentArray* position_components = malloc(sizeof(struct PositionComponentArray));
    if (position_components == NULL) {
        TraceLog(LOG_ERROR, "failed to allocate memory for PositionComponentArray");
        return NULL;
    }

    for (unsigned int i = 0; i < MAX_ENTITIES; i++) {
        position_components->components[i] = NULL;
    }

    return position_components;
}

void FreePositionComponentArray(struct PositionComponentArray* position_components) {
    if (position_components == NULL) {
        return;
    }

    for (unsigned int i = 0; i < MAX_ENTITIES; i++) {
        FreePosition(position_components->components[i]);
    }
}


void AddPositionToEntity(unsigned int entity, struct PositionComponentArray* position_components, float x, float y) {
    struct PositionComponent* component = malloc(sizeof(struct PositionComponent));
    if (component == NULL) {
        TraceLog(LOG_ERROR, "failed to allocate memory for entity %u's PositionComponent", entity);
    }
    component->x = x;
    component->y = y;

    if (position_components->components[entity] != NULL) {
        TraceLog(LOG_ERROR, "entity %u already has a PositionComponent", entity);
        FreePosition(position_components->components[entity]);
    }
    position_components->components[entity] = component;
}

void FreePosition(struct PositionComponent* component) {
    free(component);
}

struct PositionComponent* GetPosition(struct PositionComponentArray* position_components, unsigned int entity) {
    return position_components->components[entity];
}
