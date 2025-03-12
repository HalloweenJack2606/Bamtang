#pragma once
#include "Core/CoreMinimal.h"
#include "Gameplay/Maze/Maze.h"

class World
{
public:
    void Init();

    void OnUpdate();
    void OnRender();
private:
    void GenerateMaze();

    void CameraMovement();
    void PlayerMovement();

    void CalculateViewMatrix();

    void CheckGoal();

    void WandererAI();
private:
    uint32 m_MazeSize = 11;
    vec2 m_WandererPosition = vec2(1.0f);
    vec2 m_Position = vec2(1.0f);
    vec3 m_CameraPosition = vec3(5.0f, 6.0f, 5.0f);
    vec3 m_CameraRotation = vec3(90.0f, 0.0f, 0.0f);
    mat4 m_Perspective;
    mat4 m_View;

    Maze m_Maze;
};