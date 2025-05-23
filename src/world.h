#ifndef WORLD_H
#define WORLD_H

#include "ecs/ecs.h"
#include "ecs/physics/position_component.h"
#include "ecs/physics/velocity_component.h"
#include "ecs/physics/collider_component.h"
#include "ecs/ai/chase_behaviour_component.h"
#include "ecs/render/sprite_component.h"
#include "tag_component.h"

struct World {
    struct ECS* ecs;

    float player_move_speed;

    RenderTexture2D debug_layer;
    bool should_draw_collision_bounds;
};

#endif
