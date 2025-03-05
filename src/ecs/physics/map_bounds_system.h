#ifndef MAP_BOUNDS_SYSTEM_H
#define MAP_BOUNDS_SYSTEM_H

#include "collider_component.h"
#include "position_component.h"

void UpdateMapBounds(struct PositionComponent* positions[MAX_ENTITIES], struct ColliderComponent* colliders[MAX_ENTITIES], Vector2 map_size);

#endif
