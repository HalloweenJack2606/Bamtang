#include "Input/Input.h"

void Input::OnUpdate()
{
    for (auto& [keycode, released] : s_KeyReleasedMap)
    {
        released = false;
    }

    for (auto& [keycode, pressed] : s_KeyPressedMap)
    {
        pressed = false;
    }
}

bool Input::IsKeyPressed(KeyCode keycode)
{
    return s_KeyPressedMap[keycode];
}

bool Input::IsKeyReleased(KeyCode keycode)
{
    return s_KeyReleasedMap[keycode];
}

bool Input::IsKeyDown(KeyCode keycode)
{
    return s_KeyDownMap[keycode];
}

bool Input::IsKeyUp(KeyCode keycode)
{
    return s_KeyUpMap[keycode];
}

void Input::OnKeyEvent(int32 keycode, int32 action)
{
    if (action == InputAction::Press)
    {
        s_KeyPressedMap[keycode] = true;
        s_KeyDownMap[keycode] = true;
        s_KeyReleasedMap[keycode] = false;
        s_KeyUpMap[keycode] = false;
    }
    else if (action == InputAction::Release)
    {
        s_KeyPressedMap[keycode] = false;
        s_KeyDownMap[keycode] = false;
        s_KeyReleasedMap[keycode] = true;
        s_KeyUpMap[keycode] = true;
    }
}
