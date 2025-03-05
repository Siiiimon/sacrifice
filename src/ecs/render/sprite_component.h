#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "defs.h"
#include "raylib.h"

#include <ecs.h>

struct SpriteComponentArray {
    struct SpriteComponent* components[MAX_ENTITIES];
};

struct SpriteComponent {
    Texture texture;
};

struct SpriteComponentArray* NewSpriteComponentArray(void);
void FreeSpriteComponentArray(struct SpriteComponentArray* sprites);

void AddSpriteToEntity(Entity entity, struct SpriteComponentArray* sprites, Texture texture);
struct SpriteComponent* GetSprite(struct SpriteComponentArray* sprites, Entity entity);
void FreeSprite(struct SpriteComponent* sprite);

#endif
