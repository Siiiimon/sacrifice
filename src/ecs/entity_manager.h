#ifndef ECS_ENTITY_MANAGER_H
#define ECS_ENTITY_MANAGER_H

#include "defs.h"
#include <stdbool.h>

struct EntityManager {
    unsigned int entities[MAX_ENTITIES];
    bool active_entities[MAX_ENTITIES];
    unsigned int next_entity;
};

struct EntityManager* NewEntityManager(void);
void FreeEntityManager(struct EntityManager* manager);

unsigned int NewEntity(struct EntityManager* manager);
unsigned int* GetActiveEntities(struct EntityManager* manager, unsigned int* count);
void RemoveEntity(struct EntityManager* manager, unsigned int entity);

#endif
