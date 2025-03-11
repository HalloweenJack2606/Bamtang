#include "World/World/World.h"
#include "Graphics/Renderer2D/Renderer2D.h"
#include "Input/Input.h"
#include "Graphics/CubeRenderer/CubeRenderer.h"

void World::Init()
{
    m_CubeShader.Init("assets/shaders/cube.glsl");
    m_QuadShader.Init("assets/shaders/quad.glsl");
    m_CircleShader.Init("assets/shaders/circle.glsl");

    m_Camera.SetViewportSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    float halfMazeSize = (float)m_MazeSize / 2.0f - 0.5f;
    m_Camera.SetOrthographic((float)m_MazeSize, 0, 10);
    m_Camera.SetPosition(vec3(halfMazeSize, halfMazeSize, 0.0f));

    m_3DCamera.SetViewportSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    m_3DCamera.SetPerspective(90.0f, 0.1f, 100.0f);
    m_3DCamera.SetPosition(vec3(1.0f, 0.0f, 1.0f));
    m_3DCamera.SetRotation(vec3(0.0f, 0.2f, 0.0f));


    GenerateMaze();
}

void World::OnUpdate()
{
    PlayerMovement();
    m_Camera.OnUpdate();
    m_3DCamera.OnUpdate();
    CheckGoal();

    if(Input::IsKeyPressed(Key::Q))
    {
        if(m_ProjectionType == ProjectionType::ORTHOGRAPHIC)
        {
            m_ProjectionType = ProjectionType::PERSPECTIVE;
        }
        else
        {
            m_PlayerPosition.x = std::round(m_PlayerPosition.x);
            m_PlayerPosition.y = std::round(m_PlayerPosition.y);

            if (m_Maze.At(m_PlayerPosition) == '*')
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    for (int dx = -1; dx <= 1; dx++)
                    {
                        vec2 testPos = m_PlayerPosition + vec2(dx, dy);
                        if (m_Maze.At(testPos) != '*')
                        {
                            m_PlayerPosition = testPos;
                            break;
                        }
                    }
                }
            }
            m_ProjectionType = ProjectionType::ORTHOGRAPHIC;
        }
    }
}

void World::OnRender()
{
    if(m_ProjectionType == ProjectionType::ORTHOGRAPHIC)
    {
        Render2D();
    }
    else
    {
        Render3D();
    }
}

void World::PlayerMovement()
{
    if(m_ProjectionType == ProjectionType::ORTHOGRAPHIC)
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
            m_3DCamera.SetPosition(vec3(m_PlayerPosition.x, 0.0f, m_PlayerPosition.y));
        }
    }
    else
    {
        int32 horizontal = Input::IsKeyDown(Key::D) - Input::IsKeyDown(Key::A);
        int32 vertical = Input::IsKeyDown(Key::W) - Input::IsKeyDown(Key::S);
        float moveSpeed = 0.1f;
        vec3 movement = vec3(0.0f);

        vec3 frontFlat = m_3DCamera.GetFront();
        frontFlat.y = 0.0f;
        frontFlat = glm::normalize(frontFlat);

        movement += frontFlat * static_cast<float>(vertical) * moveSpeed;
        movement += m_3DCamera.GetRight() * static_cast<float>(horizontal) * moveSpeed;

        vec3 tentativePos3D = m_3DCamera.GetPosition() + movement;

        vec2 tentativePos2D = vec2(tentativePos3D.x, tentativePos3D.z);

        if (m_Maze.At(tentativePos2D) != '*')
        {
            m_3DCamera.SetPosition(tentativePos3D);
            m_PlayerPosition = tentativePos2D;
        }
    }

    vec2 delta = Input::GetMouseDelta();
    m_PlayerRotation += delta * m_MouseSensitivity;

    if(m_PlayerRotation.y > 45.0f) m_PlayerRotation.y = 45.0f;
    if(m_PlayerRotation.y < -45.0f) m_PlayerRotation.y = -45.0f;

    m_3DCamera.SetRotation(vec3(-m_PlayerRotation.y, -m_PlayerRotation.x, 0.0f));
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
    m_Maze = Maze();
    m_Maze.Generate(m_MazeSize);
    //m_Maze.Print();
    m_PlayerPosition = vec2(1);
    m_3DCamera.SetPosition(vec3(m_PlayerPosition.x, 0.0f, m_PlayerPosition.y));
}

void World::Render2D()
{
    Renderer2D::SetShader(m_CircleShader);
    Renderer2D::BeginScene(m_Camera);
    Renderer2D::DrawQuad(m_PlayerPosition, vec2(1.0f), Colors::Green());
    Renderer2D::EndScene();

    Renderer2D::SetShader(m_QuadShader);
    Renderer2D::BeginScene(m_Camera);
    const uint32 mazeSize = m_Maze.GetSize();
    for (int y = 0; y < mazeSize; y++)
    {
        for (int x = 0; x < mazeSize; x++)
        {
            vec2 pos = vec2(x, y);
            if (m_Maze.At(pos) == '*') Renderer2D::DrawQuad(pos, vec2(1.0f), Colors::Red());
            if (m_Maze.At(pos) == 'B') Renderer2D::DrawQuad(pos, vec2(1.0f), Colors::Blue());
        }
    }
    Renderer2D::EndScene();
}

void World::Render3D()
{
    vec3 cubeSize = vec3(1.0f, 0.1f, 1.0f);
    CubeRenderer::SetShader(m_CubeShader);
    CubeRenderer::BeginScene(m_3DCamera);
    const uint32 mazeSize = m_Maze.GetSize();
    uint32 index = 0;
    for (int y = 0; y < mazeSize; y++)
    {
        for (int x = 0; x < mazeSize; x++)
        {
            vec2 pos = vec2(x, y);
            Color color = (index % 2 == 0) ? Colors::Red() : Colors::NiceYellow();
            if (m_Maze.At(pos) == '*') CubeRenderer::DrawCube(vec3(pos.x, -0.5f, pos.y), cubeSize, color);
            if (m_Maze.At(pos) == 'B') CubeRenderer::DrawCube(vec3(pos.x, -0.5f, pos.y), cubeSize, Colors::Blue());
            index++;
        }
    }
    CubeRenderer::EndScene();
}
