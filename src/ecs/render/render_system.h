#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "render/sprite_component.h"
#include "physics/position_component.h"

void RenderSprites(struct SpriteComponentArray* sprites, struct PositionComponent* positions[MAX_ENTITIES]);

#endif
