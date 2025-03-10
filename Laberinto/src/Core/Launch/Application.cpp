#include "Core/Launch/Application.h"
#include "Graphics/Renderer2D/Renderer2D.h"

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
    camera.SetOrthographic(10, 0, 10);

    while(!m_pWindow->ShouldClose())
    {
        m_pWindow->OnUpdate();
        m_pWindow->Clear();
        camera.OnUpdate();
        Renderer2D::BeginScene(camera);
        vec2 position = vec2(0.0f);
        vec2 size = vec2(1.0f);
        Renderer2D::DrawQuad(position, size, Colors::Red());
        vec2 position2 = vec2(1);
        vec2 size2 = vec2(0.5f);
        Renderer2D::DrawQuad(position2, size2, Colors::Green());
        Renderer2D::EndScene();
    }

    Renderer2D::Shutdown();
}
