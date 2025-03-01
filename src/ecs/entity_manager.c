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
    manager->next_entity = 1;
    return manager;
}

unsigned int NewEntity(struct EntityManager* manager) {
    unsigned int entity = manager->next_entity++;
    manager->entities[entity] = entity;
    return entity;
}

void RemoveEntity(struct EntityManager* manager, unsigned int entity) {
    manager->entities[entity] = 0;
}
