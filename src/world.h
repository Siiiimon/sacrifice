#ifndef WORLD_H
#define WORLD_H

#include "ecs/physics/position_component.h"

struct World {
    struct PositionComponentArray* positions;
};

#endif
