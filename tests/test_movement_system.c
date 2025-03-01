#include <greatest.h>
#include "ecs/physics/movement_system.h"
#include "ecs/physics/position_component.h"
#include "ecs/physics/velocity_component.h"
#include <stdlib.h>

/* Create component arrays for testing */
static struct PositionComponentArray* create_position_array(void) {
    struct PositionComponentArray* positions = malloc(sizeof(struct PositionComponentArray));
    memset(positions->components, 0, sizeof(positions->components));
    return positions;
}

static struct VelocityComponentArray* create_velocity_array(void) {
    struct VelocityComponentArray* velocities = malloc(sizeof(struct VelocityComponentArray));
    memset(velocities->components, 0, sizeof(velocities->components));
    return velocities;
}

/* Test movement with a single entity */
TEST test_update_movement_single_entity(void) {
    struct PositionComponentArray* positions = create_position_array();
    struct VelocityComponentArray* velocities = create_velocity_array();

    // Create components for entity 1
    struct PositionComponent* pos = malloc(sizeof(struct PositionComponent));
    pos->x = 10.0f;
    pos->y = 20.0f;
    positions->components[1] = pos;

    struct VelocityComponent* vel = malloc(sizeof(struct VelocityComponent));
    vel->x = 5.0f;
    vel->y = -3.0f;
    velocities->components[1] = vel;

    // Update movement
    UpdateMovement(positions, velocities);

    // Check position was updated
    ASSERT_EQ_FMT(15.0f, positions->components[1]->x, "%.1f");
    ASSERT_EQ_FMT(17.0f, positions->components[1]->y, "%.1f");

    // Cleanup
    free(pos);
    free(vel);
    free(positions);
    free(velocities);
    PASS();
}

/* Test movement with multiple entities */
TEST test_update_movement_multiple_entities(void) {
    struct PositionComponentArray* positions = create_position_array();
    struct VelocityComponentArray* velocities = create_velocity_array();

    // Entity 1
    struct PositionComponent* pos1 = malloc(sizeof(struct PositionComponent));
    pos1->x = 10.0f;
    pos1->y = 20.0f;
    positions->components[1] = pos1;

    struct VelocityComponent* vel1 = malloc(sizeof(struct VelocityComponent));
    vel1->x = 5.0f;
    vel1->y = -3.0f;
    velocities->components[1] = vel1;

    // Entity 2
    struct PositionComponent* pos2 = malloc(sizeof(struct PositionComponent));
    pos2->x = -5.0f;
    pos2->y = 8.0f;
    positions->components[2] = pos2;

    struct VelocityComponent* vel2 = malloc(sizeof(struct VelocityComponent));
    vel2->x = 1.0f;
    vel2->y = 2.0f;
    velocities->components[2] = vel2;

    // Update movement
    UpdateMovement(positions, velocities);

    // Check positions were updated
    ASSERT_EQ_FMT(15.0f, positions->components[1]->x, "%.1f");
    ASSERT_EQ_FMT(17.0f, positions->components[1]->y, "%.1f");

    ASSERT_EQ_FMT(-4.0f, positions->components[2]->x, "%.1f");
    ASSERT_EQ_FMT(10.0f, positions->components[2]->y, "%.1f");

    // Cleanup
    free(pos1);
    free(vel1);
    free(pos2);
    free(vel2);
    free(positions);
    free(velocities);
    PASS();
}

/* Test that entities without both position and velocity are skipped */
TEST test_update_movement_incomplete_components(void) {
    struct PositionComponentArray* positions = create_position_array();
    struct VelocityComponentArray* velocities = create_velocity_array();

    // Entity with position but no velocity
    struct PositionComponent* pos1 = malloc(sizeof(struct PositionComponent));
    pos1->x = 10.0f;
    pos1->y = 20.0f;
    positions->components[1] = pos1;

    // Entity with velocity but no position
    struct VelocityComponent* vel2 = malloc(sizeof(struct VelocityComponent));
    vel2->x = 5.0f;
    vel2->y = -3.0f;
    velocities->components[2] = vel2;

    // Complete entity
    struct PositionComponent* pos3 = malloc(sizeof(struct PositionComponent));
    pos3->x = 100.0f;
    pos3->y = 200.0f;
    positions->components[3] = pos3;

    struct VelocityComponent* vel3 = malloc(sizeof(struct VelocityComponent));
    vel3->x = 10.0f;
    vel3->y = 20.0f;
    velocities->components[3] = vel3;

    // Update movement
    UpdateMovement(positions, velocities);

    // Entity 1 should be unchanged
    ASSERT_EQ_FMT(10.0f, positions->components[1]->x, "%.1f");
    ASSERT_EQ_FMT(20.0f, positions->components[1]->y, "%.1f");

    // Entity 3 should be updated
    ASSERT_EQ_FMT(110.0f, positions->components[3]->x, "%.1f");
    ASSERT_EQ_FMT(220.0f, positions->components[3]->y, "%.1f");

    // Cleanup
    free(pos1);
    free(vel2);
    free(pos3);
    free(vel3);
    free(positions);
    free(velocities);
    PASS();
}

SUITE(movement_system_suite) {
    RUN_TEST(test_update_movement_single_entity);
    RUN_TEST(test_update_movement_multiple_entities);
    RUN_TEST(test_update_movement_incomplete_components);
}
