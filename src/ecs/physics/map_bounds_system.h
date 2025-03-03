#ifndef MAP_BOUNDS_SYSTEM_H
#define MAP_BOUNDS_SYSTEM_H

#include "collider_component.h"
#include "position_component.h"

void UpdateMapBounds(struct PositionComponentArray* positions, struct ColliderComponentArray* colliders, Vector2 map_size);

#endif
