#include "raylib.h"
#include "imgui_wrapper.h"

int main(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetupImGui(true);

    // TODO: check on normal dpi displays
    SetImGuiDpiScale(1.0f);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
#ifdef DEBUG
        DrawText("Debug mode enabled!", 10, 10, 20, RED);
#endif

        BeginImGuiFrame();
        ShowDebugUI();
        EndImGuiFrame();

        EndDrawing();
    }

    ShutdownImGui();
    CloseWindow();

    return 0;
}
