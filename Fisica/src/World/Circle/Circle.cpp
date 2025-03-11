#include "World/Circle/Circle.h"
#include "Graphics/CircleRenderer/CircleRenderer.h"

void Circle::OnUpdate(float ts)
{
    if(ShouldDestroy()) return;

    float aspectRatio = 800.0f / 600.0f;
    velocity.y += GRAVITY * ts;
    position += velocity * ts;

    if (position.x - radius < -5.0f * aspectRatio) {
        position.x = -5.0f * aspectRatio + radius;
        velocity.x = -velocity.x * ELASTICITY;
    }
    if (position.x + radius > 5 * aspectRatio) {
        position.x = 5.0f * aspectRatio - radius;
        velocity.x = -velocity.x * ELASTICITY;
    }

    if (position.y + radius > 5.0f) {
        position.y = 5.0f - radius;
        velocity.y = -velocity.y * ELASTICITY;
        velocity.x *= (1.0f - FRICTION);
    }
    if (position.y - radius < -5.0f) {
        position.y = -5.0f + radius;
        velocity.y = -velocity.y * ELASTICITY;
    }

    float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (speed > 0.0f) {
        velocity *= (1.0f - FRICTION * 0.1f);
    }


    if(abs(velocity.x) < SPEED_THRESHOLD && abs(velocity.y) < SPEED_THRESHOLD)
    {
        circleColor = Colors::Red();

        m_TimeStill += ts;
        if(m_TimeStill >= TIME_TO_DISAPPEAR) m_bShouldDestroy = true;
    }
    else
    {
        m_TimeStill = 0.0f;
        circleColor = Colors::White();
    }
}

void Circle::OnRender() const
{
    CircleRenderer::DrawCircle(position, thickness, radius * 2.0f, circleColor);
}
