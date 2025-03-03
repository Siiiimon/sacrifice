#include "tag_component.h"
#include "raylib.h"
#include <stdlib.h>

struct TagComponentArray* NewTagComponentArray(void) {
    struct TagComponentArray* tags = malloc(sizeof(struct TagComponentArray));
    if (!tags) {
        TraceLog(LOG_ERROR, "Failed to allocate memory for TagComponentArray");
        return NULL;
    }

    for (unsigned int i = 0; i < MAX_ENTITIES; i++) {
        tags->components[i] = NULL;
    }

    return tags;
}

void FreeTagComponentArray(struct TagComponentArray* tags) {
    if (!tags) return;

    for (unsigned int i = 0; i < MAX_ENTITIES; i++) {
        FreeTag(tags->components[i]);
    }

    free(tags);
}

void AddTagToEntity(unsigned int entity, struct TagComponentArray* tags, enum ENTITY_TAG tag) {
    if (!tags) return;
    if (entity >= MAX_ENTITIES) {
        TraceLog(LOG_ERROR, "Entity index out of bounds");
        return;
    }

    struct TagComponent* component = malloc(sizeof(struct TagComponent));
    if (!component) {
        TraceLog(LOG_ERROR, "Failed to allocate memory for TagComponent");
        return;
    }

    component->tag = tag;

    if (tags->components[entity] != NULL) {
        component->tag |= tags->components[entity]->tag;
    }
    tags->components[entity] = component;
}

struct TagComponent* GetTag(struct TagComponentArray* tags, unsigned int entity) {
    if (!tags) return NULL;
    if (entity >= MAX_ENTITIES) {
        TraceLog(LOG_ERROR, "Entity index out of bounds");
        return NULL;
    }
    return tags->components[entity];
}

void FreeTag(struct TagComponent* tag) {
    if (!tag) return;
    free(tag);
}

const char* GetTagName(enum ENTITY_TAG tag) {
    switch (tag) {
        case ENTITY_TAG_PLAYER:
            return "Player";
        case ENTITY_TAG_WALL:
            return "Wall";
        case ENTITY_TAG_ENEMY:
            return "Projectile";
        default:
            return "Unknown";
    }
}
