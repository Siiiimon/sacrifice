#include "tag_component.h"
#include "raylib.h"
#include <stdlib.h>

struct TagComponent* NewTag(enum ENTITY_TAG tag) {
    struct TagComponent* tag_component = malloc(sizeof(struct TagComponent));

    tag_component->tag = tag;

    return tag_component;
}

void FreeTag(struct TagComponent* tag) {
    if (!tag) return;
    free(tag);
}

const char* GetTagName(enum ENTITY_TAG tag) {
    switch (tag) {
        case ENTITY_TAG_PLAYER:
            return "Player";
        case ENTITY_TAG_WALL:
            return "Wall";
        case ENTITY_TAG_ENEMY:
            return "Projectile";
        default:
            return "Unknown";
    }
}
