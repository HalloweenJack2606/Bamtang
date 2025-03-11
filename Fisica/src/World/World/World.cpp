#include "World/World/World.h"
#include "Input/Input.h"
#include "Graphics/CircleRenderer/CircleRenderer.h"
#include "Graphics/LineRenderer/LineRenderer.h"
#include <glm/gtc/matrix_transform.hpp>

void World::Init()
{
    float orthoSize = 10.0f;
    float aspectRatio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
    float orthoLeft = -orthoSize * aspectRatio * 0.5f;
    float orthoRight = orthoSize * aspectRatio * 0.5f;
    float orthoBottom =  -orthoSize * 0.5f;
    float orthoTop = orthoSize * 0.5f;
    float orthoNear = 0.0f;
    float orthoFar = 10.0f;

    m_Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, orthoNear, orthoFar);

    LineRenderer::Init(m_Projection);
}

void World::OnUpdate(float ts)
{
    std::vector<Circle*> destroyList;
    for(auto* c : m_Circles)
    {
        c->OnUpdate(ts);
        if(c->ShouldDestroy()) destroyList.push_back(c);
    }
    m_Circles.erase(std::remove_if(std::begin(m_Circles), std::end(m_Circles), [](const Circle* circle) { return circle->ShouldDestroy(); }), std::end(m_Circles));
    for(auto* c : destroyList) delete c;

    CheckCollisions();
    Controls(ts);
}

void World::OnRender()
{
    CircleRenderer::BeginScene(m_Projection);
    for(auto* c : m_Circles) c->OnRender();
    auto color = Colors::Blue();
    color.a = 1.0f;
    CircleRenderer::DrawCircle(m_Position, 1.0f, m_BallSize, color);
    CircleRenderer::EndScene();

    float radians = glm::radians(m_Angle - 90.0f);
    vec2 direction = vec2(std::cos(radians), std::sin(radians));

    vec2 endPoint = m_Position + direction * (m_Velocity * 0.25f);

    LineRenderer::DrawLine(m_Position, endPoint, Colors::Red());
}

void World::CheckCollisions()
{
    for (size_t i = 0; i < m_Circles.size(); i++)
    {
        for (size_t j = i + 1; j < m_Circles.size(); j++)
        {
            Circle* a = m_Circles[i];
            Circle* b = m_Circles[j];

            vec2 centerDist = a->position - b->position;
            float distance = std::sqrt(centerDist.x * centerDist.x + centerDist.y * centerDist.y);

            float minDistance = a->radius + b->radius;
            if (distance < minDistance)
            {
                ResolveCollision(a, b);
            }
        }
    }
}

void World::ResolveCollision(Circle* a, Circle* b)
{
    // https://ericleong.me/research/circle-circle/
    vec2 delta = a->position - b->position;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (distance == 0.0f)
    {
        delta = vec2(0.01f, 0.0f);
        distance = 0.01f;
    }

    vec2 normal = delta / distance;

    float overlap = (a->radius + b->radius) - distance;

    float totalSize = a->radius + b->radius;
    float ratioA = a->radius / totalSize;
    float ratioB = b->radius / totalSize;

    a->position += normal * overlap * (1.0f - ratioA);
    b->position -= normal * overlap * (1.0f - ratioB);

    float velAlongNormal = (a->velocity.x * normal.x + a->velocity.y * normal.y) - (b->velocity.x * normal.x + b->velocity.y * normal.y);

    if (velAlongNormal > 0) return;

    float impulseScalar = -(1.0f + ELASTICITY) * (1.0f - FRICTION) * velAlongNormal;

    vec2 impulse = normal * impulseScalar;
    a->velocity += impulse;
    b->velocity -= impulse;
}

void World::Controls(float ts)
{
    {
        int32 horizontal = Input::IsKeyDown(Key::Right) - Input::IsKeyDown(Key::Left);
        int32 vertical = Input::IsKeyDown(Key::Up) - Input::IsKeyDown(Key::Down);
        m_Angle += (float)horizontal * ts * -150.0f;
        m_Velocity += (float)vertical * ts * 20.0f;
        if(m_Velocity < 0.0f) m_Velocity = 0.0f;
        else if(m_Velocity > 20.0f) m_Velocity = 20.0f;
    }

    {
        float aspectRatio = 800.0f / 600.0f;
        float halfCameraSize = 10.0f / 2.0f;
        int32 horizontal = Input::IsKeyDown(Key::D) - Input::IsKeyDown(Key::A);
        int32 vertical = Input::IsKeyDown(Key::W) - Input::IsKeyDown(Key::S);
        m_Position += vec2(horizontal, vertical) * ts * 10.0f;

        if(m_Position.x > halfCameraSize * aspectRatio) m_Position.x = halfCameraSize * aspectRatio;
        if(m_Position.x < -halfCameraSize * aspectRatio) m_Position.x = -halfCameraSize * aspectRatio;
        if(m_Position.y > halfCameraSize) m_Position.y = halfCameraSize;
        if(m_Position.y < -halfCameraSize) m_Position.y = -halfCameraSize;
    }

    if(Input::IsKeyPressed(Key::Space))
    {
        shootBall();
    }
}

void World::shootBall()
{
    auto* c = new Circle();
    c->position = m_Position;
    float radians = glm::radians(m_Angle - 90.0f);
    vec2 velocity = vec2(std::cos(radians), std::sin(radians)) * m_Velocity;
    c->velocity = velocity;
    c->radius = m_BallSize / 2.0f;
    m_Circles.push_back(c);
}
