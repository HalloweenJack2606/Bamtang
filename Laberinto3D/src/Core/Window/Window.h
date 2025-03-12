#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Core/CoreMinimal.h"

struct WindowData
{
    CString Name;
    uint32 Width;
    uint32 Height;
    std::function<void(int32, int32)> KeyCodeCallback;
};

class Window
{
public:
    void Init(const WindowData& data);
    void OnUpdate();
    void Clear();

    [[nodiscard]] inline bool ShouldClose() const { return m_bShouldClose; }
private:
    bool m_bShouldClose = false;

    WindowData m_Data;
    GLFWwindow* m_pWindow = nullptr;
};