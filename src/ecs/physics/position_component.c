#include "position_component.h"
#include "raylib.h"
#include <stdlib.h>

struct PositionComponentArray* NewPositionComponentArray(void) {
    struct PositionComponentArray* position_components = malloc(sizeof(struct PositionComponentArray));
    if (position_components == NULL) {
        TraceLog(LOG_ERROR, "failed to allocate memory for PositionComponentArray");
        return NULL;
    }

    position_components->count = 0;
    return position_components;
}

void FreePositionComponentArray(struct PositionComponentArray* position_components) {
    if (position_components == NULL) {
        return;
    }

    for (unsigned int i = 0; i < position_components->count; i++) {
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

    position_components->entities[position_components->count] = entity;
    position_components->components[position_components->count] = component;
    position_components->count++;
}

void FreePosition(struct PositionComponent* component) {
    free(component);
}

struct PositionComponent* GetPosition(struct PositionComponentArray* position_components, unsigned int entity) {
    if (position_components == NULL || entity >= position_components->count) {
        return NULL;
    }

    for (unsigned int i = 0; i < position_components->count; i++) {
        if (position_components->entities[i] == entity) {
            return position_components->components[i];
        }
    }
    return NULL;
}
