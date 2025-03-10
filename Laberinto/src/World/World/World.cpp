#include "World/World/World.h"
#include "Graphics/Renderer2D/Renderer2D.h"
#include "Input/Input.h"


void World::Init()
{
    m_QuadShader.Init("assets/shaders/quad.glsl");
    m_CircleShader.Init("assets/shaders/circle.glsl");

    m_Camera.SetViewportSize(800, 600);
    m_Camera.SetViewportSize(800, 600);
    float halfMazeSize = (float)m_MazeSize / 2.0f - 0.5f;
    m_Camera.SetOrthographic((float)m_MazeSize, 0, 10);
    m_Camera.SetPosition(vec3(halfMazeSize, halfMazeSize, 0.0f));
    GenerateMaze();
}

void World::OnUpdate()
{
    PlayerMovement();
    m_Camera.OnUpdate();
    CheckGoal();
}

void World::OnRender()
{
    Renderer2D::SetShader(m_CircleShader);
    Renderer2D::BeginScene(m_Camera);
    Renderer2D::DrawQuad(m_PlayerPosition, vec2(1.0f), Colors::Green());
    Renderer2D::EndScene();

    Renderer2D::SetShader(m_QuadShader);
    Renderer2D::BeginScene(m_Camera);
    const uint32 mazeSize = m_Maze.GetSize();
    for (int y = 0; y < mazeSize; y++) {
        for (int x = 0; x < mazeSize; x++) {
            vec2 pos = vec2(x, y);
            if (m_Maze.At(pos) == '*') Renderer2D::DrawQuad(pos, vec2(1.0f), Colors::Red());
            if (m_Maze.At(pos) == 'B') Renderer2D::DrawQuad(pos, vec2(1.0f), Colors::Blue());
        }
    }
    Renderer2D::EndScene();
}

void World::PlayerMovement()
{
    bool right = Input::IsKeyPressed(Key::D) || Input::IsKeyPressed(Key::Right);
    bool left = Input::IsKeyPressed(Key::A) || Input::IsKeyPressed(Key::Left);
    bool up = Input::IsKeyPressed(Key::W) || Input::IsKeyPressed(Key::Up);
    bool down = Input::IsKeyPressed(Key::S) || Input::IsKeyPressed(Key::Down);


    int32 horizontal = right - left;
    int32 vertical = up - down;

    vec2 velocity = vec2(horizontal, vertical);

    vec2 tentativePos = m_PlayerPosition + velocity;

    if(m_Maze.At(tentativePos) != '*')
    {
        m_PlayerPosition = tentativePos;
    }
}

void World::CheckGoal()
{
    if(m_Maze.At(m_PlayerPosition) == 'B')
    {
        GenerateMaze();
    }
}

void World::GenerateMaze()
{
    m_Maze.Generate(m_MazeSize);
    //m_Maze.Print();
    m_PlayerPosition = vec2(1);
}
