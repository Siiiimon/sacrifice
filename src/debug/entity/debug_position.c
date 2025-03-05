#include "debug_position.h"
#include "cimgui_include.h"

void DrawPositionDebug(RenderTexture2D debug_layer, struct PositionComponent* position) {
    BeginTextureMode(debug_layer);
    DrawLineEx(
        CLITERAL(Vector2){position->x - 8, position->y},
        CLITERAL(Vector2){position->x + 8, position->y},
        2.0f,
        MAGENTA);
    DrawLineEx(
        CLITERAL(Vector2){position->x, position->y - 8},
        CLITERAL(Vector2){position->x, position->y + 8},
        2.0f,
        MAGENTA);
    EndTextureMode();
    float pos[2] = {position->x, position->y};
    if (igDragFloat2("Position", pos, 0.5f, 0.0f, 0.0f, "%.1f", 0)) {
        position->x = pos[0];
        position->y = pos[1];
    }
    igSameLine(0.0f, 0.0f);
    if (igSmallButton("[C]")) {
        TraceLog(LOG_TRACE, "copied position to clipboard");
        SetClipboardText(TextFormat("%.1f, %.1f", position->x, position->y));
    }
}
