#include "Core/Launch/Application.h"
#include "Graphics/Renderer2D/Renderer2D.h"
#include "Graphics/CubeRenderer/CubeRenderer.h"
#include "World/World/World.h"
#include "Input/Input.h"

Application::Application(CommandLineArgs args)
{

}

void Application::Run()
{
    m_pWindow = new Window();
    m_pWindow->Init({.Name = "Laberinto 2D", .Width = WINDOW_WIDTH, .Height = WINDOW_HEIGHT});

    Renderer2D::Init();
    CubeRenderer::Init();

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

    CubeRenderer::Shutdown();
    Renderer2D::Shutdown();
}
