#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include "world.h"

struct GameContext {
    struct World* world;
    int game_width;
    int game_height;
};

#endif
