#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "defs.h"

#include <ecs.h>

struct PositionComponent {
    float x;
    float y;
};

struct PositionComponent* NewPosition(float x, float y);
void FreePosition(struct PositionComponent* component);

#endif
