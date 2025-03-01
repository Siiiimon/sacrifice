#include "entity_manager.h"
#include "raylib.h"
#include <stdlib.h>
#include <string.h>

struct EntityManager* NewEntityManager(void) {
    struct EntityManager* manager = malloc(sizeof(struct EntityManager));
    if (!manager) {
        TraceLog(LOG_ERROR, "Failed to allocate memory for EntityManager");
        return NULL;
    }
    memset(manager->entities, 0, sizeof(manager->entities));
    memset(manager->active_entities, false, sizeof(manager->active_entities));
    manager->next_entity = 1;
    return manager;
}

unsigned int NewEntity(struct EntityManager* manager) {
    unsigned int entity = manager->next_entity++;
    TraceLog(LOG_INFO, "new entity: %u", entity);
    manager->entities[entity] = entity;
    manager->active_entities[entity] = true;
    return entity;
}

unsigned int* GetActiveEntities(struct EntityManager* manager, unsigned int* count) {
    *count = 0;
    unsigned int* active_entities = malloc(sizeof(unsigned int) * manager->next_entity);
    if (!active_entities) {
        TraceLog(LOG_ERROR, "Failed to allocate memory for active entities");
        return NULL;
    }
    for (unsigned int i = 0; i < manager->next_entity; ++i) {
        if (manager->active_entities[i]) {
            active_entities[*count++] = i;
        }
    }
    active_entities = realloc(active_entities, sizeof(unsigned int) * *count);
    return active_entities;
}

void RemoveEntity(struct EntityManager* manager, unsigned int entity) {
    manager->entities[entity] = 0;
    manager->active_entities[entity] = false;
}
