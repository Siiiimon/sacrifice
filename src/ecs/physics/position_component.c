#include "position_component.h"
#include <stdlib.h>


struct PositionComponent* NewPosition(float x, float y) {
    struct PositionComponent* pos = malloc(sizeof(struct PositionComponent));

    pos->x = x;
    pos->y = y;

    return pos;
}

void FreePosition(struct PositionComponent* position) {
    free(position);
}
