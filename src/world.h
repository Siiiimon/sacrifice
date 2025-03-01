#ifndef WORLD_H
#define WORLD_H

#include "ecs/physics/position_component.h"
#include "ecs/entity_manager.h"

struct World {
    struct EntityManager* entities;
    struct PositionComponentArray* positions;
};

#endif
