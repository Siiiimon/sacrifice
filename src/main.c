#include "raylib.h"
#include "imgui_wrapper.h"

int main(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Sacrifice");
    SetupImGui(true);

    // TODO: check on normal dpi displays
    SetImGuiDpiScale(1.0f);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

#ifdef DEBUG
        BeginImGuiFrame();
        ShowDebugUI();
        EndImGuiFrame();
#endif

        EndDrawing();
    }

    ShutdownImGui();
    CloseWindow();

    return 0;
}
