#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"
#include "main_ui.h"
#include "imgui_wrapper.h"

extern "C" {

void SetupImGui(bool dark_theme) {
    rlImGuiSetup(dark_theme);
}

void BeginImGuiFrame(void) {
    rlImGuiBegin();
}

void EndImGuiFrame(void) {
    rlImGuiEnd();
}

void ShutdownImGui(void) {
    rlImGuiShutdown();
}

void SetImGuiStyle(float fontSize, float framePadding, float windowRounding) {
    ImGuiIO& io = ImGui::GetIO();
    io.FontGlobalScale = 1.0f;

    ImGuiStyle& style = ImGui::GetStyle();

    style.FramePadding = ImVec2(framePadding, framePadding);
    style.WindowRounding = windowRounding;

    io.Fonts->Clear();
    io.Fonts->AddFontDefault();
    io.Fonts->Build();

    if (fontSize > 0) {
        io.FontGlobalScale = fontSize / 13.0f;
    }

    rlImGuiReloadFonts();
}

void SetImGuiDpiScale(float dpiScale) {
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(dpiScale);
    SetImGuiStyle(13.0f * dpiScale, 4.0f * dpiScale, 2.0f * dpiScale);
}

void ShowDebugUI(void) {
    ShowMainDebugUI();
}

} // extern "C"
