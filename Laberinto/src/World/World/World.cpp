#include "World/World/World.h"
#include "Graphics/Renderer2D/Renderer2D.h"


void World::Init()
{
    m_Maze.Generate(11);
    m_Maze.Print();
}

void World::OnUpdate()
{
    const uint32 mazeSize = m_Maze.GetSize();
    for(int y = 0; y < mazeSize; y++)
    {
        for(int x = 0; x < mazeSize; x++)
        {
            vec2 pos = vec2(x, y);
            if(m_Maze.At(pos) == '*') Renderer2D::DrawQuad(pos, vec2(1.0f), Colors::Red());
            if(m_Maze.At(pos) == 'A') Renderer2D::DrawQuad(pos, vec2(1.0f), Colors::Green());
            if(m_Maze.At(pos) == 'B') Renderer2D::DrawQuad(pos, vec2(1.0f), Colors::Blue());
        }
    }
}
