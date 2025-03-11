#pragma once
#include "Core/CoreMinimal.h"
#include "World/Circle/Circle.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class World
{
public:
    void Init();

    void OnUpdate(float ts);
    void OnRender();
private:
    void CheckCollisions();
    void ResolveCollision(Circle* a, Circle* b);

    void Controls(float ts);

    void shootBall();
private:
    const float m_BallSize = 0.5f;
    const float m_StartingAngle = 0.0f;
    float m_Angle = m_StartingAngle;
    float m_Velocity = 1.0f;
    vec2 m_Position = vec2(0.0f);
    std::vector<Circle*> m_Circles;
    mat4 m_Projection;
};