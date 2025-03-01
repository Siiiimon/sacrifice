#ifndef IMGUI_WRAPPER_H
#define IMGUI_WRAPPER_H


#ifdef __cplusplus
extern "C" {
#endif

void SetupImGui(bool dark_theme);
void BeginImGuiFrame(void);
void EndImGuiFrame(void);
void ShutdownImGui(void);

void SetImGuiStyle(float fontSize, float framePadding, float windowRounding);
void SetImGuiDpiScale(float dpiScale);

void ShowDebugUI(void);

#ifdef __cplusplus
}
#endif

#endif // IMGUI_WRAPPER_H
