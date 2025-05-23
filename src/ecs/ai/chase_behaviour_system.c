#include "chase_behaviour_system.h"
#include "raylib.h"
#include "raymath.h"

void UpdateChaseBehaviours(
    struct PositionComponent* positions[MAX_ENTITIES],
    struct VelocityComponent* velocities[MAX_ENTITIES],
    struct ChaseBehaviourComponent* chase_behaviours[MAX_ENTITIES]
) {
    if (!positions || !velocities || !chase_behaviours) {
        TraceLog(LOG_ERROR, "UpdateChaseBehaviours: positions, velocities or chase_behaviours is NULL");
        return;
    }
    for (Entity i = 0; i < MAX_ENTITIES; i++) {
        struct PositionComponent* position = positions[i];
        struct VelocityComponent* velocity = velocities[i];
        struct ChaseBehaviourComponent* chaseBehaviour = chase_behaviours[i];

        if (!position || !velocity || !chaseBehaviour)
            continue;

        struct PositionComponent* target_position = positions[chaseBehaviour->target];
        if (!target_position) {
            TraceLog(LOG_ERROR, "chase target entity not found for entity %u", i);
            continue;
        }

        Vector2 from_here_to_target = Vector2Subtract(CLITERAL(Vector2){target_position->x, target_position->y}, CLITERAL(Vector2){position->x, position->y});
        if (Vector2Length(from_here_to_target) > 0.0f) {
            from_here_to_target = Vector2Normalize(from_here_to_target);
        }

        Vector2 new_velocity = Vector2Scale(from_here_to_target, 3.0f);
        velocity->x = new_velocity.x;
        velocity->y = new_velocity.y;
    }
}
