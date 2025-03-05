#ifndef VELOCITY_COMPONENT_H
#define VELOCITY_COMPONENT_H

#include "defs.h"

#include <ecs.h>

struct VelocityComponentArray {
    struct VelocityComponent* components[MAX_ENTITIES];
};

struct VelocityComponent {
    float x;
    float y;
};

struct VelocityComponentArray* NewVelocityComponentArray(void);
void FreeVelocityComponentArray(struct VelocityComponentArray* velocities);

void AddVelocityToEntity(Entity entity, struct VelocityComponentArray* velocities, float x, float y);
struct VelocityComponent* GetVelocity(struct VelocityComponentArray* velocities, Entity entity);
void FreeVelocity(struct VelocityComponent* velocity);

#endif
