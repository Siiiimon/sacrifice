#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "physics/position_component.h"

void RenderSprites(struct SpriteComponent* sprites[MAX_ENTITIES], struct PositionComponent* positions[MAX_ENTITIES]);

#endif
