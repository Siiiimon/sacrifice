#include "render_system.h"

void RenderSprites(struct SpriteComponentArray* sprites, struct PositionComponentArray* positions) {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        struct SpriteComponent* sprite = sprites->components[i];
        struct PositionComponent* position = positions->components[i];
        if (sprite && position) {
            DrawTexture(sprite->texture, position->x, position->y, WHITE);
        }
    }
}
