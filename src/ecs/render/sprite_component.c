#include "sprite_component.h"
#include "raylib.h"
#include <stdlib.h>

struct SpriteComponent* NewSprite(Texture texture) {
    struct SpriteComponent* sprite = malloc(sizeof(struct SpriteComponent));

    sprite->texture = texture;

    return sprite;
}

void FreeSprite(struct SpriteComponent *sprite) {
    if (!sprite) {
        return;
    }
    UnloadTexture(sprite->texture);
    free(sprite);
}
