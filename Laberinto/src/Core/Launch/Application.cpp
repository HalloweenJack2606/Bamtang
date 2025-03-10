#include "Core/Launch/Application.h"

Application::Application(CommandLineArgs args)
{

}

void Application::Run()
{
    m_pWindow = new Window();
    m_pWindow->Init({.Name = "Laberinto pero cheverenge", .Width = 800, .Height = 600});

    while(!m_pWindow->ShouldClose())
    {
        m_pWindow->OnUpdate();
    }
}
