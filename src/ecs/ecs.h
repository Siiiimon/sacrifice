#ifndef ECS_ENTITY_MANAGER_H
#define ECS_ENTITY_MANAGER_H

#include "defs.h"
#include <stdbool.h>

typedef unsigned int Entity;

struct ECS {
    Entity entities[MAX_ENTITIES];
    bool active_entities[MAX_ENTITIES];
    Entity next_entity;
};

struct ECS* NewEntityManager(void);
void FreeEntityManager(struct ECS* manager);

Entity NewEntity(struct ECS* manager);
Entity* GetActiveEntities(struct ECS* manager, unsigned int* count);
void RemoveEntity(struct ECS* manager, Entity entity);

#endif
