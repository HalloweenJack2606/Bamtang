#pragma once
#include "Core/CoreMinimal.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct WindowData
{
    CString Name;
    uint32 Width;
    uint32 Height;

    std::function<void(int32 keycode, int32 action)> KeyCodeFunc;
};

class Window
{
public:
    Window() = default;

    void Init(const WindowData& data);

    void OnUpdate();
    void Clear() const;

    [[nodiscard]] inline static double GetTime() noexcept { return glfwGetTime(); }

    [[nodiscard]] inline bool ShouldClose() const noexcept { return m_bShouldClose; }
private:
    bool m_bShouldClose = false;

    WindowData m_Data;
    GLFWwindow* m_pWindow = nullptr;
};
