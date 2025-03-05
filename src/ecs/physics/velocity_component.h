#ifndef VELOCITY_COMPONENT_H
#define VELOCITY_COMPONENT_H

#include "defs.h"

#include <ecs.h>

struct VelocityComponent {
    float x;
    float y;
};

struct VelocityComponent* NewVelocity(float x, float y);
void FreeVelocity(struct VelocityComponent* velocity);

#endif
