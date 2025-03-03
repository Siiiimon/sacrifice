#ifndef DEBUG_H
#define DEBUG_H

#include "cimgui_include.h"
#include "../game_context.h"

#include "debug_entities.h"

void DrawDebugUI(struct GameContext* game_context);
void DrawCollisionBounds(RenderTexture2D debug_layer, struct PositionComponentArray* positions, struct ColliderComponentArray* colliders);

#endif
