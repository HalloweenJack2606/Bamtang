#pragma once
#include "Input/Codes/KeyCodes.h"
#include "Input/Codes/ActionCodes.h"

class Input
{
public:
    static void OnUpdate();

    static bool IsKeyPressed(KeyCode keycode);
    static bool IsKeyReleased(KeyCode keycode);
private:
    friend class Window;

    static void OnKeyEvent(int32 keycode, int32 action);

private:
    inline static std::unordered_map<KeyCode, bool> s_KeyPressedMap;
    inline static std::unordered_map<KeyCode, bool> s_KeyReleasedMap;
};
