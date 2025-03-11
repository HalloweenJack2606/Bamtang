#include "Core/Window/Window.h"
#include "Input/Input.h"

static void GLFWErrorCallback(int error, const char* desc)
{
    std::cout << "GLFW Error (" << error << "): " << desc << std::endl;
}

void Window::Init(const WindowData& data)
{
    m_Data = data;
    m_Data.KeyCodeFunc = Input::OnKeyEvent;
    m_Data.MousePosFun = Input::OnMousePositionEvent;
    auto success = glfwInit();
    if(!success)
    {
        std::cout << "Could not initialize GLFW" << std::endl;
    }
    glfwSetErrorCallback(GLFWErrorCallback);

    glfwWindowHint(GLFW_RESIZABLE, m_Data.bResizable ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef PLATFORM_APPLE
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);
#endif

    m_pWindow = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Name.c_str(), nullptr, nullptr);
    if(!m_pWindow)
    {
        std::cout << "Could not create GLFW Window" << std::endl;
    }
    glfwMakeContextCurrent(m_pWindow);
    glewExperimental = true;
    auto glewSuccess = glewInit();
    if(glewSuccess != GLEW_OK)
    {
        std::cout << "Could not initialize GLEW" << std::endl;
    }

    glfwSetWindowUserPointer(m_pWindow, &m_Data);

    glfwSetKeyCallback(m_pWindow, [](GLFWwindow* pWindow, int32 keycode, int32 scancode, int32 action, int32 mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(pWindow);
        data.KeyCodeFunc(keycode, action);
    });

    glfwSetCursorPosCallback(m_pWindow, [](GLFWwindow* pWindow, double xpos, double ypos) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(pWindow);
        data.MousePosFun(xpos, ypos);
    });

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Window::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_pWindow);
    m_bShouldClose = glfwWindowShouldClose(m_pWindow);
}

void Window::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
