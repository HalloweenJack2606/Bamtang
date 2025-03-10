#include "Core/Launch/Application.h"
#include "Graphics/Renderer2D/Renderer2D.h"
#include "World/World/World.h"
#include "Input/Input.h"

Application::Application(CommandLineArgs args)
{

}

void Application::Run()
{
    m_pWindow = new Window();
    m_pWindow->Init({.Name = "Laberinto pero cheverenge", .Width = 800, .Height = 600});

    Renderer2D::Init();

    World world;
    world.Init();

    while(!m_pWindow->ShouldClose())
    {
        m_pWindow->OnUpdate();
        m_pWindow->Clear();

        world.OnUpdate();
        world.OnRender();

        Input::OnUpdate();
    }

    Renderer2D::Shutdown();
}
