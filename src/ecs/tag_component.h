#ifndef TAG_COMPONENT_H
#define TAG_COMPONENT_H

#include "defs.h"

#include <ecs.h>

enum ENTITY_TAG {
    ENTITY_TAG_PLAYER = 0,
    ENTITY_TAG_WALL = 1 << 0,
    ENTITY_TAG_ENEMY = 1 << 1,
};

struct TagComponent {
    enum ENTITY_TAG tag;
};

struct TagComponent* NewTag(enum ENTITY_TAG tag);
void FreeTag(struct TagComponent* tag);

const char* GetTagName(enum ENTITY_TAG tag);

#endif // TAG_COMPONENT_H
