#include "Core/Launch/Application.h"
#include "Input/Input.h"
#include "Graphics/CircleRenderer/CircleRenderer.h"
#include "Graphics/LineRenderer/LineRenderer.h"
#include "World/World/World.h"

Application::Application(CommandLineArgs args)
{

}

void Application::Run()
{
    m_pWindow = new Window();
    m_pWindow->Init({.Name = "Fisica", .Width = WINDOW_WIDTH, .Height = WINDOW_HEIGHT});
    CircleRenderer::Init();

    World world;
    world.Init();

    float accumulatedTime = 0.0f;
    float lastFrame = 0.0f;

    while(!m_pWindow->ShouldClose())
    {
        auto time = (float)m_pWindow->GetTime();
        auto deltaTime = time - lastFrame;
        lastFrame = time;
        accumulatedTime += deltaTime;

        m_pWindow->OnUpdate();
        m_pWindow->Clear();
        world.OnUpdate(deltaTime);
        world.OnRender();

        Input::OnUpdate();
    }

    CircleRenderer::Shutdown();
    LineRenderer::Shutdown();
}
