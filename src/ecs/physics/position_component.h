#ifndef ECS_PHYSICS_POSITION_COMPONENT_H
#define ECS_PHYSICS_POSITION_COMPONENT_H

#include "defs.h"

struct PositionComponentArray {
    struct PositionComponent* components[MAX_ENTITIES];
};

struct PositionComponent {
    float x;
    float y;
};

struct PositionComponentArray* NewPositionComponentArray(void);
void FreePositionComponentArray(struct PositionComponentArray* position_components);

void AddPositionToEntity(unsigned int entity, struct PositionComponentArray* position_components, float x, float y);
struct PositionComponent* GetPosition(struct PositionComponentArray* position_components, unsigned int entity);
void FreePosition(struct PositionComponent* component);

#endif
