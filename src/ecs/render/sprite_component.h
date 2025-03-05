#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "raylib.h"

#include <ecs.h>

struct SpriteComponent {
    Texture texture;
};

struct SpriteComponent* NewSprite(Texture texture);
void FreeSprite(struct SpriteComponent* sprite);

#endif
