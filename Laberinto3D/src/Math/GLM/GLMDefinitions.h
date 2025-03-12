#pragma once

#include "glm/glm.hpp"

typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat4 mat3;
typedef glm::mat4 mat4;
typedef vec4 Color;

namespace Colors
{
    inline const vec4 Red() { return vec4(1.0f, 0.0f, 0.0f, 1.0f); }
    inline const vec4 Green() { return vec4(0.0f, 1.0f, 0.0f, 1.0f); }
    inline const vec4 Blue() { return vec4(0.0f, 0.0f, 1.0f, 1.0f); }
    inline const vec4 Black() { return vec4(0.0f, 0.0f, 0.0f, 1.0f); }
    inline const vec4 Clear() { return vec4(0.0f, 0.0f, 0.0f, 0.0f); }
    inline const vec4 Transparent() { return Clear(); }
    inline const vec4 Cyan() { return vec4(0.0f, 1.0f, 1.0f, 1.0f); }
    inline const vec4 Gray() { return vec4(0.5f, 0.5f, 0.5f, 1.0f); }
    inline const vec4 Grey() { return Gray(); }
    inline const vec4 Magenta() { return vec4(1.0f, 0.0f, 1.0f, 1.0f); }
    inline const vec4 White() { return vec4(1.0f, 1.0f, 1.0f, 1.0f); }
    inline const vec4 Yellow() { return vec4(1.0f, 1.0f, 0.0f, 1.0f); }
    inline const vec4 NiceYellow() { return vec4(1.0f, 0.92f, 0.016f, 1.0f); }
}