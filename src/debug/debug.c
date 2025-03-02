#include "debug.h"
#include "debug_entities.h"

void DrawDebugUI(struct GameContext *game_context) {
    igBegin("Debug", NULL, 0);
    if (igCollapsingHeader_TreeNodeFlags("Performance", ImGuiTreeNodeFlags_DefaultOpen)) {
        igText("FPS: %d", GetFPS());
    }
    if (igCollapsingHeader_TreeNodeFlags("System", ImGuiTreeNodeFlags_DefaultOpen)) {
        igText("DPI scale: %f", GetWindowScaleDPI().x);
        igText("Platform: %s",
        #if defined(_WIN32)
            "Windows"
        #elif defined(__APPLE__)
            "macOS"
        #elif defined(__linux__)
            "Linux"
        #else
            "Unknown"
        #endif
        );
    }
    igEnd();

    DrawEntitiesDebugUI(game_context);
}
