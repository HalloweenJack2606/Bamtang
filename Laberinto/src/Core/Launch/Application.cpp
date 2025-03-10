#include "Core/Launch/Application.h"
#include "Graphics/Renderer2D/Renderer2D.h"
#include "World/World/World.h"

Application::Application(CommandLineArgs args)
{

}

void Application::Run()
{
    m_pWindow = new Window();
    m_pWindow->Init({.Name = "Laberinto pero cheverenge", .Width = 800, .Height = 600});

    Renderer2D::Init();

    Camera camera;
    camera.SetViewportSize(800, 600);
    camera.SetOrthographic(30, 0, 10);

    World world;
    world.Init();

    while(!m_pWindow->ShouldClose())
    {
        m_pWindow->OnUpdate();
        m_pWindow->Clear();
        camera.OnUpdate();
        Renderer2D::BeginScene(camera);
        world.OnUpdate();
        Renderer2D::EndScene();
    }

    Renderer2D::Shutdown();
}
