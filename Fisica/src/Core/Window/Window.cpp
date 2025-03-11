#include "Core/Window/Window.h"
#include "Input/Input.h"


void Window::Init(const WindowData& data)
{
    m_Data = data;
    m_Data.KeyCodeFunc = Input::OnKeyEvent;

    auto glfwSuccess = glfwInit();
    if(!glfwSuccess) std::cout << "Error Initializing GLFW" << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef PLATFORM_APPLE
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);
#endif


    m_pWindow = glfwCreateWindow((int32)m_Data.Width, (int32)m_Data.Height, m_Data.Name.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_pWindow);

    glewExperimental = true;
    if(glewInit() != GLEW_OK) std::cout << "Error initializing GLEW" << std::endl;

    glEnable(GL_BLEND);
    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetWindowUserPointer(m_pWindow, (void*)&m_Data);

    glfwSetKeyCallback(m_pWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto* dataPtr = (WindowData*)glfwGetWindowUserPointer(window);
        dataPtr->KeyCodeFunc(key, action);
    });

    glViewport(0, 0, data.Width, data.Height);
}

void Window::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_pWindow);
    m_bShouldClose = glfwWindowShouldClose(m_pWindow);
}

void Window::Clear() const
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
