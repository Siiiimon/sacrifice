#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include "world.h"

struct GameContext {
    struct World* world;
    int game_width;
    int game_height;

#ifdef DEBUG
    unsigned int currently_inspected_entity_id;
#endif
};

#endif
