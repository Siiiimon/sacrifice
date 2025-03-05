#ifndef ECS_ENTITY_MANAGER_H
#define ECS_ENTITY_MANAGER_H

#include "defs.h"
#include <stdbool.h>

struct ECS {
    unsigned int entities[MAX_ENTITIES];
    bool active_entities[MAX_ENTITIES];
    unsigned int next_entity;
};

struct ECS* NewEntityManager(void);
void FreeEntityManager(struct ECS* manager);

unsigned int NewEntity(struct ECS* manager);
unsigned int* GetActiveEntities(struct ECS* manager, unsigned int* count);
void RemoveEntity(struct ECS* manager, unsigned int entity);

#endif
