#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "ecs/physics/collider_component.h"
#include "ecs/tag_component.h"
#include "position_component.h"

void UpdateColliders(struct PositionComponentArray* positions, struct ColliderComponentArray* colliders, struct TagComponentArray* tags);

#endif
