#pragma once
#include "Core/CoreMinimal.h"

class Camera
{
public:
    enum class ProjectionType
    {
	    PERSPECTIVE = 0,
		ORTHOGRAPHIC = 1
    };
public:
    Camera();
    ~Camera() = default;

    void OnUpdate();

    inline void SetPosition(vec3 position) { m_Position = position; }

    void SetPerspective(float verticalFOV, float nearClip, float farClip);
    void SetOrthographic(float size, float nearClip, float farClip);

    void SetViewportSize(uint32 width, uint32 height);

    inline ProjectionType GetProjectionType() const { return m_ProjectionType; }
    inline void SetProjectionType(ProjectionType type) { m_ProjectionType = type; }

    vec2 ScreenToWorldPoint(const vec2& position);

    inline mat4 GetProjectionView() const { return m_Projection * m_ViewMatrix; }
private:
    void RecalculateProjection();
    void RecalculateView();
private:

    ProjectionType m_ProjectionType = ProjectionType::ORTHOGRAPHIC;

    float m_PerspectiveFOV = 45.0f;
    float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1000.0f;

    float m_OrthographicSize = 10.0f;
    float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

    float m_AspectRatio;
    uint32 m_uScreenWidth, m_uScreenHeight = 0;

    mat4 m_Projection = mat4(1.0f);
    mat4 m_ViewMatrix = mat4(1.0f);

    vec3 m_WorldUp = vec3(0.0f, 1.0f, 0.0f);
    vec3 m_Front = vec3(0.0f, 0.0f, -1.0f);
    vec3 m_Right = vec3(1.0f, 0.0f, 0.0f);
    vec3 m_Up = vec3(0.0f, 1.0f, 0.0f);

    vec3 m_Position = vec3(0.0f);
    vec3 m_Rotation = vec3(0.0f);
};
