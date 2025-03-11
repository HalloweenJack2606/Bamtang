#pragma once
#include "Core/CoreMinimal.h"

#define TIME_TO_DISAPPEAR 3.0f
#define GRAVITY (-9.8f)
#define ELASTICITY 0.8f
#define FRICTION 0.04f
#define SPEED_THRESHOLD 0.15f

class Circle
{
public:
    void OnUpdate(float ts);
    void OnRender() const;

    [[nodiscard]] inline bool ShouldDestroy() const noexcept { return m_bShouldDestroy; }
public:
    float radius = 0.5f;
    float thickness = 0.3f;

    vec2 velocity = vec2(0.0f);
    vec2 position = vec2(0.0f);

    Color circleColor = Colors::White();
private:
    bool m_bShouldDestroy = false;
    float m_TimeStill = 0.0f;
};