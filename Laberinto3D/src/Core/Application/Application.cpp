#include "Core/Application/Application.h"
#include "Gameplay/World/World.h"
#include "Graphics/Renderer/Renderer.h"
#include "Input/Input.h"


void Application::Run()
{
    m_Window.Init({.Name = "Laberinto 3D", .Width = WINDOW_WIDTH, .Height = WINDOW_HEIGHT});
    Renderer::Init();

    World world = World();
    world.Init();

    while (!m_Window.ShouldClose())
    {
        m_Window.OnUpdate();
        m_Window.Clear();

        world.OnUpdate();
        world.OnRender();

        Input::OnUpdate();
    }

    Renderer::Shutdown();
}
