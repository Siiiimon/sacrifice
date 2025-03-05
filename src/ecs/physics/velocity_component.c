#include "velocity_component.h"
#include "defs.h"
#include "raylib.h"
#include <stdlib.h>

struct VelocityComponent* NewVelocity(float x, float y) {
    struct VelocityComponent* velocity = malloc(sizeof(struct VelocityComponent));

    velocity->x = x;
    velocity->y = y;

    return velocity;
}

void FreeVelocity(struct VelocityComponent* velocity) {
    free(velocity);
}
