#include "render_system.h"

#include "sprite_component.h"

#include <raylib.h>

void RenderSprites(struct SpriteComponent* sprites[MAX_ENTITIES], struct PositionComponent* positions[MAX_ENTITIES]) {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        struct SpriteComponent* sprite = sprites[i];
        struct PositionComponent* position = positions[i];
        if (sprite && position) {
            DrawTexture(sprite->texture, position->x, position->y, WHITE);
        }
    }
}
