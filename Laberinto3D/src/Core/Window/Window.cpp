#include "Core/Window/Window.h"
#include "Input/Input.h"

void Window::Init(const WindowData& data)
{
    m_Data = data;
    m_Data.KeyCodeCallback = Input::OnKeyEvent;

    if(!glfwInit())
    {
        std::cout << "Error initializing GLFW" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);

    m_pWindow = glfwCreateWindow((int32)m_Data.Width, (int32)m_Data.Height, m_Data.Name.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(m_pWindow);

    glewExperimental = true;
    if(glewInit() != GLEW_OK)
    {
        std::cout << "Error initializing GLEW" << std::endl;
    }

    glfwSetWindowUserPointer(m_pWindow, (void*)&m_Data);

    glfwSetKeyCallback(m_pWindow,[](GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto* data = (WindowData*)glfwGetWindowUserPointer(window);
        data->KeyCodeCallback(key, action);
    });

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
}

void Window::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_pWindow);
    m_bShouldClose = glfwWindowShouldClose(m_pWindow);
}

void Window::Clear()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}
