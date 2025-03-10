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
    bool bResizable;
};

class Window
{
public:
    void Init(const WindowData& data);
    void OnUpdate();
    void Clear();

    [[nodiscard]] inline bool ShouldClose() const noexcept { return m_bShouldClose; }
private:
    bool m_bShouldClose = false;
    WindowData m_Data;
    GLFWwindow* m_pWindow = nullptr;
};
