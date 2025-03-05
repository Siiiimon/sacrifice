#ifndef DEBUG_H
#define DEBUG_H

#include "cimgui_include.h"
#include "../game_context.h"

void DrawDebugUI(struct GameContext* game_context);
void DrawCollisionBounds(RenderTexture2D debug_layer, struct PositionComponent* positions[MAX_ENTITIES], struct ColliderComponent* colliders[MAX_ENTITIES]);

#endif
