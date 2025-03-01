#ifndef WORLD_H
#define WORLD_H

#include "ecs/entity_manager.h"
#include "ecs/physics/position_component.h"
#include "ecs/physics/velocity_component.h"

struct World {
    struct EntityManager* entities;
    struct PositionComponentArray* positions;
    struct VelocityComponentArray* velocities;
};

#endif
