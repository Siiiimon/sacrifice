#ifndef WORLD_H
#define WORLD_H

#include "ecs/entity_manager.h"
#include "ecs/physics/position_component.h"
#include "ecs/physics/velocity_component.h"
#include "ecs/physics/collider_component.h"
#include "ecs/ai/chase_behaviour_component.h"
#include "ecs/render/sprite_component.h"
#include "tag_component.h"

struct World {
    struct EntityManager* entities;
    struct TagComponentArray* tags;
    struct PositionComponentArray* positions;
    struct VelocityComponentArray* velocities;
    struct SpriteComponentArray* sprites;
    struct ColliderComponentArray* colliders;
    struct ChaseBehaviourComponentArray* chase_behaviours;

    float player_move_speed;

    RenderTexture2D debug_layer;
    bool should_draw_collision_bounds;
};

#endif
