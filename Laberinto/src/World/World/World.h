#pragma once
#include "World/Maze/Maze.h"
#include "Core/CoreMinimal.h"
#include "Graphics/Resources/Shader/Shader.h"
#include "World/Camera/Camera.h"

class World
{
public:
    void Init();

    void OnUpdate();
    void OnRender();
private:
    void PlayerMovement();
    void CheckGoal();
    void GenerateMaze();
private:
    uint32 m_MazeSize = 51;

    Camera m_Camera;
    Shader m_QuadShader;
    Shader m_CircleShader;
    Maze m_Maze;
    vec2 m_PlayerPosition = vec2(1);
};
