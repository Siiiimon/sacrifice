#ifndef DEBUG_POSITION_H
#define DEBUG_POSITION_H

#include "raylib.h"
#include "../../ecs/physics/position_component.h"

void DrawPositionDebug(RenderTexture2D debug_layer, struct PositionComponent* position);

#endif //DEBUG_POSITION_H
