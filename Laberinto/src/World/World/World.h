#pragma once
#include "World/Maze/Maze.h"
#include "Core/CoreMinimal.h"
#include "Graphics/Resources/Shader/Shader.h"
#include "World/Camera/Camera.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

enum class ProjectionType
{
    ORTHOGRAPHIC = 0,
    PERSPECTIVE = 1
};

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

    void Render2D();
    void Render3D();
private:
    const float m_MouseSensitivity = 0.5f;

    uint32 m_MazeSize = 11;
    vec2 m_PlayerPosition = vec2(1);
    vec2 m_PlayerRotation = vec2(0.0f);
    ProjectionType m_ProjectionType =  ProjectionType::ORTHOGRAPHIC;

    Camera m_Camera;
    Camera m_3DCamera;
    Shader m_QuadShader;
    Shader m_CircleShader;
    Shader m_CubeShader;
    Maze m_Maze;
};
