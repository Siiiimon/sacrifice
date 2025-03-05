#include "ecs.h"
#include "raylib.h"
#include <stdlib.h>
#include <string.h>

struct ECS* NewEntityManager(void) {
    struct ECS* manager = malloc(sizeof(struct ECS));
    if (!manager) {
        TraceLog(LOG_ERROR, "Failed to allocate memory for EntityManager");
        return NULL;
    }
    memset(manager->entities, 0, sizeof(manager->entities));
    memset(manager->active_entities, false, sizeof(manager->active_entities));
    manager->next_entity = 1;
    return manager;
}

void FreeEntityManager(struct ECS *manager) {
    free(manager);
}

Entity NewEntity(struct ECS* manager) {
    Entity entity = manager->next_entity++;
    TraceLog(LOG_INFO, "new entity: %u", entity);
    manager->entities[entity] = entity;
    manager->active_entities[entity] = true;
    return entity;
}

Entity* GetActiveEntities(struct ECS* manager, unsigned int* count) {
    *count = 0;
    Entity* active_entities = malloc(sizeof(Entity) * manager->next_entity);
    if (!active_entities) {
        TraceLog(LOG_ERROR, "Failed to allocate memory for active entities");
        return NULL;
    }
    for (Entity i = 0; i < manager->next_entity; ++i) {
        if (manager->active_entities[i]) {
            active_entities[(*count)++] = i;
        }
    }
    active_entities = realloc(active_entities, sizeof(Entity) * *count);
    return active_entities;
}

void RemoveEntity(struct ECS* manager, Entity entity) {
    manager->entities[entity] = 0;
    manager->active_entities[entity] = false;
}
