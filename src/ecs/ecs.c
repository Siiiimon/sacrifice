#include "ecs.h"
#include "raylib.h"
#include <stdlib.h>
#include <string.h>

struct ECS* NewECS(void) {
    struct ECS* manager = malloc(sizeof(struct ECS));
    if (!manager) {
        TraceLog(LOG_ERROR, "Failed to allocate memory for EntityManager");
        return NULL;
    }

    memset(manager->entities, 0, sizeof(manager->entities));
    memset(manager->active_entities, false, sizeof(manager->active_entities));
    manager->next_entity = 1;
    memset(manager->tag_component_array, 0, sizeof(struct TagComponent*) * MAX_ENTITIES);
    memset(manager->position_component_array, 0, sizeof(struct PositionComponent*) * MAX_ENTITIES);
    memset(manager->velocity_component_array, 0, sizeof(struct VelocityComponent*) * MAX_ENTITIES);
    memset(manager->sprite_component_array, 0, sizeof(struct SpriteComponent*) * MAX_ENTITIES);
    memset(manager->collider_component_array, 0, sizeof(struct ColliderComponent*) * MAX_ENTITIES);
    memset(manager->health_component_array, 0, sizeof(struct HealthComponent*) * MAX_ENTITIES);

    return manager;
}

void FreeECS(struct ECS *manager) {
    free(manager);
}

void AttachComponentToEntity(struct ECS* ecs, Entity entity, void* component, enum ComponentType component_type) {
    if (!ecs->active_entities[entity]) {
        TraceLog(LOG_ERROR, "Failed to attach component to %u, but it's not an active entity", entity);
        return;
    }

    switch (component_type) {
    case COMPONENT_TYPE_TAG:
        ecs->tag_component_array[entity] = (struct TagComponent*)component;
    case COMPONENT_TYPE_POSITION:
        ecs->position_component_array[entity] = (struct PositionComponent*)component;
        break;
    case COMPONENT_TYPE_VELOCITY:
        ecs->velocity_component_array[entity] = (struct VelocityComponent*)component;
    case COMPONENT_TYPE_SPRITE:
        ecs->sprite_component_array[entity] = (struct SpriteComponent*)component;
    case COMPONENT_TYPE_COLLIDER:
        ecs->collider_component_array[entity] = (struct ColliderComponent*)component;
    case COMPONENT_TYPE_HEALTH:
        ecs->health_component_array[entity] = (struct HealthComponent*)component;
    default:
        TraceLog(LOG_ERROR, "Failed to attach component to %u, but it's an unknown component type");
    }
}

void* GetComponentOfEntity(struct ECS* ecs, Entity entity, enum ComponentType component_type) {
    if (!ecs->active_entities[entity]) {
        TraceLog(LOG_ERROR, "Failed to get component of %u, but it's not an active entity", entity);
        return NULL;
    }

    switch (component_type) {
    case COMPONENT_TYPE_TAG:
        return ecs->tag_component_array[entity];
    case COMPONENT_TYPE_POSITION:
        return ecs->position_component_array[entity];
    case COMPONENT_TYPE_VELOCITY:
        return ecs->velocity_component_array[entity];
    case COMPONENT_TYPE_SPRITE:
        return ecs->sprite_component_array[entity];
    case COMPONENT_TYPE_COLLIDER:
        return ecs->collider_component_array[entity];
    case COMPONENT_TYPE_HEALTH:
        return ecs->health_component_array[entity];
    default:
        TraceLog(LOG_ERROR, "Failed to get component of %u, but it's an unknown component type");
    }

    TraceLog(LOG_ERROR, "How did we get here?");
    return NULL;
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
