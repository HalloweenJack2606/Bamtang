#pragma once
#include "Input/Codes/KeyCodes.h"
#include "Input/Codes/ActionCodes.h"

class Input
{
public:
    static void OnUpdate();

    static bool IsKeyPressed(KeyCode keycode);
    static bool IsKeyReleased(KeyCode keycode);
    static bool IsKeyDown(KeyCode keycode);
    static bool IsKeyUp(KeyCode keycode);

    static vec2 GetMousePosition();
    static vec2 GetMouseDelta();
private:
    friend class Window;

    static void OnKeyEvent(int32 keycode, int32 action);
    static void OnMousePositionEvent(double xpos, double ypos);
private:
    inline static std::unordered_map<KeyCode, bool> s_KeyPressedMap;
    inline static std::unordered_map<KeyCode, bool> s_KeyReleasedMap;
    inline static std::unordered_map<KeyCode, bool> s_KeyDownMap;
    inline static std::unordered_map<KeyCode, bool> s_KeyUpMap;

    inline static vec2 s_MousePosition = vec2(0.0f);
    inline static vec2 s_LastMousePosition = vec2(0.0f);
};
