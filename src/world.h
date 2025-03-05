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
    struct TagComponentArray* tags;
    struct VelocityComponentArray* velocities;
    struct SpriteComponentArray* sprites;
    struct ColliderComponentArray* colliders;
    struct HealthComponentArray* healths;
    struct HarmComponentArray* harms;
    struct ChaseBehaviourComponentArray* chase_behaviours;

    float player_move_speed;

    RenderTexture2D debug_layer;
    bool should_draw_collision_bounds;
};

#endif
