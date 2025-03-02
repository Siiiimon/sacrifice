#include "input.h"

Vector2 GetMovementInput(void)
{
    Vector2 movement = {0.0f, 0.0f};

    if (IsKeyDown(KEY_W)) movement.y -= 1.0f;
    if (IsKeyDown(KEY_S)) movement.y += 1.0f;
    if (IsKeyDown(KEY_A)) movement.x -= 1.0f;
    if (IsKeyDown(KEY_D)) movement.x += 1.0f;

    return movement;
}
