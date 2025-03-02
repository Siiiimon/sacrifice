#include "sprite_component.h"
#include "defs.h"
#include "raylib.h"
#include <stdlib.h>

struct SpriteComponentArray* NewSpriteComponentArray(void) {
    struct SpriteComponentArray* sprites = malloc(sizeof(struct SpriteComponentArray));
    if (!sprites) {
        TraceLog(LOG_ERROR, "Failed to allocate memory for SpriteComponentArray");
        return NULL;
    }

    for (int i = 0; i < MAX_ENTITIES; i++) {
        sprites->components[i] = NULL;
    }

    return sprites;
}

void FreeSpriteComponentArray(struct SpriteComponentArray* sprites) {
    if (!sprites) {
        return;
    }
    for (int i = 0; i < MAX_ENTITIES; i++) {
        FreeSprite(sprites->components[i]);
    }
    free(sprites);
}


void AddSpriteToEntity(unsigned int entity, struct SpriteComponentArray* sprites, Texture texture) {
    if (!sprites) {
        TraceLog(LOG_ERROR, "Failed to add Sprite because SpriteComponentArray is NULL");
        return;
    }
    if (entity > MAX_ENTITIES) {
        TraceLog(LOG_ERROR, "Failed to add Sprite because entity ID is out of bounds");
        return;
    }

    struct SpriteComponent* sprite = malloc(sizeof(struct SpriteComponent));
    if (!sprite) {
        TraceLog(LOG_ERROR, "Failed to allocate memory for SpriteComponent");
        return;
    }

    sprite->texture = texture;

    if (sprites->components[entity] != NULL) {
        TraceLog(LOG_ERROR, "entity %u already has a SpriteComponent", entity);
        FreeSprite(sprite);
        return;
    }
    sprites->components[entity] = sprite;
}

struct SpriteComponent* GetSprite(struct SpriteComponentArray* sprites, unsigned int entity) {
    if (!sprites) {
        TraceLog(LOG_ERROR, "Failed to get Sprite because SpriteComponentArray is NULL");
        return NULL;
    }
    if (entity > MAX_ENTITIES) {
        TraceLog(LOG_ERROR, "Failed to get Sprite because entity ID is out of bounds");
        return NULL;
    }

    return sprites->components[entity];
}

void FreeSprite(struct SpriteComponent *sprite) {
    if (!sprite) {
        return;
    }
    UnloadTexture(sprite->texture);
    free(sprite);
}
