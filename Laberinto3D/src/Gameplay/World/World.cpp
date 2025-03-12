#include "Gameplay/World/World.h"
#include "Graphics/Renderer/Renderer.h"
#include "Input/Input.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <random>

std::random_device g_RDWorld;
std::mt19937 g_RNGWorld(g_RDWorld());

void World::Init()
{
    float fov = 90.0f;
    m_Perspective = glm::perspective(glm::radians(fov), ASPECT_RATIO, 0.1f, 100.0f);
    CalculateViewMatrix();
    GenerateMaze();
}

void World::OnUpdate()
{
    CameraMovement();
    PlayerMovement();
    CheckGoal();

    if(Input::IsKeyPressed(Key::R))
    {
        GenerateMaze();
    }
}

void World::OnRender()
{
    vec3 cubeSize = vec3(1.0f, 1.0f, 1.0f);
    Renderer::BeginScene(m_Perspective * m_View);
    const uint32 mazeSize = m_Maze.GetSize();
    uint32 index = 0;
    for (int y = 0; y < mazeSize; y++)
    {
        for (int x = 0; x < mazeSize; x++)
        {
            vec2 pos = vec2(x, y);
            Color color = (index % 2 == 0) ? Colors::Red() : Colors::NiceYellow();
            if (m_Maze.At(pos) == '*') Renderer::DrawCube(vec3(pos.x, -0.5f, pos.y), cubeSize, 1, color);
            if (m_Maze.At(pos) == 'B') Renderer::DrawCube(vec3(pos.x, -0.5f, pos.y), cubeSize, 1, Colors::Green());
            index++;
        }
    }
    Renderer::DrawCube(vec3(m_Position.x, -0.5f, m_Position.y), cubeSize, 1, Colors::Blue());
    Renderer::DrawCube(vec3(m_WandererPosition.x, -0.5f, m_WandererPosition.y), cubeSize, 1, Colors::White());
    Renderer::EndScene();
}

void World::CameraMovement()
{
    int32 horizontal = Input::IsKeyDown(Key::A) - Input::IsKeyDown(Key::D);
    int32 depth = Input::IsKeyDown(Key::W) - Input::IsKeyDown(Key::S);
    int32 vertical = Input::IsKeyDown(Key::Space) - Input::IsKeyDown(Key::LeftShift);

    vec3 speed = vec3(horizontal, vertical, depth);

    m_CameraPosition += speed * 0.01f;

    CalculateViewMatrix();
}

void World::CalculateViewMatrix()
{
    glm::quat orientation = glm::quat(glm::radians(m_CameraRotation));
    const vec3 front = glm::normalize(orientation * vec3(0.0f, 0.0f, 1.0f));
    const vec3 up = glm::normalize(orientation * vec3(0.0f, 1.0f, 0.0f));
    m_View = glm::lookAt(m_CameraPosition, m_CameraPosition + front, up);
}

void World::PlayerMovement()
{
    int32 horizontal = Input::IsKeyPressed(Key::Left) - Input::IsKeyPressed(Key::Right);
    int32 vertical = Input::IsKeyPressed(Key::Up) - Input::IsKeyPressed(Key::Down);

    vec2 velocity = vec2(horizontal, vertical);
    vec2 tentativePosition = m_Position + velocity;

    if(tentativePosition == m_Position) return;

    if(m_Maze.At(tentativePosition) != '*')
    {
        m_Position = tentativePosition;
        WandererAI();
    }
}

void World::GenerateMaze()
{
    m_Position = vec2(1.0f);
    m_Maze.Generate(m_MazeSize);


    vec2 tentativeWandererPosition = vec2(floor((float)m_MazeSize / 2.0f), floor((float)m_MazeSize / 2.0f));
    vec2 directions[8] = {{0.0f, 1.0f}, {1.0f, 0.0f}, {-1.0f, 0.0f}, {0.0f, -1.0f}, {-1.0f, -1.0f}, {1.0f, 1.0f}, {-1.0f, 1.0f}, {1.0f, -1.0f}};
    int i = 0;
    while(m_Maze.At(tentativeWandererPosition) == '*')
    {
        tentativeWandererPosition = m_WandererPosition;
        tentativeWandererPosition += directions[i++];
        if(i >= 8)
        {
            break;
        }
    }
    m_WandererPosition = tentativeWandererPosition;
}

void World::CheckGoal()
{
    if(m_Maze.At(m_Position) == 'B' || m_Maze.At(m_WandererPosition) == 'B')
    {
        GenerateMaze();
    }
}

void World::WandererAI()
{
    vec2 directions[4] = {{0.0f, 1.0f}, {1.0f, 0.0f}, {-1.0f, 0.0f}, {0.0f, -1.0f}};
    std::shuffle(std::begin(directions), std::end(directions), g_RNGWorld);

    for(auto direction : directions)
    {
        vec2 tentativePosition = m_WandererPosition + direction;
        if(m_Maze.At(tentativePosition) == ' ' || m_Maze.At(tentativePosition) == 'B')
        {
            m_WandererPosition = tentativePosition;
            break;
        }
    }
}
