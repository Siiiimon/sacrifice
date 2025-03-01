#include "imgui.h"
#include "raylib.h"
#include <cstdio>
#include "main_ui.h"

extern "C" {

void ShowMainDebugUI(void) {
    ImGui::Begin("Debug");

    if (ImGui::CollapsingHeader("Performance", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Text("FPS: %d", GetFPS());
        ImGui::Text("Frame Time: %.3f ms", GetFrameTime() * 1000.0f);
    }

    // System info
    if (ImGui::CollapsingHeader("System")) {
        ImGui::Text("Window Size: %d x %d", GetScreenWidth(), GetScreenHeight());
        ImGui::Text("DPI Scale: %.2f", GetWindowScaleDPI().x);
        ImGui::Text("Platform: %s",
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
    ImGui::End();
}

} // extern "C"
