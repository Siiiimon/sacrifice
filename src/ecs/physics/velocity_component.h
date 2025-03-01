#ifndef VELOCITY_COMPONENT_H
#define VELOCITY_COMPONENT_H

#include "defs.h"

struct VelocityComponentArray {
    struct VelocityComponent* components[MAX_ENTITIES];
};

struct VelocityComponent {
    float x;
    float y;
};

struct VelocityComponentArray* NewVelocityComponentArray(void);
void FreeVelocityComponentArray(struct VelocityComponentArray* velocities);

void AddVelocityToEntity(unsigned int entity, struct VelocityComponentArray* velocities, float x, float y);
struct VelocityComponent* GetVelocity(struct VelocityComponentArray* velocities, unsigned int entity);
void FreeVelocity(struct VelocityComponent* velocity);

#endif
