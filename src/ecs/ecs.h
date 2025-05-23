#ifndef ECS_ENTITY_MANAGER_H
#define ECS_ENTITY_MANAGER_H

#include "defs.h"
#include <stdbool.h>

typedef unsigned int Entity;

enum ComponentType {
    COMPONENT_TYPE_TAG,
    COMPONENT_TYPE_POSITION,
    COMPONENT_TYPE_VELOCITY,
    COMPONENT_TYPE_SPRITE,
    COMPONENT_TYPE_COLLIDER,
    COMPONENT_TYPE_HEALTH,
    COMPONENT_TYPE_HARM,
    COMPONENT_TYPE_CHASE_BEHAVIOUR,
};

struct ECS {
    Entity entities[MAX_ENTITIES];
    bool active_entities[MAX_ENTITIES];
    Entity next_entity;

    struct TagComponent* tag_component_array[MAX_ENTITIES];
    struct PositionComponent* position_component_array[MAX_ENTITIES];
    struct VelocityComponent* velocity_component_array[MAX_ENTITIES];
    struct SpriteComponent* sprite_component_array[MAX_ENTITIES];
    struct ColliderComponent* collider_component_array[MAX_ENTITIES];
    struct HealthComponent* health_component_array[MAX_ENTITIES];
    struct HarmComponent* harm_component_array[MAX_ENTITIES];
    struct ChaseBehaviourComponent* chase_behaviour_component_array[MAX_ENTITIES];
};

struct ECS* NewECS(void);
void FreeECS(struct ECS* manager);

void AttachComponentToEntity(struct ECS* ecs, Entity entity, void* component, enum ComponentType component_type);
void* GetComponentOfEntity(struct ECS* ecs, Entity entity, enum ComponentType component_type);
void FreeComponentArray(void* component_array);

Entity NewEntity(struct ECS* manager);
Entity* GetActiveEntities(struct ECS* manager, unsigned int* count);
void RemoveEntity(struct ECS* manager, Entity entity);

#endif
