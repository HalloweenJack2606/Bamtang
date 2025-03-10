#include "World/Camera/Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

Camera::Camera()
{
    RecalculateProjection();
}

void Camera::OnUpdate()
{
    RecalculateView();
}

void Camera::SetPerspective(float verticalFOV, float nearClip, float farClip)
{
    m_ProjectionType = ProjectionType::PERSPECTIVE;
    m_PerspectiveFOV = verticalFOV;
    m_PerspectiveNear = nearClip;
    m_PerspectiveFar = farClip;
    RecalculateProjection();
}

void Camera::SetOrthographic(float size, float nearClip, float farClip)
{
    m_ProjectionType = ProjectionType::ORTHOGRAPHIC;
    m_OrthographicSize = size;
    m_OrthographicNear = nearClip;
    m_OrthographicFar = farClip;
    RecalculateProjection();
}

void Camera::SetViewportSize(uint32 width, uint32 height)
{
    m_uScreenWidth = width;
    m_uScreenHeight = height;
    m_AspectRatio = (float)width / (float)height;
    RecalculateProjection();
}

void Camera::RecalculateProjection()
{
    if (m_ProjectionType == ProjectionType::PERSPECTIVE) {
        m_Projection = glm::perspective(glm::radians(m_PerspectiveFOV), m_AspectRatio, m_PerspectiveNear,
                                        m_PerspectiveFar);
    } else {
        float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
        float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
        float orthoBottom = -m_OrthographicSize * 0.5f;
        float orthoTop = m_OrthographicSize * 0.5f;
        m_Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
    }
}

void Camera::RecalculateView()
{
    auto position = m_Position;
    auto rotation = m_Rotation;

    glm::quat quat = glm::quat(vec3(-rotation.z, -rotation.y, -rotation.x));

    m_ViewMatrix = glm::translate(mat4(1.0f), position) * glm::toMat4(quat);
    m_ViewMatrix = glm::inverse(m_ViewMatrix);
}

vec2 Camera::ScreenToWorldPoint(const vec2& position)
{
    vec2 normalized;
    normalized.x = 2.0f * (position.x / m_uScreenWidth) - 1.0f;
    normalized.y = 1.0f - 2.0f * (position.y / m_uScreenHeight);

    vec4 clipCoords = vec4(normalized.x, normalized.y, m_OrthographicNear, m_OrthographicFar);

    vec4 viewCoords = glm::inverse(m_Projection) * clipCoords;
    viewCoords = glm::vec4(viewCoords.x, viewCoords.y, m_OrthographicNear, 0.0f);

    vec4 worldCoords = glm::inverse(m_ViewMatrix) * viewCoords;

    return vec2(worldCoords) * vec2(1.0f, -1.0f);
}
